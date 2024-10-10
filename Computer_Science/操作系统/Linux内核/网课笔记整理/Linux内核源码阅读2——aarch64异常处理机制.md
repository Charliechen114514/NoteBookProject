# Linux内核源码阅读：AArch64的异常处理机制详谈

​	任何玩过Arm64架构的朋友都知道，我们的ARM64架构有异常：Exception Levels, ELs，它是其异常处理机制的核心组成部分，允许系统在不同的特权级别下执行代码。ARM64定义了四个异常级别，每个级别具有不同的特权、功能和访问权限。以下是对每个异常级别的详细介绍：

## 四层异常与他们的切换

#### 1. EL0（用户模式）

- **特权级别**：最低。
- **功能**：咱们的程序一般都在这里，EL0运行普通用户应用程序，没有访问硬件资源的直接权限，所有对资源的访问都必须通过系统调用转发到EL1。
- **访问限制**：不能直接访问系统控制寄存器、内存管理单元等关键硬件组件。

#### 2. EL1（内核模式）

- **特权级别**：中等特权。
- **功能**：执行操作系统内核（Linux跑在这里）和设备驱动程序。EL1可以管理硬件资源，提供对应用程序的支持。
- **访问权限**：可以访问大多数系统资源，包括中断控制器、定时器等。EL1能够处理来自EL0的系统调用和异常。

#### 3. EL2（虚拟化模式）

- **特权级别**：高特权。
- **功能**：主要用于虚拟化环境，允许多个虚拟机共享硬件资源。EL2可以管理虚拟机监控器（hypervisor），提供对虚拟机的管理和资源分配。
- **访问权限**：除了访问EL1的资源外，还能控制和管理EL0和EL1的虚拟化环境。

#### 4. EL3（安全监控模式）

- **特权级别**：最高特权。
- **功能**：处理安全相关任务，如可信执行环境（TEE）的管理。EL3主要用于处理与系统安全性相关的异常。
- **访问权限**：拥有对所有资源的完全访问权限，包括其他所有异常级别的资源。

#### 异常级别的切换

当系统发生异常时，ARM64会根据当前的异常级别和异常类型自动转移到相应的更高异常级别。这个切换过程通常包括：

- **保存上下文**：保存当前处理程序的上下文（如PC和PSTATE）。
- **转移到更高的异常级别**：根据异常类型进入相应的处理程序。

## 两种异常

​	我们的异常分为两个大类：依照我们执行时异常的发生方式分为同步异常和异步异常。

#### 1. 同步异常

- **系统调用**：当用户模式（EL0）应用程序需要请求操作系统服务时，通过系统调用触发异常，转到内核模式（EL1）进行处理。
- **页面错误**：当程序试图访问未映射或无效的内存地址时，会引发页面错误。处理此异常通常涉及内存管理单元（MMU）的操作。
- **非法指令**：如果CPU执行了无效或未定义的指令，系统将引发此异常，并转入异常处理程序。
- **浮点异常**：与浮点运算相关的错误，如除以零或浮点溢出，触发此类型的异常。
- **断点异常**：用于调试的断点指令执行时，会触发该异常，转到调试处理程序。

#### 2. 异步异常

- **外部中断**：由硬件设备（如键盘、网络适配器等）生成，通知CPU有事件需要处理。外部中断通常具有高优先级，能够打断当前的执行流程。
- **定时器中断**：由系统定时器生成，用于实现任务调度和时间管理。定时器中断确保系统能够进行周期性的任务调度。
- **电源管理中断**：与电源状态变化相关的中断，例如进入休眠或唤醒时生成的信号。



## 处理办法（艰辛！）

​	笔者花费一些时间阅读了Entry.S文件，得到了这个结论。

​	外面首先锁定到这里，找到这个文件：定位到这个代码段：

>arch/arm64/kernel/entry.S

```
SYM_CODE_START(vectors)
	kernel_ventry	1, t, 64, sync		// Synchronous EL1t
	kernel_ventry	1, t, 64, irq		// IRQ EL1t
	kernel_ventry	1, t, 64, fiq		// FIQ EL1t
	kernel_ventry	1, t, 64, error		// Error EL1t

	kernel_ventry	1, h, 64, sync		// Synchronous EL1h
	kernel_ventry	1, h, 64, irq		// IRQ EL1h
	kernel_ventry	1, h, 64, fiq		// FIQ EL1h
	kernel_ventry	1, h, 64, error		// Error EL1h

	kernel_ventry	0, t, 64, sync		// Synchronous 64-bit EL0
	kernel_ventry	0, t, 64, irq		// IRQ 64-bit EL0
	kernel_ventry	0, t, 64, fiq		// FIQ 64-bit EL0
	kernel_ventry	0, t, 64, error		// Error 64-bit EL0

	kernel_ventry	0, t, 32, sync		// Synchronous 32-bit EL0
	kernel_ventry	0, t, 32, irq		// IRQ 32-bit EL0
	kernel_ventry	0, t, 32, fiq		// FIQ 32-bit EL0
	kernel_ventry	0, t, 32, error		// Error 32-bit EL0
SYM_CODE_END(vectors)
```

​	ARM64架构中不同异常向量的处理入口点（vector entry points）。每个`kernel_ventry`行代表一个特定异常类型在不同异常级别和模式下的处理方式。下面列个表说明：

1. **异常级别**：
   - **EL1t**（EL1 Synchronous）: 内核模式下的同步异常处理。
   - **EL1h**（EL1 Hypervisor）: 虚拟化环境下的同步异常处理。
   - **EL0**: 用户模式下的异常处理，分为64位和32位两种模式。
2. **异常类型**：
   - **sync**: 同步异常，如系统调用或页面错误。
   - **irq**: 硬件中断请求（IRQ），由外部设备生成的中断。
   - **fiq**: 快速中断请求（FIQ），用于更高优先级的中断处理。
   - **error**: 处理其他类型的错误，如未定义指令或故障。
3. **指令解释**：
   - `kernel_ventry`: 这是一个宏或函数，表示定义一个异常处理程序的入口点。
   - 第一个参数（如`1`或`0`）通常表示异常级别（1表示EL1，0表示EL0）。
   - 第二个参数（如`t`或`h`）表示异常类型（`t`表示异常，`h`表示虚拟化）。
   - 第三个参数（如`64`或`32`）表示处理器的位数（64位或32位）。
   - 第四个参数是具体的异常类型（如`sync`、`irq`等）。

也就是说这个汇编文件实际上就是描述了不同的Exception Level下的不同的异常类型的处理机制表。

​	很好，但是当你browse大部分博客准备查看我们的异常exception vector handler在哪里的时候，你会惊喜的发现自己找不到handler了！在哪里呢？在这里！

​	当然，这是为了简化在ARM64内核中定义异常处理程序的流程，通过参数化异常级别、处理类型和寄存器大小，方便地创建多个处理程序。这种结构化的方式有助于保持代码的整洁和可维护性。（但是苦了我这种喜欢读recent源码的人）

```
	.macro entry_handler el:req, ht:req, regsize:req, label:req
SYM_CODE_START_LOCAL(el\el\ht\()_\regsize\()_\label)
	kernel_entry \el, \regsize
	mov	x0, sp
	bl	el\el\ht\()_\regsize\()_\label\()_handler	# 跳转到这个异常的handler
	.if \el == 0
	b	ret_to_user
	.else
	b	ret_to_kernel
	.endif
SYM_CODE_END(el\el\ht\()_\regsize\()_\label)
	.endm

/*
 * Early exception handlers
 */
	entry_handler	1, t, 64, sync
	entry_handler	1, t, 64, irq
	entry_handler	1, t, 64, fiq
	entry_handler	1, t, 64, error

	entry_handler	1, h, 64, sync
	entry_handler	1, h, 64, irq
	entry_handler	1, h, 64, fiq
	entry_handler	1, h, 64, error

	entry_handler	0, t, 64, sync
	entry_handler	0, t, 64, irq
	entry_handler	0, t, 64, fiq
	entry_handler	0, t, 64, error

	entry_handler	0, t, 32, sync
	entry_handler	0, t, 32, irq
	entry_handler	0, t, 32, fiq
	entry_handler	0, t, 32, error
```

​	不着急一点点看：

#### 宏定义结构

```
SYM_CODE_START_LOCAL(el\el\ht\()_\regsize\()_\label)
```

- **SYM_CODE_START_LOCAL**：这个宏用于开始定义一个本地符号，通常用于异常处理程序的入口点。
- **`el`**：表示异常级别（例如EL0、EL1等）。
- **`ht`**：表示处理类型（可能指同步或异步）。
- **`regsize`**：表示寄存器大小（如32位或64位）。
- **`label`**：定义处理程序的标签名称。

#### 处理程序的入口逻辑

```
kernel_entry \el, \regsize
```

- **kernel_entry**：这通常是另一个宏，用于设置内核入口环境，根据`el`和`regsize`初始化异常处理的上下文。

```
mov x0, sp
```

- 将堆栈指针（SP）的值移动到寄存器`x0`，这通常用于传递参数或保存上下文。

```
bl el\el\ht\()_\regsize\()_\label\()_handler
```

- **`bl`**指令用于调用指定的异常处理程序。在这里，它根据传入的参数构造处理程序名称，调用实际的异常处理函数。

#### 返回逻辑

```
if \el == 0
    b ret_to_user
.else
    b ret_to_kernel
.endif
```

- 这部分代码根据当前的异常级别决定返回的处理逻辑。
  - **如果`el`是0**，表示用户模式，则跳转到`ret_to_user`，该标签通常处理返回用户态的逻辑。
  - **如果`el`不是0**，表示内核模式，则跳转到`ret_to_kernel`，用于返回内核态的逻辑。

#### 宏结束

```
SYM_CODE_END(el\el\ht\()_\regsize\()_\label)
.endm
```

- **SYM_CODE_END**：结束符号定义，标记宏的结束。

很好！我们大致明白了：实际上这个handler就是处理完毕后判断需要调回哪个层级（内核态还是用户态），最后，我们需要揭露以下kernel_entry的神秘面纱:

​	回到这个文件的开头：

```
	.macro kernel_ventry, el:req, ht:req, regsize:req, label:req
	.align 7
.Lventry_start\@:
	.if	\el == 0
	/*
	 * This must be the first instruction of the EL0 vector entries. It is
	 * skipped by the trampoline vectors, to trigger the cleanup.
	 */
	b	.Lskip_tramp_vectors_cleanup\@
	.if	\regsize == 64
	mrs	x30, tpidrro_el0
	msr	tpidrro_el0, xzr
	.else
	mov	x30, xzr
	.endif
.Lskip_tramp_vectors_cleanup\@:
	.endif

	sub	sp, sp, #PT_REGS_SIZE
#ifdef CONFIG_VMAP_STACK
	/*
	 * Test whether the SP has overflowed, without corrupting a GPR.
	 * Task and IRQ stacks are aligned so that SP & (1 << THREAD_SHIFT)
	 * should always be zero.
	 */
	add	sp, sp, x0			// sp' = sp + x0
	sub	x0, sp, x0			// x0' = sp' - x0 = (sp + x0) - x0 = sp
	tbnz	x0, #THREAD_SHIFT, 0f
	sub	x0, sp, x0			// x0'' = sp' - x0' = (sp + x0) - sp = x0
	sub	sp, sp, x0			// sp'' = sp' - x0 = (sp + x0) - x0 = sp
	b	el\el\ht\()_\regsize\()_\label

0:
	/*
	 * Either we've just detected an overflow, or we've taken an exception
	 * while on the overflow stack. Either way, we won't return to
	 * userspace, and can clobber EL0 registers to free up GPRs.
	 */

	/* Stash the original SP (minus PT_REGS_SIZE) in tpidr_el0. */
	msr	tpidr_el0, x0

	/* Recover the original x0 value and stash it in tpidrro_el0 */
	sub	x0, sp, x0
	msr	tpidrro_el0, x0

	/* Switch to the overflow stack */
	adr_this_cpu sp, overflow_stack + OVERFLOW_STACK_SIZE, x0

	/*
	 * Check whether we were already on the overflow stack. This may happen
	 * after panic() re-enables interrupts.
	 */
	mrs	x0, tpidr_el0			// sp of interrupted context
	sub	x0, sp, x0			// delta with top of overflow stack
	tst	x0, #~(OVERFLOW_STACK_SIZE - 1)	// within range?
	b.ne	__bad_stack			// no? -> bad stack pointer

	/* We were already on the overflow stack. Restore sp/x0 and carry on. */
	sub	sp, sp, x0
	mrs	x0, tpidrro_el0
#endif
	b	el\el\ht\()_\regsize\()_\label # 还是一样，最后跳转道实际的处理程序上去
.org .Lventry_start\@ + 128	// Did we overflow the ventry slot?
	.endm
```

​	下面慢慢说：

```
.macro kernel_ventry, el:req, ht:req, regsize:req, label:req
    .align 7
.Lventry_start\@:
    .if \el == 0
        b .Lskip_tramp_vectors_cleanup\@
        .if \regsize == 64
            mrs x30, tpidrro_el0
            msr tpidrro_el0, xzr
        .else
            mov x30, xzr
        .endif
.Lskip_tramp_vectors_cleanup\@:
    .endif

    sub sp, sp, #PT_REGS_SIZE
```

- `kernel_ventry`宏定义了内核在不同异常级别和寄存器大小下的入口逻辑。
- 指令说明
  - `b .Lskip_tramp_vectors_cleanup\@`用于跳过清理操作。
  - 根据寄存器大小（64位或32位），适当设置`x30`寄存器。

#### 堆栈溢出检查

```
#ifdef CONFIG_VMAP_STACK
    add sp, sp, x0
    sub x0, sp, x0
    tbnz x0, #THREAD_SHIFT, 0f
    sub x0, sp, x0
    sub sp, sp, x0
    b el\el\ht\()_\regsize\()_\label

0:
    msr tpidr_el0, x0
    sub x0, sp, x0
    msr tpidrro_el0, x0
    adr_this_cpu sp, overflow_stack + OVERFLOW_STACK_SIZE, x0
    mrs x0, tpidr_el0
    sub x0, sp, x0
    tst x0, #~(OVERFLOW_STACK_SIZE - 1)
    b.ne __bad_stack
    sub sp, sp, x0
    mrs x0, tpidrro_el0
#endif
```

此段代码检测堆栈溢出并执行相应的处理。

- 通过调整`sp`来检查堆栈溢出情况。
- 如果检测到溢出，保存相关寄存器值并切换到溢出堆栈。

#### 入口跳转

```
b el\el\ht\()_\regsize\()_\label
.org .Lventry_start\@ + 128  // Did we overflow the ventry slot?
.endm
```

- **功能**：最终跳转到对应的内核处理函数，确保进入正确的异常处理逻辑。



​	现在我们总结以下：

​	我们的现代内核采用汇编宏的办法定义了一个及其灵活的内核异常句柄表。他排列开来，使用一个handler模板生成对应的注册机制。进入中断向量，他首先要检查堆栈情况（看看是堆栈溢出还是其他错误），然后跳转道实际的处理函数（这个要在外面找，但是遗憾的是目前没有找到 :( ），随后要做清理退出，根据进入处理句柄的时候是内核态还是用户态来决定是返回恢复哪里的堆栈信息。

​	就是这样！