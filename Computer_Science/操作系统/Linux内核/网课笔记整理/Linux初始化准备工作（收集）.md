引导过程中，Linux的内核代码被解压至内存中，但是Linux初始化还需要做一些准备工作，Linux初始化内核大部分是由C语言编写，所以需要在初始前对cpu的栈寄存器等进行设置，让后续的C语言代码工作。

## Linux初始化准备工作

### 更新栈顶、GDT、IDT

Linux的内核代码是从arch/x86/kernel/head_64.S开始执行的。首先更新栈顶地址。

```text
	.text
	__HEAD
	.code64
SYM_CODE_START_NOALIGN(startup_64)
	UNWIND_HINT_EMPTY
	leaq	(__end_init_task - FRAME_SIZE)(%rip), %rsp
	
```

_text的在文件 arch/x86/kernel/vmlinux.lds.S中出现，下面的代码会用到该变量

```text
	.text :  AT(ADDR(.text) - LOAD_OFFSET) {
		_text = .;
		...
	} :text =0xcccc
	...
	. = ALIGN(PAGE_SIZE);
```

_text 指向程序的起始地址。leaq _text(%rip), %rdi 将 _text 的地址与 %rip 中的下一条指令的地址相加，结果存放在 %rdi 中，作为程序的入口点参数。

MSR_GS_BASE 寄存器的值设置为 initial_gs(%rip) 加上 _text 的地址与当前代码执行位置的差。MSR_GS_BASE 是一个机器特定的寄存器，它用于存储用于访问线程本地存储（TLS）的基址。在 Linux 内核中，它被用来存储当前任务的线程本地存储基址。initial_gs 是用于存储内核代码使用的 GS 寄存器的值。通过在 initial_gs(%rip) 中存储的值，程序可以找到内核 GS 寄存器的值。然后计算 _text 的地址与当前指令地址的偏移量，将这个偏移量加上 initial_gs(%rip) 中的值，得到 GS 寄存器的新值，最后将它写入到 MSR_GS_BASE 寄存器中。

最后将rsi寄存器的值压入栈中，然后调用startup_64_setup_env函数，最后将rsi出栈

```text
    leaq	_text(%rip), %rdi

    movl	$MSR_GS_BASE, %ecx
	movq	initial_gs(%rip), %rax
	movq	$_text, %rdx
	subq	%rdx, %rax
	addq	%rdi, %rax
	movq	%rax, %rdx
	shrq	$32,  %rdx
	wrmsr

	pushq	%rsi
	call	startup_64_setup_env
	popq	%rsi
```

### startup_64_setup_env

1. 加载 GDT：将 startup_gdt 中定义的[全局描述符表](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=全局描述符表&zhida_source=entity)（GDT）的地址加载到 GDTR 寄存器中，以便操作系统能够访问 GDT 中的描述符。
2. 加载新的 GDT 后，重新加载数据段寄存器：由于新的 GDT 已经加载，所以需要重新加载数据段寄存器（DS、SS、ES）。
3. 加载 IDT：使用 startup_64_load_idt 函数加载中断描述符表（IDT）。

确保操作系统能够正确访问和使用内存和中断等硬件资源。

```text
void __head startup_64_setup_env(unsigned long physbase)
{
	/* Load GDT */
	startup_gdt_descr.address = (unsigned long)fixup_pointer(startup_gdt, physbase);
	native_load_gdt(&startup_gdt_descr);

	/* New GDT is live - reload data segment registers */
	asm volatile("movl %%eax, %%ds\n"
		     "movl %%eax, %%ss\n"
		     "movl %%eax, %%es\n" : : "a"(__KERNEL_DS) : "memory");

	startup_64_load_idt(physbase);
}
```

### 加载CS

加载内核段的CS，并跳转到.Lon_kernel_cs代码段中

```text
    pushq	$__KERNEL_CS
	leaq	.Lon_kernel_cs(%rip), %rax
	pushq	%rax
	lretq
```

### Lon_kernel_cs

调用verify_cpu函数,是为了检验CPU的PAT、NX、MTRR是否开启。PAT是指"Page Attribute Table"（页属性表），是一种x86处理器的内存管理机制。它允许对物理页面设置多种内存类型，如缓存、可写、不可写、写回等属性。NX (No-Execute) 是一项硬件技术，用于保护计算机系统不受到恶意代码攻击，防止恶意代码在内存中执行。MTRR是Memory Type Range Registers（内存类型范围寄存器）的缩写，它是一种机制，用于定义系统中某些物理内存区域的缓存属性。并且verify_cpu将CPU的一些属性存储到全局变量boot_cpu_data中。

```text
.Lon_kernel_cs:
	UNWIND_HINT_EMPTY

	/* Sanitize CPU configuration */
	call verify_cpu
	leaq	_text(%rip), %rdi
	pushq	%rsi
	call	__startup_64
	popq	%rsi

	/* Form the CR3 value being sure to include the CR3 modifier */
	addq	$(early_top_pgt - __START_KERNEL_map), %rax
	jmp 1f
```

### __startup_64

__startup_64函数将物理地址空间的前4G映射到[虚拟地址空间](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=虚拟地址空间&zhida_source=entity)中的低4G。它首先检查LA57的支持，物理地址是否过大，是否2M对齐，然后计算出物理地址和虚拟地址之间的偏移，用来修复页表项中的地址。最后，它还会处理一些内核映像之外的地址空间，保证这些地址空间不会被访问。并返回操作成功的标准，若失败则会陷入死循环。

具体如下

1. 检查LA57支持；
2. 检查物理地址是否过大；
3. 计算运行地址和实际地址之间的偏移量；
4. 检查地址是否对齐；
5. 获取SME加密掩码，并将其包括在修正值中；
6. 修正页表中的物理地址；
7. 为switchover设置[恒等映射](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=恒等映射&zhida_source=entity)；
8. 修正内核文本和数据虚拟地址，并使内核镜像之外的页面无效

```text
unsigned long __head __startup_64(unsigned long physaddr,
				  struct boot_params *bp)
{
	unsigned long load_delta, *p;
	unsigned long pgtable_flags;
	pgdval_t *pgd;
	p4dval_t *p4d;
	pudval_t *pud;
	pmdval_t *pmd, pmd_entry;
	pteval_t *mask_ptr;
	bool la57;
	int i;
	unsigned int *next_pgt_ptr;

	la57 = check_la57_support(physaddr);

	/* Is the address too large? */
	if (physaddr >> MAX_PHYSMEM_BITS)
		for (;;);

	/*
	 * Compute the delta between the address I am compiled to run at
	 * and the address I am actually running at.
	 */
	load_delta = physaddr - (unsigned long)(_text - __START_KERNEL_map);

	/* Is the address not 2M aligned? */
	if (load_delta & ~PMD_PAGE_MASK)
		for (;;);

	/* Include the SME encryption mask in the fixup value */
	load_delta += sme_get_me_mask();

	/* Fixup the physical addresses in the page table */

	pgd = fixup_pointer(&early_top_pgt, physaddr);
	p = pgd + pgd_index(__START_KERNEL_map);
	if (la57)
		*p = (unsigned long)level4_kernel_pgt;
	else
		*p = (unsigned long)level3_kernel_pgt;
	*p += _PAGE_TABLE_NOENC - __START_KERNEL_map + load_delta;

	if (la57) {
		p4d = fixup_pointer(&level4_kernel_pgt, physaddr);
		p4d[511] += load_delta;
	}

	pud = fixup_pointer(&level3_kernel_pgt, physaddr);
	pud[510] += load_delta;
	pud[511] += load_delta;

	pmd = fixup_pointer(level2_fixmap_pgt, physaddr);
	for (i = FIXMAP_PMD_TOP; i > FIXMAP_PMD_TOP - FIXMAP_PMD_NUM; i--)
		pmd[i] += load_delta;

	next_pgt_ptr = fixup_pointer(&next_early_pgt, physaddr);
	pud = fixup_pointer(early_dynamic_pgts[(*next_pgt_ptr)++], physaddr);
	pmd = fixup_pointer(early_dynamic_pgts[(*next_pgt_ptr)++], physaddr);

	pgtable_flags = _KERNPG_TABLE_NOENC + sme_get_me_mask();

	if (la57) {
		p4d = fixup_pointer(early_dynamic_pgts[(*next_pgt_ptr)++],
				    physaddr);

		i = (physaddr >> PGDIR_SHIFT) % PTRS_PER_PGD;
		pgd[i + 0] = (pgdval_t)p4d + pgtable_flags;
		pgd[i + 1] = (pgdval_t)p4d + pgtable_flags;

		i = physaddr >> P4D_SHIFT;
		p4d[(i + 0) % PTRS_PER_P4D] = (pgdval_t)pud + pgtable_flags;
		p4d[(i + 1) % PTRS_PER_P4D] = (pgdval_t)pud + pgtable_flags;
	} else {
		i = (physaddr >> PGDIR_SHIFT) % PTRS_PER_PGD;
		pgd[i + 0] = (pgdval_t)pud + pgtable_flags;
		pgd[i + 1] = (pgdval_t)pud + pgtable_flags;
	}

	i = physaddr >> PUD_SHIFT;
	pud[(i + 0) % PTRS_PER_PUD] = (pudval_t)pmd + pgtable_flags;
	pud[(i + 1) % PTRS_PER_PUD] = (pudval_t)pmd + pgtable_flags;

	pmd_entry = __PAGE_KERNEL_LARGE_EXEC & ~_PAGE_GLOBAL;
	/* Filter out unsupported __PAGE_KERNEL_* bits: */
	mask_ptr = fixup_pointer(&__supported_pte_mask, physaddr);
	pmd_entry &= *mask_ptr;
	pmd_entry += sme_get_me_mask();
	pmd_entry +=  physaddr;

	for (i = 0; i < DIV_ROUND_UP(_end - _text, PMD_SIZE); i++) {
		int idx = i + (physaddr >> PMD_SHIFT);

		pmd[idx % PTRS_PER_PMD] = pmd_entry + i * PMD_SIZE;
	}

	pmd = fixup_pointer(level2_kernel_pgt, physaddr);

	/* invalidate pages before the kernel image */
	for (i = 0; i < pmd_index((unsigned long)_text); i++)
		pmd[i] &= ~_PAGE_PRESENT;

	/* fixup pages that are part of the kernel image */
	for (; i <= pmd_index((unsigned long)_end); i++)
		if (pmd[i] & _PAGE_PRESENT)
			pmd[i] += load_delta;

	/* invalidate pages after the kernel image */
	for (; i < PTRS_PER_PMD; i++)
		pmd[i] &= ~_PAGE_PRESENT;

	*fixup_long(&phys_base, physaddr) += load_delta - sme_get_me_mask();

	return sme_postprocess_startup(bp, pmd);
}
```

### 获取页表物理地址

将页表物理地址基址加到 rax 中，从而获得内核代码在物理内存中的地址，因为现在还处于实模式

```text
addq	phys_base(%rip), %rax
```

### 校验C位

C位为EDX寄存器第三十位，也称为CPUID寄存器中的“bit 30”，用于SEV技术，防止C位被篡改而执行ROP攻击。

### 切换新的页表

上面获取了页表的物理地址放在了[rax寄存器](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=rax寄存器&zhida_source=entity)中。

```text
pushq	%rsi
	movq	%rax, %rdi
	call	sev_verify_cbit
	popq	%rsi
```

### 刷新TLB

更新页表以后也需要将TLB中的缓存刷新，因此重置CR3寄存器的PGE位关闭分页，后再重新开启分页达到刷新TLB的目的

```text
movq	%cr4, %rcx
	movq	%rcx, %rax
	xorq	$X86_CR4_PGE, %rcx
	movq	%rcx, %cr4
	movq	%rax, %cr4
```

### 加载全局描述符表，段寄存器置零

加载全局描述符表，ds、ss、es、fs、gs都置为0。

```text
lgdt	early_gdt_descr(%rip)
	/* set up data segments */
	xorl %eax,%eax //eax置为0
	movl %eax,%ds
	movl %eax,%ss
	movl %eax,%es
    movl %eax,%fs
	movl %eax,%gs
```

### 更新GS

MSR_GS_BASE是一个用于x86架构的IA32_MSR_GS_BASE的控制寄存器，用于存储当前进程的TLS（线程本地存储）指针。在64位操作系统中，由于线程的TLS指针可以使用FS和GS寄存器来访问，因此MSR_GS_BASE寄存器的值就是指向GS寄存器的值，用于访问进程的TLS存储区。通过movlinitial_gs(%rip),%eax 和movlinitial_gs+4(%rip),%edx分别存储initial_gs存储的地址高32位和低32位。通过wrmsr指令将eax和edx存储的initial_gs所指向的地址写入到MSR_GS_BASE所指向的寄存器中。

```text
        movl	$MSR_GS_BASE,%ecx
	movl	initial_gs(%rip),%eax
	movl	initial_gs+4(%rip),%edx
	wrmsr
```

### 更新栈

将initial_stack的地址更新到rsp中

```text
movq initial_stack(%rip), %rsp
```

### 更新[全局中断](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=全局中断&zhida_source=entity)表IDT

调用early_setup_idt函数更新全局中段表

```text
    pushq	%rsi
	call	early_setup_idt
	popq	%rsi
```

### early_setup_idt

如果系统启用了AMD内存加密，则会调用setup_ghcb函数设置GHCB，并为虚拟化异常设置中断处理程序。然后将初始化阶段的中断描述表的地址赋给描述符。最后，调用native_load_idt函数来加载新的IDT。

```text
void early_setup_idt(void)
{
	/* VMM Communication Exception */
	if (IS_ENABLED(CONFIG_AMD_MEM_ENCRYPT)) {
		setup_ghcb();
		set_bringup_idt_handler(bringup_idt_table, X86_TRAP_VC, vc_boot_ghcb);
	}

	bringup_idt_descr.address = (unsigned long)bringup_idt_table;
	native_load_idt(&bringup_idt_descr);
}
```

### 获取cpu信息

通过**cpuid**指令获取CPU的一些特性信息，并将EDX寄存器的内容保存到EDI寄存器中

```text
  movl	$0x80000001, %eax
	cpuid
	movl	%edx,%edi
```

### 读取EFER寄存器

通过rdmsr指令读取EFER（Extended Feature Enable Register）的值

```text
 movl	$MSR_EFER, %ecx
	rdmsr
```

### 设置EFER寄存器

将读取到的EFER值保存到EDX寄存器中。通过位操作使EFER的SCE位设置为1，并根据CPU是否支持NX位来设置EFER的NX位。如果需要对EFER进行了修改，则将修改后的值通过wrmsr指令写入EFER中。

```text
movl    %eax, %edx
	btsl	$_EFER_SCE, %eax	/* Enable System Call */
	btl	$20,%edi		/* No Execute supported? */
	jnc     1f
	btsl	$_EFER_NX, %eax
	btsq	$_PAGE_BIT_NX,early_pmd_flags(%rip)
1:	cmpl	%edx, %eax
	je	1f
	xor	%edx, %edx
	wrmsr	
```

### 设置CR0寄存器

设置CR0寄存器，该寄存器是控制处理器的模式（保护模式或实模式）和各种特性（如分页和写保护）的关键寄存器。

```text
/* Setup cr0 */
	movl	$CR0_STATE, %eax
	/* Make changes effective */
	movq	%rax, %cr0
```

### 清空EFLAGS寄存器

将数字0推送到栈上，然后通过popfq指令弹出该数字并写入EFLAGS寄存器中。这将导致EFLAGS寄存器中的所有位都被设置为0，从而清除它之前存储的任何标志信息。

```text
    pushq $0
	popfq
```

### 设置参数

此时的rsi 寄存器是指向实模式结构体的指针，该结构体保存了一些与实模式启动有关的参数，例如 BIOS 数据区地址、命令行参数等。在这里，将 rsi 寄存器中保存的实模式结构体的指针保存到 rdi 寄存器中，以便在后续的 C 代码中使用。

```text
movq	%rsi, %rdi
```

### 跳转到C函数

将返回地址 Lafter_lret 压入栈中以便后续恢复，然后清除帧指针 ebp，接着将代码地址 initial_code 加载到 rax 中，然后将 __KERNEL_CS 和 rax 分别压入栈中，最后使用 lretq 跳转到 x86_64_start_kernel 函数。

```text
   pushq	$.Lafter_lret		
    xorl	%ebp, %ebp		movq	initial_code(%rip), %rax
	pushq	$__KERNEL_CS	
	pushq	%rax		
	lretq
```

### initial_code

initial_code 被定义为一个四字节的地址，其内容为 x86_64_start_kernel 符号的地址，而 x86_64_start_kernel 是一个函数，代表着内核的入口点。

```text
SYM_DATA(initial_code,	.quad x86_64_start_kernel)
```

### x86_64_start_kernel

1. 进行内核镜像和模块内存区域映射的构建时检查。
2. 初始化CR4寄存器的值，并进行Shadow页表的初始化。
3. 重置早期页表以清除内存映射关系。
4. 清零BSS段。
5. 执行SME的初始化。
6. 执行KASan的初始化。
7. 刷新全局TLB缓存中的旧数据。
8. 设置IDT早期处理程序。
9. 初始化TDX相关的数据结构。
10. 复制启动参数。
11. 加载处理器的微码。
12. 设置内核的高端内存映射。

```text
asmlinkage __visible void __init x86_64_start_kernel(char * real_mode_data)
{
	/*
	 * BUILD_BUG_ON函数用于编译期间的静态检查，用于确保 __START_KERNEL_map 映射到的地址和模块的映射区域没有重叠，并且模块镜像和内核镜像大小之和不超过两个页目录项（2*PUD_SIZE）的大小。另外，还检查了 __START_KERNEL_map 和 MODULES_VADDR 的对齐情况，以及 MODULES_END 是否落在 PGDIR 的边界上
	 */
	BUILD_BUG_ON(MODULES_VADDR < __START_KERNEL_map);
	BUILD_BUG_ON(MODULES_VADDR - __START_KERNEL_map < KERNEL_IMAGE_SIZE);
	BUILD_BUG_ON(MODULES_LEN + KERNEL_IMAGE_SIZE > 2*PUD_SIZE);
	BUILD_BUG_ON((__START_KERNEL_map & ~PMD_MASK) != 0);
	BUILD_BUG_ON((MODULES_VADDR & ~PMD_MASK) != 0);
	BUILD_BUG_ON(!(MODULES_VADDR > __START_KERNEL));
	MAYBE_BUILD_BUG_ON(!(((MODULES_END - 1) & PGDIR_MASK) ==
				(__START_KERNEL & PGDIR_MASK)));
	BUILD_BUG_ON(__fix_to_virt(__end_of_fixed_addresses) <= MODULES_END);

cr4_init_shadow();/*cr4_init_shadow 函数用于初始化内核页表。*/

	/*reset_early_page_tables 函数用于将早期的页表映射去掉，使内核空间从虚拟地址 0 开始。 */
	reset_early_page_tables();

/*clear_bss 函数用于清除内核 bss 段。*/
	clear_bss();

	/*
	 当运行在早期阶段的x86_64_start_kernel函数调用kasan_early_init函数时，它可能会分配一些内存并对其进行映射，这可能导致内存分配页面与已经映射的init_top_pgt页面重叠。如果init_top_pgt页面上有任何内容，则会覆盖新分配的页面，因此需要在kasan_early_init函数之前清除init_top_pgt页面。而clear_page函数用于将一个页面清零，这样在调用kasan_early_init之前，就能确保init_top_pgt页面上没有任何数据。
	 */
	clear_page(init_top_pgt);

	/*
	 sme_early_init 函数用于提前进行内存加密的初始化，为后续的内存访问提供支持
kasan_early_init 函数用于初始化内核地址的 KASan影子映射表，以便在运行时检测内核
	 */
	sme_early_init();

	kasan_early_init();

	/*
	 * __native_tlb_flush_global 函数用于刷新全局 TLB缓存，以避免 trampoline 页表的缓存残留导致的问题。
idt_setup_early_handler 函数用于设置中断处理程序，为异常、中断和系统调用提供支持。

	 */
	__native_tlb_flush_global(this_cpu_read(cpu_tlbstate.cr4));

	idt_setup_early_handler();

	/* tdx_early_init 函数用于提前进行 TDX的初始化，为后续的加密内存访问提供支持。
copy_bootdata 函数用于将真实模式下的 bootdata 拷贝到内核内存中。 */
	tdx_early_init();

	copy_bootdata(__va(real_mode_data));

	/*
	 * Load microcode early on BSP.
	 */
	load_ucode_bsp();

	/* load_ucode_bsp 函数用于在 BSP上加载微码。
    x86_64_start_reservations 函数用于初始化内核的内存管理，包括页表初始化、内存区域初始化、虚拟内存初始化、页框映射初始化等操作。
*/
	init_top_pgt[511] = early_top_pgt[511];

	x86_64_start_reservations(real_mode_data);
}
```

### x86_64_start_reservations

1. 检查 boot_params.hdr.version 是否为0。如果为0，则复制启动参数。否则，说明启动参数已经被复制。
2. 调用 x86_early_init_platform_quirks()，用于检查并修复平台的一些不规范行为。
3. 根据硬件子架类型调用相应的初始化函数。对于X86_SUBARCH_INTEL_MID子架，调用x86_intel_mid_early_setup()。
4. 最后调用 start_kernel() 函数，跳转到内核的入口处，启动 Linux 内核。

```text
void __init x86_64_start_reservations(char *real_mode_data)
{
	/* version is always not zero if it is copied */
	if (!boot_params.hdr.version)
		copy_bootdata(__va(real_mode_data));

	x86_early_init_platform_quirks();

	switch (boot_params.hdr.hardware_subarch) {
	case X86_SUBARCH_INTEL_MID:
		x86_intel_mid_early_setup();
		break;
	default:
		break;
	}
	start_kernel();
}
```

现在Linux初始化的准备工作已经完成。并正式跳转到start_kernel函数

## 系统初始化

### 0号进程

0号进程（init_task），这是唯一一个不是fork或者kernel_thread产生的进程。

init_task是Linux内核中的一个全局变量（下面的代码可以看见是有GCC申请了内存），它是在内核启动过程中动态完成初始化的。init_task在Linux内核中扮演着非常重要的角色，它是进程描述符（task_struct）的第一个实例，也是Linux内核进程的起点。当Linux内核启动时，它会首先创建一个进程描述符(init_task)，然后通过该进程描述符来启动第一个进程([init进程](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=init进程&zhida_source=entity))，即用户空间的第一个进程。因此，init_task可以被认为是整个Linux内核启动的起点。

在Linux内核中，init_task的定义在init/init_task.c文件中，它包含了task_struct结构体的所有成员变量的初始值，这些成员变量描述了进程的各种属性和状态，比如进程ID、进程状态、进程优先级、进程的父进程和子进程等等。在内核启动时，init_task被用作第一个进程(init进程)的进程描述符，并在init进程启动后被初始化为init进程的进程描述符。

### start_kernel

[https://elixir.bootlin.com/linux/v6.0-rc1/source/init/main.c](https://link.zhihu.com/?target=https%3A//elixir.bootlin.com/linux/v6.0-rc1/source/init/main.c)

当完成工作后，正式进入初始化化函数init/main.c中的start_kernel函数中。

### 设置栈底魔数

set_task_stack_end_magic(&init_task) 用于设置进程的内核栈底部的魔数，以便内核能够在调试时检测到栈溢出等问题。它会在 init_task 的内核栈的尾部设置一个特殊的标记值。这个标记值是用来检测内核栈是否溢出的。

内核栈是用来保存进程或线程执行期间的函数调用栈信息的。如果内核栈溢出，将会覆盖其他内存区域，导致不可预测的结果。为了避免内核栈溢出，内核会在内核栈的尾部设置一个特殊的标记值，当内核栈溢出时，这个标记值会被覆盖，从而触发一个内核错误。

### 设置CPU的ID

smp_setup_processor_id() 函数是用来设置处理器 ID 的。在 Linux 内核中，处理器 ID 是指每个 CPU 的唯一标识符。在多核系统中，不同的 CPU 需要有不同的处理器 ID，以便内核可以区分不同的 CPU。

### 初始化内核调试对象

debug_objects_early_init() 函数是用于在内核初始化早期阶段初始化内核对象调试代码的。它会在内核中启用一些调试功能，如对象的[引用计数](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=引用计数&zhida_source=entity)和对象的类型等。这个函数的作用是帮助内核开发人员在内核运行时及时检测内核对象的错误，提高内核的健壮性和可靠性。

该函数在内核初始化早期调用，初始化用于跟踪内核对象的调试机制，包括对象的类型，引用计数和对象名等。在这个阶段，内核中的其他调试机制还没有完全启动，因此，这个函数主要是为了帮助内核开发人员在内核启动早期发现内核对象的错误和问题

### 初始化内核信息

init_vmlinux_build_id() 函数用于初始化内核的版本号和编译时间等信息，以便在调试内核时能够方便地查看内核的版本和编译时间等信息。

### 初始化cgroup

cgroup_init_early() 函数用于初始化 Linux 控制组（cgroup）的一些数据结构，这个数据结构用于实现资源隔离和管理等功能。

### 关中断

local_irq_disable() 函数用于关闭本地中断，这个操作通常是为了保证内核在启动过程中的一些关键代码能够被顺利执行。

early_boot_irqs_disabled = true; 表示启动过程中的所有中断都已经被关闭，这个操作通常是为了确保内核在启动过程中的一些关键代码能够被顺利执行。

### 初始化CPU 信息

1. 初始化 cpu_data，包括各种 CPU 寄存器、寄存器地址和掩码等，以便内核可以在多个 CPU 之间正确地共享数据。
2. 初始化 APIC（Advanced Programmable Interrupt Controller）相关寄存器，包括寄存器的地址和掩码，以便内核可以正确地管理中断。
3. 保存启动 CPU 的信息（包括 CPU ID、CPU 类型、CPU 厂商等），以便内核在后续使用。

### 初始化虚拟地址和物理地址之间的映射关系。

page_address_init()函数初始化了内核用于查找物理页面地址的数据结构。（在Linux内核中，物理页面是一个非常基础的概念，用于描述物理内存中的一段固定大小的连续字节。在内核中，许多数据结构都是基于物理页面的）

为了更高效地访问物理页面，内核使用了一个称为Page框架的机制，这个机制提供了一个内核用于查找物理页面地址的数据结构。page_address_init()函数的任务就是初始化这个数据结构，使得内核能够更快速地访问物理页面。

该函数会在物理内存区域中分配一定数量的内存用于存储Page框架的数据结构，并对这些数据结构进行初始化。在初始化完成后，内核就能够使用Page框架来查找任何物理页面的地址。

### 打开内核代码页保护、随机化内核地址

early_security_init()主要工作

1. 设置内核代码段只读
2. 初始化内核页表，包括设置页保护位，开启 NX 位和 SMEP 位，从而防止[缓冲区溢出](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=缓冲区溢出&zhida_source=entity)、堆栈溢出等攻击
3. 启用 KASLR（内核地址空间随机化），将内核空间的代码和数据地址进行随机化，从而增加攻击者猜测内核代码和数据位置的难度

### 与体系结构相关的初始化

setup_arch(&command_line) 负责对体系结构进行初始化，以便内核在正确的硬件配置下运行。它的具体工作如下：

1. 根据体系结构的不同，调用不同的体系结构特定的初始化函数。例如，x86 架构会调用 x86_init() 函数。
2. 进行体系结构相关的设置，例如设置 CPU 缓存、TLB 等。
3. 初始化内存管理模块，将内核空间和用户空间的内存映射到不同的虚拟地址空间。
4. 初始化 DMA，为 I/O 设备和内存之间的数据传输提供支持。
5. 初始化时钟和定时器，为进程调度、时间戳等提供支持。
6. 初始化中断和异常处理，为系统调用、设备中断等提供支持。
7. 设置系统调用表、文件系统、网络等其他体系结构无关的部分。

setup_arch(&command_line) 负责初始化 Linux 内核的底层硬件和体系结构相关的部分，为后续的系统启动做好准备。

### 解析内核命令行

setup_command_line(command_line)函数 解析内核命令行。

### 设置 CPU 的数量

setup_nr_cpu_ids() 函数主要用于初始化 nr_cpu_ids 变量，该变量指示系统中逻辑处理器的数量。它会在系统启动时通过扫描硬件[拓扑结构](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=拓扑结构&zhida_source=entity)进行初始化，以便内核正确地识别和使用每个处理器。

该函数会调用 topology_physical_package_id() 函数，该函数通过查询处理器拓扑结构，获取物理处理器的数量。nr_cpu_ids 变量的值被设置为逻辑处理器数量和物理处理器数量的较大值。

在启动早期初始化完成之后，内核会根据 nr_cpu_ids 的值来为每个处理器分配内存、初始化调度器以及其他必要的数据结构。

### 为每个CPU分配 per-CPU 变量和栈空间

setup_per_cpu_areas() 函数主要是为每个 CPU 配置 per-cpu 区域，这个区域是专门为每个 CPU 保留的一块内存区域，它包含一些与 CPU 相关的数据结构，比如当前 CPU 的任务指针（current）、当前进程的进程控制块（current_thread_info()->task）等等。这个区域是用于高效地访问与当前 CPU 相关的数据，因为在多 CPU 系统中，各个 CPU 同时访问共享的内核数据结构是很常见的，如果不使用 per-cpu 区域，那么在访问这些数据结构时就需要加锁来保证同步，这样就会影响性能。

具体工作如下：

1. 根据 CPU 数量，为每个 CPU 分配一块 per-CPU 数据结构的内存空间。
2. 初始化每个 per-CPU 数据结构中的内存池。
3. 将每个 per-CPU 数据结构的指针存储到相应 CPU 的 gs 寄存器中，以便 CPU 在运行时能够快速访问它自己的 per-CPU 数据结构
4. setup_per_cpu_areas() 还会为每个 CPU 分配并设置 per-CPU 数据结构，例如 per-CPU 的内存分配器，用于在每个 CPU 上管理内存的对象池，以及其他与 CPU 相关的数据结构。
5. 最后，还会初始化一个叫做 x86_cpuinit 的全局变量，用于跟踪每个 CPU 的初始化状态。该变量是一个指向 cpuinfo_x86 结构的指针数组，其中每个元素表示一个 CPU 的信息。每个元素中的数据结构包含有关该 CPU 的硬件信息、性能计数器和其他有用的信息。

setup_per_cpu_areas() 函数执行完毕后，启动 CPU 将开始执行内核代码，每个 CPU 将开始执行其相应的初始化过程。

### 初始化启动引导 CPU 数据

smp_prepare_boot_cpu() 函数是在多处理器系统中准备启动引导CPU的函数。在多处理器系统中，需要初始化所有CPU的数据结构和参数。这个函数的主要任务是对引导处理器（boot CPU）进行初始化。

该函数主要完成以下工作：

1. 设置引导CPU的ID号。
2. 初始化一些全局变量，如 cpu_possible_map，cpu_online_map 和 cpu_present_map，这些变量用于描述系统中有哪些CPU。
3. 初始化当前CPU的本地数据结构。每个CPU有一些本地数据结构（如栈，GDT表），这些数据结构只能被当前CPU访问。smp_prepare_boot_cpu() 函数会为当前CPU初始化这些数据结构。
4. 初始化一些用于调试的变量和结构体，比如 FPU 寄存器、跟踪内存分配等。
5. 最后，该函数会调用 smp_store_cpu_info() 函数保存当前CPU的信息。

smp_prepare_boot_cpu() 函数主要是初始化启动引导 CPU 的数据结构，以及一些与当前 CPU 相关的数据结构和变量，为操作系统的运行做好准备。

### 启动 CPU 热插拔功能

boot_cpu_hotplug_init():函数启动 CPU 热插拔功能，这个功能让内核可以在运行时添加或移除 CPU。

### 构建内存区域列表

build_all_zonelists(NULL)会为所有 NUMA 节点构建并初始化内存节点的 zonelist，这些列表包含了物理内存的不同区域（例如DMA区域、普通区域、高端区域等）。

zomelist 是用于描述每个内存节点中各个内存区域的数据结构，用于存储内存块的各种属性信息，例如可用性、内存类型等。在多 NUMA 节点的系统中，每个节点都有自己的 zonelist，因此内核需要为每个节点构建适当的 zonelist，以便在后续的内存管理中使用。

build_all_zonelists 的参数为 NULL，表示使用系统当前配置的内存信息来构建 zonelist。在函数内部，它首先会计算出系统中有多少个 NUMA 节点，然后为每个节点构建对应的 zonelist。具体过程中，函数会根据可用内存的大小和物理地址等信息，将内存块分配到不同的内存区域（zone）中，然后在每个内存区域中构建内存块的链表，并计算好每个内存区域可用的页面数量，最终形成 zonelist。

构建好 zonelist 后，函数会将其存储在一个全局的变量 node_zonelists 中，以便在后续的内存分配和管理中使用。这个全局变量是一个数组，每个元素对应一个 NUMA 节点的 zonelist。

### 初始化页框分配器

page_alloc_init(): 初始化页框分配器，为内核的页框分配子系统建立框架。主要负责初始化物理页面分配器。它会在系统启动时调用，创建并初始化[伙伴系统](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=伙伴系统&zhida_source=entity)来管理物理页面的分配与释放，为操作系统提供可用的物理页面，确保在系统运行过程中能够满足进程、内核和设备驱动程序对物理页面的需求。

在该函数中，会调用 init_mmzone() 和 init_per_zone_wmark_min() 来初始化内存的[伙伴算法](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=伙伴算法&zhida_source=entity)，这是一个高效的内存分配算法，用于将物理页面划分为大小相等的块，以满足系统中各种不同大小的内存需求。接着，它会初始化全局内存描述符和内存管理数据结构，然后调用 bootmem_init() 函数，创建物理页面管理结构，将所有的物理页面组织到管理数据结构中。

在 page_alloc_init() 函数完成之后，内核就能够正常分配和使用系统的物理内存

### 初始化内核跳转标签功能

jump_label_init() 函数初始化内核跳转标签功能，用于优化代码执行。jump_label_init() 是在内核启动时初始化跳转标签（jump label）的函数。跳转标签是一种机制，用于在内核中进行代码替换而无需重启系统。跳转标签被用于在运行时替换内核代码的一些关键部分，如一些函数的代码实现，以便在不需要重启系统的情况下应用更新或更改。这个机制的实现基于 GCC 的 __builtin_static_cpu_has() 和 __builtin_static_branch() 等内置函数，它们将在编译时处理静态跳转表，使得运行时进行代码替换更加高效。 jump_label_init() 的主要工作是初始化跳转标签的相关数据结构，以便在内核运行时进行动态跳转表的创建和更新。

### 解析指定内核启动参数

parse_early_param() 函数是 Linux 内核中的一个早期初始化函数，其主要作用是解析在内核启动参数中指定的早期参数。

在 Linux 内核启动时，会接收到一些启动参数，如 root 设备、内存大小等。在这些启动参数之前，可能还会有一些其他的启动参数，这些参数是由 boot loader（如 GRUB）在内核启动前解析并传递给内核的。

parse_early_param() 函数的主要工作就是解析这些早期参数。这些参数可以用来控制内核的一些行为，如调试、调整内存分配策略等。

parse_early_param() 函数会遍历所有的早期参数，找到与内核参数匹配的参数，并将其值保存下来。在之后的内核初始化过程中，内核会使用这些参数来决定其行为。

### 解析内核启动参数

parse_args() 函数是用于解析内核启动参数的函数，具体完成以下工作：

1. 解析内核启动参数，并将解析后的结果存储在全局变量 boot_option 中。
2. 将解析后的内核启动参数打印到控制台，以便在内核启动时查看。
3. 如果内核启动参数中包含 debug 参数，则启用内核的调试模式。
4. 如果内核启动参数中包含 earlyprintk 参数，则启用内核的早期打印功能，这样可以在内核启动时将调试信息输出到串口等设备。

parse_args() 函数是内核启动时重要的参数解析函数，它能够解析启动参数并对内核进行相应的设置，从而为内核的后续操作打下基础。

### 打印未知的内核启动参数

print_unknown_bootoptions()用于将内核命令行中未知的启动选项打印到控制台，以便于开发人员调试。

当内核命令行中包含未知的启动选项时，该函数会将这些选项打印到控制台上，以便用户或开发人员知道哪些选项未被识别。在内核解析命令行参数时，如果发现无法识别的选项，则会调用这个函数。

### 设置用于记录内核日志的缓冲区

setup_log_buf() 函数用于设置用于记录内核日志的缓冲区。用于记录内核日志的缓冲区地址及大小设置为 log_buf 和 log_buf_len 变量所指定的值。在内核启动早期调用为了确保内核日志系统能够在后续的内核运行中正常工作。

### 初始化文件系统缓存

vfs_caches_init_early() 函数的作用是初始化文件系统缓存。函数会创建用于缓存文件系统对象的高速缓存，以提高文件系统访问的效率。它还会设置缓存的参数和策略，以及执行其他与文件系统缓存相关的初始化操作。由于此函数是在内核启动的早期阶段调用的，因此它还需要注意一些特定的限制和要求，以确保它能够正确地工作并且不会影响到其他关键的系统组件。

### 内核异常处理表排序

sort_main_extable() - 对内核异常处理表进行排序。sort_main_extable() 是一个用于内核异常处理的函数，在内核启动时被调用。它的主要工作是对内核异常处理表进行排序，使得异常处理程序能够按照正确的顺序被调用。这对于确保内核异常处理机制的正确性和稳定性非常重要。

### 初始化中断处理程序

trap_init() 是一个用于初始化中断处理程序的函数，其具体工作如下：

1. 初始化IDT（Interrupt Descriptor Table）：IDT 是一个中断描述符表，它记录了每种中断类型的处理程序的地址。trap_init() 函数通过调用 idt_init() 函数初始化 IDT 表，为每种中断类型的处理程序指定一个地址。
2. 设置中断处理程序：trap_init() 函数通过调用 set_trap_gate()、set_system_gate()、set_system_intr_gate() 函数为每种中断类型设置中断处理程序。
3. 初始化系统调用：trap_init() 函数还通过调用 system_call_init() 函数初始化系统调用，它把系统调用的中断类型和对应的处理程序进行了绑定。
4. 初始化CPU本地中断处理器：对于SMP系统，每个CPU都有一个本地中断处理器，trap_init()函数通过调用 init_bsp_APIC() 或 init_nonboot_cpu_APIC() 函数初始化本地中断处理器。

trap_init() 函数完成了操作系统中断处理的初始化工作，为后续的中断处理打下了基础。

### 初始化内存管理子系统

mm_init()它的作用是初始化内存管理子系统。

在该函数中，会初始化内核的物理内存管理、虚拟内存管理、内存分配器等子系统，包括初始化页面描述符、设置物理内存映射、设置内核堆栈和页表等。

在初始化过程中，该函数还会调用 zone_init() 函数对系统的内存区域进行初始化，包括建立伙伴系统和伙伴链表，并且将可用的内存区域划分成若干个内存区域（zone），为内存分配器提供基础。

mm_init() 函数的主要作用是初始化内存管理子系统，为后续的内存管理操作提供基础支持。

### 初始化函数跟踪功能

ftrace_init()的作用是初始化内核的函数跟踪器，也就是 Ftrace。

Ftrace 是 Linux 内核自带的一个轻量级的函数跟踪器，可以用来跟踪内核函数的执行情况和性能瓶颈，是内核性能调优和分析的有力工具。ftrace_init() 函数会初始化 ftrace 的核心数据结构，以及注册 ftrace 相关的文件系统操作等。具体而言，它会做以下工作：

1. 初始化 ftrace 的核心数据结构，包括 ftrace 的跟踪缓冲区、跟踪器控制器等。
2. 注册 ftrace 相关的文件系统操作，以便用户空间程序可以访问和控制 ftrace，例如通过 /sys/kernel/debug/tracing 目录访问跟踪信息和控制跟踪器。
3. 注册 ftrace 相关的系统调用，使用户空间程序可以通过系统调用来控制 ftrace 的行为，例如启动和停止跟踪等。
4. 注册一些 ftrace 的默认事件，例如函数进入和退出事件，以便用户可以方便地开始跟踪函数执行情况。
5. 注册 ftrace 的[钩子函数](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=钩子函数&zhida_source=entity)，使得内核中的其他模块和子系统可以通过钩子函数来使用 ftrace，例如注册自己的跟踪事件。

ftrace_init() 的作用是初始化 Linux 内核的函数跟踪器，并为用户空间程序和内核模块提供访问和控制 ftrace 的接口。

### 初始化跟踪日志

early_trace_init()初始化跟踪日志。early_trace_init() 函数是 Linux 内核初始化过程中的一个早期阶段，在此阶段会设置与跟踪相关的参数，准备好跟踪系统调用的基本设施。具体来说，该函数会初始化 ftrace，即跟踪框架，为后续的跟踪操作提供基本支持。在这个阶段，仅仅是初始化和设置相关参数，而真正的跟踪操作会在更晚的阶段进行。

### 初始化进程调度器

sched_init() 函数用于系统调度器的初始化，具体完成以下工作：

1. 初始化调度器数据结构，包括进程链表、就绪队列、[时间片](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=时间片&zhida_source=entity)等；
2. 初始化进程 0 和当前进程，进程 0 是系统启动时的第一个进程，当前进程是系统调度器当前正在调度的进程；
3. 初始化定时器，用于定时更新进程的状态和时间片等；
4. 初始化 CPU [上下文切换](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=上下文切换&zhida_source=entity)函数指针；
5. 设置系统调度器的时间片长度；
6. 注册进程调度器的操作函数，包括创建、删除、挂起、恢复进程等。

sched_init() 函数是 Linux 内核中非常重要的初始化函数，它为后续的进程调度和管理工作打下了基础。

### 初始化 radix 树

radix_tree_init() 是 Linux 内核中的一个函数，用于初始化 radix 树。具体完成以下工作：

1. 为 radix 树的根节点分配内存空间，并初始化根节点；
2. 初始化 radix 树的高度限制；
3. 设置 radix 树的节点大小，根据节点大小的不同，选择相应的操作函数；
4. 初始化 radix 树的相关操作函数。

初始化完成后，就可以在 Linux 内核中使用 radix 树结构了。radix 树是一种基于前缀匹配的树形数据结构，常用于 Linux 内核中的进程调度、网络协议栈等模块中。

### 初始化系统垃圾清理模块

housekeeping_init()函数用于初始化系统垃圾清理模块，该模块用于周期性地清理内核中的垃圾数据。该函数主要完成以下工作：

1. 初始化系统垃圾清理模块的定时器，定时器用于在一定时间间隔后启动垃圾数据清理功能。
2. 初始化系统垃圾清理模块的内存池，内存池用于分配和释放内存，用于存储需要清理的垃圾数据。
3. 注册系统垃圾清理模块的回调函数，该回调函数将在定时器到期时被调用，用于清理内核中的垃圾数据。

通过初始化垃圾清理模块，系统可以周期性地清理内核中的垃圾数据，从而提高系统性能和稳定性。

### 初始化内核工作队列

workqueue_init_early()初始化内核工作队列，用于处理异步任务。它用于在内核启动早期初始化工作队列子系统。具体而言，该函数会初始化一个名为system_wq的工作队列，该队列用于执行系统中与延迟处理相关的任务。初始化工作包括对该队列的头节点进行初始化以及设置队列的相关属性。通过初始化工作队列，系统可以在内核启动后尽早开始调度工作，并且可以确保工作队列子系统在其他子系统使用之前已经初始化完毕。

### 初始化RCU机制

rcu_init() 函数的主要作用是初始化Linux内核的 RCU(Read-Copy-Update)子系统。RCU是一种用于多核系统的同步机制，它允许并发访问共享数据结构，而不会造成死锁或争用。这个函数会初始化 RCU 系统的各个组件，包括rcu_ctrlblk、rcu_state等，以及调用rcu_init_percpu()来为每个CPU核分配 RCU 状态数据结构。这样在多CPU环境下，每个CPU核就有一个专用的 RCU 状态数据结构，避免了多核之间的竞争和冲突。

RCU 子系统在内核中扮演着重要的角色，因为很多内核子系统和模块都会依赖 RCU 来实现高效的并发同步。因此，RCU 初始化的正确性和稳定性对于整个系统的稳定性和性能是至关重要的。

### 初始化跟踪系统

trace_init()函数初始化跟踪系统，用于记录内核事件。trace_init()是Linux内核中的一个函数，其主要作用是初始化内核跟踪系统，以允许内核和用户空间跟踪功能的使用。

该函数主要完成以下任务：

1. 为内核跟踪子系统创建并初始化跟踪缓冲区。
2. 初始化跟踪事件处理程序和跟踪控制器。
3. 为跟踪子系统创建并初始化跟踪钩子。
4. 将内核跟踪子系统的回调函数注册到相应的内核事件中。
5. 最后，使内核跟踪系统处于活动状态，以允许内核和用户空间的跟踪工具进行跟踪数据收集。

### 初始化期间启用 initcall 调试

initcall_debug_enable()用于在内核初始化期间启用 initcall 调试。在 Linux 内核中，initcall 是一种机制，用于按照特定的顺序自动执行模块的初始化和清除函数。这个函数会将内核的 initcall_debug 标志设置为 true，以便在内核启动期间打印出 initcall 的调用顺序，以便调试和分析内核初始化的过程。这样做可以帮助内核开发人员更好地理解内核的初始化顺序，并且在出现问题时可以更方便地定位和解决问题。

### 初始化和设置[进程上下文](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=进程上下文&zhida_source=entity)追踪（CPT）

context_tracking_init()函数的主要作用是在内核中初始化和设置进程上下文追踪（CPT）功能，用于记录进程的上下文切换。进程上下文追踪是一种跟踪进程状态和行为的技术，它可以记录进程的上下文切换、调度信息、系统调用等。通过这种方式，可以更好地理解进程在系统中的行为和性能瓶颈。在具体实现上，context_tracking_init()会初始化内核的跟踪数据结构，并为CPU注册一些跟踪事件，用于在进程状态发生变化时记录相关信息。同时，该函数还会设置一些标志位，用于控制进程追踪功能的开启和关闭。

### 初始化中断处理器

early_irq_init()主要作用初始化中断处理器，主要完成以下工作：

1. 对[中断控制器](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=中断控制器&zhida_source=entity)进行初始化；
2. 为各个处理器启用中断（包括 I/O 中断和 CPU 异常中断）；
3. 注册默认的中断处理函数。

early_irq_init() 的作用是在内核启动过程中初始化中断子系统，以确保内核能够正确地响应各种中断请求。

### 初始化IRQ处理器

init_IRQ() - 初始化IRQ处理器，用于初始化中断子系统。

具体来说，init_IRQ() 函数会做以下工作：

1. 它会调用 init_ISA_irqs() 函数来初始化 ISA 总线上的中断。ISA 总线是一个旧的总线标准，它的[中断机制](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=中断机制&zhida_source=entity)与现代总线不同，需要特殊处理。
2. 接着，init_IRQ() 会调用 init_IRQ_proc() 函数，该函数会在 /proc 文件系统中创建一个名为 interrupts 的文件，用于记录系统中断的统计信息。
3. init_IRQ() 还会调用 irqchip_init() 函数，该函数用于初始化中断控制器硬件，并注册对应的中断处理函数。
4. 最后，init_IRQ() 会调用 init_IRQ_default_affinity() 函数，该函数用于设置中断处理程序的亲和性，以便将其绑定到特定的 CPU 上。

通过这些工作，init_IRQ() 函数完成了中断子系统的初始化。

### 初始化内核时钟

tick_init() 主要完成了系统时钟的初始化，它会初始化 tick 定时器并注册一个钩子函数来每个系统 tick 调用此函数，以便更新系统的时间状态。tick_init() 会使用 TSC（时间戳计数器）或 ACPI 定时器等，具体取决于处理器的支持情况。tick_init() 还会初始化时钟事件设备和 NMI watchdog，最后启动 CPU 时间轮询器。这些初始化工作都是为了确保系统能够正确地计算时间并进行调度。

### 初始化RCU机制的节能模式

rcu_init_nohz() 是一个 RCU（Read-Copy-Update）初始化的函数。RCU是一种无锁的同步机制，允许在不加锁的情况下实现并发访问共享数据结构。

具体而言，rcu_init_nohz() 函数的作用是初始化RCU的静态变量，并配置 RCU 定时器以实现无中断（nohz）的操作。在这种操作下，系统中断被抑制了一段时间，允许CPU在无中断的情况下执行一些工作。

这个函数还会设置 RCU 计时器，用于定期触发 RCU 的回收过程，以及调用

rcu_init_nohz_kthreads() 函数，创建与 RCU 无关的内核线程，以帮助完成 RCU 中需要的一些任务。这些任务包括延迟回收 RCU 数据结构、检查 RCU 中挂起的工作等。

### 初始化内核定时器

init_timers()函数用于系统时钟的初始化，具体完成以下工作：

1. 初始化系统定时器子系统，包括设置定时器管理结构体（timer_list）数组的内存池、计数器和[时钟源](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=时钟源&zhida_source=entity)等；
2. 初始化 per-CPU 定时器向量，使用了一个名为“tick_setup_percpu_timer()”的函数，并通过“tick_install_broadcast_device()”在所有 CPU 上安装了定时器广播设备；
3. 配置 timer wheel 数组，以及建立了所有 CPU 的 timer interrupt 的中断处理函数；
4. 完成后会设置系统全局定时器链表（sys_timer_list）的头指针为空，用于存储所有定时器的时间队列。

### 初始化SRCU机制

srcu_init() 是用于初始化 SRCU（Synchronization-RCU） 子系统的函数。SRCU是RCU机制的扩展，它提供了一种延迟释放机制，用于在使用并发数据结构时更好地控制内存回收。

具体来说，srcu_init() 函数的主要工作是初始化 SRCU 子系统中的变量和数据结构，例如创建并初始化了 SRCU 数据结构、保留了 CPU 核心数量信息、初始化了 SRCU 回调机制，以及为它们分配内存等。它还注册了 SRCU 的 /proc 文件系统接口，使得用户可以在系统运行时查询 SRCU 状态。

在这些工作完成后，SRCU 子系统就可以被使用，以提供高效的内存回收支持，以及优化并发数据结构的性能。

### 初始化高精度定时器

hrtimers_init()函数是用于初始化高精度定时器（High Resolution Timers）子系统的函数。具体来说，它会执行以下工作：

1. 初始化定时器子系统中使用的时间轮（time wheel）数组和链表，以及其他必要的数据结构。
2. 注册定时器子系统所需要的回调函数，例如在系统时钟中断处理程序中调度定时器的函数。
3. 启用高精度定时器子系统的内核参数和功能，例如 CONFIG_HIGH_RES_TIMERS 配置项和 NO_HZ_FULL 配置项。

hrtimers_init()函数的主要任务是为高精度定时器子系统做必要的初始化，使得内核可以正常使用和调度这个功能强大的子系统。

### 初始化[软中断](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=软中断&zhida_source=entity)机制

softirq_init() 的主要作用是初始化软中断（SoftIRQ）机制。软中断是一种在内核中运行的任务，它们通常是由一些异步事件触发的，例如网络数据包的到达、块设备的 I/O 完成等。软中断通过中断号来标识自己，并使用一个基于优先级的队列来维护。每个 CPU 都有自己的软中断队列，并使用全局的软中断数组来存储所有软中断的信息。

softirq_init() 的具体实现主要包括以下几个方面：

1. 初始化软中断的相关数据结构，包括全局的软中断数组、软中断的优先级、中断处理函数等。
2. 注册软中断处理函数，将软中断处理函数注册到内核的软中断向量表中。这样，当相应的软中断被触发时，内核就能够正确地分派对应的处理函数。
3. 初始化每个 CPU 的软中断控制块，包括软中断掩码、软中断计数器等。
4. 最后，启用软中断机制，允许软中断在内核中执行。

软中断机制是 Linux 内核中重要的事件处理机制，softirq_init() 函数的作用是初始化软中断机制，为软中断的正常处理打下基础。

### 初始化内核时间子系统

timekeeping_init()初始化内核时间子系统。负责初始化时间相关的模块，它首先初始化一个基准时钟，然后初始化各种定时器（如周期定时器，即tickless系统中的NoHZ模块），为时间相关的事件提供一个时间源，并初始化系统的时间戳计数器，以便系统能够记录事件发生的时间。此外，timekeeping_init()还会启动一些内核线程，如kthread_timekeeping，它们用于更新时间戳计数器。总之，timekeeping_init()函数是Linux内核时间管理的基础，为系统提供准确的时间服务。

### 初始化内核随机数生成器

random_init() 函数主要完成了 Linux 内核中的[伪随机数生成器](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=伪随机数生成器&zhida_source=entity)的初始化。

在 Linux 内核中，有一个随机数池，包含了许多熵数据源的输入。这些输入数据源包括硬件的中断，磁盘 I/O 操作，网络数据包的到达和离开等等。random_init() 函数负责对这个随机数池进行初始化，将其中的数据清空，并开始收集新的熵数据。

为了保证内核的随机数生成质量，需要在随机数池中保持足够的熵。这需要随机数生成器不断地收集来自熵源的新数据。在 random_init() 函数中，会使用一些硬件计时器等作为熵源，生成初始的熵数据。之后，内核中的其他子系统和驱动程序可以继续向随机数池中贡献更多的熵数据，以保证随机数的生成质量。

随机数生成器在内核中有着广泛的应用，例如在网络协议中使用随机数来生成初始序列号，以及在密码学中使用随机数生成密钥和向量等。因此，random_init() 函数的正确初始化对于内核的安全性和可靠性是非常重要的。

### 初始化堆栈 canary

boot_init_stack_canary() 是用于初始化堆栈 canary（堆栈金丝雀）的函数。堆栈 canary 是一种用于检测堆栈缓冲区溢出的安全机制，它的原理是在栈帧中插入一个随机数值，当函数返回时会检查该数值是否被修改，如果被修改则说明发生了缓冲区溢出，从而触发错误处理机制。boot_init_stack_canary() 函数在 Linux 内核启动过程中调用，用于为堆栈 canary 初始化一个随机数值，以增加堆栈 canary 的随机性。

### 初始化性能事件子系统

perf_event_init() 函数是 Linux 内核初始化性能事件子系统的入口函数。它主要完成以下几个任务：

1. 为系统提供性能事件支持所需的相关数据结构和全局变量的初始化。
2. 基于系统的硬件架构和内核配置选项，配置系统的性能计数器、调度器和中断等相关子系统，以满足性能事件采集和度量的要求。
3. 启用性能事件子系统，并将其集成到内核中，从而为用户空间提供性能事件的接口和功能。

性能事件子系统的主要作用是支持系统的性能调优和优化。它提供了一个接口，让用户程序能够监控指定的软件或硬件事件，例如 CPU 指令执行数、缓存命中率、内存访问次数等等，以便于用户能够对程序进行性能分析和优化。perf_event_init() 函数在 Linux 内核初始化过程中扮演了至关重要的角色，确保了性能事件子系统的正确启动和初始化。

### 初始化性能分析机制

profile_init()初始化性能分析机制。主要用于初始化Linux系统的分析性能计数器功能

（profiling），即系统的代码分析功能。它主要做了如下几件事情：

1. 为perf子系统注册初始化处理程序（perf_events_init），perf子系统是Linux内核性能分析的核心部分，profile_init()通过注册初始化处理程序来启用perf子系统。
2. 初始化和注册perf子系统的模块（perf_event_mod_init和perf_event_mod_exit），模块提供了实现代码分析的接口。
3. 初始化Linux内核中的性能计数器（performance counter），包括内核自身的计数器和可编程的硬件性能计数器（PMC）。
4. 初始化Linux内核中的代码分析功能（profiling），通过设置内核的函数跳转表（ftrace）来实现代码分析功能。

profile_init()主要是为Linux系统提供性能分析功能，为性能优化提供数据支持。

### 初始化跨CPU调用机制

call_function_init() - 初始化跨CPU调用机制。用于初始化调用CPU之间函数的机制。

在多CPU的系统中，内核中可能需要在一个CPU上执行某些函数。当一个CPU调用另一个CPU执行某些函数时，就需要使用一个机制来在不同CPU之间进行通信。call_function_init() 函数就是用来初始化这种机制的。

具体来说，call_function_init() 函数会初始化一个软件中断，用于将函数调用请求发送到其他CPU。初始化过程包括创建一个软中断，并将软中断处理函数设置为 smp_call_function_interrupt()。这个函数会对请求进行处理，并调用需要执行的函数。

在初始化完成后，其他内核组件可以使用 smp_call_function() 函数调用其他CPU上的函数，smp_call_function() 函数会将函数调用请求发送到其他CPU的软中断队列中，并唤醒目标CPU的内核线程，以便执行请求的函数。

因此，call_function_init() 函数对于多CPU的系统中，实现内核函数调用的机制非常重要。

### 初始化内核锁机制

lockdep_init()负责初始化内核锁机制，主要完成以下任务：

1. 初始化内核的锁依赖检测机制，包括分配和初始化相关的数据结构、参数等；
2. 注册系统调用 debug_locks，可以用来打印系统中存在的锁；
3. 注册内核机制 notifier_call_chain，它允许用户为内核某个事件注册回调函数，lockdep 在某些场景下可以使用该机制来通知调试器发生了锁相关的事件；
4. 如果开启了 CONFIG_LOCKDEP_CACHING 配置选项，那么 lockdep_init() 还会尝试在缓存中恢复锁依赖关系的历史记录。

总之，lockdep_init() 函数在系统初始化阶段设置好了内核锁依赖检测机制，并且可以方便地被其他模块调用和使用。

### 内核锁机制的自检

locking_selftest() 函数是一个内核自检函数，用于检测锁的正确性和性能。该函数会运行多个子测试用例，分别测试多个锁的实现和行为，包括自旋锁、[读写锁](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=读写锁&zhida_source=entity)、原子变量等。每个子测试都会执行一些锁相关操作，例如尝试获取锁、释放锁等，以检查锁的正确性和性能。在所有子测试完成后，该函数会输出测试结果，如果测试发现了问题，将输出相应的错误信息。这个函数主要是为了确保内核中的锁的正确性和稳定性，避免死锁和其他相关问题的出现。

### 初始化内存加密机制

mem_encrypt_init() 负责初始化内存加密机制。具体来说，它在处理器支持内存加密的情况下启用内存加密，并设置相应的内核参数。内存加密是一种将主存中的数据加密以保护其机密性的安全功能。在启用内存加密后，所有内核数据结构、代码和用户进程数据将以加密形式存储在内存中，以防止恶意软件攻击或物理攻击者获取内存中的机密信息。此函数的执行是系统启动过程中的一部分。

### 初始化每CPU的内存管理

setup_per_cpu_pageset()负责初始化每个CPU的内存管理。函数setup_per_cpu_pageset()的主要作用是初始化per-CPU页面集。

在Linux内核中，每个CPU都有一个单独的页面集结构，用于存储该CPU运行时使用的页面。这些页面被分配给各种内核子系统，例如虚拟内存、进程管理和网络子系统等。

在启动时，内核通过调用setup_per_cpu_pageset()来初始化每个CPU的页面集。该函数分配了一个包含多个页面集的结构体，并将每个CPU的页面集指针与相应的CPU ID相关联。随后，内核使用这些页面集来分配和管理各个CPU的页面。

### 初始化NUMA机制

numa_policy_init() 函数用于初始化 NUMA 内存分配策略相关的数据结构。NUMA（Non-Uniform Memory Access，非一致性存储访问）是指在一个系统中存在多个物理 CPU 和内存组件，不同的 CPU 访问不同的内存区域的速度不同。NUMA 策略通常用于在多 CPU 和内存组件的系统中优化内存分配和访问。这个函数在内核启动时被调用，初始化了 NUMA 相关的内存数据结构，包括节点、节点间距离和其他相关的配置信息。初始化完毕后，内核就可以根据 NUMA 策略来优化内存分配和访问，提高系统的性能。

### 初始化ACPI子系统

acpi_early_init() 负责初始化ACPI子系统。它的主要作用是启用 ACPI 早期解析，并设置 ACPI 相关的内核变量。

具体来说，该函数会在 Linux 内核初始化时执行，它会通过 ACPI 查找到 RSDP （Root System Description Pointer）表，该表包含系统信息的地址，然后根据该地址找到其他 ACPI 相关的表。

然后，该函数会将找到的 ACPI 表存储到内存中，并设置 ACPI 相关的内核变量，包括 acpi_disabled、acpi_gsi_to_irq、acpi_ioapic、acpi_lapic、acpi_numa、acpi_pci_disabled、acpi_skip_timer_override 等。这些变量的设置将为后续的内核启动阶段提供 ACPI 支持。

### 初始化进程调度器的时钟

sched_clock_init() 函数的作用是初始化调度器时钟。在 Linux 内核中，调度器时钟是一种用于测量时间间隔的计数器，它与调度器紧密相关，用于记录进程在 CPU 上运行的时间。该函数会调用底层体系结构相关的函数，以设置调度器时钟的频率和相关寄存器，以便在调度程序中使用调度器时钟。在 Linux 内核中，调度器时钟可以是一个纯软件计数器或是由硬件支持的计数器。

### 校准系统延迟

calibrate_delay() 函数是一个内核启动期间的延迟精度校准函数，用于测量系统定时器的精度。

具体而言，该函数会在启动期间校准循环延迟，以帮助内核在不同的系统上确定调度器的最佳时间分片和精度，并为内核定时器的精度提供参考。在校准时，该函数会使用自旋锁和读取时间戳计数器 (TSC) 的方式来进行高分辨率的测量，从而获得系统定时器的精度，并将测量结果记录在 loops_per_jiffy 变量中，供内核在运行时使用。

### 初始化进程ID的IDR

pid_idr_init()：初始化进程ID的IDR（idr属于Linux内核提供的一种简单的键值对存储数据结构）。它的主要作用是初始化用于存储进程 ID（PID）的 IDR 数据结构。IDR 是一种用于管理 ID 分配和释放的数据结构，Linux 内核使用它来分配和释放 PID。

pid_idr_init() 函数会通过调用 idr_init() 函数来初始化 IDR，设置起始 ID 为 0，ID 最大值为 PID_MAX_DEFAULT。此外，pid_idr_init() 还会调用 pidmap_init() 函数来初始化内核进程的 PID 映射表，该表用于为内核进程分配 PID。

### 初始化匿名虚拟内存区域

anon_vma_init() 是一个用于匿名内存映射的初始化函数，它在系统启动期间被调用。该函数的主要目的是初始化用于跟踪匿名内存映射的内核数据结构，特别是匿名虚拟内存区域（anon_vma）链表和相关的自旋锁。

在 Linux 内核中，匿名内存映射指的是一种不与文件系统关联的虚拟内存映射方式。在应用程序中，通过调用类似于 malloc() 或 mmap() 等函数，可以向内核请求分配一块匿名内存区域，该内存区域与文件系统没有任何关联。而这些分配的匿名内存区域需要通过一个专门的数据结构进行管理。这就是 anon_vma_init() 函数所创建的匿名虚拟内存区域链表，它可以帮助内核快速定位和管理这些匿名内存区域。

### 初始化线程栈缓存

thread_stack_cache_init()其作用是初始化线程栈缓存。

具体来说，该函数会为线程栈缓存分配一定的内存空间，并初始化这个内存空间中的数据结构。线程栈缓存是一块用于存储线程栈的内存空间，其作用是为线程提供快速的栈空间分配和释放。当一个线程需要使用栈空间时，可以从线程栈缓存中获取一块适当大小的栈空间，使用完后再将其归还到线程栈缓存中，以便下一次使用。

该函数的目的是提高线程栈的使用效率，避免频繁地进行内存分配和释放，从而提高系统的性能和响应速度。

### 初始化进程的安全凭证

cred_init()函数是Linux操作系统中的一个函数，其作用是初始化用户凭证结构体。该函数通常在系统启动时调用，以确保所有用户凭证结构体都被正确地初始化。

用户凭证结构体用于表示一个进程或线程的身份信息，包括用户ID、组ID、安全标签等信息。cred_init()函数会为一个新的用户凭证结构体分配一块内存空间，并将其中的所有字段都初始化为默认值，包括将用户ID和组ID设置为0（代表超级用户），安全标签设置为空等等。

通过初始化用户凭证结构体，操作系统可以为每个进程或线程分配一个独立的身份标识，从而保证了系统的安全性和隔离性。同时，通过将用户ID和组ID初始化为默认值，也确保了系统在启动时始终具有超级用户的权限，可以执行所有的系统操作。

### 初始化fork系统调用相关的资源

fork_init()：初始化fork系统调用相关的资源，其作用是初始化进程创建的相关数据结构。

在操作系统中，fork()函数是创建一个新进程的重要方法，通过复制父进程的状态来创建一个新的子进程。fork_init()函数会初始化这个过程中涉及到的相关数据结构，包括进程表、进程状态、资源限制等等。具体来说，该函数会为进程表中的每个字段分配内存空间，并将其中的所有值都设置为默认值，以确保在进程创建时，这些字段都能正确地初始化和更新。

通过初始化这些数据结构，操作系统可以有效地管理进程的创建和资源分配，确保每个进程都具有独立的进程ID和资源限制，从而避免进程间相互干扰和资源竞争。同时，通过确保进程表的正确性和完整性，也可以更加有效地管理进程的状态和运行情况，从而提高系统的稳定性和可靠性。

### 初始化proc文件系统缓存

proc_caches_init()函数是在Linux操作系统中初始化/proc文件系统缓存的一个函数，其作用是为/proc文件系统缓存分配内存，并进行初始化。

/proc文件系统是一个[虚拟文件系统](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=虚拟文件系统&zhida_source=entity)，用于向用户空间提供内核的各种信息，如进程列表、硬件信息、系统参数等。为了提高/proc文件系统的性能，操作系统会在内存中维护一个缓存，用于存储/proc文件系统中的数据。而proc_caches_init()函数则是用来初始化这个缓存的。

具体来说，该函数会为/proc文件系统缓存分配内存空间，并对其中的数据结构进行初始化。其中包括文件系统缓存的大小、缓存中各种数据结构的结构体等。通过初始化/proc文件系统缓存，操作系统可以加快读取/proc文件系统数据的速度，提高系统的响应速度和性能。

总之，proc_caches_init()函数是一个在Linux操作系统中用于初始化/proc文件系统缓存的函数，其目的是提高系统性能和效率，使得用户可以更快地访问/proc文件系统中的信息。

### 初始化UTS命名空间

uts_ns_init()：初始化UTS命名空间（UTS Namespace），其作用是为UTS命名空间分配内存空间，并初始化UTS命名空间中的各个字段。

UTS命名空间用于隔离不同的主机名和域名，使得每个进程可以拥有自己独立的主机名和域名，从而实现隔离和安全性。在操作系统启动时，uts_ns_init()函数会被调用，以初始化UTS命名空间，并为每个进程创建独立的UTS命名空间。

具体来说，uts_ns_init()函数会为UTS命名空间分配内存，并初始化其中的各个字段，包括主机名、域名等等。这些字段都是与进程相关的，因此需要为每个进程单独分配空间并进行初始化。通过初始化UTS命名空间，操作系统可以为每个进程提供独立的主机名和域名，从而实现了UTS命名空间的隔离和安全性。

总之，uts_ns_init()函数是Linux操作系统中用于初始化UTS命名空间的函数，其作用是为UTS命名空间分配内存并初始化其中的字段，以实现UTS命名空间的隔离和安全性。

### 初始化内核中的密钥管理

key_init()其作用是为密钥管理子系统分配内存空间，并进行初始化。

密钥管理子系统是Linux操作系统中的一个功能模块，用于管理密钥和访问控制。在操作系统启动时，key_init()函数会被调用，以初始化密钥管理子系统。具体来说，该函数会为密钥管理子系统分配内存空间，并初始化其中的各个数据结构，包括密钥环和密钥类型等。

通过初始化密钥管理子系统，操作系统可以提供更加安全和灵活的密钥管理和访问控制功能。例如，用户可以使用密钥管理子系统来管理和保护密码、数字证书等重要信息，同时可以通过密钥访问控制机制来限制对这些信息的访问。

key_init()函数是在Linux操作系统中用于初始化密钥管理子系统的函数，其作用是为密钥管理子系统分配内存并初始化其中的数据结构，从而提供更加安全和灵活的密钥管理和访问控制功能。

### 初始化安全子系统

security_init()其作用是为安全模块分配内存空间，并进行初始化。

在Linux操作系统中，安全模块是一种可插拔的模块化系统，用于提供安全性方面的功能，例如访问控制、身份验证等。在操作系统启动时，security_init()函数会被调用，以初始化安全模块。具体来说，该函数会为安全模块分配内存空间，并初始化其中的各个数据结构，包括安全策略和安全标签等。

通过初始化安全模块，操作系统可以提供更加安全和可靠的安全保护功能，以保护用户的数据和系统不受恶意攻击。例如，安全模块可以使用访问控制策略来限制对系统资源的访问，以确保只有经过身份验证的用户才能访问受保护的资源。

security_init()函数是在Linux操作系统中用于初始化安全模块的函数，其作用是为安全模块分配内存并初始化其中的数据结构，从而提供更加安全和可靠的安全保护功能。

### 初始化调试系统

dbg_late_init()其作用是在系统运行时为调试器提供支持。

在操作系统启动之后，dbg_late_init()函数会被调用，以初始化调试器的相关信息。具体来说，该函数会注册内核调试器，为其分配内存空间，并进行初始化。同时，该函数还会在操作系统中建立与调试器之间的通信通道，以便进行调试器的远程控制和调试。

通过调试器，系统管理员可以监控操作系统的运行状态，并诊断系统中出现的错误。调试器可以帮助管理员定位问题的根本原因，并对系统进行调优和优化。在操作系统运行过程中，调试器的重要性不言而喻，它可以有效地提高系统的稳定性和可靠性，为系统管理员提供更好的工作环境。

dbg_late_init()函数是用于在操作系统启动之后初始化和注册调试器的函数，其作用是为调试器提供支持，在系统运行过程中帮助管理员进行系统监控、故障排除和调试。

### 初始化网络命名空间

net_ns_init()负责初始化网络命名空间（Network Namespace），其作用是为每个网络命名空间分配内存，并进行初始化。

在Linux操作系统中，网络命名空间是一种虚拟化网络环境的技术，它可以将操作系统中的网络资源隔离开来，以便在同一台主机上运行多个网络应用程序，而不会相互干扰。在操作系统启动时，net_ns_init()函数会被调用，以为每个网络命名空间分配内存并进行初始化。具体来说，该函数会为每个网络命名空间创建一个唯一的标识符，并分配相应的内存空间，同时初始化网络命名空间的各种数据结构，包括网络设备、套接字等。

通过初始化网络命名空间，操作系统可以有效地隔离网络资源，确保网络应用程序之间的互不干扰，同时提供更好的网络性能和安全性。例如，在多租户环境中，网络命名空间可以用于将多个租户的网络资源隔离开来，以保护租户的数据安全性和隐私。

总之，net_ns_init()函数是用于初始化网络命名空间的函数，其作用是为每个网络命名空间分配内存并进行初始化，以提供更好的网络性能和安全性，同时隔离不同网络应用程序之间的网络资源，确保操作系统的稳定性和安全性。

### 初始化虚拟文件系统的缓存

vfs_caches_init()用于初始化虚拟文件系统（VFS）的缓存。VFS是Linux操作系统中的一个子系统，它为所有文件系统提供了统一的接口，从而使得不同的文件系统可以在操作系统中共存。

在[操作系统启动过程](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=操作系统启动过程&zhida_source=entity)中，vfs_caches_init()函数会被调用，以初始化VFS缓存。具体来说，该函数会为VFS缓存分配内存空间，并初始化VFS缓存中的各种数据结构，包括inode和dentry等。这些数据结构是VFS中非常重要的组成部分，它们存储了文件系统的元数据和[目录结构](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=目录结构&zhida_source=entity)等信息。

通过初始化VFS缓存，操作系统可以提高文件系统的性能和响应速度。例如，当应用程序请求访问文件系统中的文件时，操作系统可以通过VFS缓存快速定位到对应的文件数据，从而提高文件系统的访问速度。此外，VFS缓存还可以缓存文件系统的元数据和目录结构等信息，以加快文件系统的访问速度。

vfs_caches_init()函数是用于初始化VFS缓存的函数，其作用是为VFS缓存分配内存并初始化其中的各种数据结构，从而提高文件系统的性能和响应速度。

### 初始化页面缓存

pagecache_init()用于初始化页高速缓存（page cache）。页高速缓存是Linux操作系统中非常重要的一个子系统，它是文件系统缓存的一种，用于缓存文件系统中的数据块。这些数据块可以是文件的内容，也可以是文件系统中的元数据。

在操作系统启动过程中，pagecache_init()函数会被调用，以初始化页高速缓存。具体来说，该函数会为页高速缓存分配内存空间，并初始化其中的各种数据结构。在初始化过程中，操作系统会设置页高速缓存的各种参数，例如缓存大小、数据块大小等。

通过初始化页高速缓存，操作系统可以提高文件系统的性能和响应速度。例如，当应用程序请求访问文件系统中的文件时，操作系统可以通过页高速缓存快速定位到对应的文件数据块，从而提高文件系统的访问速度。此外，页高速缓存还可以减少文件系统中的磁盘I/O操作，从而提高文件系统的性能和响应速度。

pagecache_init()函数是用于初始化页高速缓存的函数，其作用是为页高速缓存分配内存并初始化其中的各种数据结构，从而提高文件系统的性能和响应速度。

### 初始化信号处理器

signals_init()用于初始化信号处理器。信号是Linux中一个非常重要的机制，它允许进程之间进行通信，以及处理系统中的异常情况。

在操作系统启动过程中，signals_init()函数会被调用，以初始化信号处理器。具体来说，该函数会为信号处理器分配内存空间，并初始化其中的各种数据结构。在初始化过程中，操作系统会设置信号处理器的各种参数，例如信号处理函数、信号的默认行为等。

通过初始化信号处理器，操作系统可以为应用程序提供可靠的信号处理机制。例如，当操作系统检测到某个进程发生异常时，可以向该进程发送一个信号，以通知进程处理异常情况。此外，应用程序也可以通过信号处理器自定义处理信号的行为，从而满足应用程序的特定需求。

signals_init()函数是用于初始化信号处理器的函数，其作用是为信号处理器分配内存并初始化其中的各种数据结构，从而为应用程序提供可靠的信号处理机制。

### 初始化seq_file

seq_file_init()用于初始化seq_file（用于向用户空间输出大量数据的接口）。顺序文件是Linux中一个非常重要的机制，它允许内核中的数据结构以顺序的方式进行迭代，以便用户空间的程序能够读取这些数据。

在操作系统启动过程中，seq_file_init()函数会被调用，以初始化顺序文件。具体来说，该函数会为顺序文件分配内存空间，并初始化其中的各种数据结构。在初始化过程中，操作系统会设置顺序文件的各种参数，例如读取函数、缓存大小等。

通过初始化顺序文件，操作系统可以为用户空间的程序提供一种方便的方式来访问内核中的数据结构。例如，内核中的某个数据结构可以通过顺序文件的方式进行迭代，用户空间的程序可以通过读取顺序文件来获取这些数据。此外，顺序文件还可以进行缓存，从而提高数据访问的效率。

seq_file_init()函数是用于初始化顺序文件的函数，其作用是为顺序文件分配内存并初始化其中的各种数据结构，从而为用户空间的程序提供一种方便的方式来访问内核中的数据结构。

### 初始化/proc文件系统

proc_root_init()用于初始化/proc文件系统的根目录。/proc文件系统是一个虚拟文件系统，它允许用户空间的程序访问内核中的各种信息和统计数据。

在操作系统启动过程中，proc_root_init()函数会被调用，以初始化/proc文件系统的根目录。具体来说，该函数会创建/proc文件系统的根目录，并向其中添加各种文件和目录。这些文件和目录包括进程列表、内存信息、CPU信息等。

通过初始化/proc文件系统的根目录，操作系统可以为用户空间的程序提供一种方便的方式来访问内核中的各种信息和统计数据。例如，用户空间的程序可以读取/proc目录中的某个文件来获取进程的详细信息，或者获取系统的内存使用情况。

proc_root_init()函数是用于初始化/proc文件系统的根目录的函数，其作用是创建/proc文件系统的根目录，并向其中添加各种文件和目录，从而为用户空间的程序提供一种方便的方式来访问内核中的各种信息和统计数据。

### 初始化命名空间文件系统

nsfs_init()用于初始化[名字空间](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=名字空间&zhida_source=entity)文件系统。名字空间是Linux中一个非常重要的机制，它允许内核中的各种资源被隔离和封装，从而提高系统的安全性和可靠性。

在操作系统启动过程中，nsfs_init()函数会被调用，以初始化名字空间文件系统。具体来说，该函数会创建名字空间文件系统的根目录，并向其中添加各种文件和目录。这些文件和目录包括各种名字空间的类型，例如网络、进程、用户等。

通过初始化名字空间文件系统，操作系统可以为用户空间的程序提供一种方便的方式来管理各种名字空间。例如，用户空间的程序可以通过访问名字空间文件系统中的某个目录来创建、销毁或修改名字空间。

nsfs_init()函数是用于初始化名字空间文件系统的函数，其作用是创建名字空间文件系统的根目录，并向其中添加各种文件和目录，从而为用户空间的程序提供一种方便的方式来管理各种名字空间。

### 初始化CPU集合控制器

cpuset_init()用于初始化cpuset子系统。cpuset子系统是Linux中一个非常重要的机制，它允许将系统中的CPU和内存资源分组，从而可以更好地管理系统的性能和资源使用情况。

在操作系统启动过程中，cpuset_init()函数会被调用，以初始化cpuset子系统。具体来说，该函数会创建cpuset子系统的根节点，并向其中添加各种控制文件和目录。这些控制文件和目录包括cpuset的控制文件、任务文件等。

通过初始化cpuset子系统，操作系统可以为用户空间的程序提供一种方便的方式来管理系统的CPU和内存资源。例如，用户空间的程序可以通过修改cpuset中的控制文件来限制进程的CPU和内存使用，从而更好地管理系统的性能和资源使用情况。

cpuset_init()函数是用于初始化cpuset子系统的函数，其作用是创建cpuset子系统的根节点，并向其中添加各种控制文件和目录，从而为用户空间的程序提供一种方便的方式来管理系统的CPU和内存资源。

初始化控制组（Cgroup）

cgroup_init()用于初始化cgroup（control group）子系统的函数。cgroup是一种Linux内核机制，用于对进程、任务或者一组进程进行分组，并为这些分组提供一组资源管理机制，包括CPU、内存、IO、网络等资源。

在系统启动过程中，cgroup_init()函数被调用，用于初始化cgroup子系统。具体来说，该函数会创建cgroup子系统的根节点，并向其中添加各种控制文件和目录。这些控制文件和目录包括cgroup的控制文件、任务文件等。

通过初始化cgroup子系统，操作系统可以为用户空间的程序提供一种方便的方式来管理系统的资源使用。例如，用户空间的程序可以通过修改cgroup中的控制文件来限制进程的资源使用，从而更好地管理系统的性能和资源使用情况。

cgroup_init()函数是用于初始化cgroup子系统的函数，其作用是创建cgroup子系统的根节点，并向其中添加各种控制文件和目录，从而为用户空间的程序提供一种方便的方式来管理系统的资源使用。

### 初始化进程任务统计

taskstats_init_early()用于在系统启动过程中早期初始化taskstats子系统的函数。taskstats子系统是一种用于统计和记录进程和任务活动信息的机制，包括CPU使用、内存使用、I/O操作、网络等信息。

该函数主要完成以下工作：

1. 注册网络命名空间回调函数，以便在创建或销毁网络命名空间时更新taskstats信息。
2. 注册系统调用拦截钩子函数，以便在进程创建或结束时记录相应的taskstats信息。
3. 创建taskstats控制文件，为用户空间提供读取taskstats信息的接口。

通过taskstats_init_early()函数的调用，操作系统可以在系统启动过程中早期就开始初始化taskstats子系统，以便在进程和任务的活动过程中记录相应的信息。这样，用户空间的程序就可以通过读取taskstats控制文件来获取相应的系统活动信息，以便进行性能分析、资源优化等操作。

taskstats_init_early()函数是用于在系统启动过程中早期初始化taskstats子系统的函数，其作用是注册回调函数和系统调用拦截钩子函数，创建taskstats控制文件，以便在进程和任务的活动过程中记录相应的系统活动信息，并为用户空间提供相应的接口。

### 初始化延迟会计系统

delayacct_init()用于初始化延迟账户（delay accounting）子系统的函数。延迟账户是一种用于统计进程等待时间的机制，通过它可以记录进程等待CPU时间、磁盘I/O时间等等。这些信息可以用于性能分析、优化和故障排除等操作。

该函数主要完成以下工作：

1. 初始化进程等待队列，并将其添加到系统中。
2. 注册系统调用拦截钩子函数，以便在进程调用系统调用时记录相应的延迟账户信息。
3. 创建延迟账户控制文件，为用户空间提供读取延迟账户信息的接口。

通过delayacct_init()函数的调用，操作系统可以初始化延迟账户子系统，以便在进程等待CPU时间、磁盘I/O时间等时记录相应的延迟账户信息。这样，用户空间的程序就可以通过读取延迟账户控制文件来获取相应的系统活动信息，以便进行性能分析、资源优化等操作。

delayacct_init()函数是用于初始化延迟账户子系统的函数，其作用是初始化进程等待队列，注册系统调用拦截钩子函数，创建延迟账户控制文件，以便记录进程等待时间的信息，并为用户空间提供相应的接口。

### 检查错误和异常

check_bugs()主要用于在系统启动时检测处理器是否有已知的缺陷或 bug，并且在必要时禁用相关功能或采取其他措施来规避这些问题。该函数会检测处理器是否有特定的 bug，并对这些 bug 采取相应的措施，例如禁用相关的 CPU 功能或更新微代码。

具体来说，check_bugs() 函数会执行以下任务：

1. 检测处理器是否支持一些特定的 CPU 功能，例如 SSE、SSE2 等，并在必要时禁用这些功能。
2. 检测处理器是否有已知的 bug，并对这些 bug 采取相应的措施，例如禁用相关的 CPU 功能或更新微代码。
3. 检测系统是否有特定的硬件，例如某些型号的硬盘，这些硬件可能会导致系统崩溃或数据损坏，并在必要时采取相应的措施。

check_bugs() 函数是一个非常重要的函数，它可以确保系统在启动时能够正确地检测和规避已知的处理器和硬件问题，以确保系统的稳定性和可靠性。

### 初始化ACPI

acpi_subsystem_init()主要用于初始化 ACPI 子系统。ACPI（Advanced Configuration and Power Interface）是一种开放标准，旨在为操作系统提供系统配置信息、电源管理等功能。在 Linux 中，ACPI 子系统负责解析 ACPI 表格、解释 ACPI 事件、实现 ACPI 接口等。

具体来说，acpi_subsystem_init() 函数会执行以下任务：

1. 注册 ACPI 子系统驱动程序，并向 ACPI 事件子系统注册 ACPI 事件处理程序。
2. 初始化 ACPI 名字空间，建立 ACPI 对象之间的关系。
3. 解析 ACPI 表格，生成 ACPI 对象，并建立对象之间的关系。
4. 建立 ACPI 事件通道，等待 ACPI 事件的到来。
5. 向系统注册电源管理相关的接口，如 CPU 状态、系统状态等。

acpi_subsystem_init() 函数是一个非常重要的函数，它负责初始化和管理 ACPI 子系统，提供了操作系统与硬件之间的接口，确保操作系统能够正常使用系统的配置信息和实现电源管理等功能。

### 执行架构特定的后续初始化

arch_post_acpi_subsys_init()用于在 ACPI 子系统初始化完成之后，完成架构相关的初始化。

具体来说，arch_post_acpi_subsys_init() 函数会执行以下任务：

1. 完成与 ACPI 子系统相关的架构初始化，如启用 MMIO 区域、设置 ACPI 硬件平台数据等。
2. 完成其他体系结构相关的初始化，如设置 CPU 的缓存大小、初始化时钟等。
3. 最后，启动 init 进程，使系统进入用户空间。

arch_post_acpi_subsys_init() 函数是系统启动过程中的一个重要函数，负责完成与 ACPI 子系统相关的架构初始化，并启动用户空间的 init 进程，使系统进入正常运行状态。

### 初始化 Kernel Concurrency Sanitizer

kcsan_init()用于初始化 Kernel Concurrency Sanitizer (KCSAN)。

具体来说，kcsan_init() 函数会执行以下任务：

1. 为 KCSAN 分配并初始化内存空间。
2. 注册 KCSAN 的回调函数，以便在内核中发生并发错误时进行相应的处理。
3. 如果当前系统已开启 KCSAN 的用户接口，则在初始化时通过 procfs 创建相应的文件，以便用户可以设置 KCSAN 的参数。

kcsan_init() 函数是负责初始化 Kernel Concurrency Sanitizer 的函数，通过注册回调函数、初始化内存空间等方式，为检测内核中的并发错误做好准备。同时，它还提供了用户接口，方便用户对 KCSAN 进行配置。

### 调用初始化函数

arch_call_rest_init()用于在系统引导时调用平台特定的初始化函数。

在启动过程中，当内核完成了基本的初始化后，调用 rest_init() 进入到用户空间线程中，而在 rest_init() 函数中，会调用 kernel_init() 函数创建用户空间进程 init ，同时创建内核线程 kthreadd。但由于需要先创建 init 进程再创建内核线程 kthreadd，否则在 init 进程中创建线程时会产生 OOPS 错误，所以 arch_call_rest_init() 函数将这两个操作分别放在不同的函数中完成。

arch_call_rest_init() 函数会首先调用架构相关的 rest_init() 函数完成一些架构相关的初始化工作，然后调用 kernel_init() 函数创建 init 进程。在创建完 init 进程后，调用 kthreadd() 函数创建内核线程 kthreadd，同时等待 kthreadd 线程创建完成。最后，启用抢占功能，调用 cpu_startup_entry() 函数开始多处理器的启动。

具体来说，arch_call_rest_init() 函数会执行以下任务：

1. 调用rcu_scheduler_starting()启动RCU调度器。
2. 创建一个用户空间进程，即kernel_init，并指定其PID为1。
3. 对创建的PID为1的进程进行CPU亲和性绑定操作，将其绑定到启动CPU上。
4. 调用numa_default_policy()，设置NUMA的默认策略。
5. 创建一个内核线程kthreadd。
6. 等待kthreadd线程启动完成。
7. 启用中断和调度器功能。
8. 启动CPU调度器。
9. 完成kthreadd线程的启动，并允许调度器调度其他进程。
10. 调用cpu_startup_entry(CPUHP_ONLINE)，将CPU置为在线状态，使其能够执行任务。

当 rest_init 函数完成后，它调用了 cpu_startup_entry 函数，该函数将启动 CPU 并进入内核线程的执行环境，从而开始执行内核线程。在内核线程启动后，如果没有可执行的进程，内核会使 CPU 进入 idle 状态，等待下一次的中断。

```text
noinline void __ref rest_init(void)
{
	struct task_struct *tsk;
	int pid;

	rcu_scheduler_starting();
		rcu_read_lock();
	tsk = find_task_by_pid_ns(pid, &init_pid_ns);
	tsk->flags |= PF_NO_SETAFFINITY;
	set_cpus_allowed_ptr(tsk, cpumask_of(smp_processor_id()));
	rcu_read_unlock();

	numa_default_policy();
	pid = kernel_thread(kthreadd, NULL, CLONE_FS | CLONE_FILES);
	rcu_read_lock();
	kthreadd_task = find_task_by_pid_ns(pid, &init_pid_ns);
	rcu_read_unlock();

		system_state = SYSTEM_SCHEDULING;

	complete(&kthreadd_done);

		schedule_preempt_disabled();
		cpu_startup_entry(CPUHP_ONLINE);
}
```

### 避免[尾调用](https://zhida.zhihu.com/search?content_id=223252723&content_type=Article&match_order=1&q=尾调用&zhida_source=entity)优化

prevent_tail_call_optimization()：避免尾调用优化，确保函数调用链的正确性。prevent_tail_call_optimization() 函数是 Linux 内核中的一个辅助函数，用于防止编译器对某些函数进行尾调用优化（Tail Call Optimization，TCO）。

尾调用优化是编译器优化的一种形式，它可以将一个函数的尾部调用替换为跳转指令，从而减少函数调用的开销。但有时候，尾调用优化可能会导致调试变得困难，因为当一个函数被优化成尾调用时，函数调用关系链会被打破，难以在调试器中回溯函数调用栈。为了解决这个问题，prevent_tail_call_optimization() 函数被设计为在函数调用的尾部添加一些无用的代码，使编译器无法将这个函数优化为尾调用。这样可以保证在调试时可以正确的回溯函数调用栈。

具体来说，prevent_tail_call_optimization() 函数会在函数的尾部插入一条不可能执行到的语句，例如一个死循环语句，以防止编译器进行尾调用优化。这个函数通常用于一些需要调试的函数，如调试信息输出函数等。