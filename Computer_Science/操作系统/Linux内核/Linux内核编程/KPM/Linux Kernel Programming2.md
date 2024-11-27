# Linux Kernel Programming 2

## 书写内核框架

​	首先，我们需要确认的是我们的内核是适合写Module的，办法老简单了。

```
zcat /proc/config.gz | grep MODULES
```

![enable_module](./Linux Kernel Programming2/enable_module.png)

> 当然这个事情有点递归了，支持存在config,gz查看的适合还需要你的内核支持 `CONFIG_IKCONFIG` 和 `CONFIG_IKCONFIG_PROC`，不过好在绝大部分的发行版和内核的构建都是支持的

当然，想要开发module，对于本机上的模块，我们需要保证：

- 本机有目标平台上的GCC模块
- 本机上有Linux目标内核的头文件

​	就这样，完事。

## 起手我们需要理解的是：用户态和内核态

​	现代微处理器至少支持两种特权级别的代码执行。举一个现实世界的例子，Intel/AMD x86[-64] 系列支持四种特权级别（它们称之为环级别），**AArch32（ARM-32）微处理器系列支持多达七种模式（ARM 称之为执行模式；其中六种是特权模式，一种是非特权模式）**，

​	AArch64（ARM-64/ARMv8）微处理器系列支持四种异常级别（EL0 至 EL3，其中 EL0 特权级别最低，EL3 特权级别最高）。这里的关键点是，为了平台的安全性和稳定性，在这些处理器上运行的所有现代操作系统都将使用（至少）两个特权级别（或模式）的执行，从而将虚拟地址空间 (VAS) 分成两个明确区分的（虚拟）地址空间： 用户空间：用于在非特权用户模式下运行的应用程序。所有应用程序（进程和线程）都将在此空间中以此特权执行。

​	现在，您可能正在使用浏览器、编辑器、PDF 阅读器、终端、电子邮件客户端等。它们都是应用程序 - 最终是进程和线程；在 Linux 上，它们都在用户空间中以用户模式执行，这是非特权的。 我们很快就会明白特权和非特权的确切含义。 内核空间：用于在特权模式（内核模式）下运行的内核（及其所有组件）。这是操作系统及其内部内容的领域（如驱动程序、网络、I/O 等，包括内核模块）。它们都以操作系统特权运行；

​	实际上，它们可以做任何它们想做的事情！请注意，此特权级别是硬件功能，与是否以 root 身份运行不同（这是纯软件产物）；在许多情况下，以内核特权运行可以被视为以 root 身份有效运行。下图显示了此基本架构：

![image-20241101222331775](./Linux Kernel Programming2/image-20241101222331775.png)

​	

### 库和系统调用 API

​	用户空间应用程序通常依赖应用程序编程接口 (API) 来执行其工作。库本质上是 API 的集合或存档，允许您使用标准化、编写良好且经过充分测试的接口（并利用常见的好处：不必重新发明轮子、可移植性、标准化等）。

​	其中，所有用户模式 Linux 应用程序（可执行文件）都“自动链接”到一个重要的、始终使用的库中：glibc - GNU 标准 C 库，您将会了解到。但是，库仅在用户模式下可用；内核不使用这些用户模式库（有关此内容的更多信息，请参阅下一章）。库 API 的示例包括众所周知的 printf(3)、scanf(3)、strcmp(3)、malloc(3) 和 free(3)。 （回想一下在线章节“内核工作区设置”中的“使用 Linux 手册页”部分。）

​	现在，一个关键点：如果用户和内核是独立的地址空间并且具有不同的特权级别，那么用户进程（正如我们刚刚了解到的，仅限于用户空间）如何访问内核？简短的回答是：通过系统调用。系统调用是一种特殊的 API，因为它是用户空间进程（或线程）访问内核的唯一合法（同步）方式。换句话说，系统调用是进入内核空间的唯一合法入口点。

​	它们（系统调用）具有从非特权用户模式切换到特权内核模式的内置能力系统调用的示例包括 fork(2)、execve(2)、open(2)、read(2)、write(2)、socket(2)、accept(2)、chmod(2) 等等。

### 内核空间组件

当今的 Linux 内核是一个相当庞大和复杂的庞然大物。在内部，它由几个主要的子系统和多个组件组成。对内核子系统和组件进行广泛列举可得出以下列表：

1. 核心内核：此代码处理任何现代操作系统的典型核心工作，包括（用户和内核）进程和线程创建/销毁、CPU 调度、同步原语、信号、计时器、中断处理、命名空间、cgroup、模块支持、加密等。

2. 内存管理 (MM)：处理所有与内存相关的工作，包括内核和进程虚拟地址空间 (VAS) 的设置和维护。
   VFS（用于文件系统支持）：虚拟文件系统交换机 (VFS) 是 Linux 内核中实现的实际文件系统的抽象层（例如，ext[2|4]、vfat、ntfs、msdos、iso9660、f2fS、ufS 等等）。

3. 块 I/O：实现实际文件 I/O 的代码路径，从文件系统一直到块设备驱动程序以及其间的所有内容（真的，相当多！）都包含在这里。
   网络协议栈：Linux 以其精确、符合 RFC 要求的高质量实现而闻名，这些协议在模型的所有层上都众所周知（和不太知名的）网络协议，其中 TCP/IP 可能是最著名的。
   进程间通信 (IPC) 支持：IPC 机制的实现在这里完成； Linux 支持消息队列、共享内存、信号量（包括较旧的 SysV 和较新的 POSIX）和其他 IPC 机制。

4. 声音支持：实现音频的所有代码都在这里，从固件到驱动程序和编解码器。

5. 虚拟化支持：Linux 已在大型和小型云提供商中变得非常受欢迎，一个重要原因是其高质量、低占用空间的虚拟化引擎，即基于内核的虚拟机 (KVM)。

![image-20241101223713359](./Linux Kernel Programming2/image-20241101223713359.png)

​	上面的架构说的很明白了：Linux是一个宏内核，在这个巨大的内核内部是多个子系统之间协调的工作。

​	您应该知道的另一个事实是，**这些地址空间当然是虚拟地址空间，而不是物理地址空间。内核将在页面粒度级别将虚拟页面映射到物理页面框架，利用硬件块（例如内存管理单元 (MMU) 和处理器以及转换后备缓冲区 (TLB) 缓存）来提高效率**。它通过使用主内核分页表将内核虚拟页面映射到物理框架 (RAM) 来实现这一点，并且对于每个处于活动状态的用户空间进程，它通过每个进程的单独分页表将进程的（用户）虚拟页面映射到物理页面框架

## 探索 LKM（Linux Kernel Module体系）

​	内核模块是一种提供内核级功能的方法，无需在内核源代码树和静态内核映像中工作。

​	想象一下您必须向 Linux 内核添加支持功能的场景——可能是一个新的设备驱动程序，以便使用某个硬件外围芯片、新的文件系统或新的 I/O 调度程序。实现此目的的一种方法是显而易见的：使用新代码更新内核源代码树，然后对其进行配置、构建、测试和部署。

​	虽然这看起来很简单，但工作量很大——我们编写的代码的每一个更改，无论多么小，都需要我们重建内核映像，然后重新启动系统以进行测试。一定有一个更干净、更简单的方法；事实上，确实有——LKM 框架！

### LKM 框架

​	LKM 框架是一种**编译内核代码的方法，通常在内核源代码树之外，通常称为“树外”代码**，在有限的意义上使其独立于内核，然后将生成的“模块对象”插入或插入内核内存、内核 VAS，让它运行并执行其工作，然后从内核内存中删除（或拔出）。（请注意，LKM 框架也可用于生成树内内核模块，就像我们在构建内核时所做的那样。这里，我们重点介绍树外模块）。

​	内核模块的源代码通常由一个或多个 C 源文件、头文件和一个 Makefile 组成，并（当然是通过 make）构建到内核模块中。内核模块本身只是一个二进制对象文件，而不是二进制可执行文件。在 Linux 2.4 及更早版本中，内核模块的文件名带有 .o 后缀；在现代 2.6 Linux 及更高版本上，它反而具有 .ko（内核对象）后缀。构建后，您可以在运行时将此 .ko 文件（内核模块）插入到实时内核中，从而有效地使其成为内核的一部分。

​	请注意，并非所有内核功能都可以通过 LKM 框架提供。**几个核心功能（例如核心 CPU（任务）调度程序代码、内存管理、信号、计时器、中断管理代码路径、用于驱动引脚控制器、时钟等的平台特定驱动程序）只能在内核本身内开发。**同样，内核模块仅允许访问完整内核 API 和数据变量的子集；稍后将对此进行详细介绍。

​	我们如何插入内核模块呢？答案是通过 insmod 实用程序：

![image-20241106100357529](./Linux Kernel Programming2/image-20241106100357529.png)

​	蓝色框中，我们调用了内核的Makefile辅助我们生成模块文件，现在，我们调用insmod程序将内核安排到了可以被索引的内存控件当中，现在我们的内核就可以找到这个模块然后启动这个模块内部的代码了

​	内核模块被加载到内核内存中并驻留在其中 - 即内核为其分配的空间区域中的内核 VAS。毫无疑问，它是内核代码并以内核权限运行。这样，我们不必每次都重新配置、重建和重新启动系统。您所要做的就是编辑内核模块的代码，重建它，从内存中删除旧副本（如果存在），然后插入新版本。它节省时间并提高生产力。话虽如此，在现实世界中，即使是内核模块也可能导致系统级崩溃（并且确实会导致），从而需要重新启动系统（在隔离的 VM 中运行有利的另一个原因）。内核模块有利的另一个原因是它们适合动态产品配置。例如，内核模块可以设计为以不同的价格点提供不同的功能；为嵌入式产品生成最终映像的脚本可以根据客户愿意支付的价格安装一组给定的内核模块。这是该技术在调试或故障排除场景中如何利用的另一个示例：内核模块可用于动态生成现有产品的诊断和调试日志。诸如 Kprobes 之类的技术允许这样做

​	实际上，LKM 框架为我们提供了一种动态扩展内核功能的方法，允许我们将实时代码插入（然后从）内核内存中删除。这种随心所欲地插入和拔出内核功能的能力让我们意识到 Linux 内核并不是纯粹的整体式的，它也是模块化的。

### 内核源代码树中的内核模块

事实上，内核模块对象对我们来说并不完全陌生。在我们构建源码内核的时候就已经干过类似的事情了。内核模块作为内核构建过程的一部分并安装了它们。回想一下，这些内核模块是内核源代码的一部分，并且已通过在 tristate 内核菜单配置提示中选择 M 将其配置为模块。它们安装在 /lib/modules/$(uname -r)/ 下的目录中。因此，要了解我们当前运行的 x86_64 Ubuntu 22.04 LTS 客户内核下安装的内核模块，我们可以执行以下操作：

```
lsb_release -a 2>/dev/null |grep Description 
```

​	可以看到存在一大堆的模块！想想看，这是有道理的：分销商无法提前确切知道用户最终会使用什么硬件外围设备（尤其是在 x86 PC 等通用计算机上）。内核模块是一种方便的手段，可以支持大量硬件，而不会使内核映像文件（例如 bzImage 或 Image 文件）变得非常臃肿。我们的 Ubuntu Linux 系统安装的内核模块位于 /lib/modules/$(uname -r)/kernel 目录中

```
ls /lib/modules/5.19.0-45-generic/kernel/
```

​	在这里，查看发行版内核（运行 5.19.0-45-generic 内核的 Ubuntu 22.04 LTS）的 kernel/ 目录的顶层，我们发现其中有许多子文件夹，并且实际上打包了数千个内核模块。我们自己构建的版本当然实际上是选取了小而快的构建。所以少一些！

### modinfo

​	modinfo 实用程序允许我们查看内核模块的二进制映像并提取有关它的一些详细信息您可能会发现内核模块文件已压缩（例如，e1000.ko.xz）；这是一个功能，而不是错误（稍后会详细介绍）。获取有关系统的有用信息（包括有关当前已加载的内核模块的信息）的另一种方法是通过 systool 实用程序。对于已安装的内核模块（有关安装内核模块的详细信息，请参阅下一章中的“系统启动时自动加载模块”部分），执行 `systool -m <module-name> -v `将显示有关它的信息。查找 systool(1) 手册页以了解使用详情。

​	最重要的是，内核模块已成为构建和分发某些类型的内核组件的实用方法，其中设备驱动程序可能是它们最常见的用例。其他用途包括但不限于文件系统、网络防火墙、数据包嗅探器和自定义内核代码。

## 动手！写年轻人的第一个内核模块程序

### 先试试看！

​	下面我们就开始动手写内核了！先不要着急问步骤，您可以先看看下面的代码

```
#include<linux/init.h>
#include<linux/module.h>

MODULE_AUTHOR("Charliechen");
MODULE_DESCRIPTION("This is a module print hello world for u!");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

/* modified for print times */
static const short PRT_TIMES = 10;

static void print_me(void)
{
    for(short i = 0; i < PRT_TIMES; i++)
        pr_info("Hello, world!");
}


static int __init hello_init(void)
{
    pr_info("The module is about hanging on the kernel:)\n");
    print_me();
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Then the kernel is about to leave!");
}


module_init(hello_init);
module_exit(hello_exit);
```

​	我先不写注释，以保留您的一点好奇心（不是。

​	当然，你也可以复制代码到hello_lkm.c中体验一番。

> 下一步就是写一个Makefile！

​	当然，你可能会发颤，欸！我写内核Makefile，真的假的？你放心，你做的工作实际上是调用内核写的markfile来完成这项工作！

```
# A makefile sheet for compiling the kernel

PWD 	:= $(shell pwd)
KDIR 	:= /lib/modules/$(shell uname -r)/build/
obj-m 	+= hello_lkm.o

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
```

​	之后就是Make，笔者make一下：

```
[Charliechen@ArchLinux chap4]$ cd try1/
[Charliechen@ArchLinux try1]$ make
make -C /lib/modules/6.11.7-arch1-1/build/ M=/home/Charliechen/Works/module_programming/chap4/try1 modules
make[1]: Entering directory '/usr/lib/modules/6.11.7-arch1-1/build'
  CC [M]  /home/Charliechen/Works/module_programming/chap4/try1/hello_lkm.o
  MODPOST /home/Charliechen/Works/module_programming/chap4/try1/Module.symvers
  CC [M]  /home/Charliechen/Works/module_programming/chap4/try1/hello_lkm.mod.o
  LD [M]  /home/Charliechen/Works/module_programming/chap4/try1/hello_lkm.ko
  BTF [M] /home/Charliechen/Works/module_programming/chap4/try1/hello_lkm.ko
make[1]: Leaving directory '/usr/lib/modules/6.11.7-arch1-1/build'
```

​	事情就是这样的简单，当然，路径问题对着查就行。

​	下一步就是挂起我们的module试试看：

```
sudo insmod hello_lkm.ko
```

​	你可以看到，我们的模块挂起来了，啥反应没有！在哪里看现象呢？答案是dmesg！

```
sudo dmesg | tail -13
```

```
[ 5187.941248] The module is about hanging on the kernel:)
[ 5187.941253] Hello, world!
[ 5187.941254] Hello, world!
[ 5187.941254] Hello, world!
[ 5187.941255] Hello, world!
[ 5187.941256] Hello, world!
[ 5187.941256] Hello, world!
[ 5187.941257] Hello, world!
[ 5187.941257] Hello, world!
[ 5187.941258] Hello, world!
```

​	我们可以看看我们挂起的内核模块的信息：

```
sudo modinfo hello_lkm.ko
```

```
filename:       /home/Charliechen/Works/module_programming/chap4/try1/hello_lkm.ko
version:        0.1
license:        Dual MIT/GPL
description:    This is a module print hello world for u!
author:         Charliechen
srcversion:     E85791CF389F9691386FD90
depends:        
retpoline:      Y
name:           hello_lkm
vermagic:       6.11.7-arch1-1 SMP preempt mod_unload 
```

​	以及卸载我们的module

```
sudo rmmod hello_lkm.ko
```

​	笔者的电脑上不会打印信息，直到下一次我们挂起模块的时候才会打印退出的信息，你试试看！

### 开始我们的详解旅程

#### Kernel Headers

​	无论您是何种发行版，基本上可以确定的是，您的模块开发头文件基本上都在`/lib/modules/$(shell uname -r)`下，以笔者为例子：

```
[Charliechen@ArchLinux try1]$ cd /lib/modules/$(uname -r)/
[Charliechen@ArchLinux 6.11.7-arch1-1]$ ls -l
total 20264
drwxr-xr-x 1 root root      442 Nov 13 15:27 build
drwxr-xr-x 1 root root       92 Nov 13 15:27 kernel
-rw-r--r-- 1 root root  1640809 Nov 13 15:27 modules.alias
-rw-r--r-- 1 root root  1601568 Nov 13 15:27 modules.alias.bin
-rw-r--r-- 1 root root     6853 Nov  9 01:57 modules.builtin
-rw-r--r-- 1 root root     7995 Nov 13 15:27 modules.builtin.alias.bin
-rw-r--r-- 1 root root     9013 Nov 13 15:27 modules.builtin.bin
-rw-r--r-- 1 root root    70149 Nov  9 01:57 modules.builtin.modinfo
-rw-r--r-- 1 root root   857294 Nov 13 15:27 modules.dep
-rw-r--r-- 1 root root  1124303 Nov 13 15:27 modules.dep.bin
-rw-r--r-- 1 root root      437 Nov 13 15:27 modules.devname
-rw-r--r-- 1 root root   251482 Nov  9 01:57 modules.order
-rw-r--r-- 1 root root     2870 Nov 13 15:27 modules.softdep
-rw-r--r-- 1 root root   749296 Nov 13 15:27 modules.symbols
-rw-r--r-- 1 root root   909081 Nov 13 15:27 modules.symbols.bin
-rw-r--r-- 1 root root       55 Nov 13 15:27 modules.weakdep
-rw-r--r-- 1 root root        6 Nov  9 01:57 pkgbase
drwxr-xr-x 1 root root        8 Nov 13 15:27 updates
-rw-r--r-- 1 root root 13480448 Nov  9 01:57 vmlinuz
```

​	以及我们的build底下就是我们的开发文件：

```
[Charliechen@ArchLinux 6.11.7-arch1-1]$ ls build/
arch     Kconfig                  net         version
block    kernel                   samples     virt
certs    lib                      scripts     vmlinux
crypto   localversion.10-pkgrel   security    vmlinux-gdb.py
drivers  localversion.20-pkgname  sound       vmlinux.h
fs       Makefile                 System.map
include  mm                       tools
init     Module.symvers           usr
```

​	现在我们应该猜到：

```
#include<linux/init.h>
#include<linux/module.h>
```

​	实际上引用的就是这两个文件了！

#### 小插曲：在VSCode上配置你的开发环境

​	哦对了，这里简单介绍一下如何在VSCode上配置开发环境！一般而言，如果您可以在shell编译您的module，但是在VSCode中则缺失相关信息，办法是在.vscode下写一个c_cpp_properties.json文件，这里笔者给出我的配置：

```
{
    "configurations": [
        {
            "name": "kernel_dev",
            "includePath": [
                "${workspaceFolder}/**",
                "/lib/modules/6.11.7-arch1-1/build/include",
                "/lib/modules/6.11.7-arch1-1/build/arch/x86/include",
                "/lib/modules/6.11.7-arch1-1/build/arch/x86/include/generated",
                "/lib/modules/6.11.7-arch1-1/build/include",
                "/lib/modules/6.11.7-arch1-1/build/arch/x86/include/uapi",
                "/lib/modules/6.11.7-arch1-1/build/arch/x86/include/generated/uapi",
                "/lib/modules/6.11.7-arch1-1/build/include/uapi",
                "/lib/modules/6.11.7-arch1-1/build/include/generated/uapi"
            ],
            "defines": [                
                "__GNUC__",
                "__KERNEL__",
                "MODULE"
            ],
            "intelliSenseMode": "clang-x64"
        }
    ],
    "version": 4
}
```

​	includePath中添加您现在使用的内核的版本的头文件，注意到默认的define需要添加defines的

```
"__GNUC__",
"__KERNEL__",
"MODULE"
```

​	这几个宏将会使能我们内核开发的功能，所以，just do it!

#### 一些模块开发的宏介绍

​	在Linux内核模块（LKM，Loadable Kernel Module）中，`MODULE_*` 宏用于定义与模块相关的元数据。每个宏都有特定的用途：

**`MODULE_AUTHOR()`**： 这个宏用于指定内核模块的作者或作者列表。它接受一个字符串参数，该字符串通常是作者的姓名、电子邮件地址或者其他识别信息。这个宏是为了提供作者信息，便于其他开发者或用户在需要时联系作者。

**`MODULE_DESCRIPTION()`**： 该宏用来简短地描述内核模块的功能或用途。描述通常是简洁且明确的，旨在向用户或其他开发者解释模块的基本作用。这个描述会显示在使用 `lsmod` 或 `modinfo` 命令时。
示例：

```
MODULE_DESCRIPTION("This module provides a simple device driver for example hardware.");
```

这段描述说明该模块是一个简单的设备驱动程序，适用于某个示例硬件。

**`MODULE_LICENSE()`**： 该宏指定了内核模块的许可证类型，告诉系统该模块的使用和分发条款。不同的许可证可能会影响模块的合法性，尤其是在与内核的兼容性方面。常见的许可证包括GPL（GNU General Public License）、MIT、BSD等。

- `MODULE_LICENSE("GPL")` 适用于遵循 GPL 许可证的模块。
- `MODULE_LICENSE("Proprietary")` 用于专有软件许可证的模块。
- 如果没有指定许可证，Linux内核会认为模块不符合GPL，因此会发出警告。
  示例：

```
MODULE_LICENSE("GPL");
```

这意味着该模块遵循GPL许可证。

**`MODULE_VERSION()`**： 该宏用于指定模块的版本信息。它接受一个字符串参数，通常用于记录模块的版本号。这对于模块的维护、调试、版本控制等非常有用。
示例：

```
MODULE_VERSION("1.0.0");
```

这指定了该内核模块的版本号为1.0.0。

​	好吧，来一个省流的版本：

- `MODULE_AUTHOR()` 记录了作者信息。
- `MODULE_DESCRIPTION()` 说明了模块的功能。
- `MODULE_LICENSE()` 明确了该模块遵循GPL许可证。
- `MODULE_VERSION()` 指定了该模块的版本号。

#### entry和exit点（欸！这不是我们构造和析构吗，下此记得标明出处）

​	内核模块不像普通的应用程序，它们是运行在内核空间的代码，拥有内核权限。因此，内核模块没有像应用程序那样的入口点（如 `main()` 函数）。这就引出了一个问题：内核模块的入口点和退出点在哪里？

​	内核模块的入口和退出点由两个宏 `module_init()` 和 `module_exit()` 指定。在模块加载时，`module_init()` 宏会调用传入的函数，这个函数就是模块的入口点；而在模块卸载时，`module_exit()` 宏会调用另一个函数，这个函数则是模块的退出点。在现代的 C 编译器中，我们可以直接指定函数名作为参数，简化了代码的编写。举例来说，`helloworld_lkm_init()` 是模块的初始化函数，即模块加载时执行的入口函数，而 `helloworld_lkm_exit()` 则是模块的退出函数，也就是在模块卸载时执行的清理操作。

​	虽然从概念上看，这些入口和退出函数类似于构造函数和析构函数的配对（例如在 C++ 中的类构造与析构），但实际上它们并不是在面向对象编程框架下的构造和析构函数。它们更像是内核模块的生命周期管理函数，负责在模块加载时进行必要的初始化工作，在模块卸载时清理资源。

​	通过这两个宏，内核模块的加载和卸载变得更加清晰和有序，确保了在内核模块的生命周期内，正确的操作得以执行，避免资源泄漏或错误的操作。这种设计帮助开发者简化了内核模块的生命周期管理，同时也使得模块与内核系统之间的交互更加规范化。

​	你已经注意到这个规范了：

```
static int  __init <modulename>_init(void); 
static void __exit <modulename>_exit(void);
```

​	作为良好的编码习惯，我们使用函数的命名格式为 `<modulename>_{init|exit}()`，其中 `<modulename>` 被替换为内核模块的名称。

​	好吧，其实这并不是强迫的，但是这样的书写非常有助于我们开发人员深入理解哪里是模块的入口点哪里是出口点！

​	这里用静态限定符标记这两个函数意味着它们是这个内核模块的私有函数。这就是我们想要的。

#### 0/-E 返回约定

​	内核模块的 init 函数返回一个整数，即 int 类型的值；这是一个关键方面。 Linux 内核已经发展出一种风格或惯例，如果你愿意的话，关于从它返回值（意味着从模块驻留和运行的内核空间到用户空间进程）。为了返回一个值，LKM 框架遵循俗称的 0/-E 惯例：

- 成功时，返回整数值 0。
- 失败时，返回您希望将用户空间全局未初始化整数 errno 设置为的值的负数。

​	请注意，errno 是一个全局整数，位于用户进程 VAS 的未初始化数据段内。除了极少数例外，每当 Linux 系统调用失败时，都会返回 -1，并将 errno 设置为正值，表示失败代码或诊断；这项工作由 glibc 在系统调用返回路径上的“粘合”代码执行。此外，errno 值是英文错误消息全局表（const char * sys_errlist[]）的索引；这就是 perror(3)、strerror[_r](3) 等例程打印出故障诊断的方式。顺便说一句，您可以从这些（内核源代码树）头文件中查找可用的错误（errno）代码的完整列表：include/uapi/asm-generic/errno-base.h 和 include/uapi/asm-generic/errno.h。

​	一个关于如何从内核模块的 init 函数返回的简单示例将有助于明确这一关键点：假设我们的内核模块的 init 函数正在尝试动态分配一些内核内存（当然，后面的章节将介绍 kmalloc() API 等的详细信息；请暂时忽略它）。然后，我们可以像这样编码：

```
[...]
ptr = kmalloc(87, GFP_KERNEL);
if (!ptr) {
pr_warning("%s():%s():%d: kmalloc failed! Out of memory\n", _
return -ENOMEM;
}
[...]
return 0; /* success */
```

​	如果内存分配确实失败（实不相瞒，笔者除了自己作死写大申请以外，极少遇到内存不足的case），我们会执行以下操作：
1. 首先，我们发出警告含义的 printk。在这种特殊情况下——“内存不足”——发出消息被认为是迂腐且不必要的。如果内核空间内存分配失败，内核肯定会发出足够的诊断信息！
2. 返回整数值 -ENOMEM：
  在用户空间中，此值将返回到的层实际上是 glibc；它有一些“粘合”代码，将此值乘以 -1，并将全局整数 errno 设置为它。
  现在，[f]init_module() 系统调用将返回 -1，表示失败（这是因为 insmod 实际上调用了 finit_module()（或者更早的 init_module()）系统调用，您很快就会看到）。errno 将设置为 ENOMEM，反映出由于分配内存失败而导致内核模块插入失败的事实。相反，框架期望 init 函数在成功时返回值 0。事实上，在较旧的内核版本中，如果成功后未能返回 0，则会导致内核模块突然立即从内核内存中卸载。**如今，这种内核模块的删除不会发生；相反，内核会发出一条警告消息，说明已返回可疑的非零值。此外，现代编译器通常会在以下情况下捕捉到您没有返回值的事实**，随后会触发类似这样的错误消息：

  ```
  错误：函数中没有返回语句，返回非 void [-Werror=return-type]。 
  ```

  ​	清理例程没什么好说的。它不接收任何参数，也不返回任何内容（void）。**它的工作是在内核模块从内核内存中卸载之前执行任何和所有必需的清理（释放内存对象、设置某些寄存器等等，具体取决于模块的设计用途）。** 如果内核模块中不包含 module_exit() 宏，则无法卸载它（当然，即使系统关闭或重新启动）。 

  #### ERR_PTR 和 PTR_ERR 宏 

  在讨论返回值时，您现在明白内核 模块的 init 例程必须返回一个整数。如果您希望返回一个 指针，该怎么办？ERR_PTR() 内联函数可以帮到我们， 它允许我们通过将其类型转换为 void * 来返回伪装成指针的整数。 情况会变得更好：您可以使用 IS_ERR() 内联函数检查错误 （它实际上只是确定值是否在 [-1 到 -4095] 范围内）， 通过 ERR_PTR() 内联将负错误值编码为指针函数，并使用逆例程 PTR_ERR() 从指针中检索该值。

  ​	作为一个简单的例子，请参见此处给出的被调用者代码。这次，作为示例，我们让（示例）函数 myfunc() 返回一个指针（指向名为 mystruct 的结构）而不是一个整数：

  ```
  struct mystruct * myfunc(void)
  {
  	struct mystruct *mys = NULL;
  	mys = kzalloc(sizeof(struct mystruct), GFP_KERNEL);
  	if (!mys)
  		return ERR_PTR(-ENOMEM);
  	[...]
  	return mys;
  }
  ```

  调用者代码如下：

  ```
  [...]
  retp = myfunc();
  if (IS_ERR(retp)) {
  	pr_warn("myfunc() mystruct alloc failed, aborting...\n");
  	stat = PTR_ERR(retp); /* 将“stat”设置为值 -ENOME
  	goto out_fail_1;
  }
  [...]
  out_fail_1:
  return stat;
  }
  ```

  ​	当然 ERR_PTR()、PTR_ERR() 和 IS_ERR() 函数都位于（内核头）include/linux/err.h 文件中。感兴趣的空语看看。

#### \_\_init 和 __exit 关键字

回想一下我们简单模块的 init 和清理函数：

```
static int __init helloworld_lkm_init(void)
{
[ … ]
static void __exit helloworld_lkm_exit(void)
{
[ … ]
```

​	我们在前面的函数签名中看到的 __init 和 __exit 宏到底是什么？它们只是指定了内存优化链接器属性。\_\_init 宏为代码定义了一个 init.text 部分。同样，任何使用 \_\_initdata 属性声明的数据都会进入 init.data 部分。
​	这里的重点是 init 函数中的代码和数据在初始化期间只使用一次。一旦调用它，它就不会再被调用；因此，一旦调用，这些 init 部分中的所有代码和数据都会被释放（通过 free_initmem()）。
​	__exit 宏的处理方式类似，不过当然，这只对内核模块有意义。一旦调用清理函数，所有内存都会被释放。如果代码是静态内核映像的一部分（或者如果禁用了模块支持），则此宏将不起作用。很好，但到目前为止，我们还没有解释一些实际问题：您究竟如何构建新的内核模块，将其放入内核内存并执行，然后卸载它

## 扩展

### MODULE_*的源文件

```
/*
 * The following license idents are currently accepted as indicating free
 * software modules
 *
 *	"GPL"				[GNU Public License v2]
 *	"GPL v2"			[GNU Public License v2]
 *	"GPL and additional rights"	[GNU Public License v2 rights and more]
 *	"Dual BSD/GPL"			[GNU Public License v2
 *					 or BSD license choice]
 *	"Dual MIT/GPL"			[GNU Public License v2
 *					 or MIT license choice]
 *	"Dual MPL/GPL"			[GNU Public License v2
 *					 or Mozilla license choice]
 *
 * The following other idents are available
 *
 *	"Proprietary"			[Non free products]
 *
 * Both "GPL v2" and "GPL" (the latter also in dual licensed strings) are
 * merely stating that the module is licensed under the GPL v2, but are not
 * telling whether "GPL v2 only" or "GPL v2 or later". The reason why there
 * are two variants is a historic and failed attempt to convey more
 * information in the MODULE_LICENSE string. For module loading the
 * "only/or later" distinction is completely irrelevant and does neither
 * replace the proper license identifiers in the corresponding source file
 * nor amends them in any way. The sole purpose is to make the
 * 'Proprietary' flagging work and to refuse to bind symbols which are
 * exported with EXPORT_SYMBOL_GPL when a non free module is loaded.
 *
 * In the same way "BSD" is not a clear license information. It merely
 * states, that the module is licensed under one of the compatible BSD
 * license variants. The detailed and correct license information is again
 * to be found in the corresponding source files.
 *
 * There are dual licensed components, but when running with Linux it is the
 * GPL that is relevant so this is a non issue. Similarly LGPL linked with GPL
 * is a GPL combined work.
 *
 * This exists for several reasons
 * 1.	So modinfo can show license info for users wanting to vet their setup
 *	is free
 * 2.	So the community can ignore bug reports including proprietary modules
 * 3.	So vendors can do likewise based on their own policies
 */
#define MODULE_LICENSE(_license) MODULE_FILE MODULE_INFO(license, _license)

/*
 * Author(s), use "Name <email>" or just "Name", for multiple
 * authors use multiple MODULE_AUTHOR() statements/lines.
 */
#define MODULE_AUTHOR(_author) MODULE_INFO(author, _author)

/* What your module does. */
#define MODULE_DESCRIPTION(_description) MODULE_INFO(description, _description)

#ifdef MODULE
/* Creates an alias so file2alias.c can find device table. */
#define MODULE_DEVICE_TABLE(type, name)					\
extern typeof(name) __mod_##type##__##name##_device_table		\
  __attribute__ ((unused, alias(__stringify(name))))
#else  /* !MODULE */
#define MODULE_DEVICE_TABLE(type, name)
#endif

/* Version of form [<epoch>:]<version>[-<extra-version>].
 * Or for CVS/RCS ID version, everything but the number is stripped.
 * <epoch>: A (small) unsigned integer which allows you to start versions
 * anew. If not mentioned, it's zero.  eg. "2:1.0" is after
 * "1:2.0".

 * <version>: The <version> may contain only alphanumerics and the
 * character `.'.  Ordered by numeric sort for numeric parts,
 * ascii sort for ascii parts (as per RPM or DEB algorithm).

 * <extraversion>: Like <version>, but inserted for local
 * customizations, eg "rh3" or "rusty1".

 * Using this automatically adds a checksum of the .c files and the
 * local headers in "srcversion".
 */

#if defined(MODULE) || !defined(CONFIG_SYSFS)
#define MODULE_VERSION(_version) MODULE_INFO(version, _version)
#else
#define MODULE_VERSION(_version)					\
	MODULE_INFO(version, _version);					\
	static struct module_version_attribute __modver_attr		\
		__used __section("__modver")				\
		__aligned(__alignof__(struct module_version_attribute)) \
		= {							\
			.mattr	= {					\
				.attr	= {				\
					.name	= "version",		\
					.mode	= S_IRUGO,		\
				},					\
				.show	= __modver_version_show,	\
			},						\
			.module_name	= KBUILD_MODNAME,		\
			.version	= _version,			\
		}
#endif
```

