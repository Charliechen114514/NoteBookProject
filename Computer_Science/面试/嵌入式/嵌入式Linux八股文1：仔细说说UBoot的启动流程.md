# 嵌入式Linux八股文1：仔细说说UBoot的启动流程

## 前言

​	笔者投了一些嵌入式Linux的厂，需要对嵌入式Linux有一个相对比较基本的了解，这里就准备开始进行一个整理和总结，尝试将我们的流程梳理的更加清楚和详细。

​	关于UBoot的启动问题似乎相当常见（这是可以理解的，UBoot就是负责启动的流程，是板子上电 CPU执行第一条指令开始到加载并启动内核的主角），**下面笔者针对无设备树启动和有设备树启动两种**

## 无设备树的UBoot启动流程

​	正点原子的教程使用的是2016年的无设备树的UBoot启动，下面就针对此聊一聊我们的无设备树的UBoot是如何进行启动的。

### CPU上电到准备潜在的重定向

​	我们的板子在CPU上电之后，就应当跳转到我们默认的存储设备的地址上，在那里，我们期待那里放置着我们的中断向量表，这跟单片机（至少是笔者熟悉的STM32）是类似的，我们单片机上电也是跳转道我们的中断向量表的表头，一般而言，表头的第一个就是我们的RESET向量，他会跳转到我们的start code上。这里我们就准备开始我们的初始化流程。

​	现在，我们的CPU执行流正在跟我们的内部片上的ROM进行交互（读写），我们利用这一部分空间完成必要的**低级初始化**（时钟、PLL、SRAM），并读取映像到 SRAM 或其他低端内存中。现在，我们的空间被进一步的增大了。

​	如果我们的板子上存在第二阶段启动（比如说我们的SoC RAM实在少的可怜），这个时候我们会在SPL中进一步初始化我们的DRAM，并加载主 U-Boot 镜像至 DRAM 中。SPL 通常不会执行重定位。这是后面的UBoot自己动手做的。SPL 加载完后跳转到主 U-Boot（入口通常为 `_start` 或 `board_init_f`），开始完整程序流程。

​	现在，板子的基本的功能都已经准备就绪了，下一步就是进一步初始化UBoot的功能，进一步开启板子上的高级外设功能。

​	我们在开启更多的RAM之后，就要准备初始化更多的硬件，准备为一部分自己后续启动环境运行和Linux内核的加载准备好环境。所以，我们要准备做代码的重定位问题。但是做重定位之前，我们要做一些准备。这也就是大名鼎鼎的board_init_f阶段，他按照一定的顺序依次调用重定向前需要做的工作，比如说：

- 初始化硬件（UART、缓存、定时器、DDR controller）
- 设置全局数据 `gd`（Global Data）
- 为重定位设定目标地址（基于 `CONFIG_SYS_RELOCATE_ADDR`、`CONFIG_SYS_TEXT_BASE`）

### 重定位代码段和uboot搬移

​	我们首先看看是否有必要进行搬移：
​	 利用 `ADR/ADR` + `LDR` 指令判断是否已在目标地址运行。

```
adr r0, _start
ldr r1, _TEXT_BASE
cmp r0, r1
bne proceed          ; 若不同，则需要重定位
```

​	`memcpy(_reloc_start, _text, _text_size)`，将 `.text` 副本移动到高端 DRAM，避免原始段成为通用内存。这样的话就可以释放和归并通用内存。

​	下一步就是填充和修正我们的重定位修正表，编译时启用 `-pie` 和自动生成 `.rela.dyn` 区段，runtime 利用 fixup table 修正绝对引用的代码和数据地址，**随后我们跳转到新位置并重建栈/GD**，跳转至重定向后的代码入口，设置新的 stack pointer、全局数据指针 `gd->relocaddr`，并完成 BSS 清零、`.data` 拷贝等重定位后工作（现在BSS可用了）

### 执行重定向后的完全初始化逻辑：board_init_r

​	现在，我们的全局变量现在实际位于新地址，`bdinfo` 可见 `relocaddr` 和 `reloc_off` 等信息，进一步的，我们需要准备好可以远程或者本地加载Linux内核环境的东西。初始化内存池、动态分配、外围设备和环境变量等，进入交互式 shell 或自动执行脚本。

### ARM Tag扫描可用的设备和Linux启动

​	现在，我们可能会使用上一个阶段准备好的shell环境或者是已经确定的脚本立刻启动我们按照预设方式规定好的启动流程去驱动我们的内核。对于比较死板的ARM Tag方式是如下的：

- **ATAG 构造**：通过函数如 `setup_bootargs()` 构建包括 `ATAG_CORE`、`ATAG_MEM`、`ATAG_CMDLINE`、`ATAG_INITRD2` 的链表结构。
- **加载 kernel/initrd**：依据 `bootcmd`，通过 `load` 命令从 flash/SD/TFTP 加载 `zImage` 或 `uImage` 和可选 initrd。
- **执行启动指令**：使用 `bootm` 或 `bootz`，将内核跳转给 CPU；参数传递为预设的 machine type 和 ATAG list 指针（r0=0, r1=machine type, r2=ATAG 地址）。

Linux boot code 收到参数后：

- 解析 ATAG list，完成 Memory、Command Line、initrd 等配置。
- 初始化硬件子系统、挂载 initrd 并启动用户空间的 `init` 程序。

​	当然，如果是设备树，我们就把满足fdt格式的二进制文件所在的地址告诉我们的内核进行解析即可。

## 有设备树的UBoot启动流程

​	其实很类似，中间多了加载设备树fdt的环节，这里再说一次：

### CPU上电到准备潜在的重定向

​	我们的板子在CPU上电之后，就应当跳转到我们默认的存储设备的地址上，在那里，我们期待那里放置着我们的中断向量表，这跟单片机（至少是笔者熟悉的STM32）是类似的，我们单片机上电也是跳转道我们的中断向量表的表头，一般而言，表头的第一个就是我们的RESET向量，他会跳转到我们的start code上。这里我们就准备开始我们的初始化流程。

​	现在，我们的CPU执行流正在跟我们的内部片上的ROM进行交互（读写），我们利用这一部分空间完成必要的**低级初始化**（时钟、PLL、SRAM），并读取映像到 SRAM 或其他低端内存中。现在，我们的空间被进一步的增大了。

​	如果我们的板子上存在第二阶段启动（比如说我们的SoC RAM实在少的可怜），这个时候我们会在SPL中进一步初始化我们的DRAM，并加载主 U-Boot 镜像至 DRAM 中。SPL 通常不会执行重定位。这是后面的UBoot自己动手做的。SPL 加载完后跳转到主 U-Boot（入口通常为 `_start` 或 `board_init_f`），开始完整程序流程。

​	现在，板子的基本的功能都已经准备就绪了，下一步就是进一步初始化UBoot的功能，进一步开启板子上的高级外设功能。

​	我们在开启更多的RAM之后，就要准备初始化更多的硬件，准备为一部分自己后续启动环境运行和Linux内核的加载准备好环境。所以，我们要准备做代码的重定位问题。但是做重定位之前，我们要做一些准备。这也就是大名鼎鼎的board_init_f阶段，他按照一定的顺序依次调用重定向前需要做的工作，比如说：

- 初始化硬件（UART、缓存、定时器、DDR controller）
- 设置全局数据 `gd`（Global Data）
- 为重定位设定目标地址（基于 `CONFIG_SYS_RELOCATE_ADDR`、`CONFIG_SYS_TEXT_BASE`）

### 重定位代码段和uboot搬移

​	我们首先看看是否有必要进行搬移：
​	 利用 `ADR/ADR` + `LDR` 指令判断是否已在目标地址运行。

```
adr r0, _start
ldr r1, _TEXT_BASE
cmp r0, r1
bne proceed          ; 若不同，则需要重定位
```

​	`memcpy(_reloc_start, _text, _text_size)`，将 `.text` 副本移动到高端 DRAM，避免原始段成为通用内存。这样的话就可以释放和归并通用内存。

​	下一步就是填充和修正我们的重定位修正表，编译时启用 `-pie` 和自动生成 `.rela.dyn` 区段，runtime 利用 fixup table 修正绝对引用的代码和数据地址，**随后我们跳转到新位置并重建栈/GD**，跳转至重定向后的代码入口，设置新的 stack pointer、全局数据指针 `gd->relocaddr`，并完成 BSS 清零、`.data` 拷贝等重定位后工作（现在BSS可用了）

 	到这里，我们有一个不同，就是我们可以加载我们的设备树而不是硬耦合我们的设备描述代码段。

- U-Boot 支持多种加载 DTB 方式：**嵌入式** (`OF_EMBED`)、**外部 DTB 文件** (`OF_SEPARATE`)、**运行时动态加载** (`OF_BOARD` / `BLOBLIST`) 
- 加载后 U-Boot 会使用 `fdt` 命令在 DTB 中注入实际硬件信息（如 RAM 尺寸、kernel bootargs、MAC 地址等）来“tweak” DTB 。

### 执行重定向后的完全初始化逻辑：board_init_r

1. **board_init_r() 阶段**
    已经迁移到 DRAM，U-Boot 开启 rootfs memory pool、并初始化存储、网络、串口、USB 等设备，同时准备环境变量（`bootcmd`、`bootargs`、`fdtcontroladdr`）。
2. **`fdt` 命令调整**
    — 在交互命令下可用 `fdt print/set/move` 调整 DTB 属性；
    — 可通过脚本或保存脚本（`cmd_custom`）来自动修改，以支持动态设备需求 。

### 启动我们的Linux内核

1. **加载镜像**
    根据 `bootcmd` 脚本，从指定设备读取 kernel (`zImage` 或 `uImage`)、initrd（如果有）、以及 DTB 文件到内存指定位置（通过 `fdtcontroladdr` 环境变量指定地址）。
2. **执行 boot 命令**
    使用类似 `booti ${kernel_addr} - ${fdt_addr}` 或 `bootz` 的命令，并将 `r2` 指向 DTB 的物理地址（`r0=0`，`r1=machine type`）。
3. **跳转给内核**
    控制权交由 Linux kernel，kernel 会读取 `r2`，通过 magic 判断这是 DTB 而非 ATAG，并解析其内部结构 。

#### Linux自己做的事情

- **解析设备树**：kernel 在 `setup_arch()` 中调用 `unflatten_device_tree()`，解包 DTB，构建硬件节点树并扫描 `/chosen`, `/aliases` 等。
- **教育设备**：使用 DTB 中提供的信息驱动硬件初始化、IRQ、GPIO、bus、内存等结构。
- **启动 init**：构建完硬件环境后，挂载 initrd rootfs，并执行用户空间 init 进程。

------

## 📊 总结流程对照

```
ROM → SPL → U-Boot pre-reloc (.text/data in FLASH)
    ↳ relocate_code() → copy to DRAM, fix addresses
           ↳ post-reloc (board_init_r)
                 ↳ load and patch DTB (fdt)
                 ↳ load kernel + dtb + initrd
                 ↳ run bootz/booti → r2 = DTB ptr
                      ↳ Linux start → parse DTB → hw init → userspace
```