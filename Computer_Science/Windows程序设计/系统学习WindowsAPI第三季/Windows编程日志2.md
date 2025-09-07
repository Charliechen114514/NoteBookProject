# Windows编程日志2

在上一篇文章里，我们用 `WinMain` 和 `MessageBox` 看了一眼 Windows API 的编程风格。但光弹个对话框还不算真正的“Windows 程序”。如果你要写一个像记事本、画图那样的应用，就必须学会 **创建窗口**。

## 1. 创建窗口的五大步骤

在 Win32 API 的世界里，创建一个窗口通常分为以下几个环节：

1. 首先，我们尝试做GUI Windows编程，必须定义的是WinMain函数

2. **定义窗口类 (RegisterClassEx)**
    告诉系统“我要造一种窗口”，描述它的特征（样式、光标、背景色、消息处理函数）。

3. **注册窗口类**
    把这个“窗口蓝图”登记到系统里。

4. **创建窗口 (CreateWindowEx)**
    根据蓝图真正造出一个窗口实例。

5. **显示和更新窗口 (ShowWindow + UpdateWindow)**
    把窗口展示到屏幕上。

6. **消息循环 (GetMessage + DispatchMessage)**
    让窗口“活”起来，响应鼠标、键盘、系统事件。

7. 消息处理

   我们需要给我们的消息上一些Hook，处理我们的机制

------

## 写代码试试味道

在使用VS2022（我用的这个，期待明年出新的试试味道），如果你是创建了一个空项目，需要在VS2022中对项目的构建中右键选择属性`->` 链接器 `->` 系统 `->` 子系统中改成窗口，默认是控制台，这样代码入口就会从main函数进入WinMain函数。

```
#include <Windows.h>

int WINAPI WinMain(
	_In_		HINSTANCE	current_handle,
	_In_opt_	HINSTANCE	prev_handle,
	_In_		LPSTR		command_line,
	_In_		int			show_type
) {

	MessageBox(NULL, TEXT("Hello world!"),
	TEXT("Hello Win Programming"), 
	MB_OKCANCEL | MB_ICONINFORMATION);
	return 0;
}
```

​	运行下玩玩。



## 准备写一个最小的demo试试看

```cpp
#include <Windows.h>

LPARAM CALLBACK window_proc(
	HWND WindowType,
	UINT messageID,
	WPARAM wParam,
	LPARAM lParam)
{
	return DefWindowProc(WindowType, messageID, wParam, lParam);
}

void setup_window(
	WNDCLASS& window_class, 
	HINSTANCE current_instance,
	LPCWSTR name)
{
	window_class = { 0 };
	// cached buffer for struct itself
	window_class.cbClsExtra = 0;
	// cached buffer for the window post init
	window_class.cbWndExtra = 0;
	// background color type
	window_class.hbrBackground =
		reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	// cursor for sys default
	window_class.hCursor = NULL;
	// window icon
	window_class.hIcon = NULL;
	// bind to current instance
	window_class.hInstance = current_instance;
	// post process
	window_class.lpfnWndProc = window_proc;
	// window class type
	window_class.lpszClassName = name;
	// menu name
	window_class.lpszMenuName = NULL; // no menu
	// force repaint
	window_class.style = CS_HREDRAW | CS_VREDRAW;
}

int WINAPI WinMain(
	_In_		HINSTANCE	current_handle,
	_In_opt_	HINSTANCE	prev_handle,
	_In_		LPSTR		command_line,
	_In_		int			show_type
) { 
	WNDCLASS window;
	LPCWSTR name = TEXT("Main");
	setup_window(window, current_handle, name);
	RegisterClass(&window);

	HWND hwnd = CreateWindow(name, TEXT("Window"), WS_OVERLAPPEDWINDOW, 100, 100, 500, 500,
		NULL, NULL, current_handle, NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}

	return 0;
}

```

> 注意，这个程序并不标准，我们没有处理窗口退出处理，但是Windows11中，这个API会默认的处理关闭事件为退出了。

------

## 3. 编程风格观察

在这个过程中，我们能明显感受到 Windows API 编程的几个“套路”：

- **大量结构体**
   `WNDCLASS` 是窗口类的描述，字段很多（背景、光标、图标、回调函数），就像一份“窗口简历”。
- **函数链条很长**
   你必须先注册窗口类，再创建窗口，再显示窗口，最后进入消息循环。缺一不可。
- **消息驱动思想**
   重点在 `WndProc` —— 窗口过程函数。
   你不用手动写循环去检测鼠标点击，而是写好 `case WM_DESTROY`，当系统派发消息时它自然会运行。
- **样式常量丰富**
   创建窗口时的 `WS_OVERLAPPEDWINDOW` 就是一种组合样式，控制窗口外观。类似的还有 `WS_POPUP`, `WS_CHILD`。

