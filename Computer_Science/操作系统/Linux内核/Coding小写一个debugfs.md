# Coding:小写一个debugfs

​	上一次整活还是在上一个月，写了一个简单的module并且熟悉了module的挂载查看和卸载。这一次我们自然玩一个大的，就是利用linux的debugfs API写一个调试文件系统。

​	事实上，底层的API全写好了，我们就是简单的调调API就成的事情！

## 事先检查

​	第一步是检查我们当前的内核是否支持debugfs调试：

```
zcat /proc/config.gz | grep DEBUG_FS
# CONFIG_XEN_DEBUG_FS is not set
CONFIG_BLK_DEBUG_FS=y
CONFIG_BLK_DEBUG_FS_ZONED=y
# CONFIG_SCSI_SNIC_DEBUG_FS is not set
# CONFIG_SCSI_LPFC_DEBUG_FS is not set
# CONFIG_USB_GADGET_DEBUG_FS is not set
# CONFIG_OCFS2_DEBUG_FS is not set
CONFIG_DEBUG_FS=y
CONFIG_DEBUG_FS_ALLOW_ALL=y
# CONFIG_DEBUG_FS_DISALLOW_MOUNT is not set
# CONFIG_DEBUG_FS_ALLOW_NONE is not set
```

​	在这里，我们是要查看的是：`CONFIG_DEBUG_FS=y`，在这件事情上，如果是n，说明当前内核是不支持调试文件系统的，这就要求我们另外编译内核（打开这个开关），安装并进入内核才行。这里不再赘述如何自定义内核了。

## 开干

​	我们的文件系统有自己的一套fops，这里，也不是意外的。和我们对文件系统自身的认知，我们知道文件系统实际上就是提供一种对目标设备一套被抽象出来的访问读写等若干操作的句柄。所以我们所需要做的就是自己实现这一套句柄。显然我们需要实现的有打开文件 ，读文件以及写文件，这是最基本的！

​	我们的文件系统将会以模块的方式动态的加载到内核。所以这就要求我们需要先掌握学习如何编写模块的知识，这个在我之前的博客里有所提到。[关于如何在Arch Linux上编写自己的第一个module_archlinux modules-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/139374482?spm=1001.2014.3001.5502)

​	各位看官之前并没有了解到这方面的知识，可以阅读我上面所写的博客等掌握这个知识之后，再进行下一步的实践。

​	现在，我们沿用写模块的Makefile:

```
obj-m:= charlie.o
pwd:= $(shell pwd)
ker-ver:= $(shell uname -r)
KDIR:= /lib/modules/$(ker-ver)/build
# 下面这一行是用来调试的
# ccflags-y	+= -DDEBUG -g -ggdb -gdwarf-4 -Og \
				-Wall -fno-omit-frame-pointer -fvar-tracking-assignments

all:
	make -C $(KDIR) M=$(pwd) modules # 先调整一下目录，用人家的Makefile

clean:
	rm -rf *.o .* .cmd *.ko *.mod.c .tmp_versions *.order *.symvers *.mod写代码！
```

## 撸代码

​	我们首先需要引入写模块和调试文件系统的基本头文件。

```
#include <linux/debugfs.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/types.h>
```

​	然后完成读写，打开等基本操作。

```
static int charlie_fs_open(struct inode* inode, struct file* pfile)
{
// 函数是打开某一个文件，准备进行读或者写。
    printk("Charlie_filesystem_open\n");
    pfile->private_data = inode->i_private;
    return 0;
}


static ssize_t charlie_fs_read(struct file* pFile, char __user *buf, size_t cnt, loff_t* offp)
{
// 函数完成的任务是对传入进来的内存块进行存入buf里。
    int retval = 0;
    if((*offp + cnt) > 512)
        cnt = 512 - *offp;
// printk函数主要是向控制台打印一些控制信息，这个信息需要通过这条指令进行查看: sudo dmesg
    printk("Received read request! count:%ld, offset:%lld\n", cnt, *offp);
    if(copy_to_user(buf, charlie_buf + *offp, cnt)){
    	// 警告！
        pr_warn("Oh no, failed to copy to user! count is %ld\n", cnt);
        retval = -EFAULT;
        goto out;
    }
    *offp += cnt;
    retval = cnt;
out:
    return retval; 
}

static ssize_t charlie_fs_write(struct file* pFile, const char __user *buf, size_t cnt, loff_t* offp)
{
// 函数完成的任务是向文件块进行写入。
    int retval;
    pr_info("Write request is here: count: %ld, offset:%lld\n", cnt, *offp);
    if(*offp > 512)
        return 0;
    if((*offp + cnt) > 512)
        cnt = 512 - *offp;
    if(copy_from_user(charlie_buf + *offp, (const void*)buf, cnt)){
        pr_warn("Oh no, failed to copy from user! count is %ld\n", cnt);
        retval = -EFAULT;
        goto out;
    }
    *offp += cnt;
    retval = cnt;
out:
    return retval; 
}
```

​	关于这里的几个所用到的函数都是什么意思，各位看官可自行百度更加详细的说明！

​	我们的文件系统是通过模块进行载入和卸载的，这就意味着我们仍然需要写初始化函数和析构函数。我们所做的就是要在初始化的时候完成对文件系统处理函数的注册。即在卸载文件系统的时候，移除我们在初始化时进行注册的相关函数。

```
// 句柄
struct file_operations charlie_fs_fops = {
    .owner = THIS_MODULE,
    .read = charlie_fs_read,
    .write = charlie_fs_write,
    .open = charlie_fs_open
};


// 模块的初始化
static int __init charlie_debug_fs_init(void)
{
    pr_info("The module is initing...");
    charlie_dir = debugfs_create_dir("Charliedir", NULL);
    if(!charlie_dir){
        pr_crit("Failing shit! can not create any dir at all!");
        goto failed;
    }

    static struct dentry* sub_charlie_dir;
    sub_charlie_dir =  debugfs_create_dir("CharlieSubDir", charlie_dir);
        if(!sub_charlie_dir){
        pr_crit("Failing shit! can not create any sub dir at all!");
        goto failed;
    }

    struct dentry* filent = debugfs_create_file("Charlie", 0644, sub_charlie_dir, NULL, &charlie_fs_fops);
    if(!filent){
        pr_err("Can not create file!");
        goto failed;
    }
    pr_info("Init finish!");
    return 0;
failed:
    return -ENOENT;
}

// 模块的析构函数
static void __exit charlie_debug_fs_exit(void)
{
    pr_info("Safe quit! begin");
    debugfs_remove_recursive(charlie_dir);
    pr_info("Safe quit! end");
}

module_init(charlie_debug_fs_init);
module_exit(charlie_debug_fs_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Charliechen");
```

​	到这里我们保存，然后make一下

```
make -C /lib/modules/6.9.7-arch1-1/build M=/home/Charliechen/Works/opearte_system/module/test2 modules
make[1]: Entering directory '/usr/lib/modules/6.9.7-arch1-1/build'
  CC [M]  /home/Charliechen/Works/opearte_system/module/test2/charlie.o
  MODPOST /home/Charliechen/Works/opearte_system/module/test2/Module.symvers
  CC [M]  /home/Charliechen/Works/opearte_system/module/test2/charlie.mod.o
  LD [M]  /home/Charliechen/Works/opearte_system/module/test2/charlie.ko
  BTF [M] /home/Charliechen/Works/opearte_system/module/test2/charlie.ko
make[1]: Leaving directory '/usr/lib/modules/6.9.7-arch1-1/build'
```

```
➜  sudo insmod charlie.ko && lsmod | grep charlie
[sudo] password for Charliechen: 
charlie                16384  0
```

​	看到我们的模块已经被正确的挂载！下一步，则是测试我们写的一系列功能。

```
➜  sudo ls /sys/kernel/debug/ | grep Charliedir
Charliedir
➜  sudo ls /sys/kernel/debug/Charliedir
CharlieSubDir
➜  sudo ls /sys/kernel/debug/Charliedir/CharlieSubDir
Charlie
➜  su
Password: 
[root@ArchLinux test2]# ls
charlie.c  charlie.ko  charlie.mod  charlie.mod.c  charlie.mod.o  charlie.o  Makefile  modules.order  Module.symvers
[root@ArchLinux test2]# sudo insmod charlie.ko && lsmod | grep charlie
charlie                16384  0
[root@ArchLinux test2]# echo 114514 > /sys/kernel/debug/Charliedir/CharlieSubDir/Charlie
[root@ArchLinux test2]# dmesg | tail -4
[18109.769088] The module is initing...
[18109.769097] Init finish!
[18117.722104] Charlie_filesystem_open
[18117.722177] Write request is here: count: 7, offset:0
[root@ArchLinux test2]# cat /sys/kernel/debug/Charliedir/CharlieSubDir/Charlie 
114514

[root@ArchLinux test2]# dmesg | tail -7
[18109.769088] The module is initing...
[18109.769097] Init finish!
[18117.722104] Charlie_filesystem_open
[18117.722177] Write request is here: count: 7, offset:0
[18147.692623] Charlie_filesystem_open
[18147.692645] Received read request! count:512, offset:0
[18147.692666] Received read request! count:0, offset:512
[root@ArchLinux test2]# rmmod charlie.ko
[root@ArchLinux test2]# dmesg | tail -8
[18109.769088] The module is initing...
[18109.769097] Init finish!
[18117.722104] Charlie_filesystem_open
[18117.722177] Write request is here: count: 7, offset:0
[18147.692623] Charlie_filesystem_open
[18147.692645] Received read request! count:512, offset:0
[18147.692666] Received read request! count:0, offset:512
[18165.395570] Safe quit! begin
```

​	完成！
