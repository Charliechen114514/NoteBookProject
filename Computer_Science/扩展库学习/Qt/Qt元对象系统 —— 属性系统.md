# Qt元对象系统 —— 属性系统

​	我们下面要讨论的是Qt元对象系统的第二部分：那就是Qt的属性系统。我们知道大部分的类其实都在现实生活中表达一种属性——我们希望通过接口来处理，使用Qt的信号与槽机制通知我们的属性相关的事物。

## 属性系统

​	Qt的属性系统是一个强大的功能，用于支持对象的动态特性和信号槽机制。它允许你在运行时查询和修改对象的属性，而无需直接访问对象的内部数据。说白了，就是让我们不必手动封装，直接提供了一套完整的属性通知，设置，获取流程。

```
Q_PROPERTY(type name
           (READ getFunction [WRITE setFunction] |
            MEMBER memberName [(READ getFunction | WRITE setFunction)])
           [RESET resetFunction]
           [NOTIFY notifySignal]
           [REVISION int | REVISION(int[, int])]
           [DESIGNABLE bool]
           [SCRIPTABLE bool]
           [STORED bool]
           [USER bool]
           [BINDABLE bindableProperty]
           [CONSTANT]
           [FINAL]
           [REQUIRED])
```

​	老样子，这里列一个简单的表格说下每一个都在干什么：

| 参数                                                      | 说明                                                         |
| --------------------------------------------------------- | ------------------------------------------------------------ |
| `type`                                                    | 属性的数据类型，例如 `int`、`QString`、`QColor` 等。         |
| `name`                                                    | 属性的名称，用于访问和引用该属性。                           |
| `(READ getFunction)`                                      | 指定用于获取属性值的成员函数。                               |
| `[WRITE setFunction]`                                     | 可选项，指定用于设置属性值的成员函数。如果不提供，则该属性为只读。 |
| `MEMBER memberName[(READ getFunction|WRITE setFunction)]` | 这里表达是对应的映射成员                                     |
| `[RESET resetFunction]`                                   | 可选项，指定一个成员函数，用于将属性重置为默认值。           |
| `[NOTIFY notifySignal]`                                   | 可选项，指定一个信号，当属性值变化时发出通知。               |
| `[REVISION int | REVISION(int[, int])]`                   | 用于指定属性的版本控制，以便在修改类时保持向后兼容性。       |
| `[DESIGNABLE bool]`                                       | 可选项，指定该属性是否在Qt Designer中可见，`true` 表示可见，`false` 表示不可见。 |
| `[SCRIPTABLE bool]`                                       | 可选项，指定该属性是否可以在QML或JavaScript中访问。          |
| `[STORED bool]`                                           | 可选项，指定该属性是否应该在对象的状态中存储。               |
| `[USER bool]`                                             | 可选项，指定该属性是否应该对用户可见，通常用于指示用户界面中的控件。 |
| `[BINDABLE bindableProperty]`                             | 可选项，指定该属性是否可以在QML中绑定到另一个属性。          |
| `[CONSTANT]`                                              | 可选项，指示该属性是一个常量，不能被修改。                   |
| `[FINAL]`                                                 | 可选项，指示该属性不可以被重写。                             |
| `[REQUIRED]`                                              | 可选项，指示该属性在某些情况下是必需的。                     |

​	随手就可以从Qt的源码中获得案例，比如说Qt Document的例子是：

```
Q_PROPERTY(bool focus READ hasFocus)
Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
Q_PROPERTY(QCursor cursor READ cursor WRITE setCursor RESET unsetCursor)
```

​	很容易做出这些解读：

第一个属性是 `focus`，类型为布尔值，表示对象的焦点状态。它有一个读取函数 `hasFocus`，用于返回对象是否当前具有焦点。**这个属性是只读的，因此没有设置函数。**

第二个属性是 `enabled`，同样是布尔值，表示对象 是否启用。它有一个读取函数 `isEnabled` 和一个设置函数 `setEnabled`，允许读取和修改这个属性的值。

第三个属性是 `cursor`，类型为 `QCursor`，表示当前光标状态。它有一个读取函数 `cursor`，用于获取当前光标的状态，还有一个设置函数 `setCursor` 用于修改光标。同时，它还有一个重置函数 `unsetCursor`，用于将光标重置为默认状态。这个属性支持读取、修改和重置操作。

​	当然，它也可以跟信号系统直接挂起钩来：

```
    Q_PROPERTY(QColor color MEMBER m_color NOTIFY colorChanged)
    Q_PROPERTY(qreal spacing MEMBER m_spacing NOTIFY spacingChanged)
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged)
    ...
signals:
    void colorChanged();
    void spacingChanged();
    void textChanged(const QString &newText);

private:
    QColor  m_color;
    qreal   m_spacing;
    QString m_text;
```

第一个属性是 `color`，其类型为 `QColor`，对应的私有成员变量是 `m_color`。当 `m_color` 发生变化时，会发出 `colorChanged()` 信号，以通知其他部分的代码。

第二个属性是 `spacing`，类型为 `qreal`，对应的成员变量是 `m_spacing`。当 `m_spacing` 变化时，会发出 `spacingChanged()` 信号，允许观察者知晓间距的变化。

第三个属性是 `text`，类型为 `QString`，对应的成员变量是 `m_text`。当 `m_text` 发生变化时，会发出 `textChanged(const QString &newText)` 信号，并传递新的文本值，以便其他代码可以接收到更新后的文本。

​	这样事情就很简单了：我们的属性的变化就可以传递到其他子系统，比如说典型的就是我们的Ui显示。

## 进一步：使用上面的阐述详细讨论如何对对象的属性读写

Qt的元对象系统是通过 `QObject` 类及其派生类实现的。每个 `QObject` 的子类都自动具备元对象功能，这包括对象的类型信息、属性、信号和槽等。通过这个系统，开发者可以在不直接依赖具体实现的情况下，动态地访问和修改对象的属性。

​	我们一般这样干：

1. **获取元对象**：首先，需要获取对象的元对象。可以通过调用 `metaObject()` 方法来完成。该方法返回一个 `const QMetaObject*` 指针，指向该对象的元对象。
2. **查询属性**：使用获取的元对象，可以通过 `QMetaObject::property(int index)` 方法来查询属性。这个方法返回一个 `QMetaProperty` 对象，该对象包含了属性的名称、类型、读写方法等信息。
3. **读取属性值**：通过 `QMetaProperty` 对象的 `read()` 方法，可以读取属性值。该方法接受一个指向对象的指针，并返回一个 `QVariant` 类型的值。这种方式的优点在于 `QVariant` 支持多种数据类型，因此可以轻松处理不同类型的属性。

​	在写入属性时，过程类似：

1. **获取元对象**：同样地，通过调用 `metaObject()` 方法获取元对象。
2. **查询属性**：通过 `QMetaObject::indexOfProperty(const char* name)` 方法获取指定属性的索引，然后使用 `property(int index)` 方法获取 `QMetaProperty` 对象。
3. **写入属性值**：利用 `QMetaProperty::write()` 方法，可以将新值写入属性。该方法需要指定一个指向对象的指针和一个 `QVariant` 类型的新值。如果属性是只读的，写入操作将失败。

## 一个例子

​	典中典之学生：

```
#ifndef STUDENT_H
#define STUDENT_H
#include <QDebug>
#include <QObject>

class Student : public QObject {
    Q_OBJECT
    Q_PROPERTY(
        QString name READ getName WRITE setName NOTIFY notifyNameChange FINAL)
public:
    explicit Student(QObject* parent = nullptr);

public:
    QString getName() const {
        return name;
    }

    void setName(const QString& name) {
        this->name = name;
        emit notifyNameChange();
    }

    void handle_change() {
        qDebug() << "Chaneg !";
    }

signals:
    void notifyNameChange();

private:
    QString name;
signals:
};

#endif  // STUDENT_H
```

​	我们来试试看：

```
#include <QCoreApplication>
#include <QMetaProperty>
#include "Student.h"
void handle_change() {
    qDebug() << "Yes, the name has changed!";
}

int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    auto             stu         = new Student;
    QObject*         seen_as_obj = dynamic_cast<QObject*>(stu);
    if (!seen_as_obj) return -1;
    qDebug() << "Property are here" << "\n";
    auto cnt = seen_as_obj->metaObject()->propertyCount();
    for (auto i = 0; i < cnt; i++) {
        QMetaProperty metaproperty = seen_as_obj->metaObject()->property(i);
        const char*   name         = metaproperty.name();
        qDebug() << "Property Name:> " << name;
    }

    stu->setProperty("name", "Charliechen");
    qDebug() << "Let's see if name changed:> " << stu->getName();
    delete stu;
    return a.exec();
}
```

```
Property are here

Property Name:>  objectName
Property Name:>  name
Let's see if name changed:>  "Charliechen"
```



## Detailed Descriptions of settings

​	下面这段来自Qt Document

> - 如果没有指定 MEMBER 变量，则需要 READ 访问器函数。它用于读取属性值。理想情况下，为此目的使用 const 函数，并且它必须返回属性的类型或对该类型的 const 引用。例如，QWidget::focus 是一个只读属性，具有 READ 函数 QWidget::hasFocus()。如果指定了 BINDABLE，您可以写入 READ default 以从 BINDABLE 生成 READ 访问器。
> - WRITE 访问器函数是可选的。它用于设置属性值。它必须返回 void，并且必须只接受一个参数，该参数要么是属性的类型，要么是指向该类型的指针或引用。例如，QWidget::enabled 具有 WRITE 函数 QWidget::setEnabled()。只读属性不需要 WRITE 函数。例如，QWidget::focus 没有 WRITE 函数。如果您同时指定了 BINDABLE 和 WRITE 默认值，则将从 
> - BINDABLE 生成 WRITE 访问器。生成的 WRITE 访问器不会明确发出任何用 NOTIFY 声明的信号。您应该将信号注册为 BINDABLE 的更改处理程序，例如使用 Q_OBJECT_BINDABLE_PROPERTY。
>   如果未指定 READ 访问器函数，则需要 MEMBER 变量关联。这使得给定的成员变量可读可写，而无需创建 READ 和 WRITE 访问器函数。如果您需要控制变量访问，除了 MEMBER 变量关联之外，仍然可以使用 READ 或 WRITE 访问器函数（但不能同时使用）。
> - RESET 函数是可选的。它用于将属性设置回其上下文特定的默认值。例如，QWidget::cursor 具有典型的 READ 和 WRITE 函数 QWidget::cursor() 和 QWidget::setCursor()，并且它还具有 RESET 函数 QWidget::unsetCursor()，因为对 QWidget::setCursor() 的任何调用都不能意味着重置为上下文特定的光标。RESET 函数必须返回 void 并且不带任何参数。
> - NOTIFY 信号是可选的。如果已定义，它应该指定该类中的一个现有信号，该信号在属性值更改时发出。MEMBER 变量的 NOTIFY 信号必须采用零个或一个参数，该参数必须与属性的类型相同。该参数将采用属性的新值。NOTIFY 信号应该仅在属性确实已更改时发出，以避免在 QML 中不必要地重新评估绑定。当通过 Qt API（QObject::setProperty、QMetaProperty 等）更改属性时，会自动发出信号，但直接更改 MEMBER 时不会发出信号。
> - REVISION 编号或 REVISION() 宏是可选的。如果包含，则它定义属性及其通知信号，以便在 API 的特定修订版中使用（通常用于 QML）。如果不包含，则默认为 0。
> - DESIGNABLE 属性指示属性是否应在 GUI 设计工具（例如 Qt Widgets Designer）的属性编辑器中可见。大多数属性都是 DESIGNABLE（默认为 true）。有效值为 true 和 false。
>   SCRIPTABLE 属性指示此属性是否应由脚本引擎访问（默认为 true）。有效值为 true 和 false。
> - STORED 属性指示是否应将属性视为独立存在或依赖于其他值。它还指示在存储对象状态时是否必须保存属性值。大多数属性都是 STORED（默认为 true），但例如 QWidget::minimumWidth() 的 STORED 为 false，因为其值仅取自属性 QWidget::minimumSize() 的宽度组件，该属性为 QSize。
>   USER 属性指示该属性是否被指定为类的面向用户的属性或用户可编辑的属性。通常，每个类只有一个 USER 属性（默认为 false）。例如，QAbstractButton::checked 是（可检查）按钮的用户可编辑属性。请注意，QItemDelegate 获取和设置小部件的 USER 属性。
> - BINDABLE bindableProperty 属性指示该属性支持绑定，并且可以通过元对象系统（QMetaProperty）设置和检查对此属性的绑定。bindableProperty 命名 QBindable<T> 类型的类成员，其中 T 是属性类型。此属性是在 Qt 6.0 中引入的。
> - CONSTANT 属性的存在表示属性值是常量。对于给定的对象实例，常量属性的 READ 方法每次调用时都必须返回相同的值。对于对象的不同实例，此常量值可能不同。常量属性不能具有 WRITE 方法或 NOTIFY 信号。
> - FINAL 属性的存在表示该属性不会被派生类覆盖。在某些情况下，这可以用于性能优化，但 moc 不会强制执行。必须注意永远不要覆盖 FINAL 属性。
>
> - REQUIRED 属性的存在表示该属性应由类的用户设置。moc 不会强制执行此操作，并且主要用于暴露给 QML 的类。在 QML 中，除非已设置所有必需属性，否则无法实例化具有必需属性的类。