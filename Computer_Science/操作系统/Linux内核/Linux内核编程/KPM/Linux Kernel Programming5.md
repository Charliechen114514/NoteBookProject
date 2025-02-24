# Linux Kernel Programming 5

## 前言

​	鸽了两个月玩操作系统和单片机了，现在回归正事。

## 速速配置一个可以用于Debug的内核

​	现在，我们需要配置一个可以用来速速debug的内核。关于内核如何进行配置，笔者在[Linux Kernel Programming (个人读书笔记)-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/143441049)已经说的很明白了。

​	我们现在需要开启如下的选项。

#### 通用内核调试工具

- **CONFIG_DEBUG_KERNEL** 和 **CONFIG_DEBUG_INFO**: 内核调试信息和调试内核。
- **CONFIG_DEBUG_MISC**: 其他调试选项。
- **CONFIG_MAGIC_SYSRQ**: 启用魔术 SysRq 快捷键功能。
- **CONFIG_DEBUG_FS**: 启用 debugfs 伪文件系统。
- **CONFIG_KGDB**: 内核 GDB 调试支持（可选，推荐）。
- **CONFIG_UBSAN**: 未定义行为检查器。
- **CONFIG_KCSAN**: 动态数据竞争检测器。

#### 内存调试

- **CONFIG_SLUB_DEBUG**: SLUB 内存分配器调试。
- **CONFIG_DEBUG_MEMORY_INIT**: 内存初始化调试。
- **CONFIG_KASAN**: 强大的内核地址消毒器（KASAN）内存检查器。
- **CONFIG_DEBUG_SHIRQ**: 共享中断请求调试。
- **CONFIG_SCHED_STACK_END_CHECK**: 调度器栈结束检查。
- **CONFIG_DEBUG_PREEMPT**: 抢占调试。

#### 锁调试

- **CONFIG_PROVE_LOCKING**: 强大的锁依赖检测功能，用于捕获锁相关的错误。此选项会启用其他多个锁调试配置（详见第13章，内核同步 - 第二部分）。
- **CONFIG_LOCK_STAT**: 锁统计信息。
- **CONFIG_DEBUG_ATOMIC_SLEEP**: 原子操作中的睡眠调试。
- **CONFIG_BUG_ON_DATA_CORRUPTION**: 数据损坏时触发 BUG。
- **CONFIG_STACKTRACE**: 堆栈跟踪。
- **CONFIG_DEBUG_BUGVERBOSE**: 详细的 BUG 信息。

#### 跟踪和性能分析

- **CONFIG_FTRACE**: ftrace 跟踪工具。在其子菜单中，至少启用几个“跟踪器”，包括“内核函数[图]跟踪器”。
- **CONFIG_BUG_ON_DATA_CORRUPTION**: 数据损坏时触发 BUG。

#### 架构特定调试（x86 架构）

- **CONFIG_EARLY_PRINTK**: 早期打印内核信息（架构特定）。
- **CONFIG_DEBUG_BOOT_PARAMS**: 启动参数调试。
- **CONFIG_UNWINDER_FRAME_POINTER**: 选择 FRAME_POINTER 和 CONFIG_STACK_VALIDATION。

### 需要注意的是

​	我们之后会开始编写常见的驱动，为此，需要我们留意的是——我们的驱动能否加载成功，需要保证我们编译使用的kernel版本和现在目标操作系统上Linux的版本是完全一致——精确到小数点的！比如说，我们在Ubuntu22.04, 使用6.13.1编译的内核中，我们进一步借用这里配置编译我们的驱动后，不可以直接拿到其他的发行版甚至是同一发行版不同配置的内核！（注意，甚至一些config的选项差异都会决定我们能否挂载成功我们的模块）。所以，需要确保我们的源码编译和目标操作系统上的那个是完全一致的！不容许有任何差别。（一个好的办法就是直接复制.config编译部署）

## 注意：一些安全函数的使用

​	在过去，我们习惯上使用诸如sprintf,strlen等函数，但实际上，这些函数并不安全。比如说，在很多场合下，我们的sprintf生成字符串的函数可能会引发潜在的内存践踏（虽说默认的场景下编译器会汇报一个警告，但是你知道的，很多人不在乎警告）

​	静态分析器有的时候会捕捉这些潜在的危险行为。所以，使用那些带有边界检查的（比如说我们的strncat啊，strncpy等等函数）

## 关于License的使用

​	Linux Kernel的License是GPL v2协议的，意味着我们要给Linux提供源码，也就必须是GNU GPL-2.0协议。每一个源文件的第一行也必须著名 SPDX (Software Package Data Exchange)

```
// SPDX-License-Identifier: GPL-2.0 
```

​	对于非主线部分的代码，可以有两个部分

1. 通过 SPDX-License-Identifier 标记作为第一个源代码行（中的注释）。这严格适用于源代码树中的模块，并不总是适用于树外模块。
2. 通过 MODULE_LICENSE() 宏。请注意官方内核文档明确指出的内容 此标签既不能替代正确的源代码许可证信息 (SPDX-License-Identifier)，也不以任何方式与表达或确定模块源代码所依据的确切许可证相关。” 此标签的唯一目的是提供足够的信息，说明模块是免费软件还是内核模块加载器和用户空间工具的专有软件。