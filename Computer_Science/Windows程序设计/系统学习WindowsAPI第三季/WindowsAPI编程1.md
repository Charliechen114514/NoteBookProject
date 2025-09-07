# Windows编程日志学习

## 了解一下Windows开发中常见的头文件

#### 基础类头文件

- **`windows.h`**
   Win32 编程的“总头文件”。几乎所有常用 API（窗口管理、消息循环、GDI、内存、线程、同步等）都在这里。
   👉 常见的 `CreateWindow`, `MessageBox`, `GetMessage`, `DispatchMessage` 等函数都出自这里。

- **`windef.h`**
   定义 Windows 常用的数据类型，比如 `DWORD`, `HWND`, `HINSTANCE`，它其实是 `windows.h` 的基础。

  > 一般我们使用Windows已经定义好的数据类型，很简单，后续如果API的接口类型发生改变，我们可以无需修改代码的保证我们的程序可以跑通。

- **`winnt.h`**
   定义了很多底层结构和常量，比如安全属性、访问权限、NT 内核相关定义。

#### 🎨 图形与界面相关

- **`wingdi.h`**
   GDI（图形设备接口）函数，绘制直线、矩形、位图、字体。比如 `BitBlt`, `CreateCompatibleDC`, `TextOut`。
- **`winuser.h`**
   窗口管理、消息机制、菜单、对话框。比如 `CreateWindowEx`, `RegisterClassEx`, `DefWindowProc`。
   👉 实际上很多 UI 函数虽然表面上写 `windows.h`，但内部就是走 `winuser.h`。
- **`commctrl.h`**
   公共控件（按钮、列表视图、树视图、进度条等），需要链接 `comctl32.lib`。
- **`commdlg.h`**
   公共对话框（文件打开/保存、颜色选择、字体选择），对应 `comdlg32.dll`。

------

#### 📂 文件与系统

- **`fileapi.h`**
   文件操作相关，如 `CreateFile`, `ReadFile`, `WriteFile`。
- **`winbase.h`**
   基础系统服务，线程、同步、进程管理、内存操作。比如 `CreateProcess`, `CreateMutex`, `VirtualAlloc`。
- **`shellapi.h`**
   与 Windows Shell 交互，比如 `ShellExecute` 打开应用/网页、托盘图标。
- **`shlobj.h`**
   Shell 扩展相关，获取特殊文件夹路径（桌面、文档等），`SHGetFolderPath`。

------

#### 📡 网络与通信

- **`winsock2.h`**
   套接字编程（TCP/UDP 网络通信），需要链接 `ws2_32.lib`。
- **`ws2tcpip.h`**
   Winsock 的扩展功能，比如 IPv6、地址解析。
- **`wininet.h`**
   更高层的 Internet 功能（HTTP、FTP），不过比较老了，现在常用 `WinHTTP` 或 `libcurl`。

------

#### 🔧 高级 / 扩展

- **`tlhelp32.h`**
   提供进程快照、线程/模块枚举的 API（`CreateToolhelp32Snapshot`）。
- **`psapi.h`**
   获取进程内存使用情况、模块信息，常用于任务管理器类工具。
- **`d2d1.h` / `d3d11.h`**
   分别是 Direct2D 和 Direct3D 图形接口。
- **`windowsx.h`**
   宏集合，用来简化 Windows 消息处理，比如 `GET_X_LPARAM(lParam)` 取鼠标坐标。

​	当然，写demo的时候，我们一般都是 `#include <windows.h>` 就能间接包含绝大多数子模块。快速的包含基础的模块，但是这就跟你工程开发中使用C++中的万能头文件一样，很容易拖慢编译的速度（嗯，粘贴上来一大堆无关系的头文件，所以实际开发时，为了编译更快、更清晰，通常会直接包含你需要的专用头，比如只写 `#include <winsock2.h>` 而不是让 `windows.h` 全家桶上。

## Windows API 编程的风格，以WinMain 与 MessageBox API为例子。

```c
#include <windows.h>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MessageBox(NULL, "Hello, Windows!", "My First API", MB_OK);
    return 0;
}
```

​	在标准 C++ 里，程序的入口是 `main()`；而在 Windows 平台，桌面应用的入口被定义为 `WinMain()`。它的参数表看起来有点吓人，但仔细分析就会发现：

- **`HINSTANCE hInstance`**：当前程序实例的句柄，相当于系统给这个进程的一张身份证。
- **`HINSTANCE hPrevInstance`**：老版本遗留，几乎恒为 `NULL`，可以无视。
- **`LPSTR lpCmdLine`**：命令行参数，字符串形式。
- **`int nCmdShow`**：窗口显示方式，比如正常/最小化/最大化。

可以说，`WinMain` 是 Windows API 风格的一个缩影：**入口函数参数冗长，类型都是“句柄”或“指针”，风格非常 C，而非 C++。**

------

### MessageBox：API 风格的典型缩影

`MessageBox` 是最常见的弹窗函数。它的原型是：

```
int MessageBox(
    HWND hWnd,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType
);
```

逐一对照：

- `HWND hWnd`：父窗口句柄。这里传 `NULL`，就是让它成为一个独立弹窗。
- `LPCSTR lpText`：消息文本（ANSI 字符串）。
- `LPCSTR lpCaption`：标题栏文本。
- `UINT uType`：按钮和图标的样式，比如 `MB_OK`、`MB_YESNO`。

API 的返回值也是一个整数，用来表示用户点了哪个按钮。

👉 这就是 Windows API 的“味道”：**函数名直白（MessageBox）、参数全是句柄/宏、返回值是枚举常量，调用起来像拼积木。**

------

### Windows API 编程的风格特征

通过 `WinMain + MessageBox`，其实我们能总结出 Windows API 编程的几大“气质”：

1. **C 风格浓厚**
    Win32 API 的设计年代比较久远，所以大量使用 `typedef` 的句柄（如 `HWND`, `HINSTANCE`）和 C 宏常量（`MB_OK`）。对初学者来说有点“神秘”，但其实都是整数/指针的别名。
2. **面向过程，而非面向对象**
    Windows API 没有 C++ 的类和方法，更多是“函数 + 结构体”的组合。要构建一个窗口，你要先 `RegisterClassEx` 注册，再 `CreateWindowEx` 创建，然后在消息循环里不断处理消息。
3. **以消息驱动为核心**
    与传统 `while(1)` 的流程不同，Windows 应用是事件驱动的。API 里大量存在“消息”（Message）概念，`GetMessage` + `DispatchMessage` 形成循环，用户点击、键盘输入、窗口变化都被封装成消息。
4. **大量使用句柄 (Handle)**
    文件有 `HANDLE`，窗口有 `HWND`，图形对象有 `HDC`。这些句柄其实就是操作系统内核对象的引用，程序员不用关心内部结构，只需要把“句柄”交给 API 使用。