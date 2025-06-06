# ARM Cortex M架构手册阅读

## 前言

​	笔者另一个阅读的是AMD架构的手册阅读：[AMD架构简单读书笔记1-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/145411243)，这里则是ARM CortexM3架构手册的阅读。这个架构广泛的运用到了经典的STM32F103系列的单片机。笔者的阅读动机也在于此。

文档指引：

- [ARMv7-M架构手册](https://documentation-service.arm.com/static/5f8fef3af86e16515cdbf816)
- [ARM-Cortex M3手册下载](https://documentation-service.arm.com/static/5f2286f2f3ce30357bc28b2a?token=)

​	笔者的阅读资料从这里来，同时，非常感谢文档：[Cortex-M4，M3，M0权威指南（中英文版） - STM32F429 - 硬汉嵌入式论坛 - Powered by Discuz! (armbbs.cn)](https://www.armbbs.cn/forum.php?mod=viewthread&tid=96973)，这里的Cortex-M3权威指南是打开了笔者ARM架构体系理解的一本好书！

## 关于处理器

​	Cortex-M3 是一款**低功耗处理器，具有门数少、中断延迟低和调试成本低等特点。**它适用于需要最佳中断响应功能的深度嵌入式应用。（也就是说，Cortex-M3是一个注重实时性的，用于嵌入式领域的CPU）

## 关于编程模型

​	这个是Chapter3的内容，笔者短暂的跳过了第一张后半部分的和第二章的内容。等有需要了再回来阅读。

​	首先需要注意的是，Cortex-M3实际上是采用的是ARMv7-M的架构。

### 操作和执行模式

​	Cortex-M3 处理器支持线程和处理程序操作模式，并可在 Thumb 或调试操作状态下运行。此外，处理器可以通过在特权或非特权模式下执行代码来限制或排除对某些资源的访问。这件事情是ARMv7-M约束的，具体可以参考ARMv7-M的文档，960多页，链接已经再最上面给出了。

#### 操作模式

导致处理器进入线程或处理程序模式的条件如下：

- 处理器在复位时或由于**异常返回而进入线程模式**。特权和非特权代码可以在线程模式下运行。
- 处理器由于异常而进入处理程序模式。所有代码在处理程序模式下都是特权的。

#### 操作状态

处理器可以在 Thumb 或调试状态下运行：

- Thumb 状态。这是运行 16 位和 32 位半字对齐 Thumb 指令的正常执行。
- 调试状态。这是处理器处于暂停调试状态。

#### 特权访问和用户访问

处理程序模式始终是特权模式。线程模式可以是特权模式，也可以是非特权模式。

