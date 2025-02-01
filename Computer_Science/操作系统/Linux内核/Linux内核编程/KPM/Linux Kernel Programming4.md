# Linux Kernel Programming

## 限制 printk 实例的速率

​	当我们从执行频率非常高的代码路径发出 printk 实例时，大量的 printk 实例可能会很快溢出内核日志缓冲区（在 RAM 中，请记住它是一个循环缓冲区！），从而覆盖可能是关键的信息。除此之外，不断增长的非易失性日志文件重复几乎相同的内核日志消息（几乎）无限期也不是一个好主意，而且会浪费磁盘空间，或者更糟的是，浪费闪存空间。例如，想象一下中断处理程序代码路径中的大型 printk。如果以 100 Hz 的频率调用硬件中断（即每秒 100 次）会怎么样？为了缓解这些问题，内核提供了一个有趣且有用的替代方案：速率受限的 printk。 pr\_\<foo>_ratelimited() 宏（其中 \<foo> 是 emerg、alert、crit、err、warn、notice、info 或 debug 之一）
​	具有与常规 printk 相同的语法；关键点在于，当满足某些条件时，它会有效地抑制常规打印。
为此，内核通过 proc 文件系统提供了两个名为 printk_ratelimit 和 printk_ratelimit_burst 的 sysctl 文件。在这里，我们直接复制了 sysctl 文档（来自
https://www.kernel.org/doc/Documentation/sysctl/kernel.txt），该文档解释了这两个（伪）文件的确切含义：

> printk_ratelimit:某些警告消息有速率限制。printk_ratelimit 指定这些消息之间的最短时间间隔（以 jiffies 为单位），默认情况下，我们允许每 5 秒发送一条消息。值为 0 将禁用速率限制。
>
> printk_ratelimit_burst:虽然我们长期强制每 printk_ratelimit 秒发送一条消息，但我们确实允许大量消息通过。
> printk_ratelimit_burst 指定在速率限制生效之前我们可以发送的消息数量。

​	笔者的Arch Linux主机上，其值是

```
cat /proc/sys/kernel/printk_ratelimit /proc/sys/kernel/printk_ratelimit_burst
5
10
```

​	这意味着默认情况下，在速率限制启动之前，5 秒时间间隔内最多有 10 个相同消息的实例可以通过。printk 速率限制器在抑制内核 printk 实例时，会发出一条有用的消息，确切说明有多少早期的 printk 回调被抑制。一些示例输出有助于说明这一点：

内核提供了以下宏来帮助您限制打印/日志的速率（您应该使用 #include <linux/kernel.h>）：

- printk_ratelimited()：警告！不要使用它 - 内核会对此发出警告。
- pr\_*\_ratelimited()：其中通配符 * 被替换为通常的 - emerg、alert、crit、err、warn、notice、info 或 debug 之一。
- dev\_*\_ratelimited()：其中通配符 * 被替换为通常的 - emerg、alert、crit、err、warn、notice、info 或 debug 之一。
  确保您优先使用 pr_*_ratelimited() 宏而不是 printk_ratelimited()；驱动程序作者应该使用 dev_*_ratelimited()
  宏。

​	在 AMD GPU 驱动程序中可以看到一个使用速率受限（驱动程序调试）printk 的代码级示例（内核树中的多个示例之一），

使用 dev_\*\_*() 宏时，请注意第一个参数始终是指向设备的指针。

- 不要使用较旧的（现已弃用）printk_ratelimited() 和 printk_ratelimit() 宏。

- 另外，仅供参考，实际的速率限制代码位于 lib/ratelimit.c:\_\__ratelimit() 中。以下是内核约定：以两个或更多下划线开头的函数/宏（__foo()）被视为内部函数/宏。避免直接使用它；使用它的包装器 foo()。

## 从用户空间生成内核消息

​	我们程序员使用的一种流行的调试技术是在代码的各个点上散布打印，这通常允许我们缩小问题的来源。这确实是一种有用的调试技术，更正式地称为检测代码。内核开发人员经常使用古老的 printk API（和朋友）来实现此目的。因此，假设您已经编写了一个内核模块并正在调试它（通过在代码中的适当位置添加几个 printk 实例）。您的内核代码现在发出这几个 printk 实例，当然，您可以在运行时通过 dmesg（或 journalctl 等）看到它们。

​	这很好，但是，特别是因为您正在运行一些自动化的用户空间测试脚本，您希望通过打印出某条消息来查看脚本在我们的内核模块中启动某些操作的时间点的时候，我们要怎么做？

​	我们可以让用户空间测试脚本将一条消息写入内核日志缓冲区，就像内核 printk 一样，通过将所述消息写入特殊的 /dev/kmsg 设备文件：

```
echo "test_script: @user msg 1" > /dev/kmsg
```

​	但是，请注意，在 echo 之前使用简单的 sudo 根本不起作用：

```
$ sudo echo "test_script: @user msg 1" > /dev/kmsg
bash: /dev/kmsg: Permission denied
$ sudo bash -c "echo \"test_script: @user msg 1\" > /dev/kmsg"
[sudo] password for c2kp:
$ dmesg |tail -n1
[55527.523756] test_script: @user msg 1
```

​	第二次尝试中使用的语法有效，但获取 root shell（sudo -s）并执行此类任务更简单。

​	还有一件事。dmesg 实用程序有几个选项，旨在使输出更易于阅读；我们在这里通过 dmesg 的示例别名展示其中一些，然后使用它：

```
$ alias dmesg='sudo dmesg --decode --nopager --color --ctime'
$ dmesg | tail -n1
```

通过特殊 /dev/kmsg 设备文件写入内核日志的消息将以当前默认日志级别打印，通常为 4：KERN_WARNING。我们可以通过在消息前面加上所需的日志级别（作为字符串格式的数字）来覆盖它。例如，要从用户空间写入日志级别 6 的内核日志：KERN_INFO，请使用以下命令：

```
$ sudo bash -c "echo \"<6>Charlie says the info is from info level"
> /dev/kmsg"
$ dmesg | tail -n1
user  :info  : [Mon Dec 30 09:21:55 2024] pocky says the info is from info level:)

```

​	我们可以看到，我们的后一条消息是在日志级别 6 发出的，如 echo 中指定的那样。实际上没有办法区分用户生成的内核消息和内核 printk() 生成的消息；它们看起来完全相同。因此，当然，它可以像在消息中插入或添加一些特殊的签名字节或字符串（例如 @user ...）一样简单，以帮助您区分这些用户生成的打印和内核打印。顺便说一下，下面有几点需要注意。

​	用户空间和内核空间之间的接口是一个关键且重要的主题，通常是驱动程序作者需要做的事情。有很多方法可以做到这一点，但总是在某种程度上涉及从用户空间发出系统调用作为切换到内核的手段。在 Linux 上，可用于在用户空间和内核空间之间进行接口的技术包括通过 procfs、sysfs、debugfs、netlink 套接字和 ioctl() 系统调用来实现。

通过 pr_fmt 宏标准化 printk 输出

​	关于内核 printk 的另一个要点：通常，为了给您的 printk() 输出提供上下文（它究竟发生在哪里？），您可以像这样编写代码，利用各种 GCC 宏，如`__FILE__、__func__` 和 `__LINE__`，它们当然会分别发出文件名、函数名和行号，从哪里发出打印：

```
pr_info("%s:%s:%s():%d: mywork XY failed!\n", OURMODNAME, __FILE__, __func__, __LINE__);
```

​	这样就很好了；问题是，如果项目中有很多 printk 实例，那么保证项目中的所有成员始终一致且正确地遵循标准 printk 格式（例如，首先显示模块名称，然后显示文件名，然后显示函数名称，可能还有行号，如这里所示）可能会很麻烦。
输入 pr_fmt() 宏；在代码开头定义此宏（必须在第一个 #include 之前），可确保代码中每个后续 printk 都以此宏指定的格式作为前缀。

```
#define pr_fmt(fmt) "%s:%s(): " fmt, KBUILD_MODNAME, __func__
```

​	pr_fmt() 宏被突出显示；它使用预定义的 KBUILD_MODNAME宏来替换内核模块的名称，并使用 GCC __func__
说明符来显示我们当前正在运行的函数的名称！您可以为 `__FILE__` 添加 %s，并添加与相应 `__LINE__`宏匹配的 %d 来显示行号；这完全取决于您。因此，最重要的是，我们在此 LKM 的 init 函数中发出的 pr_info() 将在内核日志中显示如下：

​	请注意，模块名称和函数名称如何自动添加到 printk 消息内容的前缀！这非常有用，而且确实非常常见；在内核中，实际上有数百个源文件以pr_fmt() 开头。在 6.1.25 内核代码库上快速搜索后，发现代码库中有超过 2,200 个此宏的实例！我们也将遵循此约定，尽管并非在我们所有的演示内核模块中都如此。pr_fmt() 还通过 dev_*() 宏对驱动程序作者推荐的 printk 用法产生影响。接下来，让我们深入研究参考 printk 编写可移植代码的问题。

## 可移植性和 printk 格式说明符

​	关于多功能 printk 内核 API，有一个问题值得思考：如何确保您的 printk 输出看起来正确（格式正确）并且无论位宽如何都能在任何 CPU 上同样出色地工作？可移植性问题在这里浮出水面；好消息是，熟悉提供的各种格式说明符将在这方面对您大有帮助，实际上允许您编写独立于架构的 printk 实例。

重要的是要意识到 size_t（发音为 sizetype）是无符号整数的 typedef；类似地，ssize_t（有符号大小类型）是有符号整数的 typedef。以下是编写可移植代码时要记住的一些最常用的 printk 格式说明符：

对于 size_t 和 ssize_t（无符号和有符号）整数，分别使用 %zu 和%zd。
对于内核指针，使用 %pK 表示安全性（散列值），使用 %px 表示实际指针（不要在生产中使用！）。此外，使用 %pa 表示物理地址（必须通过引用传递）。kptr_restrictsysctl 在这方面可以发挥作用；

​	对于十六进制字符串形式的原始缓冲区，请使用 %*ph（其中 * 被替换为字符数）。对于 64 个字符以内的缓冲区，请使用它，对于更多情况，请使用 print_hex_dump_bytes() 例程；有可用的变体（请参阅内核文档 - 链接如下）。对于 IPv4 地址，请使用 %pI4，对于 IPv6 地址，请使用 %pI6（此处也有变体）。官方内核文档中包含一份详尽的 printk 格式说明符列表以及何时使用每个说明（附有示例！）：https://www.kernel.org/doc/Documentation/printk-formats.txt。内核还明确记录了在 printk() 语句中使用未修饰的 %p 可能导致安全问题（https://www.kernel.org/doc/html/latest/process/deprecated.html#p-format-specifier）。

## printk 索引

解新的 printk 索引功能，您编写了一个内核模块（也许是一个驱动程序），作为作业的一部分，它会发出一些 printk 实例（当然，作为一个好人，您知道要尽可能减少打印次数）。所以，假设您的一条日志消息是 mydriver：检测到疯狂情况 X；好的，没问题。您的项目已部署在生产中；假设某种用户空间监视守护进程（也）正在监视内核日志消息以查找异常情况，以便它可以提醒人类用户。这让我们意识到 printk 实例不仅供人类使用；程序也可能持续监视它们，这在大型安装中经常发生。现在，几个月后，项目中的另一位开发人员觉得您的内核日志消息不太好，并将其更改为 mydriver：检测到异常条件 X。问题是，日志监控守护进程仍在寻找您的旧消息（可能通过 grepping mydriver：检测到疯狂情况字符串），现在将完全错过这个（新的）关键消息，从而导致各种问题。

​	为了解决这种情况（是的，它们确实会出现），Chris Down 提出了一个内核 printk 索引功能（已在 5.15 中合并到主线中）。启用此功能后，本质上会发生以下情况：每个 printk实例的元数据 - 实际格式字符串（实际的消息）、其发出的源位置、日志级别等 - 都保存到一个结构（struct pi_entry）中，并且所有这些结构都整理到内核 vmlinux 映像中的特殊部分（名为
.printk_index；单个内核模块也是如此！）。这些消息通过 debugfs 条目显示（这确实表明依赖于启用的 debugfs），
<debugfs_mount_point>/printk/index/<file>，其中 <file> 可以是vmlinux 以及所有内核模块。有问题的内核配置（布尔值）名为 CONFIG_PRINTK_INDEX；默认情况下它是关闭的（您可以通过此处的常用 make menuconfig UI 查看它：常规设置 | Printk 索引 debugfs 接口）。

## 理解内核模块 Makefile 的基础知识

​	如您所知，make 命令默认会在当前目录中查找名为Makefile 的文件；如果该文件存在，它将解析该文件并执行
其中指定的命令序列。以下是 printk_loglevel 内核模块项目的简单 Makefile

```
$ nl Makefile
# ch4/printk_loglvl/Makefile
PWD := $(shell pwd)
KDIR := /lib/modules/$(shell uname -r)/build/

obj-m += printk_loglvl.o

# 通过移除以下行之一启用 pr_debug() 和 pr_devel()
# 以下行之一
#（注意：EXTRA_CFLAGS 已弃用；使用 ccflags-y）
#ccflags-y += -DDEBUG
#CFLAGS_printk_loglvl.o := -DDEBUG
all: 
	make -C $(KDIR) M=$(PWD) modules
install:
	make -C $(KDIR) M=$(PWD) modules_install
clean:
	make -C $(KDIR) M=$(PWD) clean
```

毋庸置疑，Unix Makefile 语法要求这种基本格式：

```
target: [dependent-source-file(s)]
	rule(s)
```

​	规则实例始终以 [Tab] 字符为前缀，而不是空格。让我们收集有关此（模块）Makefile 工作原理的基本信息。首先，关键点是：内核的 Kbuild 系统（我们从第 2 章“从源代码构建 6.x Linux 内核 - 第 1 部分”开始就一直在提及和使用）主要使用两个软件变量字符串进行构建，链接在两个变量 obj-y 和 obj-m 中。

​	obj-y 字符串包含要构建并合并到最终内核映像文件的所有对象的连接列表 - 未压缩的 vmlinux 和压缩的（可启动）[b][z]Image 映像。想想看 - 这是有道理的：obj-y 中的 y 代表是。所有在内核配置过程中设置为 Y（或默认为 Y）的内核内置和 Kconfig 选项都通过此项链接在一起，由 Kbuild 构建系统构建并最终编织到最终内核映像文件中。另一方面，现在很容易看出 obj-m 字符串是所有要单独构建的内核对象的连接列表，作为内核模块！
这正是我们的 Makefile 有这行非常重要的行（第 4 行）的原因：

```
obj-m += printk_loglvl.o
```

​	实际上，它告诉 Kbuild 系统包含我们的代码；更准确地说，它告诉它隐式地将 printk_loglvl.c 源代码编译成 printk_loglvl.o 二进制对象，然后将此对象添加到 obj-m 列表中。
接下来，由于 make 的默认规则是 all 规则（第 10 行和第 11 行），因此它被处理：

```
all:
	make -C $(KDIR) M=$(PWD) modules
```

​	这个单个语句（第 11 行）的处理相当复杂；事情的经过如下：
1. make 的 -C 选项开关让 make 进程将目录（通过 chdir() 系统调用）更改为 -C 后面的目录名。因此，它将目录更改为 `$(KDIR)` 目录，该目录设置为（第 3 行）`/lib/modules/$(uname-r) `下的内核构建符号链接（如前所述，它指向通过 kernel-headers 包安装的有限内核源代码树的位置）。

```
$ ls -l /lib/modules/$(uname -r)/build
lrwxrwxrwx 1 root root 31 May 5 10:51 build -> /home/c2k
```

2. 因此，很明显，make 进程更改了目录到文件夹 ~/kernels/linux-6.1.25/，在本例中，它指向我们原来的 6.1.25 内核源代码树（因为我们运行的是之前构建的自定义内核）。到达那里后，它会自动解析内核顶层 Makefile 的内容 - 即驻留在该内核源代码树根目录中的 Makefile。这是关键点。内核顶层 Makefile 相当大且复杂（在 6.1.25 上，它超过 2,000 行），包含关键的构建细节和变量。这样，每次构建树外模块时都会进行解析，从而保证所有内核模块都与它们所针对的内核紧密耦合（稍后会详细介绍）。这还保证了内核模块的构建遵循与内核映像本身完全相同的规则集 - 即编译器/链接器配置（\*CFLAGS* 选项、编译器选项开关等）。这是二进制兼容性所必需的。

3. 接下来，在 Makefile 中，仍然在第 11 行，您可以看到名为 M 的变量的初始化（到当前工作目录），并且指定的目标为模块；因此，make 过程现在将目录更改为 M 变量指定的目录，即 \$(PWD) - 我们开始的那个文件夹（第 2 行：Makefile 中的 PWD := $(shell pwd) 将其初始化为正确的值）！因此，有趣的是，这是一个递归构建：构建过程在解析内核顶层 Makefile 后（非常重要），现在切换回内核模块的目录并在其中构建模块。

第 12 行和第 13 行构成安装目标（我们将在下一章中介绍），第 14 行和第 15 行构成清理目标。

您是否注意到，在构建内核模块时，也会生成大量中间工作文件？其中包括 

```
modules.order、<file>.mod.c、<file>.o、Module.symvers、<file>.mod.o、
.<file>.o.cmd、.<file>.ko.cmd、名为 .tmp_versions/ 的文件夹，当然还有内核模块二进制对象本身 <file>.ko 
```

​	此外，还会生成几个隐藏文件。清除所有这些临时构建工件（包括目标（内核模块对象本身））很容易：只需执行 make clean。clean 规则会将其全部清除。

​	您可以在内核文档中查找 modules.order 和 modules.builtin 文件（和其他文件）的用途：https://elixir.bootlin.com/linux/v6.1.25/source/Documentation/kbuild/kbuild.rst。

