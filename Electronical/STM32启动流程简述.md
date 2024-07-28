# STM32启动流程简述

​	下面我们要阐述的是STM32的启动原理。

## 上电时

​	我们的STM32一经上电，他会跟CPU上电的行为一致，也就是跳转到一个固定的地址。我们的STM32也是一样，对于不同的boot选择，他会跳转到不同的地址。这就跟启动模式的三种方式很有关系：

| BOOT0 | BOOT1 | 启动模式   | 0x00000000的映射地址 | 0x00000004的映射地址 |
| ----- | ----- | ---------- | -------------------- | -------------------- |
| 0     | x     | 内部FLASH  | 0x08000000           | 0x08000004           |
| 1     | 1     | 内部SRAM   | 0x20000000           | 0x20000004           |
| 1     | 0     | 系统存储器 | 0x1FFFF000           | 0x1FFFF004           |

​	也就是说，选择不同的boot引脚本质上就是在选择不一样的跳转地址，无论如何，我们要做的，就是在选定我们的特定的跳转地址后，在这些地址上排列我们之后的指令。

## 启动文件分析

​		这一场串的文件很大，也是一份arm汇编文件，为此，为了理解这份文件，我们来看看一些简单的汇编标识符：

| 指令名称      | 作用                                                         |
| ------------- | ------------------------------------------------------------ |
| EQU           | 相当于#define给常量取名称                                    |
| AREA          | 汇编一段全新的段                                             |
| ALIGN         | 编译器对指令或者数据的存放地址进行对齐。一般需要跟一个立即数，缺省表示四字节对齐。不过要注意的是：**这个并不是arm汇编指令，而是编译器的内置指令** |
| SPACE         | 分配内存空间                                                 |
| PRESERVE8     | 当前文件堆栈需要按照八字节对齐                               |
| THUMB         | 表示向后兼容THUMB指令（详细可以查询ARM状态和THUMB状态）      |
| EXPORT        | 声明导出这个符号给外边文件用                                 |
| IMPORT        | 声明这个符号来源于外面                                       |
| DCD           | 以字节为单位分配内存要求四字节对齐并且要求初始化这些内存     |
| PROC          | 子程序的开始，要求以ENDP成对出现                             |
| WEAK          | 这表示若定义如果外部文件声明的一个符号，则优先使用外部文件定义的符号。如果外部文件没有定义这个符号也不会出错。**要注意的是这也不是arm的汇编指令而是编译器的内置指令** |
| LDR           | 从存储器加载一个字                                           |
| BLX           | 跳转到寄存器给出的地址，并且根据寄存器的LSE确定处理器的状态，还要把跳转前的下条指令地址保存到LR（实际上就是call） |
| BX            | 跳转到由寄存器或者标号给出的地址不用返回                     |
| B             | 跳转到一个标号                                               |
| IF ELSE ENDIF | 汇编条件分支语句跟C语言类似                                  |
| END           | 文件结束                                                     |

​	那我们现在尝试着手分析这个文件

> 文件名称：startup_stm32f103xe.s

```
Stack_Size      EQU     0x00000400						# 声明一个栈大小的宏

                AREA    STACK, NOINIT, READWRITE, ALIGN=3 # STACK栈区域，不初始化，可读可写，对齐3字节
Stack_Mem       SPACE   Stack_Size						# 表达栈的大小是1024B，也就是1KB大小
__initial_sp											
                                                  
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200						# 堆大小为512B

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3  # HEAP堆区域，不初始化，可读可写，对齐3字节	
__heap_base											  # HEAP起始地址
Heap_Mem        SPACE   Heap_Size						# HEAP区域
__heap_limit										  # HEAP终止地址

                PRESERVE8								# 这两条看上面的说明：当前文件堆栈需要按照八字节对齐
                THUMB									# THUMB指令

; 上面的区域划分了区域，下面开始排布中断向量表，他在0地址处（数据段）

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY			# 中断向量表安排在0地址处
                EXPORT  __Vectors					   # 下面的三个符号将会可见（被外面的使用）
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
# 具体含义如何不是这里的侧重点
__Vectors       DCD     __initial_sp               ; Top of Stack	
                DCD     Reset_Handler              ; Reset Handler	
;				... 省略了大量的中断向量
                DCD     DMA2_Channel4_5_IRQHandler ; DMA2 Channel4 & Channel5
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors			# 推导出我们的向量表的大小

                AREA    |.text|, CODE, READONLY			# 只读代码段，放在.text段上
                
; Reset handler	# 我们很关心这个
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                # __main函数，也是标准的C库函数，负责初始化堆栈（这里要求要连接到C库）
                IMPORT  __main
                # SystemInit()是一个库函数，在system_stm32f1xx.c中定义的
                IMPORT  SystemInit	# SystemInit贴在了下面
                # 先调用SystemInit
                LDR     R0, =SystemInit
                BLX     R0         
                # 再调用__main函数初始化
                LDR     R0, =__main
                BX      R0
                ENDP
                
; 省略了大量的handlers的弱定义
; ....
; ....
; 结束

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
# 有没有定义__MICROLIB?我们默认人没有定义，这样的化就是使用C库函数___main帮助我们完成初始化，
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                 # 我们正常走这里
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****

```

```
**
 * @brief Setup the microcontroller system
 * Initialize the Embedded Flash Interface, the PLL and update the 
 * SystemCoreClock variable.
 * @note This function should be used only after reset.
 * @param None
 * @retval None
 */
 # 简单来讲就是初始化Flash接口和初始化系统的时钟
void SystemInit (void)
{
 /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
 /* Set HSION bit */
 RCC->CR |= 0x00000001U;
 
 /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#if !defined(STM32F105xC) && !defined(STM32F107xC)
 RCC->CFGR &= 0xF8FF0000U;
#else
 RCC->CFGR &= 0xF0FF0000U;
#endif /* STM32F105xC */ 
 
 /* Reset HSEON, CSSON and PLLON bits */
 RCC->CR &= 0xFEF6FFFFU;
 
 /* Reset HSEBYP bit */
 RCC->CR &= 0xFFFBFFFFU;
 
 /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
 RCC->CFGR &= 0xFF80FFFFU;
 
#if defined(STM32F105xC) || defined(STM32F107xC)
 /* Reset PLL2ON and PLL3ON bits */
 RCC->CR &= 0xEBFFFFFFU;
 
 /* Disable all interrupts and clear pending bits */
 RCC->CIR = 0x00FF0000U;
 
 /* Reset CFGR2 register */
 RCC->CFGR2 = 0x00000000U;
#elif defined(STM32F100xB) || defined(STM32F100xE)
 /* Disable all interrupts and clear pending bits */
 RCC->CIR = 0x009F0000U;
 
 /* Reset CFGR2 register */
 RCC->CFGR2 = 0x00000000U; 
#else
 /* Disable all interrupts and clear pending bits */
 RCC->CIR = 0x009F0000U;
#endif /* STM32F105xC */
 
#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
 #ifdef DATA_IN_ExtSRAM
 SystemInit_ExtMemCtl(); 
 #endif /* DATA_IN_ExtSRAM */
#endif 
 
#ifdef VECT_TAB_SRAM
 SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
 SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif 
}
```

​	看完了：我们捋一下如何启动的：

## 启动流程分析

​	**上电：单片机根据选择的BOOT引脚跳转到相应的地址，开始取出堆栈指针的初始值（栈顶的初始值）和PC计数器的值（下一条指令在哪里）**

​	**这个PC值就是中断向量表的起始地址，也是复位程序的入口地址，接着跳转到复位程序入口处，初始向量表，然后设置时钟(SystemInit)，设置堆栈(__main函数)，最后跳转到C空间的main函数，即进入用户程序**

​	**实际上就是这样的简单。**