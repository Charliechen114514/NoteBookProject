# Windows编程日志——说一说经典的输入场景处理

## 键盘事件

​	我们在之前就接触了消息循环框架和消息队列的使用，我们后面的键盘事件处理，鼠标事件处理和定时器消息处理都是紧紧基于我们前面的阐述进一步继续的。

## 键盘捕获与展开

​	在最普通的场景下，我们通过 `WM_KEYDOWN`（捕获按键摁下的事件） 和 `WM_KEYUP` （捕获按键抬起的事件）消息捕获键盘事件。此时，Windows 会在 `wParam` 中传递虚拟键码（Virtual-Key Code），而在 `lParam` 中包含扫描码等附加信息。若要将虚拟键码转换为字符，可以使用 `ToUnicode` 或 `ToUnicodeEx`。为了获取当前的键盘状态，需要先调用 `GetKeyboardState`。

> 虚拟键码（Virtual Key Codes, VK_*) 是**一套用于识别键盘按键的标准编码**，它们在编程中扮演着至关重要的角色，特别是在处理键盘输入事件时。 这些键码是独立于硬件的，这意味着无论使用哪种类型的键盘，它们都能提供一致的表示方式。
>
> Reference: [VC虚拟键值表（详细介绍）_vc 键名与键值的转换-CSDN博客](https://blog.csdn.net/qq_42372031/article/details/105178789)

涉及的 API 有：
 `GetKeyboardState` —— 获取 256 个按键的状态。
 `ToUnicode` / `ToUnicodeEx` —— 将虚拟键码和键盘状态转换为 Unicode 字符。
 `MapVirtualKey` —— 在虚拟键码和扫描码之间进行映射。

```c
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
    case WM_KEYDOWN: {
        int vk = (int)wParam;  // 虚拟键码
        BYTE keyState[256];
        WCHAR buf[8];
        GetKeyboardState(keyState);
        if (ToUnicode(vk, (lParam >> 16) & 0xFF, keyState, buf, 8, 0) > 0) {
            // buf[0] 就是对应的字符
        }
        return 0;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
```

​	需要注意的是WM_KEYDOWN和WM_KEYUP不是对称出现的，因为他是水平触发的而不是边沿触发的，默认行为如此。这一点是我们编程的时候需要注意的。

## 鼠标捕获与展开

在窗口内部捕获鼠标时，最常用的 API 是 `SetCapture` 与 `ReleaseCapture`。当调用 `SetCapture` 之后，即使鼠标移出窗口，当前窗口也能持续收到鼠标消息，直到释放。我们一般会放到窗口事件回调函数的LParam上，一般则是放在高2字节和低2字节的位置上。需要用GET_X_LPARAM和GET_Y_LPARAM把我们感兴趣的值捕捉下来。

API 包括：
 `SetCapture` —— 把鼠标捕获到当前窗口。
 `ReleaseCapture` —— 释放鼠标捕获。
 `GetCursorPos` —— 获取当前光标的屏幕坐标。
 `SetCursorPos` —— 设置光标的新位置。
 `ClipCursor` —— 限制光标的活动区域。

```c
case WM_LBUTTONDOWN:
    SetCapture(hwnd);
    break;
case WM_MOUSEMOVE:
    if (wParam & MK_LBUTTON) {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
    }
    break;
case WM_LBUTTONUP:
    ReleaseCapture();
    break;
```

------

## 定时器捕获与展开

Windows 的定时器机制有多种形式。最常见的是消息定时器：`SetTimer` 创建定时器，`KillTimer` 销毁定时器，系统会投递 `WM_TIMER` 消息到窗口过程。

API 包括：
 `SetTimer` —— 设置基于消息的定时器。
 `KillTimer` —— 关闭定时器。

```c
case WM_CREATE:
    SetTimer(hwnd, 1, 1000, NULL);
    break;
case WM_TIMER:
    if (wParam == 1) {
        // 定时器逻辑
    }
    break;
case WM_DESTROY:
    KillTimer(hwnd, 1);
    PostQuitMessage(0);
    break;
```

如果需要高精度定时，可以使用等待定时器。这里涉及的 API 有：
 `CreateWaitableTimer` —— 创建一个可等待定时器对象。
 `SetWaitableTimer` —— 设置定时器触发时间。
 `WaitForSingleObject` —— 等待定时器触发。

代码示例如下：

```c
HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
LARGE_INTEGER li;
li.QuadPart = -10000000LL; // 1秒 (单位100ns，负数表示相对时间)
SetWaitableTimer(hTimer, &li, 0, NULL, NULL, 0);
WaitForSingleObject(hTimer, INFINITE);
// 到期后执行逻辑
```

## （搜集整理）Windows是如何处理输入流的？

Windows 的输入路径并不是单一的一条线，而是一组分层通道：物理设备（例如 PS/2 或 USB HID）通过驱动程序把原始数据送到内核，再由内核/类驱动（HID 类）交给 Windows 的输入子系统；对于应用程序，输入最终可以以传统的窗口消息（WM\_* 系列）、原始输入（Raw Input）、低级钩子（SetWindowsHookEx）、或更现代的 Pointer API（WM_POINTER*）等形式到达。选择哪一种路径取决于你要的精度、来源区分能力（比如区分哪个鼠标或触控笔）以及是否需要在消息被系统处理前拦截或修改它们。

```c
Physical_Device -> Dirver -> Windows Input Subsystem -> Application Hooks
```

### 键盘信息

#### 从硬件到驱动：PS/2、USB（HID）与 Windows 的处理

现代 PC 上的键盘可能通过 PS/2、USB 或蓝牙连接，但 Windows 统一把很多设备视为 HID（Human Interface Device）类，HID 描述符定义了按键、按钮和其它控制项的“usage”。内核里有 HID 类驱动负责把设备报告（report）送上来；上层应用通常不用直接处理 USB 报告，而是通过 Windows 提供的输入 API 来获得语义化的事件或原始数据。若你需要访问某个物理设备、区分多个键盘或读取原始扫描码流，Raw Input 与 HID API 是可选路径。

#### 扫描码（scan code）、虚拟键（VK）与字符（字符消息）

按键在最原始的层面产生的是扫描码（键盘硬件对按键的编码），Windows 把扫描码映射到“虚拟键码”（Virtual-Key，VK_* 常量），再由系统根据当前键盘布局、修饰键状态与 IME 将虚拟键转换为字符（可通过 WM_CHAR 接收字符消息）。因此开发者常常需要在三层之间来回转换：若你关心“哪个物理键被按下”，看扫描码或 RAWINPUT 里的信息更合适；若你在做文本输入处理，WM_CHAR / ToUnicodeEx 更方便。WM_KEYDOWN/WM_KEYUP 用来表示按键动作（wParam 含 VK），WM_CHAR 表示文本字符（wParam 是字符）。MapVirtualKey、ToUnicodeEx/ToAsciiEx 等函数用于虚拟键、扫描码和字符间的转换。

#### 原始输入（Raw Input）与设备区分

Raw Input API 允许应用直接接收来自 HID 的未被高层修改的输入数据（WM_INPUT 事件），这在游戏或需要精确、低延迟、能区分具体物理设备的场景非常有用。使用前需调用 RegisterRawInputDevices 注册设备类型（键盘/鼠标/其他 HID）。Raw Input 提供 RAWKEYBOARD、RAWMOUSE 等结构，能看到原始扫描码、设备句柄和更多细节。若你的程序需要区分“哪一把键盘发来的按键”或获取硬件级别的状态，Raw Input 是首选。

#### 键盘状态查询与合成输入

Windows 提供 GetKeyState、GetAsyncKeyState 与 GetKeyboardState 等函数来查询按键状态（它们的语义不同：GetKeyState/ GetKeyboardState 与线程消息队列有关，而 GetAsyncKeyState 报告调用时刻的物理状态）。当需要模拟按键或合成输入时，可以使用 SendInput（或较老的 keybd_event）来产生系统级输入事件。注意不要混用“以消息为准”的状态查询与“立即物理状态”的查询，理解它们之间的差别能避免许多竞态和焦点相关的 bug

#### 钩子（Hooks）与全局拦截

SetWindowsHookEx 提供了多种钩子点，其中 WH_KEYBOARD_LL（低级键盘钩子）允许应用在一个全局位置看到按键事件（适合实现全局热键、键盘监控工具等），但使用低级钩子要注意线程上下文、必须维持消息循环，以及权限（比如不同权限等级的进程间钩子有差异）。钩子是强力工具，但滥用会影响系统性能与安全。

### 定时器（Timers）信息

#### Windows 中的“定时器”类别：消息定时器、计时器队列、等待对象与多媒体定时器

在 Windows 里，“定时器”并不是单一概念，而是多个层次的实现：最常见的消息定时器由 SetTimer 创建，到期后系统向窗口投递 WM_TIMER（这是一个基于消息队列的、高层次、低精度的定时机制）。如果需要高精度回调，可以使用多媒体定时器（timeSetEvent，历史上用于音频/多媒体，但现在鼓励使用 CreateTimerQueueTimer）。若需要内核等待对象式的行为，CreateWaitableTimer / SetWaitableTimer 提供可等待的内核对象并可与 WaitForSingleObject 等配合使用；还有定时器队列（CreateTimerQueueTimer）可创建线程池回调。选择哪种机制要看你需要的精度、线程上下文与是否介入消息循环。

#### 精度、计时器分辨率与 QueryPerformanceCounter

Windows 的默认计时器分辨率并不非常高（经典值约 15.6ms），如果把定时器频率调高会影响功耗与系统整体性能（因此系统与平台引入了“timer coalescing”等能量优化机制）。对于测量短时间间隔或实现微秒级时间戳，QueryPerformanceCounter（及 QueryPerformanceFrequency）是推荐的高分辨率计时方式；当需要精确唤醒或等待，等待式定时器（CreateWaitableTimer/SetWaitableTimer）或高精度计时器 API 更合适。

#### 定时器合并（Timer Coalescing）与能耗考量

为了减少时钟中断次数、延长空闲时间并节约能耗，Windows 支持定时器合并/容忍度（coalescing / tolerable delay）：应用可以在设置定时器时表明一个容忍范围，内核会把若干相近的定时器到期时间往一起“挤”来触发，从而降低中断频率。这对移动设备与电池续航尤为重要；但如果你的场景对延迟非常敏感（比如某些实时音频或高精度测量），就不能给太大的容忍度。Windows 在不同层（用户态、内核态、驱动）都提供了相关 API，例如 SetCoalescableTimer / KeSetCoalescableTimer 等用于支持合并行为。

### 鼠标信息

#### 硬件、驱动与 HID 报告

鼠标同样通常被 HID 分类，设备上可能有多个按钮、滚轮（包括水平滚轮）和多轴输入。HID Usage Table 为不同按钮、轮和轴定义了 usage 值；Windows 的 HID 类驱动与上层 Raw Input API 能把这些底层报告送到用户态。若需要直接读取物理移动增量（例如在全屏游戏里需要“硬件增量”不受加速度/指针映射影响），Raw Input 的 RAWMOUSE 提供了更接近硬件的数据。

#### 窗口消息与常用 API：WM_MOUSE*、GetCursorPos / SetCursorPos

传统的鼠标交互在 Win32 环境中通过 WM_MOUSEMOVE、WM_LBUTTONDOWN / WM_LBUTTONUP、WM_RBUTTON*、WM_MBUTTON*、WM_MOUSEWHEEL、WM_XBUTTON* 等消息到达窗口过程，消息的 lParam 通常含有瞬时的坐标（相对于窗口客户区），wParam 含有修饰键和按钮状态。GetCursorPos 返回当前屏幕坐标，SetCursorPos 可以移动光标（注意与剪裁区域 ClipCursor 的交互）。WM_MOUSE 的坐标与 GetCursorPos 返回的屏幕坐标有坐标系差异，使用时需注意是“消息生成时的位置”还是“查询时的位置”。

#### 原始鼠标数据与高频率输入（游戏/全屏场景）

对于需要高精度或高轮询率（例如 500Hz/1000Hz 鼠标）并且不能被鼠标加速度或 Windows 指针变换影响的应用，Raw Input（WM_INPUT、GetRawInputData）通常是更合适的路径：它能提供原始增量、轮值及设备 ID。但注意高频率输入可能压在消息循环上，某些情况下需要使用更适合的读取策略（例如 GetRawInputBuffer）或在专门线程里处理以避免主消息循环堵塞

#### Pointer API（WM_POINTER*）与触控/笔/鼠标的统一

自 Windows 8 起，引入了 Pointer 输入体系（WM_POINTERDOWN / WM_POINTERUP / WM_POINTERUPDATE 等），它把触控、笔和鼠标等统一为“指针”，并提供了能识别输入来源（pointer type）与更丰富数据（压力、倾斜等）的 API。如果你的应用需要区分触控与真实鼠标、或要同时支持多点触控/笔压力，建议考虑 WM_POINTER 系列与相关 GetPointerInfo 等函数；对于只需要传统鼠标行为的应用，老的 WM_MOUSE 系列仍然有效且兼容性最好。

#### 鼠标钩子与捕获

像键盘一样，鼠标也支持低级钩子（WH_MOUSE_LL）用于全局监控。窗口内部的“捕获”（SetCapture / ReleaseCapture）允许在按下鼠标按钮后即使鼠标移出窗口也继续接收鼠标事件（常用于拖放）。使用钩子与捕获时要小心线程与权限问题，以及不要在钩子回调中做耗时工作以免影响系统响应。