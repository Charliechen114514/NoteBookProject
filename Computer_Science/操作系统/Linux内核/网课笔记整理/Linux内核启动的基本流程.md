# Linux内核启动的基本流程

## 从硬件上电到BIOS

​	我们首先需要说的是实模式，实模式让所有软件访问到的地址都是最真实的物理地址。同时，软件可以不受限制的操作IO和内存。与之相对的是保护模式：进程访问到的全部都是虚拟地址，使用页表等维护到物理地址的映射，从而对内存和IO设备进行保护，显然这更加的安全。同时保证了扩展性和灵活性（在不同的进程下，他们使用的同一个虚拟地址可以访问到不同的物理地址）。

​	现在，摁下电源键，主板开始reset我们的硬件状态，将CPU进行初始化。对于使用Intel的芯片，他们会首先开启实模式：此时此刻使用内存段管理0 - 0xFFFFF。CPU自身被初始化为0XFFFF0（CS:IP = 0xFFFF: 0x0000）

## 从BIOS到Bootloader

​	BIOS的启动和运行程序放在了CPU上电后初始化的位置。上面，我提到了CPU自身被初始化为0XFFFF0（CS:IP = 0xFFFF: 0x0000）。说明我们的BIOS程序放在了这里。现在，程序开始进行硬件自检（查看硬件有没有问题）。随后将会选择一个启动设备，即扫描存在启动代码的扇区，交给其中的Bootloader来初始化中断向量和中断服务程序。现在在将boot.img放到一个0x7c00（暂时放到这里）

## BootLoader加载流程

​	boot.img就是boot.S编译的结果，安装在启动盘的第一个扇区，即MBR。由于空间大小有限，故只是起到了一个引导的作用。现在，我们加载好内核后启动main函数：即初始化控制台，计算模块的基地址，设置root设备，读取grub引导文件以及加载模块。之后就会开始创建0号进程等开始运行了。

### main

​	main函数将会进行一系列初始化，之后才会开启新的中断。从而使得内核模式进行真正的运行：

- 为0号进程建立内核态的堆栈
- 清空eflags今存其
- 调用setup_idt填充idt
- 把bios获取到的参数传递给第一个页框进行保存
- 使用GDT和IDT表填充寄存器
- 建立终端，让用户可以开始交互

​	在Linux的核心启动函数是：start_kernel

>init/main.c

```
asmlinkage __visible __init __no_sanitize_address __noreturn __no_stack_protector
void start_kernel(void)  // 内核启动入口函数
{
    char *command_line;   // 存储命令行参数的指针
    char *after_dashes;   // 存储处理后的命令行参数指针

    set_task_stack_end_magic(&init_task);  // 设置初始任务的栈结束魔数，检测栈溢出
    smp_setup_processor_id();                // 设置对称多处理系统的 CPU ID
    debug_objects_early_init();              // 进行早期调试对象的初始化
    init_vmlinux_build_id();                 // 初始化内核版本信息和编译时间

    cgroup_init_early();                     // 早期初始化控制组（cgroup）
    local_irq_disable();                     // 禁用本地中断
    early_boot_irqs_disabled = true;        // 标记早期引导中断已禁用

    boot_cpu_init();                         // 初始化引导 CPU
    page_address_init();                     // 初始化页地址
    pr_notice("%s", linux_banner);           // 输出内核版本信息
    early_security_init();                   // 初始化安全相关配置
    setup_arch(&command_line);               // 进行架构相关设置
    setup_boot_config();                     // 设置引导配置
    setup_command_line(command_line);        // 解析命令行参数
    setup_nr_cpu_ids();                      // 设置 CPU ID 数量
    setup_per_cpu_areas();                   // 初始化每个 CPU 的内存区域
    smp_prepare_boot_cpu();                  // 准备引导 CPU 的架构特定设置
    early_numa_node_init();                  // 进行早期 NUMA 节点初始化
    boot_cpu_hotplug_init();                 // 初始化引导 CPU 热插拔支持

    pr_notice("Kernel command line: %s\n", saved_command_line);  // 打印内核命令行参数
    jump_label_init();                       // 初始化跳跃标签
    parse_early_param();                     // 解析早期参数

	// 如果还记得如何调试Linux内核的话
    after_dashes = parse_args("Booting kernel", // 解析引导时的命令行参数
                               static_command_line, __start___param,
                               __stop___param - __start___param,
                               -1, -1, NULL, &unknown_bootoption);
    print_unknown_bootoptions();             // 打印未识别的引导选项

    if (!IS_ERR_OR_NULL(after_dashes))      // 如果解析成功
        parse_args("Setting init args", after_dashes, NULL, 0, -1, -1,
                   NULL, set_init_arg);    // 设置初始化参数

    if (extra_init_args)                    // 如果有额外的初始化参数
        parse_args("Setting extra init args", extra_init_args,
                   NULL, 0, -1, -1, NULL, set_init_arg);  // 设置额外初始化参数

    random_init_early(command_line);        // 进行早期随机数生成器初始化

    setup_log_buf(0);                       // 设置日志缓冲区
    vfs_caches_init_early();                // 初始化虚拟文件系统缓存
    sort_main_extable();                    // 排序主异常表
    trap_init();                            // 初始化异常处理
    mm_core_init();                         // 初始化内存管理核心
    poking_init();                          // 初始化 poking 机制
    ftrace_init();                          // 初始化跟踪功能

    early_trace_init();                     // 进行早期跟踪初始化

    sched_init();                           // 初始化调度器

    if (WARN(!irqs_disabled(),                // 检查中断是否意外启用
            "Interrupts were enabled *very* early, fixing it\n"))
        local_irq_disable();                // 如果启用，则禁用本地中断

    radix_tree_init();                      // 初始化基数树
    maple_tree_init();                      // 初始化maple tree
    									// 这是Linux新引入的数据结构

    housekeeping_init();                    // 初始化系统管理相关内容

    workqueue_init_early();                 // 初始化工作队列
    rcu_init();                             // 初始化 RCU

    trace_init();                           // 初始化跟踪事件

    if (initcall_debug)                     // 如果启用初始化调用调试
        initcall_debug_enable();            // 启用调试

    context_tracking_init();                // 初始化上下文跟踪
    early_irq_init();                       // 早期初始化中断
    init_IRQ();                            // 初始化中断处理
    tick_init();                            // 初始化定时器
    rcu_init_nohz();                       // 初始化无时钟 RCU
    init_timers();                         // 初始化定时器系统
    srcu_init();                           // 初始化 SRCU
    hrtimers_init();                        // 初始化高分辨率定时器
    softirq_init();                         // 初始化软中断
    timekeeping_init();                     // 初始化时间keeping系统
    time_init();                           // 完成时间初始化

    random_init();                          // 进行随机数生成器初始化

    kfence_init();                          // 初始化内存保护机制
    boot_init_stack_canary();               // 初始化栈金丝雀

    perf_event_init();                      // 初始化性能事件监控
    profile_init();                         // 初始化性能分析配置

    call_function_init();                   // 初始化函数调用机制
    WARN(!irqs_disabled(),                  // 检查中断状态
         "Interrupts were enabled early\n");

    early_boot_irqs_disabled = false;      // 允许后续启用中断
    local_irq_enable();                     // 启用本地中断

    kmem_cache_init_late();                 // 延迟初始化内存缓存

    console_init();                         // 初始化控制台以输出信息
    if (panic_later)                        // 如果有紧急情况
        panic("Too many boot %s vars at `%s'", panic_later,
              panic_param);                 // 触发内核恐慌

    lockdep_init();                        // 初始化锁依赖检查

    locking_selftest();                     // 自检锁机制

#ifdef CONFIG_BLK_DEV_INITRD
    if (initrd_start && !initrd_below_start_ok &&  // 检查 initrd
        page_to_pfn(virt_to_page((void *)initrd_start)) < min_low_pfn) {
        pr_crit("initrd overwritten (0x%08lx < 0x%08lx) - disabling it.\n",
            page_to_pfn(virt_to_page((void *)initrd_start)),
            min_low_pfn);
        initrd_start = 0;                   // 如果被覆盖则禁用 initrd
    }
#endif

    setup_per_cpu_pageset();                // 设置每个 CPU 的页面集合
    numa_policy_init();                     // 初始化 NUMA 策略
    acpi_early_init();                      // 早期初始化 ACPI
    if (late_time_init)                     // 如果有延迟时间初始化
        late_time_init();                   // 执行延迟时间初始化
    sched_clock_init();                     // 初始化调度时钟
    calibrate_delay();                      // 校准延迟

    arch_cpu_finalize_init();               // 完成架构相关的 CPU 初始化

    pid_idr_init();                         // 初始化 PID IDR
    anon_vma_init();                        // 初始化匿名虚拟内存

#ifdef CONFIG_X86
    if (efi_enabled(EFI_RUNTIME_SERVICES))  // 检查 EFI 运行时服务是否启用
        efi_enter_virtual_mode();           // 进入 EFI 虚拟模式
#endif

    thread_stack_cache_init();              // 初始化线程栈缓存
    cred_init();                            // 初始化凭证管理
    fork_init();                            // 初始化进程分叉机制
    proc_caches_init();                     // 初始化进程缓存
    uts_ns_init();                          // 初始化 UTS 命名空间
    key_init();                             // 初始化密钥管理
    security_init();                        // 初始化安全管理
    dbg_late_init();                        // 延迟初始化调试相关内容
    net_ns_init();                          // 初始化网络命名空间
    vfs_caches_init();                      // 初始化虚拟文件系统缓存
    pagecache_init();                       // 初始化页面缓存
    signals_init();                         // 初始化信号管理
    seq_file_init();                        // 初始化序列文件支持
    proc_root_init();                       // 初始化进程根目录
    nsfs_init();                            // 初始化命名空间文件系统
    pidfs_init();                           // 初始化 PID 文件系统
    cpuset_init();                          // 初始化 CPU 集
    cgroup_init();                          // 初始化控制组
    taskstats_init_early();                 // 早期初始化任务统计
    delayacct_init();                       // 初始化延迟账户

    acpi_subsystem_init();                  // 初始化 ACPI 子系统
    arch_post_acpi_subsys_init();           // 执行架构特定的 ACPI 后初始化
    kcsan_init();                           // 初始化 KCSAN（内存竞争检测）

    rest_init();                            // 执行后续初始化，开始内核主循环
}

```

​	当然还有标记有没有关闭本地中断的检查：

```
/*
 * Debug helper: via this flag we know that we are in 'early bootup code'
 * where only the boot processor is running with IRQ disabled.  This means
 * two things - IRQ must not be enabled before the flag is cleared and some
 * operations which are not allowed with IRQ disabled are allowed while the
 * flag is set.
 */
bool early_boot_irqs_disabled __read_mostly;
```

​	更加详细的注释我放在Reference了









# Reference

```
asmlinkage __visible __init __no_sanitize_address __noreturn __no_stack_protector
void start_kernel(void)
```

- `asmlinkage`：指示此函数的参数通过栈传递，通常用于系统调用。
- `__visible`：表示该函数对外可见。
- `__init`：表示函数只在初始化期间使用，之后会被释放以节省内存。
- `__no_sanitize_address`：告诉编译器不要对该函数进行地址消毒检查。
- `__noreturn`：指示该函数不会返回，通常是因为它会调用 `exec()` 或进入无限循环。
- `__no_stack_protector`：表示不启用栈保护机制。

```
c复制代码char *command_line;
char *after_dashes;
```

定义了两个指针：`command_line` 用于存储内核启动时的命令行参数，`after_dashes` 用于存储在命令行参数中处理后的部分。

```
set_task_stack_end_magic(&init_task);
```

设置初始任务的栈结束魔数，帮助检测栈溢出。魔数是一种特殊值，用于标识栈的边界。

```
smp_setup_processor_id();
```

针对对称多处理（SMP）系统设置 CPU ID，为每个 CPU 分配唯一的标识符。

```
debug_objects_early_init();
```

进行早期的调试对象初始化，确保调试工具可以使用，用于后续的内存和对象管理。

```
init_vmlinux_build_id();
```

初始化内核的版本信息（如编译时间和版本号），便于在调试时识别使用的内核版本。

```
cgroup_init_early();
```

早期初始化控制组（cgroup），用于管理和限制资源使用，如 CPU 和内存。

```
local_irq_disable();
early_boot_irqs_disabled = true;
```

禁用本地中断，防止在初始化期间发生中断，标记早期引导中断已禁用。

接下来是进行各个子系统的初始化，包括：

```
boot_cpu_init();
```

初始化引导 CPU，包括设置其状态和特性。

```
page_address_init();
```

初始化页地址，设置虚拟地址到物理地址的映射。

```
pr_notice("%s", linux_banner);
```

输出内核版本信息，通常由 `linux_banner` 定义。

```
early_security_init();
```

进行安全相关的初始化，确保引导过程中的安全性。

```
setup_arch(&command_line);
```

进行与架构相关的设置，处理 `command_line`。

```
setup_boot_config();
setup_command_line(command_line);
```

设置引导配置和命令行参数。

```
setup_nr_cpu_ids();
setup_per_cpu_areas();
```

初始化 CPU ID 数量和每个 CPU 的区域，准备多处理器支持。

```
smp_prepare_boot_cpu();
```

为引导 CPU 准备架构特定的设置。

```
early_numa_node_init();
```

进行早期 NUMA（非统一内存访问）节点初始化。

```
boot_cpu_hotplug_init();
```

初始化引导 CPU 热插拔功能，允许动态管理 CPU。

接下来，打印内核命令行参数并进行早期参数解析：

```
pr_notice("Kernel command line: %s\n", saved_command_line);
jump_label_init();
parse_early_param();
```

显示当前的内核命令行，初始化跳跃标签（用于动态调试），解析早期参数。

```
after_dashes = parse_args("Booting kernel",
                  static_command_line, __start___param,
                  __stop___param - __start___param,
                  -1, -1, NULL, &unknown_bootoption);
```

解析命令行参数并处理，查找未知选项。

```
print_unknown_bootoptions();
```

打印未识别的引导选项，以便开发者调试。

```
if (!IS_ERR_OR_NULL(after_dashes))
    parse_args("Setting init args", after_dashes, NULL, 0, -1, -1,
           NULL, set_init_arg);
```

如果解析成功，则设置初始化参数。

接下来的代码块继续进行早期的随机数生成、日志缓冲区初始化、虚拟文件系统缓存初始化等，确保内核启动时各个子系统处于良好状态。

```
sched_init();
```

初始化调度器，准备管理任务的执行。

```
local_irq_disable();
```

再次禁用本地中断，确保在初始化期间不会发生中断。

```
rcu_init();
```

初始化 RCU（读-复制-更新）机制，确保高效的并发访问。

```
tick_init();
```

- 初始化系统定时器（tick），这为内核提供了时间管理的基础，允许内核跟踪时间流逝并管理任务的调度。

```
timekeeping_init();
```

- 进行时间keeping系统的初始化。这包括设置系统时钟、处理闰年和闰秒等，以确保系统时间的准确性。

```
time_init();
```

- 完成时间相关的初始化，设置系统的基准时间，确保其他模块可以使用正确的时间信息。

```
perf_event_init();
```

- 初始化性能事件监控。这个机制允许内核和用户空间程序监控硬件性能计数器，以进行性能分析和调优。

```
c


复制代码nit();
```

- 初始化性能分析相关的配置和数据结构。这为后续的性能分析提供支持。

### 进程管理

```
fork_init();
```

- 初始化进程分叉相关的设置，准备处理新的进程创建。这个函数为系统的多任务处理打下基础。

```
proc_caches_init();
```

- 初始化与进程相关的缓存，以提高进程管理的效率。这涉及到为进程信息、文件描述符等分配缓存，以减少内存访问延迟。

```
cred_init();
```

- 初始化进程的凭证（credentials）管理系统。凭证用于管理进程的身份和权限，确保安全性。

```
signals_init();
```

- 初始化信号处理系统，使内核能够有效地处理进程间通信和信号通知。



>[Linux初始化 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/608043853)
>
>[Introducing maple trees [LWN.net\]](https://lwn.net/Articles/845507/)













