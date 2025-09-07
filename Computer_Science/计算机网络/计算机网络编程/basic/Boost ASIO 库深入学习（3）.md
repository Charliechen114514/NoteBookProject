# Boost ASIO 库深入学习（3）

## UDP简单通信导论

在继续深入前，我们不妨也来点碎碎念，因为UDP通信协议的模型与TCP是不同的，这种差异正是理解“无连接通信”的关键所在。我们下面要构建的，是一个经典的UDP通信对，UDP服务器（接收特定的消息）与UDP客户端（发送数据报文并等待可能的响应）。这将帮助我们在编程过程中更加明确目标。

UDP通信是轻量级的。UDP客户端若想发起通信，第一步同样是创建Socket套接字，但与TCP不同，UDP不建立连接，它是“无连接”的协议。客户端不需要预先连接目标地址，它只需要准备好要发送的消息，指定目标的IP地址和端口，然后就可以将数据报文（Datagram）直接发出。需要注意的是，由于UDP不保证可靠传输，因此丢包、顺序错乱或者重复发送都是可能出现的情况。

另一方面，UDP服务器的工作更像一个随时准备接收包裹的邮筒。它需要创建UDP Socket，并绑定在指定的IP和端口上（这一点和TCP服务端类似）。不过，它不需要监听或者接受连接请求，它所要做的，就是不断地接收来自任意来源的数据报。这些数据报可能来自任何客户端，彼此之间没有状态记录，因此每一条消息都应被视作独立处理。

一旦UDP服务器接收到客户端的消息，它可以选择是否回应，如果回应，那么也需要指明目标地址（通常就是消息来源）。因为UDP的“无连接”性质，每一次通信都是“即发即收”，不保证对方一定在线或一定收到。

典型UDP服务使用知名端口如53（DNS），而我们在后续的例子中将尝试使用随机端口，模拟UDP服务端和客户端之间的简单通信。

了解了这个基本模型，我们就可以借助 Boost ASIO 来尝试构建这个轻量级的UDP通信系统了。我们即将展示的代码，会用最小化的结构完成一次完整的UDP消息发送与接收过程。

## UDP客户端

​	UDP的客户端跟TCP的可以说是大差不差

```cpp
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <exception>
#include <print>

using boost::asio::ip::udp;
int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::println("Error usage!");
		return -1;
	}
	try {
		boost::asio::io_context io_context;

		udp::resolver solver(io_context);
		auto receiver_endpoint = *solver.resolve(udp::v4(), argv[1], "daytime").begin();

		udp::socket socket(io_context);
		socket.open(udp::v4());
		std::array<char, 1> send_buf = { { 0 } };
		socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

		std::array<char, 128> recv_buf;
		udp::endpoint sender_endpoint;
		socket.receive_from(
		    boost::asio::buffer(recv_buf), sender_endpoint);
		std::println("receive: {}", recv_buf.data());
	} catch (const std::exception& e) {
		std::println("Exception occurs: {}", e.what());
	}
}
```

​	值得注意的是，这里我们需要发一个空载的包刺激对方UDP服务器，这是因为UDP通信中缺乏了状态薄记，所以，我们需要自己通知对面，我们的通信开始了。当然，您可以自己设置自己的一套起始动作。来确保通信的有效性。

## UDP同步服务器

```c++
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>
#include <chrono>
#include <exception>
#include <format>
#include <print>
using namespace std::chrono;

using my_time_t = std::chrono::time_point<
    std::chrono::system_clock,
    std::chrono::nanoseconds>;
static inline std::string __make_format_date(const year_month_day& ymd,
                                             const hh_mm_ss<minutes>& time) {
	return std::format(
	    "{}-{:02}-{:02} {:02}:{:02}",
	    static_cast<int>(ymd.year()),
	    static_cast<unsigned>(ymd.month()),
	    static_cast<unsigned>(ymd.day()),
	    time.hours().count(),
	    time.minutes().count());
}
std::string
current_time() {
	using namespace std;
	using namespace std::chrono;
	const my_time_t raw_time = std::chrono::system_clock::now();
	auto now = floor<minutes>(raw_time);
	auto days_part = floor<days>(now);
	year_month_day ymd = year_month_day { days_part };

	auto time_since_midnight = now - days_part;
	hh_mm_ss time { time_since_midnight };

	return __make_format_date(ymd, time);
}
using boost::asio::ip::udp;

int main() {
	try {
		boost::asio::io_context io_context;
		udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));

		for (;;) {
			std::array<char, 1> recv_buf;
			udp::endpoint remote_endpoint;
			socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

			std::string message = current_time();

			boost::system::error_code ignored_error;
			socket.send_to(boost::asio::buffer(message),
			               remote_endpoint, 0, ignored_error);
		}
	} catch (const std::exception& e) {
		std::println("Exception occurs: {}", e.what());
	}
}
```

​	作为对称，我们在一个循环中，只是监听潜在道来的包`remote_endpoint`，这里没做校验，我们也不关心如何处理后续的远程UDP通信节点。因此这里只是一个占位符而已。

​	之后，我们粗暴的将信息直接丢给我们的客户端。

​	完成上述的代码编写之后

```
[charliechen@Charliechen build]$ sudo ./server 
[sudo] password for charliechen: 


```

```
[charliechen@Charliechen build]$ ./client 127.0.0.1
receive: 2025-06-08 12:48
[charliechen@Charliechen build]$ 
```

​	可以看到完成了一次经典的UDP通信了。

## UDP异步服务器

```c++
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>
#include <chrono>
#include <cstddef>
#include <exception>
#include <format>
#include <print>

using boost::asio::ip::udp;

using namespace std::chrono;

using my_time_t = std::chrono::time_point<
    std::chrono::system_clock,
    std::chrono::nanoseconds>;
static inline std::string __make_format_date(const year_month_day& ymd,
                                             const hh_mm_ss<minutes>& time) {
	return std::format(
	    "{}-{:02}-{:02} {:02}:{:02}",
	    static_cast<int>(ymd.year()),
	    static_cast<unsigned>(ymd.month()),
	    static_cast<unsigned>(ymd.day()),
	    time.hours().count(),
	    time.minutes().count());
}
std::string
current_time() {
	using namespace std;
	using namespace std::chrono;
	const my_time_t raw_time = std::chrono::system_clock::now();
	auto now = floor<minutes>(raw_time);
	auto days_part = floor<days>(now);
	year_month_day ymd = year_month_day { days_part };

	auto time_since_midnight = now - days_part;
	hh_mm_ss time { time_since_midnight };

	return __make_format_date(ymd, time);
}

class udp_server {
public:
	udp_server()
	    : socket(io_context, udp::endpoint(udp::v4(), 13)) {
		process_receive();
	}

	void run() {
		io_context.run();
	}

private:
	void process_receive() {
		std::array<char, 1> recv_buffer;
		socket.async_receive_from(
		    boost::asio::buffer(recv_buffer),
		    remote_endpoint,
		    [this](const boost::system::error_code& error, size_t bytes) {
			    if (error) {
				    return;
			    }

			    std::shared_ptr<std::string> message(
			        new std::string(current_time()));

			    socket.async_send_to(
			        boost::asio::buffer(*message), remote_endpoint,
			        [this, message](const boost::system::error_code&, std::size_t cnt) {
				        std::println("Process message {}, bytes cnt: {}", *message, cnt);
			        });

			    process_receive();
		    });
		;
	}

	boost::asio::io_context io_context;
	udp::socket socket;
	udp::endpoint remote_endpoint;
};

int main() {

	try {
		udp_server server;
		server.run();
	} catch (const std::exception& e) {
		std::println("Exception occurs: {}", e.what());
	}
}
```

​	这里的步骤跟我们之前做

1. 启动 UDP 服务器。
2. 通过 `async_receive_from()` 等待客户端请求。
3. 收到请求后：
   1. 构造时间字符串；
   2. 异步发送给客户端；
   3. 打印日志；
   4. 继续监听其他请求。
4. 主线程通过 `run()` 阻塞等待事件处理。

​	我们简单的抽象一下上面的代码：

```cpp
class udp_server {
public:
    udp_server()
        : socket(io_context, udp::endpoint(udp::v4(), 13))
    {
        process_receive();
    }

    void run() {
        io_context.run();
    }

private:
    void process_receive() { /* ... */ }

    boost::asio::io_context io_context;
    udp::socket socket;
    udp::endpoint remote_endpoint;
};
```

- `io_context`：事件循环核心。
- `socket`：绑定到 UDP 端口 13，用于接收和发送数据。
- `remote_endpoint`：用于记录客户端的地址与端口，便于回传消息。

------

###  构造函数：初始化与接收启动

```cpp
udp_server()
   : socket(io_context, udp::endpoint(udp::v4(), 13))
{
    process_receive();
}
```

- 创建一个监听 UDP 13 端口的 socket；
- 启动异步接收过程，等待客户端发送数据。

------

### 🔁 process_receive() 方法详解

```cpp
void process_receive() {
    std::array<char, 1> recv_buffer;
    socket.async_receive_from(
        boost::asio::buffer(recv_buffer),
        remote_endpoint,
        [this](auto& error, std::size_t bytes) {
            if (error) return;

            // 收到客户端消息后准备发送响应
            auto message = std::make_shared<std::string>(current_time());

            socket.async_send_to(
                boost::asio::buffer(*message),
                remote_endpoint,
                [this, message](auto& /*ec*/, std::size_t cnt) {
                    std::println("Process message {}, bytes cnt: {}", *message, cnt);
                });

            // 再次启动接收
            process_receive();
        });
}
```

- `recv_buffer`：申请 1 字节的接收缓冲；通常客户端只需触发一次接收，所以大小设置为 1 即可。
- `async_receive_from` 异步接收调用，完成后由 lambda 处理：
  - 若无错误，生成当前时间的字符串并包装成 `shared_ptr`，确保其在异步发送期间有效。
  - 调用 `async_send_to` 向先前的 `remote_endpoint` 回应时间信息；
  - 回调中打印发送的内容与字节数；
  - 最后重新调用 `process_receive()`，保持服务器持续接收能力。

⚠️ 每次接收成功后都会**递归启动下一次接收**，确保可持续处理多个客户端请求。

------

### ⏱️ 运行方法

```cpp
void run() {
    io_context.run();
}
```

这一调用在主线程中启动异步事件循环，直到没有待处理的操作为止（本例会一直运行，因为持续触发 `process_receive()`）。

