# Windows编程日志——Windows 资源（RC）机制深度解析 — 从 rc.exe 到 .rsrc 到运行时加载

​	资源，这个在Qt中我们就有类似的东西存在，Windows自身就有类似的机制。

​	在 Windows 桌面开发里，“资源”（resources）指的是程序里除了代码以外的二进制或文本资产——图标、光标、位图、对话模板、菜单模板、字符串表、版本信息、以及任意二进制块等。

​	开发时你通常在 `.rc`（resource script）里描述资源，使用 `rc.exe`（或 IDE 的封装）把 `.rc` 编译为 `.res`，然后链接器把 `.res` 的内容放到目标 PE 文件的 `.rsrc` 节（Resource Directory）里；程序运行时通过一套 Win32 API（`FindResource`/`LoadResource`/`LockResource`、以及 `LoadString`、`LoadMenu`、`LoadIcon`/`LoadImage` 等）来定位并把这些资源读出来、变成内核/用户对象或字符串。



------

## rc.exe（Resource Compiler）的基本用途和命令行流程

`rc.exe` 是微软提供的资源编译器（也在 Visual Studio 的工具链 / Windows SDK 中），它把以人类可读语法写成的 `.rc` 文件编译成二进制的 `.res` 文件。`.rc` 可以引用 `.ico`, `.bmp`, `.dlg`（对话定义）、`STRINGTABLE`（字符串表）等条目，`rc.exe` 解析这些描述，处理 `#include`、`#define`、语言标记等，并生成编译产物。典型用法是：

```text
rc [options] filename.rc
# 常见输出： filename.res
# 例如：
rc /fo myapp.res myapp.rc
```

在 Visual Studio 的 MSBuild 中，这个流程通常由 RC 任务封装，生成 `.res` 再交给链接器（link.exe）与目标对象文件一起合并到最终的 `.exe` 或 `.dll`。MSBuild/VC 工程会自动处理 `resource.h`（ID 定义）与 `.rc` 的包含关系。关于 `rc.exe` 的选项（例如 `/l` 指定语言，`/n` 对 string table 是否以 NUL 结尾等）请参考官方文档。

```rc
#include "resource.h"

STRINGTABLE
BEGIN
    IDS_APP_TITLE   "我的程序"
    IDS_HELLO       "Hello, world!"
END

IDR_MYMENU MENU
BEGIN
    POPUP "&File"
    BEGIN
        MENUITEM "&Open", ID_FILE_OPEN
        MENUITEM "E&xit", ID_FILE_EXIT
    END
END

IDR_MAINICON ICON "app.ico"
```

然后在命令行编译并链接：

```bat
rc /fo myres.res myres.rc
cl /c main.c           # 生成 main.obj
link main.obj myres.res /OUT:MyApp.exe
```

注意：`rc.exe` 的细节、一些历史遗留的行为和 edge case（比如字符串块处理、字符编码和长路径问题）在现实的工程里会碰到；很多替代实现（如 `windres`、`llvm-rc`）在兼容性上也有差异，实际使用以官方 `rc.exe` 为准。

------

## `.res` 到 `.exe`：资源如何被嵌入到 PE（.rsrc 节）的基本原理

链接器不会把 `.res` 的二进制直接“附在文件末尾”，而是把资源重新格式化并放到 PE 的资源数据目录（通常为 `.rsrc` 节）下，按照 Windows PE 的资源目录树结构组织。资源的逻辑组织是三层目录树：**Type → Name/ID → Language**。也就是说，在 `.rsrc` 中，顶层目录列出所有资源类型（例如 `RT_ICON`、`RT_MENU`、`RT_STRING` 等），每个类型下列出具体的名字或数值 ID，每个名字/ID 下又可以包含同一资源的多个语言版本（language）。每个叶子（leaf）最终指向一段原始数据（有 RVA 和 size），那段数据就是我们在 `.rc` 中定义并由 `rc.exe`/链接器写进去的二进制内容。运行时 API 就是查询这棵目录树并得到数据。关于 PE .rsrc 节与资源目录结构的低层定义可以参考 PE/COFF 规范与相关 MSDN 文档。

更直观地说：链接器把资源写成一组 `IMAGE_RESOURCE_DIRECTORY` / `IMAGE_RESOURCE_DIRECTORY_ENTRY` / `IMAGE_RESOURCE_DATA_ENTRY` 等结构（这些结构描述表与叶子），数据本体按 RVA 存放；用户代码通过 `FindResource`（或 `FindResourceEx`）、`LoadResource`、`LockResource`、`SizeofResource` 等 API 来定位、加载并获得内存指针。

------

## 在 Visual Studio 中如何 GUI 化创建字符串、菜单、图标（实际操作步骤与生成的东西）

Visual Studio 提供 Resource View / Resource Editor，开发者通常通过 IDE 来可视化创建资源，而不是手写 `.rc`。总体流程是：在 Resource View 对 `.rc` 文件右键选择 “Add Resource” → 选择资源类型（String、Menu、Icon 等）→ 打开对应的编辑器（字符串表编辑器、菜单编辑器、图标导入器）→ 保存后 Visual Studio 会更新 `.rc` 文件和 `resource.h`（生成/维护 ID 宏）。官方资源编辑器文档列出了具体步骤和行为细节

- 创建字符串：在 Resource View 右键 `Add Resource` → 选择 `String Table`，会打开一个以 16 个条目为一行的可编辑表格（注意底层实现是 16 字符串一组的块，详见下面“字符串的底层存储”）。Visual Studio 会在 `resource.h` 中生成 `#define IDS_MYSTRING 101` 之类的 ID 定义，并在 `.rc` 中写入 `STRINGTABLE` 段。
- 创建菜单：在 Resource View 右键 `Add Resource` → `Menu`，打开 Menu Editor，可以拖拽/输入菜单项与快捷键，保存后在 `.rc` 里会生成 `menuID MENU BEGIN ... END` 的文本，同时资源编译器在编译时把这个菜单模板写入资源目录。运行时使用 `LoadMenu` / `SetMenu` 即可把它变成窗体的菜单。
- 导入图标：`Add Resource` → `Icon` → 选择 `.ico` 文件。IDE 会把 .ico 的各尺寸切片拆成资源里所需的 `RT_ICON`（每个图像单独一条）并生成一个 `RT_GROUP_ICON`（图标组）条目来描述组合信息，运行时通过 `LoadIcon`/`LoadImage` 或使用 `CreateIconFromResourceEx` 构造 `HICON`。这就是为什么一个 `.ico` 在资源里并不是单一 blob，而是一个分成条目并有“组描述”的结构。

------

## 字符串 / 菜单 / 图标 在资源中的底层格式与运行时加载逻辑（API + 底层行为）

下面按类型分别说明：如何存储（编译时），以及如何在运行时用 API 读取并转换成可用对象；同时解释 API 在底层通常做了什么。

#### 字符串（STRINGTABLE）

资源脚本里你写 `STRINGTABLE`，看起来像单条一条的字符串，但编译器输出时会把字符串打包成**每块最多 16 个字符串的一组（block）**；每块在资源树里有一个单独的资源 ID（这个 ID 与你在 `.rc` 中写的字符串 ID 并非一对一关系）。换句话说：字符串资源按 16 个为一组写入，每个字符串在组内用“计数 wchar 长度 + 文本”格式存储（不是以 NULL 结尾的普通 C 字符串）。对给定的字符串 ID `uId`，找到它所在的组的做法是 `blockId = uId / 16 + 1`（整数除法），在加载该组并遍历第 `uId & 15` 个条目就能得到目标字符串；MS 的博客（Old New Thing）里也有示例代码演示如何基于 `FindResourceEx/LoadResource/LockResource` 手动找到字符串并提取长度与文本。`LoadString` 是对这种流程的封装，但有局限（例如它不能直接指定语言分支）。若使用 `rc.exe` 的 `/n` 选项，会对字符串结尾的处理有所不同（NUL 终结等）

```c
WCHAR buf[256];
int len = LoadStringW(hInstance, IDS_HELLO, buf, ARRAYSIZE(buf));
if (len > 0) {
    // buf 为宽字符、以 NUL 结尾的字符串
}
```

如果你需要跨语言或需要取得字符串长度而不复制，可按 Raymond Chen 的例子用 `FindResourceEx`/`LoadResource`/`LockResource` 手工访问那一块原始数据并跳到组内索引位置解析。

#### 菜单（MENU）

菜单资源在编译后成为“菜单模板”（menu-template），它有老格式和扩展格式（`MENUITEMTEMPLATEHEADER`、`MENUITEMTEMPLATE` 等结构）。运行时调用 `LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MYMENU))` 会让系统从当前模块的资源树中找到对应的菜单模板数据，然后把模板解析并在内核/用户对象层面构造一个 HMENU（内部会为每项创建对应的菜单项结构、文本、标志等）。如果你把菜单模板当作纯二进制模板想操作，也可以用 `FindResource`/`LoadResource`/`LockResource` 拿到原始模板数据，再用 `LoadMenuIndirect` 在内存中创建菜单对象（这在动态生成或从网络/文件加载菜单模板时有用）。加载后用 `SetMenu(hwnd, hMenu)` 将菜单和窗口绑定。关于菜单模板格式以及加载方式的官方文档对开发者非常有帮助。

```c
HMENU hMenu = LoadMenuW(hInstance, MAKEINTRESOURCE(IDR_MYMENU));
SetMenu(hwnd, hMenu);
// 后续在窗口消息里处理 WM_COMMAND 根据 ID 响应菜单事件
```

#### 图标（ICON）

`.ico` 文件可以包含多个尺寸与色深的图像。资源编译器在把 `.ico` 加入资源时，会把每个图像位图单独存为 `RT_ICON` 类型的资源（每张图片是一个条目），同时会生成一个 `RT_GROUP_ICON`（图标组）来描述哪个图像对应哪些尺寸/色深，这样运行时可以根据请求的图标大小/显示深度选择最匹配的图像。常用的运行时 API 有 `LoadIcon`（历史更老的简便接口，返回共享 HICON，有限制）和更灵活的 `LoadImage`（可用于从资源或从文件加载、并可指定尺寸与标志），底层构造图标通常会调用 `CreateIconFromResourceEx`（它以资源位图数据创建一个新的 HICON）。官方有对“如何选择最佳图像（尺寸/色深匹配）”的说明。([Microsoft Learn](https://learn.microsoft.com/en-us/windows/win32/menurc/about-icons?utm_source=chatgpt.com))

示例（从资源加载最合适大小的图标）：

```c
HICON hIcon = (HICON)LoadImageW(hInstance, MAKEINTRESOURCE(IDR_MAINICON),
                                IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
```

底层可以手工实现：先用 `FindResource(hInst, MAKEINTRESOURCE(groupId), RT_GROUP_ICON)` 得到组描述，`LoadResource/LockResource` 得到组目录，找到合适的 `RT_ICON` ID，用 `FindResource(..., RT_ICON, MAKEINTRESOURCE(iconId))` 载入对应块，再 `CreateIconFromResourceEx` 构成 HICON。

------

## 核心 API 的语义（FindResource/LoadResource/LockResource/SizeofResource/FreeResource）以及它们在底层做了什么

在运行时访问任意资源的典型流程是三步：

1. 使用 `FindResource`（或 `FindResourceEx`）查找模块的资源目录，传入 `HMODULE`（或 NULL 表示当前进程模块）、资源类型（如 `RT_ICON`、`RT_STRING`、或 `MAKEINTRESOURCE(ID)`）和资源名/ID，返回 `HRSRC`（资源信息句柄）。`FindResource` 不返回资源数据指针，而是返回一个句柄/索引，表示在 PE 的资源目录里找到了某个条目。`FindResourceEx` 允许你指定语言。
2. 使用 `LoadResource(hModule, hResInfo)` 把资源“载入”。在现代 Win32 上，`LoadResource` 的返回类型是 `HGLOBAL`（出于向后兼容），但文档明确指出它并非返回 GlobalAlloc 的句柄；在 Win32/64 中，资源通常是由内核将映像文件（PE）映射到进程地址空间或者由 loader 延迟页面调入，`LoadResource` 的作用是确保资源数据可用并返回一个可传递给 `LockResource` 的句柄/标识。`LoadResource` 不需要（也不应）用 `GlobalLock`/`GlobalFree` 去处理其返回值。
3. 使用 `LockResource(hResData)` 获得指向资源数据首字节的指针（类型 `LPVOID`）。文档特别说明 `LockResource` 并不真的“锁定内存”——这个名字是历史遗留；现在它只是把资源数据映射为一个内存指针，指针在模块卸载之前一直有效。要得到资源大小，用 `SizeofResource(hModule, hResInfo)`。`FreeResource` 在 Win32/64 是过时的，不需要（实际上对现代系统通常总是返回 FALSE），因为资源内存由系统管理并在模块卸载或进程结束时回收。

把这些拼起来的示例代码（读取任意二进制资源并把它写到磁盘）：

```c
HRSRC hrsrc = FindResourceW(hModule, MAKEINTRESOURCE(IDR_MYDATA), L"MYDATA");
if (hrsrc) {
    HGLOBAL hres = LoadResource(hModule, hrsrc);
    if (hres) {
        void* p = LockResource(hres);
        DWORD sz = SizeofResource(hModule, hrsrc);
        // p 指向 sz 字节资源数据，直到模块被卸载都有效
        FILE* f = _wfopen(L"dump.bin", L"wb");
        fwrite(p, 1, sz, f);
        fclose(f);
        // 不需要 FreeResource/UnlockResource（已过时）
    }
}
```

底层事情的总结：`FindResource` 在 PE 的 `.rsrc` 目录树中查表，获得指向 `IMAGE_RESOURCE_DATA_ENTRY` 的索引；`LoadResource` 确保对应的页被调入 / 确保内存可读并返回用于 `LockResource` 的句柄；`LockResource` 返回实际指针。所有这些细节在经典的 PE 结构与 Windows loader / 内存管理实现中完成。

------

## API 在更高层（LoadString / LoadMenu / LoadIcon / LoadImage）内部做了什么

这些较高级的 API 封装了上面的查找/加载/解析流程，并把原始数据转换为方便使用的对象或字符串。

- `LoadString`：把字符串 ID 转换为相应的字符串组 ID（`uId/16 + 1`），用 `FindResource` 找组、`LoadResource/LockResource` 得到块数据，然后在块内跳过若干“计数+文本”条目，拷贝并 NUL-终结返回给调用者。它对语言选择不灵活（用的是默认语言），且无法返回字符串长度以外的元信息。若需要语言控制或更灵活的访问，开发者应使用 `FindResourceEx` 等低级 API。
- `LoadMenu`：从资源目录读取菜单模板数据，然后把模板解析并在用户子系统中创建菜单对象（HMENU），实际上内部会调用菜单管理的低级函数，把模板的每一项创建为内部菜单项结构，并把字符串文本从资源里转换成菜单显示文本。若你只是想在内存中从模板创建菜单，`LoadMenuIndirect` 可直接使用内存中的菜单模板。
- `LoadIcon` / `LoadImage`：`LoadImage` 更灵活，既能从资源加载也能从文件加载（`LR_LOADFROMFILE`），还允许指定尺寸、颜色选项。对于资源图标，API 会先读 `RT_GROUP_ICON` 以得到组描述，然后从 `RT_ICON` 里选择最契合的单个位图（基于请求大小与色深），最终通过 `CreateIconFromResourceEx`（或者等价内部流程）把 raw 位图数据转换为 `HICON`（或者 `HCURSOR`）。`LoadIcon` 是早期的简便函数，会返回共享图标句柄（某些情况下不是新的可自由销毁的句柄），而 `LoadImage`/`CreateIconFromResourceEx` 更适合精细控制并需要销毁的图标句柄。