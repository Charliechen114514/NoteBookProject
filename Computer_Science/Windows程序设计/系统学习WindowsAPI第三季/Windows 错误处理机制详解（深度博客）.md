# Windows 错误处理机制详解（深度博客）

> 目标读者：熟悉 C/C++ 或 Windows 编程，希望系统了解 Windows 上「错误码 / 异常 / 崩溃上报」之间的关系、常用 API、以及生产级错误处理实践的开发者。
>  我会把概念、体系、常用 API、C++ 与 SEH 的交互、崩溃收集（minidump / WER）和实际推荐做法都覆盖，并给出示例代码片段与要点说明。思考后写出，尽量贴近微软文档与社区实践。

------

## 一、Windows的三种异常/错误处理

在 Windows 平台上，经常会看到三类不同但会相互转换的“状态/错误”：

- **Win32 错误码（DWORD）**：由许多传统 Win32 API 用 `GetLastError()` 报告（0 表示成功）。程序级调用失败常用此机制。
- **HRESULT（COM / Win32 上层约定）**：32 位编码（带 severity/facility/代码字段），COM/WinRT/很多 Windows API 使用，通常用 `SUCCEEDED()`/`FAILED()` 判断。可以把 Win32 错误映射为 HRESULT（`HRESULT_FROM_WIN32`）。
- **NTSTATUS**：内核 / 驱动层与部分底层 API 使用的 32 位状态码，语义与 HRESULT/Win32 有交叉但不同的编码空间。

​	此外还有 **结构化异常（SEH）**：由 CPU/系统（例如访问违规）或程序（`RaiseException`）触发的同步/异步“异常事件”，这属于运行时异常流（类似 Unix 下的信号）。SEH 与前面三类“状态码”不是同一层次，但在实践中会交互（例如访问违规通常会表现成 SEH 异常，再由上层记录为错误/崩溃信息）。

​	但是在这一片博客中，我们打算专门聊的是最为传统的Win32错误码机制。

## 可以自己定义Win32错误码嘛？有没有什么含义

### 1. 对于“Win32 错误码”（`GetLastError()` 返回的系统错误码）

这些错误码来源于操作系统的系统级定义（如 `ERROR_ACCESS_DENIED = 5` 等），由系统管理，不建议直接“自定义”或伪造，因为它们预留给系统使用，混用可能导致冲突和混淆。系统错误码以数字形式分布于 `WinError.h` 文件中，覆盖多个区间（0–499, 500–999, …, 12000–15999, …）等。

虽然你在自己的模块中可以定义类似错误码，但不建议使用 `GetLastError()` 传递它们。最佳做法是使用应用级错误机制，比如返回自定义结构、异常或文档中规定的错误范围。

### 2. 自定义 HRESULT 错误码（推荐做法）

如果你希望定义可通过 `FormatMessage` 输出文本、带错误描述的错误码，建议使用 `HRESULT`，并设置其 **Customer flag** 和 **Facility** 字段来标明来源和自定义标志，如下：

- **结构组成**：

  - **Severity（S）**：表示失败（1）或成功（0）。
  - **Customer bit（C）**：自定义错误必须置为 1（Microsoft 定义为 0）。
  - **Facility**：用来表明错误来源（比如 `FACILITY_ITF`=4，代表接口错误；也可自定义）。
  - **Code**：具体的错误编号。

  这种格式允许唯一识别你的错误来源，Microsoft 文档允许厂商扩展错误码值，只要设置 Customer 位为 1 。

- **建议做法**：

  - 使用 `FACILITY_ITF`（通常用于接口方法错误，也适合作为自定义错误范围）；
  - 设置 Severity = 错误，Customer = 自定义；
  - Code 字段填你的错误编号。

- **示例用法**：

  ```cpp
  HRESULT MAKE_CUSTOM_HRESULT(int customCode) {
      const int severity = 1; // failure
      const int customer = 1;
      const int facility = FACILITY_ITF; // 4
      return (HRESULT)((severity << 31) | (customer << 29) | (facility << 16) | (customCode & 0xFFFF));
  }
  ```

- **显示文本**：

  你需要将以这些自定义 HRESULT 为键的消息表作为资源（MessageTable .mc）嵌入可执行文件或 DLL 中，利用 `FormatMessage(..., FORMAT_MESSAGE_FROM_HMODULE, ...)` 来读取对应的自定义信息

### 3. 驱动程序层（NTSTATUS 自定义）

在 Windows 驱动开发中，可以使用 `.mc` 文件（Message Compiler）来定义自定义的 **NTSTATUS** 值和消息，通过为 `MessageIdTypedef=NTSTATUS` 和使用 `-c`（Customer bit）参数来生成带 Customer 标志的状态码 。在应用层你还可以利用 `FormatMessage` 指定 `ntdll.dll` 模块来格式化该 NTSTATUS，或用 `RtlNtStatusToDosError` 转换为 Win32 error 码，再格式化。

------

## Win32 / HRESULT 错误码的分类和含义

#### Win32 系统错误码分类（GetLastError 返回值）

Windows 将系统错误码按数字区间分类，覆盖从基本文件/路径错误到网络、设备、Internet 等多个领域，每个数字段对应不同含义与上下文。常见的是：

- 0–499：文件/句柄/访问/内存等通用错误；
- 更高区段（如 12000–15999）：Internet / WinINet、网络错误等 

系统维护文档，并提供工具（如 Error Lookup、ERR.EXE、ERRLOOK.EXE）帮助查询含义

#### HRESULT 结构详解

`HRESULT` 是一个 32 位结构，常用于 COM / WinRT：

- 格式如下（bit 字段见下）：

  | Bit   | Meaning                              |
  | ----- | ------------------------------------ |
  | 31    | Severity (1 = fail, 0 = success)     |
  | 30    | Reserved (R)                         |
  | 29    | Customer (1 = custom, 0 = Microsoft) |
  | 28    | N (NTSTATUS indicator)               |
  | 27    | X (reserved)                         |
  | 16–26 | Facility (source)                    |
  | 0–15  | Code (error code)                    |

- 常见 `Facility` 值包括：`FACILITY_WIN32`=7, `ITF`=4 等 

- 常用 HRESULT：`0x80070005` 表示 Win32 错误 `Access Denied`，是通过 `HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED)` 转换得到 

------



## Win32错误码处理的几个经典的API

**Win32 错误码（system error codes）**：许多经典 Win32 API 在失败时通过 `SetLastError` / `GetLastError` 抛出一个 `DWORD` 类型的错误码（0 = ERROR_SUCCESS）。这些错误码的定义可在 Microsoft 的 System Error Codes 列表和 WinError.h 中找到。我们后面还会看到，我们可能还需要自己定义

#### `GetLastError()` 的使用细节与常见陷阱

1. **先检查返回值，再调用 `GetLastError()`**
    绝大多数 Windows API 在失败时有明确的返回值（例如：`BOOL` 返回 `FALSE`、指针返回 `NULL`、句柄返回 `INVALID_HANDLE_VALUE` 等）。只有在返回值表明“失败”时才调用 `GetLastError()`；否则不要盲目调用 `GetLastError()`。很多 API 只有在失败时才设置 last-error，这在各函数的参考页里会有说明。
2. **马上读，并妥善保存**
    因为同一线程后续的任何 Windows API 调用都可能调用 `SetLastError(0)` 或覆盖错误码，所以**一旦检测到失败，应立即执行 `DWORD err = GetLastError();` 并在随后把 `err` 记录或传入 `FormatMessage()`**，不要在读取前再调用可能改写 last-error 的函数（例如字符串处理、日志库的 Win32 调用等）。微软文档明确建议立即读取。
3. **有些函数在“成功”情形也会修改 last-error**
    少数 API 会在成功返回时也调用 `SetLastError`（例如创建命名内核对象时会返回 `ERROR_ALREADY_EXISTS` 等），这些都是在各函数的文档中单独说明的。不要假定“只有失败才改 last-error”。如果你必须区分这些情况，要读该 API 的文档或在调用前手动 `SetLastError(0)`（谨慎，见下）。
4. **不要把 `GetLastError()` 当作“通用异常机制”**
    它是一个**辅助**手段，主要用于把底层系统调用失败的更详细信息（数字码）暴露出来。设计 API 或库时，尽量将错误通过返回值或异常机制明确传递给上层，而不是依赖外部 `GetLastError()` 在任意位置读取

------

#### 用 `FormatMessage()` 把错误码格式化成人可读文本

##### 常用 Flag 和参数解释（关键点）

- `FORMAT_MESSAGE_FROM_SYSTEM`：从系统消息表中查找错误文本（常用于 `GetLastError()` 返回的系统错误码）。
- `FORMAT_MESSAGE_ALLOCATE_BUFFER`：告诉 `FormatMessage` 为输出分配缓冲区（函数会用 `LocalAlloc`），此时你传入 `(LPWSTR)&pBuf` 并在用完后用 `LocalFree(pBuf)` 释放。
- `FORMAT_MESSAGE_FROM_HMODULE`：如果错误文本不在系统消息表（例如 NTSTATUS 的文本位于 `ntdll.dll`），可以把 `lpSource` 指向具体模块的 HMODULE（`GetModuleHandle` / `LoadLibrary`）并加上这个 flag。

**注意**：`FormatMessage` 返回的文本通常带有结尾的回车换行（`\r\n`），也可能包含一个终结符 `%0` 的特殊处理，所以在日志里打印之前常做 trim。

##### NTSTATUS / 内核错误的特殊情况

有些错误码实际上是 NT 内核的 `NTSTATUS`，如果你直接把 NTSTATUS 当作 Win32 system-error 用 `FormatMessage(FROM_SYSTEM)` 查找，会找不到。常见做法有两种：

- 使用 `RtlNtStatusToDosError` 把 `NTSTATUS` 转为等价的 Win32 错误码，然后 `FormatMessage`。或者
- 直接用 `FormatMessage` 并同时传入 `FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE`，把 `lpSource` 设置为 `GetModuleHandle(L"ntdll.dll")`，从 ntdll 的消息表中查询。两者都在微软文档里有说明。

##### Winsock / 其它子系统

Winsock 错误不通过 `GetLastError()` 返回，而是使用 `WSAGetLastError()` / `WSASetLastError()`。如果你在做 socket 编程，请用 Winsock 的错误函数获取错误码再格式化

------

## 实用工具函数（C++）—— 推荐模板（Unicode 版本）

下面是一个在生产中常用的、稳定的辅助函数（会立即从 `GetLastError()` 读取、用 `FormatMessageW` 获取文本、释放缓冲区并 trim 尾部空白）：

```cpp
#include <windows.h>
#include <string>
#include <algorithm> // for rtrim

static std::wstring TrimEnd(const std::wstring &s) {
    auto end = s.find_last_not_of(L"\r\n \t");
    if (end == std::wstring::npos) return L"";
    return s.substr(0, end+1);
}

std::wstring GetLastErrorMessageW(DWORD err = ::GetLastError(), LPCWSTR fallbackPrefix = L"Error") {
    if (err == ERROR_SUCCESS) return L"0 (ERROR_SUCCESS)";

    LPWSTR buf = nullptr;
    DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    // LANG_NEUTRAL with default sublang = user's language
    DWORD n = ::FormatMessageW(flags, nullptr, err,
                               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                               (LPWSTR)&buf, 0, nullptr);
    std::wstring msg;
    if (n != 0 && buf != nullptr) {
        msg.assign(buf, n);
        ::LocalFree(buf);
        msg = TrimEnd(msg); // remove trailing newline
    } else {
        // fallback: no message found in system table
        wchar_t tmp[64];
        swprintf_s(tmp, L"%u (0x%08X)", err, err);
        msg = std::wstring(fallbackPrefix) + L" " + tmp;
    }
    return msg;
}
```

**使用模式示例**：

```cpp
// 调用某个可能失败的 API
BOOL ok = SomeWinApi(...);
if (!ok) {
    DWORD err = GetLastError();                        // 立即保存
    std::wstring text = GetLastErrorMessageW(err);     // 格式化文本（安全）
    // 记录：API 名、参数、err (十进制/十六进制)、text、tid/time/version 等
}
```

> 要点：**不要**在检查返回值前再做其它 Win32 调用（比如字符串格式化或日志中调用会使用 Win32 的函数），以免 `GetLastError()` 被覆盖。

------

## 如何把 Win32 错误和 HRESULT/NTSTATUS 互通（常见用法）

- **把 Win32 错误转为 HRESULT**：使用 `HRESULT_FROM_WIN32(code)`。这在 COM/WinRT 层面很常见。微软文档与头文件里有这个宏。
- **反向（从 HRESULT 推断 Win32 错误）**：要小心，直接反推不总是可靠（参考 Raymond Chen 的老文）。通用建议是：如果你自己的 API返回 HRESULT，但你知道它来源于 Win32 error，就把 code 保留或用 `HRESULT_FROM_WIN32` 明确转换；否则按需查文档或使用 helper（例如在 ATL 中的 `AtlHresultFromLastError`）。

------

## Notes

- **记录最小但必要的信息**：API 名、输入关键参数、失败的返回值、`GetLastError()`（十进制 + 十六进制）、FormatMessage 返回的文本、时间戳、线程 id、进程版本/模块版本。
- **立即采集错误码**：在失败检测点先 `DWORD err = GetLastError();` 再做其它事情（例如格式化、堆栈收集等）。
- **Winsock 特殊处理**：socket 错误使用 `WSAGetLastError()`，不要用 `GetLastError()`。
- **NTSTATUS / 驱动层错误**：若处理来自内核或 DeviceIoControl 等返回的内核状态，要么先 `RtlNtStatusToDosError`，要么用 `FormatMessage(..., lpSource=GetModuleHandle(L"ntdll.dll") ...)` 去查询 ntdll 的消息。
- **不要在库内部随便依赖 last-error**：如果你写的是公共库或 DLL，最好把失败信息通过返回值/异常明确传回到调用者；把 `SetLastError` 作为实现细节，而不是通信机制。

