# Kotlin编程学习记录1

## 前言

​	笔者最近同时也在开始Schedule Kotlin的学习，这门JVM虚拟机语言是笔者打算跟Java一起联合学习的，当然，学习这个更多的是出于对Kotlin/Java等JVM虚拟机语言的使用和底层原理 + 新技术领域的扩展。因此，这个系列的博客显然会比其他笔者的系列博客要稍微简单一些。

​	这里默认读者之前已经掌握了至少一门编程语言，不再像类似Head First Kotlin那样做这么基础的讲解了。

## Kotlin的变量声明

Kotlin 的变量声明看起来简洁，但细节很多：可变/不可变、类型推断与显式类型、可空性、初始化时机（`lateinit`、`lazy`）、编译时常量（`const val`）、属性的 getter/setter/backing field、以及委托属性等。

------

## `var` vs `val`：可变性与语义

​	Kotlin笔者认为作为一门比较现代的语言，收到了函数式编程语言的影响，也会重点关心变量自身的可变性。当然，这里我们有两种赋值。

- `var`：可被重新赋值（mutable）。
- `val`：只读（read-only），只能被赋值一次；**注意**：`val` 表示引用不能再指向另一个对象，但并不保证对象本身是不可变（对象内部状态仍可能被修改）。

val有点像具备const修饰的var，也就是字面值的含义，熟悉C/C++的朋友都知道，字面值是不可以变动的。所以Kotlin把恒定值（只读值）叫做val有一定的道理

示例：

```kotlin
var count = 0      // 可变
val name = "Alice" // 只读（不能再赋新值给 name）

val list = mutableListOf(1,2)
// list = mutableListOf() // 编译错误：不能给 val 重新赋值
list.add(3) // 但可以修改 list 的内部状态
```

**建议**：默认用 `val`，只有确实需要重赋值时使用 `var`。

------

## 显式类型与类型推断（Type inference）

Kotlin 支持在声明时省略类型，由编译器推断（尤其常见于局部变量与简单初始化）。当初始化表达式无法明确类型或出于 API 可读性时，可显式指定类型。类型推断规则更复杂（局部推断、函数签名推断等）。

```kotlin
val x = 42          // Int，类型由编译器推断
val s: String = "Kotlin" // 显式类型

val items = listOf(1, 2, 3) // items 类型被推断为 List<Int>
```

​	我们可以看到，Kotlin中我们的属性推导是完全交给编译器做的，而不是程序员。这有点像咱们C++的auto。

- 当需要表达泛型/可空/宽松类型时，建议写出显式类型以提高可读性。
- 对于复杂的表达式或 lambda 返回的推断结果不明确时，写出类型能避免歧义。

------

## 可空性（Nullable）与空安全

Kotlin 将可空性纳入类型系统：在类型后加 `?` 表示可空，例如 `String?`。非空类型（`String`）在编译时由编译器保证不能赋 `null`，从而减少 NPE（NullPointerException，空指针）。常见操作符包括安全调用 `?.`、Elvis 操作符 `?:`、非空断言 `!!`（会在运行时抛出 NullPointerException）。

```kotlin
var name: String? = null
println(name?.length)         // 安全调用，结果为 null
val len = name?.length ?: 0   // Elvis：如果为 null 则使用备用值
// val crash = name!!.length  // 非空断言，若 name 为 null 则抛出异常
```

**Java 互操作提示**：来自 Java 的类型在 Kotlin 中经常是 “平台类型”，编译器放宽空检查，调用方仍需谨慎处理。

## 初始化时机与 `lateinit`

对类成员属性而言，非空属性通常必须在构造时初始化。`lateinit` 提供延迟初始化（仅用于 **可变属性 `var`**、**非空引用类型**，不能用于基本类型），常用于依赖注入或测试中在构造后赋值的场景。使用 `lateinit` 前应保证实际在使用前已初始化；可以通过 `::prop.isInitialized` 检查。

```kotlin
class MyActivity {
    lateinit var repo: UserRepository // 强迫编译器放松检查，且保证我们会使用前已初始化

    fun setup(r: UserRepository) {
        repo = r
    }

    fun use() {
        if (::repo.isInitialized) {
            repo.load()
        }
    }
}
```

**限制/注意**：

- `lateinit` 只能修饰 `var`、非空引用类型；不能修饰 `val` 或基本类型（`Int`、`Boolean` 等）。
- 如果在未初始化时访问会抛出 `UninitializedPropertyAccessException`。

------

## 编译时常量 `const val`

当值在编译期已知、需要被内联（在字节码中直接替换字面量）时，用 `const val`。`const val` 有严格的要求（例如只能用于顶层或 `object` / `companion object` 中、必须为基本类型或 `String`、不能有自定义 getter、初始化表达式必须是编译时常量等）。`const val` 的引用在编译时被内联到使用处，从而避免 getter 调用。

示例：

```kotlin
const val MAX_ATTEMPTS = 3

object Config {
    const val API_VERSION = "v1"	// 等价于C++11+的constexpr了，表达严格的编译常量
}
```

**建议**：

- 把需要跨模块内联并且确实是编译时常量的值用 `const val`，否则用 `val`。

## 函数参数与局部变量的可变性

​	我相信在C++中，很多人都被函数的形参和实参困扰过，的确，如果我们是初学者，很容易陷入函数形参和实参的混乱中，对此函数参数在 Kotlin 中是只读的（相当于隐含 `val`），不能在函数体内直接重新赋值；若需要在函数内部修改，需声明新的 `var` 变量或使用另一个局部 `var` 来 shadow（遮蔽）。这是语言设计的一部分，旨在**减少副作用与误用。**

```kotlin
fun foo(x: Int) {
    // x = 10 // 编译错误：参数为只读
    var y = x
    y += 1
}
```

------

## 笔者阅读书籍的一些Ideas

1. **默认 `val`，必要时用 `var`**：尽可能声明为只读，减少不必要的重赋值。
2. **可空性显式化**：`String?` 明示可空，善用 `?.` / `?:` / `let` 等空安全工具。
3. **延迟初始化**：`lateinit` 适用于注入/测试等场景，但要承担检查与异常风险；`by lazy` 适合惰性只读初始化（尤其是开销较大的计算）。
4. **常量用 `const val`**：当需要编译时内联且为基本类型或 `String` 时使用（并遵守作用域限制）。
5. **封装可变集合**：对外暴露 `List<T>` 或使用 backing property 防止外部篡改内部状态。
6. **当心 `val` 的误解**：`val` 仅表示引用不可变（只读），不代表对象内部不可变。

## Kotlin的内置类型

### Kotlin采用了更加激进的面对对象

​	虽然 Kotlin 在语言层面将所有类型看作对象，但出于性能考虑，编译器在运行时会根据具体的场景将某些类型优化为 JVM 的原始类型（primitive）——如 `Int`, `Double`, `Boolean` 等。从语言层面，无需关注到底是对象还是原始类型，Kotlin 程序员只使用统一的类型系统。

### 常见基本数据类型（Numbers, Boolean, Char, String, Array）

- **整数类型**：`Byte`（8 bits）、`Short`（16 bits）、`Int`（32 bits）、`Long`（64 bits）
- **浮点类型**：`Float`（32 bits）、`Double`（64 bits）
- **布尔类型**：`Boolean`，值为 `true` 或 `false`
- **字符类型**：`Char`，16 bits，Unicode 字符
- **字符串**：`String` 类型，作为对象存在，可使用模板语法 `$var`
- **数组**：原始类型或对象类型数组，如 `Array<Int>`、`Array<String>`

此外，还有一些特殊类型如 `Any`（所有非空类型超类）、`Unit`（类似 Java 的 `void`）、`Nothing`（表示无正常返回）等，在扩展类型系统时非常有用。

虽然 Kotlin 表面上不存在“原始类型”的区别（所有类型都是对象），但编译器会在可能的情况下将非空的基础类型自动编译为 JVM 的 primitive 类型，以提高性能。例如 `Int` 在非空环境下会转成 `int`。

且有明确指出：

> “Kotlin 语言本身没有 primitive 类型，它使用包装类如 `Int`, `Float`，但在 JVM 上编译器会在可能的情况下将它们转换为原始类型。”

在讨论区中也提到，例如 `lateinit var` 无法用于 primitive 类型，说明语言层面仍有这种“原始”概念的暗含影响。

# Kotlin的函数（初步篇）

## 基本语法 — `fun`、返回类型、表达式体 vs 块体

​	Kotlin很现代，我们都知道现代语言很喜欢将返回类型后置（C++er表示有点奇怪，但是如果默念：我接受XXX参数，返回XXX，似乎就能理解一些了！）

```kotlin
fun name(params): ReturnType {
	... 
}
```

​	比如说

```kotlin
fun getMax(number1: Int, number2: Int): Int {
    return if(number1 > number2)
            number1 else number2
}
```

如果函数体是单表达式，可以用表达式体并省略 `return`（例如 `fun sum(a:Int,b:Int)=a+b`）。

```kotlin
// 块体 + 显式返回
fun max(a: Int, b: Int): Int {
    return if (a > b) a else b
}

// 表达式体（简洁）
fun sum(a: Int, b: Int) = a + b  // 返回类型由编译器推断为 Int

// 无返回值 -> Unit（类似 Java 的 void）
fun printHello(): Unit { println("Hello") }
// Unit 返回类型通常可以省略
fun printHello2() { println("Hello") }
```

------

## 参数及调用细节：默认参数 / 命名参数 / `vararg` / trailing lambda

​	**默认参数**：Kotlin也有默认参数机制，支持在声明处给参数默认值，减少重载数量。调用时可以省略带默认值的参数。**配合命名参数**（named arguments）非常方便，可读性高。

```kotlin
fun greet(name: String = "World", punctuation: String = "!") {
    println("Hello, $name$punctuation")
}

greet()                     // Hello, World!
greet("Alice")              // Hello, Alice!
greet(punctuation = "?!")   // Hello, World?!
greet(name = "Bob", punctuation = ".")
```

​	Kotlin还支持可变参数：**`vararg`**：可变参数，函数内部以数组访问；

```kotlin
fun log(vararg msgs: String) {
    for (m in msgs) println(m)
}
val arr = arrayOf("a","b")
log(*arr)
```

## 函数类型、lambda、匿名函数、函数引用（作为值传递）

​	**函数类型**： `(Int, String) -> Boolean` 是函数类型的书写方式。函数可以作为参数或者返回值（一等公民）。这一点有点像C++的函数类型。

```kotlin
val f: (Int, Int) -> Int = { a, b -> a + b }
fun higher(op: (Int,Int)->Int) = op(1,2)
```

**lambda vs 匿名函数**：lambda 用 `{} `，匿名函数用 `fun(...) { ... }`。二者在 `return` 行为上不同（详见下）。

**函数引用**：`::println`、`::myFunc` 可以把已有函数作为值传递或存储。这个有点像函数指针

```kotlin
val printer: (Any?) -> Unit = ::println
```

**可空的函数类型**：例如 `((Int) -> String)?` — 要处理 null 情况。

`return` 在 lambda 中默认是**非本地返回（non-local return）** —— 即 `return` 会尝试返回外层函数（不是仅从 lambda 返回），但这仅在对应调用函数是 `inline` 时成立（更多见下节）。若想在 lambda 中只返回 lambda 本身，使用标签 `return@lambdaLabel` 或改用匿名函数。

## 内联/性能相关：`inline` / `noinline` / `crossinline` / `reified`

- **`inline`**：把函数体（以及传入的 lambda）在调用点展开，能避免为 lambda 创建对象、能允许非本地返回、并且可以用来实现 `reified` 泛型参数（retain type info at runtime）。适用于小的高频高阶函数。过度内联会增大字节码（code bloat）。
- **`noinline`**：用于 `inline` 函数中，标记不想内联的 lambda 参数（例如需要把这个 lambda 存储或传给非内联函数）。
- **`crossinline`**：在 `inline` 函数中防止 lambda 使用非本地返回（即禁止 lambda 中的 `return` 退出外层函数），常用于需要把 lambda 包装成 Runnable/对象并在其它上下文调用的情况。
- **`reified`**：只能用于 `inline` 的泛型参数，允许在运行时访问类型信息，解决 JVM 的类型擦除（常用于 `inline fun <reified T> ...`）。

示例（`reified` + `inline`）：

```kotlin
inline fun <reified T> isA(value: Any) = value is T
println(isA<String>("x")) // true
```

**设计建议**：

- 把公共小工具高阶函数考虑 `inline`（比如 `runIf`, `measureTime`）；但避免把大型函数或包含大量代码的函数标 `inline`

------

## `return` 语义、标签（label）与非本地返回（non-local return）

​	普通函数中的 `return` 返回当前函数；在 lambda 中 `return` **默认**会尝试返回外层函数（非本地返回），但只有当调用该 lambda 的函数是 `inline` 的时候才可能（因为只有内联时，lambda 代码被放到外层）。如果你只想从 lambda 本身返回，使用带标签的 `return@label` 或使用 **匿名函数**（`fun(...) {}`）来限定返回。

示例：

```kotlin
fun foo() {
    listOf(1,2,3).forEach {
        println("Holding Session $it")
        if (it == 2) return@forEach   // 仅从 lambda 返回，继续外层循环
        println("Holding Session $it done!")
    }
    println("done")
}
```

​	调用上面的函数，你就会看到这个结果：

```
Holding Session 1
Holding Session 1 done!
Holding Session 2
Holding Session 3
Holding Session 3 done!
done
```

## 可见性、成员 vs 顶层函数

Kotlin 的函数可以是顶层（在 `.kt` 文件直接声明）或类成员。顶层函数在 JVM 上编译为静态方法（文件类），更贴近函数式/工具方法风格。类成员函数受类的可见性修饰符控制（`public` / `internal` / `protected` / `private`）。默认是 `public`。

**注意**：`internal` 的可见性是“模块级别”，类似 Java 的包私有但语义不同（按模块定义）。在多模块项目中要注意 `internal` 的边界。

# Reference

- Kotlin — Basic syntax（变量、val/var 与示例）。([Kotlin](https://kotlinlang.org/docs/basic-syntax.html?utm_source=chatgpt.com))
- Kotlin — Null safety（可空类型与空安全设计）。([Kotlin](https://kotlinlang.org/docs/null-safety.html?utm_source=chatgpt.com))
- Kotlin — Properties（属性、backing field、lateinit、const 等）。([Kotlin](https://kotlinlang.org/docs/properties.html?utm_source=chatgpt.com))
- Kotlin — Delegated properties（属性委托，`by lazy` 等）。([Kotlin](https://kotlinlang.org/docs/delegated-properties.html?utm_source=chatgpt.com))
- 讨论/Q&A（函数参数只读等语言设计背景）。([Stack Overflow](https://stackoverflow.com/questions/40563406/final-or-val-function-parameter-or-in-kotlin?utm_source=chatgpt.com))
- Kotlin Functions（官方语言文档）— 基本语法、infix、operator、顶层函数等。([Kotlin](https://kotlinlang.org/docs/functions.html?utm_source=chatgpt.com))
- Inline functions（官方）— `inline` / `noinline` / `crossinline` / `reified` 的细节与注意点。([Kotlin](https://kotlinlang.org/docs/inline-functions.html?utm_source=chatgpt.com))
- Higher-order functions & Lambdas（官方）— 函数类型、lambda、非本地返回、函数引用。
- Extensions（官方）— 扩展函数语义。([Kotlin](https://kotlinlang.org/docs/extensions.html?utm_source=chatgpt.com))
- Coroutines overview & Best practices（官方 + Android）— `suspend` 与协程的使用建议。([Kotlin](https://kotlinlang.org/docs/coroutines-overview.html?utm_source=chatgpt.com), [Android Developers](https://developer.android.com/kotlin/coroutines/coroutines-best-practices?utm_source=chatgpt.com))
- `@JvmOverloads` / Java interop（官方 API + Android 指南）— Java 调用 Kotlin 默认参数的处理。([Kotlin](https://kotlinlang.org/api/core/kotlin-stdlib/kotlin.jvm/-jvm-overloads/?utm_source=chatgpt.com), [Android Developers](https://developer.android.com/kotlin/interop?utm_source=chatgpt.com))