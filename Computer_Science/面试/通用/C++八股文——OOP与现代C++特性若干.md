# OOP

## 2.2.1 继承和虚继承

### 继承 (Inheritance)

**继承**是面向对象编程（OOP）的三大基本特性之一（另外两个是封装和多态）。它允许一个类（**派生类 / 子类**）从另一个类（**基类 / 父类**）获取（继承）其成员变量和成员函数。通过继承，可以实现代码的重用和扩展，建立类之间的**“is-a” (是某种)** 关系。

**普通继承的特点：**

- **代码复用：** 子类可以重用父类的代码，避免重复编写。
- **层次结构：** 建立类之间的等级体系，从一般到特殊。
- **访问权限：**
  - `public` 继承：基类的 `public` 成员在派生类中仍是 `public`；`protected` 成员在派生类中仍是 `protected`；`private` 成员不可访问。
  - `protected` 继承：基类的 `public` 和 `protected` 成员在派生类中都变为 `protected`；`private` 成员不可访问。
  - `private` 继承：基类的 `public` 和 `protected` 成员在派生类中都变为 `private`；`private` 成员不可访问。
- **构造与析构：**
  - 子类构造时，首先调用基类的构造函数，然后调用子类自己的构造函数。
  - 子类析构时，首先调用子类自己的析构函数，然后调用基类的析构函数。
- **内存布局：** 派生类对象会包含基类子对象的所有成员。

**示例：**

```
class Animal { // 基类
public:
    void eat() { /* ... */ }
    void sleep() { /* ... */ }
};

class Dog : public Animal { // 派生类，public 继承 Animal
public:
    void bark() { /* ... */ }
};
```

这里的 `Dog` 是 `Animal` 的一种，它继承了 `Animal` 的 `eat()` 和 `sleep()` 方法，并有自己特有的 `bark()` 方法。



### 虚继承 (Virtual Inheritance)



**虚继承**是 C++ 中一种特殊的继承方式，主要用于解决**多重继承中出现的菱形继承 (Diamond Problem)** 问题。当一个类通过多条路径（即通过两个或更多中间基类）间接继承自同一个基类时，如果没有虚继承，会导致这个公共基类的子对象在派生类中存在多份副本，造成数据冗余和二义性。

**菱形继承的例子：**

```
      GrandParent
        /    \
       /      \
    Parent1  Parent2
       \      /
        \    /
       Child
```

在这个例子中，`Child` 类同时继承 `Parent1` 和 `Parent2`，而 `Parent1` 和 `Parent2` 又都继承 `GrandParent`。如果没有虚继承，`Child` 对象中会包含两份 `GrandParent` 的子对象，一份来自 `Parent1`，一份来自 `Parent2`。

**虚继承的特点：**

- **解决菱形继承问题：** 通过在**派生类继承基类时使用 `virtual` 关键字**，可以确保公共的虚基类在最终的派生类中**只存在一个共享的子对象实例**。

- **语法：** 在继承时使用 `virtual` 关键字。

  ```
  class GrandParent {
  public:
      int gp_data;
  };
  
  class Parent1 : virtual public GrandParent { // 虚继承 GrandParent
  public:
      int p1_data;
  };
  
  class Parent2 : virtual public GrandParent { // 虚继承 GrandParent
  public:
      int p2_data;
  };
  
  class Child : public Parent1, public Parent2 { // 多重继承
  public:
      int c_data;
  };
  ```

  在上述代码中，`Child` 对象将只包含一个 `GrandParent` 子对象。

- **内存布局：** 虚继承会引入额外的开销，通常是通过**虚基类指针 (virtual base pointer, VBPtr)** 或**虚基类表 (virtual base table, VBT)** 来实现。这些指针/表用于在运行时确定虚基类子对象在内存中的实际偏移量。这使得内存布局更加复杂，通常会增加对象大小和访问虚基类成员的开销。

- **构造函数调用：**

  - 虚基类的构造函数只会被最底层的派生类（即最终的派生类，如 `Child`）直接调用一次。
  - 中间派生类（如 `Parent1`, `Parent2`）不再负责构造虚基类。

**虚继承与普通继承的区别：**

| 特性             | 普通继承                      | 虚继承                                |
| ---------------- | ----------------------------- | ------------------------------------- |
| **目的**         | 代码复用，建立 "is-a" 关系    | 解决多重继承中的菱形继承问题          |
| **公共基类实例** | 可能存在多份副本 (菱形继承时) | 只有一份共享副本 (解决菱形继承问题)   |
| **语法**         | `class Derived : public Base` | `class Derived : virtual public Base` |
| **内存布局**     | 相对简单，直接包含基类子对象  | 复杂，通常引入虚基类指针/表，增加开销 |
| **构造函数**     | 按继承链顺序依次调用基类构造  | 虚基类由最终派生类直接构造一次        |

**总结：**

- **继承**是 C++ 面向对象的基本机制，用于代码复用和构建类层次。
- **虚继承**是继承的一种特殊形式，专门为了解决多重继承中由于公共基类导致的数据冗余和二义性问题，通过共享基类子对象实现。它引入了额外的复杂性和开销，应在确实需要时使用。

------



## 多态的类，内存布局是怎么样的

**多态 (Polymorphism)** 在 C++ 中主要通过**虚函数 (Virtual Functions)** 和**虚函数表 (Virtual Table, vtable)** 来实现。当一个类中包含虚函数时，它就成为一个多态的类。

### 多态类的内存布局

当一个类中存在至少一个虚函数时（无论是自身定义的，还是从基类继承的虚函数），编译器会为这个类生成一些额外的结构来支持多态性：

1. **虚函数表指针 (Virtual Table Pointer, vptr)：**
   - **位置：** 每个**多态类对象**的内存布局中，都会在**最前端**（通常是对象内存的起始位置，但具体位置依赖于编译器和继承方式）添加一个隐藏的指针，称为 `vptr`。
   - **作用：** `vptr` 指向该类对应的**虚函数表 (vtable)**。
   - **数量：** 每个多态类对象只有一个 `vptr`（在单继承情况下）。在多重继承和虚继承的复杂情况下，一个对象可能拥有多个 `vptr`。
   - **赋值：** `vptr` 的值在对象构造时由编译器设置，指向该对象实际类型的 `vtable`。
2. **虚函数表 (Virtual Table, vtable)：**
   - **位置：** `vtable` 是一个**静态**的数据结构，通常存储在程序的**只读数据段 (.rodata)** 中。每个**类**只有一份 `vtable`，而不是每个对象一份。
   - **内容：** `vtable` 实际上是一个函数指针数组。这个数组的每个条目都指向该类中声明的**虚函数**的实际实现地址。
     - 如果派生类重写了基类的虚函数，那么 `vtable` 中对应的条目会指向派生类中的实现。
     - 如果派生类没有重写虚函数，则该条目会指向基类中的实现。
   - **作用：** 在运行时，通过 `vptr` 找到正确的 `vtable`，然后通过 `vtable` 中的函数指针找到并调用正确的虚函数实现，从而实现动态绑定。
3. **成员变量：**
   - 对象的内存中会包含其自身非静态成员变量，以及其所有基类的非静态成员变量。

**简单单继承多态类的内存布局示例：**

假设有如下类结构：

```
class Base {
public:
    int b_data;
    virtual void func1() { /* ... */ }
    virtual void func2() { /* ... */ }
};

class Derived : public Base {
public:
    int d_data;
    void func1() override { /* ... */ } // 重写 func1
    virtual void func3() { /* ... */ }  // Derived 新增虚函数
};
```

**`Base` 对象的内存布局：**

```
+------------------+  <-- `Base` 对象起始地址
| vptr             |  <-- 指向 Base 类的 vtable
+------------------+
| b_data           |
+------------------+
```

**`Base` 类的 `vtable` (静态，存储在 `.rodata` 段)：**

```
+------------------+
| &Base::func1     |
+------------------+
| &Base::func2     |
+------------------+
```

**`Derived` 对象的内存布局：**

```
+------------------+  <-- `Derived` 对象起始地址
| vptr             |  <-- 指向 Derived 类的 vtable
+------------------+
| b_data           |  <-- 继承自 Base
+------------------+
| d_data           |
+------------------+
```

**`Derived` 类的 `vtable` (静态，存储在 `.rodata` 段)：**

```
+------------------+
| &Derived::func1  |  <-- 重写了 func1
+------------------+
| &Base::func2     |  <-- 未重写，指向 Base 的 func2
+------------------+
| &Derived::func3  |  <-- Derived 新增的虚函数
+------------------+
```



### 多重继承下的内存布局



在多重继承中，如果一个类继承了多个包含虚函数的基类，其内存布局会变得更复杂。一个派生类对象可能包含**多个 `vptr`**，每个 `vptr` 对应一个基类子对象的 `vtable`。

**示例：**

```
class Base1 {
public:
    int data1;
    virtual void f1() {}
};

class Base2 {
public:
    int data2;
    virtual void f2() {}
};

class Derived : public Base1, public Base2 {
public:
    int data_derived;
    void f1() override {}
    void f2() override {}
};
```

**`Derived` 对象的内存布局（示意，具体取决于编译器）：**

```
+------------------+  <-- `Derived` 对象起始地址
| vptr_Base1       |  <-- 指向 Base1 相关的 vtable
+------------------+
| data1            |
+------------------+
| vptr_Base2       |  <-- 指向 Base2 相关的 vtable
+------------------+
| data2            |
+------------------+
| data_derived     |
+------------------+
```

每个 `vptr` 会指向对应的 `vtable`，这些 `vtable` 中包含了该基类接口的所有虚函数地址（包括派生类重写后的地址）。



### 虚继承下的内存布局



虚继承为了解决菱形继承问题，会将虚基类子对象放在一个特殊的位置，通常是通过**虚基类指针 (vptr_base)** 或 **虚基类表 (vbtable)** 来实现。这样，无论从哪条路径继承，最终派生类都只有一个虚基类子对象。这进一步增加了内存布局的复杂性。

**总结：** 多态类的内存布局主要通过在对象中嵌入**虚函数表指针 (`vptr`)**，并让其指向类对应的**虚函数表 (`vtable`)** 来实现。`vtable` 存储了虚函数的实际地址，从而在运行时能够根据对象的实际类型调用正确的函数。这种机制是 C++ 实现运行时多态的核心。

## 被隐藏的基类函数如何调用或者子类调用父类的同名函数和父类成员变量



在 C++ 中，当派生类中定义了与基类同名的成员函数或成员变量时，默认情况下，派生类中的同名成员会**隐藏 (hide)** 基类的同名成员。这意味着通过派生类对象直接访问该成员时，会优先访问派生类中的版本。



### 如何调用被隐藏的基类函数



要调用被隐藏的基类同名函数，需要使用**作用域解析运算符 `::`** 来明确指定要访问的基类版本。

```
#include <iostream>

class Base {
public:
    void func() {
        std::cout << "Base::func()" << std::endl;
    }
    void func(int i) { // 重载函数
        std::cout << "Base::func(int): " << i << std::endl;
    }
};

class Derived : public Base {
public:
    void func() { // 隐藏了 Base 的 func() 和 func(int)
        std::cout << "Derived::func()" << std::endl;
    }
    void myDerivedMethod() {
        // 1. 通过作用域解析运算符直接调用基类的同名函数
        Base::func();        // 调用 Base::func()
        Base::func(10);      // 调用 Base::func(int)

        // 2. 如果不指定作用域，将调用派生类的同名函数
        func();              // 调用 Derived::func()
    }
};

int main() {
    Derived d;
    d.func();            // 调用 Derived::func()

    // 无法直接通过 d.func(10) 调用 Base::func(int)，因为已被隐藏
    // d.func(10);        // 编译错误：'func' does not take 1 argument

    d.myDerivedMethod(); // 通过派生类方法调用基类被隐藏的函数

    // 也可以通过基类指针/引用来调用基类的函数，从而实现多态（如果函数是虚函数）
    Base* b_ptr = &d;
    b_ptr->func();       // 如果 func 是虚函数，这里会调用 Derived::func()
                         // 如果 func 不是虚函数，这里会调用 Base::func() (静态绑定)
    b_ptr->func(20);     // 调用 Base::func(int) (静态绑定)

    return 0;
}
```

**关键点：**

- 当派生类和基类有**同名函数**时，派生类的函数会**隐藏**基类的所有同名版本（包括重载版本），即使它们的参数列表不同。
- 要访问被隐藏的基类函数，必须使用 `BaseClass::functionName()` 的形式。



## 多态实现的三个条件、实现的原理

### 多态的三个必要条件

多态 (Polymorphism) 是 C++ 面向对象编程的核心特性之一，它允许你使用一个基类指针或引用来操作不同派生类的对象，并调用其适当的方法。要实现运行时多态，必须满足以下三个条件：

1. **必须有继承关系：**

   - 多态的基础是类之间的继承层次结构。必须有一个基类 (Base Class) 和至少一个派生类 (Derived Class)，并且派生类以 **`public` 方式继承**基类。
   - 例如：`class Derived : public Base { ... };`

2. **必须有虚函数：**

   - 基类中必须声明至少一个 **虚函数 (`virtual` function)**。虚函数是实现动态绑定的关键。

   - 派生类可以选择性地**重写 (override)** 基类的虚函数。重写时，函数签名（名称、参数列表）和返回类型必须与基类虚函数一致（C++11 引入 `override` 关键字来明确表示重写）。

   - 例如：

     ```
     class Base {
     public:
         virtual void show() { /* ... */ } // 虚函数
     };
     class Derived : public Base {
     public:
         void show() override { /* ... */ } // 重写虚函数
     };
     ```

3. **通过基类指针或引用调用虚函数：**

   - **必须使用基类的指针或基类的引用**来指向或引用派生类对象。

   - 通过这个基类指针或引用调用**虚函数**时，才能实现运行时多态。如果调用的是非虚函数，将发生静态绑定，总是调用基类的版本。

   - 例如：

     ```
     Base* ptr = new Derived(); // 基类指针指向派生类对象
     ptr->show();               // 通过基类指针调用虚函数，实现多态
     
     Base& ref = derived_obj;   // 基类引用引用派生类对象
     ref.show();                // 通过基类引用调用虚函数，实现多态
     ```

这三个条件缺一不可。如果没有继承，就没有父子关系；没有虚函数，编译器就不知道需要动态绑定；没有基类指针/引用，就无法体现“用统一接口操作不同实现”的多态性。



### 多态实现的原理 (动态绑定 / 运行时绑定)



多态在 C++ 中主要通过**虚函数表 (Virtual Table, vtable)** 和**虚函数表指针 (Virtual Table Pointer, vptr)** 来实现，这种机制被称为**动态绑定 (Dynamic Binding)** 或**运行时绑定 (Runtime Binding)**。

1. **虚函数表 (vtable)：**
   - 当一个类中包含虚函数时，编译器会为这个类生成一个**虚函数表 (vtable)**。
   - `vtable` 是一个**静态的、只读的函数指针数组**，它存储了该类中所有虚函数的实际地址。
   - 每个类只有一个 `vtable`，它在程序编译时就已经确定并存储在程序的只读数据段中。
   - 如果派生类重写了基类的虚函数，那么派生类的 `vtable` 中对应位置的函数指针会指向派生类自己的实现。如果派生类没有重写，则指向基类的实现。
2. **虚函数表指针 (vptr)：**
   - 每个**多态类对象**（即包含虚函数的类的对象）都会在其实例的内存布局中，通常在**对象内存的最前端**，添加一个隐藏的指针，这个指针就是 **`vptr`**。
   - `vptr` 的作用是**指向该对象所属类的 `vtable`**。
   - 当对象被构造时，`vptr` 会被正确初始化，使其指向该对象**实际类型**的 `vtable`。
3. **动态绑定过程：**
   - 当通过基类指针（`Base* ptr`）或基类引用（`Base& ref`）调用一个虚函数时：
     1. 编译器会知道这是一个虚函数调用。
     2. 它不会在编译时确定具体调用哪个函数（静态绑定），而是会在**运行时**执行以下步骤：
     3. 通过基类指针/引用访问其所指向/引用的**对象的 `vptr`**。
     4. 通过 `vptr` 找到该对象**实际类型对应的 `vtable`**。
     5. 在 `vtable` 中，找到对应虚函数（根据虚函数在 `vtable` 中的固定偏移量）的**函数指针**。
     6. 调用该函数指针所指向的**实际函数实现**。

**示意图：**

```
     对象A (Derived Type) 的内存
   +--------------------+
   | vptr --------------|------->  Derived 类的 vtable
   +--------------------+          +---------------------+
   | 成员变量 (Base)    |          | &Derived::virtualFunc1 |
   +--------------------+          +---------------------+
   | 成员变量 (Derived) |          | &Base::virtualFunc2    |
   +--------------------+          +---------------------+

       Base* ptr = &对象A;
       ptr->virtualFunc1();  // 运行时：
                             // 1. 通过 ptr 找到对象A
                             // 2. 找到对象A的 vptr
                             // 3. 通过 vptr 找到 Derived 类的 vtable
                             // 4. 在 vtable 中找到 virtualFunc1 的地址
                             // 5. 调用 Derived::virtualFunc1()
```

这种机制使得尽管 `ptr` 是一个 `Base*` 类型，但它能根据其指向的实际对象类型（`Derived`）来调用 `Derived` 版本的虚函数，从而实现了“一个接口，多种形态”的多态性。

## 对拷贝构造函数 深浅拷贝 的理解 拷贝构造函数作用及用途？什么时候需要自定义拷贝构造函数？

### 拷贝构造函数 (Copy Constructor)



- **定义：** 拷贝构造函数是一种特殊的构造函数，它接受一个**同类类型的常量引用**作为参数。它的作用是用一个已存在的对象来初始化（构造）一个新对象。
- **语法：** `ClassName(const ClassName& other);`
- **作用：** 用于在以下三种情况下**初始化**一个新对象：
  1. 当用一个对象去初始化另一个同类型对象时：`ClassName obj2 = obj1;` 或 `ClassName obj2(obj1);`
  2. 当对象作为函数参数进行**值传递**时：`void func(ClassName obj) { ... }`
  3. 当函数返回一个对象时（某些编译器优化可能会避免调用）。

### 深拷贝 (Deep Copy) 与 浅拷贝 (Shallow Copy)



理解拷贝构造函数的核心在于区分深拷贝和浅拷贝。



#### 浅拷贝 (Shallow Copy)

- **定义：** 浅拷贝是**默认的拷贝行为**（当没有自定义拷贝构造函数时，编译器会提供一个默认的）。它只对成员变量进行**按位复制 (bitwise copy)**。这意味着如果类中包含指针或动态分配的资源，那么新对象中的指针会和原对象中的指针**指向同一块内存地址**。

- **问题：**

  - **重复释放：** 当原对象和新对象都被销毁时，它们会尝试释放同一块动态内存，导致**二次释放 (double free)** 错误，引发程序崩溃。
  - **数据污染：** 任何一个对象通过指针修改了共享的内存内容，都会影响到另一个对象。

- **示例 (默认拷贝构造函数实现浅拷贝)：**

  ```
  class MyClass {
  public:
      int* data;
      MyClass(int val) {
          data = new int(val);
          std::cout << "Constructor: " << *data << std::endl;
      }
      ~MyClass() {
          if (data) {
              delete data;
              data = nullptr;
              std::cout << "Destructor" << std::endl;
          }
      }
  };
  
  // main 函数中
  // MyClass obj1(10);
  // MyClass obj2 = obj1; // 默认拷贝构造函数进行浅拷贝
  // obj2.data 和 obj1.data 指向同一块内存
  // 当 obj1 和 obj2 析构时，会重复 delete data，导致崩溃
  ```



#### 深拷贝 (Deep Copy)



- **定义：** 深拷贝通过**自定义拷贝构造函数**来实现。在深拷贝中，当复制含有指针或动态分配资源的成员时，会为新对象**重新分配一块独立的内存**，并将原对象中的数据内容复制到新分配的内存中。这样，原对象和新对象各自拥有独立的资源副本，互不影响。

- **解决问题：** 避免了浅拷贝导致的重复释放和数据污染问题。

- **示例 (自定义拷贝构造函数实现深拷贝)：**

  ```
  class MyClass {
  public:
      int* data;
      MyClass(int val) {
          data = new int(val);
          std::cout << "Constructor: " << *data << std::endl;
      }
      // 自定义拷贝构造函数 (深拷贝)
      MyClass(const MyClass& other) {
          data = new int(*other.data); // 为新对象分配新的内存，并复制内容
          std::cout << "Copy Constructor (Deep Copy): " << *data << std::endl;
      }
      ~MyClass() {
          if (data) {
              delete data;
              data = nullptr;
              std::cout << "Destructor" << std::endl;
          }
      }
  };
  
  // main 函数中
  // MyClass obj1(10);
  // MyClass obj2 = obj1; // 调用自定义的拷贝构造函数 (深拷贝)
  // obj2.data 和 obj1.data 指向不同的内存地址，内容相同
  // 析构时各自释放各自的内存，安全
  ```



### 什么时候需要自定义拷贝构造函数？



你需要自定义拷贝构造函数（并实现深拷贝）的根本原因是：

当你的类中包含**指向动态分配内存的指针**或**管理其他外部资源（如文件句柄、网络连接）**的成员时。

更具体地说，当以下任一条件成立时：

1. **类中拥有指针或裸资源句柄作为成员：** 这是最常见的情况。如果你的类成员变量中包含 `int*`, `char*`, `FILE*` 等指针，并且这些指针指向的内存是在构造函数中通过 `new` 或 `malloc` 动态分配的，那么你就需要自定义拷贝构造函数。
2. **默认的按位拷贝不能满足你的需求：** 如果默认的浅拷贝会导致资源共享问题（如上述的二次释放或数据污染），你就需要深拷贝。
3. **遵循“三/五/零法则” (Rule of Three/Five/Zero)：**
   - **三法则 (Rule of of Three)：** 如果你需要定义析构函数、拷贝构造函数或拷贝赋值运算符中的任何一个，那么你很可能需要定义另外两个。这是因为如果你手动管理资源（需要析构函数），那么拷贝操作很可能也需要特殊的处理。
   - **五法则 (Rule of Five) (C++11后)：** 加上移动构造函数和移动赋值运算符。如果类需要自定义析构函数、拷贝构造函数、拷贝赋值运算符、移动构造函数或移动赋值运算符中的任何一个，它可能需要定义所有这五个特殊成员函数。
   - **零法则 (Rule of Zero)：** 最好的情况是什么都不需要自定义。这意味着你的类不直接管理资源，而是通过使用标准库容器（如 `std::vector`, `std::string`, `std::unique_ptr`, `std::shared_ptr`）来自动管理资源。这些标准库容器已经正确实现了深拷贝和资源管理。

**总结：** 拷贝构造函数用于通过现有对象初始化新对象。深拷贝和浅拷贝是其实现方式。当类中包含动态分配资源（如指针）时，为了避免资源共享问题（如重复释放），必须自定义拷贝构造函数来实现深拷贝。

## 析构函数可以抛出异常吗？为什么不能抛出异常？除了资源泄露，还有其他需考虑的因素吗？

### 析构函数可以抛出异常吗？



从语法上讲，C++ 析构函数**可以**抛出异常。然而，从程序设计的健壮性和安全性角度来看，**强烈不建议析构函数抛出异常**。

C++11 之后，析构函数默认是 `noexcept` 的（隐式声明为不抛出异常）。这意味着如果一个析构函数在运行时抛出了异常，并且这个异常没有在析构函数内部被捕获，那么程序会立即调用 `std::terminate()` 终止，而不是将异常传播出去。

### 为什么不能抛出异常？

主要原因在于异常处理机制和程序状态的复杂性：

1. **导致不确定行为或程序终止 (Undefined Behavior / `std::terminate`)：**
   - **最危险的情况：** 如果一个异常已经在传播中（例如，某个函数抛出了异常，正在向上层调用栈查找 `catch` 块），此时又有一个析构函数（例如，在堆栈展开时被调用的局部对象的析构函数）抛出另一个异常。
   - C++ 标准规定，在同一个 `throw` 语句中，不能有两个异常同时处于激活状态。如果发生这种情况（即在处理第一个异常时，析构函数又抛出第二个异常），程序会立即调用 `std::terminate()` 终止程序，而不是去处理第二个异常。这会导致程序以一个不确定的状态结束，并且很难调试。
2. **资源泄露 (Resource Leak)：**
   - 析构函数的主要职责是**释放资源**（内存、文件句柄、网络连接等）。如果析构函数在释放资源时抛出异常，那么该异常可能会阻止析构函数中剩余的资源释放代码执行。
   - 例如，析构函数中有多条 `delete` 语句或资源关闭操作。如果第一条 `delete` 抛出异常，后面的 `delete` 就不会被执行，导致剩余资源无法释放，造成**内存泄漏或资源泄漏**。
3. **对象状态不确定性：**
   - 如果析构函数抛出异常，那么对象可能处于一个部分销毁的状态。其内部的一些资源可能已经被释放，而另一些则没有。
   - 这使得程序状态变得非常复杂和不可预测。如果尝试对这个部分销毁的对象进行任何操作，都可能导致更严重的错误。
4. **栈展开中断：**
   - 当一个异常被抛出时，C++ 运行时会执行**栈展开 (Stack Unwinding)**：它会沿着调用栈向上查找匹配的 `catch` 块。在这个过程中，所有在栈上创建的局部对象的析构函数都会被调用以清理资源。
   - 如果在栈展开过程中，某个析构函数又抛出了异常，这会中断正常的栈展开流程，导致上述的程序终止。



### 除了资源泄露，还有其他需考虑的因素吗？



是的，除了资源泄露，主要还有以下因素：

1. **程序终止 (std::terminate)：** 这是最重要的因素。双重异常传播（一个异常未处理，另一个析构函数又抛出）是 C++ 运行时的大忌，会导致程序强行终止。
2. **调试困难：** 当程序因析构函数抛出异常而终止时，很难定位是哪个析构函数以及为什么抛出异常，给调试带来极大困难。
3. **违反RAII原则：** 析构函数是 RAII (Resource Acquisition Is Initialization) 模式的终点。RAII 的核心思想是资源在对象生命周期结束时自动安全释放。如果析构函数可能失败并抛出异常，就违背了 RAII 的自动性和可靠性原则。
4. **接口契约破坏：** 析构函数通常被期望是无失败的。如果它们可能抛出异常，会给客户端代码带来额外的复杂性，需要考虑在对象销毁时进行异常处理，这在实践中几乎不被接受。

### 如何处理析构函数中可能出现的问题？



如果析构函数中调用的某个操作（例如，关闭文件句柄，刷新缓冲区）确实可能失败或抛出异常，应该：

1. **在析构函数内部捕获并处理异常：**

   - 不要让异常逃逸出析构函数。在析构函数内部捕获任何可能抛出的异常，并进行适当的错误处理（例如，记录日志，但不重新抛出）。

   - **示例：**

     ```
     class MyClass {
         // ...
         ~MyClass() {
             try {
                 // 可能抛出异常的操作
                 flush_buffer_to_disk();
             } catch (const std::exception& e) {
                 // 记录日志，但不要重新抛出异常
                 std::cerr << "Error in destructor: " << e.what() << std::endl;
             }
             // 确保所有资源都被释放，即使前面抛出异常
             close_file_handle();
         }
     };
     ```

2. **将可能失败的操作移出析构函数：**

   - 将可能失败的操作（如 `flush()` 或 `close()`）作为普通成员函数提供，让客户端代码在对象销毁前显式调用。这样，客户端可以捕获并处理这些操作可能抛出的异常。如果客户端没有调用，则在析构函数中进行静默的（不抛出异常的）清理。

**结论：** 尽管语法允许，但从设计和稳定性角度，C++ 析构函数**绝对不应该抛出异常**。如果内部操作可能失败，必须在析构函数内部处理这些失败，确保不抛出异常。

------



## 2.2.7 什么情况下会调用拷贝构造函数（三种情况）



拷贝构造函数在 C++ 中用于**初始化一个新对象**，它接受一个**同类类型对象的常量引用**作为参数。以下是调用拷贝构造函数的三种主要情况：

1. **用一个已存在的对象去初始化一个新对象时：**

   - 这是最直接也是最常见的调用方式。当定义一个新对象，并使用另一个同类型的对象来对其进行初始化时，拷贝构造函数会被调用。

   - **语法形式：**

     - `ClassName newObject = existingObject;` (等价于 `ClassName newObject(existingObject);`)
     - `ClassName newObject(existingObject);`

   - **示例：**

     ```
     class MyClass {
     public:
         MyClass() { std::cout << "Default Constructor" << std::endl; }
         MyClass(const MyClass& other) {
             std::cout << "Copy Constructor" << std::endl;
         }
     };
     
     int main() {
         MyClass obj1;           // 调用默认构造函数
         MyClass obj2 = obj1;    // 情况1：使用 = 初始化新对象，调用拷贝构造函数
         MyClass obj3(obj1);     // 情况1：直接括号初始化新对象，调用拷贝构造函数
         return 0;
     }
     ```

2. **当对象作为函数参数进行**值传递**时：**

   - 如果函数参数是按值传递一个对象，那么在函数调用时，会创建一个参数对象的临时副本，并使用拷贝构造函数来初始化这个临时副本。

   - **示例：**

     ```
     class MyClass {
     public:
         MyClass() { std::cout << "Default Constructor" << std::endl; }
         MyClass(const MyClass& other) {
             std::cout << "Copy Constructor" << std::endl;
         }
     };
     
     void func(MyClass obj) { // 参数按值传递
         std::cout << "Inside func" << std::endl;
     }
     
     int main() {
         MyClass obj1;           // 调用默认构造函数
         func(obj1);             // 情况2：obj1 作为参数值传递给 func，调用拷贝构造函数
         return 0;
     }
     ```

   - **注意：** 为了避免不必要的拷贝和提高效率，通常推荐将对象作为**常量引用 (`const ClassName&`)** 或**右值引用 (`ClassName&&`)** 传递给函数，除非你需要函数内部对参数进行修改且不影响原始对象。

3. **当函数返回一个对象时（作为值返回）：**

   - 如果函数返回一个对象，那么在函数返回时，会创建一个临时对象来存储返回值，并使用拷贝构造函数来初始化这个临时对象。

   - **注意：** 现代 C++ 编译器通常会进行**返回值优化 (Return Value Optimization, RVO)** 或 **命名返回值优化 (Named Return Value Optimization, NRVO)**，这可以**省略**拷贝构造函数的调用。即使在理论上会调用拷贝构造函数，实际编译时也可能被优化掉。

   - **示例：**

     ```
     class MyClass {
     public:
         MyClass() { std::cout << "Default Constructor" << std::endl; }
         MyClass(const MyClass& other) {
             std::cout << "Copy Constructor" << std::endl;
         }
     };
     
     MyClass createObject() {
         MyClass temp_obj; // 调用默认构造函数
         return temp_obj;    // 情况3：返回一个对象，可能调用拷贝构造函数 (RVO/NRVO 可能省略)
     }
     
     int main() {
         MyClass obj = createObject(); // 可能调用拷贝构造函数 (如果未优化)
         return 0;
     }
     ```

   - 即使编译器省略了拷贝构造函数的调用，你的类也必须有一个可访问的拷贝构造函数，否则代码将无法编译通过。

**总结：** 拷贝构造函数是在“从一个现有对象初始化一个新对象”时被调用的。理解这三种情况对于正确管理对象生命周期和避免潜在的性能问题至关重要。

------



## 2.2.8 析构函数一般写成虚函数的原因



**析构函数一般写成虚函数的主要原因是为了确保在通过基类指针删除派生类对象时，能够正确调用到派生类的析构函数，从而避免资源泄漏和未定义行为。这与 C++ 的多态性密切相关。**

```
class Base {
public:
    Base() { std::cout << "Base Constructor" << std::endl; }
    ~Base() { std::cout << "Base Destructor" << std::endl; } // 非虚析构函数
};

class Derived : public Base {
public:
    int* data;
    Derived() : data(new int(10)) { std::cout << "Derived Constructor" << std::endl; }
    ~Derived() {
        delete data; // 派生类中需要释放的资源
        std::cout << "Derived Destructor" << std::endl;
    }
};
```

现在，如果我们通过基类指针删除派生类对象：

```
Base* ptr = new Derived(); // 基类指针指向派生类对象
delete ptr; // 问题发生在这里！
```

### 为什么会出问题？

当基类析构函数不是虚函数时，`delete ptr;` 会发生**静态绑定 (Static Binding)**。这意味着编译器在编译时就会根据指针的类型（`Base*`）来决定调用哪个析构函数。因此，只会调用 `Base` 类的析构函数，而不会调用 `Derived` 类的析构函数。

**结果：**

1. `Base` 析构函数被调用。
2. `Derived` 析构函数（负责释放 `data` 指向的内存）**没有被调用**。
3. `Derived` 对象中动态分配的内存 `data` 无法被释放，导致**内存泄漏 (Memory Leak)**

### 解决方案：将基类析构函数声明为虚函数

通过将基类的析构函数声明为 `virtual`：

```
class Base {
public:
    Base() { std::cout << "Base Constructor" << std::endl; }
    virtual ~Base() { std::cout << "Base Destructor" << std::endl; } // 虚析构函数
};

class Derived : public Base {
public:
    int* data;
    Derived() : data(new int(10)) { std::cout << "Derived Constructor" << std::endl; }
    ~Derived() {
        delete data;
        std::cout << "Derived Destructor" << std::endl;
    }
};
```

现在，当执行 `delete ptr;` 时：

- 由于基类析构函数是虚函数，`delete` 操作会触发**动态绑定 (Dynamic Binding)**。
- 运行时系统会根据 `ptr` 实际指向的对象的类型（即 `Derived` 类型），通过对象的 `vptr` 查找并调用 `Derived` 类的析构函数。
- `Derived` 类的析构函数被调用后，会**自动链式调用**其基类（`Base`）的析构函数。

**结果：**

1. `Derived` 析构函数被调用，释放 `data`。
2. `Base` 析构函数被调用。
3. 所有资源都被正确释放，没有内存泄漏。

- **何时将析构函数声明为虚函数？**
  - **当一个类打算作为基类，并且你期望通过基类指针或引用来删除派生类对象时，其析构函数就应该声明为 `virtual`。**
  - 如果一个类没有任何虚函数，但它可能被用作基类，并且其派生类可能需要通过基类指针删除，那么其析构函数也应该声明为虚函数。
  - **经验法则：** 如果类中有任何虚函数，那么其析构函数也应该是虚函数。
  - 如果一个类不是为了被继承而设计的（即它不包含任何虚函数，并且不打算作为基类使用），那么其析构函数不需要是虚函数。为非多态类添加虚析构函数会增加对象的大小（因为需要 `vptr`）和一些小的运行时开销，这是不必要的。

------



## 构造函数为什么一般不定义为虚函数



构造函数通常（并且**不能**）被定义为虚函数，主要有以下几个原因：

1. **虚函数机制的实现原理：**
   - 虚函数的调用依赖于**虚函数表指针 (`vptr`)** 和**虚函数表 (`vtable`)**。`vptr` 存储在对象的内存中，指向该对象实际类型的 `vtable`。
   - 然而，在**构造函数执行期间**，对象的 `vptr` 还没有被完全初始化以指向派生类的 `vtable`。在基类构造函数执行时，对象的 `vptr` 指向的是基类的 `vtable`；只有当基类构造函数执行完毕，控制权回到派生类构造函数时，`vptr` 才会更新以指向派生类的 `vtable`。
   - 因此，如果在构造函数中调用虚函数，即使是基类的虚函数，它也只能调用到当前构造阶段对应的类的版本（例如，在基类构造函数中，即使是虚函数调用，也只能调用基类自己的实现），无法实现多态行为。
2. **对象尚未完全构造：**
   - 当构造函数被调用时，对象还没有完全形成。特别是当基类构造函数被调用时，派生类的成员变量还没有被初始化。
   - 如果在基类构造函数中调用派生类的虚函数（假设它能实现多态），那么这个派生类的虚函数可能会访问尚未初始化或构造的派生类成员，导致**未定义行为**或程序崩溃。
   - 多态的本质是“用基类指针/引用调用派生类的函数”，但构造过程是从基类到派生类的，当基类构造时，派生类尚不存在。
3. **多态的前提是对象已存在：**
   - 多态要求通过一个**已经存在的、完整创建的**对象来调用虚函数。
   - 而构造函数的作用正是**创建和初始化对象**。在对象创建完成之前，谈论多态性是没有意义的。你没有一个指向“尚未完全存在的对象”的指针或引用来进行多态调用。
4. **不需要多态性：**
   - 构造函数的目的就是创建一个特定类型的对象。你总是知道你正在构造的是哪个确切类型的对象。
   - 你不需要基类指针或引用来构造派生类对象，你直接通过派生类名来构造。因此，构造函数不具备多态性的需求。

**总结：**

- **技术限制：** 虚函数机制依赖于 `vptr` 和 `vtable`，这些在构造函数执行期间尚未完全就绪，无法实现正确的动态绑定。
- **安全风险：** 在构造期间调用派生类的代码可能会访问未初始化的成员，导致未定义行为。
- **设计需求：** 构造函数的目的就是创建特定类型的对象，不需要多态行为。

因此，C++ 标准明确规定**构造函数不能是虚函数**。如果你尝试将构造函数声明为 `virtual`，编译器会报错。

## 什么是纯虚函数

### 纯虚函数 (Pure Virtual Function)



- **定义：** 纯虚函数是在基类中声明的虚函数，但**没有提供实现 (implementation)**，而是在函数声明的末尾加上 `= 0`。
- **语法：** `virtual 返回类型 函数名(参数列表) = 0;`
- **特点：**
  1. **无实现：** 纯虚函数只声明接口，不提供具体实现。
  2. **强制派生类实现：** 任何直接或间接继承包含纯虚函数的基类的派生类，**必须**实现（重写）这个纯虚函数，否则它自己也会变成抽象类。
  3. **使类成为抽象类：** 只要一个类中包含一个或多个纯虚函数（无论是自身定义还是从基类继承未实现的），那么这个类就自动成为一个**抽象类 (Abstract Class)**。
  4. **抽象类不能实例化：** 抽象类不能被直接创建对象（不能实例化），因为它们是不完整的，缺少某些函数的实现。它们只能作为基类来使用。
  5. **抽象类指针/引用：** 可以声明抽象类的指针或引用，用于指向其派生类的对象，从而实现多态。
- **用途：**
  - **定义接口 (Interface)：** 纯虚函数用于定义一个通用的接口规范，强制所有派生类都必须遵循这个接口，提供具体的实现。
  - **实现多态：** 抽象类及其纯虚函数是实现运行时多态的重要手段。
  - **设计模式：** 在许多设计模式中，如策略模式、模板方法模式等，都广泛使用纯虚函数来定义抽象接口。

```
#include <iostream>

// 抽象基类
class Shape {
public:
    // 纯虚函数：定义了所有形状都必须有的计算面积和周长的方法
    virtual double getArea() const = 0;   // = 0 使其成为纯虚函数
    virtual double getPerimeter() const = 0; // = 0 使其成为纯虚函数

    // 虚析构函数，以防通过基类指针删除派生类对象
    virtual ~Shape() {
        std::cout << "Shape Destructor" << std::endl;
    }
    // 普通成员函数
    void printInfo() const {
        std::cout << "This is a shape." << std::endl;
    }
};

// 具体派生类：Rectangle
class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    // 必须实现基类的纯虚函数
    double getArea() const override {
        return width * height;
    }
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    ~Rectangle() override {
        std::cout << "Rectangle Destructor" << std::endl;
    }
};

// 具体派生类：Circle
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    // 必须实现基类的纯虚函数
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
    double getPerimeter() const override {
        return 2 * 3.14159 * radius;
    }
    ~Circle() override {
        std::cout << "Circle Destructor" << std::endl;
    }
};

int main() {
    // Shape s; // 错误：不能实例化抽象类 Shape
    
    Shape* s1 = new Rectangle(5, 4);
    Shape* s2 = new Circle(3);

    std::cout << "Rectangle Area: " << s1->getArea() << std::endl;
    std::cout << "Circle Perimeter: " << s2->getPerimeter() << std::endl;

    s1->printInfo(); // 可以调用普通成员函数

    delete s1;
    delete s2;

    return 0;
}
```

**总结：** 纯虚函数是 C++ 中定义抽象接口的机制。它强制派生类提供特定函数的实现，从而使基类成为抽象类，不能直接实例化。它是实现多态和构建稳健类层次结构的重要工具。

------



## 2.2.11 静态绑定和动态绑定的介绍



在 C++ 中，**绑定 (Binding)** 是指将函数调用与函数体中的代码进行关联的过程。根据绑定发生的时间，可以分为**静态绑定**和**动态绑定**。



### 1. 静态绑定 (Static Binding / Early Binding / Compile-Time Binding)



- **定义：** 在**编译时 (Compile-Time)** 确定函数调用的具体实现（即调用哪个函数）。
- **特点：**
  - **基于指针/引用的类型：** 编译器根据**指针或引用的声明类型**来决定调用哪个函数，而不是实际对象的类型。
  - **效率高：** 因为在编译时就已经确定了调用目标，所以运行时开销较小。
  - **无多态性：** 无法实现运行时多态。
- **发生条件：**
  - 调用**非虚函数**时。
  - 通过**对象本身**（而不是指针或引用）调用函数时。
  - 在构造函数和析构函数中调用虚函数时（即使是虚函数，也退化为静态绑定，因为此时对象可能未完全构建）。

**示例：**

```
#include <iostream>

class Base {
public:
    void func() { // 非虚函数
        std::cout << "Base::func()" << std::endl;
    }
    virtual void vfunc() { // 虚函数
        std::cout << "Base::vfunc()" << std::endl;
    }
};

class Derived : public Base {
public:
    void func() { // 隐藏基类 func()
        std::cout << "Derived::func()" << std::endl;
    }
    void vfunc() override { // 重写虚函数
        std::cout << "Derived::vfunc()" << std::endl;
    }
};

int main() {
    Derived d_obj;
    Base* b_ptr = &d_obj; // 基类指针指向派生类对象
    Derived* d_ptr = &d_obj; // 派生类指针指向派生类对象

    // 静态绑定示例：调用非虚函数
    b_ptr->func();   // 编译时根据 b_ptr 的类型 (Base*) 确定调用 Base::func()
                     // 输出: Base::func()
    d_ptr->func();   // 编译时根据 d_ptr 的类型 (Derived*) 确定调用 Derived::func()
                     // 输出: Derived::func()
    d_obj.func();    // 编译时根据 d_obj 的类型 (Derived) 确定调用 Derived::func()
                     // 输出: Derived::func()

    // 静态绑定示例：通过对象本身调用虚函数
    d_obj.vfunc();   // 即使是虚函数，通过对象本身调用也是静态绑定
                     // 输出: Derived::vfunc()

    return 0;
}
```



### 2. 动态绑定 (Dynamic Binding / Late Binding / Run-Time Binding)



- **定义：** 在**运行时 (Run-Time)** 确定函数调用的具体实现。
- **特点：**
  - **基于实际对象类型：** 编译器根据**指针或引用实际指向的对象的类型**来决定调用哪个函数。
  - **运行时开销：** 需要通过 `vptr` 和 `vtable` 查找，会有一定的运行时开销，但通常很小。
  - **实现多态性：** 允许用统一的接口处理不同类型的对象，是面向对象多态的核心。
- **发生条件：**
  - **必须有继承关系。**
  - **必须调用的是虚函数。**
  - **必须通过基类指针或基类引用来调用虚函数。**

**示例：**

```
#include <iostream>

class Base {
public:
    void func() { std::cout << "Base::func()" << std::endl; }
    virtual void vfunc() { // 虚函数
        std::cout << "Base::vfunc()" << std::endl;
    }
};

class Derived : public Base {
public:
    void func() { std::cout << "Derived::func()" << std::endl; }
    void vfunc() override { // 重写虚函数
        std::cout << "Derived::vfunc()" << std::endl;
    }
};

int main() {
    Derived d_obj;
    Base* b_ptr = &d_obj; // 基类指针指向派生类对象
    Base& b_ref = d_obj;  // 基类引用引用派生类对象

    std::cout << "--- Dynamic Binding Examples ---" << std::endl;

    // 动态绑定示例：通过基类指针调用虚函数
    b_ptr->vfunc();  // 运行时根据 b_ptr 实际指向的 Derived 对象调用 Derived::vfunc()
                     // 输出: Derived::vfunc()

    // 动态绑定示例：通过基类引用调用虚函数
    b_ref.vfunc();   // 运行时根据 b_ref 实际引用的 Derived 对象调用 Derived::vfunc()
                     // 输出: Derived::vfunc()

    // 另一个例子
    Base* ptr1 = new Base();
    Base* ptr2 = new Derived();

    ptr1->vfunc(); // 输出: Base::vfunc()
    ptr2->vfunc(); // 输出: Derived::vfunc()

    delete ptr1;
    delete ptr2;

    return 0;
}
```



### 总结比较：



| 特性         | 静态绑定 (Static Binding)                                    | 动态绑定 (Dynamic Binding)       |
| ------------ | ------------------------------------------------------------ | -------------------------------- |
| **时机**     | 编译时                                                       | 运行时                           |
| **依据**     | 指针/引用的**声明类型**                                      | 指针/引用实际指向的**对象类型**  |
| **函数类型** | 非虚函数；或通过对象本身调用的虚函数；或构造/析构函数中调用的虚函数 | 虚函数                           |
| **调用方式** | 通过对象、指针或引用                                         | **必须通过基类指针或基类引用**   |
| **效率**     | 高 (直接跳转)                                                | 略低 (通过 `vptr`/`vtable` 查找) |
| **多态性**   | 不支持多态                                                   | **支持多态** (核心机制)          |



理解静态绑定和动态绑定对于理解 C++ 多态性至关重要，它决定了在运行时程序的行为。

------





## 2.2.13 重写、重载、覆盖的区别



### 1. 重载 (Overload)



- **发生范围：** 同一个作用域（同一个类或同一个命名空间）。

- **概念：** 允许在**同一个作用域内**，定义多个名称相同但**参数列表（参数类型、参数数量、参数顺序）不同**的函数。

- **特点：**

  - 与返回类型无关，只看参数列表。
  - 是一种**编译时多态**（或静态多态），编译器在编译时根据参数列表决定调用哪个函数。

- **示例：**

  ```
  class Printer {
  public:
      void print(int i) { /* ... */ }
      void print(double d) { /* ... */ } // 重载 print
      void print(const char* s) { /* ... */ } // 重载 print
  };
  ```

  这里 `print` 函数被重载了三次。



### 2. 重写 (Override) / 覆盖 (Override)



- **发生范围：** 发生在**继承关系中**，派生类中的函数与基类中的**虚函数**同名、同参数列表、同返回类型（C++11 `override` 关键字可帮助检查）。

- **概念：** 派生类对基类中**虚函数**的实现进行重新定义。

- **特点：**

  - 必须是虚函数。
  - 参数列表和返回类型必须与基类虚函数完全一致。
  - 是一种**运行时多态**（或动态多态），通过虚函数表 (vtable) 和虚指针 (vptr) 实现，在运行时根据对象的实际类型决定调用哪个版本的函数。
  - C++11 引入了 `override` 关键字，显式标记函数为重写，有助于编译器检查是否正确重写了基类虚函数，避免拼写错误或签名不匹配导致的问题。

- **示例：**

  ```
  class Base {
  public:
      virtual void show() { std::cout << "Base::show\n"; }
  };
  
  class Derived : public Base {
  public:
      void show() override { // 重写/覆盖 Base::show
          std::cout << "Derived::show\n";
      }
  };
  ```

  当通过基类指针或引用调用 `show()` 时，会根据实际指向的对象类型调用相应的 `show()`。



### 3. 隐藏 (Hide) / 遮蔽 (Shadow)



- **发生范围：** 发生在**继承关系中**，派生类中的函数与基类中的函数同名，但**不满足重写条件**（基类函数不是虚函数，或者参数列表、返回类型不一致）。

- **概念：** 派生类中定义了一个与基类同名的函数，导致基类中的同名函数在派生类中**被隐藏（遮蔽）**。此时，即使参数列表不同，基类的同名函数也不会被重载，而是被隐藏。

- **特点：**

  - 与虚函数无关。
  - 即使参数列表不同，基类的同名函数也会被隐藏。
  - 是一种**编译时行为**。

- **示例：**

  ```
  class Base {
  public:
      void func(int i) { std::cout << "Base::func(int)\n"; }
  };
  
  class Derived : public Base {
  public:
      void func(double d) { std::cout << "Derived::func(double)\n"; } // 隐藏 Base::func(int)
  };
  
  // 使用示例
  Derived d;
  d.func(10.5); // 调用 Derived::func(double)
  // d.func(10); // 编译错误！Base::func(int) 被隐藏了
  // 要调用 Base::func(int)，需要显式指定：
  d.Base::func(10); // OK
  ```

  在这个例子中，`Derived::func(double)` 隐藏了 `Base::func(int)`。



### 总结对比：



| 特性       | 重载 (Overload)          | 重写 (Override)                       | 隐藏 (Hide) / 遮蔽 (Shadow)                                  |
| ---------- | ------------------------ | ------------------------------------- | ------------------------------------------------------------ |
| **范围**   | 同一作用域（类内或全局） | 继承关系中的派生类                    | 继承关系中的派生类                                           |
| **函数名** | 相同                     | 相同                                  | 相同                                                         |
| **参数**   | 必须不同                 | 必须相同                              | 可以相同也可以不同                                           |
| **虚函数** | 无关                     | 基类函数必须是虚函数                  | 基类函数可以是虚函数也可以不是，但派生类函数不是虚函数或签名不匹配时 |
| **多态**   | 编译时多态（静态绑定）   | 运行时多态（动态绑定）                | 无多态，编译时行为                                           |
| **关键字** | 无                       | `virtual` (基类), `override` (派生类) | 无                                                           |

------



##  成员初始化列表的概念，为什么用成员初始化列表会快一些（性能优势）？

### 成员初始化列表的概念



**成员初始化列表 (Member Initializer List)** 是一种在 C++ 构造函数中初始化类成员的特殊语法。它位于构造函数的参数列表之后、函数体之前，以冒号 `:` 开头，后面跟着逗号分隔的成员初始化表达式。

**语法结构：**

```
ClassName::ClassName(parameter_list) : member1(arg1), member2(arg2, arg3), ... {
    // 构造函数体
}
```

- `member1`, `member2` 是类的成员变量。
- `arg1`, `arg2`, `arg3` 是用于初始化对应成员的参数或表达式。

**示例：**

```
class MyClass {
public:
    int value1;
    double value2;
    const int constValue; // const 成员必须通过初始化列表初始化
    ReferenceClass& ref; // 引用成员必须通过初始化列表初始化
    AnotherClass obj; // 另一个类的对象成员

    // 使用成员初始化列表
    MyClass(int v1, double v2, int cv, ReferenceClass& r, AnotherClass a_obj)
        : value1(v1),
          value2(v2),
          constValue(cv),
          ref(r),
          obj(a_obj) // 调用 AnotherClass 的拷贝构造函数
    {
        // 构造函数体，此时所有成员都已初始化
        // 可以在这里执行其他逻辑
    }

    // 假设不使用初始化列表，在函数体中赋值
    /*
    MyClass(int v1, double v2, int cv, ReferenceClass& r, AnotherClass a_obj) {
        value1 = v1; // 赋值
        value2 = v2; // 赋值
        // constValue = cv; // 错误：const 成员不能被赋值
        // ref = r; // 错误：引用不能被重新绑定
        // obj = a_obj; // 这里调用的是 AnotherClass 的拷贝赋值运算符
    }
    */
};
```



### 为什么用成员初始化列表会快一些（性能优势）？



使用成员初始化列表比在构造函数体内部进行赋值操作具有**显著的性能优势**，尤其是在处理**非内建类型成员（如自定义类对象）**、**`const` 成员**和**引用成员**时。

主要原因在于它们的**初始化时机和方式不同**：

1. **初始化 vs. 赋值：**
   - **成员初始化列表：** 成员在构造函数体**执行之前**就被**直接初始化**了。对于非内建类型，这意味着它们直接调用了相应的构造函数（如拷贝构造函数、移动构造函数或默认构造函数）。
   - **构造函数体内部赋值：** 成员在构造函数体中是通过**赋值运算符**来赋值的。这意味着对于非内建类型，它们会先调用**默认构造函数进行一次默认初始化**，然后再调用**赋值运算符**进行一次赋值操作。
2. **避免两次操作（默认构造 + 赋值）：**
   - 考虑一个自定义类 `ExpensiveObject`，它的构造和赋值操作都很耗时。
   - **使用初始化列表：** `MyClass(ExpensiveObject eo) : myObj(eo) {}`
     - `myObj` 直接通过 `ExpensiveO	bject` 的拷贝构造函数（或移动构造函数）进行初始化。**只执行一次构造操作。**
   - **在函数体中赋值：** `MyClass(ExpensiveObject eo) { myObj = eo; }`
     - `myObj` 首先会调用 `ExpensiveObject` 的**默认构造函数**进行初始化。
     - 然后，`myObj = eo;` 会调用 `ExpensiveObject` 的**拷贝赋值运算符**进行赋值。
     - 这导致了**两次操作**：一次默认构造，一次拷贝赋值。显然，这会带来额外的开销。
3. **强制性要求（const 成员和引用成员）：**
   - `const` 成员和引用成员在声明时就必须初始化，它们不能被赋值。因此，它们**只能**通过成员初始化列表进行初始化。如果在构造函数体中尝试对其赋值，会导致编译错误。
   - 这意味着，对于这些类型的成员，**没有其他选择，只能使用初始化列表**。
4. **对于内建类型（int, double, char* 等）：**
   - 对于内建类型，例如 `int` 或 `double`，使用初始化列表和在构造函数体中赋值的性能差异通常**可以忽略不计**。因为内建类型没有构造函数和赋值运算符的概念，它们的初始化和赋值都是简单的内存操作。
   - 然而，出于代码风格一致性和防止意外行为（如忘记初始化），仍然推荐对所有成员使用初始化列表。

**总结性能优势：**

成员初始化列表的性能优势主要体现在：

- **避免了对非内建类型成员的额外默认构造和赋值操作。**
- **对于需要初始化的 `const` 成员和引用成员，它是唯一合法的初始化方式。**

因此，最佳实践是**始终优先使用成员初始化列表**来初始化所有成员变量。这不仅能提升性能，还能确保代码的正确性和健壮性。

## 如何避免编译器进行的隐式类型转换；（`explicit` 关键字）

在 C++ 中，**转换构造函数**（只有一个非默认参数的构造函数）和**类型转换运算符**（将当前类转换为其他类型的运算符）可能导致编译器执行**隐式类型转换**。虽然这在某些情况下很方便，但它也可能导致意想不到的行为或难以发现的逻辑错误。

为了避免编译器进行的隐式类型转换，C++ 提供了 `explicit` 关键字。



### `explicit` 关键字的作用



`explicit` 关键字只能用于**修饰构造函数**和 **C++11 之后的类型转换运算符**。它的作用是：

- **阻止编译器进行隐式类型转换。**
- **强制程序员使用显式转换**（例如通过强制类型转换或直接调用构造函数）。



### 使用 `explicit` 阻止转换构造函数进行隐式转换



当一个类的构造函数被 `explicit` 关键字修饰时，它就不能用于执行隐式类型转换。

**没有 `explicit` 关键字（允许隐式转换）：**

```
#include <iostream>

class MyClass {
public:
    int value;
    MyClass(int val) : value(val) { // 转换构造函数
        std::cout << "MyClass(int) called with: " << val << std::endl;
    }
};

int main() {
    MyClass obj1 = 10;          // 隐式转换：int 10 被转换为 MyClass 对象，调用 MyClass(int)
    MyClass obj2(20);           // 显式调用构造函数
    MyClass obj3 = static_cast<MyClass>(30); // 显式转换

    void func(MyClass m) {
        std::cout << "func(MyClass) called with value: " << m.value << std::endl;
    }
    func(40); // 隐式转换：int 40 被转换为 MyClass 对象，然后传递给 func
    return 0;
}
```

**输出：**

```
MyClass(int) called with: 10
MyClass(int) called with: 20
MyClass(int) called with: 30
MyClass(int) called with: 40
func(MyClass) called with value: 40
```

在上述例子中，`MyClass obj1 = 10;` 和 `func(40);` 都发生了隐式类型转换。

**使用 `explicit` 关键字（阻止隐式转换）：**

```
#include <iostream>

class MyClass {
public:
    int value;
    explicit MyClass(int val) : value(val) { // explicit 转换构造函数
        std::cout << "explicit MyClass(int) called with: " << val << std::endl;
    }
};

int main() {
    // MyClass obj1 = 10; // 编译错误！不允许隐式转换
    MyClass obj2(20);           // OK：显式调用构造函数
    MyClass obj3 = static_cast<MyClass>(30); // OK：显式转换

    void func(MyClass m) {
        std::cout << "func(MyClass) called with value: " << m.value << std::endl;
    }
    // func(40); // 编译错误！不允许隐式转换

    // 必须显式转换才能调用 func
    func(MyClass(40)); // OK：显式调用构造函数
    func(static_cast<MyClass>(50)); // OK：显式转换
    return 0;
}
```

**输出：**

```
explicit MyClass(int) called with: 20
explicit MyClass(int) called with: 30
explicit MyClass(int) called with: 40
func(MyClass) called with value: 40
explicit MyClass(int) called with: 50
func(MyClass) called with value: 50
```

可以看到，加上 `explicit` 后，需要显式地构造 `MyClass` 对象，编译器不再允许隐式转换。

### `explicit` 在类型转换运算符中的应用 (C++11 及更高版本)

在 C++11 之后，`explicit` 也可以用于修饰用户定义的类型转换运算符（`operator T()`），以防止隐式转换到目标类型 `T`。

**没有 `explicit` 关键字（允许隐式转换）：**

```
#include <iostream>

class MyNum {
public:
    int num;
    MyNum(int n) : num(n) {}

    // 允许隐式转换为 bool
    operator bool() const {
        std::cout << "operator bool() called" << std::endl;
        return num != 0;
    }
};

int main() {
    MyNum n1(0);
    if (n1) { // 隐式转换为 bool
        std::cout << "n1 is true" << std::endl;
    } else {
        std::cout << "n1 is false" << std::endl;
    }

    bool b = n1; // 隐式转换为 bool
    std::cout << "b = " << b << std::endl;
    return 0;
}
```

**输出：**

```
operator bool() called
n1 is false
operator bool() called
b = 0
```

**使用 `explicit` 关键字（阻止隐式转换）：**

```
#include <iostream>

class MyNum {
public:
    int num;
    MyNum(int n) : num(n) {}

    // 阻止隐式转换为 bool
    explicit operator bool() const {
        std::cout << "explicit operator bool() called" << std::endl;
        return num != 0;
    }
};

int main() {
    MyNum n1(0);
    // if (n1) { // 编译错误！不允许隐式转换
    //     std::cout << "n1 is true" << std::endl;
    // } else {
    //     std::cout << "n1 is false" << std::endl;
    // }

    // 此时 if 语句需要显式转换
    if (static_cast<bool>(n1)) { // OK：显式转换
        std::cout << "n1 is true" << std::endl;
    } else {
        std::cout << "n1 is false" << std::endl;
    }

    // bool b = n1; // 编译错误！不允许隐式转换

    bool b = static_cast<bool>(n1); // OK：显式转换
    std::cout << "b = " << b << std::endl;
    return 0;
}
```

**输出：**

```
explicit operator bool() called
n1 is false
explicit operator bool() called
b = 0
```

通过 `explicit` 关键字，我们可以更好地控制类型转换的行为，避免了可能导致逻辑错误的隐式转换。



### 总结



`explicit` 关键字是 C++ 中防止不期望的隐式类型转换的重要工具，它提高了代码的清晰性和健壮性，减少了潜在的bug。在设计类时，除非你非常确定需要隐式转换，否则通常推荐将单参数构造函数标记为 `explicit`。