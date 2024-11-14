# 从0开始的STM32库8 串口通信（II）

## 在开始理解底层原理之前，我们先尝试一下

​	现在我们综合一下，要求完成如下的事情：

> 在主程序中存在一个flag变量描述当前有没有嗯下按钮，当摁下时，打印“finishing flip!”字样，没有的话要求每间隔一秒输出输出Loop is working...，当然，摁扭嗯下的时候，要求打印日志You pressed a key, with led toggled once!，以及反转小灯状态一次！

​	你的程序效果在串口软件如下：

![image-20241106080028959](C:\Users\陈冠豪\AppData\Roaming\Typora\typora-user-images\image-20241106080028959.png)

## 怎么做

​	首先打开STM32CubeMX，配置好时钟之后，我们按照从0开始的STM32库——中断部分所谈到的那样，首先配置好按钮引脚中断的优先级（低于Systick的Time Base优先级），配置好LED的GPIO。下一步，就是开启我们的Connections->USART1（看官按照自己的做就行），选择好异步即可

![image-20241106080238575](C:\Users\陈冠豪\AppData\Roaming\Typora\typora-user-images\image-20241106080238575.png)

​	在生成的主程序中，写下这些逻辑：

```
static const char* buffer = "You pressed a key, with led toggled once!\n"; // 定义按键触发时发送的消息
char flip = 0; // 用于标记LED状态反转

// 外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t Pin){
  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin); // 切换LED状态
  HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), -1); // 通过UART发送按键触发消息
  flip = 1; // 设置flip标志，表示完成反转
}

/**
  * @brief  应用程序入口点。
  * @retval int
  */
int main(void)
{
  /* MCU配置部分--------------------------------------------------------*/

  /* 重置所有外设，初始化Flash接口和Systick定时器。 */
  HAL_Init();
  /* 配置系统时钟 */
  SystemClock_Config();
  /* 初始化所有已配置的外设 */
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  char* plain_buffer = "Loop is working...\n"; // 循环中定期发送的消息
  char* plain_buffer2 = "finishing flip!\n"; // 完成LED反转后发送的消息

  while (1)
  {
    // 发送周期性消息
    HAL_UART_Transmit(&huart1, (uint8_t*)plain_buffer, strlen(plain_buffer), -1); 
    HAL_Delay(1000); // 延时1秒

    if(flip){
      flip = 0; // 重置flip标志
      // 发送LED反转完成的消息
      HAL_UART_Transmit(&huart1, (uint8_t*)plain_buffer2, strlen(plain_buffer2), -1); 
    }
  }
}
```

​	程序很简单！

## 进一步理解

​		在HAL库，我们的串口通信是依靠一个叫做`UART_HandleTypeDef`的结构体进行的，这个方法内部配置了我们的通信约定，可以查看HAL为我们生成的代码：

```
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
}
```

​	我们可以看到生成的办法是：

> 首先初始化实际的USART实例，实际上我们使用的是USART1，那根据HAL库，就是我们的USART1这个定义的句柄。
>
> 下一步就是设置波特率。值得一提的是：这个设置不一定要遵循115200，实际上只要是双方约定的速率即可
>
> 下一个就是数据的字长，比如说我们这里就设置为8bit
>
> ...
>
> 设置好了之后。我们采用初始化的办法进行初始化

| 配置项                     | 可能的值                                                     | 说明                                     |
| -------------------------- | ------------------------------------------------------------ | ---------------------------------------- |
| `huart1.Instance`          | `USART1`, `USART2`, `USART3`, `UART4`, `UART5`, ...          | UART 外设实例选择                        |
| `huart1.Init.BaudRate`     | `9600`, `19200`, `38400`, `57600`, `115200`, `230400`, `460800`, `921600`, `1000000` | 波特率，决定每秒传输的数据位数           |
| `huart1.Init.WordLength`   | `UART_WORDLENGTH_8B`, `UART_WORDLENGTH_9B`                   | 数据字长，8位或9位数据                   |
| `huart1.Init.StopBits`     | `UART_STOPBITS_1`, `UART_STOPBITS_2`, `UART_STOPBITS_1_5`    | 停止位，决定每个数据包的结束标志位       |
| `huart1.Init.Parity`       | `UART_PARITY_NONE`, `UART_PARITY_EVEN`, `UART_PARITY_ODD`    | 校验位，决定错误检测方式                 |
| `huart1.Init.Mode`         | `UART_MODE_TX_RX`, `UART_MODE_TX`, `UART_MODE_RX`            | 数据传输模式，支持发送、接收或两者都支持 |
| `huart1.Init.HwFlowCtl`    | `UART_HWCONTROL_NONE`, `UART_HWCONTROL_RTS`, `UART_HWCONTROL_CTS`, `UART_HWCONTROL_RTS_CTS` | 硬件流控制，决定是否启用流控制           |
| `huart1.Init.OverSampling` | `UART_OVERSAMPLING_8`, `UART_OVERSAMPLING_16`                | 过采样，决定波特率的采样精度             |

​	现在，我们调用HAL_UART_Init传递实际的参数来完成最后的初始化，`HAL_UART_Init` 函数负责初始化 STM32 的 UART 外设，配置通信参数，并确保外设能够正常工作。它包括硬件流控制、波特率、数据位、停止位等多个重要参数的配置，同时还考虑了回调函数的注册和低级硬件的初始化。

```
/**
  * @brief  Initializes the UART mode according to the specified parameters in
  *         the UART_InitTypeDef and creates the associated handle.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
  /* Check the UART handle allocation */
  if (huart == NULL)
  {
    return HAL_ERROR;  // 如果传入的 UART 句柄为空，返回错误状态
  }

  /* Check the parameters */
  if (huart->Init.HwFlowCtl != UART_HWCONTROL_NONE)
  {
    // 硬件流控制只适用于 USART1, USART2 和 USART3，因此需要检查是否是这些实例之一
    assert_param(IS_UART_HWFLOW_INSTANCE(huart->Instance));  // 通过宏检查 UART 是否为支持硬件流控制的实例
    assert_param(IS_UART_HARDWARE_FLOW_CONTROL(huart->Init.HwFlowCtl));  // 检查硬件流控制的参数是否合法
  }
  else
  {
    assert_param(IS_UART_INSTANCE(huart->Instance));  // 如果没有硬件流控制，则检查是否为有效的 UART 实例
  }

  // 校验 UART 字长是否合法
  assert_param(IS_UART_WORD_LENGTH(huart->Init.WordLength));  

#if defined(USART_CR1_OVER8)
  // 如果 MCU 支持 8 倍过采样，则需要验证过采样设置是否合法
  assert_param(IS_UART_OVERSAMPLING(huart->Init.OverSampling));  
#endif /* USART_CR1_OVER8 */

  // 检查 UART 的当前状态是否为重置状态
  if (huart->gState == HAL_UART_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    huart->Lock = HAL_UNLOCKED;  // 解锁 UART 资源，准备初始化

    #if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
      // 如果启用了回调函数注册机制，则调用默认回调函数初始化
      UART_InitCallbacksToDefault(huart);

      // 检查是否设置了用户的初始化回调函数，如果没有则使用默认回调
      if (huart->MspInitCallback == NULL)
      {
        huart->MspInitCallback = HAL_UART_MspInit;  // 使用默认的硬件初始化回调
      }

      /* Init the low level hardware */
      // 调用用户的回调函数进行硬件初始化
      huart->MspInitCallback(huart); 
    #else
      /* Init the low level hardware : GPIO, CLOCK */
      // 如果没有启用回调函数，则调用默认的 HAL_UART_MspInit 进行硬件初始化
      HAL_UART_MspInit(huart);  
    #endif /* (USE_HAL_UART_REGISTER_CALLBACKS) */
  }

  // 更新 UART 状态为忙碌状态，表示正在初始化
  huart->gState = HAL_UART_STATE_BUSY;

  /* Disable the peripheral */
  // 禁用 UART 外设，防止在初始化过程中出现干扰
  __HAL_UART_DISABLE(huart);  

  /* Set the UART Communication parameters */
  // 根据配置结构体中的参数，设置 UART 的通信参数
  UART_SetConfig(huart);  // 设置波特率、数据位、停止位、校验等配置

  /* In asynchronous mode, the following bits must be kept cleared:
     - LINEN and CLKEN bits in the USART_CR2 register,
     - SCEN, HDSEL and IREN bits in the USART_CR3 register. */
  // 在异步模式下，清除 USART_CR2 和 USART_CR3 寄存器中某些特定位，以确保 UART 正常工作
  CLEAR_BIT(huart->Instance->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));  // 禁用 LIN 和时钟
  CLEAR_BIT(huart->Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));  // 禁用智能卡、半双工和红外功能

  /* Enable the peripheral */
  // 启用 UART 外设，使能 UART 的发送和接收功能
  __HAL_UART_ENABLE(huart);  

  /* Initialize the UART state */
  // 初始化 UART 状态，表示 UART 初始化完成
  huart->ErrorCode = HAL_UART_ERROR_NONE;  // 错误代码清零
  huart->gState = HAL_UART_STATE_READY;  // 更新为就绪状态
  huart->RxState = HAL_UART_STATE_READY;  // 接收状态更新为就绪

  return HAL_OK;  // 返回成功状态，表示初始化完成
}
```

​	HAL_UART_Init首先进行的就是**参数检查**，他检查的是：

1. **`huart` 检查**： 首先，检查传入的 `huart` 指针是否为空。若为空，则返回 `HAL_ERROR`，表示初始化失败。
2. **硬件流控制检查**： 如果选择了硬件流控制（`HwFlowCtl != UART_HWCONTROL_NONE`），则需要验证 UART 是否为支持硬件流控制的外设（如 USART1、USART2 和 USART3）。通过 `assert_param(IS_UART_HWFLOW_INSTANCE(huart->Instance))` 宏检查实例是否合法。同时，还要检查硬件流控制参数是否合法（`IS_UART_HARDWARE_FLOW_CONTROL`）。
3. **其他配置项检查**： 校验数据字长（`WordLength`）、过采样（`OverSampling`）和 UART 实例是否有效。通过多个宏进行这些检查，确保配置项在硬件上是支持的。

​	下一步：**状态初始化**！，我们需要对UART做状态机的初始化：

- **`gState` 检查**： 如果 `huart->gState` 的状态是 `HAL_UART_STATE_RESET`，说明 UART 外设尚未初始化，需要进行初始化过程。否则，继续执行后续步骤。

- **锁定机制**： 初始化时，设置 `huart->Lock = HAL_UNLOCKED`，表示 UART 外设当前没有被锁定，可以进行配置。

- **回调函数注册（可选）**： 如果启用了回调函数注册（`USE_HAL_UART_REGISTER_CALLBACKS == 1`），会将回调函数设置为默认回调，并检查是否用户已经注册了初始化回调函数。如果没有，则使用默认的 `HAL_UART_MspInit` 作为初始化回调函数。

  如果没有启用回调，则直接调用 `HAL_UART_MspInit` 进行低级硬件初始化（如 GPIO 配置和时钟设置）。

​	现在我们来配置UART：

- **禁用 UART 外设**： 在进行配置之前，首先禁用 UART 外设，防止在配置过程中发生数据传输或接收。
- **配置通信参数**： 调用 `UART_SetConfig` 函数，设置 UART 的波特率、数据位长度、停止位数、校验方式等。这个函数会根据 `huart->Init` 中的配置项来设置相关寄存器。
- **清除无关功能**： 在异步模式下，清除一些不必要的功能（如 LIN、时钟、半双工、红外等），确保 UART 以标准模式运行。

​	关键的一步在于：**启用 UART 外设**后就要更新状态到可用，然后结束函数调用

- **启用 UART**： 配置完成后，通过 `__HAL_UART_ENABLE(huart)` 启用 UART 外设，开始实际的通信工作。

- **更新状态**： 最后，重置 `ErrorCode` 为 `HAL_UART_ERROR_NONE`，表示没有发生错误，并将 `gState` 和 `RxState` 更新为 `HAL_UART_STATE_READY`，表示 UART 已准备好进行数据收发。

- **成功返回**： 如果所有步骤都成功完成，返回 `HAL_OK`，表示初始化成功。

## HAL_UART_Transmit

​	我们刚刚使用到的是这个函数：`HAL_UART_Transmit` 函数，用于通过 UART 外设发送数据，采用阻塞模式（即函数会一直等待直到数据发送完成或超时）。它接受一个数据缓冲区指针、数据大小和超时设置作为输入参数。传输过程中，函数会不断检查 TXE（发送数据寄存器空标志）和 TC（传输完成标志）来控制数据的发送。

```
/**
  * @brief  Sends an amount of data in blocking mode.
  * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 provided through pData.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (u8 or u16 data elements).
  * @param  Size  Amount of data elements (u8 or u16) to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint8_t  *pdata8bits;  // 指向 8 位数据的指针
  uint16_t *pdata16bits; // 指向 16 位数据的指针
  uint32_t tickstart = 0U; // 用于超时管理的时间戳

  /* 检查是否有传输过程正在进行 */
  if (huart->gState == HAL_UART_STATE_READY)
  {
    // 如果传入的数据为空或者数据大小为0，则返回错误
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* 处理锁定 */
    __HAL_LOCK(huart);  // 锁定 UART 句柄，防止多线程环境下的竞争

    huart->ErrorCode = HAL_UART_ERROR_NONE;  // 初始化错误代码
    huart->gState = HAL_UART_STATE_BUSY_TX;  // 将 UART 状态设置为忙碌，表示正在进行传输

    /* 初始化 tickstart，用于超时管理 */
    tickstart = HAL_GetTick();  // 获取当前的时间戳，用于计算超时

    huart->TxXferSize = Size;  // 设置要发送的数据总量
    huart->TxXferCount = Size; // 设置剩余要发送的数据量

    /* 如果是9位数据并且没有启用校验，则需要将数据处理为 uint16_t 指针 */
    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      pdata8bits  = NULL;  // 对于 9 位数据，8 位数据指针为空
      pdata16bits = (uint16_t *) pData;  // 数据指针被转换为 16 位指针
    }
    else
    {
      pdata8bits  = pData;  // 否则，8 位数据指针指向传入的数据
      pdata16bits = NULL;   // 16 位数据指针为空
    }

    /* 解锁处理 */
    __HAL_UNLOCK(huart);  // 解锁 UART 句柄，允许其他操作

    /* 开始数据传输 */
    while (huart->TxXferCount > 0U)
    {
      // 等待 TXE 标志（发送数据寄存器为空），直到超时或成功
      if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;  // 如果超时，则返回超时错误
      }

      // 如果是 9 位数据，则将数据写入数据寄存器时需要将其作为 16 位处理
      if (pdata8bits == NULL)
      {
        huart->Instance->DR = (uint16_t)(*pdata16bits & 0x01FFU);  // 将 16 位数据的低 9 位写入数据寄存器
        pdata16bits++;  // 移动到下一个数据
      }
      else
      {
        huart->Instance->DR = (uint8_t)(*pdata8bits & 0xFFU);  // 将 8 位数据写入数据寄存器
        pdata8bits++;  // 移动到下一个字节
      }

      huart->TxXferCount--;  // 递减待发送数据计数
    }

    // 等待直到 TC（传输完成）标志被置位，表示所有数据已成功发送
    if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;  // 如果超时，则返回超时错误
    }

    /* 传输结束，恢复 UART 状态为就绪 */
    huart->gState = HAL_UART_STATE_READY;

    return HAL_OK;  // 返回成功状态，表示数据已成功发送
  }
  else
  {
    return HAL_BUSY;  // 如果 UART 正在忙碌，则返回忙碌状态
  }
}
```

​	也就是做下面这个顺序的检查：

1. **状态检查**： 函数首先检查 UART 是否处于就绪状态（`HAL_UART_STATE_READY`）。如果 UART 正忙，则返回 `HAL_BUSY`，否则开始初始化传输。
2. **参数检查**： 如果数据缓冲区为空或者传输大小为零，则返回错误。
3. **锁定 UART 资源**： 使用 `__HAL_LOCK(huart)` 锁定 UART 资源，以避免在多任务环境下同时访问同一个 UART 外设。
4. **设置初始状态**： 设置错误码为 `HAL_UART_ERROR_NONE`，并将 UART 的状态设置为 `HAL_UART_STATE_BUSY_TX`，表示当前正在进行数据传输。
5. **数据指针设置**： 如果配置了 9 位数据传输并且未启用校验，则数据以 `uint16_t` 形式进行处理（每个数据元素是 16 位），否则按 `uint8_t` 数据处理。
6. **开始传输**： 在数据传输过程中，函数进入一个循环，依次检查 `TXE` 标志是否已置位，若已置位则将数据写入 `DR` 寄存器。数据可以是 8 位或 16 位，具体取决于配置。
7. **超时管理**： 如果在传输过程中没有及时收到 `TXE` 或 `TC` 标志，且超时，函数会返回 `HAL_TIMEOUT`。
8. **完成传输**： 在所有数据发送完成后，检查 `TC` 标志，确认数据传输完全结束，并恢复 UART 状态为就绪（`HAL_UART_STATE_READY`）。
9. **返回状态**： 如果一切顺利，函数返回 `HAL_OK`，否则返回超时或错误状态。

## HAL_UART_Receive

​	笔者在这里没有设计实验，这是因为这个函数笔者没咋用过，后面我们会进一步介绍更加高级的（基于中断和DMA的通信！）：`HAL_UART_Receive` 函数是阻塞的接受！用于通过 UART 接收指定数量的数据，采用阻塞模式（即直到数据接收完成或超时）。函数等待接收缓冲区的数据，并将其存储到提供的缓冲区中。函数会根据配置的字长和是否启用了校验来决定如何处理接收到的数据。

```
/**
  * @brief  以阻塞模式接收一定数量的数据。
  * @note   当 UART 未启用校验（PCE = 0），且字长配置为 9 位（M1-M0 = 01）时，
  *         接收到的数据将作为一组 u16 来处理。在这种情况下，Size 参数应表示
  *         pData 中的 u16 数据数量。
  * @param  huart 指向 UART_HandleTypeDef 结构体的指针，该结构体包含
  *               配置的 UART 模块的信息。
  * @param  pData 指向数据缓冲区的指针（可以是 u8 或 u16 数据元素）。
  * @param  Size  要接收的数据元素数量（u8 或 u16）。
  * @param  Timeout 超时时间，单位为毫秒。
  * @retval HAL 状态
  */
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint8_t  *pdata8bits;  // 用于处理 8 位数据的指针
  uint16_t *pdata16bits; // 用于处理 16 位数据的指针
  uint32_t tickstart = 0U; // 用于超时管理的时间戳

  /* 检查是否已有接收过程正在进行 */
  if (huart->RxState == HAL_UART_STATE_READY)
  {
    // 检查参数是否有效：pData 为空或 Size 为 0
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* 锁定 UART，防止并发访问 */
    __HAL_LOCK(huart);

    huart->ErrorCode = HAL_UART_ERROR_NONE;  // 重置错误码
    huart->RxState = HAL_UART_STATE_BUSY_RX;  // 将 UART 状态设置为正在接收数据
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;  // 设置为标准接收类型

    /* 开始超时管理，记录当前时间戳 */
    tickstart = HAL_GetTick();

    huart->RxXferSize = Size;  // 设置要接收的总数据量
    huart->RxXferCount = Size; // 设置剩余要接收的数据量

    /* 如果启用了 9 位数据传输且没有校验，处理为 16 位数据 */
    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      pdata8bits  = NULL;  // 不使用 8 位指针
      pdata16bits = (uint16_t *) pData;  // 使用 16 位指针处理 9 位数据
    }
    else
    {
      pdata8bits  = pData;  // 使用 8 位指针处理 8 位数据
      pdata16bits = NULL;   // 不使用 16 位指针
    }

    /* 解锁 UART，允许其他操作 */
    __HAL_UNLOCK(huart);

    /* 循环等待接收数据，直到所有数据接收完成 */
    while (huart->RxXferCount > 0U)
    {
      // 等待 RXNE 标志位被置位（数据可用）
      if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;  // 超时，返回超时错误
      }

      // 如果是 9 位数据，处理为 16 位数据
      if (pdata8bits == NULL)
      {
        *pdata16bits = (uint16_t)(huart->Instance->DR & 0x01FF);  // 从数据寄存器读取 9 位数据
        pdata16bits++;  // 移动到下一个数据位置
      }
      else
      {
        // 根据字长和是否启用校验来选择数据的处理方式
        if ((huart->Init.WordLength == UART_WORDLENGTH_9B) || 
            ((huart->Init.WordLength == UART_WORDLENGTH_8B) && (huart->Init.Parity == UART_PARITY_NONE)))
        {
          *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);  // 从数据寄存器读取 8 位数据
        }
        else
        {
          *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x007F);  // 从数据寄存器读取 7 位数据（排除校验位）
        }
        pdata8bits++;  // 移动到下一个字节
      }

      huart->RxXferCount--;  // 减少剩余接收的数据量
    }

    /* 接收完成后，将 UART 状态恢复为 READY */
    huart->RxState = HAL_UART_STATE_READY;

    return HAL_OK;  // 返回成功
  }
  else
  {
    return HAL_BUSY;  // 如果 UART 正在忙碌，则返回 HAL_BUSY
  }
}

```

1. **状态检查**： 函数首先检查 UART 的接收状态（`huart->RxState`），确保没有正在进行的接收过程。如果 UART 正在接收数据，则返回 `HAL_BUSY`，否则继续执行。
2. **参数检查**： 如果数据缓冲区为空或者传输大小为零，函数返回 `HAL_ERROR`。
3. **锁定 UART 资源**： 使用 `__HAL_LOCK(huart)` 锁定 UART，防止其他任务同时访问该资源。
4. **初始化接收状态**： 清除错误代码，并将 UART 的接收状态设置为 `HAL_UART_STATE_BUSY_RX`，表示正在进行数据接收。同时初始化超时管理的时间戳 `tickstart`。
5. **数据指针设置**： 如果配置为 9 位数据传输且没有启用校验，数据指针会被处理为 `uint16_t` 类型，否则按 `uint8_t` 类型处理数据。
6. **开始接收数据**： 在接收过程中，函数进入一个循环，检查 `RXNE` 标志是否被置位（表示数据已准备好），然后读取数据并存储到缓冲区。如果是 9 位数据，则从数据寄存器读取 9 位数据；否则，根据数据位长（8 位或 7 位）读取相应的数据。
7. **超时管理**： 如果接收过程中的 `RXNE` 标志未在指定超时时间内被置位，函数会返回 `HAL_TIMEOUT`。
8. **完成接收**： 在接收到所有数据后，UART 状态被恢复为 `HAL_UART_STATE_READY`，表示接收过程已完成。
9. **返回状态**： 如果接收过程成功完成，函数返回 `HAL_OK`，否则返回超时或错误状态。