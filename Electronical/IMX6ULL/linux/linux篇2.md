# IMX6ULL驱动开发Linux篇02——移植Rootfs

## 编译rootfs

​	我们下面做的活就是移植rootfs，咱们打算是从NFS上走（网络文件系统）。笔者使用的rootfs是走的1.29.0的版本，之后要作点魔改。

​	首先就是取消我们的shell限制，好像这里的源码写的稍微有点问题——就是支持Unicode了但是shell打印字符的时候还是会查ASCII码来比较，如果是纯英文选手那没关系

​	修改libbb/printable_string.c下的printable_string函数

```c
const char* FAST_FUNC printable_string(uni_stat_t *stats, const char *str)
{
	char *dst;
	const char *s;

	s = str;
	while (1) {
		unsigned char c = *s;
		if (c == '\0') {
			/* 99+% of inputs do not need conversion */
			if (stats) {
				stats->byte_count = (s - str);
				stats->unicode_count = (s - str);
				stats->unicode_width = (s - str);
			}
			return str;
		}
		if (c < ' ')
			break;
		s++;
	}

#if ENABLE_UNICODE_SUPPORT
	dst = unicode_conv_to_printable(stats, str);
#else
	{
		char *d = dst = xstrdup(str);
		while (1) {
			unsigned char c = *d;
			if (c == '\0')
				break;
			if (c < ' ')
				*d = '?';
			d++;
		}
		if (stats) {
			stats->byte_count = (d - dst);
			stats->unicode_count = (d - dst);
			stats->unicode_width = (d - dst);
		}
	}
#endif
	return auto_string(dst);
}
```

​	修改libbb/unicode.c

```c
static char* FAST_FUNC unicode_conv_to_printable2(uni_stat_t *stats, const char *src, unsigned width, int flags)
{
	char *dst;
	unsigned dst_len;
	unsigned uni_count;
	unsigned uni_width;

	if (unicode_status != UNICODE_ON) {
		char *d;
		if (flags & UNI_FLAG_PAD) {
			d = dst = xmalloc(width + 1);
			while ((int)--width >= 0) {
				unsigned char c = *src;
				if (c == '\0') {
					do
						*d++ = ' ';
					while ((int)--width >= 0);
					break;
				}
				// 改了这个！！！把后面小于0x7F的部分删掉
				*d++ = (c >= ' ') ? c : '?';
				src++;
			}
			*d = '\0';
		} else {
			d = dst = xstrndup(src, width);
			while (*d) {
				unsigned char c = *d;
				if (c < ' ' || c >= 0x7f)
					*d = '?';
				d++;
			}
		}
		if (stats) {
			stats->byte_count = (d - dst);
			stats->unicode_count = (d - dst);
			stats->unicode_width = (d - dst);
		}
		return dst;
	}
	...
```

​	然后就是尝试编译了

```
make  ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- defconfig
```

​	我们还需要图形化微操。第一个事情是检查——检查我们是动态库编译：

![image-20250309104245997](./linux篇2/image-20250309104245997.png)

​	第二个事情是使用vi风格的命令行

![image-20250309104304109](./linux篇2/image-20250309104304109.png)

​	第三个事情是采取比较全面的编译

![image-20250309104321666](./linux篇2/image-20250309104321666.png)

​	以及确保我们的mdev是选中的

![image-20250309104335945](./linux篇2/image-20250309104335945.png)

​	最后使能Unicode

![image-20250309104346883](./linux篇2/image-20250309104346883.png)

```
make  ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j12
make  ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- CONFIG_PREFIX=/home/charliechen/linux/nfs/rootfs install
```

​	install的时候，需要安装到我们挂载nfs的位置上

## 添加lib库

​	原本的rootfs非常稀少，需要我们自己添加lib，我们把编译器中使用到的库复制粘贴一下：



​	先进入自己家的arm-gcc下的`arm-linux-gnueabihf/libc/lib`，拷贝所有的库

```
cp *so* *.a /home/charliechen/linux/nfs/rootfs/lib/ -d 
```

​	以及`arm-linux-gnueabihf/lib`

```
cp *so* *.a /home/charliechen/linux/nfs/rootfs/lib/ -d 
```

​	我们在rootfs下的usr目录下新建一个lib目录，然后到`arm-linux-gnueabihf/libc/usr/lib`下拷贝

```
cp *so* *.a /home/charliechen/linux/nfs/rootfs/usr/lib/ -d 
```

```
charliechen@ubuntu:~/linux/nfs/rootfs$ du lib usr/lib/ -sh
59M	lib
67M	usr/lib/
```

​	OK，我们下一步就是设置一下板子的bootargs

```
bootargs=console=ttymxc0,115200 root=/dev/nfs nfsroot=192.168.137.10:/home/charliechen/linux/nfs/rootfs,proto=tcp rw ip=192.168.137.4:192.168.137.10:192.168.137.1:255.255.255.0::eth0:off
```

​	Documentation/filesystems/nfs/nfsroot.txt下是有告诉你如何如何使用nfs挂载的，笔者这里整理一下：

```
root=/dev/nfs nfsroot=[服务器IP]:[根文件系统路径],[NFS 选项] ip=[客户端IP]:[服务器IP]:[网关IP]:[子网掩码]:[主机名]:[设备]:[自动配置]:[DNS0]:[DNS1]
```

- 服务器 IP 地址是存放根文件系统的主机 IP，例如 我的就是Ubuntu嘛！192.168.137.10，麻烦自己在ubuntu主机上ifconfig一下
- 根文件系统的存放路径例，笔者的是 /home/charliechen/linux/nfs/rootfs。
- NFS 选项一般不设置，但是这里我们强调使用proto=tcp rw，表达使用TCP协议来完成挂载
- 客户端 IP 地址是开发板的 IP，需与服务器同一网段，且未被占用，我选择了 192.168.137.4，这个IP有没有效，很简单，跑到主机上ping一下，**要求是没有人应答，说明没有人占用这个IP，这个IP就可以被分配到板子上**。
- 网关地址，参考我咋搞uboot的，这里沿用 192.168.137.1。
- 子网掩码例如 255.255.255.0。
- 主机名一般不设置，可留空。
- 设备名是网卡名称，例如 eth0、eth1。本例中使用 ENET2，对应 eth0。
- 自动配置一般设为 off。
- DNS 服务器 IP 一般不使用，可留空。

​	完事，启动一下

![image-20250309105254445](./linux篇2/image-20250309105254445.png)

​	Oh，出现这个问题了，需要我们补充一下rcS

```
#!/bin/sh

PATH=/sbin:/bin:/usr/sbin:/usr/bin:$PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lib:/usr/lib
export PATH LD_LIBRARY_PATH
mount -a
mkdir -p /dev/pts
mount -t devpts devpts /dev/pts

echo /sbin/mdev > /proc/sys/kernel/hotplug
mdev -s
```

​	我们很快还有了新的错误，一个个来

```
mount: can't read '/etc/fstab': No such file or directory
/etc/init.d/rcS: line 10: can't create /proc/sys/kernel/hotplug: nonexistent directory
mdev: /sys/dev: No such file or directory

```

## 创建fstab文件

​	这个笔者跟之有交集是很早的事情了，当时沉迷Arch，就因为这个文件把系统搞崩过，这个文件实际上就是告知自动挂载的分区

​	创建/etc/fstab文件

```
proc	/proc	proc	defaults	0	0
tmpfs	/tmp	tmpfs	defaults	0	0
sysfs	/sys	sysfs	defaults	0	0
```

## 创建/etc/inittab文件

​	init 程序会读取/etc/inittab这个文件做一些事情，我们也要这样做。

```
::sysinit:/etc/init.d/rcS
console::askfirst:-/bin/sh
::restart:/sbin/init
::ctrlaltdel:/sbin/reboot
::shutdown:/bin/umount -a -r
::shutdown:/sbin/swapoff -a
```

## 启动开发板检查一下

```
VFS: Mounted root (nfs filesystem) on device 0:15.
devtmpfs: mounted
Freeing unused kernel memory: 400K (8090e000 - 80972000)

Please press Enter to activate this console. 
/ # 

```

​	没有问题，我们下面做其他测试

## 测试一下程序能不能跑

```
#include <stdio.h> 
   
int main(void) 
{ 
    while(1) { 
        printf("Hello!!! My Really Tiny Linux!!!\r\n"); 
        sleep(2); 
    } 
    return 0; 
}
```

```
charliechen@ubuntu:~/IMX6ULL_Programming_Code/test/rfs$ arm-linux-gnueabihf-gcc hello.c -o hello
charliechen@ubuntu:~/IMX6ULL_Programming_Code/test/rfs$ ls
hello  hello.c
charliechen@ubuntu:~/IMX6ULL_Programming_Code/test/rfs$ file hello
hello: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, for GNU/Linux 2.6.31, BuildID[sha1]=93e70461bd94c25c5d7aa8a1663265cbc753f128, not stripped
```

​	测试一下

```
/ # ls
bin      etc      lib      mnt      root     sys      usr
dev      hello    linuxrc  proc     sbin     tmp
/ # ./hello 
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!
Hello!!! My Really Tiny Linux!!!

```

## 测试一下中文

```
/ # mkdir 你好！
/ # ls
bin        etc        linuxrc    proc       sbin       tmp        你好！
dev        lib        mnt        root       sys        usr
/ 
/ # cd 你好！
/你好！ # ls
/你好！ # cd ..
/ # ls
bin        etc        linuxrc    proc       sbin       tmp        你好！
dev        lib        mnt        root       sys        usr
```

​	OK,基本完事了！