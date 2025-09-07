# Android系统学习2——Android.Utils.Log模块讨论

​	打日志是一个很好的习惯，有的时候我们可以通过这里排查我们的程序的问题。在这里，我们可以从Android的日志机制入手讨论我们的Log模块。

#### `android.util.Log` 类的作用

Android 中最常用的日志工具是 `android.util.Log`，它提供了多个静态方法来打印日志：

- `Log.v()`（Verbose）
- `Log.d()`（Debug）
- `Log.i()`（Info）
- `Log.w()`（Warning）
- `Log.e()`（Error）

Stack Overflow 的实战建议：

> Log.e：用于捕获“真正”的错误，比如异常捕获块中。
>  Log.w：用于捕获“可疑”但不至于崩溃的情况。
>  Log.i：表示成功或信息性的状态，如连接成功。
>  Log.d：用于调试，打印变量、执行流程等。
>  Log.v：用于“疯狂”式的日志输出，记录非常详细的信息。这个信息可以用来最大程度的登记我们的信息

### 2. 底层机制如何运作？

- `android.util.Log` 的方法最终调用一个 native 方法 `println_native`，这个 native 方法将日志发送到系统底层的 `logd` 服务。
- 对于 C/C++ 层的日志，通过 `liblog`（NDK 中的日志库）实现，最终同样写入 `logd`，日志被分发到不同的环形缓存（circular buffers）：`main`（主应用日志）、`system`（系统日志）、`crash`（崩溃日志）等 。

日志在发出后，会经过不同级别的过滤：

1. **编译时过滤**：ProGuard 等工具可以移除 `Log.d`、`Log.v` 等日志。
2. **系统属性过滤**：若设置了 `log.tag.<TAG>` 属性，`liblog` 会根据其值决定是否发送该日志。
3. **应用级过滤**：通过 `__android_log_set_minimum_priority`，可设置最低日志等级，默认是 `INFO`。
4. **展示过滤**：`adb logcat` 或 Android Studio 可按 tag/级别过滤展示内容。

------

## Logcat 与 Android Studio 的配合使用

#### Logcat 是什么？

Logcat 是 Android 提供的日志查看工具，包括：

- 命令行工具：`adb logcat` 或直接在设备 shell 中执行 `logcat`
- Android Studio 内置的 Logcat 窗口，可以实时查看设备或模拟器产生的日志

在 Android Studio 中，Logcat 窗口默认显示每条日志的以下信息：**日期、时间戳、进程 ID、线程 ID、Tag、包名、优先级、消息内容**，不同优先级使用不同颜色显示，便于快速识别（例如 Error 通常是红色）

#### 如何高效使用 Logcat？

- **过滤功能**：可根据 Log 等级（Verbose、Debug、Info、Warning、Error、Assert）过滤日志，只关注重要内容 
- **文本搜索**：支持文本或正则表达式搜索日志内容 
- **自定义过滤器**：Android Studio 会自动为 debuggable 应用生成过滤器，也可以自行创建过滤条件（tag、应用包名等）
- **分区查看**：在 Logcat 面板中，可以开启“Scroll to End”、暂停、清除日志等控制按钮来方便查看 

## 原理分析

#### 总体架构：从 `Log` 到 `liblog` 再到 `logd` 与环形缓冲区

Android 的日志系统由系统进程 **`logd`** 维护的**结构化环形缓冲区**组成。各语言层（Java/Kotlin、C/C++）的日志最终都会进入这些缓冲区，然后由 IDE（Android Studio 的 Logcat 视图）或命令行工具（`adb logcat`）读取与过滤。缓冲区是**循环覆盖**的（不是无限增长，也不会跨重启持久化，除非设备厂商/工程构建开启了持久化日志服务）。

日志写入路径大致如下：

- **应用层**：`android.util.Log`（Java/Kotlin）或 `<android/log.h>`（NDK）。
- **系统库**：所有语言最终会调用 **`__android_log_write`**（位于 `liblog`），默认通过 socket 将日志条目送至 **`logd`**。从 **API 30** 起，可以通过 `__android_set_log_writer` 替换默认写入函数（通常用于特殊场景或主机端单元测试）。
- **缓冲区（主要）**：`main`（应用为主）、`system`（系统组件）、`crash`（崩溃相关）等。NDK 文档列出 `MAIN / EVENTS / CRASH / KERNEL / DEFAULT` 等 ID，并明确**普通应用仅能写入/访问 `MAIN`**。

Android 将不同来源、不同优先级的消息统一汇聚到这些缓冲区，形成最终你在 Logcat 中看到的“混合”流。AOSP 文档也特别指出，Logcat 里混合了不同标准（如 `android.util.Log`、`syslog` 风格等）的日志

------

#### 2）`android.util.Log` 的 API 与真实行为

`Log` 提供六个主流级别（VERBOSE/DEBUG/INFO/WARN/ERROR/ASSERT），对应静态方法 `v/d/i/w/e/wtf`，以及底层的 `println()` 重载。Logcat 过滤时常用到首字母：`V/D/I/W/E/A`；`S`（silent）常用作过滤规格中的“全静音”。（级别与过滤法在命令行与 IDE 里一致，文后有速查。）

#### `isLoggable()` 与系统属性开关

`Log.isLoggable(tag, level)` 可在**运行时**读取系统属性 `log.tag.<TAG>`（或全局 `log.tag`）来判断某个 tag 在某级别是否应当输出，从而**避免拼接大对象或格式化字符串的性能开销**。例如：

```kotlin
private const val TAG = "BillingManager"

fun query() {
  if (Log.isLoggable(TAG, Log.DEBUG)) {
    Log.d(TAG, "Querying items: ${expensiveToString(items)}")
  }
}
```

这一行为在 AOSP 源码 `Log.java` 里写得很清楚：它会查询系统属性来决定是否可记录。

> 实用例：临时开启某 tag 的 DEBUG
>  `adb shell setprop log.tag.BillingManager DEBUG`（需开发者设备/有权设置属性环境）→ 你的 `isLoggable(..., DEBUG)` 即会返回 true（直到设备重启/属性被还原）。

#### Tag 的长度限制（历史与现状）

AOSP 在 `Log.java` 的注释中提到：**在 Android 7.0（Nougat）及更早**版本中，tag 长度**曾经被强制限制为 23 个字符**。后续版本**放宽**了这一限制，但出于兼容性考虑，某些分组/过滤默认行为仍保留历史痕迹（避免与旧系统混用时出现“错误分组”）。如果你在维护非常老的设备或需要兼容老系统，这条历史尤为重要；新系统上则基本不用刻意把 tag 缩到 23 以内。

#### `Log.wtf()`（What a Terrible Failure）

`wtf()` 用于记录**绝不应该发生**的错误情况。AOSP 注释直言：**可能导致进程退出**（取决于系统配置），因此请仅在“逻辑上不可能出现”的致命条件下使用。IDE/命令行里它对应 **ASSERT** 级别。

#### 其他便利用法

- `Log.getStackTraceString(Throwable)`：将异常堆栈转为字符串，避免你自己 `StringWriter`/`PrintWriter` 的样板代码。

------

### Android Studio 的 Logcat（即“Logcat v2”）——更强大的 IDE 端查询与 UI

从新版 Android Studio 起，Logcat 采用流式视图与**键值式查询语法**，能非常方便地组合条件过滤，例如：

- `package:com.example.myapp level:W`（仅看你应用的警告及以上）
- `tag:OkHttp|OkHttpClient level:D`（多个 tag 的或关系）
- `pid:12345`、`uid:10234`、时间范围、正则等

Logcat 视图还支持**分栏（Split）**、**固定（Pin）**多个查询、历史自动补全与更灵活的布局/配色设置。进入 **Settings > Tools > Logcat** 可调整循环缓冲读入、默认过滤器、历史补全等；配色在 **Editor > Color Scheme > Android Logcat**。

------

### 命令行 `adb logcat` 速查：从过滤规格到缓冲区与格式

命令行在 CI、远程联调或采集日志包时非常关键。官方文档要点如下：

### 常用命令与过滤规格（filterspec）

- **基本：**

  ```bash
  adb logcat                # 持续输出
  adb logcat -d             # dump 一次并退出
  adb logcat -c             # 清空缓冲区（慎用）
  ```

- **过滤规格（经典语法）：** `TAG:LEVEL *:S`
   例如：`adb logcat MyTag:D *:S`（只看 `MyTag` 的 DEBUG 及以上，其它静默）。LEVEL 取 `V/D/I/W/E/A`。

- **按进程/用户过滤：**

  ```bash
  adb logcat --pid=$(pidof com.example.myapp)
  adb logcat --uid=10234
  ```

- **选择缓冲区：** `-b <buffer>`
   常见：`main`（默认）、`system`、`crash`、（设备/构建不同还可能有 `events`、`radio` 等）。
   例：`adb logcat -b crash *:S`（只看崩溃缓冲区）。

- **输出格式：** `-v <format>`
   常用 `threadtime`（包含日期、时间、PID/TID、级别、tag、消息），也有 `raw`、`time`、`long` 等。

- **缓冲区大小：**

  - 查看：`adb logcat -g`
  - 设置：`adb logcat -G 10M`（需具备相应权限/构建允许）

> NDK 侧说明：`LOG_ID_MAIN` 是**应用唯一可用**的日志缓冲区；其它如 `EVENTS`/`CRASH`/`KERNEL` 通常不对三方应用开放。

------

## 5）权限与可见性：为什么应用“看不到别人的日志”

- 普通第三方应用**不能**随意读取系统/他应用的 Logcat。早年曾有 `READ_LOGS` 权限，但现在**仅限系统/同签名应用**使用；你的应用**只能读取自己产生的日志**。
- 开发时，**通过 `adb`（USB 调试）** 可以从主机上查看系统范围的日志（受设备安全策略与构建类型影响）。IDE 的 Logcat 也正是借助这一渠道做富交互过滤与展示。

------

## 6）性能与隐私安全：必须重视的硬性要求

- **避免记录任何 PII/敏感信息**（账号、令牌、位置、联系人、银行卡等），除非这对应用核心功能绝对必要；Android 安全最佳实践与合规指南明确提出此要求。
- **发布版尽量减少/去除冗余日志**：可以在发布构建里借助 `Log.isLoggable()`、编译器优化或混淆配置减少日志开销与暴露面（同时保留必要的错误/关键指标）。OWASP 移动安全测试指南同样建议在生产版避免输出敏感数据。
- **性能注意**：对大对象 `toString()`、字符串拼接、昂贵计算要**先用 `isLoggable()` 判定**再输出，避免在日志被过滤时仍然产生计算/分配成本。（见第 2 节示例。）

### 一些搜集到的问题：

- **为何某些日志“重复被折叠/合并”**：系统为抑制刷屏，`logd`/Logcat 会对大量重复行做“chatty” 合并（你会看到类似合并提示行）。这是**日志守护进程层面的限流策略**，用于提升可读性与性能。官方命令行文档在“日志系统概述”中描述了 `logd` 与缓冲区特性（合并提示本质上来自 logd 的输出策略）。
- **崩溃日志在哪看**：
  - Java/Kotlin 崩溃栈会进入 Logcat，并可在 **`-b crash`** 缓冲区快速定位。
  - **Native 崩溃**还会产生 **tombstone** 文件，AOSP 有完整的排查文档，配合 Logcat 能更快锁定原因。
- **缓冲区容量不够（日志被覆盖）**：用 `adb logcat -g` 看大小，必要时临时用 `-G` 调大（注意设备/构建权限）。IDE 侧也可以在 Settings > Tools > Logcat 调整读取策略与默认过滤器，提高“看到关键行”的概率。



