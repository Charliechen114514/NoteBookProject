# QT中的定时器与计时器

​	笔者写Qt的时候经常遇到需要定时完成任务的情况。举个例子：我写串口通信程序的时候需要定时向下位机发送数据。或者是定时任务周期性出发（更新时间等）

​	在Qt中，有两个非常常用的类来完成定时操作，请看：

## QTimer

​	`QTimer` 类提供了一个高级的定时器编程接口。使用时，创建一个 `QTimer`，将其 `timeout()` 信号连接到相应的槽，并调用 `start()`。之后，它将在固定的时间间隔内发射 `timeout()` 信号。以下是一个一秒（1000 毫秒）定时器的示例（来自模拟钟表示例）：

```
QTimer *timer = new QTimer(this);
connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
timer->start(1000);
```

​	从那时起，`update()` 槽每秒会被调用一次。你可以通过调用 `setSingleShot(true)` 将定时器设置为只触发一次。你还可以使用静态的 `QTimer::singleShot()` 函数在指定的时间间隔后调用一个槽：

```
QTimer::singleShot(200, this, &Foo::updateCaption);
```

​	在多线程应用程序中，你可以在任何具有事件循环的线程中使用 `QTimer`。要从非 GUI 线程启动事件循环，使用 `QThread::exec()`。Qt 使用定时器的线程亲和性来确定哪个线程将发射 `timeout()` 信号。因此，必须在其线程中启动和停止定时器；不能从其他线程启动定时器。

​	在特殊情况下，超时时间为 0 的 `QTimer` 将尽快超时，但零定时器与其他事件源之间的顺序是未指定的。零定时器可以用于在保持用户界面响应的同时执行一些工作：

```
QTimer *timer = new QTimer(this);
connect(timer, &QTimer::timeout, this, &Foo::processOneThing);
timer->start();
```

​	从那时起，`processOneThing()` 将被重复调用。它应编写为总是快速返回（通常在处理一条数据项后），以便 Qt 能够向用户界面传递事件，并在完成所有工作后尽快停止定时器。这是实现 GUI 应用程序中重型工作的传统方法，但随着多线程在越来越多的平台上的可用性增加，我们预期零毫秒的 `QTimer` 对象将逐渐被 `QThread` 取代。

​	定时器的精度取决于底层操作系统和硬件。大多数平台支持 1 毫秒的分辨率，尽管在许多实际情况下，定时器的精度可能无法达到这一分辨率。精度也取决于定时器类型。对于 `Qt::PreciseTimer`，`QTimer` 将尽力保持 1 毫秒的精度。精确定时器也不会提前超时。

​	对于 `Qt::CoarseTimer` 和 `Qt::VeryCoarseTimer` 类型，`QTimer` 可能会在预期之前提前唤醒，具体提前的时间范围为这些类型的边界：对于 `Qt::CoarseTimer` 为间隔的 5%，对于 `Qt::VeryCoarseTimer` 为 500 毫秒。

​	所有定时器类型可能会因系统繁忙或无法提供请求的精度而延迟超时。在超时过载的情况下，即使多个超时已经到达，Qt 只会发射一次 `timeout()`，然后恢复原始的时间间隔。

### QTimer 的替代方案

​	Qt 6.8 引入了 `QChronoTimer`。这两个类之间的主要区别在于，`QChronoTimer` 支持更大的时间间隔范围和更高的精度（`std::chrono::nanoseconds`）。对于 `QTimer`，最大支持的间隔为 ±24 天，而对于 `QChronoTimer` 为 ±292 年（对大于 `std::numeric_limits<int>::max()` 的时间间隔，减少了整数溢出的可能性）。如果你只需要毫秒级的分辨率和 ±24 天的范围，可以继续使用 `QTimer`。

​	另一个替代方案是在你的类中重新实现 `QObject::timerEvent()` 方法（该类必须是 `QObject` 的子类），并使用以下方法之一：

- 使用 `QBasicTimer`，这是一个轻量级的值类，封装了定时器 ID。你可以使用 `QBasicTimer::start()` 启动定时器，并用 `QBasicTimer::stop()` 停止它。你可以在重新实现的 `timerEvent()` 中处理事件。
- 更低级的方法是直接操作定时器 ID。启动定时器时调用 `QObject::startTimer()`，存储返回的 ID。停止定时器时调用 `QObject::killTimer()`。你可以在重新实现的 `timerEvent()` 中处理事件。这种方法通常比使用 `QBasicTimer` 更麻烦。

​	使用 `timerEvent()` 的一个缺点是一些高级功能，如单次触发定时器和信号，不受支持。

### API

| 成员/信号/槽                                                 | 类型     | 说明                                                        |
| ------------------------------------------------------------ | -------- | ----------------------------------------------------------- |
| `QTimer(QObject *parent = nullptr)`                          | 构造函数 | 创建一个定时器对象，可以选择设置父对象。                    |
| `virtual ~QTimer()`                                          | 析构函数 | 销毁定时器对象。                                            |
| `QBindable<bool> bindableActive()`                           | 成员     | 返回一个可绑定的布尔值，指示定时器是否处于活动状态。        |
| `QBindable<int> bindableInterval()`                          | 成员     | 返回一个可绑定的整型值，表示定时器的时间间隔。              |
| `QBindable<bool> bindableSingleShot()`                       | 成员     | 返回一个可绑定的布尔值，指示定时器是否为单次触发模式。      |
| `QBindable<Qt::TimerType> bindableTimerType()`               | 成员     | 返回一个可绑定的枚举值，表示定时器的类型。                  |
| `QMetaObject::Connection callOnTimeout(Functor &&slot)`      | 成员     | 连接指定的槽函数到 `timeout()` 信号，当定时器超时时调用。   |
| `QMetaObject::Connection callOnTimeout(const QObject *context, Functor &&slot, Qt::ConnectionType connectionType = Qt::AutoConnection)` | 成员     | 在指定上下文中连接槽函数到 `timeout()` 信号。               |
| `Qt::TimerId id() const` (since 6.8)                         | 成员     | 返回定时器的 ID，用于唯一标识定时器。                       |
| `int interval() const`                                       | 成员     | 返回定时器的时间间隔（毫秒）。                              |
| `std::chrono::milliseconds intervalAsDuration() const`       | 成员     | 返回以 `std::chrono::milliseconds` 表示的时间间隔。         |
| `bool isActive() const`                                      | 成员     | 判断定时器是否处于活动状态。                                |
| `bool isSingleShot() const`                                  | 成员     | 判断定时器是否为单次触发模式。                              |
| `int remainingTime() const`                                  | 成员     | 返回定时器下次超时之前剩余的时间（毫秒）。                  |
| `std::chrono::milliseconds remainingTimeAsDuration() const`  | 成员     | 返回以 `std::chrono::milliseconds` 表示的剩余时间。         |
| `void setInterval(int msec)`                                 | 成员     | 设置定时器的时间间隔（毫秒）。                              |
| `void setInterval(std::chrono::milliseconds value)`          | 成员     | 设置定时器的时间间隔，以 `std::chrono::milliseconds` 表示。 |
| `void setSingleShot(bool singleShot)`                        | 成员     | 设置定时器为单次触发或循环触发模式。                        |
| `void setTimerType(Qt::TimerType atype)`                     | 成员     | 设置定时器的类型。                                          |
| `void start(std::chrono::milliseconds msec)`                 | 成员     | 启动定时器，设置时间间隔。                                  |
| `int timerId() const`                                        | 成员     | 返回定时器的 ID。                                           |
| `Qt::TimerType timerType() const`                            | 成员     | 返回定时器的类型。                                          |
| `void start(int msec)`                                       | 公共槽   | 启动定时器，并设置时间间隔（毫秒）。                        |
| `void start()`                                               | 公共槽   | 启动定时器，使用之前设置的时间间隔。                        |
| `void stop()`                                                | 公共槽   | 停止定时器。                                                |
| `void timeout()`                                             | 信号     | 当定时器超时时发射的信号。                                  |
| `void singleShot(Duration interval, Functor &&functor)`      | 静态成员 | 设置一个单次触发的定时器，在指定时间后调用给定的函数。      |
| `void singleShot(Duration interval, Qt::TimerType timerType, Functor &&functor)` | 静态成员 | 设置单次触发定时器，并指定定时器类型。                      |
| `void singleShot(Duration interval, const QObject *context, Functor &&functor)` | 静态成员 | 在指定上下文中设置单次触发定时器。                          |
| `void singleShot(Duration interval, Qt::TimerType timerType, const QObject *context, Functor &&functor)` | 静态成员 | 在指定上下文中设置单次触发定时器，并指定类型。              |
| `void singleShot(std::chrono::nanoseconds nsec, const QObject *receiver, const char *member)` | 静态成员 | 在指定纳秒数后调用接收者的成员函数。                        |
| `void singleShot(std::chrono::nanoseconds nsec, Qt::TimerType timerType, const QObject *receiver, const char *member)` | 静态成员 | 在指定纳秒数后调用接收者的成员                              |

## QElapsedTimer

​	这个玩意是用来实现计时操作的：通常用于快速计算两个事件之间经过的时间。它的 API 与 `QTime` 类似，因此可以快速将使用 `QTime` 的代码迁移到这个新类。然而，与 `QTime` 不同，`QElapsedTimer` 尽可能使用单调时钟。这意味着无法将 `QElapsedTimer` 对象转换为人类可读的时间。该类的典型用例是确定在某个缓慢操作中花费了多少时间。最简单的示例是用于调试目的，如下所示：

```
QElapsedTimer timer;
timer.start();
slowOperation1();
qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
```

​	在这个示例中，通过调用 `start()` 启动计时器，经过的时间通过 `elapsed()` 函数计算。经过的时间还可以用来重新计算另一项操作可用的时间，这在执行必须在特定时间内完成的多步操作时非常有用。例如，`QIODevice` 及其子类中的 `waitFor` 类型函数就是这种需求的良好示例。在这种情况下，代码可以如下：

```
void executeSlowOperations(int timeout)
{
    QElapsedTimer timer;
    timer.start();
    slowOperation1();

    int remainingTime = timeout - timer.elapsed();
    if (remainingTime > 0)
        slowOperation2(remainingTime);
}
```

​	另一个用例是为特定的时间片执行某个操作。为此，`QElapsedTimer` 提供了 `hasExpired()` 便利函数，可用于判断某些毫秒是否已经过去：

```
void executeOperationsForTime(int ms)
{
    QElapsedTimer timer;
    timer.start();

    while (!timer.hasExpired(ms))
        slowOperation1();
}
```

​	在这种情况下，使用 `QDeadlineTimer` 更为方便，它计算未来的超时，而不是跟踪经过的时间。`QElapsedTimer` 将在所有支持的平台上使用平台的单调参考时钟（见 `QElapsedTimer::isMonotonic()`）。这带来了额外的好处，即 `QElapsedTimer` 对时间调整（例如用户修正时间）是免疫的。与 `QTime` 不同，`QElapsedTimer` 也对时区设置的变化（例如夏令时）免疫。

另一方面，这意味着 `QElapsedTimer` 的值只能与使用相同参考的其他值进行比较。如果从 `QElapsedTimer` 对象提取的参考时间（`QElapsedTimer::msecsSinceReference()`）被序列化，这一点尤其重要。这些值不应在网络中交换或保存到磁盘，因为无法确定接收数据的计算机节点是否与原始节点相同，或者是否自那以来已经重启。

然而，确实可以与在同一机器上运行的其他进程交换该值，前提是它们也使用相同的参考时钟。`QElapsedTimer` 将始终使用相同的时钟，因此与来自同一机器的其他进程的值进行比较是安全的。如果要与其他 API 生成的值进行比较，应该检查使用的时钟是否与 `QElapsedTimer` 相同（见 `QElapsedTimer::clockType()`）。

### API

| 成员/操作符                                                  | 类型         | 说明                                                   |
| ------------------------------------------------------------ | ------------ | ------------------------------------------------------ |
| `QElapsedTimer()`                                            | 构造函数     | 创建一个 `QElapsedTimer` 对象。                        |
| `QElapsedTimer::Duration durationElapsed() const` (since 6.6) | 成员         | 返回从计时器启动到现在经过的时间。                     |
| `QElapsedTimer::Duration durationTo(const QElapsedTimer &other) const` (since 6.6) | 成员         | 返回当前计时器到另一个计时器之间的经过时间。           |
| `qint64 elapsed() const`                                     | 成员         | 返回自 `start()` 被调用以来的经过时间（毫秒）。        |
| `bool hasExpired(qint64 timeout) const`                      | 成员         | 判断指定的超时是否已经到达。                           |
| `void invalidate()`                                          | 成员         | 使计时器无效。                                         |
| `bool isValid() const`                                       | 成员         | 判断计时器是否有效。                                   |
| `qint64 msecsSinceReference() const`                         | 成员         | 返回自参考时间以来经过的毫秒数。                       |
| `qint64 msecsTo(const QElapsedTimer &other) const`           | 成员         | 返回当前计时器到另一个计时器的毫秒数。                 |
| `qint64 nsecsElapsed() const`                                | 成员         | 返回自 `start()` 被调用以来的经过时间（纳秒）。        |
| `qint64 restart()`                                           | 成员         | 重新启动计时器并返回自上次启动以来的经过时间（毫秒）。 |
| `qint64 secsTo(const QElapsedTimer &other) const`            | 成员         | 返回当前计时器到另一个计时器的秒数。                   |
| `void start()`                                               | 成员         | 启动计时器。                                           |
| `QElapsedTimer::ClockType clockType()`                       | 静态公共成员 | 返回 `QElapsedTimer` 使用的时钟类型。                  |
| `bool isMonotonic()`                                         | 静态公共成员 | 判断当前平台是否支持单调时钟。                         |
| `bool operator!=(const QElapsedTimer &lhs, const QElapsedTimer &rhs)` | 非成员操作符 | 判断两个 `QElapsedTimer` 对象是否不相等。              |
| `bool operator<(const QElapsedTimer &lhs, const QElapsedTimer &rhs)` | 非成员操作符 | 判断第一个 `QElapsedTimer` 对象是否小于第二个。        |
| `bool operator==(const QElapsedTimer &lhs, const QElapsedTimer &rhs)` | 非成员操作符 | 判断两个 `QElapsedTimer` 对象是否相等。                |

