# 嵌入式通信协议学习——SPI篇

## 前言

​	在我们接触过了IIC之后，使用SPI也不会变得特别的费事，他跟其他的通信协议还是非常的类似的。下面我们就来深入的理解一下我们的SPI协议。

## 什么是SPI

​	SPI（Serial Peripheral Interface，串行外设接口）是一种由摩托罗拉公司在20世纪80年代初提出的同步串行通信协议，广泛应用于微控制器（MCU）与外设之间的数据传输。其主要特点是**高速、全双工、主从结构，适用于短距离、高速率的数据交换**，可以看到他跟我们的IIC差距不小的，IIC比起来速度会稍微弱一些，支持的力度也是半双工。

​	对于SPI的通信中，通常涉及四条信号线（注意，我们的讨论中没有VCC和GND，但是不代表没有）

- **MOSI（Master Out Slave In）**：主设备输出，从设备输入。
- **MISO（Master In Slave Out）**：主设备输入，从设备输出。
- **SCLK（Serial Clock）**：时钟信号，由主设备生成。
- **SS/CS（Slave Select/Chip Select）**：片选信号，用于选择特定的从设备，通常为低电平有效。

​	SPI这个通信协议跟我们的IIC一样，也是主从模式的通信，但是跟IIC不同的是，SPI下只能由一个主设备，一个或多个从设备（这个无所谓）。提供时钟的为主设备（Master），接收时钟的设备为从设备（Slave），所有针对SPI接口的读写操作，**都是由主设备发起。当存在多个从设备时，通过各自的片选信号进行管理。**

## SPI的四种工作模式

​	SPI的数据传输协议在物理特性上还是非常的灵活的。我们的数据传输由**时钟极性（CPOL）**和**时钟相位（CPHA）**两个关键参数定义，共同决定数据的采样和锁存时机

1. **CPOL（时钟极性）**
   - **CPOL=0**：时钟空闲时为低电平。
   - **CPOL=1**：时钟空闲时为高电平。
2. **CPHA（时钟相位）**
   - **CPHA=0**：数据在时钟的第一个边沿（上升沿或下降沿）采样。
   - **CPHA=1**：数据在时钟的第二个边沿采样。

四种模式组合如下：

- **模式0**：CPOL=0，CPHA=0 → 数据在时钟上升沿采样。
- **模式1**：CPOL=0，CPHA=1 → 数据在时钟下降沿采样。
- **模式2**：CPOL=1，CPHA=0 → 数据在时钟下降沿采样。
- **模式3**：CPOL=1，CPHA=1 → 数据在时钟上升沿采样。

## **SPI的通信通信流程**

​	基本上都是按照——初始化通信——交换数据——完成通信的流程来的。

1. **初始化总线**
   主设备配置时钟极性、相位、数据顺序和时钟频率（需符合从设备要求）。
2. **选择从设备**
   主设备拉低目标从设备的片选信号（SS），激活通信。
3. **数据传输**
   - 主设备通过MOSI线逐位发送数据，同时从设备通过MISO线返回数据。
   - 每个时钟周期传输一位数据，实现全双工通信（同时发送和接收）。
   - 数据长度通常为8位或16位，具体取决于设备要求。
4. **结束通信**
   传输完成后，主设备拉高片选信号（SS），释放总线。若需连续传输，可保持SS为低电平并继续发送数据。

举个例子，假设主设备向从设备发送字节`0x55`（二进制`01010101`），并接收从设备返回的字节`0xAA`（二进制`10101010`），工作模式为模式0（CPOL=0，CPHA=0）：

1. 主设备拉低SS信号，选中从设备。
2. 主设备生成时钟信号（空闲时为低电平）。
3. 主设备在时钟上升沿从MOSI输出数据位（MSB先发）：
   - 第1个上升沿发送`0`（最高位），同时读取MISO上的`1`（最高位）。
   - 依次传输后续位，8个时钟周期后完成一字节交换。
4. 主设备拉高SS信号，结束本次传输。

## HAL库的SPI API

### 1. 阻塞模式（Polling Mode）

在阻塞模式下，函数在数据传输完成前会一直等待，适用于简单、对实时性要求不高的场合。

- `HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)`
   发送数据。
- `HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)`
   接收数据。
- `HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)`
   同时发送和接收数据。

这些函数在调用时会阻塞程序，直到数据传输完成或超时。

### 2. 中断模式（Interrupt Mode）

中断模式通过中断机制实现非阻塞通信，适用于对实时性有一定要求的应用。

- `HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)`
   启动发送数据的中断传输。
- `HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)`
   启动接收数据的中断传输。
- `HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)`
   启动同时发送和接收数据的中断传输。

在使用中断模式时，需要实现相应的回调函数，如`HAL_SPI_TxCpltCallback()`、`HAL_SPI_RxCpltCallback()`和`HAL_SPI_TxRxCpltCallback()`，以处理传输完成后的操作。

### 3. DMA模式（Direct Memory Access Mode）

DMA模式利用DMA控制器实现数据的高速传输，适用于大量数据的传输，减轻CPU负担。

- `HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)`
   启动发送数据的DMA传输。
- `HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)`
   启动接收数据的DMA传输。
- `HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)`
   启动同时发送和接收数据的DMA传输。

使用DMA模式时，也需要实现相应的回调函数，如`HAL_SPI_TxCpltCallback()`、`HAL_SPI_RxCpltCallback()`和`HAL_SPI_TxRxCpltCallback()`，以处理传输完成后的操作。

## Reference

https://www.nxp.com/docs/en/application-note/AN991.pdf