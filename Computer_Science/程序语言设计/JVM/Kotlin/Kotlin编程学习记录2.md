# Kotlin编程学习记录2——条件与循环

# 条件语句：`if` 与 `when`

​	Kotlin 的控制流把“表达式优先”作为设计原则——`if`、`when` 不只是控制语句，**都可以作为表达式使用并返回值**，这影响了日常代码风格（更函数式、可组合）。笔者这里影响深刻的是If的可返回表达式性，这个我在GNU C扩展语法中玩过，没想到在Kotlin中是一个非常标准的用法。

## 总体要点（速览）

- `if` 可以用作表达式或语句：表达式时可直接返回值（因此 Kotlin 没有三元运算符）。
- `when` 是比 `switch` 更强大的多分支构造：支持匹配常量、区间、类型检查、任意条件（无 subject 的 `when`），也能作为表达式返回值。`when` 分支不会“穿透”（不需要 `break`）。
- 当 `when` 用于 sealed class（或 sealed interface）时，编译器可以检测是否覆盖所有子类型，从而允许省略 `else`（exhaustive）。

------

## `if`：声明、表达式、注意点

 	Kotlin的If跟大部分编程语言别无二致，我这种C++er看了都觉得回了家一般。

```kotlin
if (condition) {
    // statement block
} else {
    // statement block
}
```

​	但是独特的是，当 `if` 用作**表达式**时，可以把值直接赋给变量或作为函数返回值：

```kotlin
val max = if (a > b) a else b    // 表达式形式
fun maxOf(a: Int, b: Int) = if (a > b) a else b
```

> 说明：Kotlin 因为有 `if` 表达式，所以没有三元运算符 `?:`。

​	这就有点像：

```kotlin
var max = 0
if(a > b){
	max = a
}else{
	max = b
}
```

​	但是你可以看到写法上Kotlin使用If直接返回值的写法显然简单的多。

### 表达式的类型规则

作为表达式时，`if` 的每个分支末尾表达式会被推断为某个类型。整个 `if` 表达式的类型是（各分支类型的）最近公共父类型或由编译器推断的**最小上界**（least upper bound）。如果某分支没有值（如最后是 `Unit`），则表达式类型会相应地调整

```kotlin
val x = if (flag) 1 else 2        // Int
val y = if (flag) "ok" else null  // String?（可空）
```

### 典型用法与陷阱

- **优先用 `if` 表达式代替临时变量**，代码更简洁、函数式风格更明显。
- **不要误把 `if` 写成布尔表达式赋值**：在有分支返回布尔值与其它副作用混合时，容易让类型变成 `Boolean`（见社区讨论“guarding against unintentional return types”）。谨慎检查每个分支返回的值类型。
- `if` 支持嵌套与 block（块）形式，块内最后一行是该分支的结果（用于表达式场景）。

## 练习 1：使用 `if/else` 判断奇偶数

**目标：** 编写一个函数，它接受一个整数，然后返回一个字符串，告诉我们这个数是 "奇数" 还是 "偶数"。

**要求：**

1. 创建一个名为 `checkOddEven` 的函数。
2. 该函数接受一个 `Int` 类型的参数，名为 `number`。
3. 函数应返回一个 `String` 类型的结果。
4. 使用 `if/else` 表达式来判断 `number` 是否能被 2 整除。
5. 如果能，则返回 "偶数"；如果不能，则返回 "奇数"。

**参考代码：**

```kotlin
fun checkOddEven(number: Int): String {
    return if (number % 2 == 0) {
        "偶数"
    } else {
        "奇数"
    }
}

fun main() {
    val num1 = 10
    val num2 = 7
    println("$num1 是 ${checkOddEven(num1)}") // 输出: 10 是 偶数
    println("$num2 是 ${checkOddEven(num2)}") // 输出: 7 是 奇数
}
```

**笔记重点：**

- 在 Kotlin 中，`if/else` 是一个**表达式 (expression)**，不是一个语句 (statement)。这意味着它可以有返回值。
- 因此，我们可以直接使用 `return if (...)` 这样的简洁写法。
- 代码块 `{}` 中最后一行就是该块的返回值。



# `when`：强大且灵活的多分支工具

`when` 在 Kotlin 中是一个“一网打尽”的多用途分支表达式/语句：它既能完成传统 `switch` 的工作，也能做更复杂的匹配（范围、类型、任意条件），还可以作为表达式返回值。

### 基本语法（有 subject 与无 subject 两种形式）

**有 subject 的形式（最常见）**：

```kotlin
when (x) {
    0 -> print("x == 0")
    1, 2 -> print("x == 1 or x == 2")  // 多个值使用逗号分隔
    in 3..5 -> print("x ∈ [3,5]")
    else -> print("x is something else")
}
```

**无 subject 的形式（相当于一连串 `if/else if`）**：

```kotlin
when {
    x.isEmpty() -> println("empty")
    x.length > 5 -> println("long")
    else -> println("other")
}
```

- `when` 分支可以使用逗号把多个匹配值合并到同一个分支。

### `when` 作为表达式

`when` 可以返回值并直接赋给变量或返回：

```kotlin
val result = when (x) {
    1 -> "one"
    2 -> "two"
    else -> "many"
}
```

**注意**：当 `when` 被用作表达式时，编译器要求覆盖所有可能情况或提供 `else`（除非 `when` 是对 sealed class 的完全覆盖情况）。

### 多种匹配条件支持（比 switch 更强）

每个 `when` 分支的条件可以是：

- 常量（`0`, `'a'`, `"s"`）
- 多个常量（逗号分隔）
- 区间或集合成员关系：`in 1..10` / `!in setOf(...)`
- 类型检查：`is String` / `!is Int`（结合智能转换 smart cast）
- 任意表达式（在 **无 subject** 的 `when` 中尤其常见）
- 函数调用的结果（在带 subject 的 `when(x)` 中，分支条件会与 subject 的值做等值比较 —— 例如 `parseInt(s) ->` 表示“当 subject 等于 `parseInt(s)` 时”）。

```kotlin
when (val v: Any = getValue()) {
    is String -> println(v.length) // v 被智能转换为 String
    is Int -> println(v + 1)      // v 是 Int
    else -> println("unknown")
}
```

### sealed classes 与可穷尽的 `when`

当 `when` 的 subject 类型是 **sealed**（或 sealed interface）的一个实例时，编译器能在编译期知道所有可能的子类型，从而检查 `when` 是否穷尽覆盖（exhaustive）。如果穷尽，则无需 `else` 分支；否则编译器会要求 `else`。这使得 `when` 在实现状态机或代数数据类型（ADT）匹配时非常强大。

```kotlin
sealed class Result {
    data class Success(val data: String): Result()
    object Failure: Result()
}

fun handle(r: Result) = when (r) {
    is Result.Success -> println(r.data)
    Result.Failure -> println("failed")
    // 不需要 else（若覆盖了所有子类）
}
```

### 6. 复杂分支与多语句块

每个 `when` 的分支可以是单行表达式，也可以是一个块（`{ ... }`），块的最后一行将作为该分支的返回值（当 `when` 作为表达式使用时）。这允许在分支中执行多步逻辑再返回最终值。([Kotlin](https://kotlinlang.org/docs/control-flow.html?utm_source=chatgpt.com))

```kotlin
val msg = when (cmd) {
    "ok" -> {
        log("ok received")
        "all good"
    }
    else -> "unknown"
}
```

------

## 练习 2：使用 `when` 表达式进行分数评级

**目标：** 编写一个函数，根据输入的分数（整数）给出对应的等级评价（字符串）。

**要求：**

1. 创建一个名为 `getGrade` 的函数。
2. 该函数接受一个 `Int` 类型的参数，名为 `score`。
3. 函数应返回一个 `String` 类型的结果。
4. 使用 `when` 表达式实现以下评级逻辑：
   - `score` 为 100 时，返回 "满分！"
   - `score` 在 90 到 99 之间时，返回 "优秀"
   - `score` 在 75 到 89 之间时，返回 "良好"
   - `score` 在 60 到 74 之间时，返回 "及格"
   - 否则，返回 "不及格"

**参考代码：**

```kotlin
fun getGrade(score: Int): String {
    return when (score) {
        100 -> "满分！"
        in 90..99 -> "优秀"
        in 75..89 -> "良好"
        in 60..74 -> "及格"
        else -> "不及格"
    }
}

fun main() {
    println("95分评价: ${getGrade(95)}")   // 输出: 95分评价: 优秀
    println("82分评价: ${getGrade(82)}")   // 输出: 82分评价: 良好
    println("60分评价: ${getGrade(60)}")   // 输出: 60分评价: 及格
    println("45分评价: ${getGrade(45)}")   // 输出: 45分评价: 不及格
    println("100分评价: ${getGrade(100)}") // 输出: 100分评价: 满分！
}
```

**笔记重点：**

- `when` 是 Kotlin 中用于替代传统 `switch` 语句的更强大、更灵活的表达式。
- 它可以匹配**具体的值**（如 `100`）。
- 它可以用来检查值是否在**一个区间**内（如 `in 90..99`）。
- `else` 分支用于处理所有其他未匹配的情况，类似于 `switch` 中的 `default`。
- 和 `if` 一样，`when` 也是一个表达式，可以直接将其结果返回或赋值给变量。

# Kotlin的循环语法

## `for` 循环：更贴近 “foreach” 而非传统的 C/Java 风格

- Kotlin 没有经典的三段式 `for` 遍历语法，而是更倾向函数式、可迭代结构：

  ```kotlin
  for (item in collection) { ... }
  ```

  适用于数组、集合、字符串、范围（只要实现了 `Iterable`）

- 常见用法：

  ```kotlin
  // Ranges
  for (i in 1..5) println(i)               // 1,2,3,4,5
  for (i in 5 downTo 1) println(i)         // 5,4,3,2,1
  for (i in 1..10 step 2) println(i)       // 1,3,5,7,9 :contentReference[oaicite:1]{index=1}
  
  // 数组、集合、字符串
  for (ch in "Kotlin") println(ch)
  for (elem in listOf(1,2,3)) println(elem) :contentReference[oaicite:2]{index=2}
  
  // 带索引迭代
  for (i in arr.indices) println("index $i = ${arr[i]}")
  for ((i, v) in arr.withIndex()) println("$i -> $v") :contentReference[oaicite:3]{index=3}
  ```

  

  ## `while` 与 `do-while`：标准条件循环

### `while`

- 初次检查条件，若为 `true` 执行循环体。若初始条件为 `false`，则一次都不执行：

  ```kotlin
  while (condition) {
    // body
  }
  ```

  ```kotlin
  var i = 1
  while (i <= 5) {
    println(i)
    i++
  }
  ```

### `do-while`

- 循环体至少执行一次，之后再判断条件决定是否继续：

  ```kotlin
  do {
    // body
  } while (condition)
  ```

  常用场景：输入验证 / 重试逻辑等！

------

## 控制循环：`break`、`continue`

- **`break`**：直接退出整个循环。
- **`continue`**：跳过当前迭代，继续下一次。

```kotlin
for (i in 1..10) {
  if (i == 5) break       // 遇到 5 时退出循环
  if (i % 2 == 0) continue // 偶数跳过
  println(i)
}
```

------

## 防止无限循环的技巧与注意

- `while (true)` 可用于无限循环，通常配合 `break` 结束：

  ```kotlin
  while (true) {
    // ...
    if (someCondition) break
  }
  ```

  这种写法虽常见，但要小心，确保终止条件有效

- `for` 循环没有原生的无限循环形式，这也是 Kotlin 设计上摒弃经典 C/Java 风格循环的体现

## 快速对照总结

| 场景                     | 推荐用法                   | 说明                             |
| ------------------------ | -------------------------- | -------------------------------- |
| 遍历集合、字符串、范围等 | `for (x in ...)`           | 简洁、安全、函数式风格           |
| 条件循环                 | `while`, `do-while`        | 根据是否至少执行一次决定使用哪种 |
| 带索引遍历               | `withIndex()` 或 `indices` | 获取下标或值更方便               |
| 跳出/跳过循环            | `break`, `continue`        | 灵活控制循环流程                 |
| 避免无限循环             | 小心 `while(true)` 使用    | 必须确保有跳出条件               |

## 练习 3：使用 `for` 循环打印九九乘法表

**目标：** 在控制台打印出一个经典、格式整齐的九九乘法表。

**要求：**

1. 使用**嵌套的 `for` 循环**来完成。
2. 外层循环控制乘法表的行（从 1 到 9）。
3. 内层循环控制乘法表的列。**关键点：** 内层循环的次数应该依赖于外层循环当前的行数（例如，第 5 行只打印到 `5 * 5`）。
4. 输出格式应为 `“{乘数1} * {乘数2} = {结果}”`，并且为了美观，每个算式之间用制表符 `\t` 分隔。
5. 每打印完一行后，需要换行。

**预期的输出效果：**

```
1 * 1 = 1   
2 * 1 = 2   2 * 2 = 4   
3 * 1 = 3   3 * 2 = 6   3 * 3 = 9   
4 * 1 = 4   4 * 2 = 8   4 * 3 = 12  4 * 4 = 16  
... (以此类推，直到第9行)
9 * 1 = 9   9 * 2 = 18  ...          9 * 9 = 81  
```

**提示：**

- 你可以使用 `1..9` 来创建一个从 1 到 9 的整数区间 (range)。
- `print()` 函数用于在同一行打印，而 `println()` 函数会在打印后换行。

```Kotlin
fun printMultiplicationTable() {
    // 外层循环控制行，从1到9
    for (row in 1..9) {
        // 内层循环控制列，从1到当前行数
        for (col in 1..row) {
            // 打印乘法表达式，并用 \t 补齐，使其对齐
            print("$col * $row = ${col * row}\t")
        }
        // 每行结束后，换行
        println()
    }
}

fun main() {
    printMultiplicationTable()
}
```

**笔记重点：**

- `for (variable in range)` 是 Kotlin 中最常见的循环形式。
- `1..9` 创建了一个闭区间，包含 1 和 9。
- 嵌套循环是处理二维结构（如表格、矩阵）的常用方法。
- `print()` 和 `println()` 的区别使用是格式化输出的关键。

------



## 练习 4：使用 `while` 循环实现猜数字游戏

**目标：** 编写一个简单的猜数字游戏。程序会随机生成一个 1 到 100 之间的整数，然后让用户反复猜测，直到猜对为止。

**要求：**

1. 在程序开始时，生成一个 1 到 100 之间的随机整数作为“谜底”。
2. 使用 `while` 循环或 `do-while` 循环来不断获取用户的输入。
3. 每次用户输入后，程序需要判断：
   - 如果用户猜的数字比谜底**大**，则提示 "太大了，再猜！"。
   - 如果用户猜的数字比谜底**小**，则提示 "太小了，再猜！"。
   - 如果用户猜对了，则提示 "恭喜你，猜对了！"，然后**结束循环**。
4. 记录用户总共猜了多少次，并在猜对后一并输出。

**提示：**

- 生成随机数：可以使用 `(1..100).random()`。
- 读取用户输入：可以使用 `readln()` 或 `readLine()`。注意它返回的是 `String?`，你可能需要用 `toIntOrNull()` 转换成整数并处理无效输入。

```kotlin
fun guessTheNumber() {
    // 1. 生成1到100的随机数作为谜底
    val secret = (1..100).random()
    var guessCount = 0
    var userGuess: Int? = null

    println("我已经想好了一个 1 到 100 之间的数字，你来猜猜看！")

    // 2. 使用 while 循环，只要没猜对就一直继续
    while (userGuess != secret) {
        print("请输入你猜的数字: ")
        
        // 读取用户输入并转换为整数
        userGuess = readln().toIntOrNull()
        
        // 增加猜测次数
        guessCount++

        // 检查用户输入是否有效
        if (userGuess == null) {
            println("无效的输入，请输入一个数字！")
            continue // 跳过本次循环的剩余部分，直接开始下一次循环
        }

        // 3. 判断大小并给出提示
        if (userGuess > secret) {
            println("太大了，再猜！")
        } else if (userGuess < secret) {
            println("太小了，再猜！")
        }
    }

    // 4. 猜对后，循环结束，打印祝贺信息
    println("恭喜你，猜对了！谜底就是 $secret。")
    println("你总共猜了 $guessCount 次。")
}

fun main() {
    guessTheNumber()
}
```

**笔记重点：**

- `while (condition)` 循环会在条件为 `true` 时持续执行。它适用于循环次数不确定的场景。
- `do-while` 循环（未在此示例中使用）与 `while` 类似，但它保证循环体**至少执行一次**。
- 从控制台读取用户输入是与用户交互的基础。
- `toIntOrNull()` 是一个安全的字符串转整数方法，当转换失败时会返回 `null`，避免程序崩溃。
- `continue` 关键字可以用来跳过当前循环的剩余代码，直接进入下一次迭代。





# Reference

- Kotlin 官方 — Control flow（`if` / `when` 等）。([Kotlin](https://kotlinlang.org/docs/control-flow.html?utm_source=chatgpt.com))
- Kotlin 官方 — Basic syntax（说明 `if` 为表达式示例）。([Kotlin](https://kotlinlang.org/docs/basic-syntax.html?utm_source=chatgpt.com))
- Kotlin 官方 — Sealed classes（`when` 与 sealed 的 exhaustiveness）。([Kotlin](https://kotlinlang.org/docs/sealed-classes.html?utm_source=chatgpt.com))
- Baeldung — Guide to `when`（讲解 `when` 的常见变体与比较 `switch`）。([Baeldung on Kotlin](https://www.baeldung.com/kotlin/when?utm_source=chatgpt.com))
- GeeksforGeeks — Kotlin `when` expression 教程（多值、区间示例）。([GeeksforGeeks](https://www.geeksforgeeks.org/kotlin/kotlin-when-expression/?utm_source=chatgpt.com))
- Kotlin 官方文档，比如控制流章节解读 `while`、`do-while`([Kotlin](https://kotlinlang.org/docs/control-flow.html?utm_source=chatgpt.com))，以及 `for` 循环和 ranges 介绍([programiz.com](https://www.programiz.com/kotlin-programming/for-loop?utm_source=chatgpt.com), [Kotlin](https://kotlinlang.org/docs/ranges.html?utm_source=chatgpt.com), [GeeksforGeeks](https://www.geeksforgeeks.org/kotlin/kotlin-for-loop/?utm_source=chatgpt.com))。
- 权威教程如 Baeldung、Programiz 的实战示例([Baeldung on Kotlin](https://www.baeldung.com/kotlin/loops?utm_source=chatgpt.com), [programiz.com](https://www.programiz.com/kotlin-programming/while-loop?utm_source=chatgpt.com))。
- 社区讨论强调设计理念与常见路径([Kotlin Discussions](https://discuss.kotlinlang.org/t/any-reason-to-not-keep-the-good-old-for-loop-format/25287?utm_source=chatgpt.com), [Reddit](https://www.reddit.com/r/Kotlin/comments/1aljxw4/whats_the_purpose_of_dowhile_loop_cant_the_same/?utm_source=chatgpt.com))。



