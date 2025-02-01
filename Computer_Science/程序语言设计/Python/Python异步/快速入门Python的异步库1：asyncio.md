# 快速入门Python的异步库：asyncio

## 异步

​	我们首先先来谈谈异步，你应该遇到过这样的场景：

> 在一个单线程中你总是需要做一些复杂的事情，但是这些复杂的事情往往可能跟我们想干的其他事情几乎只有接口上的关系！（何为接口上的关系呢：我只是希望调用这个接口，并且在完成这个工作后告诉我这一接口实行的功能返回给我的结果是如何的，而并不关心内部到底如何运作！这样的任务就是我们的目标。

​	这在涉及到界面编程场景的时候非常多，比如说我想要做耗时的网络操作，有需要实时的刷新Ui。这个时候，我们的就会希望把耗时的网络操作，或者是界面刷新分为两个线程干，但是互相不关心两者的关系（只是接口关系），面对这样的耗时的但却两者不相关的操作的时候，我们往往希望给它们进行分离。异步这一概念就是对这一场景的一个抽象。

## Python asyncio

​	Python自身就提供了一个相对完善的异步库。请看VCR。

```
import asyncio
import time

async def do_hardy_task() -> str:
    print("do hardy task started")
    print(f"task started at {time.strftime('%X')}")

    await asyncio.sleep(1)

    print(f"task finished at {time.strftime('%X')}")

    return "done!" # 这个可以是结果

async def main():
    print("Running in the top level...")
    result = await do_hardy_task()
    print("Done!")

# Start the run
asyncio.run(main())
```

​	这段程序的输出如下

```
Running in the top level...
do hardy task started
task started at 18:01:23
task finished at 18:01:24
Done!
```

​	这个程序并没有发挥真正的并发优势，但是把asyncio的关键字说明了一下：

### 1. `async` 关键字

`async` 关键字用于定义异步函数。异步函数是通过`asyncio`事件循环来调度执行的，它们不会阻塞主程序的执行。使用`async`标记函数时，它返回一个协程对象，而不是一个普通的返回值。

在代码中，`do_hardy_task`和`main`都是用`async`定义的异步函数。

- `async def do_hardy_task() -> str:`：这表示`do_hardy_task`是一个异步函数，返回一个`str`类型的结果。
- `async def main():`：这表示`main`函数也是异步的。

### 2. `await` 关键字

`await` 用来等待一个异步操作的结果。当你在异步函数中使用`await`时，它会暂停该函数的执行，直到等待的异步操作完成，然后继续执行。这个过程不会阻塞主程序的其他任务。

在这段代码中，`await asyncio.sleep(1)`使得`do_hardy_task`函数暂停1秒钟，但这期间不会阻塞其他可能的异步任务。

- `await asyncio.sleep(1)`：这是一个异步的睡眠操作，模拟了一个耗时操作（如硬性任务）。它会暂停1秒钟并释放控制权给事件循环，允许其他任务继续执行。

### 3. `asyncio.run()`

`asyncio.run()`是一个用于启动异步程序的函数。它接受一个协程作为参数，并运行事件循环直到该协程完成。调用`asyncio.run(main())`时，它启动了事件循环，执行`main()`协程，并在所有异步操作完成后关闭事件循环。

- `asyncio.run(main())`：这里会启动`main`异步函数的执行。

### 4. `asyncio.sleep()`

`asyncio.sleep()`是一个异步的睡眠函数，它不会阻塞程序的执行，而是将控制权返回给事件循环。通过这种方式，其他异步任务可以在`sleep`期间运行。

- `await asyncio.sleep(1)`：这表示当前任务将会等待1秒钟，但在此期间不会阻塞其他异步任务。

### 5. 协程

在`async`定义的函数实际上是返回一个**协程**（coroutine）（有趣的是这个更加像是一个对象）。协程是一个可暂停和恢复的函数，它可以与事件循环一起工作，通过异步的方式并行执行任务。在这段代码中，`do_hardy_task()`和`main()`都是协程。

### 程序执行流程

​	我们来看看程序实际上的执行流程是如何的：

1. 当调用`asyncio.run(main())`时，`main()`异步函数开始执行。
2. `main()`中调用了`await do_hardy_task()`，导致程序进入`do_hardy_task`函数。
3. 在`do_hardy_task`中，`await asyncio.sleep(1)`使任务暂停1秒，但在这期间可以执行其他任务。
4. 一秒钟后，`do_hardy_task`继续执行，打印出任务结束的时间，并返回结果`"done!"`。
5. `main()`接收到返回值后，打印出`"Done!"`。

这样，`asyncio`实现了异步执行，使得即使存在耗时操作，也不会阻塞程序的其他任务

## 可以被等待的异步

​	我们下面来看看那些可以被等待的异步对象。一般的我们说有三个：协程函数，任务和Future（期许啥的）。下面的部分被来自Python Documentation

### 协程

​	Python 协程属于 *可等待* 对象，因此可以在其他协程中被等待:

```
import asyncio

async def nested():
    return 42

async def main():
    # 如果我们只调用 "nested()" 则无事发生。
    # 一个协程对象会被创建但是不会被等待，
    # 因此它 *根本不会运行*。
    # nested()  # 将引发 "RuntimeWarning"。

    # 现在让我们改为等待它：
    print(await nested())  # 将打印 "42"。

asyncio.run(main())
```

- *协程函数*: 定义形式为 [`async def`](https://docs.python.org/zh-cn/3/reference/compound_stmts.html#async-def) 的函数;
- *协程对象*: 调用 *协程函数* 所返回的对象。

### 任务

​	*任务* 被用来“并行的”调度协程当一个协程通过 [`asyncio.create_task()`](https://docs.python.org/zh-cn/3/library/asyncio-task.html#asyncio.create_task) 等函数被封装为一个 *任务*，该协程会被自动调度执行:

```
import asyncio

async def nested():
    return 42

async def main():
    # 将 nested() 加入计划任务
    # 立即与 "main()" 并发运行。
    task = asyncio.create_task(nested())

    # 现在可以使用 "task" 来取消 "nested()"，or
    # 或简单地等待它直到它被完成：
    await task

asyncio.run(main())
```

### Futures

[`Future`](https://docs.python.org/zh-cn/3/library/asyncio-future.html#asyncio.Future) 是一种特殊的 **低层级** 可等待对象，表示一个异步操作的 **最终结果**。当一个 Future 对象 *被等待*，这意味着协程将保持等待直到该 Future 对象在其他地方操作完毕。在 asyncio 中需要 Future 对象以便允许通过 async/await 使用基于回调的代码。通常情况下 **没有必要** 在应用层级的代码中创建 Future 对象。Future 对象有时会由库和某些 asyncio API 暴露给用户，用作可等待对象:

```
async def main():
    await function_that_returns_a_future_object()

    # 这样也可以：
    await asyncio.gather(
        function_that_returns_a_future_object(),
        some_python_coroutine()
    )
```

一个很好的返回对象的低层级函数的示例是 [`loop.run_in_executor()`](https://docs.python.org/zh-cn/3/library/asyncio-eventloop.html#asyncio.loop.run_in_executor)。

## 任务

​	刚刚我们看到了任务这个概念，下面我们来看看常见的API。

```
import asyncio
import time

async def do_hard_task() -> str:
    print("Shell start handling hard task")

    # mulipulate the hard task
    await asyncio.sleep(5)

    return "done!"

async def main():
    print("shell depatch the task :) ")

    task = asyncio.create_task(do_hard_task())

    print("the task has been depatched")

    result = await task

    print(result)

asyncio.run(main())
```

​	我们在这里看看用到了啥。

#### `asyncio.create_task()`

- **`task = asyncio.create_task(do_hard_task())`** 使用 `asyncio.create_task()` 创建一个新的任务。这将 `do_hard_task()` 协程调度到事件循环中执行，并返回一个 `task` 对象。
- `create_task()` 会立即返回一个任务对象，而任务本身是异步执行的。注意，这个任务并不会阻塞后续代码的执行，因此它会在后台运行。

#### `await` 和任务结果

- **`result = await task`** 等待 `task` 完成，意味着程序会暂停在这里直到 `do_hard_task` 执行结束并返回结果。在这段时间内，事件循环允许其他任务运行（如果有的话）。
- `await task` 会将 `task` 的返回结果赋给 `result`，然后打印出来。

​	任务当然还可以被取消。当任务被取消时，[`asyncio.CancelledError`](https://docs.python.org/zh-cn/3/library/asyncio-exceptions.html#asyncio.CancelledError) 将在遇到机会时在任务中被引发。所以，对于用户态推荐协程使用 `try/finally` 代码块来可靠地执行清理逻辑。 对于 [`asyncio.CancelledError`](https://docs.python.org/zh-cn/3/library/asyncio-exceptions.html#asyncio.CancelledError) 被显式捕获的情况，它通常应当在清理完成时被传播。 [`asyncio.CancelledError`](https://docs.python.org/zh-cn/3/library/asyncio-exceptions.html#asyncio.CancelledError) 会直接子类化 [`BaseException`](https://docs.python.org/zh-cn/3/library/exceptions.html#BaseException) 因此大多数代码都不需要关心这一点。

​	启用结构化并发的 asyncio 组件，如 [`asyncio.TaskGroup`](https://docs.python.org/zh-cn/3/library/asyncio-task.html#asyncio.TaskGroup) 和 [`asyncio.timeout()`](https://docs.python.org/zh-cn/3/library/asyncio-task.html#asyncio.timeout)，在内部是使用撤销操作来实现的因而在协程屏蔽了 [`asyncio.CancelledError`](https://docs.python.org/zh-cn/3/library/asyncio-exceptions.html#asyncio.CancelledError) 时可能无法正常工作。 类似地，用户代码通常也不应调用 [`uncancel`](https://docs.python.org/zh-cn/3/library/asyncio-task.html#asyncio.Task.uncancel)。 但是，在确实想要屏蔽 [`asyncio.CancelledError`](https://docs.python.org/zh-cn/3/library/asyncio-exceptions.html#asyncio.CancelledError) 的情况下，则还有必要调用 `uncancel()` 来完全移除撤销状态。



# Reference

[Python 异步编程入门 - 阮一峰的网络日志 (ruanyifeng.com)](https://ruanyifeng.com/blog/2019/11/python-asyncio.html)

[协程与任务 — Python 3.13.1 文档](https://docs.python.org/zh-cn/3/library/asyncio-task.html#)