# AutoClassGenerator开发记录 ——几个要点

​		本篇博客的主要目的是为了记录一下自己开发AutoClassGenerator的几个开发的要点，算是对本次的开发（大约是四天，每天8个小时的开发）的一个回顾和总结。

## friend在重载部分符号的作用

​		解析类中，我构造了一个类来专门存储类的信息，就是NewClass类，为了标识一个类，要求我需要在容器中找到他。

```
QList<NewClass> classLists
```

​		现在，我们希望在NewClass中，使用模板算法：`indexOf(A& T)`来找到目标。

​		开始的时候，我这只是简单的在类中

```C++
bool operator==(const NewClass& otherClass){
	return otherClass.name == this->name;
}
```

​		但是我很快就发现不对，简单的讲，就是：

```
:> can not find suitable operator== for const NewClass& and const NewClass&
```

​		换而言之，编译器没有找到合适的函数来充当==的运算机制，可是我分明重载了运算符？

​		答案是，我们重载的是类内的`==`运算符，也就是说，这个`==`只可以用在自身和别人的比较，而在这个模板算法中则是需要==被全局使用。这就需要我们添加C++的friend修饰符，，也就是改写我们的函数签名为

```C++
friend bool operator==(const NewClass& one, const NewClass& otherClass){
	return one.getName() == otherClass.getName();
}
```

​		现在，我们就可以使用模板算法了！

## 使用父类方法类传递作为具体实现的接口的参数

​		什么意思呢，举个例子：现在我希望导出生成的字符串用不同的方式去操纵导出，也就是说：

```C++
class ExportManager{
	public:
    	void exportStringInNormal(QString sth);
    	void exportStringToCMake(QString sth);
    	void exportStringToSourceHeaderSperate(QString sth);
    	...
}
```

​		可以看到我们的方法数量会直接暴涨，臃肿不堪。这个时候，我们就有必要请出继承和组合的方式，来仔细分析：

> 我们的导出可能是以到CMakeLists的形式，或者是要给QMake识别，亦或者我们打算自己动手改配置...无论如何，我们完全可以抽象除一个ExportPlaceAbstract方法，指代我们的导出地址操作如何推进，所有的子类去实现这些复杂的，各异的，而我们只需要完成一个接口即可。

```C++
class ExportManager{
	public:
		processExport(QString buf, ExportPlaceAbsract& placeMethod, ExportPathAbstract& pathMethod, ...);
    	...
}
```

​		我们实现的时候，会意识到，只需要

```
placeMethod.process();
pathMethod.process();
```

​		而完全不需要写冗余的代码。

## 在C++中，如果需要完全控制对象的声明周期，考虑堆上开辟内存后，容器内存储指针。

​		在qt框架下，需要注意的是，对于类型是指针的容器，只会开辟一个指针数组存储，容器自身的占比会小。同时，也会更加有利于管理对象的声明周期。而且，查询的时候不需要复杂的重载，对于对象本身的来讲，只需要比较指针指向的地址就可以了。但是，如果是想要查找符合要求的对象，那就需要使用for遍历一个一个取出来解引用对照了。