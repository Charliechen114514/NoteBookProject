# Windows编程日志3——注册窗口类的深入学习

​	在上一篇博客中，我们已经讨论了一个最小的窗口显示的小Demo的步骤是如何的，为了深入理解每一个仔细的流程，我们需要回答清楚每一个步骤，我们到底在做什么，系统在干什么。

> https://blog.csdn.net/charlie114514191/article/details/150704312

​	Windows编程中，在我们初始化结束了WndClass的一个窗口实例对象之后，会调用一个`RegisterClass`，简单的说，它实际上是向我们的操作系统告知：我打算创建一个什么样的窗口？这很显然，我们的Windows操作系统实际上早就内置了一些选项，比如说"Button"是按钮，"Edit"是编辑器等等。这两个函数是 **Windows 窗口管理机制的基石**，如果不了解它们背后的原理，就很难真正明白 Windows 窗口是怎么被操作系统识别、创建与管理的。

### 理解窗口类

​	RegisterClass(Ex)就一个参数：**窗口类**（Window Class），在 Win32 API 世界里，他就是一份告诉系统“这个窗口长什么样、怎么响应消息”的**蓝图**。

#### WNDCLASS 结构体

`WNDCLASS` 是 **Win16 时代**的设计产物（最初出现在 Windows 3.x）。它的定义如下：

```cpp
typedef struct _WNDCLASS {
    UINT      style;         // 窗口类风格
    WNDPROC   lpfnWndProc;   // 窗口过程函数
    int       cbClsExtra;    // 窗口类额外内存
    int       cbWndExtra;    // 窗口实例额外内存
    HINSTANCE hInstance;     // 应用程序实例句柄
    HICON     hIcon;         // 大图标
    HCURSOR   hCursor;       // 光标
    HBRUSH    hbrBackground; // 背景画刷
    LPCWSTR   lpszMenuName;  // 菜单资源名
    LPCWSTR   lpszClassName; // 窗口类名
} WNDCLASS;
```

#### (1) `style` —— 窗口类风格

控制窗口的一些行为，常用取值：

- `CS_HREDRAW` / `CS_VREDRAW`：当窗口宽/高变化时，强制重绘整个窗口。
- `CS_DBLCLKS`：启用双击消息 (`WM_LBUTTONDBLCLK`)。
- `CS_OWNDC`：为窗口分配独立的设备上下文（DC），适合需要频繁绘制的应用（比如 OpenGL）。
- `CS_CLASSDC`：窗口类共享一个 DC。
- `CS_GLOBALCLASS`：注册为全局窗口类（可被其他进程使用，现代应用基本不用）。

系统通过这些标志来决定窗口刷新和输入的默认行为。

------

#### (2) `lpfnWndProc` —— 窗口过程函数

这是 **窗口消息的中枢**，几乎所有用户交互（鼠标、键盘、绘图、系统事件）都会被发送到这里。

例如：

```cpp
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT:
            // 绘制逻辑
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
```

可以把它类比为 **面向对象中的虚函数表 (vtable)**，不同窗口类的行为差异主要就靠它。

------

#### (3) `cbClsExtra` / `cbWndExtra` —— 额外内存

- `cbClsExtra`：给**整个窗口类**分配额外的字节，用于存放附加数据。
- `cbWndExtra`：给**每个窗口实例**分配额外的字节。

通过 `SetWindowLongPtr` / `GetWindowLongPtr` 就能访问这片额外内存。
 这在 Win16 时期非常有用，因为那时没有方便的面向对象封装，开发者往往把自定义数据塞到这里，相当于“扩展字段”。

------

#### (4) `hInstance` —— 实例句柄

标识当前应用程序实例。
 Windows 早期支持“多开同一个 EXE”，系统通过 `hInstance` 来区分不同实例。
 在资源加载（图标、菜单）时，系统会用这个句柄去定位正确的资源表。

------

#### (5) `hIcon` —— 窗口图标

这是窗口显示在标题栏和 Alt+Tab 任务切换中的**大图标**。
 它通常对应 32×32 或更大的资源。

------

#### (6) `hCursor` —— 鼠标光标

窗口默认的鼠标形状，例如：

- `LoadCursor(NULL, IDC_ARROW)` —— 标准箭头
- `IDC_HAND` —— 手形

如果应用没有在 `WM_SETCURSOR` 里自行设置，系统就用这里的值。

------

#### (7) `hbrBackground` —— 背景画刷

决定窗口客户区的默认背景色。
 常见用法：

```cpp
wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
```

当窗口收到 `WM_ERASEBKGND` 时，系统会自动用这个刷子填充。

------

#### (8) `lpszMenuName` —— 菜单资源名

指定一个内嵌的菜单资源名称（字符串或资源 ID）。
 窗口创建时会自动加载这个菜单。

------

#### (9) `lpszClassName` —— 窗口类名

窗口类的唯一标识。
 `CreateWindow` 会用这个名字来查找对应的窗口蓝图。

------

### 2. WNDCLASSEX 结构体

随着 Windows 95 引入任务栏和小图标，微软扩展了窗口类，推出了 `WNDCLASSEX`：

```cpp
typedef struct _WNDCLASSEX {
    UINT      cbSize;        // 结构大小（必须设定）
    UINT      style;         // 窗口类风格
    WNDPROC   lpfnWndProc;   // 窗口过程
    int       cbClsExtra;    // 类额外内存
    int       cbWndExtra;    // 窗口额外内存
    HINSTANCE hInstance;     // 程序实例
    HICON     hIcon;         // 大图标
    HCURSOR   hCursor;       // 光标
    HBRUSH    hbrBackground; // 背景刷子
    LPCWSTR   lpszMenuName;  // 菜单名
    LPCWSTR   lpszClassName; // 窗口类名
    HICON     hIconSm;       // **新增：小图标**
} WNDCLASSEX;
```

#### 新增字段：`hIconSm`

- 用于指定 **小图标**（通常是 16×16），显示在任务栏和 Alt+Tab 中的缩略窗口。
- 如果未指定，系统会自动缩放 `hIcon`。

#### 新增要求：`cbSize`

- 必须设置为 `sizeof(WNDCLASSEX)`，这样 Windows 才能识别是 `WNDCLASSEX` 而不是 `WNDCLASS`。
- 这是 Windows API 常见的“结构版本控制”机制。

这样来看，RegisterClassEx比他的前辈更加的现代，因此 **今天写代码时，几乎只用 RegisterClassEx。**

- `RegisterClass`：接受 `WNDCLASS`，只支持大图标。
- `RegisterClassEx`：接受 `WNDCLASSEX`，支持小图标，现代推荐使用。

​	所以，我们下面就可以快速的试试看：

```cpp
WNDCLASS wc = {};
wc.lpfnWndProc   = WindowProc;   // 窗口过程函数
wc.hInstance     = hInstance;    // 当前程序实例
wc.lpszClassName = L"MyWindow";  // 窗口类名

RegisterClass(&wc);

HWND hwnd = CreateWindowEx(
    0,                        // 窗口扩展样式
    L"MyWindow",              // 使用上面注册的类名
    L"Hello Windows",         // 窗口标题
    WS_OVERLAPPEDWINDOW,      // 窗口样式
    CW_USEDEFAULT, CW_USEDEFAULT,
    500, 300,
    NULL, NULL, hInstance, NULL
);
```

------

## 注册窗口类背后发生了什么？

当我们调用 `RegisterClassEx` 时，Windows 内核其实做了这样几件事：

1. **验证输入结构**
   - 检查 `cbSize` 是否正确
   - 检查 `lpfnWndProc` 是否存在
   - 确认 `lpszClassName` 唯一性（每个进程内窗口类名不能重复）
2. **构造内部数据结构 (ATOM)**
    Windows 内部会把窗口类存储在一张**原子表（Atom Table）**里，并为其分配一个 **ATOM 标识符**（实际上就是个 16-bit 值）。
   - 这就是为什么你能用字符串类名 `"MyWindow"` 来创建窗口，因为系统会把它转换成对应的 ATOM。
   - 内核中，这个窗口类结构会存放在 `USER32.DLL` 管理的内存区域。
3. **注册到当前进程的类表中**
   - 每个进程都有独立的窗口类表（Class List）。
   - 同一个类名可以在不同进程里重复存在，但在同一进程内是唯一的。
4. **绑定窗口过程函数**
    当未来某个窗口实例接收到消息（如 `WM_PAINT`），操作系统会查表，找到它对应的 `lpfnWndProc` 并回调。

也就是说，**RegisterClassEx 是窗口创建流程的“元注册中心”**，没有它，系统无法知道一个窗口应该长什么样、怎么响应消息。

------

## 为什么不能跳过注册？

为什么 CreateWindow 不能直接传递一个函数指针和参数，而一定要事先 RegisterClass？

原因在于 **Windows 的消息调度机制**。

- Windows 是事件驱动的 GUI 系统，内核层需要通过窗口类快速找到消息分发目标。
- 如果直接用函数指针，就会缺乏统一的“窗口标识”，导致窗口管理（样式、默认行为、光标、图标等）无法集中管理。
- 通过 **类表 + ATOM 机制**，系统不仅能高效查找，还能在多窗口应用中复用蓝图，避免重复描述相同属性。这样的话我们就可以复用对象了。

这是一种 **抽象与复用的权衡**：

- RegisterClass 注册了一个“类型定义”
- CreateWindow 就像是“实例化对象。

## CreateWindow(Ex)

​	**`CreateWindow` 本质是一个宏**：它直接展开为 `CreateWindowEx(0, …)`——也就是“没有扩展样式（`dwExStyle = 0`）的 `CreateWindowEx`”。所以**多数情况下你应当优先用 `CreateWindowEx`**，因为它能同时设定普通样式和扩展样式。进一步的，他会继续根据是否为Unicode环境展开成W版本或者是A版本的调用参数。

```c
HWND CreateWindowExW(
    DWORD     dwExStyle,
    LPCWSTR   lpClassName,   // 类名或原子
    LPCWSTR   lpWindowName,  // 标题/文本（对控件有特定含义）
    DWORD     dwStyle,       // WS_* 样式组合
    int       x, int y,
    int       nWidth, int nHeight,
    HWND      hWndParent,    // 父/所有者/特殊值
    HMENU     hMenu,         // 顶层: 菜单句柄; 子窗口: 控件ID
    HINSTANCE hInstance,     // 模块句柄（拥有者）
    LPVOID    lpParam        // 自定义指针, 传给 WM_NCCREATE/WM_CREATE
);
```

- **`dwExStyle`**：扩展样式。比如
  - `WS_EX_TOPMOST`（置顶）、`WS_EX_TOOLWINDOW`（工具窗，不进任务栏/Alt-Tab）、`WS_EX_NOACTIVATE`（点击不激活，做悬浮条常用）、`WS_EX_LAYERED`（分层窗，用来做半透明/全透明/异形）。扩展样式列表及语义见官方清单。
  - `WS_EX_LAYERED` 曾经**只支持顶层窗**，Windows 8 起**支持子窗口**；配合 `UpdateLayeredWindow`/`SetLayeredWindowAttributes` 使用。
- **`lpClassName`**：窗口类名的 Unicode/ANSI 字符串**或**类原子（`MAKEINTATOM`）。必须是已经注册过的类（例如系统控件 `"BUTTON"`, `"EDIT"`, `"STATIC"` 等）。
- **`lpWindowName`**：标题/文本；对于许多**标准控件**（如 `STATIC/EDIT/BUTTON`），它就是控件显示的文本。
- **`dwStyle`**：普通样式（`WS_*`）。决定窗口类型与外观：
  - `WS_OVERLAPPED`/`WS_CAPTION`/`WS_SYSMENU`/`WS_THICKFRAME`/`WS_MINIMIZEBOX`/`WS_MAXIMIZEBOX` 的组合构成经典“应用主窗”（`WS_OVERLAPPEDWINDOW` 宏）。
  - `WS_CHILD` 是**子窗口**；`WS_POPUP` 是**弹出/无边框顶层窗**；**`WS_CHILD` 与 `WS_POPUP` 互斥**。完整风格列表与可否运行时修改，见文档。
- **`x, y, nWidth, nHeight`**：初始位置与大小。
  - 对顶层窗，若 `x` 传 `CW_USEDEFAULT`，系统选择合适的位置（同时对宽高有特殊处理）。
- **`hWndParent`**：
  - 对 **子窗口**：是真正的父窗口句柄。
  - 对 **顶层弹出**：这个参数将把该窗设为**某个所有者（owner）**的“拥有窗口”（例如对话框拥有它），影响 Z 序/任务栏行为。
  - 还可以传 **`HWND_MESSAGE`** 创建**消息专用窗口（Message-only window）**：不可见、无子孙，专收发消息做组件通信。
- **`hMenu`**：**语义取决于是否子窗口**：
  - **顶层窗**：这里是“菜单句柄”（也可在类注册时指定 class menu）。
  - **子窗口/控件**：这里不是菜单，而是**控件 ID**（`int`）。**子窗口不能挂菜单**。
- **`hInstance`**：拥有新窗口的模块句柄，通常就是 `WinMain` 里拿到的实例句柄。它也会出现在 `CREATESTRUCT.hInstance` 中。
- **`lpParam`**：任意指针，系统会把它塞进 `CREATESTRUCT.lpCreateParams`，再随 `WM_NCCREATE/WM_CREATE` 交给你的窗口过程（高频用法：把 `this`/状态结构指针在 `WM_NCCREATE` 里取出并保存）。

------

### 调用后，系统内部到底发生了什么？（“创建时序”）

当你调用 `CreateWindowEx`，系统不仅仅是“返回一个句柄”，而是触发一连串的“非客户区 + 客户区”初始化消息；**窗口过程能用这些钩点决定是否继续创建**：

1. **（可选）CBT 钩子拦截**
    若系统或第三方装了 `WH_CBT` 钩子，先收到 **`HCBT_CREATEWND`** 通知；**钩子返回非零可直接否决创建**，这会让 `CreateWindow(Ex)` 返回 `NULL`，同时**不会**给目标窗发 `WM_DESTROY`。
2. **`WM_NCCREATE`**（非客户区初始化，**先于** `WM_CREATE`）
    `lParam` 指向 `CREATESTRUCT`，其中含你传入的 `lpParam`。**如果你的窗口过程在该消息里返回 `FALSE`，窗口创建会被**取消**。这一步常用于把 `lpCreateParams` 里的 `this/状态指针` 存到 `GWLP_USERDATA`。
3. **`WM_NCCALCSIZE`**（计算客户区大小）
    系统需要知道标题栏/边框占了多少，好安放客户区。`CreateWindowEx` 文档明确这一步会在创建过程中发送。
4. **`WM_CREATE`**（客户区对象初始化）
    这时窗体**已创建但仍不可见**。`lParam` 依旧是 `CREATESTRUCT*`；适合创建子控件、加载资源、初始化数据等。如果你在样式里一开始就给了 `WS_VISIBLE`，系统随后会安排显示流程。

> 小贴士：UI 自动化/辅助功能在窗口创建时还会抛出 `EVENT_OBJECT_CREATE` 等事件；顺序上是先有事件，后有 `WM_CREATE`。做自动化适配时要注意时序。

1. **可见 & 激活（可选）**
    是否立刻可见由 `WS_VISIBLE` 和之后你是否调用 `ShowWindow/UpdateWindow` 决定。**如果在 `CreateWindow(Ex)` 时就带了 `WS_VISIBLE`**，系统会自动发送激活/显示相关消息；**若没有**，就由你稍后调用 `ShowWindow` 来控制。
2. **Z 序默认规则**
    若未用 `SetWindowPos` 指定插入点，顶层窗口会放到**顶端**；子窗口默认放在父窗口**底部**。

> 线程与消息队列：**线程的消息队列是“按需创建”的**，第一次调用某些与窗口/消息相关的 API（比如 `CreateWindowEx`/`PeekMessage` 等）时才会被分配。不要指望“先天存在”。这是系统级设计，并非文档巧合。

- **标准主窗**：`dwStyle = WS_OVERLAPPEDWINDOW`（就是标题栏+系统菜单+可调整大小+最小化/最大化按钮的组合），`dwExStyle` 依据需求加 `WS_EX_APPWINDOW/WS_EX_ACCEPTFILES/…`。
- **无边框工具窗**：`WS_POPUP` + `WS_EX_TOOLWINDOW`（不进任务栏/Alt+Tab），需要置顶时再加 `WS_EX_TOPMOST`。
- **半透明/异形窗（飞窗/贴边条）**：`WS_POPUP` + `WS_EX_LAYERED`，内容通过 `UpdateLayeredWindow` 绘制；注意 Windows 8 起子窗口也能用。
- **消息专用窗**：`hWndParent = HWND_MESSAGE`，完全不可见，用于组件/模块间消息通信。
- **标准控件**：直接把 `lpClassName` 设为 `"BUTTON"`, `"EDIT"`, `"STATIC"` 等系统类名；`hWndParent` 设真实父窗；`hMenu` 传**控件 ID**（不是菜单）。

------

## `CreateWindowEx` vs `CreateWindow`：到底该用哪个？

- **用 `CreateWindowEx`**：因为你很可能需要设置 `WS_EX_*` 扩展样式（置顶、工具窗、分层窗、无激活等），这些只能在 Ex 版本里一次性到位。
- **`CreateWindow` 只是语法糖**：它完全等价于不带扩展样式的 `CreateWindowEx`。

------

#### 错误处理 & 真实世界的失败原因

- 调用失败时返回 `NULL`，请立刻 `GetLastError()`。**失败常见源头**：
  - 类名不存在/拼错、类未在本进程注册；
  - 你创建了**顶层子窗口**（Child 不允许当顶层），典型错误码 **`1406 ERROR_CANNOT_CREATE_WINDOW`**（“Cannot create top-level child window”）；
  - CBT 钩子否决了创建（见上文）。

- 在调用 `CreateWindowEx` 时把 `this`/状态块指针塞进 `lpParam`。
- 在窗口过程里于 **`WM_NCCREATE`**：从 `CREATESTRUCT` 取回 `lpCreateParams`，保存到 `GWLP_USERDATA` 或你自己的成员里；后续消息即可直接拿到上下文，无需全局变量。官方示例就是这么干的。

#### 需要注意的是

- **子窗口不能挂菜单**；因此 `hMenu` 对子窗口就是控件 ID。顶层窗的菜单既可在 `CreateWindowEx` 的 `hMenu` 传入，也可在**注册类时**指定“类菜单模板”。
- **置顶/取消置顶**要用 `SetWindowPos(HWND_TOPMOST/HWND_NOTOPMOST, …)`；历史上在某些版本里从置顶降级可能出现显示层级异常，还真有 KB 记录。
- **ANSI/Unicode 版本**：`CreateWindowExW/A`；若你的程序是 Unicode，确保类名/窗口名/菜单等全链路都是 Unicode，避免 “???” 文本。文档用“别名（A/W）”说明了映射关系。

------

### 最小复现／模板代码（带关键点评注）

```c
// UNICODE 工程；error checking 省略以便突出主线
#include <windows.h>

struct AppState {
    int counter = 0;
};

LRESULT CALLBACK WndProc(HWND h, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_NCCREATE: {
        // 把 lpParam 传进来的状态指针取出并“固化”在窗口上
        auto cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(h, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
        return TRUE; // 返回 FALSE 会终止创建
    }
    case WM_CREATE: {
        // 可在这里创建子控件；注意：子控件的 hMenu 参数是“控件ID”
        CreateWindowExW(0, L"BUTTON", L"Click",
                        WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                        16, 16, 120, 28,
                        h, (HMENU)1001, (HINSTANCE)GetWindowLongPtr(h, GWLP_HINSTANCE), nullptr);
        return 0;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 1001) {
            auto s = reinterpret_cast<AppState*>(GetWindowLongPtr(h, GWLP_USERDATA));
            ++s->counter;
            SetWindowTextW(h, (std::wstring(L"Clicked ") + std::to_wstring(s->counter) + L" times").c_str());
        }
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(h, msg, wParam, lParam);
    }
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR, int nCmdShow) {
    // 1) 注册类（略）……

    // 2) 创建窗口：推荐用 CreateWindowEx，一次性设好扩展样式
    AppState state{};
    HWND hwnd = CreateWindowExW(
        0,                       // 或 WS_EX_NOACTIVATE/WS_EX_TOOLWINDOW 等
        L"MyWndClass",           // 你注册的类名
        L"Demo",                 // 窗口标题
        WS_OVERLAPPEDWINDOW,     // 标准主窗
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 500,
        nullptr,                 // 顶层窗：无父
        nullptr,                 // 菜单句柄（顶层窗时才有意义）
        hInst,
        &state                   // 传入自定义上下文
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0)) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    return (int)m.wParam;
}
```

> 代码里的关键点（为何这么写）与官方建议一致：`lpParam` → `WM_NCCREATE` 提取 → 存储；子控件用 `hMenu` 作为控件 ID；显示流程用 `ShowWindow/UpdateWindow` 控制。

