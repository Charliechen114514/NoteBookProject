# 介绍一下Qt并发的一些常用的东西

## QThreadPool与QRunnable

​	QThreadPool自身预备了一些QThread。这样，我们就不需要频繁的创建和销毁我们的QThread，从而提升了性能。每个 Qt 应用程序都有一个全局 QThreadPool 对象，可以通过调用 globalInstance() 来访问。

​	那么，我们应该如何启动QThreadPool呢？答案是——使用一个接口叫做QRunnable。QRunnable自身只是要求你实现一个接口。那就是run接口。QRunnable自身不是一个QObject，意味着他是没有信号与槽的，适合那些跟Qt关系不大的，或者说跨线程之间没有对象交互的场景。

```c++
#include "Counter.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>
Counter::Counter() {
}

void Counter::run() {
    qInfo() << "Starting the job!";
    for (int i = 0; i < 20; i++) {
        qInfo() << QThread::currentThread() << "" << i;
        auto sleep_time = QRandomGenerator::global()->bounded(1, 100);
        QThread::msleep(sleep_time);
    }
    qInfo() << "Job done!";
}
```

​	在我们的主线程中，直接将Runable的子类对象传递给我们的QThreadPool，我们的QThreadPool回直接调用内部的run函数执行：

```c++
#include "Counter.h"
#include <QCoreApplication>
#include <QThreadPool>

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    QThread::currentThread()->setObjectName("Main");

    QThreadPool* pool = QThreadPool::globalInstance();
    qInfo() << pool->maxThreadCount();

    for (int i = 0; i < 100; i++) {
        Counter* counter = new Counter();
        counter->setAutoDelete(true);
        pool->start(counter);
    }

    return a.exec();
}
```

​	现在就可以了，可以自己拷贝看看效果。

## 互斥机制：QMutex, QMutexLocker, QSemaphore, QWaitCondition

​	oh天，简直就跟报菜名一样，这四个东西都是用来保证互斥机制的。分别对应了我们的std::mutex. std::mutex_guard, std::counting_semaphore和std::condition_variable四个东西。

​	关于锁等并发编程，这里笔者不打算重复说明了。笔者有一个专门讲述高级并发编程的模块，感兴趣的朋友可以看看：

https://blog.csdn.net/charlie114514191/article/details/145428774

> 一个简单的demo

```c
#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include <QSemaphore>
#include <QThread>
#include <QWaitCondition>

const int      BufferSize = 5;         // 缓冲区大小
QList<int>     buffer;                 // 共享缓冲区
QMutex         mutex;                  // 用于保护共享缓冲区
QSemaphore     freeSpace(BufferSize);  // 空闲空间信号量
QSemaphore     usedSpace(0);           // 已使用空间信号量
QWaitCondition bufferNotEmpty;         // 缓冲区非空条件
QWaitCondition bufferNotFull;          // 缓冲区未满条件

// 生产者线程
class Producer : public QThread {
protected:
    void run() override {
        for (int i = 0; i < 10; ++i) {
            freeSpace.acquire();  // 等待空闲空间
            mutex.lock();         // 锁定互斥量

            // 如果缓冲区已满，等待缓冲区未满条件
            if (buffer.size() == BufferSize) {
                bufferNotFull.wait(&mutex);
            }

            buffer.append(i);  // 生产数据
            qDebug() << "Produced:" << i;

            mutex.unlock();       // 解锁互斥量
            usedSpace.release();  // 增加已使用空间

            // 通知消费者缓冲区非空
            bufferNotEmpty.wakeAll();
        }
    }
};

// 消费者线程
class Consumer : public QThread {
protected:
    void run() override {
        for (int i = 0; i < 10; ++i) {
            usedSpace.acquire();  // 等待已使用空间
            mutex.lock();         // 锁定互斥量

            // 如果缓冲区为空，等待缓冲区非空条件
            if (buffer.isEmpty()) {
                bufferNotEmpty.wait(&mutex);
            }

            int value = buffer.takeFirst();  // 消费数据
            qDebug() << "Consumed:" << value;

            mutex.unlock();       // 解锁互斥量
            freeSpace.release();  // 增加空闲空间

            // 通知生产者缓冲区未满
            bufferNotFull.wakeAll();
        }
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Producer producer;
    Consumer consumer;

    producer.start();  // 启动生产者线程
    consumer.start();  // 启动消费者线程

    producer.wait();  // 等待生产者线程结束
    consumer.wait();  // 等待消费者线程结束

    return a.exec();
}
```

## 跨线程的通信

​	所以Qt如何完成跨线程的通信，即跨线程的信号与槽呢？答案是在使用QueueConnection，当然AutoConnection也可以，Qt6中会默认判断两个对象是否在同一个线程，不再的话就会自动选择QueueConnection。这个是将我们的信号与槽机制放置到了事件的监听循环队列当中去了。

```c++
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QThread>

// 工作线程类
class Worker : public QObject {
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr) : QObject(parent) {
    }

public slots:
    void doWork() {
        qDebug() << "Worker: Running in thread" << QThread::currentThreadId();

        // 模拟耗时操作
        QThread::sleep(2);

        // 发送完成信号
        emit workDone();
    }

signals:
    void workDone();  // 工作完成信号
};

// 主线程类
class Controller : public QObject {
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr) : QObject(parent) {
    }

    void start() {
        qDebug() << "Controller: Running in thread"
                 << QThread::currentThreadId();

        // 创建工作线程
        QThread *workerThread = new QThread;
        Worker  *worker       = new Worker;

        // 将 Worker 移动到工作线程
        worker->moveToThread(workerThread);

        // 连接信号与槽
        connect(workerThread, &QThread::started, worker, &Worker::doWork);
        connect(worker, &Worker::workDone, this, &Controller::handleWorkDone);
        connect(worker, &Worker::workDone, workerThread, &QThread::quit);
        connect(workerThread, &QThread::finished, worker, &Worker::deleteLater);
        connect(workerThread, &QThread::finished, workerThread,
                &QThread::deleteLater);

        // 启动工作线程
        workerThread->start();
    }

public slots:
    void handleWorkDone() {
        qDebug() << "Controller: Work done, running in thread"
                 << QThread::currentThreadId();
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Controller controller;
    controller.start();  // 启动控制器

    return a.exec();
}

#include "main.moc"
```

- 1. 这里`#include "main.moc"`是一个小的偷懒技巧，QT的元对象是依赖于元对象处理器的，我们include进来qt处理后的结果才好方便解决未定义的符号问题
- `2. Worker::workDone` 信号是从工作线程发射的，而 `Controller::handleWorkDone` 槽是在主线程中执行的。
- 3. 由于信号与槽的连接类型是 `Qt::QueuedConnection`（默认跨线程连接类型），信号会被放入主线程的事件循环中，由主线程异步执行槽函数。

## 入门QtConcurrent，Qt集成的一个并发框架

​	为什么会有QtConcorrent呢？因为大部分情况下，我们可以不需要太客制化的并发（特殊场景除外）。我们总是希望将任务并行化但是不想要关心其具体的细节。

​	QtConcurrent就将并发进一步的提升为了一个经典的异步框架。我们只需要让一个任务并发的执行出去，而不需要关心它如何执行，在另一个时间点上我调用一个wait机制就把东西取回来（如果已经做完了直接返回，没有做完那就阻塞的等待直到做完了为之）

| 返回值       | 函数签名                                                     |
| ------------ | ------------------------------------------------------------ |
| `QFuture<T>` | **[run](https://doc.qt.io/qt-6/qtconcurrent.html#run)**(Function *function*, ...) |
| `QFuture<T>` | **[run](https://doc.qt.io/qt-6/qtconcurrent.html#run-1)**(QThreadPool **pool*, Function *function*, ...) |

​	这里，我们的Run就是直接的派发一个任务出去。返回回来的QFuture就是我们希望得到的一个结果。比如说，我们depatch了一个网络请求。需要其结果的时候，我们的结果就应该被存放在我们的QFuture里面。

​	直到我们获取的时候，我们才会获取我们想要的东西。我们调用的是waitForFinish这个函数，明确的表达我们需要结果后才会执行。

> 简单的说：QFuture 允许线程与一个或多个将在稍后某个时间点准备就绪的结果同步。结果可以是任何具有默认、复制和可能移动构造函数的类型。如果在调用 result()、resultAt()、results() 和 takeResult() 函数时结果不可用，QFuture 将等待，直到结果可用。您可以使用 isResultReadyAt() 函数来确定结果是否已准备就绪。对于报告多个结果的 QFuture 对象，resultCount() 函数返回连续结果的数量。这意味着从 0 到 resultCount() 迭代结果始终是安全的。takeResult() 会使未来无效，并且任何后续尝试访问未来结果的尝试都会导致未定义的行为。isValid() 告诉您是否可以访问结果。
>
> QFuture 提供了 Java 样式的迭代器 (QFutureIterator) 和 STL 样式的迭代器 (QFuture::const_iterator)。使用这些迭代器是访问未来结果的另一种方式。
>
> 如果需要将一个异步计算的结果传递给另一个异步计算，QFuture 提供了一种使用 then() 链接多个顺序计算的便捷方法。onCanceled() 可用于添加在 QFuture 被取消时要调用的处理程序。此外，onFailed() 可用于处理链中发生的任何故障。请注意，QFuture 依赖于异常来进行错误处理。如果无法使用异常，您仍然可以通过将错误类型作为 QFuture 类型的一部分来指示 QFuture 的错误状态。例如，您可以使用 std::variant、std::any 或类似类型来保存结果或失败，或者创建自定义类型。
>
> 上面的部分是翻译Qt文档的结果。

​	如果需要使用到信号与槽的机制，我们还会需要使用的是QFutureWatcher来监控我们的QFuture的状态，这样，信号与槽机制就可以跟异步框架精密协调的工作起来了。

> QFutureWatcher 中还提供了一些 QFuture 函数：progressValue()、progressMinimum()、progressMaximum()、progressText()、isStarted()、isFinished()、isRunning()、isCanceled()、isSuspending()、isSuspended()、waitForFinished()、result() 和 resultAt()。cancel()、setSuspended()、suspend()、resume() 和 toggleSuspended() 函数是 QFutureWatcher 中的插槽。 状态更改通过 started()、finished()、canceled()、suspending()、suspended()、resumed()、resultReadyAt() 和 resultsReadyAt() 信号报告。进度信息由 progressRangeChanged()、void progressValueChanged() 和 progressTextChanged() 信号提供。 节流控制由 setPendingResultsLimit() 函数提供。当待处理的 resultReadyAt() 或 resultsReadyAt() 信号的数量超过限制时，未来所代表的计算将自动受到限制。一旦待处理信号的数量低于限制，计算将恢复。

​	以及，Qt自身也提供了一个类似域LockGuard的机制，这里，我们的类名称是**[QFutureSynchronizer](https://doc.qt.io/qt-6/qfuturesynchronizer.html#QFutureSynchronizer)**，可以看看这里的Qt文档。

## 一些参考

- [Qt 6 Core Advanced with C++ | Udemy](https://www.udemy.com/course/qt-6-core-advanced/)
- Qt Documentations [Qt Documentation | All Documentation](https://doc.qt.io/all-topics.html)

 