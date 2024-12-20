# README

​	这是一个超级入门的迷你小工程，目标是开发一个使用基于IIC的四阵脚OLED作为前端展示，使用DHT11作为后端传感器的入门级别项目。

​	本项目相对侧重软件模块设计，**目标是尽可能将使用的代码低耦合高内聚**，使用接口而不是跨层级通信。

## 可能需要的前置知识

1. 简单的OLED驱动原理
2. 简单的IIC通信知识
3. 基础的查手册能力
4. 相对稳固的C语言基础

不会没关系，我会详细说明的！

## 一种可能的器件方案

1. 一块可以通过厂家测试样例的 DHT11 （这个事情请在您购买 DHT11 的时候向卖家索要厂家测试样例）
2. 一块可以通过厂家测试样例的使用IIC协议通信的 OLED 屏幕（这个事情请在您购买 OLED 的时候向卖家索要厂家测试样例）
3. 一块STM32F103C8T6核心板（BTW，最好是ST厂家生产的，国产可以，后续会讲如何修改cfg文件通过上机校验码检查）

## 一种可能的开发环境配置

下面的三种配置三选一即可

1. 正常工作的STM32CubeMX + Keil5
2. 正常工作的STM32CubeMX + STM32CubeIDE
3. **PlatformIO + VSCode（笔者的选择）**

全程我们的环境配置使用的是第三个，其他环境配置请按照自己的经验酌情修改！

## 一种可能的使用的开发框架

1. HAL库即可
2. （有爹使用标准库的话，我选择最高级别的Solute）