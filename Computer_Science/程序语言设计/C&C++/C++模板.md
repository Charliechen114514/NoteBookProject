# Lesson I: `function_template`

​	我们很快就可以开始我们的模板之旅：

## 入门

​	我们将会介绍基本的模板：函数模板，类模板。以及剩下更有趣的无类型的模板，可变模板，`typename`这个关键字等。

​	一个显而易见的问题是：为什么学习模板？我们知道：模板就是为了解决那些为了不得不为新类型重写模板的繁琐的工作的。当然你可以：

> 1. 当超级苦力工：我就乐意疯狂穷举类型塞implements
> 2. 更聪明一点，你传递一个父类：`Object`(`Java`味道来了)或者是`void*`（C风格）
> 3. 你打算整点预处理器

​	我们承认，这确实可行，但是只是works，他的缺点是明显的：

> 1. 第一个最笨：你在干一件事情：那就是重复的造轮子`(Reinvent the wheel :))`
> 2. 不得不增加了依赖，你的一切实现都被迫带上了一个`Object`的依赖，而事实上它完全不必存在！或者是void*干脆让类型检查失效——退后到写C去了！
> 3. 预处理器？可以！但是你知道宏过于复杂会诱发怎样奇怪的语义错误（很有可能是没思考全部逻辑！）

​	为了更快的，更高效率的开发，使用templates是一个显然不错的选择。现代C++ STL就是Template - Based的

## 函数模板

### 基础与使用

​	先来看函数模板！

​	回忆你最开始写一个叫做add的函数：

```c++
int add(int a, int b){
	return a + b;
}
```

​	现在，你想要给两个double也做加法，在过去没有模板的日子里：

```c++
double double_add(double a, double b){
	return a + b;
}
```

​	之后呢？如果我想要处理更多的像不同类型不同长度的浮点数，难不成还要写一大堆的其他函数？太繁琐了！只是数据类型不同却要搞很多相同操作的函数显得太蠢。

​	**函数模板让单个函数拥有了处理不同类型的能力：也就是说，他现在就是等价于一组可以handle多个类型进行相同处理的函数了。**

​	口说无凭，上代码！

```c++
template<typename T>
T add(T a, T b) {
	return a + b;
}

int main()
{
	int res = add<int>(1, 2);
	double res2 = add<double>(1.0, 2);
}
```

​	现在，你可以看到，一个函数add可以handle不同类型的相加了！再比如，我们希望求解两个数的在最大值，现在你也不需要费劲的为每一个类型编写`typename_max`函数了，直接使用模板：

```c++
template<typename T>
T max(T a, T b) {
	return a > b ? a : b;
}

int main()
{
	auto res = ::max<int>(1, 2);
	auto res2 = ::max<double>(1.0, 2.0);
	std::cout << res << " " << res2;
}
```

​	回到正题：我们模板的一般格式是啥呢：

```
template< seperated-lists-parameters >
```

​	就是这样！`template<>`，里头加上一些独立的参数。注意，还真不一定是类型名称，可能还是其他一些东西，我们放在后面的非类型模板里会提到。

​	在现在这个阶段，我们可以狭隘的认为模板就是这样声明的：

```c++
template<typename T1, typename T2, ...> // if any required!
```

​	因为一些历史的遗留问题，事实上这里的关键字是class也没问题（乐）

```c++
template<class T1, class T2, ...> // if any required!
```

​	但是这样就会给人造成一种误解——这里貌似只可以传递类！好吧，事实上不一定是的！

​	实际上，我们看看模板到底做了什么工作！当我们使用上面我们编写的`add`或者是`max`的时候，编译器会根据我们写的代码进行扫描：当他看到我们分别对`int, double`类型使用了模板，他就会生成（严肃的讲，应该称之为实例化才对）两个函数的定义：

​	当我们为模板函数使用`int`类型进行实例化的时候，实际上等价的生成了一个这样的函数

```
int max(int, int);
```

​	有点像将T换成了int！一种简单的理解方式。这样的过程被我们定义为：当我们给模板函数以确定的类型的时候，模板函数就会被实例化为一个具体的函数。

​	但是我们试着想一下：如果我们的类型不支持比较操作，进而压根就没有`max`操作这一说，会怎样呢？我们把我们写的`max`函数里实例化复数类型：

```
template<typename T>
T max(T a, T b) {
	return a > b ? a : b;
}

int main()
{
	std::complex<float> t1(1, 2);
	std::complex<float> t2(2, 2);
	auto res = ::max(t1, t2);
}
```

​	代码IDE奇怪的没有向你抱怨，一切太平，但是很快：

```
二进制“>”:“T”不定义该运算符或到预定义运算符可接收的类型的转换
```

​	也就是说，只有在我们的代码被编译的时候，编译器才会实例化模板，他将T替换成`std::complex<float>`之后就会发现：我们没法对复数做比较操作！这个时候就会抛错了

​	总的来讲，我们的模板代码的“编译”分为两步走：

​	实例化之前：

> 1. 查看有没有语法书写上的错误：比如说掉了分号，单书名号这种
> 2. 使用了那些模板和之前代码没有定义，也就是未知的名称会报错误
> 3. 其他的一些跟模板无关的static_assertions也会检查

​	实例化之后，实际上就是将类型装进去之后查看代码是不是合理的，符合逻辑的。

```c
template<typename T>
void makeError(T t)
{
	undeclared(); // First TimeError
    other_undeclared(t); // Second Time Compiled
    static_assert(sizeof(int) > 10,"int is too small"); // First TimeError
    static_assert(sizeof(T) > 10, "T is too small");//  First TimeError
}
```

​	当通过引用声明调用参数时，即使是微不足道的转换也不适用于类型推导。用同一模板参数T声明的两个参数必须完全匹配。

​	当按值声明调用参数时，只支持这样的退化的转换 ：忽略带有const或volatile的限定，引用转换为引用类型，以及原始数组或函数转换为相应的指针类型。对于用声明的两个参数退化的类型必须匹配相同的模板参数T。

​	对于多模板的参数，可以这样写：

```c++
template<typename T1, typename T2>
T1 max(T1 a, T2 b);
```

​	但是现在到的问题是：只是指定了T1为返回类型，也就是说：

``` 
max(66.66, 40) -> 66.66
max(40, 66.66) -> 66
```

​	这不符合我们的预期，我们可以这样解决这个棘手的问题：

> 引入一个标识返回结果的template
>
> 让编译器自行推导返回类型
>
> 让返回类型为两者的“公共类型”为两者的“公共类型”

​	第一种方式很简单：

```c++
template<typename T1, typename T2, typename RT>
RT max(T1 a, T2 b);
```

​	第二种方式，则是使用auto来解决这个问题。在C++14之后，终于可以书写这个非常简单的方式而不需要考虑任何复杂的情况：

```c++
template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}
```

​	事实上，在没有相应尾随返回类型的情况下对返回类型使用 auto（将在末尾引入 ->）表示必须从函数体中的返回语句中推导出实际的返回类型。当然，从函数体中推导出返回类型必须是可能的。因此，代码必须可用，并且必须匹配多个 return 语句。

​	返回的类型依旧公共：

```c++
#include <iostream>
template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#define SHOW_WITH_TYPE(X) std::cout << #X << "With Value:> "<< X << " With type:> " << typeid(X).name() << "\n";


int main()
{
    auto a1 = ::max(40, 66.66); // 66.66 ->double
    SHOW_WITH_TYPE(a1);
    auto a2 = ::max(66.66, 400); /// 400->double
    SHOW_WITH_TYPE(a2);
}
```

​	而在C++14之前，代码甚至更加的复杂：我们必须指定返回的类型是如何的（一点儿不auto）

```c++
auto max (T1 a, T2 b) -> typename std::decay<decltype(true?a:b)>::type
{
	return b < a ? a : b;
}
```

​	只有这样书写，我们的程序才算完备：这是因为我们还需要考虑到引用的问题 

​	这里使用`std::decay<>`，它返回成员类型中的结果类型。它由`<type_trait>`中的标准库定义（见第732页第D.5节）。因为成员类型是一种类型，必须使用typename限定表达式才能访问它（告知编译器这里需要解释成类型而不是其他什么东西）请注意，auto类型的初始化总是会退化（也就是说他不会自动推导引用）。这也适用于以下情况的返回值返回类型只是auto。auto作为返回类型的行为与以下代码中的行为相同，其中由i的衰变类型声明int：

```
int i=42；
int const&ir=i；//ir指的是i
auto a=ir；//a被声明为int类型的新对象
```

​	或者，就是使用`std::commmon_type`这种东西完成多个类型的返回推导。

```c
#include <type_traits>
template<typename T1, typename T2>
std::common_type_t<T1,T2> max (T1 a, T2 b)
{
	return b < a ? a : b;
}
```

​	当然在C++11的地方使用的较为繁琐：

```c++
typename std::common_type<T1, T2>::type max (T1 a, T2 b)
{
	return b < a ? a : b;
}
```

​	我们还可以指定默认的模板参数

​	类模板在为多个默认模板参数声明指定默认值时，必须遵照“从右往左”的规则进行指定。而这个规则对函数模板来说并不是必须的。示例如下：

```
template <typename T1, typename T2 = int>
class DefClass1 {};

template <typename T1 = int, typename T2>
class DefClass2 {};  // ERROR: 无法通过编译：因为模板参数的默认值没有遵循“由右往左”的规则

template <typename T, int i = 0>
class DefClass3 {};
 
template <int i = 0, typename T>
class DefClass4 {};  // ERROR: 无法通过编译：因为模板参数的默认值没有遵循“由右往左”的规则

template <typename T1 = int, typename T2>
void DefFunc1(T1 a, T2 b) {}; // OK 函数模板不用遵循“由右往左”的规则

template <int i = 0, typename T>
void DefFunc2(T a) {};  // OK 函数模板不用遵循“由右往左”的规则
```

​	可以看到，不按照从右往左定义默认类模板参数的模板类DefClass2和DefClass4都无法通过编译。而对于函数模板来说，默认模板参数的位置则比较随意。DefFunc1和DefFunc2都为第一个模板参数定义了默认参数，而第二个模板参数的默认值并没有定义，C++11编译器却认为没有问题。函数模板的参数推导规则也并不复杂。简单地讲：如果能够从函数实参中推导出类型的话，那么默认模板参数就不会被使用，反之，默认模板参数则可能会被使用。

```
 1 template <class T, class U = double>
 2 void f(T t = 0, U u = 0) {};
 3 void g() 
 4 {
 5     f(1, 'c'); // f<int, char>(1, 'c') 
 6     f(1);      // f<int, double>(1, 0), 使用了默认模板参数double
 7     f();       // 错误: T无法被推导出来
 8     f<int>();  // f<int, double>(0, 0), 使用了默认模板参数double
 9     f<int, char>(); // f<int, char>(0, 0)
10 }
```

定义了一个函数模板f，f同时使用了默认模板参数和默认函数参数。可以看到，由于函数的模板参数可以由函数的实参推导而出:在f(1)这个函数调用中，实例化出了模板函数的调用应该为f<int, double>(1, 0)，其中，第二个类型参数U使用了默认的模板类型参数double，而函数实参则为默认值0。类似地，`f<int>()`实例化出的模板函数第二参数类型为double，值为0。而表达式f()由于第一类型参数T的无法推导，从而导致了编译的失败。而通过这个例子也可以看到，默认模板参数通常是需要跟默认函数参数一起使用的。还有一点应该注意：**模板函数的默认形参值不是模板参数推导的依据。函数模板参数的选择，终究是由函数的实参推导而来的。**

​	但是最好的办法还是让编译器进行推导即可。

​	函数模板也可以重载！

```c++
// maximum of two int values:
int max (int a, int b)
{
	return b < a ? a : b;
}
// maximum of two values of any type:
template<typename T>
T max (T a, T b)
{
	return b < a ? a : b;
}
int main()
{
	::max(7, 42); // calls the nontemplate for two ints
	::max(7.0, 42.0); // calls max<double> (by argument deduction)
	::max(’a’, ’b’); // calls max<char> (by argument deduction)
	::max<>(7, 42); // calls max<int> (by argument deduction)
	::max<double>(7, 42); // calls max<double> (no argument deduction)
	::max(’a’, 42.7); // calls the nontemplate for two ints
}
```

​	注意：只有在模板可以产生更好的匹配代码的时候，我们才去选择模板产生的代码，否则就会选择那些非模板参数的函数。以及，不要尝试调用可以匹配多个重载函数的函数：否则会调错误。

​	书写函数模板需要考虑到引用等问题：举个例子

```c++
#include <cstring>
// maximum of two values of any type (call-by-reference)
template<typename T>
T const& max (T const& a, T const& b)
{
	return b < a ? a : b;
}
// maximum of two C-strings (call-by-value)
char const* max (char const* a, char const* b)
{
	return std::strcmp(b,a) < 0 ? a : b;
}
// maximum of three values of any type (call-by-reference)
template<typename T>
T const& max (T const& a, T const& b, T const& c)
{
	return max (max(a,b), c); // error if max(a,b) uses call-by-value
}
int main ()
{
	auto m1 = ::max(7, 42, 68); // OK
	char const* s1 = "frederic";
	char const* s2 = "anica";
	char const* s3 = "lucas";
	auto m2 = ::max(s1, s2, s3); // run-time ERROR
}
```

​	请注意这段代码存在悬空引用：在我们调用最后一行话的时候，我们实际上走的是复制值的部分，而值在函数体结束之后就会销毁，返回一个已经销毁了的对象从来不是什么一个好的事情。

​	函数的模板匹配具有先后性，他总是会匹配第一个可以匹配的模板函数。所以如果我们希望使用的函数可以被优先考虑，那就先于一些也可以被匹配的函数进行声明：

```c++
#include <iostream>
// maximum of two values of any type:
template<typename T>
T max (T a, T b)
{
	std::cout << "max<T>() \n";
	return b < a ? a : b;
}
// maximum of three values of any type:
template<typename T>
T max (T a, T b, T c)
{
	return max (max(a,b), c); // uses the template version even for ints
} 
// because the following declaration comes too late:

// maximum of two int values:
int max (int a, int b)
{
	std::cout << "max(int,int) \n";
	return b < a ? a : b;
}

int main()
{
	::max(47,11,33); // OOPS: uses max<T>() instead of max(int,int)
}
```

### 题外话

​	您可能会想，为什么我们通常会声明函数来按值传递参数使用引用。一般来说，对于廉价以外的类型，建议通过引用传递简单类型（如基本类型或std:：string_view），因为没有不必要的副本创建。

​	然而，出于以下几个原因，传递价值通常更好些：

>语法很简单。
>
>编译器优化效果更佳。
>
>移动语义通常会使副本变得便宜。
>
>有时根本无法复制或移动。

​	此外，对于模板，还将发挥特定方面的作用：模板可能会被用于简单类型和复杂类型，因此选择复杂类型可能会对简单类型产生反作用。作为调用者，您通常仍然可以决定通过引用传递参数，使用std::ref（）和std::cref（）

​	我们还需要考虑的是——还有原始指针以及原始字符串的问题：传递他们的值可能会导致一些很大的问题

### 为什么不使用内联？

​	通常，函数模板不必使用内联来声明。不同于普通的函数，我们可以在头文件中定义非线性函数模板，并将此头文件包含在多个翻译单元。

​	此规则的唯一例外是特定类型的模板的完全专业化，因此生成的代码不再是通用的（定义了所有模板参数）。从严格的语言定义角度来看，内联仅意味着函数的定义可以在程序中多次出现。然而，它也意味着对调用的编译器的提示该函数应该“内联扩展”：这样做可以为某些函数生成更高效的代码在许多其他情况下，这也会降低代码的效率。如今，编译器通常更善于在没有内联关键字暗示的情况下决定这一点。然而，编译器仍然解释内联在该决策中的存在。（不需要你指定来优化了，现代编译器自己就会干）

## 类模版

我们首先来了解一下类模版，在STL容器当中大量的使用模版，这是很容易遇见的，毕竟我们的容器需要存储不同类型的对象

```c++
template<typename T>
class Stack{
    private:
        std::vector<T> elems;
}
```

如你所见，只需要我们在类的开头简单的声明一下模版，这个类就成为一个模版类。在外面我们实现类成员函数的时候：

```c++
template<typename T>
bool operator==(Stack<T> const& T1, Stack<T> const& T2){…}
```

我们还是要求在外面声明一下模版之后在写函数的签名和实现。使用他们也是简单的。我们跟函数模版类似，需要在使用这个容器的时候带上实例化的类型。需要注意到的只有使用到的模版才会实例化，这个重要的特性将会伴随我们学习模版的旅途。
特别的，如果我们的模版类声明太过冗长，可以使用using大法

```c++
using IntStack = Stack<int>;
IntStack st1; 
Stack<int> st2; // They are the same!
```

模版的特性让我们的实现需要顾及很多中情况：这时因为他只是会在实例化的时候才会知道类型，所以当在模版里使用一些类型并不支持的运算符的时候，它才会报错：

```c++
template<typename T>
class Stack{
    …
    void printOn(std::ostream& strm) const{
        for(T const& elem : elems)
            strm << elem << ‘ ’;
    }
}

…
Stack<std::pair<int, int>> ps; // pairs in C++ don’t support cout
ps.push({4, 5});
ps.push({6, 7});
// Only when you write the code ps.printOn, the code turns unrunnable
// ps.printOn(std::cout); // Error
```

使用Friends来支持更加好的流式输出，毕竟我们不希望在输出的时候还要专门留一行给stack的输出。所以，我们就使用一个早就有的重载技术，注意到为了给全局的<<进行重载以及外部调用，我们需要添加一个friend修饰符。

```c++
template<typename T>
class Stack
{
    void printOn(std::ostream& os);
    friend std::ostream& operator<< (std::ostream& strm
                                    Stack<T> const& s){
        s.printOn(strm);
        return strm;                                
    }
}
```

对于类模版内部如果我们的函数用到了不同于Stack的类型，我们就需要在函数签名的上方再声明一次

```c++
template<typename T>
class Stack{
    …
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, Stack<U> const& s);
}
```

## 非类型模板参数

​	模板参数可分为类型形参和非类型形参。
​	类型形参： 出现在模板参数列表中，跟在class或typename关键字之后的参数类型名称。
​	非类型形参： 用一个常量作为类（函数）模板的一个参数，在类（函数）模板中可将该参数当成常量来使用。

​	例如，我们要实现一个静态数组的类，就需要用到非类型模板参数。

```c++
template<class T, size_t N> //N：非类型模板参数
class StaticArray
{
public:
	size_t arraysize()
	{
		return N;
	}
private:
	T _array[N]; //利用非类型模板参数指定静态数组的大小
};
```


​	使用非类型模板参数后，我们就可以在实例化对象的时候指定所要创建的静态数组的大小了。

```c++
int main()
{
	StaticArray<int, 10> a1; //定义一个大小为10的静态数组
	cout << a1.arraysize() << endl; //10
	StaticArray<int, 100> a2; //定义一个大小为100的静态数组
	cout << a2.arraysize() << endl; //100
	return 0;
}
```

注意：

非类型模板参数只允许使用整型家族，浮点数、类对象以及字符串是不允许作为非类型模板参数的。
非类型的模板参数在编译期就需要确认结果，因为编译器在编译阶段就需要根据传入的非类型模板参数生成对应的类或函数。

**使用 auto 推断非类型模板参数**

从 c++17 起，可以使用 auto 推断非类型模板参数：

```cpp
template <auto value> void f() { }

f<10>();               // deduces int
```

如果没有 auto，想将非类型模板参数的类型也当做模板参数，那么必须声明两个模板参数：

```cpp
template <typename Type, Type value> constexpr Type TConstant = value;

constexpr auto const MySuperConst = TConstant<int, 100>;
```

从 c++17 开始，只需要一个 auto 即可：

```cpp
template <auto value> constexpr auto TConstant = value;

constexpr auto const MySuperConst = TConstant <100>;
```

在 auto 推导的的情况下获取类型：

```cpp
template<auto Val, typename T = decltype(Val)>
T foo();
```

或者:

```cpp
template<auto Val> struct Value {
   using ArgType = decltype(Val);
};
```

`template<decltype(auto) N>`也是可以的，这里 N 会被推断成引用类型：

```cpp
template<decltype(auto) N>
class C {
...
};
int i;
C<(i)> x;      // N is int&
```

​	举一个例子：

```c++
#include <iostream>
template<auto T> // take value of any possible nontype parameter (since C++17)
class Message {
public:
	void print() {
		std::cout << T << ’\n’;
	}
};
int main()
{
	Message<42> msg1;
	msg1.print(); // initialize with int 42 and print that value
	static char const s[] = "hello";
	Message<s> msg2; // initialize with char const[6] "hello"
	msg2.print(); // and print that value
}
```

## 可变参数模板

### **可变参数模板的基础原理**

C++的可变参数模板是怎么做到不需要告诉参数个数，也不需要告诉参数类型的呢？

1. **函数重载，依靠参数的pattern去匹配对应的函数；**
2. **函数模板，依靠调用时传递的参数自动推导出模板参数的类型；**
3. **类模板，基于partial specialization来选择不同的实现；**

**1，基础语法和例子说明**

可变参数模板的关键字沿用了C语言的ellipsis（...)，并且在3种地方进行了使用：

```cpp
#include <iostream>
void print ()
{
}
template<typename T, typename... Types>
void print (T firstArg, Types... args)
{
	std::cout << firstArg << ’\n’; // print first argument
	print(args...); // call print() for remaining arguments
}
```

1. typename... Types，这是**template parameter pack**，表明这里有多种type；
2. Types... args，这是**function parameter pack**，表明这里有多个参数；
3. args...，这是**pack expansion**，将参数名字展开为逗号分割的参数列表；

**3，sizeof...操作符和一些“勇敢但错误”的想法**

C++11引入了sizeof...操作符，可以得到可变参数的个数（注意sizeof...的参数只能是parameter pack，不能是其它类型的参数），如下所示：

```text
std::cout<<"DEBUG: "<<sizeof...(Ts)<<" | "<<sizeof...(arg_left)<<std::endl;
```

这样可以打印出parameter的个数。那下面这个代码就正确吗？

```c++
template<typename T, typename... Types>
void print (T firstArg, Types... args)
{
	std::cout << firstArg << ’\n’;
	if (sizeof...(args) > 0) { // error if sizeof...(args)==0
	print(args...); // and no print() for no 		arguments declared
}
```

​	错误的，这是因为if只在running-time的时候进行判断，但是我们的代码是在编译器就需要找好的，我们仍然没有找到`print()`，所以：

**4，C++17的if constexpr表达式和梦想实现**

C++17中引入了编译期if表达式（if constexpr），可以用来完美的解决这个问题：

```c++
template<typename T, typename... Ts>
void print(T arg1, Ts... arg_left){
    std::cout<<arg1<<", ";
    if constexpr(sizeof...(arg_left) > 0){
        print(arg_left...);
    }
}

```



### **Fold表达式（C++17的feature）**

C++17中引入了Fold表达式，如下所示：

```text
template<typename... T>
auto sum(T... s){
    return (... + s);
}
int main(int argc, char** argv)
{
   	sum(1,2,3);
}
```

当binary operator和parameter pack结合起来后，可以自动循环执行计算。像上述的... + s展开后，就相当于( (1 + 2) + 3)。Fold表达式有如下四种形式：

1. (... op pack)，相当于((( pack1 op pack2 ) op pack3 ) ... op packN)
2. (pack op ... )，相当于(pack1 op ( ... ( packN-1 op packN)))
3. (init op ... op pack)，相当于((( init op pack1) op pack2) ... op packN)
4. (pack op ... op init),相当于(pack1 op ( ... (packN op init)))

这里的op几乎是所有的binary operator都可以，不止是加减乘除，甚至是 指针操作，甚至是<<.

### **Variadic Indices（可变参数索引）**

索引操作也可以和可变参数语法结合起来：

```text
template<typename C, typename... Idx>
auto testVariadicIndices(const C& c, Idx... idx){
    print(c[idx]...);
}
int main(int argc, char** argv)
{
    std::vector<std::string> vec{"a","b","c","d","e"};
    testVariadicIndices(vec,0,3,4);
}
```

注意这个语法：print(c[idx]...)，程序会打印出【a, d, e,】。你也可以使用nontype模板参数来改造下上面的程序：

```text
template< int... idx, typename C>
auto testVariadicIndices(const C& c){
    syszuxPrint(c[idx]...);
}
int main(int argc, char** argv)
{
    std::vector<std::string> vec{"gemfield","is","a","civilnet","maintainer"};
    testVariadicIndices<0,3,4>(vec);
}
```

### **Variadic Class Templates (可变参数类模板)**

​	可变参数模板可以同样作用到类模板上。一个重要的例子就是Tuple：

```text
template<typename... Elements>
class Tuple;
......
Tuple<int, std::string, char> t;
```

​	现在就可以保存integer、string、character类型的数据。

### **Variadic 3Base Blasses（可变参数基类）**

这个名字就很直截了当了，在类的继承体系中，基类也可以是可变参数，如下所示：

```c++
#include <string>
#include <unordered_set>
class Customer
{
private:
	std::string name;
public:
	Customer(std::string const& n) : name(n) { }
	std::string getName() const { return name; }
};
struct CustomerEq {
bool operator() (Customer const& c1, Customer const& c2) const {
	return c1.getName() == c2.getName();
}
};
struct CustomerHash {
std::size_t operator() (Customer const& c) const {
	return std::hash<std::string>()(c.getName());
}
};
// define class that combines operator() for variadic base classes:
template<typename... Bases>
struct Overloader : Bases...
{
	using Bases::operator()...; // OK since C++17
};
int main()
{
// combine hasher and equality for customers in one type:
using CustomerOP = Overloader<CustomerHash,CustomerEq>;
std::unordered_set<Customer,CustomerHash,CustomerEq> coll1;
std::unordered_set<Customer,CustomerOP,CustomerOP> coll2;
...
}
```

​	注意上述代码中的public Bases... 语法，基类处出现了可变参数。

# C++ Templates

## 基本的概念

​	我们介绍完上面那些常见的模板使用方法之后，我们来探讨下其他也同样值得我们细究的东西

### Typename关键字

​	Identifier!这就是Typename的作用：声明我们的Token是一个类型而不是什么其他的东西。

​	一个简单的例子就是

```c++
template<typename T>
class MyClass
{
public:
    void foo(){
        typename T::SubType* ptr;
    }
}
```

​	我们在这里强掉T::SubType是一个类型而不是类T的静态成员SubType的什么东西！也就是说`typename`的作用就是为了消除歧义的

### 非初始化的声明`(Zero Initialization)`

​	也就是说，我们在作用域内声明了变量却不进行初始化：

```c++
void doSome()
{
	int x;
    int* ptr;
}
```

​	我们都知道，这样只是向计算机申请了若干的内存但是没有写值，读取得到的结果也就必然是垃圾值了。

​	在模板编程里，我们要高度警惕：

```c++
template<typename T>
void foo()
{
	T t;
}
```

​	对于那些可以被默认初始化的类而言，这都没什么。但是如果我们这里传递的是默认类型，我们读取的结果也就是垃圾值了，为此，我们需要请出统一初始化：

```c++
template<typename T>
void foo()
{
	T t{};
}
```

### 在类树下明确调用的是哪一级的成员

​	在一些场景中，我们需要明确的指出在类的继承树上调用的是啥

```c++
template<typename T>
class Base
{
public:
    void bar(); 
}
template<typename T>
class Derived : Base<T>{
public:
	void foo(){
        bar();	// Error! Or calls the external ::bar()
    }
}
```

​	一个良好的办法是使用`this->bar`，如果想要调用的是父类的方法的话那么：

```
Base<T>::bar();
```

```c++
#include <iostream>
template<typename T>
class ShowSthBase {
public:
	void show() {
		std::cout << "Show the type from Base Level:> " << typeid(T).name();
	}
};

template<typename T>
class ShowSthDerived : public ShowSthBase<T>{
public:
	void showSpecial() {
		ShowSthBase<T>::show();
	}
};

int main()
{
	ShowSthDerived<int> s;
	s.showSpecial();
}
```

### 面向原始数组和字符串字面量的模板

​	他们是一个大问题！我们的原始数组或者是字符串字面量传进去的时候，如果我们没有经过特殊的重载，那么，他们将退化为指针。有时候我们希望他们可以不要丢失数组的长度信息，办法是：

```c++
#include <iostream>
template<typename T, int N, int M>
void processAsArray(T(&a)[N], T(&b)[M]) // As T[N]&
{
    std::cout << "Type T is initialized as> " << typeid(T).name() << "\n";
    std::cout << "Array Length: N = " << N << " M = " << M << "\n";
}

int main()
{
    processAsArray("Hello!", "Charliechen!");
}
```

​	或者，你只是希望处理一种情况，那么，使用偏特化也行。

​	让我们来看一看情况是如何的：

```c++
#include <iostream>
template<typename T>
struct MyClass; // primary template

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]> // partial specialization for arrays of known bounds
{
	static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]> // partial spec. for references to arrays of known bounds
{
	static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template<typename T>
struct MyClass<T[]> // partial specialization for arrays of unknown bounds
{
	static void print() { std::cout << "print() for T[]\n"; }
};

template<typename T>
struct MyClass<T(&)[]> // partial spec. for references to arrays of unknown bounds
{
	static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
struct MyClass<T*> // partial specialization for pointers
{
	static void print() { std::cout << "print() for T*\n"; }
};

template<typename T1, typename T2, typename T3>
void foo(int a1[7], int a2[], // pointers by language rules
	int(&a3)[42], // reference to array of known bound
	int(&x0)[], // reference to array of unknown bound
	T1 x1, // passing by value decays
	T2& x2, T3&& x3) // passing by reference
{
	MyClass<decltype(a1)>::print(); // uses MyClass<T*>
	MyClass<decltype(a2)>::print(); // uses MyClass<T*>
	MyClass<decltype(a3)>::print(); // uses MyClass<T(&)[SZ]>
	MyClass<decltype(x0)>::print(); // uses MyClass<T(&)[]>
	MyClass<decltype(x1)>::print(); // uses MyClass<T*>
	MyClass<decltype(x2)>::print(); // uses MyClass<T(&)[]>
	MyClass<decltype(x3)>::print(); // uses MyClass<T(&)[]>
}

int main()
{
	int a[42];
	MyClass<decltype(a)>::print(); // uses MyClass<T[SZ]>
	extern int x[]; // forward declare array
	MyClass<decltype(x)>::print(); // uses MyClass<T[]>
	foo(a, a, a, x, x, x, x);
}

int x[] = { 0, 8, 15 }; // define forward-declared array
```

```
print() for T[42]
print() for T[]
print() for T*
print() for T*
print() for T(&)[42]
print() for T(&)[]
print() for T*
print() for T(&)[]
print() for T(&)[]
```

​	对于一个类，我们也可以在类内继续声明和使用模板！同样的骂它也可以用进行一定的便特化！只需要指定具体的类型即可

```C++
template<typename SomeType>
class SomeClass
{
	public:
    	template<typename Other>
    	Other T;
}
```

### 变量模板	

​	在C++14之前，我们可以使用模板来定义类型和函数，但是对于变量，我们只能在模板类或模板函数中定义它们。这在某些情况下可能会导致代码的冗余和复杂性。例如，如果我们想为每种类型定义一个常量，我们可能需要定义一个模板类，然后在这个类中定义这个常量。这不仅使代码变得冗余，而且也使得使用这个常量变得不直观。

​	为了解决这个问题，C++14引入了变量模板。变量模板允许我们直接定义模板变量，而不需要包装在模板类或模板函数中。这使得我们可以更加直观和简洁地定义和使用模板变量。

​	变量模板的引入，极大地提高了C++的表达能力，使得我们可以更加简洁、直观地编写泛型代码。它在许多领域都有着广泛的应用，例如在数学计算、数据结构设计、模板库开发等领域，都能看到它的身影。


```
// 定义一个变量模板
template<typename T>
constexpr T pi = T(3.1415926535897932385);

// 使用变量模板
double circumference(double radius) {
    return 2 * pi<double> * radius;
}
```

## 移动语义与enable_if<>

### 完美转发

​	啥是完美转发呢？很简单

- 那些可以被修改的对象在传递的过程中还是可以被修改
- 那些不变的read-only的对象在传递的过程中还是read-only
- 那些可以被移动的对象在传递的过程中还是可以按照被移动的方式进行传递

```C++
#include <utility>
#include <iostream>
class X {
	...
};
void g (X&) {
	std::cout << "g() for variable\n";
}
void g (X const&) {
	std::cout << "g() for constant\n";
}
void g (X&&) {
	std::cout << "g() for movable object\n";
}
// let f() forward argument val to g():
void f (X& val) {
	g(val); // val is non-const lvalue => calls g(X&)
}
void f (X const& val) {
	g(val); // val is const lvalue => calls g(X const&)
}
void f (X&& val) {
	g(std::move(val)); // val is non-const lvalue => needs std::move() to call g(X&&)
}
int main()
{
	X v; // create variable
	X const c; // create constant
	f(v); // f() for nonconstant object calls f(X&) => calls g(X&)
	f(c); // f() for constant object calls f(X const&) => calls g(X const&)
	f(X()); // f() for temporary calls f(X&&) => calls g(X&&)
	f(std::move(v)); // f() for movable variable calls f(X&&) => calls g(X&&)
}
```

​	这里我们看到了，我们的对象被移动只是因为我们调用了std:::move，具体的移动语义没有被传递下去。这个时候，只需要使用std::forward就好了：

```c++
#include <utility>
#include <iostream>
class X {
	...
};
void g (X&) {
	std::cout << "g() for variable\n";
}
void g (X const&) {
	std::cout << "g() for constant\n";
}
void g (X&&) {
	std::cout << "g() for movable object\n";
}
// let f() perfect forward argument val to g():
template<typename T>
void f (T&& val) {
	g(std::forward<T>(val)); // call the right g() for any passed argument val
}
int main()
{
	X v; // create variable
	X const c; // create constant
	f(v); // f() for variable calls f(X&) => calls g(X&)
	f(c); // f() for constant calls f(X const&) 	=> calls g(X const&)
	f(X()); // f() for temporary calls f(X&&) => calls g(X&&)
	f(std::move(v)); // f() for move-enabled variable calls f(X&&) => calls g(X&&)
}
```

### **使用enable_if<>禁用模板**

```cpp
template<typename T>
typename std::enable_if<(sizeof(T) > 4)>::type
foo() {
}
```

当`sizeof(T) > 4`为False时，该模板就会被忽略。如果`sizeof(T) > 4`为true时，那么该模板会被扩展为：

```cpp
void foo() {
}
```

std::enable_if<>是一种类型萃取（type trait），会根据给定的一个编译时期的表达式（第一个参数）来确定其行为：

- 如果这个表达式为true，`std::enable_if<>::type`会返回：
  - 如果没有第二个模板参数，返回类型是void。
  - 否则，返回类型是其第二个参数的类型。
- 
- 如果表达式结果false，`std::enable_if<>::type`不会被定义。根据下面会介绍的SFINAE(substitute failure is not an error)， 这会导致包含std::enable_if<>的模板被忽略掉。

给std::enable_if<>传递第二个参数的例子：

```cpp
template<typename T>
std::enable_if_t<(sizeof(T) > 4), T>
foo() {
return T();
}
```

如果表达式为真，那么模板会被扩展为：

```cpp
MyType foo();
```

如果你觉得将enable_if<>放在声明中有点丑陋的话，通常的做法是：

```cpp
template<typename T,
typename = std::enable_if_t<(sizeof(T) > 4)>>
void foo() {
}
```

当`sizeof(T) > 4`时，这会被扩展为：

```cpp
template<typename T,
typename = void>
void foo() {
}
```

还有种比较常见的做法是配合using：

```cpp
template<typename T>
using EnableIfSizeGreater4 = std::enable_if_t<(sizeof(T) > 4)>;

template<typename T,
typename = EnableIfSizeGreater4<T>>
void foo() {
}
```

### **enable3_if<>实例**

我们使用enable_if<>来解决引子中的问题：

```cpp
template <typename T>
using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

class Person {
private:
  std::string name;

public:
  // generic constructor for passed initial name:
  template <typename STR, typename = EnableIfString<STR>>
  explicit Person(STR &&n) : name(std::forward<STR>(n)) {
    std::cout << "TMPL-CONSTR for '" << name << "'\n";
  }

  // copy and move constructor:
  Person(Person const &p) : name(p.name) {
    std::cout << "COPY-CONSTR Person '" << name << "'\n";
  }
  Person(Person &&p) : name(std::move(p.name)) {
    std::cout << "MOVE-CONSTR Person '" << name << "'\n";
  }
};
```

核心点：

- 使用using来简化std::enable_if<>在成员模板函数中的写法。
- 当构造函数的参数不能转换为string时，禁用该函数。

所以下面的调用会按照预期方式执行：

```cpp
int main() {
  std::string s = "sname";
  Person p1(s);          // init with string object => calls TMPL-CONSTR
  Person p2("tmp");      // init with string literal => calls TMPL-CONSTR
  Person p3(p1);          // OK => calls COPY-CONSTR
  Person p4(std::move(p1));       // OK => calls MOVE-CONST
}
```

注意在不同版本中的写法：

- C++17 : `using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>`
- C++14 : `using EnableIfString = std::enable_if_t<std::is_convertible<T, std::string>::value>`
- C++11 : `using EnableIfString = typename std::enable_if<std::is_convertible<T, std::string>::value>::type`

### **使用Concepts简化enable_if<>**

如果你还是觉得enable_if<>不够直观，那么可以使用之前文章提到过的C++20引入的Concept.

```cpp
template<typename STR>
requires std::is_convertible_v<STR,std::string>
Person(STR&& n) : name(std::forward<STR>(n)) {
...
}
```

我们也可以将条件定义为通用的Concept:

```cpp
template<typename T>
concept ConvertibleToString = std::is_convertible_v<T,std::string>;

...
template<typename STR>
requires ConvertibleToString<STR>
Person(STR&& n) : name(std::forward<STR>(n)) {
...
}
```

甚至可以改为：

```cpp
template<ConvertibleToString STR>
Person(STR&& n) : name(std::forward<STR>(n)) {
...
}
```

### **SFINAE (Substitution Failure Is Not An Error)**

在C++中针对不同参数类型做函数重载时很常见的。编译器需要为一个调用选择一个最适合的函数。

当这些重载函数包含模板函数时，编译器一般会执行如下步骤：

- 确定模板参数类型。
- 将函数参数列表和返回值的模板参数替换掉（substitute）
- 根据规则决定哪一个函数最匹配。

但是替换的结果可能是毫无意义的。这时，编译器不会报错，反而会忽略这个函数模板。

我们将这个原则叫做：SFINAE（“substitution failure is not an error）

但是替换(substitute)和实例化(instantiation)不一样：即使最终不需要被实例化的模板也要进行替换（不然就无法执行上面的第3步）。不过它只会替换直接出现在函数声明中的相关内容（不包含函数体）。

考虑下面的例子：

```cpp
// number of elements in a raw array:
template <typename T, unsigned N> 
std::size_t len(T (&)[N]) { 
  return N; 
}

// number of elements for a type having size_type:
template <typename T> 
typename T::size_type len(T const &t) { 
  return t.size(); 
}
```

当传递一个数组或者字符串时，只有第一个函数模板匹配，因为`T::size_type`导致第二个模板函数会被忽略：

```cpp
int a[10];
std::cout << len(a);        // OK: only len() for array matches
std::cout << len("tmp");      // OK: only len() for array matches
```

同理，传递一个vector会只有第二个函数模板匹配：

```cpp
std::vector<int> v;
std::cout << len(v);    // OK: only len() for a type with size_type matches
```

注意，这与传递一个对象，有size_type成员，但是没有size()成员函数不同。例如：

```cpp
std::allocator<int> x;
std::cout << len(x);     // ERROR: len() function found, but can’t size()
```

编译器会根据SFINAE原则匹配到第二个函数，但是编译器会报找不到`std::allocator<int>`的size()成员函数。在匹配过程中不会忽略第二个函数，而是在实例化的过程中报错。

**而使用enable_if<>就是实现SFINAE最直接的方式。**

#### **SFINAE with decltype**

有的时候想要为模板定义一个合适的表达式是比较难得。

比如上面的例子，假如参数有size_type成员但是没有size成员函数，那么就忽略该模板。之前的定义为：

```cpp
template<typename T>
typename T::size_type len (T const& t) {
    return t.size();
}


std::allocator<int> x;
std::cout << len(x) << '\n';       // ERROR: len() selected, but x has no size()
```

这么定义会导致编译器选择该函数但是会在instantiation阶段报错。

处理这种情况一般会这么做：

- 通过`trailing return type`来指定返回类型 (auto -> decltype)
- 将所有需要成立的表达式放在逗号运算符的前面。
- 在逗号运算符的最后定义一个类型为返回类型的对象。

比如：

```cpp
template<typename T>
auto len (T const& t) -> decltype( (void)(t.size()), T::size_type() ) {
    return t.size();
}
```

这里，decltype的参数是一个逗号表达式，所以最后的`T::size_type()`为函数的返回值类型。逗号前面的`(void)(t.size())`必须成立才可以。

## 值传递还是引用传递

​	值传递分为

> 1. X const&（常引用传递）
> 2. X& 普通引用传递
> 3. X&& 万能引用：标志着可以移动所属权

​	值传递还是引用传递？这个原则很早就说过，除非

> 1. 无法拷贝
> 2. 参数使用来返回函数内部结果的
> 3. 使用的模板只是继续传递变量所拥有的属性
> 4. 存在巨大的性能提升

​	在现代C++中，如果我们对右值实现拷贝，它实际上会执行的是移动语义（如果存在重载的移动，那么就会调用）

```
#include <iostream>

struct Buf
{
	Buf() {
		std::cout << "Create Buf\n";
	}
	Buf(const Buf& b) {
		std::cout << "Copy Buf\n";
	}

	Buf(const Buf&& p) {
		std::cout << "moving Buf\n";
	}

	~Buf()
	{
		std::cout << "Erase Buf\n";
	}
};

//template <typename T>
//void process(T arg)
//{
//	std::cout << "go the process(T arg), With value copying!\n";
//}

template <typename T>
void process(T&& arg)
{
	std::cout << "go the process(T arg), With value moving!\n";
}

int main()
{
	Buf p;
	std::cout << "P is created!\n";
	process(p);
}
```

​	可以尝试一下。

```c++
std::string returnString();
std::string s = "hi";
printV(s); // copy constructor
printV(std::string("hi")); // copying usually optimized away (if not, move constructor)
printV(returnString()); // copying usually optimized away (if not, move constructor)
printV(std::move(s)); // move constructor
```

​	值得一提的是

> 使用值传递会使得参数发生退化：比如说数组会退化成指针
>
> 但是使用引用传递则不会退化类型，还会被保留所有的信息

### std::ref和std::cref

C++11以后，对于函数模板实参，可以让调用者决定是传值还是传引用。当函数模板声明为值传递方式传递参数，调用者可以使用std::cref()和std::ref()来以引用方式传递参数，他们在头文件<functional>中声明。

```cpp
template<typename T>
void printT(T arg)
{...}

std::string s = "hello";
printT(s);  // pass by value
printT(std::cref(s));  // pass s "as if by reference"
```

然而，std::cref()并不改变模板中参数的处理，而是它使用了一个技巧：将传入的参数s进行包装，使得它表现得像一个引用。事实上，它创建了一个对象，类型为`std::reference_wrapper<>`，指向原来的实参并以值方式传递该对象。该包装或多或少只支持一个操作：隐式类型转化为原来的类型，得到原来的对象（可以在引用包装上调用get()方法，将它作为函数对象） 。因此，对于传入的对象，任何时候你想要一个有效的操作，可以使用reference wrapper代替：

```cpp
//basics/cref.cpp
#include <functional>
#include <string>
#include <iostream>

void printString(std::string const& s)
{
    std::cout << s << '\n';
} 

template<typename T>
void printT(T arg)
{
    printString(arg);  // might convert arg back to std::string
}

int main()
{
    std::string s = "hello";
    printT(s);   // print s passed by value;
    printT(std::cref(s));  // print s passed "as if by reference"
}
```

最后一个调用以值方式传递对象`std::reference_wrapper<std::string const>`给参数arg，然后进一步进行传递，然后将其转化为潜在的类型：std::string。

注意：编译器必须知道隐式转化为原来类型是必须的。出于这个原因，std::ref()和std::cref()通常只有在将对象通过泛型代码传递给非泛型函数时才能适用。比如，尝试直接输出泛型类型T的对象会失败，因为std::reference_wrapper<>没有输出运算：

```cpp
template<typename T>
void printV(T arg)
{
    std::cout << arg << '\n';
}
...
std::string s = "hello";
printV(s);  // OK
printV(std::cref(s)); // ERROR: no operator << for reference wrapper defined
```

以下方法也很会失败，因为不能比较reference wrapper和char const* 或者std::string：

```cpp
template<typename T1, typename T2>
bool isless(T1 arg1, T2 arg2)
{
    return arg1 < arg2;
}
...
std::string s = "hello";
if(isless(std::cref(s), "world")) ... // ERROR
if(isless(std::cref(s), std::string("world"))) ... // ERROR
```

给arg1和arg2一个通用类型T也不适用：

```cpp
template<typename T>
bool isless(T arg1, T arg2)
{
    return arg1 < arg2;
}
```

因为编译器当尝试从arg1和arg2中推断出T的类型会得到冲突类型。

​	因此，类`std::reference_wrapper<>`的效果使得“使用引用作为一流对象” ，你可以拷贝然后以值方式传递给函数模板。你也可以在类内部使用，比如在容器中保存指向对象的引用。但是你总是最终需要将其转化回潜在的类型

### 一些建议：

1. 默认情况下，将参数声明为按值传递。这样做比较简单，即使对字符串常量也可以正常工作。对于比较小的对象、临时对象以及可移动对象，其性能也还不错。对于比较大的
2. 将参数声明成按值传递：

​	这一方法很简单，它会对字符串常量和裸数组的类型进行退化，但是对比较大的对象可能会受影响性能。在这种情况下，调用者仍然可以通过 std::cref()和 std::ref()按引用传递参数，

但是要确保这一用法是有效的。

1. 将参数声明成按引用传递：对于比较大的对象这一方法能够提供比较好的性能。尤其是在下面几种情况下：

> 将已经存在的对象（lvalue）按照左值引用传递
>
> 将临时对象（prvalue）或者被 std::move()转换为可移动的对象（xvalue）按右值引用传递
>
> 或者是将以上几种类型的对象按照转发引用传递。

​	由于这几种情况下参数类型都不会退化，因此在传递字符串常量和裸数组时要格外小心。

​	对于转发引用，需要意识到模板参数可能会被隐式推断为引用类型（引用折叠）。 一般性建议

基于以上介绍，对于函数模板有如下建议：

1. 默认情况下，将参数声明为按值传递。这样做比较简单，即使对字符串常量也可以正常工作。对于比较小的对象、临时对象以及可移动对象，其性能也还不错。对于比较大的对象，为了避免成本高昂的拷贝，可以使用 std::ref()和 std::cref()。

2. 如果有充分的理由，也可以不这么做：

   > 1. 如果需要一个参数用于输出，或者即用于输入也用于输出，那么就将这个参数按非const 引用传递。
   > 2. 如果使用模板是为了转发它的参数，那么就使用完美转发（perfect forwarding）。也就是将参数声明为转发引用并在合适的地方使用 std::forward<>()。考虑使用std::decay<>或者 std::common_type<>来处理不同的字符串常量类型以及裸数组类型的情况。

3. 如果重点考虑程序性能，而参数拷贝的成本又很高，那么就使用 const 引用。不过如果最终还是要对对象进行局部拷贝的话，这一条建议不适用。

​	如果你更了解程序的情况，可以不遵循这些建议。但是请不要仅凭直觉对性能做评估。在这方面即使是程序专家也会犯错。真正可靠的是：测试结果。 

### 不要过分泛型化

值得注意的是，在实际应用中，函数模板通常并不是为了所有可能的类型定义的。而是有一定的限制。比如你可能已经知道函数模板的参数只会是某些类型的 vector。这时候最好不要将该函数模板定义的过于泛型化，否则，可能会有一些令人意外的副作用。针对这种情况应该使用如下的方式定义模板：

```
template<typename T>
void printVector (std::vector<T> const& v)
{ 
}
```

​	这里通过的参数 v，可以确保 T 不会是引用类型，因为 vector 不能用引用作为其元素类型。而且将 vector 类型的参数声明为按值传递不会有什么好处，因为按值传递一个 vector 的成本明显会比较高昂（vector 的拷贝构造函数会拷贝 vector 中的所有元素）。此处如果直接将参数 v 的类型声明为 T，就不容易从函数模板的声明上看出该使用那种传递方式了。 

## 编译时编程

​	模板的特性使得我们可以在编译期间就做很多的事情：

​	模板的实例化发生在编译期间（而动态语言的泛型是在程序运行期间决定的）。事实证明C++模板的某些特性可以和实例化过程相结合，这样就产生了一种 C++自己内部的原始递归的“编程语言”。因此模板可以用来“计算一个程序的结果”。

```c++
template<unsigned p, unsigned d> // p: number to check, d: current divisor
struct DoIsPrime {
	static constexpr bool value = (p%d != 0) && DoIsPrime<p,d-1>::value;
};
template<unsigned p> // end recursion if divisor is 2
struct DoIsPrime<p,2> {
	static constexpr bool value = (p%2 != 0);
};
template<unsigned p> // primary template
struct IsPrime {
// start recursion with divisor from p/2:
	static constexpr bool value = DoIsPrime<p,p/2>::value;
};
// special cases (to avoid endless recursion with template instantiation):
template<>
struct IsPrime<0> { static constexpr bool value = false; };
template<>
struct IsPrime<1> { static constexpr bool value = false; };
template<>
struct IsPrime<2> { static constexpr bool value = true; };
template<>
struct IsPrime<3> { static constexpr bool value = true; };
```

​	这就是一个例子，下面的偏特化的目的显然：就是为了防止无穷无尽的递归。

### 	constexpr

​	C++11 引入了一个叫做 constexpr 的新特性，它大大简化了各种类型的编译期计算。如果给定了合适的输入，constexpr 函数就可以在编译期间完成相应的计算。虽然 C++11 对 constexpr函数的使用有诸多限制（比如 constexpt 函数的定义通常都只能包含一个 return 语句），但是在 C++14 中这些限制中的大部分都被移除了。当然，为了能够成功地进行 constexpr 函数中的计算，依然要求各个计算步骤都能在编译期进行：目前堆内存分配和异常抛出都不被支持。

```c++
constexpr bool
doIsPrime (unsigned p, unsigned d) // p: number to check, d: current
divisor
{
	return d!=2 ? (p%d!=0) && doIsPrime(p,d-1) // check this and smaller divisors
: (p%2!=0); // end recursion if divisor is 2
}
constexpr bool isPrime (unsigned p)
{
	return p < 4 ? !(p<2) // handle special cases
	: doIsPrime(p,p/2); // start recursion with divisor from p/2
}
```

​	为了满足 C++11 中只能有一条语句的要求，此处只能使用条件运算符来进行条件选择。不过由于这个函数只用到了 C++的常规语法，因此它比第一版中，依赖于模板实例化的代码要容易理解的多。
​	在 C++14 中，constexpr 函数可以使用常规 C++代码中大部分的控制结构。因此为了判断一个数是不是质数，可以不再使用笨拙的模板方式（C++11 之前）以及略显神秘的单行代码方式（C++11），而直接使用一个简单的 for 循环：

```c++
constexpr bool isPrime (unsigned int p)
{
	for (unsigned int d=2; d<=p/2; ++d) {
		if (p % d == 0) {
			return false; // found divisor without remainder
		}
	}
	return p > 1; // no divisor without remainder found
}
```

​	在 C++11 和 C++14 中实现的 constexpr isPrime()，都可以通过直接调用：isPrime(9)来判断 9 是不是一个质数。但是上面所说的“可以”在编译期执行，并不是一定会在编译期执行。在需要编译期数值的上下文中（比如数组的长度和非类型模板参数），编译器会尝试在编译期对被调用的 constexpr 函数进行计算，此时如果无法在编译期进行计算，就会报错（因为此处必须要产生一个常量）。在其他上下文中，编译期可能会也可能不会尝试进行编译期计算，如果在编译期尝试了，但是现有条件不满足编译期计算的要求，那么也不会报错，相应的函数调用被推迟到运行期间执行。
比如：

```
constexpr bool b1 = isPrime(9); // evaluated at compile time
```

​	会在编译期进行计算（因为 b1 被 constexpr 修饰）。而对

```
const bool b2 = isPrime(9); // evaluated at compile time if in namespace scope
```

​	如果 b2 被定义于全局作用域或者 namespace 作用域，也会在编译期进行计算。如果 b2 被定义于块作用域（{}内），那么将由编译器决定是否在编译期间进行计算。下面这个例子就属于这种情况：

```
bool fiftySevenIsPrime() {
	return isPrime(57); // evaluated at compile or running time
}
```

​	此时是否进行编译期计算将由编译期决定。
另一方面，在如下调用中：

```
int x; …
std::cout << isPrime(x); // evaluated at run time
```

​	**不管 x 是不是质数，调用都只会在运行期间执行。**

### SFINAE (Substitution Failure Is Not An Error, 替换失败不是错误)

​	在 C++中，重载函数以支持不同类型的参数是很常规的操作。当编译器遇到一个重载函数的调用时，它必须分别考虑每一个重载版本，以选择其中类型最匹配的那一个在一个函数调用的备选方案中包含函数模板时，编译器首先要决定应该将什么样的模板参数用于各种模板方案，然后用这些参数替换函数模板的参数列表以及返回类型，最后评估替换后的函数模板和这个调用的匹配情况（就像常规函数一样）。

​	但是这一替换过程可能会遇到问题：替换产生的结果可能没有意义。不过这一类型的替换不会导致错误，C++语言规则要求忽略掉这一类型的替换结果。
​	这一原理被称为 SFINAE（发音类似 sfee-nay），代表的是“substitution failure is not an error”。
​	但是上面讲到的替换过程和实际的实例化过程不一样（参见 2.2 节）：即使对那些最终被证明不需要被实例化的模板也要进行替换（不然就无法知道到底需不需要实例化）。不过它只会替换直接出现在函数模板声明中的相关内容（不包含函数体）。

### 1.1 简介

C++提供了两种模板机制，**函数模板和类模板**。

1. 使用范围：**模板的声明或定义\**只能在全局或类范围进行\**，不能在局部范围（如函数）内进行**。
2. 使用目的：使用模板是为了能够让程序员**编写与类型无关的代码。

函数模板和模板函数区别**：函数模板是一个模板，其中用到通用类型参数，不能直接执行；模板函数是一个具体的函数，它是一个具体执行的函数，由编译系统在遇到具体函数调用时生成，可执行。

### 1.2 函数模板

#### 1.2.1 函数模板格式

```cpp
template <类型形参表或称模板参数列表>   //类型函数声明
返回类型 函数名（形参表） 
{
    函数体；
}
```

注意：

- template — 声明创建模板；
- 模板参数表：定义在类或函数定义中用到的类型或值。
- 类型形参表：可以包含基本数据类型，也可以包含类类型。类型形参**需要加class或typename**关键字（两者等价）
- T — 通用的数据类型，名称可以替换，通常为大写字母

类型形参表的参数必需是唯一的，不能有重名的。

template声明语句和函数模板声明之间不允许有其他语句。

举例：

```cpp
template<class T>
T square(T number)
{
    return number * number;
}
 
 
int y, x = 4;
y = square(x);
```

 该模板前缀以关键字 template 开始，接下来是一组尖括号，里面包含一个或多个在模板中使用的通用数据类型。通用数据类型以关键字 dass 开头，后面跟着代表数据类型的形参名称。



#### 1.2.2 函数模板实例化为模板函数

函数模板不能直接执行需要实例化为模板函数后才能执行。

编译系统发现有一个函数调用“函数名（实参表）”或“函数名<类型实参表>（实参表）”时，c++将根据“实参表”中的类型生成一个重载函数，即模板函数。

函数模板：

```cpp
template <class T>  //T 的名字也为其他
T abs(T x)
{
    if (x < 0) return -x;
    return x;
}
```

//调用函数模板生成模板函数

cout << abs(-1) << endl;//输出结果为1

 生成的模板函数如下：

```cpp
int abs(int x)
{ 
    if(x<0) 
        return -x;
    return x;
}
```

###  1.2.3 编译器自动推导模板参数类型

函数模板的默认模板参数在使用规则上和其他的默认参数也有一些不同，它没有必须写在参数表最后的限制。甚至于，根据实际场景中函数模板被调用的情形，编译器还可以自行推导出部分模板参数的类型。

```cpp
template <typename R = int, typename U>
R func(U val)
{
    return val;
}
int main()
{
    func(97);               // R=int, U=int
    func<char>(97);         // R=char, U=int
    func<double, int>(97);  // R=double, U=int
    return 0;
}
```

#### 1.2.4 函数模板注意

（1）自动类型推导，必须推导出一致的数据类型T，才可以使用；

```cpp
template<class T>
void myswap(T &a ,T &b)
{
	T temp=a;
	a=b;
	b=temp;
}
 
//1.自动类型推导，必须推导出一致的数据类型T，才可以使用
void test01()
{
	int a=10;
	int b=10;
	char c ='c';
	myswap(a,b); //正确，可以推导出一致T
	myswap(a,c); //错误，推到不出一致的T类型
}
```

 （2）模板必须确定出T的数据类型，才可以使用

```cpp
template <class T>
void func()
{
	cout<<"func调用"<<endl;
}
 
void main()
{
	//func(); 错误，模板不能独立使用，必须确定出T的类型
	func<int>(); //利用显示指定类型的方式，给T一个类型，才可以使用该模板
}
```

### 1.3 类模板

#### 1.3.1 简介

类模板允许用户为类定义一种模式，**使得类中的某些数据成员、成员函数的参数或成员函数的返回值能取任意类型**。类模板的成员函数被认为是函数模板。

#### 1.3.2 类模板格式

```cpp
template <类型形参表>   //类型参数声明
class 类名
{
 	类模板的代码
}
template<类型形参表> //定义在类模板之外的函数必需以关键字template开始
返回类型 类名 类型名表::成员函数n（形参表）
{
		成员函数定义体
}
```

####  1.3.3 实例化类模板

实例化类模板

类模板不能直接使用，**必需先实例化为相应的模板类**。定义类模板之后，创建模板类的格式如下：

类模板名 <类型实参表> 对象表；

类型实参表与类模板中的类型形参表相匹配。

举例：

```cpp
#include <iostream>
#include <string>
using namespace std;
template <class T1,class T2>
class Pair
{
public:
    T1 key;  //关键字
    T2 value;  //值
    Pair(T1 k,T2 v):key(k),value(v) { };
    bool operator < (const Pair<T1,T2> & p) const;
};
template<class T1,class T2>
bool Pair<T1,T2>::operator < (const Pair<T1,T2> & p) const
//Pair的成员函数 operator <
{ //"小"的意思就是关键字小
    return key < p.key;
}
int main()
{
    Pair<string,int> student("Tom",19); //实例化出一个类 Pair<string,int>
    cout << student.key << " " << student.value;
    return 0;
}
```



#### 1.3.4 类模板举例

```cpp
#include <iostream>
#include <map>
#include "string"
 
//#include <memory>
 
using namespace std;
template <typename T>
class Array  //类模板
{
	int size;
	T *p;
public:
	Array();//默认构造函数
	Array(int n);//重载构造函数
	T &operator[](int) const;//[]重载函数
};//默认构造函数
template <typename T>
Array<T>::Array()
{
	size = 10;
	p = new T[size];
}
 
//重载构造函数
template <typename T>
Array<T>::Array(int n)
{
	size = n;
	p = new T[size];
}
//下标运算符重载函数
template<typename T>
T &Array<T>::operator[](int i)const 
{
	if (i >= 0 && i < size)
	{
		return p[i];
	}
}class Student
{
	int no;
	char name[10];
public:
	Student() {}
	Student(int n,const char *s)//注意要有const 否则”Tom“无法传参
	{
		no = n;
		strcpy_s(name, s);//使用strcpy 为字符串数组赋值
	}
    Student &operator=(Student &s) //赋值重载构造函数
	{
		no = s.no;
		strcpy_s(name, s.name);
		return *this;
	}
void display()
	{
		cout << "学号：" << no << ",姓名：" << name << endl;
	}
};

int main()
{
	Array<int> a(5);
	for (int i=0;i<5;i++)
	{
		a[i]=i+1;//调用运算符重载函数
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "学生列表" << endl;
	Array<Student> b(3);
	//int c = 1;
	Student x(1, "Tom"), y(2, "Marry"), z(3, "John");
	b[0] = x; b[1] = y; b[2] = z;
	for (int i=0;i<3;i++)
	{
		b[i].display();
	}
}
```

 输出结果：

1 2 3 4 5

学生列表

学号： 1 ，姓名： Tom

学号： 2 ，姓名： Marry

学号： 3，姓名： John



####  1.3.5 类模板作为函数参数

```cpp
//类模板
 
template <class T>  //T 的名字也为其他
class A
{
	T x;
public:
	A(T a) { x = a; }
	T abs()
	{
		if (x < 0) return -x;
		else return x;
	}
};
//函数模板中模板类作为形参
 
template <class T>
void fun(A<T> x)
{
	cout << x.abs() << endl;
}
int main()
{
	//建立对象
	A<int> s1(-5);
	A<double> s2(-5.8);
	fun(s1);
	fun(s2);
 
}
 
```

输出结果：5 5.8

#### 1.3.6 函数模板作为类模板的成员

类模板中的成员函数还可以是一个函数模板。成员函数模板只有在被调用时才会被实例化。例如下面的程序

```cpp
#include <iostream>
using namespace std;
template <class T>
class A
{
public:
    template <class T2>
    void Func(T2 t) { cout << t; }  //成员函数模板
};
int main()
{
    A<int> a;
    a.Func('K');  //成员函数模板Func被实例化
    a.Func("hello");
    return 0;
}
```

####  1.3.7 类模板中也可以使用非类型参数，即值参数

```cpp
template<class T,int size>
class A
{
	.....
}
实例化：
A<int,3> s;
```

#### 1.3.8 模板与静态函数

类模板中定义静态函数，则该模板类的所有对象共享一个静态数据成员。

#### 1.3.9 类模板的友元函数

一个类模板中可以设计友元函数，友元函数的形参可以是类模板或类模板的引用。如果在类模板中设计与参数类型无关的友元函数，那么在类外面实现时也不能省略template类型参数声明，否则将其看成是一个普通全局函数。

```cpp
template <class T>  //T 的名字也为其他
class A
{
	
public:
	T x;
	A() {  }
	A(T i):x(i){  }
	friend void f1();//与参数类型无关的友元函数
	friend void f2(A<T> &);//与参数类型有关的友元函数
	
};
 
template<class T>
void f1(){ cout << "f1" << endl; }
template<class T>
void f2(A<T> &a) { cout << "f2:x " << a.x << endl; }
int main()
{
	A<double> a(1.2);
	f1<int>();//f1是模板类A<int>的友元函数
	f1<double>();//f1是模板类A<double>的友元函数
	f2<double>(a);//f2是模板类A<double>的友元函数
}
```

输出结果：

f1

f1

f2:x 1.2

### 1.3 可变参数模板

#### 1.3.1 可变参数模板的定义

在C++11之前，类模板和函数模板只能含有固定数量的模板参数。C++11增强了模板功能，允许模板定义中包含0到任意个模板参数，这就是可变参数模板。

- 可变参数模板，对参数进行了高度泛化，能表示任意个数，任意类型的参数
- 是一个**接受可变数目参数的模板函数或模板类**。可变数目的参数被称为**参数包**。

语法：可变参数模板和普通模板的语义是一样的，只是写法上稍有区别，声明可变参数模板时需要在`typename`或`class`后面带上省略号`...`：

```cpp
template <class... T>
void f(T... args);
```

- 声明一个参数包T... args，这个参数包中可以包含0到任意个模板参数； 

举例：

```cpp
#include <iostream>
#include <map>
 
//#include <memory>
 
using namespace std;
template <typename T,typename...Args>//foo是可变参数函数模板  有一个名为T的类型参数和一个名为Args的模板参数包
void foo(const T &t,const Args& ...rest)  //foo函数列表包含一个const&类型的参数 指向T的类型，名为rest的函数参数包
{
	cout << sizeof...(rest) << endl;//输出函数参数的数目
};
int main()
{
	int i = 0; double d = 3.14; string s = "hello";
	foo(i,s,42,d);//包中有三个参数
	foo(s, 42, d);//包中有两个参数
	foo(d, s);//包中有一个参数
	foo("hi");//空包
}
```

 输出结果：

3

2 

1 

0 

#### 1.3.2 可变参数模板的展开

把带省略号的参数称为“参数包”，它里面包含了0到N（N>=0）个模版参数。我们无法直接获取参数包args中的每个参数的，只能通过展开参数包的方式来获取参数包中的每个参数，这是使用可变模版参数的一个主要特点，也是最大的难点，即如何展开可变模版参数。

可变模版参数和普通的模版参数语义是一致的，所以可以应用于函数和类，即可变模版参数函数和可变模版参数类，然而，模版函数不支持偏特化，所以可变模版参数函数和可变模版参数类展开可变模版参数的方法还不尽相同，下面我们来分别看看他们展开可变模版参数的方法。

展开可变模板参数函数的方法一般有两种：一种是通过**递归函数来展开参数包**，另外一种是通过**逗号表达式来展开参数包**。

**（1）递归函数方式展开参数包**

通过递归函数展开参数包，需要提供一个参数包展开的函数和一个递归终止函数，递归终止函数正是用来终止递归的，

```cpp
#include <iostream>
using namespace std;
//递归终止函数
void print()
{
   cout << "empty" << endl;
}
//展开函数
template <class T, class ...Args>
void print(T head, Args... rest)
{
   cout << "parameter " << head << endl;
   print(rest...);
}
 
 
int main(void)
{
   print(1,2,3,4);
   return 0;
}
```

 上例会输出每一个参数，直到为空时输出empty。展开参数包的函数有两个，一个是递归函数，另外一个是递归终止函数，参数包Args...在展开的过程中递归调用自己，每调用一次参数包中的参数就会少一个，直到所有的参数都展开为止，当没有参数时，则调用非模板函数print终止递归过程。

递归调用的顺序如下：

```html
print(1,2,3,4);
print(2,3,4);
print(3,4);
print(4);
print();
```

上面的递归终止函数还可以写成这样：

```cpp
template <class T>
void print(T t)
{
   cout << t << endl;
}
```

 修改递归终止函数后，上例中的调用过程是这样的：

```cpp
print(1,2,3,4);
print(2,3,4);
print(3,4);
print(4);
```

可变模板参数求和：

```cpp
template<typename T>
T sum(T t)
{
    return t;
}
template<typename T, typename ... Types>
T sum (T first, Types ... rest)
{
    return first + sum<T>(rest...);
}
 
sum(1,2,3,4); //10
```

 **递归函数展开参数包是一种标准做法，也比较好理解，但也有一个缺点,就是必须要一个重载的递归终止函数，即必须要有一个同名的终止函数来终止递归。**

**（2）**逗号表达式展开参数包

```cpp
template <class T>
void printarg(T t)
{
   cout << t << endl;
}
 
template <class ...Args>
void expand(Args... args)
{
   int arr[] = {(printarg(args), 0)...};
}
 
expand(1,2,3,4);
```

不需要通过递归终止函数，是直接在expand函数体中展开的, printarg不是一个递归终止函数，只是一个处理参数包中每一个参数的函数。这种就地展开参数包的方式实现的关键是逗号表达式。

expand函数中的逗号表达式：(printarg(args), 0)，也是按照这个执行顺序，先执行printarg(args)，再得到逗号表达式的结果0。同时还用到了C++11的另外一个特性——初始化列表，通过初始化列表来初始化一个变长数组, {(printarg(args), 0)...}将会展开成

((printarg(arg1),0), (printarg(arg2),0), (printarg(arg3),0), etc... )，最终会创建一个元素值都为0的数组int arr[sizeof...(Args)]。由于是逗号表达式，在创建数组的过程中会先执行逗号表达式前面的部分printarg(args)打印出参数，也就是说在构造int数组的过程中就将参数包展开了.

#### 1.3.3 可变参数模板类的展开

可变参数模板类是一个带可变模板参数的模板类，比如C++11中的元祖std::tuple就是一个可变模板类，可变参数模板类的参数包展开需要通过模板特化和继承方式去展开，展开方式比可变参数模板函数要复杂。

```cpp
//前向声明
template<typename... Args> struct Sum;
 
//基本定义
template<typename First, typename... Rest>
struct Sum<First, Rest...>
{
    enum { value = Sum<First>::value + Sum<Rest...>::value };
};
 
//递归终止
template<typename Last>
struct Sum<Last>
{
    enum { value = sizeof (Last) };
};
```

 一个基本的可变参数模板应用类由三部分组成，第一部分是：

（1）**前向声明**，声明这个sum类是一个可变参数模板类

```cpp
template<typename... Args> struct sum
```

（2）第二部分是**类的定义**

定义了一个部分展开的可变模参数模板类，告诉编译器如何递归展开参数包。

```cpp
template<typename First, typename... Rest>
struct Sum<First, Rest...>
{
    enum { value = Sum<First>::value + Sum<Rest...>::value };
};
```



（3）第三部分是**特化的递归终止类**

```cpp
template<typename Last> struct sum<last>
{
    enum { value = sizeof (First) };
}
```

