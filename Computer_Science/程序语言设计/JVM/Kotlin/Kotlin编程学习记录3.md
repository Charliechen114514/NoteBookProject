# Kotlin编程学习记录：Kotlin OOP

​	Kotlin的OOP大幅度化简了上个世纪出生的OOP编程语言语法，我们可以看看Kotlin是如何设计编程语言的。

------

## OOP的基石：类与对象

Kotlin 使用 `class` 声明类，并可在主构造函数中直接定义属性：

```kotlin
class Person(val name: String, var age: Int) {
    fun greet() = println("Hi, I'm $name, $age years old.")
}
```

对比 Java，Kotlin 将属性与构造整合，简化了冗长的 getter/setter 生成。Kotlin创建我们制定好的类后，可以跟正常的OOP语言一样得到：

```kotlin
val alice = Person("Alice", 30)
alice.greet() // 输出：Hi, I'm Alice, 30 years old.
```

------

## 封装与可见性控制

Kotlin 鼓励使用封装：通过访问修饰符控制类成员的可见性（默认 `public`）。

- **`private`**：仅类内部可见
- **`protected`**：类内部及子类可见
- **`internal`**：模块内可见
- **`public`**（默认）：全局可见

一个例子

```kotlin
open class BankAccount {
    private var balance: Double = 0.0	// 私有成员
    protected fun deposit(amount: Double) { balance += amount } // 子类和自己可以访问
    internal fun showBalance() = balance	// 模块内可访问
}
```

------

## 继承（Inheritance）与抽象类

Kotlin 中默认类是 `final`（不可继承），必须加 `open` 才能被继承；方法同理。

```kotlin
open class Animal {
    open fun makeSound() = println("Some sound")
}
class Dog : Animal() {
    override fun makeSound() = println("Woof!")
}
```

抽象类用 `abstract` 修饰，可包含抽象方法和已实现方法；子类必须实现所有抽象成员。

------

## 4. 接口（Interface）与多态（Polymorphism）

Kotlin 的接口可以包含行为实现，不仅是方法声明。类通过 `:` 实现接口：

```kotlin
interface Drivable {
    fun drive()
    fun stop() { println("Stopping") }
}
class Car : Drivable {
    override fun drive() = println("Car is driving")
}
```

类型一致接口可用于多态调用，统一处理不同类型实例。

------

## `data class`：专为数据设计

`data class` 用来简化数据持有类，自动生成 `equals()`、`hashCode()`、`toString()` 与 `copy()` 等方法：

```kotlin
data class User(val name: String, val email: String)
val u = User("Bob", "bob@example.com")
println(u) // 输出: User(name=Bob, email=bob@example.com)
val u2 = u.copy(email = "bob2@example.com")
```

这种结构在 DTO 或值对象非常有用。

------

## 单例与 Companion Object（对象相关）

### 单例（Singleton）

使用 `object` 关键字轻松声明全局单例：

```kotlin
object Logger {
    fun log(msg: String) = println("LOG: $msg")
}
Logger.log("Started") // 调用方式简单
```

### companion object

提供类似 Java `static` 成员的功能：

```kotlin
class Util {
    companion object {
        const val VERSION = "1.0"
        fun info() = println("Util v$VERSION")
    }
}
Util.info()  // 利用类名直接调用
```

适合构建工厂函数或静态工具方法。

------

## 密封类（Sealed Class）与受控继承

Sealed 类允许定义有限的子类范围，对创建可穷尽类型很有用，常配合 `when` 使用以获得编译时检查。示例：UI 状态：

```kotlin
sealed class UiState {
    object Loading : UiState()
    data class Success(val data: String) : UiState()
    data class Error(val error: Throwable) : UiState()
}

fun render(state: UiState) = when(state) {
    UiState.Loading -> showLoading()
    is UiState.Success -> showData(state.data)
    is UiState.Error -> showError(state.error)
}
```

如果覆盖不完整，编译器会警告提醒。

------

## 四大 OOP 原则在 Kotlin 的体现

| OOP 概念              | Kotlin 实现方式                           |
| --------------------- | ----------------------------------------- |
| 封装（Encapsulation） | 控制可见性、`private`/`internal` 等修饰符 |
| 抽象（Abstraction）   | 抽象类与接口 Hide implementation          |
| 继承（Inheritance）   | `open` 类、`override` 方法                |
| 多态（Polymorphism）  | 接口 / 抽象类型 可统一处理具体类型实例    |

Kotlin 用简洁语法和现代功能（如 sealed class）强力支撑 OOP 设计。Kotlin 类的构造、初始化与方法详解

Kotlin 在类的构造与初始化方面提供了简洁而灵活的机制：你会接触到 **主构造器（primary constructor）**、**初始化代码块（`init`）**、**次级构造器（secondary constructor）**，以及在类中定义方法的标准方式。理解这些内容，对设计类结构、增强代码可读性与鲁棒性至关重要。

## 细节部分：构造函数

### 主构造函数（Primary Constructor）与简化语法

- **定义位置**：主构造函数直接在类头声明，紧跟在类名之后。

  ```kotlin
  class Person(val name: String, var age: Int)
  ```

  此语法不仅定义了构造函数，还自动声明并初始化了对应的属性。

- **语法优化**：如果没有注解或可见性修饰，可省略 `constructor` 关键字。

- **默认参数**：主构造器可以为参数提供默认值，简化重载需求

  ```kotlin
  class Person(val name: String = "Unknown", var age: Int = 0)
  ```

------

## 2. 初始化块（`init`）

- **用途**：主构造函数不能包含执行逻辑，此时用 `init` 初始化块来执行代码（如校验、设置额外属性等）。
- **执行顺序**：对象实例化时，先初始化从主构造器带来的属性，然后依次执行 `init` 块，再执行次构造器体（如有）。
- **多个 `init` 块**：若定义多个，依次按书写顺序执行。

**示例：**

```kotlin
class Example(val name: String) {
    init { println("Init block 1: name is $name") }
    val length = name.length.also { println("Property initializer: length = $it") }
    init { println("Init block 2: second stage") }
}
```

------

## 次级构造函数（Secondary Constructor）

- **定义形式**：使用 `constructor` 关键字在类体内声明，用于提供额外的构造路径（如不同参数组合）。

  ```kotlin
  class Person(val name: String) {
      var age: Int = 0
      constructor(name: String, age: Int) : this(name) {
          this.age = age
      }
  }
  ```

- **必须委托**：若类声明了主构造器，次级构造器必须直接或间接调用主构造器（使用 `this(...)`）。

- **执行顺序**：次级构造器体执行在 `init` 块之后。

**示例：**

```kotlin
class User(val name: String, var age: Int = 0) {
    init { check(age >= 0) { "Age must be non-negative" } }
    constructor(name: String, age: Int, email: String) : this(name, age) {
        println("Secondary constructor: $name, $age, $email")
    }
}
```

------

## 执行顺序总结

构建流程如下：

1. 主构造器参数赋值与属性初始化；
2. `init` 块依次执行；
3. 次级构造器（如有）执行其方法体。

例如，使用以下类：

```kotlin
class Example(val msg: String) {
    init { println("Init: $msg") }
    constructor(msg: String, flag: Boolean) : this(msg) {
        println("Secondary constructor: flag = $flag")
    }
}
```

执行 `Example("Hello", true)` 会输出：

```
Init: Hello
Secondary constructor: flag = true
```

这在多个权威资源中有类似描述

------

## 类中方法的定义方式

- **普通方法**：与 Java 类似，定义在类体中：

  ```kotlin
  class Person(val name: String) {
      fun greet() = println("Hello, I'm $name")
  }
  ```

- **方法继承与覆盖**：

  - Kotlin 类和成员默认是 `final`，需使用 `open` 才能被继承/重写。
  - 使用 `override` 标记重写方法。

  ```kotlin
  open class Animal {
      open fun makeSound() = println("Some sound")
  }
  class Dog : Animal() {
      override fun makeSound() = println("Woof!")
  }
  ```

