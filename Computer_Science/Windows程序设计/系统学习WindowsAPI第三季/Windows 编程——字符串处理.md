# Windows 字符串处理

## 字符串是存在编码的

​	字符串存在编码，一般而言，咱们的起点是ASCII字符串编程，到后面，伴随我们实际上接触一定的中文显示，就需要设计到字符串编码的问题。常见的字符串的编码如下：

#### **ASCII / ANSI / 多字节（MBCS） / Code Page（代码页）**

Windows 里的“ANSI”通常不是单一编码，而是指**“系统 ANSI 代码页”**（CP_ACP），也就是 Windows 上为非 Unicode 程序指定的 8 位或多字节编码（例如在简体中文 Windows 上通常是 GBK/CP936）。不同地区或机器上 CP_ACP 可能不同。

#### **GB2312 / GBK / GB18030（汉字家族）**

- GB2312：早期简体中文国家标准，子集。
- GBK：对 GB2312 的扩展，包含更多汉字（微软的 code page 936 早期用于支持 GBK）。
- GB18030：新标准，向后兼容并支持四字节序列，微软在 Windows 中以 code page 54936 支持。简体中文系统常用 CP 936/GBK（历史/兼容），而现代建议以 Unicode（UTF-8/UTF-16）为主。

#### **Unicode / UTF-8 / UTF-16（Windows 的首选）**

- Unicode 是字符集（字符到码点的集合）；UTF-8/UTF-16/UTF-32 是其编码方式。
- **Windows 内部广泛使用 UTF-16（Little Endian），也就是 `WCHAR` / `wchar_t`（在 Windows 下通常是 16 位）**。Windows API 的“wide”（宽字符）系列使用 UTF-16。对于多字节/外部文本，Windows 提供代码页转换 API。

**BOM（字节顺序标记）**

常见 BOM：UTF-8 = `EF BB BF`；UTF-16 LE = `FF FE`；UTF-16 BE = `FE FF`。BOM 对检测与互操作很有帮助，但并非强制要求（尤其 UTF-8 通常不需要 BOM）。

------

## Windows API vs C 运行库（CRT）——两条不同但会交叉的路线

#### Win32 API（推荐用于与操作系统交互）

​	对于Windows，我们已经存在抽象宏自动根据编程环境进行字符编码的选择了。Windows 主要 API 提供 **`A`（ANSI / multibyte）和 `W`（wide / UTF-16）两套函数**：例如 `CreateFileA` / `CreateFileW`，头文件里通常有宏 `CreateFile` 根据 `_UNICODE`/`UNICODE` 定义映射到 `A` 或 `W`。一般推荐直接调用 `W` 版本以避免编码/转换问题。

字符串-编码转换的核心 Win32 API：**`MultiByteToWideChar`**（多字节 -> UTF-16）和 **`WideCharToMultiByte`**（UTF-16 -> 多字节）。这两者支持选择 code page（如 `CP_UTF8`、`CP_ACP`、`936`、`54936` 等）以及错误标志（如 `MB_ERR_INVALID_CHARS`）。这两个 API 的文档应作为转换工作的权威参考。

## C 运行库（CRT）

CRT 也提供多字节与宽字符 API（`mbstowcs` / `wcstombs` / `setlocale` / `_wcs*` / `_wfopen` 等），这些通常基于当前 C locale（例如 `setlocale(LC_CTYPE, ...)`）或 CRT 内部的 MBCS 设置。CRT 的多字节函数受 C locale 影响，且行为受实现与 locale 的影响；因此在 Windows 环境中做跨 code page 的可靠转换时，更推荐直接使用 Win32 的 `MultiByteToWideChar` / `WideCharToMultiByte`。

------

## A 后缀 与 W 后缀：具体是什么？应该使用哪个？

后缀 `A`：表示 **ANSI/multibyte** 版本（`char*`，按照某个 code page 解释字节序列）。

后缀 `W`：表示 **wide**（宽字符，UTF-16）的版本（`wchar_t*` / `WCHAR*`）。

还有不带后缀的宏（如 `CreateFile`）：根据是否定义 `UNICODE`/`_UNICODE`，编译时映射到 `CreateFileW` 或 `CreateFileA`；这称为“generic-text mappings”（`TCHAR`、`_T()` 等）。尽量直接使用 `W` 版本避免潜在的编码陷阱。

**为什么优先用 `W`？**

文件系统与许多内部 API 在 NT 内部是用 Unicode（UTF-16）表示路径与字符串，调用 `A` 版本会触发隐式从 ANSI code page 到 UTF-16 的转换（这可能丢失信息或在不同机器上行为不同）。`W` 直接接受 UTF-16，不依赖系统 ANSI code page。

## Coding Example

### 从 UTF-8（或任意 code page）转 UTF-16（`std::wstring` / `WCHAR*`）

```cpp
#include <windows.h>
#include <string>
#include <vector>
#include <stdexcept>

std::wstring MultiByteToWString(const std::string& s, UINT codePage = CP_UTF8) {
    if (s.empty()) return {};
    // 第一次获取需要的 wchar 数
    int required = MultiByteToWideChar(codePage, MB_ERR_INVALID_CHARS, s.data(), (int)s.size(), NULL, 0);
    if (required == 0) {
        DWORD err = GetLastError();
        throw std::runtime_error("MultiByteToWideChar failed: " + std::to_string(err));
    }
    std::vector<wchar_t> buf(required + 1);
    int converted = MultiByteToWideChar(codePage, MB_ERR_INVALID_CHARS, s.data(), (int)s.size(), buf.data(), required);
    if (converted == 0) {
        DWORD err = GetLastError();
        throw std::runtime_error("MultiByteToWideChar failed: " + std::to_string(err));
    }
    return std::wstring(buf.data(), converted);
}
```

说明：对 UTF-8 使用 `CP_UTF8`，并且在转换时推荐使用 `MB_ERR_INVALID_CHARS` 以便遇到非法序列能获取错误（某些 code page/flags 组合有限制，参见文档）。

### 从 UTF-16 到指定 code page（比如 CP_ACP 或 CP_UTF8）

```cpp
std::string WideStringToMultiByte(const std::wstring& w, UINT codePage = CP_UTF8) {
    if (w.empty()) return {};
    int required = WideCharToMultiByte(codePage, 0, w.data(), (int)w.size(), NULL, 0, NULL, NULL);
    if (required == 0) {
        DWORD err = GetLastError();
        throw std::runtime_error("WideCharToMultiByte failed: " + std::to_string(err));
    }
    std::string buf(required, '\0');
    int converted = WideCharToMultiByte(codePage, 0, w.data(), (int)w.size(), &buf[0], required, NULL, NULL);
    if (converted == 0) {
        DWORD err = GetLastError();
        throw std::runtime_error("WideCharToMultiByte failed: " + std::to_string(err));
    }
    return buf;
}
```

说明：写入 `CP_ACP` 会把 Unicode 串转换为当前系统 ANSI code page 的编码（可能丢失一些字符），写入 `CP_UTF8` 会得到 UTF-8 编码。

------

## DLL 导出（Export）：ANSI 与 Unicode 的区分与兼容策略

#### 导出符号本身

- DLL 的导出名是编译后生成的符号名（C++ 会有 name-mangling，`extern "C"` 可避免）。编译时如果你在代码中写 `CreateFile`（宏），那宏被展开成 `CreateFileW` 或 `CreateFileA`；但编译后的导出符号是具体的名字（`MyFuncA` 或 `MyFuncW`）。因此 **编译时的宏不会自动产生两个符号供外部选择**。如果你希望 DLL 同时提供 ANSI 和 Unicode 接口，必须分别导出两种版本（`MyApiA` 和 `MyApiW`），或在 `.def` 文件 / `__declspec(dllexport)` 中明确导出别名。

#### 推荐做法

1. **内部实现以 UTF-16 为主**（`W`），在需要同时支持旧客户端时，提供 `A` 的薄包装（在 `A` 版本中调用 `MultiByteToWideChar(CP_ACP, ...)` 将参数转换为 UTF-16，然后调用 `W` 实现；返回字符串时用 `WideCharToMultiByte` 转回）。
2. **对外文档明确列出 API 字符编码**。若你的 DLL 将被 .NET/Delphi/其他语言调用，文档需声明参数字符串的编码（例如“参数为 UTF-16LE 的 `wchar_t*`” 或“参数为 UTF-8 的 `char*`”）。对 P/Invoke，`CharSet`（`Ansi`/`Unicode`/`Auto`）会决定字符串如何被封送（marshalled）。

#### 导出样例（最简单的做法：导出两个显式名字）

```cpp
extern "C" __declspec(dllexport) BOOL MyApiW(LPCWSTR text) {
    // 真实实现（UTF-16）
}

extern "C" __declspec(dllexport) BOOL MyApiA(LPCSTR text) {
    // 将 ANSI 转为 UTF-16 然后调用 MyApiW
    std::wstring w = MultiByteToWString(text, CP_ACP);
    return MyApiW(w.c_str());
}
```

或者通过 `.def` 文件把同一实现导出为两个名字（或使用别名）。有关 `.def` 文件和 `EXPORTS` 的官方说明参见 MS 文档。

# Reference

- Windows 字符串与 Unicode 介绍（UTF-16 / `WCHAR`）：*Working with Strings*（Microsoft Learn）。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/win32/learnwin32/working-with-strings?utm_source=chatgpt.com))
- `MultiByteToWideChar`（多字节 -> UTF-16）文档。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar?utm_source=chatgpt.com))
- `WideCharToMultiByte`（UTF-16 -> 多字节）文档。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte?utm_source=chatgpt.com))
- 使用 BOM（Byte Order Marks）的说明。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/win32/intl/using-byte-order-marks?utm_source=chatgpt.com))
- Code Page 与编号（例如 CP 936 = GBK，54936 = GB18030，65001 = UTF-8 等）：*Code Page Identifiers* / *Code pages*。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers?utm_source=chatgpt.com))
- Generic-Text（`TCHAR` / `_T` / `_UNICODE`）与 A/W 映射说明。([Microsoft 学习](https://learn.microsoft.com/en-us/cpp/c-runtime-library/using-generic-text-mappings?view=msvc-170&utm_source=chatgpt.com))
- `IsTextUnicode`（检测是否为 Unicode 的启发式 API）说明。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-istextunicode?utm_source=chatgpt.com))
- 控制台与 code page（`GetConsoleOutputCP` / `SetConsoleOutputCP`）：Windows Console 文档。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/console/getconsoleoutputcp?utm_source=chatgpt.com))
- 关于在 Windows 中使用 UTF-8 的额外说明（例如 `MultiByteToWideChar` 的 flags 使用注意）：*Use UTF-8 code pages in Windows apps*。([Microsoft 学习](https://learn.microsoft.com/en-us/windows/apps/design/globalizing/use-utf8-code-page?utm_source=chatgpt.com)