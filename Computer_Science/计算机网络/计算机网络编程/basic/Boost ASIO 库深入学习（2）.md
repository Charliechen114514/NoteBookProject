# Boost ASIO 库深入学习（2）

## 构建简单的TCP协议通信样例

​	这一片博客承接上面我们讨论的基本的异步编程，来进一步好好了解一下我们如何使用Boost ASIO完成对基于TCP协议栈的CS通信模型。

## TCP简单通信导论

​	在我们开始之前，有必要开始一点简单的碎碎念，这个碎碎念是我们下面编程的一个重要的抓手。那就是理解我们的TCP通信协议的通信模型。这里我们说，我们需要构建的是经典的服务器（提供特定的服务）和经典的客户端（请求服务器的服务和接受服务器的服务）

​	为了简单起见，我们聊聊最简单的模型。

​	TCP客户端想要发起一次通信，首先第一步就是创建基本的Socket套接字，既然是TCP模型，那我们说，我们就选用TCP协议作为我们通信的支柱。这个协议要求我们提供服务器所在的IP和端口以供告知Socket如何连接对象。另一方面，TCP作为一个经典的有状态的通信协议，我们自然在连接成功之后，就可以进行持久的序列化的通信（关于TCP通信的细节这里不再赘述，感兴趣的朋友可以参考《计算机网络自顶向下》或者是更进一步的《TCP/IP详解》进一步理解）。

​	TCP服务端想要成功运作起来，成为一个TCP服务端，他就必须创建基本的Socket套接字（这个没有任何疑问），然后向操作系统申请绑定的IP和端口，一般而言，我们接下来的通信模型要求我们的通信在一个子网中，我们一般会选择绑定到可以被寻找到的（是的，对于公网的服务器，则是使用字符串DNS名称与可访问的IP对组成，对于局域网，则是要求同属于一个子网的IP方便客户端进行访问）的IP和端口。TCP的知名端口号是13号，因此我们稍后的样例中就会尝试绑定13号端口。接下来就是服务器轮循的接受潜在的远程客户端请求。现在双方就进入了通信环节。通信结束，可能是客户端自己主动断开连接，亦或者是服务器结束提供服务不再广播服务。

​	知晓这个事情，我们下面就可以尝试使用Boost ASIO搭建完成上面的模型了。

## 构建TCP客户端

```cpp
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <exception>
#include <iostream>
#include <ostream>
using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	// check arguments to see where to query the server
	if (argc != 2) {
		std::cout << "Error usage: " << argv[0] << " <host>";
		return 1;
	}

	try {
		// announced the io context for the run sessions
		boost::asio::io_context io;
		// if we are providing a string, consider it is DNS parsable,
         // normally we will get a locatable ip
		tcp::resolver resolver(io);
		tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

		tcp::socket socket_type(io);
        // connect to the server endpoint
		boost::asio::connect(socket_type, endpoints);

		while (1) {
			std::array<char, 128> buf;
			boost::system::error_code error;
			// read some read sessions of the buffer
			size_t len = socket_type.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::string res = buf.data();
             // get the message from remote
			std::cout << res << std::endl;
		}

	} catch (const std::exception& e) {
        // exception occurs, demos print the sessions and quit the demo
		std::cout << e.what() << std::endl;
	}
}
```

## 构建TCP同步服务器

```cpp
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <chrono>
#include <format>
#include <iostream>
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

int main() {
	using boost::asio::ip::tcp;
	try {
		boost::asio::io_context io_context;

		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

		for (;;) {
			tcp::socket socket(io_context);
			acceptor.accept(socket);

			std::string message = current_time();

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
```

​	抛开笔者对我们当前时间的构建，实际上服务器端的代码非常的简单，acceptor就是我们的服务器，在一个巨大的循环中，我们周而复始的接受潜在的客户端的请求，把信息进行交付。

​	我们编译代码，首先启动服务器（13号端口需要权限才能占用）

```bash
[charliechen@Charliechen build]$ sudo ./server 
[sudo] password for charliechen: 
# here the server works, listen the remote client request
```

​	下一步就是开一个客户端

```
[charliechen@Charliechen build]$ ./client 127.0.0.1
2025-06-08 11:00
```

​	很好，我们接受到了结果！

## 异步的TCP服务器

​	但是你很快会注意到，我们有大量的时间阻塞在了循环等待客户端中，仔细想想，我们完全可以采用一种更加合理的异步的方式，对于没有客户端到来的时候，我们可以做其他的事情，可以睡眠等等让出CPU做其他的事情。

​	我们下面就用更加激进的异步方式来重写我们的TCP服务器

```c++
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <chrono>
#include <cstddef>
#include <format>
#include <memory>
#include <print>
#include <thread>
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

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
	using pointer = std::shared_ptr<tcp_connection>;

	static pointer create(boost::asio::io_context& context) {
		return pointer(new tcp_connection(context));
	}

	boost::asio::ip::tcp::socket& get_socket() {
		return pvt_socket;
	}

	void process_server() {
		std::string message = current_time();
		boost::asio::async_write(
		    pvt_socket, boost::asio::buffer(message),
		    [](const boost::system::error_code& ec, size_t bytes_written) {
			    std::println("We have processed: {} bytes", bytes_written);
		    });
	}

private:
	tcp_connection(boost::asio::io_context& io_context)
	    : pvt_socket(io_context) {
	}

	boost::asio::ip::tcp::socket pvt_socket;
};

using boost::asio::ip::tcp;
class tcp_server {
public:
	tcp_server()
	    : acceptor(io_context,
	               tcp::endpoint(tcp::v4(), 13)) {
		run_acceptable();
	}

	void run() {
		io_context.run();
	}

private:
	void run_acceptable() {
		tcp_connection::pointer new_connections = tcp_connection::create(io_context);
		acceptor.async_accept(new_connections->get_socket(), std::bind(&tcp_server::async_accept_callback, this, new_connections, boost::asio::placeholders::error));
	}

	void async_accept_callback(tcp_connection::pointer new_connection,
	                           const boost::system::error_code& error) {
		if (!error) {
			new_connection->process_server();
		}

		run_acceptable(); // run again
	}

	boost::asio::io_context io_context;
	tcp::acceptor acceptor;
};

int main() {
	try {
		tcp_server server;
		server.run(); // force local run
	} catch (std::exception& e) {
		std::println("Error occurs: {}", e.what());
	}

	return 0;
}
```

`tcp_connection` 类封装了每一个客户端的连接。

```cpp
class tcp_connection : public std::enable_shared_from_this<tcp_connection>
```

##### 关键成员：

- `pvt_socket`：`boost::asio::ip::tcp::socket`，对应一条客户端连接。
- `process_server()`：通过异步写函数 `boost::asio::async_write()` 把时间写到客户端 socket。
- `create()`：用 `make_shared` 创建 shared_ptr 实例（注意构造函数是私有的）。

##### 异步写入部分：

```cpp
boost::asio::async_write(
    pvt_socket,
    boost::asio::buffer(message),
    [](const boost::system::error_code& ec, size_t bytes_written) {
        std::println("We have processed: {} bytes", bytes_written);
    });
```

注意：这里用了 lambda 作为回调，处理写完成后的通知。

------

#### 3. `tcp_server` 类

这个类是**服务器主体**，负责监听端口，接受新连接。

##### 关键成员：

- `boost::asio::io_context io_context`：事件循环核心；
- `tcp::acceptor acceptor`：监听 TCP 端口（本程序监听端口 13）；
- `run()`：调用 `io_context.run()` 启动事件循环；
- `run_acceptable()`：开始异步接受连接。

##### 接收连接逻辑：

```cpp
void run_acceptable() {
	tcp_connection::pointer new_connections = tcp_connection::create(io_context);
	acceptor.async_accept(
		new_connections->get_socket(),
		std::bind(&tcp_server::async_accept_callback, this, new_connections, boost::asio::placeholders::error));
}
```

这一步发起异步接受，等客户端连上后，自动回调 `async_accept_callback()`。

##### 回调函数逻辑：

```cpp
void async_accept_callback(tcp_connection::pointer new_connection,
                           const boost::system::error_code& error) {
	if (!error) {
		new_connection->process_server(); // 发送时间
	}
	run_acceptable(); // 再次等待下一个连接
}
```

- 如果没有错误：说明新连接建立了，开始发送时间；
- 然后递归调用 `run_acceptable()` 继续监听新连接。