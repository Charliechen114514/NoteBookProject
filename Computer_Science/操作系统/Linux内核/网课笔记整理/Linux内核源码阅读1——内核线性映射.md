# Linux内核源码阅读

## Linux内核区域映射

​	笔者开始第一次尝试阅读Linux源码，此时笔者对Linux操作系统的内核感兴趣。这里笔者决定展开研究源码进行阅读。

## 关于Linux操作系统的地址映射图

​	没有什么比Documentation更香的了。由于aarch64 Linux在内核5.10版本发生较大的变动。因此大部分老教程几乎可以说是内容作废。

​	值得注意的是：如果您手头的资料还在告诉您内核：用户=1：3的话，你可以信誓旦旦的确定他在谈论的是32位OS。事实上，我们可以在menuconfig中设定自己的Virtual Memory想要的是几位。

​	当然，这里给出的是最为常见的内存分布图，可以看到的是，对于一般的小页，页表将会是4级的。

​	一般的，现代电脑内存大多为几十GB层级，远小于 128TB或者是256 TB（48比特表达的地址长度），因此。我们的内核采用的是这样的技巧：

​	对于前 256 TB的大空间，即范围为0x0000 0000 0000 0000到0000ffffffffffff给了用户空间，这里我们的内存访问不需要高特权级。对于内核的内存映射需要注意的是：我们的所有最高16位都是1，意味着0xFFFF打头的都是内核地址空间！

>arch/arm64/include/asm/memory.h

```
/*
 * PAGE_OFFSET - the virtual address of the start of the linear map, at the
 *               start of the TTBR1 address space.
 * PAGE_END - the end of the linear map, where all other kernel mappings begin.
 * KIMAGE_VADDR - the virtual address of the start of the kernel image.
 * VA_BITS - the maximum number of bits for virtual addresses.
 */
#define VA_BITS			(CONFIG_ARM64_VA_BITS)
#define _PAGE_OFFSET(va)	(-(UL(1) << (va)))
#define PAGE_OFFSET		(_PAGE_OFFSET(VA_BITS))
```

​	这一点你可以仔细看看宏，就会发现内核编程人员采用了反码技巧来获得内存地址空间的边界。

​	我们倒过来看。对于最高的地址仍然留给了Guard Page表达这里的地址都是非法的，出现这里的地址访问将会抛出异常表达程序错误！在下面就是vmemmap：这个是内核中页表数组的存放处。

> arch/arm64/include/asm/memory.h

```
/*
 * VMEMMAP_SIZE - allows the whole linear region to be covered by
 *                a struct page array
 *
 * If we are configured with a 52-bit kernel VA then our VMEMMAP_SIZE
 * needs to cover the memory region from the beginning of the 52-bit
 * PAGE_OFFSET all the way to PAGE_END for 48-bit. This allows us to
 * keep a constant PAGE_OFFSET and "fallback" to using the higher end
 * of the VMEMMAP where 52-bit support is not available in hardware.
 */
#define VMEMMAP_RANGE		(_PAGE_END(VA_BITS_MIN) - PAGE_OFFSET)
#define VMEMMAP_SIZE		((VMEMMAP_RANGE >> PAGE_SHIFT) * sizeof(struct page))
#define VMEMMAP_START		(VMEMMAP_END - VMEMMAP_SIZE)
#define VMEMMAP_END			(-UL(SZ_1G))	# 默认的值，后续会更改移动
```

​	这里可以看到内核中表达从高向低的地址技巧：那就是取反（这是补码的表达，各位可以复习一下补码的概念！）

​	可以看到这里说明了意图：这里是线性映射区（为什么呢？我们知道内核与用户进程没有关系，在这里，我们的地址访问一定唯一。因此唯一的一个虚拟地址就是对应一个物理地址。为此我们决定单独的开一个简单的线性映射来维护我们的内核地址空间映射）

> 内核其实访问的时候也是访问的虚拟地址，也需要走页表转换，这里就是在暗示这一点。

​	我们的下一个区域就是PCI IO保留区。中间为了检查内存访问设置了一个8MB的Guard Page确保安全访问。

> arch/arm64/include/asm/memory.h 

```
#define PCI_IO_START		(VMEMMAP_END + SZ_8M)
#define PCI_IO_END		(PCI_IO_START + PCI_IO_SIZE)
```

​	SZ_8M就是8MB大小的意思。

​	下一个就是fixmap了。

​	fixmap的内容我们需要在fixmap.h中查阅：

>arch/arm64/include/asm/fixmap.h

```
/*
 * fixmap.h: compile-time virtual memory allocation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1998 Ingo Molnar
 * Copyright (C) 2013 Mark Salter <msalter@redhat.com>
 *
 * Adapted from arch/x86 version.
 *
 */
...
/*
 * Here we define all the compile-time 'special' virtual
 * addresses. The point is to have a constant address at
 * compile time, but to set the physical address only
 * in the boot process.
 *
 * Each enum increment in these 'compile-time allocated'
 * memory buffers is page-sized. Use set_fixmap(idx,phys)
 * to associate physical memory with a fixmap index.
 */
enum fixed_addresses {
	FIX_HOLE,

	/*
	 * Reserve a virtual window for the FDT that is a page bigger than the
	 * maximum supported size. The additional space ensures that any FDT
	 * that does not exceed MAX_FDT_SIZE can be mapped regardless of
	 * whether it crosses any page boundary.
	 */
	FIX_FDT_END,
	FIX_FDT = FIX_FDT_END + DIV_ROUND_UP(MAX_FDT_SIZE, PAGE_SIZE) + 1,

	FIX_EARLYCON_MEM_BASE,
	FIX_TEXT_POKE0,

#ifdef CONFIG_ACPI_APEI_GHES
	/* Used for GHES mapping from assorted contexts */
	FIX_APEI_GHES_IRQ,
	FIX_APEI_GHES_SEA,
#ifdef CONFIG_ARM_SDE_INTERFACE
	FIX_APEI_GHES_SDEI_NORMAL,
	FIX_APEI_GHES_SDEI_CRITICAL,
#endif
#endif /* CONFIG_ACPI_APEI_GHES */

#ifdef CONFIG_UNMAP_KERNEL_AT_EL0
#ifdef CONFIG_RELOCATABLE
	FIX_ENTRY_TRAMP_TEXT4,	/* one extra slot for the data page */
#endif
	FIX_ENTRY_TRAMP_TEXT3,
	FIX_ENTRY_TRAMP_TEXT2,
	FIX_ENTRY_TRAMP_TEXT1,
#define TRAMP_VALIAS		(__fix_to_virt(FIX_ENTRY_TRAMP_TEXT1))
#endif /* CONFIG_UNMAP_KERNEL_AT_EL0 */
	__end_of_permanent_fixed_addresses,

	/*
	 * Temporary boot-time mappings, used by early_ioremap(),
	 * before ioremap() is functional.
	 */
#define NR_FIX_BTMAPS		(SZ_256K / PAGE_SIZE)
#define FIX_BTMAPS_SLOTS	7
#define TOTAL_FIX_BTMAPS	(NR_FIX_BTMAPS * FIX_BTMAPS_SLOTS)

	FIX_BTMAP_END = __end_of_permanent_fixed_addresses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAL_FIX_BTMAPS - 1,

	/*
	 * Used for kernel page table creation, so unmapped memory may be used
	 * for tables.
	 */
	FIX_PTE,
	FIX_PMD,
	FIX_PUD,
	FIX_P4D,
	FIX_PGD,

	__end_of_fixed_addresses
};

#define FIXADDR_SIZE		(__end_of_permanent_fixed_addresses << PAGE_SHIFT)
#define FIXADDR_START		(FIXADDR_TOP - FIXADDR_SIZE)
#define FIXADDR_TOT_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#define FIXADDR_TOT_START	(FIXADDR_TOP - FIXADDR_TOT_SIZE)

#define FIXMAP_PAGE_IO     __pgprot(PROT_DEVICE_nGnRE)
```

​	这里就是所有的固定映射区的定义。当我们仔细看看注释的时候，我们也就明白了为什么要保留这个区域的大小：在一段固定的虚拟地址建立映射；则可以通过这块的virt addr，映射到任意的phy addr上，在mmu enable之后就可以自由自在的访问我们需要的内容了。当然这种编译时确定可以帮助我们提升内核性能。

>1. FDT 用于设备树信息的获取
>2. console 用于早期调试需要，打印log之类的
>3. text 用于映射RO段code，可以作为动态升级这种
>4. other BTMAP 用于各个模块申请使用，即临时映射
>5. fix page 用于映射页表处理，在paging_init部分会使用

​	下一个就是大名鼎鼎的vmalloc区域。这下就是我们的vmalloc申请的虚拟地址都在这里了。

​	在下一个就是module的内核模块。我们的insmod就是讲内核cv到这个片区的一个地址，让内核可以访问到模块。

```
#define MODULES_END			(MODULES_VADDR + MODULES_VSIZE)
#define MODULES_VADDR		(_PAGE_END(VA_BITS_MIN))
#define MODULES_VSIZE		(SZ_2G)
```

​	最后的最后，就是两个可能的部分了：一个就是内核的镜像区：

```
#define KIMAGE_VADDR		(MODULES_END)
```

​	这个以下的所有区域都是内核使用的堆栈区。以及若看官启用KASAN，那么它的内存分配也会在这里。

```
/*
 * Generic and Software Tag-Based KASAN modes require 1/8th and 1/16th of the
 * kernel virtual address space for storing the shadow memory respectively.
 *
 * The mapping between a virtual memory address and its corresponding shadow
 * memory address is defined based on the formula:
 *
 *     shadow_addr = (addr >> KASAN_SHADOW_SCALE_SHIFT) + KASAN_SHADOW_OFFSET
 *
 * where KASAN_SHADOW_SCALE_SHIFT is the order of the number of bits that map
 * to a single shadow byte and KASAN_SHADOW_OFFSET is a constant that offsets
 * the mapping. Note that KASAN_SHADOW_OFFSET does not point to the start of
 * the shadow memory region.
 *
 * Based on this mapping, we define two constants:
 *
 *     KASAN_SHADOW_START: the start of the shadow memory region;
 *     KASAN_SHADOW_END: the end of the shadow memory region.
 *
 * KASAN_SHADOW_END is defined first as the shadow address that corresponds to
 * the upper bound of possible virtual kernel memory addresses UL(1) << 64
 * according to the mapping formula.
 *
 * KASAN_SHADOW_START is defined second based on KASAN_SHADOW_END. The shadow
 * memory start must map to the lowest possible kernel virtual memory address
 * and thus it depends on the actual bitness of the address space.
 *
 * As KASAN inserts redzones between stack variables, this increases the stack
 * memory usage significantly. Thus, we double the (minimum) stack size.
 */
#if defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
#define KASAN_SHADOW_OFFSET	_AC(CONFIG_KASAN_SHADOW_OFFSET, UL)
#define KASAN_SHADOW_END	((UL(1) << (64 - KASAN_SHADOW_SCALE_SHIFT)) + KASAN_SHADOW_OFFSET)
#define _KASAN_SHADOW_START(va)	(KASAN_SHADOW_END - (UL(1) << ((va) - KASAN_SHADOW_SCALE_SHIFT)))
#define KASAN_SHADOW_START	_KASAN_SHADOW_START(vabits_actual)
#define PAGE_END		KASAN_SHADOW_START
#define KASAN_THREAD_SHIFT	1
#else
#define KASAN_THREAD_SHIFT	0
#define PAGE_END		(_PAGE_END(VA_BITS_MIN))
#endif /* CONFIG_KASAN */
```

​	好了到这里，我们可以看看

> Documentation/arch/arm64/memory.rst 

​	这个文件告诉了我们的内存映射是如何的：

```
AArch64 Linux memory layout with 4KB pages + 4 levels (48-bit)::

  Start                 End                     Size            Use
  -----------------------------------------------------------------------
  0000000000000000      0000ffffffffffff         256TB          user
  ffff000000000000      ffff7fffffffffff         128TB          kernel logical memory map
 [ffff600000000000      ffff7fffffffffff]         32TB          [kasan shadow region]
  ffff800000000000      ffff80007fffffff           2GB          modules
  ffff800080000000      fffffbffefffffff         124TB          vmalloc
  fffffbfff0000000      fffffbfffdffffff         224MB          fixed mappings (top down)
  fffffbfffe000000      fffffbfffe7fffff           8MB          [guard region]
  fffffbfffe800000      fffffbffff7fffff          16MB          PCI I/O space
  fffffbffff800000      fffffbffffffffff           8MB          [guard region]
  fffffc0000000000      fffffdffffffffff           2TB          vmemmap
  fffffe0000000000      ffffffffffffffff           2TB          [guard region]


AArch64 Linux memory layout with 64KB pages + 3 levels (52-bit with HW support)::

  Start                 End                     Size            Use
  -----------------------------------------------------------------------
  0000000000000000      000fffffffffffff           4PB          user
  fff0000000000000      ffff7fffffffffff          ~4PB          kernel logical memory map
 [fffd800000000000      ffff7fffffffffff]        512TB          [kasan shadow region]
  ffff800000000000      ffff80007fffffff           2GB          modules
  ffff800080000000      fffffbffefffffff         124TB          vmalloc
  fffffbfff0000000      fffffbfffdffffff         224MB          fixed mappings (top down)
  fffffbfffe000000      fffffbfffe7fffff           8MB          [guard region]
  fffffbfffe800000      fffffbffff7fffff          16MB          PCI I/O space
  fffffbffff800000      fffffbffffffffff           8MB          [guard region]
  fffffc0000000000      ffffffdfffffffff          ~4TB          vmemmap
  ffffffe000000000      ffffffffffffffff         128GB          [guard region]


Translation table lookup with 4KB pages::

  +--------+--------+--------+--------+--------+--------+--------+--------+
  |63    56|55    48|47    40|39    32|31    24|23    16|15     8|7      0|
  +--------+--------+--------+--------+--------+--------+--------+--------+
            |        |         |         |         |         |
            |        |         |         |         |         v
            |        |         |         |         |   [11:0]  in-page offset
            |        |         |         |         +-> [20:12] L3 index
            |        |         |         +-----------> [29:21] L2 index
            |        |         +---------------------> [38:30] L1 index
            |        +-------------------------------> [47:39] L0 index
            +----------------------------------------> [55] TTBR0/1


Translation table lookup with 64KB pages::

  +--------+--------+--------+--------+--------+--------+--------+--------+
  |63    56|55    48|47    40|39    32|31    24|23    16|15     8|7      0|
  +--------+--------+--------+--------+--------+--------+--------+--------+
            |        |    |               |              |
            |        |    |               |              v
            |        |    |               |            [15:0]  in-page offset
            |        |    |               +----------> [28:16] L3 index
            |        |    +--------------------------> [41:29] L2 index
            |        +-------------------------------> [47:42] L1 index (48-bit)
            |                                          [51:42] L1 index (52-bit)
            +----------------------------------------> [55] TTBR0/1
```

