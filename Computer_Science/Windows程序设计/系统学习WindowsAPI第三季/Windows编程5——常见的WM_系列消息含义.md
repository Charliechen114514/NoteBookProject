# Windows编程5——常见的WM_系列消息含义

## WM_* 系列消息总体

Windows 给窗口传递的消息都以 `WM_*` 常量定义（`winuser.h` 里）。它们大致分几类：

| 分类             | 典型消息                                                     | 含义                           |
| ---------------- | ------------------------------------------------------------ | ------------------------------ |
| **窗口生命周期** | `WM_CREATE`, `WM_DESTROY`, `WM_CLOSE`, `WM_QUIT`             | 窗口创建、销毁、关闭、线程退出 |
| **输入消息**     | `WM_KEYDOWN`, `WM_CHAR`, `WM_MOUSEMOVE`, `WM_LBUTTONDOWN` 等 | 键盘/鼠标/触控等输入           |
| **绘制消息**     | `WM_PAINT`, `WM_ERASEBKGND`                                  | 客户区需要重绘时               |
| **系统命令**     | `WM_SYSCOMMAND`, `WM_COMMAND`                                | 菜单、快捷键、控件命令         |
| **计时与异步**   | `WM_TIMER`, `WM_USER+n`                                      | 定时器、自定义异步消息         |
| **布局与移动**   | `WM_SIZE`, `WM_MOVE`                                         | 窗口大小/位置变化              |
| **杂项**         | `WM_SETFOCUS`, `WM_KILLFOCUS`                                | 焦点变化，激活/非激活等        |

当我们的 `GetMessage` 或 `PeekMessage` 从队列里取到消息时，会返回一个 `MSG` 结构：

```c
typedef struct tagMSG {
    HWND   hwnd;    // 消息目标窗口
    UINT   message; // 消息ID，即WM_*
    WPARAM wParam;  // 附加信息（无符号整型）
    LPARAM lParam;  // 附加信息（长整型/指针）
    DWORD  time;    // 产生时间
    POINT  pt;      // 当时鼠标位置
} MSG;
```

​	这个事情我们在上一篇博客就已经讨论过了，举个例子，用户在客户区点击鼠标左键的时候，这个时候显然要产生一个消息反馈给我们的窗口，Windows系统会先这样填充我们的MSG消息：

```c
MSG = {
    hwnd   = hMyWindow,         // 被点击的窗口
    message= WM_LBUTTONDOWN,    // 左键按下
    wParam = MK_LBUTTON,        // 鼠标键状态（左键=1）
    lParam = MAKELPARAM(x, y),  // 光标位置（客户区坐标）
    time   = 123456789,         // 时间戳
    pt     = {screenX, screenY} // 屏幕坐标
};
```

​	然后，当我们Get了这个Message之后，就要进入消息循环里的我们写下的 `DispatchMessage(&msg)` 会调用：

```c
WndProc(hMyWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x,y));
```

所以 **MSG 结构 → WndProc 参数** 是一一对应的。

------

## 窗口过程（WndProc）的编写与消息处理

```c
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
        // 窗口创建时初始化
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // 在客户区绘制
        TextOut(hdc, 10, 10, L"Hello Windows", 14);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_LBUTTONDOWN: {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        MessageBox(hwnd, L"鼠标点击！", L"提示", MB_OK);
        return 0;
    }

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            PostQuitMessage(0); // 退出主循环
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        // 未处理的交给系统默认行为
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
```

要点：

- **switch(uMsg)** 是标准模式。
- 不要忘记 `DefWindowProc`，否则窗口移动、标题栏绘制等系统行为会失效。
- 参数解释：
  - `wParam`：常用于键盘代码、鼠标键状态、命令 ID
  - `lParam`：常用于坐标、附加信息（通过 `LOWORD`/`HIWORD` 拆解）

------

### 常见 WM_* 的含义和处理方法

#### 生命周期

- `WM_CREATE`：窗口创建时发送，可做初始化。
- `WM_DESTROY`：窗口销毁时发送，通常调用 `PostQuitMessage(0)` 结束循环。
- `WM_CLOSE`：点击关闭按钮或 Alt+F4，通常调用 `DestroyWindow`。

#### 绘制

- `WM_PAINT`：客户区需要重绘时发送。
  - 必须用 `BeginPaint` / `EndPaint`。
  - 系统会合并多次 `WM_PAINT`，避免重复刷新。

#### 鼠标

- `WM_MOUSEMOVE`：鼠标移动，`lParam` 低/高字是 x/y 坐标。
- `WM_LBUTTONDOWN` / `UP`：左键按下/释放。
- `WM_RBUTTONDOWN` / `UP`：右键。
- `WM_MOUSEWHEEL`：滚轮，`wParam` 高字是滚动量。

#### 键盘

- `WM_KEYDOWN` / `UP`：按键按下/抬起，`wParam` 是虚拟键码。
- `WM_CHAR`：由 `TranslateMessage` 转换生成，表示字符输入（考虑键盘布局）。
- `WM_SYSKEYDOWN` / `WM_SYSCHAR`：系统按键（Alt + 键）。

#### 窗口大小和位置

- `WM_SIZE`：窗口大小改变，`wParam` 表示是最大化/最小化/还原。
- `WM_MOVE`：位置移动，`lParam` 是新左上角坐标。

#### 定时器

- `WM_TIMER`：由 `SetTimer` 触发，`wParam` 是定时器 ID。

#### 控件和菜单

- `WM_COMMAND`：按钮、菜单项、快捷键触发。
  - `LOWORD(wParam)` 是控件/命令 ID。

------

## 综上：正确匹配 MSG → 回调

1. `GetMessage(&msg, …)` 从队列取出：

   - msg.hwnd = 目标窗口
   - msg.message = WM_*
   - msg.wParam / msg.lParam = 附加数据

2. `DispatchMessage(&msg)` 调用：

   ```c
   WndProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
   ```

3. 你的 `WndProc` 用 `switch(uMsg)` 匹配消息 ID，解析参数。

**关键点**：

- 正确拆解 `wParam`/`lParam`（例如鼠标坐标、定时器 ID）。
- 保证未处理的消息交由 `DefWindowProc`。

