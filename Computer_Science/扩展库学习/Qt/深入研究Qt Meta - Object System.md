# 深入研究Qt Meta - Object System

​	这篇文章我打算研究一下QMetaObject System，也就是Qt自己构建起来的元对象系统。

## 先说RTTI

​	啥是RTTI？这是C++边长里的一个常见术语，全称是：运行阶段类型识别（Runtime Type Identification），关于RTTI如何在原生C++中使用不是我们这里的重点，但是可以明确的一点是——跟编译器实现密切相关，意味着可移植性略差。很多类库已经为其类对象提供了实现这种功能的方式，但由于C++内部并不支持，因此各个厂商的机制通常互不兼容

​	即使编译器支持RTTI，就目前而言，原生的支持仍然十分的不足。我们没有办法完全知道例如类的名字、有哪些父类、有哪些成员变量、有哪些成员函数、哪些是public的、哪些是private的、哪些是protected的等等。

​	有时候一个工程项目可能包含成千上万个类，完整的保存这些信息将会消耗大量的内存资源。为了节省内存，C++标准约定typeid只能返回类名。因此，仅靠dynamic_cast和typeid两个关键字提供的类型信息实在有限。更何况，他还会造成大量的系统开销，这也是为什么这个特性并没有被完整的纳入标准。

> 关于RTTI，可以参看：[【C++】RTTI有什么用？怎么用？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/509453699)以备快速的复习

## 再说QMeta Object System

​	下面我们聊聊，既然大家都各做各的，Qt框架作为C++早期时代就存在的框架，自然实现了自己的一套源系统机制。

​	这个元对象机制不光实现了类似于RTTI那样的动态查看类信息的作用，还扩展出了信号与槽的机制（这个就是大名鼎鼎的信号与槽）

> `Qt's meta-object system provides the signals and slots mechanism for inter-object communication, run-time type information, and the dynamic property system.`

​	这个对象说一千道一万，三个核心

>1. The [QObject](https://doc.qt.io/qt-6/qobject.html) class provides a base class for objects that can take advantage of the meta-object system.
>2. The [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro inside the private section of the class declaration is used to enable meta-object features, such as dynamic properties, signals, and slots.
>3. The [Meta-Object Compiler](https://doc.qt.io/qt-6/moc.html) (`moc`) supplies each [QObject](https://doc.qt.io/qt-6/qobject.html) subclass with the necessary code to implement meta-object features.

​	也就是说：

> 1. QObject这个类提供了整个元对象系统的一个根基
> 2. Q_Object宏这是让一个类可以使用RTTI，信号与槽机制（这就是为什么一些奇奇怪怪的Undefined Reference可以依赖这个解决，下一次发现使用信号与槽机制的时候编译炸了排查的时候考虑这个事情）
> 3. Moc则是更加进一步的提供了元对象系统的实现的保证（嘿！想一下你编译的时候是不是需要有moc文件，他就是Meta-object Compilers，元系统编译器产生的）

​	换而言之，Qt的元对象并不完全直接依赖于语言，而是借助了外来的Moc Tools预先扫描源文件，生成自己的元对象文件，在最后纳入编译阶段合并进来

​	当然，我们的元对象系统还可以做更多的事情：

> 1. QObject::metaObject作为一个静态方法返回关联的metaObject（也就是返回当前对象的元对象系统的那部分）
> 2. QMetaObject::className可以进一步返回运行时的对象名称，而这个是基于标准实现而不是编译器实现的，你知道的，一致性！
> 3. QObject::inherits则是检查一个类是不是位于Qt的继承树上
> 4. QObject::tr则是保证了我们的对象名称满足国际化
> 5. QObject::setProperty和QObject::property让我们的对象拥有了属性这个概念！
> 6. QMetaObject::newInstance()以一种工厂方法构造了这个类的一个新实例

​	我们知道dynamic_cast可以用来转化父类子类，而且转化成不成功全看是不是真的如此。这里我们入乡随俗，使用qobject_cast来检查Qt元对象的继承问题。

​	我随手写一个简单的demo:

```c++
#include <QWidget>
#include <QMainWindow>
#include <QApplication>
class MyObject : public QWidget{};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Import For QWidgets enable
    QObject* obj = new MyObject;

    QWidget* widget = qobject_cast<QWidget*>(obj);
    if(widget){
        qDebug() << "Is Widget";
    }

    QMainWindow* window = qobject_cast<QMainWindow*>(obj);
    if(window){
        qDebug() << "Is Window";
    }

    delete obj;
}
```

​	值得注意的是，如果我们希望纳入一个类进入QObject的继承对象树中，务！必！在私有区域声明一个Q_OBJECT。（当然要是想要直接暴露给外面的话放在public也不是不行）

​	手撸了一个例子

```c++
#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#define IS_USE_QOBJ_MACRO 0

class MyObject : public QWidget{
#if IS_USE_QOBJ_MACRO
    Q_OBJECT
#endif
public:
    QString _ClassName(){
        return this->metaObject()->className();
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QObject* obj = new MyObject;

    QWidget* widget = qobject_cast<QWidget*>(obj);
    if(widget){
        qDebug() << "Is Widget";
    }

    QMainWindow* window = qobject_cast<QMainWindow*>(obj);
    if(window){
        qDebug() << "Is Window";
    }

    qDebug() << dynamic_cast<MyObject*>(obj)->_ClassName();

    delete obj;
}

#if IS_USE_QOBJ_MACRO
#include "main.moc"	// 一个Demo，我们直接自己引入编译好的main.moc
#endif
```

​	你可以留意到，添加了QOBJECT宏的类的行为表现的并不一致。

```
#define IS_USE_QOBJ_MACRO 0
Is Widget
"QWidget"
```

```
#define IS_USE_QOBJ_MACRO 1
Is Widget
"MyObject"
```

​	由此，如果想要让元对象系统正确的工作，请务必使用Q_OBJECT

## 关于Q_OBJECT

```
#define Q_OBJECT \
public: \
    QT_WARNING_PUSH \
    Q_OBJECT_NO_OVERRIDE_WARNING \
    static const QMetaObject staticMetaObject; \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char *); \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
    QT_TR_FUNCTIONS \
private: \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    struct QPrivateSignal { explicit QPrivateSignal() = default; }; \
    QT_ANNOTATE_CLASS(qt_qobject, "")
```

​	这就是我们的源码。

​	可以看到他实际上就是向我们的类内嵌入了工作函数。这就是为什么需要添加一些类。



​	当然还有MOC编译器的使用，以及还有属性系统，挖个坑，有空讲。