# Boost ASIO 库深入学习（1）

## 前言

​	这段时间准备专攻网络编程，因此，这里打算稍微提炼一下Boost ASIO文档。整理一些学习笔记。

## ASIO需要从异步说起

​	这里的ASIO中的AS就是异步的意思，为什么我们常用的网络编程需要考虑异步呢？我们知道，以简单的一次国内搜索引擎访问的时间往返RTT为例子，我们的度量单位一般是毫秒，别看毫秒很短暂，这个足够计算机做极端多的事情了（想一想一个寄存器的存储往往是几十到几百纳秒，中间的数量级差的是百万倍），一些长途通信可能还会更长，因此，为了保证我们的计算机的利用效率提高，我们是有必要先掌握异步编程，之后再去搭建网络编程的脚手架的。

​	基于这个思想，我们就需要从boost asio的基本的几个概念入手（当然，如果你很着急，可以直接从笔者后面的阐述TCP/IP服务器搭建的地方先看，不懂了再回来翻这里的东西）

## ASIO异步编程的一个重要工具：定时器

### 同步定时器与异步定时器

​	为了体现我们的异步编程的概念，咱们需要从它的对立概念，同步入手。

> 在计算机和程序设计领域，“同步”指的是在执行某项操作时，调用方**必须等待该操作完成后**才能继续执行后续步骤。也就是说，当你发出请求或调用某个函数时，程序会被阻塞，直到结果返回或任务结束才能继续向下运行。
>
> 与此相对，“异步”则允许调用方在发出请求后立即继续执行后续逻辑，而无需等待该请求完成。异步机制通常依赖回调函数、事件驱动或未来／Promise 等模式，在后台并行或分离线程中处理耗时任务，任务完成时再通知主流程拿到结果。这样可以提高程序的响应性和资源利用率，避免界面卡死或请求堵塞。

```cpp
#include <bits/chrono.h>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <print>
using namespace std::chrono_literals;

int main() {
	boost::asio::io_context io_context;	// 我们需要一个新东西，IO上下文
	boost::asio::steady_timer t(io_context, 5s); // 我们定义了一个定时器，定时5s
	t.wait();	// 阻塞等待（tips: asio中所有的异步操作的名称都有async的前缀）
	std::print("Hello, world!\n"); // 这里，我们期待的现象是等待5s后打印Hello, world!
}
```

> 笔者这里为了方便大伙进行快速的测试，提供一个简单的CMake构建脚本，大家自行参考修正
>
> ```cmake
> cmake_minimum_required(VERSION 3.10)
> set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
> project(boost_asio_test)
> set(CMAKE_CXX_STANDARD 23)
> set(CMAKE_CXX_STANDARD_REQUIRED ON)
> find_package(Boost REQUIRED CONFIG COMPONENTS system)
> add_executable(boost_asio_test main.cpp)
> target_include_directories(boost_asio_test PRIVATE ${Boost_INCLUDE_DIRS})
> target_link_libraries(boost_asio_test PRIVATE Boost::system)
> ```

​	如果喜欢先动手的兄弟们自己直接试着跑一下上后面的程序就OK了，我们下面来慢慢讨论这个程序展现出来的一些基础的细节。

> Boost文档：所有使用 asio 的程序都需要至少一个 I/O 执行上下文，例如 io_context 或 thread_pool 对象。I/O 执行上下文提供对 I/O 功能的访问。

​	这个IO Context经过笔者之前的异步编程经验，他就是Boost ASIO可以做到异步的一个重要的保证工具。我们可以把 IO Context想象成一个无限循环的任务队列，它不断地检查是否有已完成的异步操作或者新提交的任务，并将这些事件分发给对应的处理函数。也就是说，他是那个幕后默默无闻的监听者，他保证我们所有期待异步的组件只需要挂载到它身上，我们就把我们的功能组件挂载到了这个异步上下文中。换而言之——我们可以做到毫无心智负担的做异步编程。

​	尽管我们这里是同步的例子，但是在这里他出现了，是因为下面我们的Boost的定时器对象需要指定一个IO上下文，嗯很，那就是`boost::asio::steady_timer`了

```
boost::asio::steady_timer t(io_context, 5s);
```

> 一些细节文档：[steady_timer](https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/steady_timer.html)
>
> 计时器始终处于两种状态之一：“已过期”或“未过期”。如果对已过期的计时器调用 steady_timer::wait() 函数，它将立即返回。

​	这里用到的小trick是使用了下chrono的字面量，这里直接填写了5s，嗯，这没啥特殊的。之后就是简单的等待5s后，打印Hello, world。可以看到，这里我们的程序就直接阻塞住了，啥也不动弹！这就像是我们做网络请求那样，有大量的，不确定的时间需要我们等待任务结束后返回。非常多的时候，我们并不希望程序就这样卡在这里，啥也不动弹，我们希望把这部分由于耗时IO造成的CPU利用率低下带来的问题解决掉，这就是我们的下面计划做的事情。

​	非常好，我们下面就来使用一下一个简单的定时器异步回调定时功能。

```cpp
#include <bits/chrono.h>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <ostream>
#include <print>
using namespace std::chrono_literals;

static bool finish_fuzy_work = false;
void process_late_work(const boost::system::error_code& ec [[maybe_unused]]) {
	std::print("Time is up! quit the session\n");
	finish_fuzy_work = true;
}

int main() {
	boost::asio::io_context io_context;
	boost::asio::steady_timer t(io_context, 5s);
	t.async_wait(&process_late_work);
	std::println("Hey I am wondering...");
	::sleep(1);
	std::println("Oh I need some working else...");
	::sleep(1);
	io_context.run();
}
```

​	您可以尝试运行一下这个程序，这里的async_wait是一种，我之前说过的——异步的等待，换而言之，这里的等待不会阻塞我们程序的运行，但是代价是必须要让我们的io_context这个IO事件循环工作起来，不然的话还是会失效的。

> 有Qt开发经验的朋友可以类比一下事件循环的exec机制，这表达的就是一个意思。

​	asio 库保证完成处理程序只会从当前正在调用 boost::asio::io_context::run() 的线程中调用。因此，除非调用 boost::asio::io_context::run() 函数，否则异步等待完成的完成处理程序将永远不会被调用。boost::asio::io_context::run() 函数在**仍有“工作”要做时也会继续运行**。在本例中，工作是异步等待计时器，因此调用将在计时器到期且完成处理程序返回之前不会返回。

​	我们需要记住的是，io_context是有自己检查的IO工作清单的，换而言之，如果发现没有任何IO任务的工作的话，他自己就会清理自己然后做退出。

### 扩展我们的异步回调能力——讨论带参数的回调函数需要如何传递

​	还有一些回调函数我们可能希望是带有参数的，这个事情也很简单，熟悉C++11的朋友可能会知道std::bind的方法来将参数绑定到我们的函数上。

```c++
#include <bits/chrono.h>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/detail/error_code.hpp>
#include <functional>
#include <print>
using namespace std::chrono_literals;

void delay_steps(
    const boost::system::error_code& ec,
    boost::asio::steady_timer& invokee_timer, int& cnt) {
	if (cnt <= 5) {
		std::println("Current count is {}", cnt);
		cnt++;
		invokee_timer.expires_at(
		    invokee_timer.expiry() + 1s); // 延长1s后再次回调
		invokee_timer.async_wait( // 继续等待
		    std::bind(delay_steps,
		              boost::asio::placeholders::error,
		              std::ref(invokee_timer), std::ref(cnt)));
	}
}

int main() {
	boost::asio::io_context io;
	boost::asio::steady_timer timer(io, std::chrono::seconds(1));
	int cnt = 0;
	timer.async_wait(
	    [&timer, &cnt](const boost::system::error_code& ec) {
		    delay_steps(ec, timer, cnt);
	    });
	io.run();
	std::println("Final count is {}", cnt);
	return 0;
}
```

​	这个程序开始有一点复杂了，为此，我们打算的就是这样的，cnt增加，一直到我们的cnt到达6的时候，我们才不会进一步回调，这样的话我们就能看到这个现象

```
Current count is 0
Current count is 1
Current count is 2
Current count is 3
Current count is 4
Current count is 5
Final count is 6
```

​	std::ref的出现是因为我们的std::bind的默认行为是拷贝而不是传递引用。

## 整理我们所学：真正的异步封装

> Tips:笔者认为ASIO样例的封装不够彻底，这里笔者自己设计了一个小小的封装。

> 目的，封装一个IOExecutor类，内部完成一些独立的打印任务，需要注意的是，我们最终的效果是这样的，调用方只需要构造对象，然后做其他事情即可。
>
> 要求的效果：
>
> ```
> Waiting unfinished IO Tasks
> Get the cnt value: 0
> Get the cnt value: 0
> Get the cnt value: 1
> Get the cnt value: 1
> Get the cnt value: 2
> Get the cnt value: 2
> Get the cnt value: 3
> Get the cnt value: 3
> Get the cnt value: 4
> Get the cnt value: 4
> Get the cnt value: 5
> Get the cnt value: 5
> Get the cnt value: 6
> Get the cnt value: 6
> Get the cnt value: 7
> Get the cnt value: 7
> Get the cnt value: 8
> Get the cnt value: 8
> Get the cnt value: 9
> Get the cnt value: 9
> IO Task finished!
> ```
>
> 其中这里是对两个独立变量进行自增后停止。每秒自增一次。
>
> 调用方代码：
>
> ```
> int main() {
> 	IOExecutor iOExecutor;
> }
> ```

​	这里无非就是将我们的之前的工作给封装起来，这里就直接给出笔者的实现了

```cpp
class IOExecutor {
public:
	IOExecutor()
	    : task1(io_context, 1s)
	    , task2(io_context, 1s) {
		/* start a thread immediately to listen the async io task */
		io_context_thread = std::thread([this]() {
			io_context.run();
			std::println("IO Task finished!");
		});

		task1.async_wait(std::bind(
		    &IOExecutor::process_processings, this,
		    boost::asio::placeholders::error,
		    std::ref(task1), std::ref(cnt1)));

		task2.async_wait(std::bind(
		    &IOExecutor::process_processings, this,
		    boost::asio::placeholders::error,
		    std::ref(task2), std::ref(cnt2)));
	}

	~IOExecutor() {
		std::println("Waiting unfinished IO Tasks");
		io_context_thread.join();
	}

private:
	void process_processings(
	    const boost::system::error_code& ec,
	    boost::asio::steady_timer& timer, int& cnt) {
		if (cnt < 10) {
			std::println("Get the cnt value: {}", cnt);
			++cnt;
			timer.expires_at(timer.expiry() + boost::asio::chrono::seconds(1));

			timer.async_wait(std::bind(&IOExecutor::process_processings, this,
			                           boost::asio::placeholders::error, std::ref(timer), std::ref(cnt)));
		}
	}

	std::thread io_context_thread;
	boost::asio::io_context io_context;
	boost::asio::steady_timer task1;
	boost::asio::steady_timer task2;
	int cnt1 = 0;
	int cnt2 = 0;
};
```

​	但是如你所见，如果我们想要访问的是同一个变量做递增呢？或者说，我们希望让我们的两个异步IO任务互斥，保证不会并发的访问，这该如何做呢？

​	实际上笔者不太喜欢boost asio给出的方案，他是使用一个互斥执行文作为锁来做到现程安全的。

```c
//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <functional>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

class printer
{
public:
  printer(boost::asio::io_context& io)
    : strand_(boost::asio::make_strand(io)),
      timer1_(io, boost::asio::chrono::seconds(1)),
      timer2_(io, boost::asio::chrono::seconds(1)),
      count_(0)
  {
    timer1_.async_wait(boost::asio::bind_executor(strand_,
          std::bind(&printer::print1, this)));

    timer2_.async_wait(boost::asio::bind_executor(strand_,
          std::bind(&printer::print2, this)));
  }

  ~printer()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void print1()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 1: " << count_ << std::endl;
      ++count_;

      timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

      timer1_.async_wait(boost::asio::bind_executor(strand_,
            std::bind(&printer::print1, this)));
    }
  }

  void print2()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 2: " << count_ << std::endl;
      ++count_;

      timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

      timer2_.async_wait(boost::asio::bind_executor(strand_,
            std::bind(&printer::print2, this)));
    }
  }

private:
  boost::asio::strand<boost::asio::io_context::executor_type> strand_;
  boost::asio::steady_timer timer1_;
  boost::asio::steady_timer timer2_;
  int count_;
};

int main()
{
  boost::asio::io_context io;
  printer p(io);
  std::thread t([&]{ io.run(); });
  io.run();
  t.join();

  return 0;
}
```

​	这里简单的说一下方案：`boost::asio::strand<boost::asio::io_context::executor_type>`是一个同步的IO上下文，它确保在多线程环境下，多个异步操作的回调能够按照提交顺序串行执行，从而避免竞态条件和数据竞争。简单来说，`strand` 就像是一条单独的执行路径，无论你有多少个线程共同调用 `io_context.run()`，只要把任务投递到同一个 `strand`，这些任务就会一个接一个地完成，不会出现并行执行导致的互相干扰。当你用 `boost::asio::io_context` 驱动异步操作时，它会将完成的事件分发给对应的回调。若此时有多个工作线程在调用 `io_context.run()`，同一个 socket 的读取和写入回调极有可能被不同线程并行调用。如果回调里需要修改某些共享状态，就必须自己在回调中加锁或使用其他同步手段。而通过 `strand`，你只需将回调包装到同一个 `strand` 上，就能保证这些回调永远不会并发执行，从而简化了线程安全的管理。

​	在代码层面，`strand` 的定义通常是这样写的：

```cpp
boost::asio::io_context io;
using Executor = boost::asio::io_context::executor_type;
boost::asio::strand<Executor> strand(io.get_executor());
```

​	这里 `io.get_executor()` 返回一个与 `io_context` 绑定的执行器，作为 `strand` 的基础。之后，无论是通过 `async_read`、`async_write` 还是定时器的 `async_wait`，你都可以传入这个 `strand`，让所有回调都排队在同一“轨道”上执行。

​	举个简单示例来说明。假设你有一个定时器和一个网络读取操作，都需要修改同一个计数器。如果直接在它们的回调里修改，就需要在回调函数内部使用互斥量；而借助 `strand`，你只需这样写：

```cpp
boost::asio::steady_timer timer(io, std::chrono::seconds(1));
timer.async_wait(
    boost::asio::bind_executor(strand,
        [](const boost::system::error_code& ec){
            ++shared_counter;
        }
    )
);
socket.async_read_some(buffer,
    boost::asio::bind_executor(strand,
        [](const boost::system::error_code& ec, std::size_t bytes){
            ++shared_counter;
        }
    )
);
```

​	在这个例子里，无论定时器回调和网络读取回调哪个先完成，最终对 `shared_counter` 的增操作都不会并发执行，从而消除了数据竞争的风险。