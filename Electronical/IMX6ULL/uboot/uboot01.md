# IMX6ULL驱动开发uboot篇

## 所以，啥是UBoot

​	我们搞过STM32或者啥其他单片机的朋友都知道，我们的程序想要跑上去，需要一个BOOTLoader来提供一个最基本的，被初始化后的软硬件环境（比如说中断向量要布置好，C语言的栈环境要布置好等等！），对于跑操作系统，想要让一个大系统跑在一个板子上的重要步骤就是提供一个提供一个BootLoader，把操作系统的环境建立好后，才能跑操作系统。就像UEFI/BIOS对于我们的电脑一样，想要跑Windows/Linux，就是需要过一下前者。

​	UBoot的作用就是如此，全称是 Universal Boot Loader，uboot 是一个遵循 GPL 协议的开源软件。

​	按照面像的开发者，我们有三“种”UBoot：

| 种类                    | 描述                                                         |
| ----------------------- | ------------------------------------------------------------ |
| 官方的 uboot 代码       | 由 uboot 官方维护开发的 uboot 版本，版本更新快，基本包含所有常用的芯片。 |
| 半导体厂商的 uboot 代码 | 半导体厂商维护的一个 uboot，专门针对自家的芯片，在对自家芯片支持上要比 uboot 官方的好。 |
| 开发板厂商的 uboot 代码 | 开发板厂商在半导体厂商提供的 uboot 基础上加入了对自家开发板的支持。 |

​	我们学习的初步阶段，就是直接用开发板厂商的 uboot 代码，学透了，再尝试自己修改半导体厂商的 uboot 代码，我们很少碰官方的 uboot 代码，毕竟，除非自己对芯片非常理解，谁会自己踩一大堆有的没的坑？

​	我自己使用的是正点原子的板子，

```shell
#!/bin/sh
# 上面这个是固定格式，可写可不写，写一定不出事

# ARCH=arm
# CROSS_COMPILE=arm-linux-gnueabihf-
# uboot的makefile似乎禁掉了这种方式传递ARCH和CROSS_COMPILE，所以只好:👇
make CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm distclean
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_14x14_ddr512_emmc_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j$(nproc)
```

​	我们直接执行这个脚本，注意，看清楚我们传递的变量直接需要中间存在一个空格，不理解Makefile的朋友我强烈推介先去看看《跟我一起学Makefile》这本书。

​	不管是用何种方式，总而言之，我们一上板子就会得到这个结果。

```
U-Boot 2016.03 (Mar 06 2025 - 00:18:41 -0800)

CPU:   Freescale i.MX6ULL rev1.1 792 MHz (running at 396 MHz)
CPU:   Industrial temperature grade (-40C to 105C) at 48C
Reset cause: POR
Board: I.MX6U ALPHA|MINI
I2C:   ready
DRAM:  512 MiB
MMC:   FSL_SDHC: 0, FSL_SDHC: 1
*** Warning - bad CRC, using default environment

In:    serial
Out:   serial
Err:   serial
switch to partitions #0, OK
mmc1(part 0) is current device
Net:   FEC1
Error: FEC1 address not set.

Normal Boot
Hit any key to stop autoboot:  0 
=>      
```

​	上述信息说了点东西，我们一行行看

1. **U-Boot版本**：2016.03，编译时间为2025年3月6日。对的，就是今天笔者发布的时候编译的。
2. **CPU信息**：Freescale i.MX6ULL rev1.1，运行频率为396 MHz（最大频率为792 MHz），属于工业级温度范围（-40°C 到 105°C），当前温度为48°C。其实i.MX6ULL之前是飞思卡尔的板子，后来飞思卡尔被NXP收购了
3. **复位原因**：POR（上电复位）。
4. **板子信息**：I.MX6U ALPHA|MINI。
5. **I2C**：已准备好。
6. **DRAM**：512 MiB。
7. **MMC**：检测到两个SDHC控制器（FSL_SDHC: 0 和 FSL_SDHC: 1），当前使用的是mmc1的第0分区。
8. **环境变量**：CRC校验失败，使用默认环境变量。
9. **串口**：输入、输出和错误都使用串口。
10. **网络**：FEC1（以太网控制器）未设置MAC地址，导致错误。
11. **自动启动**：系统正在等待用户按键中断自动启动过程，如果没有按键，系统将在0秒后继续启动。

## 使用uboot的命令行完成点事情

```
=> help
?       - alias for 'help'
base    - print or set address offset
bdinfo  - print Board Info structure
bmode   - sd1|sd2|qspi1|normal|usb|sata|ecspi1:0|ecspi1:1|ecspi1:2|ecspi1:3|esdhc1|esdhc2|esdhc3|esdhc4 [noreset]
boot    - boot default, i.e., run 'bootcmd'
bootd   - boot default, i.e., run 'bootcmd'
bootelf - Boot from an ELF image in memory
bootm   - boot application image from memory
bootp   - boot image via network using BOOTP/TFTP protocol
...
```

​	等等，具体查询一个指令，我们直接在help后面跟上指令就好了。

```
=> help bootz
bootz - boot Linux zImage image from memory

Usage:
bootz [addr [initrd[:size]] [fdt]]
    - boot Linux zImage stored in memory
	The argument 'initrd' is optional and specifies the address
	of the initrd in memory. The optional argument ':size' allows
	specifying the size of RAW initrd.
	When booting a Linux kernel which requires a flat device-tree
	a third argument is required which is the address of the
	device-tree blob. To boot that kernel without an initrd image,
	use a '-' for the second argument. If you do not pass a third
	a bd_info struct will be passed instead
```

## bdinfo, printenv和version

​	查询板子的信息等内容全靠这三个。

> 这些就是板子的具体硬件信息

```
=> bdinfo
arch_number = 0x00000000
boot_params = 0x80000100
DRAM bank   = 0x00000000
-> start    = 0x80000000
-> size     = 0x20000000
eth0name    = FEC1
ethaddr     = (not set)
current eth = FEC1
ip_addr     = <NULL>
baudrate    = 115200 bps
TLB addr    = 0x9FFF0000
relocaddr   = 0x9FF55000
reloc off   = 0x18755000
irq_sp      = 0x9EF52EA0
sp start    = 0x9EF52E90

```

> version用来查看uboot编译的具体信息

```
U-Boot 2016.03 (Mar 06 2025 - 00:18:41 -0800)
arm-linux-gnueabihf-gcc (Linaro GCC 4.9-2017.01) 4.9.4
GNU ld (GNU Binutils for Ubuntu) 2.26.1
```

> printenv也可以简单的写成print，我们后面查看环境信息使用的就是这个玩意。

## 环境变量

​	是的，uboot自身也有一个最小环境变量系统。我们使用setenv来设置环境变量，想要持久化就需要使用saveenv指令完成固化

```
=> print bootdelay
bootdelay=1
=> setenv bootdelay 5
=> saveenv
Saving Environment to MMC...
Writing to MMC(1)... done
```

 	删除一个环境变量也是非常的简单，直接设置这个环境变量为空即可。

## 内存操作

​	md 命令用于显示内存值

```
md[.b, .w, .l] address [# of objects] 
```

​	举个例子，我们想要看启动0x87800000启动地址处的后20个字节放置了怎样的二进制数据的时候，显然，一个：

```
=> md.b 87800000 14
87800000: be 00 00 ea 14 f0 9f e5 14 f0 9f e5 14 f0 9f e5    ................
87800010: 14 f0 9f e5                                        ....
```

​	是0x14而不是14，因为uboot的操作数默认都是16位的。至于w和l，就是我们的长度单位，b是字节，w是字，l就是双字

​	nm 命令 用于修改指定地址的内存值，命令格式如下： 

```
nm [.b, .w, .l] address 
```

​	mm 命令 也是修改指定地址内存值的，使用 mm 修改内存值的时候地址会自增，而使用命 令 nm 的话地址不会自增。比如以.l 格式修改从地址 0x80000000 开始的连续3 个内存块(3*4=12 个字节)的数据为 0x12345678

```
=> mm.l 80000000
80000000: ffffffff ? 12345678
80000004: ffffffff ? 12345678 
80000008: ffffffff ? 12345678
8000000c: ffffffff ? q
```

​	看看丁不丁真：

```
=> md.b 80000000 c
80000000: 78 56 34 12 78 56 34 12 78 56 34 12                xV4.xV4.xV4.
```

​	 命令mw 用于使用一个指定的数据填充一段内存，相比起来直接简化了mm指令。cp 是数据拷贝命令，用于将 DRAM 中的数据从一段内存拷贝到另一段内存中，或者把Nor Flash 中的数据拷贝到DRAM 中，cmp 是比较命令，用于比较两段内存的数据是否相等
