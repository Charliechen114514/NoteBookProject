# Windows程序设计 - 错误处理

​	这个系列是本人基于对比Linux程序设计的同时一并学习Windows的程序设计，在开始程序设计之前，我们第一件事情就是查看Windows是如何处理错误的，方便我们后续继续开展Windows程序设计的学习

## 前言

​	第一件事情，我们使用的就是Windows提供的SDK，常见的函数的返回的数据类型有

- VOID（不可能失败的函数，很少有函数的返回类型是VOID）
- BOOL（函数失败返回0，反之返回的是一个非0的值，一个好的办法是检查这个函数的返回值是不是False来断言他是否失败！）
- PVOID（函数调用失败返回NULL，否则会标识一块内存）
- LONG/DWORD，这类函数请查看具体的SDK说明！

​	一个好的办法就是立马查看GetLastError返回最近的一次错误！

```c
DWORD GetLastError();
```

> 有些令人难受的是：Windows的函数是首字母大写的，我们没办法依靠字母大小写断定他可能的类型

​	在WinError.h中，存在定义错误码的文件：近7w行的大文件！

```c
//
// MessageId: ERROR_INVALID_FUNCTION
//
// MessageText:
//
// Incorrect function.
//
#define ERROR_INVALID_FUNCTION           1L    // dderror

//
// MessageId: ERROR_FILE_NOT_FOUND
//
// MessageText:
//
// The system cannot find the file specified.
//
#define ERROR_FILE_NOT_FOUND             2L
// ...
```

​	可以看到，每一个错误有三种标识：

1. 消息ID（在源代码上使用的宏）
2. 消息文本（描述错误）
3. 一个标号（不必理会这个，不建议使用这个）

​	当我们调用GetLastError函数，返回的总是错误码，直接扔给用户看错误码多少不太友好，

```
DWORD FormatMessage(
  [in]           DWORD   dwFlags,
  [in, optional] LPCVOID lpSource,
  [in]           DWORD   dwMessageId,
  [in]           DWORD   dwLanguageId,
  [out]          LPTSTR  lpBuffer,
  [in]           DWORD   nSize,
  [in, optional] va_list *Arguments
);
```

​	可以使用这个函数得到错误描述字符串。

## 定义属于我们自己的错误码

​	我们可以定义自己的错误码！很简单

```c
VOID SetLastError(DWORD dwErrCode);
```

​	DWORD是一个32位的值，来看看你应该如何排布他！

```
//
// Note: There is a slightly modified layout for HRESULT values below,
//        after the heading "COM Error Codes".
//
// Search for "**** Available SYSTEM error codes ****" to find where to
// insert new error codes
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
```

| 位   | 31-30                                        | 29                                | 28   | 27-16                    | 15-0       |
| ---- | -------------------------------------------- | --------------------------------- | ---- | ------------------------ | ---------- |
| 内容 | 严重性                                       | Microsoft/客户                    | 保留 | Facility代码             | 异常代码   |
| 含义 | 0 成功<br>1 信息（提示）<br>2 警告<br>3 错误 | 0：Microsoft定义<br>1：客户自定义 | 0    | 前256个值被Microsoft保留 | 定义的代码 |



## Reference

> [GetLastError 函数 (errhandlingapi.h) - Win32 apps | Microsoft Learn](https://learn.microsoft.com/zh-cn/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror)
>
> [FormatMessage 函数 (winbase.h) - Win32 apps | Microsoft Learn](https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-formatmessage)

# Windows程序设计 - 字符与字符串处理

## 字符编码的问题

​	对于一些像我这样的初学者：很喜欢认为字符串的处理就是将字符排成一个序列（SequenceList），然后粗暴的以一个`\0`结尾草草了事，想要获取长度只能strlen遍历长度

```c
// A simple Implemment of strlen:
int My_Strlen(const char* str){
    int len = 0;
    for(const char* pStrIndex = str;	 // 铆定字符串的头部
        *pStrIndex == '\0';				// 循环退出条件是遇到了\0
        pStrIndex++, len++				// 更新游标
       );
    return len;
}
```

​	但是实际上，如果我们的程序走向国际，就不可避免的出现过国际化的问题，也就是字符串需要存储的是不同国家语言的文字。这样，我们就必须把目光转向Unicode了。

> 关于UTF8，UTF16以及Unicode等字符集的问题，不妨参考：[Unicode、UTF-8、UTF-16之间的区别 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/259386795)

## ANSI Vs Unicode

​	在**Microsoft C/C++**中，我们编译器内置了一个类型就是wchar_t表示宽字符（当然有开关，只有在指定了/Zc:wchar_t的时候才会开，不过你放心，默认的都开着），你看可以这样表达一个宽字符：

```c
wchar_t c = L'A';
wchar_t szBuffer[100] = L"A String";
```

​	使用一个L前缀来表达这个字符或者是字符串是宽字符或者是由宽字符组成的宽字符串！当然也可以使用Windows的内置宏来声明这个字符或者字符串是宽的，办法就是使用以下这些宏 

```
#define TEXT(quote) __TEXT(quote)   // r_winnt
#define __TEXT(quote) L##quote      // r_winnt
```

​	Windows呢，自己整了一层抽象（尽管我觉得很鸡肋）

```c
//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;

typedef _Null_terminated_ CHAR *NPSTR, *LPSTR, *PSTR;
typedef _Null_terminated_ PSTR *PZPSTR;
typedef _Null_terminated_ CONST PSTR *PCZPSTR;
typedef _Null_terminated_ CONST CHAR *LPCSTR, *PCSTR;
typedef _Null_terminated_ PCSTR *PZPCSTR;
typedef _Null_terminated_ CONST PCSTR *PCZPCSTR;

typedef _NullNull_terminated_ CHAR *PZZSTR;
typedef _NullNull_terminated_ CONST CHAR *PCZZSTR;

typedef  CHAR *PNZCH;
typedef  CONST CHAR *PCNZCH;

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE                     // r_winnt

#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPWCH LPTCH, PTCH;
typedef LPCWCH LPCTCH, PCTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR PCTSTR, LPCTSTR;
typedef LPUWSTR PUTSTR, LPUTSTR;
typedef LPCUWSTR PCUTSTR, LPCUTSTR;
typedef LPWSTR LP;
typedef PZZWSTR PZZTSTR;
typedef PCZZWSTR PCZZTSTR;
typedef PUZZWSTR PUZZTSTR;
typedef PCUZZWSTR PCUZZTSTR;
typedef PZPWSTR PZPTSTR;
typedef PNZWCH PNZTCH;
typedef PCNZWCH PCNZTCH;
typedef PUNZWCH PUNZTCH;
typedef PCUNZWCH PCUNZTCH;
```

​	看看就好，实际开发的时候跳转着看就行。

> BTW：教大伙一个快速识别的办法：P大头的表示指针，L大头的表示宽

## 函数版本区分

​	在Windows中凡是涉及到字符串处理的函数，都有至少两个版本！他们的函数基名都是一致的！唯一不同的是针对处理字符集的不同它会有不一样的后缀名，比如说处理ASCII字符串的时候，它的后缀名是A！处理Unicode的字符串的时候它的后缀名是W！

​	以Windows著名狗屎API：创建一个窗口为一个例子：

```
HWND CreateWindowExA(
  [in]           DWORD     dwExStyle,
  [in, optional] LPCSTR    lpClassName,
  [in, optional] LPCSTR    lpWindowName,
  [in]           DWORD     dwStyle,
  [in]           int       X,
  [in]           int       Y,
  [in]           int       nWidth,
  [in]           int       nHeight,
  [in, optional] HWND      hWndParent,
  [in, optional] HMENU     hMenu,
  [in, optional] HINSTANCE hInstance,
  [in, optional] LPVOID    lpParam
);

HWND CreateWindowExW(
  [in]           DWORD     dwExStyle,
  [in, optional] LPCWSTR   lpClassName,
  [in, optional] LPCWSTR   lpWindowName,
  [in]           DWORD     dwStyle,
  [in]           int       X,
  [in]           int       Y,
  [in]           int       nWidth,
  [in]           int       nHeight,
  [in, optional] HWND      hWndParent,
  [in, optional] HMENU     hMenu,
  [in, optional] HINSTANCE hInstance,
  [in, optional] LPVOID    lpParam
);
```

​	但是实际上你使用的时候使用的是CreateWindowEx，，这是一个根据是否存在Unicode而静态解析的宏：

```
#ifdef UNICODE
#define CreateWindowEx  CreateWindowExW
#else
#define CreateWindowEx  CreateWindowExA
```

## C RunTime库

​	**C run-time library里面含有初始化代码，还有错误处理代码(例如divide by zero处理)。你写的程序可以没有math库，程序照样运行，只是不能处理复杂的数学运算，不过如果没有了C run-time库，main()就不会被调用，exit()也不能被响应。因为C run-time library包含了C程序运行的最基本和最常用的函数。**

​	也就是说他给我们C语言的环境提供了支持。

​	不关心其他，我们今天看看这里的字符串相关API。

### 老生常谈的ASCII和UNICODE支持性

​	使用`_t...`类的函数，他将会动态的决定是使用何种版本的字符串。对于宽字符串处理函数则是以w作为前缀：反之就是正常的C库函数：

```
_Check_return_
_ACRTIMP size_t __cdecl wcslen(
    _In_z_ wchar_t const* _String
    );
    
_Check_return_
size_t __cdecl strlen(
    _In_z_ char const* _Str
    );
```

### 安全字符串函数

​	许多系统安全问题是由缓冲区处理不善和生成的缓冲区溢出引起的。（你猜猜为什么老谭的gets挂了，就是因为缓冲区问题） 糟糕的缓冲区处理通常与字符串操作相关联。 C/C++ 语言运行时库 (**strcat**、 **strcpy**、 **sprintf** 等) 提供的标准字符串操作函数不会阻止写入缓冲区末尾。

​	两组新的字符串操作函数（称为 *安全字符串函数*）提供额外的处理，以便在代码中正确处理缓冲区。 这些安全字符串函数在 Windows 驱动程序工具包 (WDK) 以及 Microsoft Windows XP SP1 及更高版本的驱动程序开发工具包 (DDK) 和 Windows SDK 中可用。 它们旨在替换其内置的 C/C++ 对应项和 Windows 提供的类似例程。

​	一组安全字符串函数用于内核模式代码。 这些函数在名为 Ntstrsafe.h 的头文件中原型。 WDK 中提供了此头文件和关联的库。

​	另一组安全字符串函数用于用户模式应用程序。 相应的头文件 Strsafe.h 包含这些函数的原型。 该文件和关联的库在 Windows SDK 中可用。

> 有关 Strsafe.h 的详细信息，请参阅 [使用 Strsafe.h 函数](https://learn.microsoft.com/zh-cn/windows/win32/menurc/strsafe-ovw)。

## 推介的字符和字符串处理的方式

我们应该遵守如下准则：

- 首先开始将文本字符串想象为字符的数组，而不是字节的数组。
- 用通用数据类型来表示文本字符和字符串，用明确的数据类型来表示字节，字节指针和数据缓冲区。
- 用这些宏`TEXT()` `_T()`来表示字面量字符和字符串，但是为了保持一致性和更好的可读性，请不要混用！
- 执行全局替换！例如使用PTSTR替换PSTR
- 修改与字符串相关的计算：例如函数经常希望我们传给他缓冲区大小的字符数，而不是字节数！这意味着我们需要传入`__countof(szBuf)`而不是`sizeof(szBuf)`！而且如果需要为一个字符串分配一个内存块，而且知道字符串中的字符数！那么要记住内存是以字节来进行分配的！需要调用`malloc(NCh*sizeof(TCHAR))`
- 避免使用printf系列函数！尤其是不要用%S字段类型来进行ANSI与Unicode字符串之间的表示！正确的方式使用`MultiByteToWideChar`和`WideCharToMultiByte`

​	对于字符串处理函数应该遵循以下原则

- 始终使用安全的字符串处理函数，例如后缀为杠S的函数或者前缀为StringCCH的函数！后者主要在我们想明确控制截断的时候用，如果并不想明确控制截断，使用前者！

- 不要使用不安全的C运行库字符串处理函数！一般情况下，如果一个缓冲区处理函数的参数中不包括目标缓冲区的长度，那么我们应该避免使用这个函数！而且还同样避免自己实现这样的函数！

- 不要使用kernel32方法进行字符串处理比如lstrcat等函数

- 对于想要显示在界面上的字符串如果想要处理它使用来类似于CompareString这样参数涉及到国际化的参数的函数处理！

  因为在比较字符串的时候它会考虑用户的区域设置 

## ASCII与UNICODE互转

> ASCII转UNICODE

```
int MultiByteToWideChar(
  [in]            UINT                              CodePage,
  [in]            DWORD                             dwFlags,
  [in]            _In_NLS_string_(cbMultiByte)LPCCH lpMultiByteStr,
  [in]            int                               cbMultiByte,
  [out, optional] LPWSTR                            lpWideCharStr,
  [in]            int                               cchWideChar
);
```

> `[in] lpMultiByteStr`指向要转换的字符串的指针。
>
> `[in] cbMultiByte`：
>
> *lpMultiByteStr* 参数指示的字符串的大小（以字节为单位）。 或者，如果字符串以 null 结尾，则可以将此参数设置为 -1。 请注意，如果 *cbMultiByte* 为 `0`，则函数将失败。
>
> 如果此参数为 -1，则该函数将处理整个输入字符串，包括终止 null 字符。 因此，生成的 Unicode 字符串具有终止 null 字符，并且 函数返回的长度包括此字符。
>
> 如果此参数设置为正整数，则函数将完全处理指定的字节数。 如果提供的大小不包含终止 null 字符，则生成的 Unicode 字符串不会以 null 结尾，并且返回的长度不包括此字符。
>
> `[out, optional] lpWideCharStr`指向接收转换字符串的缓冲区的指针。
>
> `[in] cchWideChar` `lpWideCharStr`指示的缓冲区的大小（以字符为单位）。 如果此值为 `0`，则该函数返回所需的缓冲区大小（以字符为单位），包括任何终止 null 字符，并且不使用 *lpWideCharStr* 缓冲区。

​	咋用？

1. 调用`MultiByteToWideChar`函数，而参数`lpWideCharStr`传入`NULL`，为`cchWideChar`参数传入0，`cbMultiByte`参数传入-1，，然后接受返回值！
2. 分配一块足以容纳转换后的Unicode字符串的内存，它的大小是上一个函数调用的返回值乘以`sizeof(wchar_t)`
3. 再次调用这个函数，这一次而参数`lpWideCharStr`传入分配的缓冲区地址，为`cchWideChar`参数传入缓冲区大小，`然后接受返回值！
4. 使用它！
5. 释放这个内存块！

>UNICODE转ASCII

```
int WideCharToMultiByte(
  [in]            UINT                               CodePage,
  [in]            DWORD                              dwFlags,
  [in]            _In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
  [in]            int                                cchWideChar,
  [out, optional] LPSTR                              lpMultiByteStr,
  [in]            int                                cbMultiByte,
  [in, optional]  LPCCH                              lpDefaultChar,
  [out, optional] LPBOOL                             lpUsedDefaultChar
);
```

​	如法炮制！具体的说明请查看Reference的文档！

# Reference

>[Unicode、UTF-8、UTF-16之间的区别 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/259386795)
>
>[C运行时库（C Run-time Library）详解_run_time-CSDN博客](https://blog.csdn.net/wqvbjhc/article/details/6612099)、
>
>[MultiByteToWideChar 函数 (stringapiset.h) - Win32 apps | Microsoft Learn](https://learn.microsoft.com/zh-cn/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar)
>
>[WideCharToMultiByte 函数 (stringapiset.h) - Win32 apps | Microsoft Learn](https://learn.microsoft.com/zh-cn/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte)