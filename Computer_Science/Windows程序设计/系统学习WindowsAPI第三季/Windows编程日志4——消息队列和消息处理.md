# Windows消息队列和消息处理（1）：基本的API和简单说明

​	Windows的窗口是使用一种叫做消息队列的机制进行处理的。您可以想象：我们的终端是一个嗷嗷待哺等待外部指令的窗口，自身有一个处理函数（是不是感到熟悉？我们自己曾经给lpWndProc成员赋值的处理函数就是这个处理函数）。外部鼠标，键盘或者是任何交互行为都期待同窗口进行交互。我们很容易想到，直接送到窗口是不现实的，窗口自己需要处理一小段时间，这些在处理事件而无暇顾及到事件到来时刻的消息，总不能直接丢弃吧！既然这些消息都是按照先来先到的方式试着进入窗口的，我们完全可以使用一个队列做缓冲。这个时候，生产者生产消息投送到消息队列中，窗口充当消费者拿取和处理消息。

​	这就是为什么常见的GUI框架采用事件循环和消息队列存储这些消息。

​	Windows给我们提供了大量的脚手架，在我们第一次CreateWindow或者是GetMessage的时候，我们实际上就会创建一个简单的消息队列维护消息存取。每个 GUI 线程最多有一个，所有系统输入（鼠标、键盘）、应用投递 (`PostMessage`) 的消息会排进这个队列。

​	消息队列有了，如何处理呢？一般而言，我们采用的是消息循环处理，Qt用的是`app.exec()`，这个时候我们会进入一个反复处理消息循环中：按照“从消息队列里取消息、处理消息、分发给窗口过程”的步骤反复执行。

​	这样事情就简单了，我们只需要关心三个部分的API

- `GetMessage` / `PeekMessage`：从队列里取消息。
- `TranslateMessage`：把按键类消息转为字符类消息。
- `DispatchMessage`：把消息分发给窗口过程（`WndProc`）。
- （可选）`IsDialogMessage`、`TranslateAccelerator`：处理对话框与快捷键。

### 最经典的消息循环

```c
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) 
{
    HWND hwnd = CreateWindowEx(
        0,                      // 扩展风格
        L"MyWindowClass",       // 注册过的窗口类名
        L"Demo Window",         // 窗口标题
        WS_OVERLAPPEDWINDOW,    // 样式
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    // 消息循环
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);   // 键盘消息转字符消息
        DispatchMessage(&msg);    // 分发给窗口过程
    }
    return (int)msg.wParam;       // WM_QUIT 的退出码
}
```

​	这个消息循环是最简单的消息循环，`GetMessage` 阻塞等待消息，CPU 占用低。收到 `WM_QUIT` 时返回 0，循环退出。

### 带加速键和对话框支持的循环

```c
MSG msg;
HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MAINACCEL));
HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), hwnd, DlgProc);

while (GetMessage(&msg, NULL, 0, 0)) {
    if (hDlg && IsDialogMessage(hDlg, &msg)) {
        continue; // 对话框内部消息已处理
    }
    if (hAccel && TranslateAccelerator(hwnd, hAccel, &msg)) {
        continue; // 快捷键消息已处理
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
```

- 常见于带菜单、快捷键、对话框的应用。

------

### 非阻塞 PeekMessage 循环

```c
bool running = true;
MSG msg;
while (running) {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { // 这个响应就会好
        if (msg.message == WM_QUIT) {
            running = false;
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (!running) break;

    // 无消息时，执行一帧逻辑/渲染
    UpdateGame(); // 这个往下都是Idel任务
    RenderFrame();
}
```

特点：

- 主动渲染，不依赖系统空闲时机。
- 注意加 `Sleep` 或 `MsgWaitForMultipleObjectsEx`，避免空转 100% CPU。

## 所以消息长啥样？

```c
typedef struct tagMSG {
    HWND   hwnd;
    UINT   message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD  time;     // 事件时间戳
    POINT  pt;       // 发生时的鼠标位置
    DWORD  lPrivate; // 系统内部使用
} MSG;
```

常见“**投递（Posted）**”消息：

- 输入：`WM_MOUSEMOVE / WM_LBUTTONDOWN / WM_KEYDOWN ...`（输入管理器根据前台队列产生）
- 绘制：`WM_PAINT`（窗口无效区域 & 队列空闲时产生，可能被合并）
- 定时器：`WM_TIMER`（若创建 timer 未指定回调函数）
- 应用投递：`PostMessage`、`PostThreadMessage` 发的自定义消息

常见“**派发（Sent）**”消息（不入队）：

- `SendMessage` 发的绝大多数消息（同步调用目标窗口过程）
- 系统同步发出的布局/激活类消息（很多 `WM_*` 在系统内部采用 send 语义）

**合并（coalescing）**：例如连续的 `WM_MOUSEMOVE`、`WM_PAINT`、`WM_TIMER` 可能被合并，减少重复处理。

------

### GetMessage —— 阻塞式取消息的主力

```c
BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
```

- **阻塞**直到有符合过滤条件的消息。拿到后把它**从队列移除**并填入 `MSG`。
- 返回值：
  - **>0**：取到正常消息
  - **0**：取到 `WM_QUIT`（线程应退出消息循环）
  - **-1**：错误（参数非法等；极少见，但要判错）
- **过滤器**：
  - `hWnd`：仅取这个窗口的消息；常用传 `NULL`（取线程队列里所有窗口/线程消息）
  - `wMsgFilterMin/max`：按消息范围过滤（例如只取键盘消息）
- **重要**：`WM_QUIT` **不受** `hWnd` 和范围过滤影响；一旦线程队列里有了 `WM_QUIT`，`GetMessage` 会直接返回 0。
- **优先级**：输入类（鼠标/键盘）优先于普通投递消息；`WM_PAINT`、`WM_TIMER` 常在队列空闲或低优先阶段生成。

> 典型用法（标准 GUI 程序主循环）：

```c
MSG msg;
while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
// 退出清理
return (int)msg.wParam; // 通常 WM_QUIT 的 wParam
```

------

### PeekMessage —— 非阻塞取消息与“游戏循环”

```c
BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT min, UINT max, UINT remove);
```

- **不阻塞**：若无消息立即返回 FALSE；适合需要持续渲染/轮询的场景（游戏/实时 UI）。
- `remove`：
  - `PM_NOREMOVE`：**窥视**，不移除
  - `PM_REMOVE`：取出并移除
  - （历史上有 `PM_NOYIELD`；现代一般不用）
- 注意：
  - **忙等风险**：错误写法里 `while (PeekMessage(...)) { ... } // 紧接着渲染` 但没有 `WaitMessage`/`Sleep`，会 100% 占用一个 CPU 核心。
  - 与定时器/`WM_PAINT` 的合并/低优先级机制叠加，可能出现**饿死**现象（一直有输入就很难得到 `WM_PAINT`）。可在空闲时调用 `WaitMessage()` 或使用 `MsgWaitForMultipleObjectsEx` 等待“任意消息或句柄事件”。

> 常见“游戏循环”范式：

```c
MSG msg;
bool running = true;
while (running) {
    // 把队列消息处理干净
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) { running = false; break; }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (!running) break;

    // 无消息：做一帧渲染/更新
    TickFrame();

    // 小心空转；推荐：
    // WaitMessage();  // 等待下一条消息再醒（纯消息驱动）
    // 或用 MsgWaitForMultipleObjectsEx(..., QS_ALLINPUT, ...) 等待消息或自定义事件
}
```

------

### TranslateMessage —— 把按键变成字符

```c
BOOL TranslateMessage(const MSG *lpMsg);
```

- 作用：对**键盘类投递消息**（`WM_KEYDOWN / WM_SYSKEYDOWN`，以及死键相关）进行布局转换、组合键态分析，按当前键盘布局和修饰键状态，把它们“翻译”成**字符类消息**：
  - 生成并投递：`WM_CHAR / WM_SYSCHAR / WM_DEADCHAR / WM_SYSDEADCHAR / WM_UNICHAR` 等
  - **不改变**原消息；只是**可能额外投递**上述字符消息
- 返回值：非 0 表示“翻译过”（投递了字符消息）。实际编程常**忽略返回值**，照常调用。
- **不是快捷键/加速键**：快捷键翻译用 `TranslateAccelerator`；对话框的 Tab/Enter/Esc 行为用 `IsDialogMessage`。
- 与 IME：`TranslateMessage` 不处理 IME 复合文本；IME 相关由 `WM_IME_*` 和输入法承担。

------

### DispatchMessage —— 把消息交给窗口过程

```c
LRESULT DispatchMessage(const MSG *lpMsg);
```

- 根据 `lpMsg->hwnd` 找到该窗口的窗口过程（`WNDPROC`），**调用**它：

  ```c
  return CallWindowProc(actualWndProc, lpMsg->hwnd, msg, wParam, lParam);
  ```

- 若你的窗口过程不处理某些消息，应调用 `DefWindowProc` 交还系统默认行为（移动、最小化、命中测试、非客户区绘制等）。

- **对话框**：若先调用了 `IsDialogMessage(hwndDlg, &msg)` 且其返回 TRUE，说明对话框已经处理（焦点切换、默认按钮等），那就**不要**再调用 `DispatchMessage`。

------

### PostMessage / PostThreadMessage —— 异步投递

```c
BOOL PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL PostThreadMessage(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam);
```

- **立即返回，不等待**目标处理（异步）。消息进入**目标线程**的队列。
- `PostThreadMessage` 目标线程**必须已创建消息队列**（见 §1）；否则失败。
- 失败返回 `FALSE`，请 `GetLastError()`；常见原因：`HWND` 无效/已销毁、线程无消息队列、队列满（极端）。
- **跨线程传指针的坑**：`wParam/lParam` 只是整数位宽。**不要**跨线程传原始指针指向临时/线程私有内存；需要引用计数对象、拷贝数据或使用安全的跨线程封送。
- **顺序性**：对于**同一来源线程**向**同一目标线程**投递的普通 posted 消息，**FIFO**；但与输入/`WM_PAINT`/`WM_TIMER` 的优先级/合并会**交叉**。

> 结束主循环的方式：`PostQuitMessage(exitCode);`
>  该调用会向**当前线程**队列投递 `WM_QUIT`，使 `GetMessage` 返回 0。

------

### （对照）SendMessage —— 同步、可重入、容易卡死

```c
LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
```

- **同步**调用目标窗口过程，**直到对方处理完返回**。**不走队列**。
- **同线程**：本质上就是直接调用目标 `WndProc`；这意味着**可重入**——如果在此期间你的线程又进入了某种消息循环（如菜单跟踪、拖动等），会产生复杂的调用栈。
- **跨线程**：内核/USER32 通知目标线程执行该窗口过程，发送线程**阻塞等待**。若目标线程卡住或也在等你，容易**死锁**。
- 用法建议：跨线程沟通优先 `PostMessage/PostThreadMessage` + 自己的同步原语；确需同步时要非常小心避免等待环。

------

### 队列优先级、合并与“饿死”

- **优先级大致从高到低**：硬件输入（鼠标/键盘） > `SendMessage`（不在队列） > 普通 posted（应用） > `WM_PAINT`/`WM_TIMER`。
- **合并**：
  - `WM_MOUSEMOVE`：连续移动只保留最新一条
  - `WM_PAINT`：多个无效区域合并成一次 `WM_PAINT`
  - `WM_TIMER`：同一 ID 的定时器可能合并
- **饿死现象**：若持续有高优先级输入，`WM_PAINT`/`WM_TIMER` 会延后。
   解决：空闲时 `WaitMessage()`、合理调度、分帧处理、降低输入频度（鼠标采样）等。

------

### 系统内部“模态循环”

- 菜单跟踪、窗口拖动/调整大小、滚动条跟踪、模态对话框等，系统会进入**内部的临时消息循环**。这时你的主循环没在跑，但消息仍会被处理。
- 这也是**重入**的来源之一（你的窗口过程在一次处理里又收到了其他消息）。
- 对话框建议：在主循环里调用 `IsDialogMessage`，或直接使用 `DialogBox`（它内部自带模态循环）。

