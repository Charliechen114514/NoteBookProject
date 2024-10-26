# Qt元对象系统 —— 信号与槽

​	信号与槽讨论的是Qt对象之间的连接与交互。我们就是使用这种方式实现了一个简单的异步调用。换而言之，信号与槽让我们可以不必考虑复杂的调用。只需要当我们需要在程序中表达：“希望在程序中通知一个事件而且按照我们设定的方式给出回应”的时候，信号与槽就会排上用场。举个例子：

```
connect(ui->lineedit, &QLineEdit::textChanged, this, &MyClass::handle_line_edit_change)
```

​	表达了我们确认一个连接：当LineEdit的文字一发生改变就通知我们的MyClass做出对应的举措。具体的举措在handle_line_edit_change函数已经得到了定义！

> 当我们想要对一个重载的信号连接槽函数的时候，注意QOverLoad的使用，他负责消除连接的二义性。

​	我们知道，Qt的信号与槽是在Qt自己家的EventLoop监控的，所有的signals都会放到一个队列等待一个个发送（非常异步），当然，具体我们可以做出调整：这是在connect里的ConnectionType中给出设置：

- **AutoConnection**: 默认连接方式。根据发射信号和接收槽的对象所在的线程自动选择连接类型。如果信号和槽在同一线程中，则使用直接连接；如果在不同线程中，则使用队列连接。
- **DirectConnection**: 直接连接，信号发射后立即调用槽函数。适用于信号和槽在同一线程的情况。
- **QueuedConnection**: 队列连接，信号发射后将调用槽函数的请求放入接收对象所在线程的事件队列中，稍后处理。这在跨线程通信时非常有用。
- **BlockingQueuedConnection**: 阻塞队列连接，类似于队列连接，但在信号发射后会阻塞直到槽函数处理完成。这通常在需要确保槽函数在信号发射后立即执行时使用。
- **UniqueConnection**: 用于确保同一对信号和槽之间只连接一次。如果尝试重复连接，将不会添加新的连接

​	当然，取消一个连接也很简单：disconnect函数的调用就会将监控给移除掉。这样我们的信号再发送的时候就不会发生槽函数对应的调用了。

```
#ifndef STUDENT_H
#define STUDENT_H
#include <QDebug>
#include <QObject>

class Student : public QObject {
    Q_OBJECT
public:
    explicit Student(QObject* parent = nullptr){
    	
    }

public:
    QString getName() const {
        return name;
    }

    void setName(const QString& name) {
        this->name = name;
        emit notifyNameChange();
    }

    void disconnect_this() {
        disconnect(this, &Student::notifyNameChange, this,
                   &Student::handle_change);
    }

    void handle_change() {
        qDebug() << "Change !";
    }

signals:
    void notifyNameChange();

private:
    QString name;
signals:
};

#endif  // STUDENT_H
```

```
#include <QCoreApplication>
#include <QMetaProperty>
#include "Student.h"
void handle_change() {
    qDebug() << "Yes, the name has changed!";
}

int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    auto             stu = new Student;
    stu->setName("Charliechen");
    stu->disconnect_this();
    stu->setName("1111");
    a.exec();
    delete stu;
}
```

​	你会发现只有第一次设置的时候给出了响应，但是后面的就没有了。这是因为我们的程序已经disconnect了连接。