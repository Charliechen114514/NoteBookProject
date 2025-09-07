# Windows系统编程系列——说一说Windows下的静态库和动态库

​	我们在日常的工程中，总是跑不了使用静态库和动态库。笔者的CCIMXDesktop就是这样的——即使用了静态库作为一个简单的可重定位文件的集合，又使用动态库作为一个插件来高效使用。这一篇博客尝试梳理 **Windows 下静态库（static library）与动态库（DLL/shared library）的制作、原理、使用与常见陷阱**。

## 所以，先说说静态链接和动态链接！

- **静态链接**把需要的目标代码（`.obj`）在链接期合并进最终可执行文件（`.exe`）；结果体积大但部署简单。
- **动态链接（DLL）**把符号的实际实现留到运行时，由 OS loader 映射 DLL、解析导入（IAT）、并把函数地址写入可执行文件的导入表；优点是共享内存页、可替换/扩展但需要管理版本与搜索路径等问题。

#### 编译的基本步骤

1. **编译（Compile）**：源代码（`.c/.cpp`）被编译器翻译为目标文件（`.obj`，COFF object）。每个 `.obj` 含符号表、节（.text/.data/.rdata 等）与重定位信息。
2. **链接（Link / Link-time）**：链接器把若干 `.obj` 与静态库（`.lib`）合并，解决未定义符号、合并节，并产出最终镜像（`.exe` 或 `.dll`）。链接期可以：
   - 把静态库中需要的 `.obj` 拷贝进输出（静态链接），或
   - 对于 DLL：使用 *导入库（import library）* 在链接期产生对 DLL 的引用（但不把实现拷入），最终生成能在运行时由 loader 解析的 import information（IAT）。
3. **装载/运行时（Load / Run-time）**：当进程启动或调用 `LoadLibrary` 时，Windows loader 映射镜像到进程地址空间，处理导入（查找导出、写入 IAT）、应用重定位、调用初始化（CRT、TLS callbacks、`DllMain`）等。理解 loader 的具体步骤对诊断运行时链接错误至关重要。

#### 补充一下：Windows的可执行文件都是Portable Executable的格式

Windows 可执行文件（.exe / .dll / .sys / .obj / .lib）都基于 **PE/COFF**（Portable Executable / Common Object File Format）族；其中 `.obj` 是 COFF 对象，`.exe`/`.dll` 是将 COFF 包装成 PE 的镜像。PE 包含 DOS Header、PE Header、节表、数据目录（Import Table、Export Table、Relocations、Certificate 等）。理解 Export（导出表）/Import（导入表 / IAT）/Relocation（重定位表）对于理解 DLL 加载机制非常关键。

------

## 两种产物：静态库和动态库

### 静态库（`.lib`） —— “把代码贴到 exe 里的Archive”

#### 1) `.lib` 的两种“长相”

- **静态 `.lib`（archive of .obj）**：真正包含实现的 COFF archive，链接器会把需要的 `.obj` 拷贝到 exe 中（Unix 上类似 `.a`）。
- **导入库 `.lib`（import library for a DLL）**：当你用 MSVC 编译生成 DLL 时，链接器通常也会产出一个小 `.lib`——它不是实现，而是“存根/重定向”，告诉链接器该符号来自某个 DLL（运行时由 loader 提供）。二者虽同扩展名但用途不同，混淆会导致部署或链接错误（缺少 DLL 或者链接到错误的实现）。

#### 2) 静态链接的工作机制（细节）

- 链接器按**目标文件顺序**解析未定义符号：当链接器找到某个符号的定义时，会把该 `.obj`（或其中被请求的 COMDAT 段）引入。静态库是“按需”提取的（只有被引用的 `.obj` 被拉入）。这解释了“把库放在链接命令后面很重要”的历史原因。
- **COMDAT 与重复定义**：现代编译器将每个函数放到独立 COMDAT 节（`/Gy`），链接器可以做 *Identical COMDAT Folding*（/OPT:ICF）来合并相同实现以节省空间；同样，链接器在遇到真正冲突时会报错（LNKxxx）。这些机制影响模板实例、inline 与重复定义的行为。

#### 优缺点小结

- 优点：部署简单（exe 独立）、不需运行时依赖；启动时不需要 loader 解析依赖。
- 缺点：体积大、无法在运行时替换实现、对更新/bugfix 不友好；重复使用代码会导致内存占用（不可共享代码页）。

------

### 动态库（DLL）与导入/导出机制（核心）

#### 什么是 DLL（文件/结构）

DLL 是一种 PE 映像（与 EXE 类似），但含有 **Export Table（导出表）**，列出可被外部模块调用的函数/变量（以及可选的 forwarder 字符串）。只有列在导出表中的符号才可被 `GetProcAddress` 或隐式导入访问。要查看导出表，可以用 `DUMPBIN /EXPORTS`。

#### 导出符号的三种常见方式

- `__declspec(dllexport)`（源代码级别直接导出）。
- `.def` 文件（module-definition）：显式列出导出名与序号。
- 链接器自动/工具（MinGW 的 auto-export 等）。
   备注：C++ 名字修饰（name mangling）会让导出名变成编译器特定的装饰名，若需要跨语言/跨编译器，建议导出 `extern "C"` 的 C ABI wrapper。官方关于 `.def`、`__declspec` 的用法有示例。

#### 隐式链接（load-time） vs 显式链接（run-time）

- **隐式（Load-time）**：编译/链接时用到导入 `.lib`，程序启动时 OS loader 自动加载依赖 DLL 并把地址写入 IAT（Import Address Table）。如果依赖的 DLL 缺失，进程无法启动。
- **显式（Run-time, 动态加载）**：程序在运行时用 `LoadLibrary/LoadLibraryEx` 加载 DLL，再用 `GetProcAddress` 得到函数指针并调用（更灵活，适用于插件/可选依赖）。官方关于这些 API 的文档在此。

#### Delay-load（延迟加载）

MSVC 链接器支持 `/DELAYLOAD`，把本应隐式加载的 DLL 延迟到首次调用时再加载（由 delay-imp 帮手处理），介于隐式与显式之间，便于可选依赖与快速启动的折中方案。

#### DLL的一些好处

**代码节（.text）可被多个进程共享**（物理页共享）——这是动态库复用节省内存的一个核心优势。

**数据节（.data）默认是每进程私有**；如果需要跨进程共享内存可以使用命名内存映射（CreateFileMapping / MapViewOfFile）或在 DLL 的节属性上使用 `#pragma data_seg`（需小心安全性与布局）。这些属于高级技巧且有权限/安全考量。

------

## Windows loader 是如何一步一步加载DLL的？

这是理解“为什么程序启动时报错：找不到某个函数/无法加载模块”的关键。

1. **定位 DLL 文件**（搜索顺序，见第五节）。
2. **映射（Map）映像到进程虚拟地址空间**：按 PE 的节表映射 `.text`、`.rdata`、`.data` 等为内存页。代码节通常设为只读并可共享（多个进程可共享物理页）。
3. **应用重定位（Base Relocations）**：如果镜像不能被加载到其“首选基址（ImageBase）”，loader 会用重定位表（Relocation Table）修正地址引用；在支持 ASLR 的系统上，镜像通常会被随机化，需要重定位。**解析导入表（Import Table / IAT）**：loader 读取目标模块的 Import Table（IMAGE_IMPORT_DESCRIPTOR），对每个被导入的 DLL，查找其 Export Table（EAT），把函数地址写入调用模块的 IAT（这样程序里的外部调用最终跳转到 IAT 表项）。理解 IAT 与 EAT 的关系是动态链接的核心
4. **调用 CRT 初始化 / TLS 回调 / DllMain**：映射与 IAT 修正后，CRT（如果有）会运行全局对象构造（C++）、TLS 回调会被触发，最后 loader 调用模块入口（`DllMain`）接收 `DLL_PROCESS_ATTACH` 等通知（注意 DllMain 的限制）。

------

## DLL 搜索顺序与安全（DLL 劫持问题）

#### 搜索顺序（概念）

Windows 的默认 DLL 搜索顺序历史复杂，现代建议**不要依赖默认搜索顺序**，而是使用 `LoadLibraryEx` 的 `LOAD_LIBRARY_SEARCH_*` 标志或 `SetDefaultDllDirectories`、`AddDllDirectory` 来显式指定受信任目录，从而避免 DLL 劫持（“DLL Hijacking”）与版本混淆问题。微软对搜索顺序与安全提供了明确的 API 与建议。

#### 典型恶劣案例

- 把可写目录（如当前工作目录）放到搜索前面会被攻击者利用：将恶意同名 DLL 放在应用目录或工作目录，程序会加载恶意库。使用 `SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32|... )` 并用绝对路径加载可以缓解风险。

------

## 一些注意事项

`DllMain` 在 loader 持有 *loader lock* 时被调用，因此在 `DllMain` 中**不能做会导致再次加载/初始化其他 DLL 或阻塞很久的工作**（例如调用 `LoadLibrary`、创建线程并等待、使用某些需要 loader 的 API、调用 COM 初始化或做耗时 I/O 等）。错误的 DllMain 实现会导致死锁或崩溃。微软有专门章节说明这些注意事项。loader lock 是 loader 用来序列化模块列表修改与初始化的内部锁；当你在 DllMain 中做会触发 loader 再次尝试获取 loader lock 的操作时，就会发生死锁。调试时若看到 `LdrLockLoaderLock` 栈顶，通常跟 loader lock 问题相关。

如果主程序与 DLL 使用不同版本或不同链接模式的 CRT（例如 EXE 使用 `/MT` 静态 CRT、DLL 使用 `/MD` 动态 CRT），那么**一个模块分配、另一个模块释放内存**会导致 heap corruption 或崩溃。类似风险也发生在把 STL（`std::string`、`std::vector`）对象跨 DLL 边界传递时。最佳实践：**在模块边界使用简单 C 风格 ABI，或保证所有模块使用相同 CRT** / 同一编译器版本。微软对此有专门文档说明。

------

## 工程意见：符号导出/名字修饰与跨语言互操作

1. 选择**动态库**用于插件化、减小 exe 大小、支持热更新与共享内存页；选择**静态库**用于部署简单、性能敏感或需要避免运行时依赖的场景。
2. **一致的工具链与 CRT**：在同一进程内尽量使用相同的编译器/CRT 选项，或者在模块边界严格控制内存/资源的分配与释放策略。
3. **安全加载**：使用 `LoadLibraryEx` 的安全标志或 `SetDefaultDllDirectories`，明确路径加载以防 DLL 劫持；并在部署时包含或安装合适的 VC++ redistributable。
4. **C++ 名字修饰**导致导出的名字不是可读的 `func`，而是编译器特定的装饰名（decorated name），因此若要跨语言或用 `GetProcAddress` 寻址，**建议导出 `extern "C"` 的 wrapper** 或使用 `.def` 显式指定导出名。若在 `.def` 中写入 C++ 被修饰名，就需保证调用方用同一编译器/版本。
5. **导出 C++ 类**（vtable、成员函数）会引入复杂的 ABI 问题（不同编译器/版本间不稳定）。解决方案通常是导出**工厂函数 + 抽象接口（纯虚类指针/opaque handle）**，让实现细节留在 DLL 内部。实践中把 ABI 层做为 C 风格或 COM 接口更稳健。



## 如何用 MSVC 工具链制作（最常见的流程与命令示例）

### 静态库（MSVC）

示例代码 `add.cpp`：

```cpp
// add.cpp
int add(int a, int b) { return a + b; }
```

构建命令（开发者命令提示符）：

```bat
cl /c /EHsc add.cpp      # 生成 add.obj
lib /OUT:libadd.lib add.obj   # 生成静态库 libadd.lib
```

使用：

```bat
cl /EHsc main.cpp libadd.lib
```

### 动态库（DLL，MSVC）——隐式链接（link-time）

示例代码（导出符号的惯用方法）：

```cpp
// mydll.h
#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

extern "C" MYDLL_API int add(int a, int b);

// mydll.cpp
#define MYDLL_EXPORTS
#include "mydll.h"
int add(int a, int b) { return a + b; }
```

构建：

```bat
cl /LD /EHsc mydll.cpp   # /LD 会让链接器生成 mydll.dll 与 mydll.lib（import library）
```

说明：

- `/LD`（或把项目类型设为 DLL）会生成 `mydll.dll`，同时生成一个 `mydll.lib`（import lib）供其他模块在链接期使用。运行时加载时，系统通过 DLL 的 Export Table 提供符号。微软的教程对创建并使用 DLL 有详细的 walkthrough。

### 动态库（DLL）——使用 .def 文件

`.def`（module-definition）文件可以显式列出导出符号和序号，示例 `mylib.def`：

```
LIBRARY "mylib"
EXPORTS
    add @1
```

用法（示例）：

```bat
cl /c mylib.cpp
link /DLL /DEF:mylib.def /OUT:mylib.dll mylib.obj
```

或者先用 `lib /DEF:mylib.def /OUT:mylib.lib` 生成 import lib。微软文档说明如何用 `LIB` 与 `/DEF` 配合。([Microsoft Learn](https://learn.microsoft.com/en-us/cpp/build/reference/working-with-import-libraries-and-export-files?view=msvc-170&utm_source=chatgpt.com))

------

## 如何用 MinGW/GCC 生成 DLL？

MinGW 的 linker（ld）也能生成 DLL，生成 import library 的参数是 `--out-implib`（生成 `.a`），示例：

```sh
# 编译
gcc -c -o mydll.o mydll.c
# 生成 dll 与 implib (libmydll.a)
gcc -shared -o mydll.dll mydll.o -Wl,--out-implib,libmydll.a
# 链接到可执行
gcc main.c -L. -lmydll
```

注意：MinGW 产生的 import lib 默认是 `lib*.a`，MSVC 要求的是 `.lib`，跨编译器互操作时需注意 import lib 格式差异（可用 `gendef`/`dlltool` 或生成 `.def` 然后用 MSVC 的 `lib` 生成 .lib）。社区与教程对 MinGW 生成 DLL 的流程有大量实践指南（如 TransmissionZero 的教程等）。

------

## 调试与分析工具（常用命令与用法）

- `dumpbin`（随 VS 提供）——`dumpbin /EXPORTS foo.dll` 查看导出，`dumpbin /DEPENDENTS exe.dll` 查看依赖。
- `dependency walker (depends.exe)`：老牌工具，可静态查看依赖与导出（注意某些新 Windows 特性不完全兼容）。
- `Process Monitor` / `Process Explorer`：查看运行时 Loader 在查找哪些文件并诊断找不到 DLL 的原因。
- `linker`/`lib` 的输出日志和 Visual Studio 的 Link 输出也能给出链接期缺失符号的线索。
- 使用 `dumpbin /ARCHIVEMEMBERS` 查看 `.lib` 内容（如果是静态 `.lib`，可以看到包含的 object）。