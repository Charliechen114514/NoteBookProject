# Linux Kernel Programming 3

​	下面我们来聊一聊我们的printk，你可能没有印象！当然这是因为我使用的是pr_info，也就是printk的一个方便的封装。

​	要打印消息，用户空间 C 开发人员通常会使用可靠的 printf() glibc API（或者在编写 C++ 代码时使用 cout）。但是，重要的是要了解在内核空间中没有（用户模式或其他）库。因此，我们根本无法访问旧的 printf() API。相反，它基本上已在内核中重新实现为 printk() 内核 API。

​	想知道它的代码在哪里？好吧，它在这里定义为内核源代码树中的宏：

```
include/linux/printk.h
printk(fmt, …)
```

​	实际函数在这里：kernel/printk/printk.c:_printk()。事实上，内部 printk 实现非常复杂，涉及 printk 索引的包装层等等；

​	幸运的是，内核或内核模块通过 printk() API 发出消息非常简单，与使用 printf() 发出消息非常相似。在我们的简单内核模块中，操作发生的位置如下：printk(KERN_INFO "Hello, world\n");虽然乍一看与 printf 非常相似，但内核中的 printk API 却截然不同。在相似性方面，API 接收格式字符串作为其参数。格式字符串与 printf 的格式字符串几乎相同。但相似之处仅此而已。printf 和 printk 之间的一个关键区别是：用户空间 printf() 库 API 的工作原理是按要求格式化文本字符串并调用 write() 系统调用，而后者又实际上执行对 stdout 设备的写入，默认情况下，stdout 设备是终端窗口（或控制台设备）。内核 printk API 也按要求格式化其文本字符串，但其输出目的地不同。它至少会写入一个位置 - 以下列表中的第一个位置 - 并且可能还会写入其他几个位置：

- RAM 中的（易失性）内核日志缓冲区
- （非易失性）日志文件，即内核日志文件
- 控制台设备

​	接下来，不要过分依赖 printk() API；您很快就会了解到，使用它的现代和推荐方式是通过 pr_foo() 形式的宏（我们将在即将到来的 `pr_<foo>` 便利宏部分中介绍它们）。

​	当您通过 printk 发出消息时，可以保证输出进入内核内存（RAM）中的日志缓冲区。实际上，这构成了（易失性）内核日志。需要注意的是，在图形模式下运行 X 服务器（Xorg、Xwayland 或其他）进程（在典型的 Linux 发行版上工作的默认环境）时，您永远不会直接看到 printk 输出。

​	因此，这里显而易见的问题是：如何查看内核日志缓冲区内容？有几种方法。但是笔者建议的是dmesg，默认情况下，dmesg 会将整个内核日志缓冲区内容转储到 stdout。

​	在内核日志中，如 dmesg 实用程序所显示的那样，最左列方括号内的数字是一个简单的时间戳，格式为 [seconds.microseconds] - 自系统启动以来经过的时间（但不建议将其视为完全准确）。顺便说一句，这个时间戳是一个 Kconfig 变量 - 一个内核配置选项 - 名为 **CONFIG_PRINTK_TIME**；它可以被 printk.time 内核参数覆盖

​	下面我们来谈谈我们的几个模块的常用的几个实用工具！

### 列出活动内核模块 lsmod

​	回到我们的内核模块。到目前为止，我们已经构建了它，将它加载到内核中，并验证了它的入口点函数是否被调用，从而执行了 printk API。那么之后，它会做什么呢？啥也不做，就是打印点东西！我们可以使用 lsmod 实用程序轻松查找它：

```
[Charliechen@ArchLinux try1]$ sudo lsmod | grep hello
hello_lkm              12288  0
```

​	lsmod 显示当前驻留在（或活动）内核内存中的所有内核模块，按时间倒序排列。其输出为列格式，有三列和可选的第四列。让我们分别看一下每一列：

- 第一列显示内核模块的名称。
- 第二列是它在内核中占用的（静态）字节大小。
- 第三列是模块使用计数。
- 可选的第四列表示依赖模块，

​	此外，在最近的 x86_64 Ubuntu 发行版中，内核模块似乎占用了至少 16 KB 的内核内存，而在 Fedora 上则占用了大约 12 KB。
​	太棒了！现在您已经成功地在内核内存中构建、加载和运行了第一个内核模块，并且它基本上可以正常工作，下面说说看他的卸载部分

### 从内核内存卸载模块

​	要卸载内核模块，我们使用便捷实用程序 rmmod（删除模块）：

​	rmmod 的参数是内核模块的名称（如 lsmod 的第一列所示），而不是路径名。显然，就像 insmod 一样，我们需要以 root 用户身份运行 rmmod 实用程序才能成功（或使用 CAP_SYS_MODULE 功能）。

​	在这里，我们还可以看到，由于我们的 rmmod，LKM 框架首先调用正在删除的内核模块的退出例程（或“析构函数”）helloworld_lkm_exit() 函数。它依次调用 printk，发出 Goodbye, world... 消息（我们用 dmesg 查找）。

​	rmmod（请注意，在内部，它调用 delete_module() 系统调用）何时会失败？以下是一些情况：

- 权限：如果它不是以 root 身份运行，或者缺少 CAP_SYS_MODULE 功能（errno 设置为值 EPERM）。
- 如果内核模块的代码和/或数据正在被另一个模块使用（如果存在依赖关系；下一章的模块堆栈部分将详细介绍）或模块当前正在被进程（或线程）使用，则模块使用计数将为正，rmmod 将失败（errno 随后设置为值 EBUSY）；这是有道理的。
- 内核模块未使用 module_exit() 宏指定退出例程（或析构函数），并且 CONFIG_MODULE_FORCE_UNLOAD 内核配置选项被禁用。

​	与模块管理有关的几个便利实用程序只不过是指向单个 kmod 实用程序的符号（软）链接（类似于流行的 busybox 实用程序所做的）。包装器是 lsmod、rmmod、insmod、modinfo、modprobe 和 depmod。

## 聊一聊printk

​	内核日志缓冲区只是内核虚拟地址空间中的一个内存缓冲区，printk 的输出保存（记录）于此。更技术性地说，它是全局 __log_buf[] 变量。其在在我们的kernel/printk/printk.c文件处（491行左右）

```
/* record buffer */
#define LOG_ALIGN __alignof__(unsigned long)
#define __LOG_BUF_LEN (1 << CONFIG_LOG_BUF_SHIFT)
#define LOG_BUF_LEN_MAX (u32)(1 << 31)
static char __log_buf[__LOG_BUF_LEN] __aligned(LOG_ALIGN);
static char *log_buf = __log_buf;
static u32 log_buf_len = __LOG_BUF_LEN;
```

​	它被设计为环形缓冲区；它的大小是有限的（__LOG_BUF_LEN 字节），一旦它满了，它就会从零字节开始被覆盖。因此，它被称为“环形”（或循环）缓冲区。在这里，我们可以看到大小基于Kconfig 变量 CONFIG_LOG_BUF_SHIFT（C 中的 1 << n 意味着 2^n）显示出来，可以作为内核（菜单）配置的一部分进行覆盖：常规设置 | 内核日志缓冲区大小。它是一个整数值，范围为 12-25（我们始终可以搜索 init/Kconfig 并查看其规范），默认值为 18。因此，默认情况下，内核日志缓冲区的大小为（1 << 18），即 218 = 256 KB。但是，实际运行时大小也受其他配置指令的影响 - 特别是 LOG_CPU_MAX_BUF_SHIFT，它使大小成为系统上 CPU 数量的函数。

​	此外，相关的 Kconfig 文件说，“当使用 log_buf_len 内核参数时，此选项也会被忽略，因为它强制使用精确的（2 的幂）环形缓冲区大小。”所以，这很有趣；我们通常可以通过传递内核参数（通过引导加载程序）来覆盖默认值！

​	无论内核日志缓冲区的大小如何，处理 printk API 时都会出现两个问题：其消息被记录在易失性存储器 (RAM) 中；如果系统以任何方式崩溃或关闭电源，我们将丢失宝贵的内核日志（通常会严重限制甚至消除我们调试内核问题的能力）。

​	默认情况下，日志缓冲区不是很大，通常只有 256 KB（和/或系统上每个 CPU 可能为 4 到 8 KB）；因此，很明显，大量的打印将压垮环形缓冲区，使其回绕，从而丢失信息。这很不对，那我们的系统日志信息又是怎么一回事呢？

## 内核日志记录和 systemd 的 journalctl

​	正如用户空间应用程序使用日志一样，内核也使用日志；该功能称为内核日志记录，除了资源最受限的系统外，所有系统都需要该功能。解决前面提到的将内核日志记录到小型且易失性内存缓冲区的问题的一个明显方法是将每个内核 printk 写入（实际上是附加）二级存储（非易失性）文件中。这正是大多数现代 Linux 发行版的设置方式。内核日志文件的位置因发行版而异：传统上，基于 Red Hat 的内核日志文件写入 /var/log/messages 文件，而基于 Debian 的内核日志文件写入 /var/log/syslog。传统上，内核 printk 会挂接到用户空间系统日志记录器守护进程 (syslogd) 以执行文件日志记录，从而自动获得更复杂的功能，例如日志轮换、压缩和归档。然而，在过去几年中，系统日志记录已完全被名为 systemd 的实用且强大的新系统初始化框架所取代（它取代了旧的 SysV init 框架，或经常作为其补充）。事实上，systemd 现在甚至在嵌入式 Linux 设备上也经常使用。在 systemd 框架内，日志记录由名为 systemd-journal 的守护进程执行，journalctl 实用程序是它的用户界面。

​	使用日志检索和解释日志的一个主要优势是，所有日志（来自应用程序（进程和线程）、库、系统守护进程、内核、驱动程序等的日志）都在此处写入（合并）。

​	这样，我们就可以看到事件的（反向）时间轴，而无需手动将不同的日志拼凑成时间轴。 journalctl(1) 实用程序的手册页详细介绍了其各种选项。当然这里我们可以搞一些好玩的：

```
#--- a few journalctl(1) aliases 
# jlog: current (from most recent) boot only, everything 
alias jlog='journalctl -b --all --catalog –no-pager' 
# jlogr: current (from most recent) boot only, everything, 
#  in *reverse* chronological order 
alias jlogr='journalctl -b --all --catalog --no-pager --reverse'
# jlogall: *everything*, all time; --merge => _all_ logs merged 
alias jlogall='journalctl --all --catalog --merge --no-pager' 
# jlogf: *watch* the live log, akin to 'tail -f' mode; very usef
# use 'journalctl -f -k' to only watch for kernel printk's 
alias jlogf='journalctl -f' 
# jlogk: only kernel messages, this (from most recent) boot 
alias jlogk='journalctl -b -k --no-pager' 
```

​	我们特意使用了 --no-pager 选项，因为它允许我们根据需要使用标准 Linux 实用程序（如 grep、awk、sort 等）进一步过滤输出。试一下！

```
[Charliechen@ArchLinux ~]$ sudo journalctl -b -k --no-pager | tail -n2 
[sudo] password for Charliechen: 
Dec 29 18:27:58 ArchLinux kernel: perf: interrupt took too long (6426 > 6373), lowering kernel.perf_event_max_sample_rate to 30900
Dec 29 18:33:57 ArchLinux kernel: perf: interrupt took too long (8094 > 8032), lowering kernel.perf_event_max_sample_rate to 24600
```

​	下面这个就是我们journalctl的格式

```
[timestamp] [hostname] [source-of-msg]: [... log message ...] 
```

此处，[source-of-msg] 是内核消息的内核或编写消息的特定应用程序或服务的名称。

​	此外，journalctl 还可以轻松地以人性化的时间方式搜索日志 - 例如，查看过去半小时内写入的所有内核日志：journalctl -k --since="30 min ago"

​	当然，将内核消息非易失性地记录到文件中非常有用。但请注意，存在一些情况，通常由硬件限制决定，这可能导致无法实现。例如，一个微型、资源高度受限的嵌入式 Linux 设备可能使用小型内部闪存芯片作为其存储介质。现**在，它不仅很小，而且所有空间几乎都被应用程序、库、内核、驱动程序和引导加载程序占用，而且基于闪存的芯片在磨损前可以承受的擦除写入周期数有一个有效限制**。因此，写入几百万次可能会耗尽它！因此，

​	有时，系统设计人员会故意和/或额外使用更便宜的外部闪存，例如 (micro)SD/MMC (MultiMediaCard) 卡，用于存储非关键数据，以减轻这种影响，因为它们很容易（且便宜）更换。

## 使用 printk 日志级别

​	当您通过 printk API（及其它）向内核日志发出消息时，通常还必须指定记录该消息的日志级别。要了解和使用这些 printk 日志级别，让我们首先重现那一行代码 - 来自我们举世闻名的 helloworld_lkm 内核模块的第一个 printk：

```
printk(KERN_INFO "Hello, world\n");
```

​	我们来看看这个KERN_INFO是一个什么东西！

```
#define KERN_SOH	"\001"		/* ASCII Start Of Header */
#define KERN_SOH_ASCII	'\001'

#define KERN_EMERG	KERN_SOH "0"	/* system is unusable */
#define KERN_ALERT	KERN_SOH "1"	/* action must be taken immediately */
#define KERN_CRIT	KERN_SOH "2"	/* critical conditions */
#define KERN_ERR	KERN_SOH "3"	/* error conditions */
#define KERN_WARNING	KERN_SOH "4"	/* warning conditions */
#define KERN_NOTICE	KERN_SOH "5"	/* normal but significant condition */
#define KERN_INFO	KERN_SOH "6"	/* informational */
#define KERN_DEBUG	KERN_SOH "7"	/* debug-level messages */

#define KERN_DEFAULT	""		/* the default kernel loglevel */
```

​	但实际上他们不太常用，常用的是下面的封装的宏：

## `pr_<foo>` 便利宏

​	此处解释的便利 pr\_<foo>()（通常称为 pr_*()）宏可减轻编码的痛苦。笨重的

```
printk(KERN_FOO "<format-str>", vars...);
```

被优雅的

```
pr_foo("<format-str>", vars...);
```

​	替换，其中 \<foo> 是日志级别，是 emerg、alert、crit、err、warn、notice、info 或 debug 之一。鼓励使用它们：

```
// include/linux/printk.h:
[ ... ]
/**

* pr_emerg - 打印紧急级别消息
* @fmt：格式字符串
* @...：格式字符串的参数
  *
* 此宏扩展为具有 KERN_EMERG 日志级别的 printk。它 u

* 生成格式字符串。
  */
  #define pr_emerg(fmt, ...) \
  printk(KERN_EMERG pr_fmt(fmt), ##__VA_ARGS__)
  /**
* pr_alert - 打印警报级别消息
* @fmt：格式字符串
* @...：格式字符串的参数
  *
* 此宏扩展为具有 KERN_ALERT 日志级别的 printk。它 u
* 生成格式字符串。
  */
  #define pr_alert(fmt, ...) \
   printk(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
   […]
  #define pr_err(fmt, ...) \
   printk(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
  [……]
  #define pr_warn(fmt, ...) \
   printk(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
  [……]
  #define pr_notice(fmt, ...) \
   printk(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
  [……]
  #define pr_info(fmt, ...) \
  printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)
  [ … ]
  #ifdef DEBUG
  #define pr_devel(fmt, ...) \
  printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
  [ … ]
```

​	在使用 pr_*() 宏时，有一个名为 pr_cont() 的宏。它的工作是充当延续字符串，继续前一个 printk！这很有用...下面是其用法的一个示例：

```
// kernel/module.c
if (last_unloaded_module[0])
	pr_cont(" [last unloaded: %s]",
l	ast_unloaded_module);
	pr_cont("\n");
```

​	我们通常确保只有最后的 pr_cont() 包含换行符。为了避免不愉快的意外，例如 printk() 似乎没有生效，请养成以换行符“\n”结束 printk 的习惯（printf() 也是如此）。

​	从现在开始，我们通常只在向内核日志发出 printk 消息时使用这些 pr_foo()（或 pr\_*()）样式的宏。此外，非常重要的一点是：驱动程序作者必须使用 dev_\*() 宏。这意味着传递一个额外的第一个参数，即指向相关设备的指针（struct device *）。

​	当然，对于驱动的开发者更多常见的是：

```
/*
 * Some callsites directly call dev_printk rather than going through the
 * dev_<level> infrastructure, so we need to emit here as well as inside those
 * level-specific macros. Only one index entry will be produced, either way,
 * since dev_printk's `fmt` isn't known at compile time if going through the
 * dev_<level> macros.
 *
 * dev_fmt() isn't called for dev_printk when used directly, as it's used by
 * the dev_<level> macros internally which already have dev_fmt() processed.
 *
 * We also can't use dev_printk_index_wrap directly, because we have a separate
 * level to process.
 */
#define dev_printk(level, dev, fmt, ...)				\
	({								\
		dev_printk_index_emit(level, fmt);			\
		_dev_printk(level, dev, fmt, ##__VA_ARGS__);		\
	})

/*
 * #defines for all the dev_<level> macros to prefix with whatever
 * possible use of #define dev_fmt(fmt) ...
 */

#define dev_emerg(dev, fmt, ...) \
	dev_printk_index_wrap(_dev_emerg, KERN_EMERG, dev, dev_fmt(fmt), ##__VA_ARGS__)
#define dev_crit(dev, fmt, ...) \
	dev_printk_index_wrap(_dev_crit, KERN_CRIT, dev, dev_fmt(fmt), ##__VA_ARGS__)
#define dev_alert(dev, fmt, ...) \
	dev_printk_index_wrap(_dev_alert, KERN_ALERT, dev, dev_fmt(fmt), ##__VA_ARGS__)
#define dev_err(dev, fmt, ...) \
	dev_printk_index_wrap(_dev_err, KERN_ERR, dev, dev_fmt(fmt), ##__VA_ARGS__)
#define dev_warn(dev, fmt, ...) \
	dev_printk_index_wrap(_dev_warn, KERN_WARNING, dev, dev_fmt(fmt), ##__VA_ARGS__)
#define dev_notice(dev, fmt, ...) \
	dev_printk_index_wrap(_dev_notice, KERN_NOTICE, dev, dev_fmt(fmt), ##__VA_ARGS__)
#define dev_info(dev, fmt, ...) \
	dev_printk_index_wrap(_dev_info, KERN_INFO, dev, dev_fmt(fmt), ##__VA_ARGS__)

#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#define dev_dbg(dev, fmt, ...)						\
	dynamic_dev_dbg(dev, dev_fmt(fmt), ##__VA_ARGS__)
#elif defined(DEBUG)
#define dev_dbg(dev, fmt, ...)						\
	dev_printk(KERN_DEBUG, dev, dev_fmt(fmt), ##__VA_ARGS__)
#else
#define dev_dbg(dev, fmt, ...)						\
({									\
	if (0)								\
		dev_printk(KERN_DEBUG, dev, dev_fmt(fmt), ##__VA_ARGS__); \
})
#endif
```

## 写入控制台

​	回想一下，printk 输出可能最多到达三个位置：

- 第一个是内核内存日志缓冲区（始终）
- 第二个是非易失性日志文件（典型）
- 最后一个（我们将在这里讨论）是控制台设备

​	传统上，控制台设备是纯内核功能，是（超级）用户在非图形环境中登录到的初始终端窗口（/dev/console）。有趣的是，在 Linux 上，我们可以定义多个控制台 - 电传打字终端 (tty) 窗口（例如 /dev/console）、文本模式 VGA 控制台、帧缓冲区，甚至通过 USB 提供的串行端口（这在嵌入式系统开发过程中很常见；有关 Linux 控制台的更多信息，请参阅本章的“进一步阅读”部分）。

例如，当我们通过 USB 转 RS232 TTL UART（USB 转串行）电缆将 Raspberry Pi 开发板连接到 x86_64 笔记本电脑时（请参阅本章的“进一步阅读”部分，了解有关此非常有用的配件以及如何在 Raspberry Pi 上进行设置的博客文章），然后使用终端仿真器应用程序（如 minicom（或 screen）），这就是 Raspberry Pi 上显示的 tty 设备 - 它是串行端口：

```
rpi # tty
/dev/ttyS0
```

​	这里的重点是控制台通常是足够重要的日志消息的目标，包括那些来自内核深处的消息。Linux 的 printk 使用 sysctl（一种基于 proc 的机制）有条件地将其日志传送到控制台设备。为了更好地理解这一点，我们首先查看相关的 proc 伪文件（此处，在我们的 x86_64 Ubuntu 客户机上）：

```
$ cat /proc/sys/kernel/printk
4 4 1 7
```

​	我们将前面的四个数字解释为 printk 日志级别（0 为“紧急程度”最高，7 为“紧急程度”最低）。前面的四个整数序列的含义是：

- 当前（控制台）日志级别。关键含义是所有小于此值的消息也将发送到控制台设备！
- 缺乏明确日志级别的消息的默认级别。
- 允许的最低日志级别。
- 启动时默认日志级别。

​	我们可以看到日志级别 4 对应于 KERN_WARNING。因此，如果第一个数字为 4（实际上是 Linux 发行版的典型默认值），则所有低于日志级别 4 的 printk 实例都将发送到控制台设备，当然，它们还会被记录到内核日志缓冲区和文件中。实际上，通过这些设置，这适用于以下日志级别的所有内核消息：KERN_EMERG、KERN_ALERT、KERN_CRIT 和 KERN_ERR 默认情况下也将自动发送到控制台设备。

​	无论设置如何，日志级别 0 [KERN_EMERG] 的内核消息始终会打印到控制台，并且确实会打印到所有（非 GUI）终端窗口和内核日志缓冲区和日志文件中。

