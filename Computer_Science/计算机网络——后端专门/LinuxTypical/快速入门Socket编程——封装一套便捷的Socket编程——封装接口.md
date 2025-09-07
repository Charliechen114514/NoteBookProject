# 快速入门Socket编程——封装一套便捷的Socket编程——封装接口

​	结合之前的导论，理清楚了我们的基本的关系之后，我们就可以开始我们的封装了。

## 直接先看接口

```cpp
#pragma once
#include "sockets_common.hpp"
#include <functional>
#include <memory>
#include <string>
class ServerSocket;
class PassiveClientBase;
struct ServerWorkers {
	using AcceptCallback = std::function<void(PassiveClientBase*)>;
	using ReceivingCallback = std::function<void(PassiveClientBase*, const std::string& data)>;
	using CloseClientCallBack = std::function<void(PassiveClientBase*)>;
	using BroadCastProcessor = std::function<std::string(PassiveClientBase* who_broadcast, const std::string&)>;
	AcceptCallback accept_callback;
	ReceivingCallback receiving_callback;
	CloseClientCallBack close_client_callback;
	BroadCastProcessor broadcast_callback;
	bool broadcast_enabled { false };
};

struct ClientWorker {
	using ReceivingCallback = std::function<void(const std::string& str)>;
	ReceivingCallback receiving_callback;
};

class ServerSocketInterface {
public:
	ServerSocketInterface(SocketsCommon::ServerProtocolSettings
	                          settings);
	~ServerSocketInterface();
	/**
	 * @brief listen to the port and ready to make server
	 *
	 * @param port
	 * @param max_accept
	 * @param settings
	 */
	void listen_at_port(const int port, const int max_accept,
	                    const ServerWorkers& worker);

private:
	std::unique_ptr<ServerSocket> serverImpl;
};

class ClientSocket;
class ClientInterface {
public:
	ClientInterface(const SocketsCommon::ClientProtocolSettings& settings);
	~ClientInterface();
	void connect_to(const std::string& host, const int target_port);
	void async_send_raw_data(const std::string& datas);
	void async_receive_from(const ClientWorker& worker);
	void close_self();

private:
	ClientInterface(const ClientInterface&) = delete;
	ClientInterface& operator=(const ClientInterface&) = delete;
	std::unique_ptr<ClientSocket> clientImpl;
};
```

​	一些朋友可能会感到困惑，为什么要这样设计接口呢？好处是什么？

## 异步回调的Reactor分发

​	我们先从最经典的两个大头说起。很快你会注意到，

```cpp
struct ServerWorkers {
	using AcceptCallback = std::function<void(PassiveClientBase*)>;
	using ReceivingCallback = std::function<void(PassiveClientBase*, const std::string& data)>;
	using CloseClientCallBack = std::function<void(PassiveClientBase*)>;
	using BroadCastProcessor = std::function<std::string(PassiveClientBase* who_broadcast, const std::string&)>;
	AcceptCallback accept_callback;
	ReceivingCallback receiving_callback;
	CloseClientCallBack close_client_callback;
	BroadCastProcessor broadcast_callback;
	bool broadcast_enabled { false };
};

struct ClientWorker {
	using ReceivingCallback = std::function<void(const std::string& str)>;
	ReceivingCallback receiving_callback;
};
```

​	是一簇经典的回调函数结构体，封装了我们打算做的一部分业务逻辑，给他解耦合出来（嗯，一部分人开源的socket server client框架是业务写死的，不太好评价）

​	这样的话，我们就可以专心的搞我们的异步网络通信框架了。也不需要进行啥其他工作。或者说：

1. 当 epoll/select 检测到某个 fd 有可读事件时，底层读取数据。
2. 数据读入 `std::string buffer` 后，调用 `workers.receiving_callback(client, buffer)`。
3. 业务逻辑通过 Lambda 或绑定函数立即处理数据。

​	这种机制是典型的 **Reactor 模式**：事件循环检测事件 → 分发给回调函数。

## pImpl法包装

​	我们下面聊的是pImpl法 + 基于RAII智能指针包装的资源管理法。结合导论，咱们就知道Windows和Linux的Socket编程的接口是不一致的，为了保证我们的上层使用的代码总是不变，显然我们就是需要pImpl办法进行包装。

```c
class ServerSocket;
class ServerSocketInterface {
public:
	ServerSocketInterface(SocketsCommon::ServerProtocolSettings
	                          settings);
	~ServerSocketInterface();
	/**
	 * @brief listen to the port and ready to make server
	 *
	 * @param port
	 * @param max_accept
	 * @param settings
	 */
	void listen_at_port(const int port, const int max_accept,
	                    const ServerWorkers& worker);

private:
	std::unique_ptr<ServerSocket> serverImpl;
};

class ClientSocket;
class ClientInterface {
public:
	ClientInterface(const SocketsCommon::ClientProtocolSettings& settings);
	~ClientInterface();
	void connect_to(const std::string& host, const int target_port);
	void async_send_raw_data(const std::string& datas);
	void async_receive_from(const ClientWorker& worker);
	void close_self();

private:
	ClientInterface(const ClientInterface&) = delete;
	ClientInterface& operator=(const ClientInterface&) = delete;
	std::unique_ptr<ClientSocket> clientImpl;
};

```

​	ServerSocket和ClientSocket才是真正的工作类，上面的其他接口不过是我们希望使用我们框架的人需要用何种接口完成我们的工作罢了。

> 为什么pImpl？
>
> - **隐藏实现细节**：头文件只暴露接口，不暴露实现类的成员，减少编译依赖，提高封装性。
> - **降低编译时间**：改动 `.cpp` 内部实现不会引起依赖文件的重新编译。
> - **内存安全**：自动管理实现类的生命周期。与 `unique_ptr` 配合，自动释放资源。
> - **清晰的 API**：外部只看到 `ClientInterface` 的方法，不关心 `ClientSocket` 内部结构。
> - **实现可替换**：你可以替换 `ClientSocket` 的实现（比如 `epoll` → `IOCP`），对外接口不变。

​	现在我们的接口变得非常的清晰，编程起来就是这样的体验：

### Server端

```cpp
#include "passive_client_socket.hpp"
#include "sockets_common.hpp"
#include "sockets_operation.h"
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/socket.h>
int main() {
	SocketsCommon::ServerProtocolSettings settings;
	settings.settings = {};
	settings.epoll_max_contains = 64;
	settings.buffer_length = 1024;
	ServerWorkers workers;
	workers.broadcast_enabled = true;
	workers.broadcast_callback = [](PassiveClientBase* sender, const std::string& data) -> std::string {
		LinuxLightPassiveClient* clients = dynamic_cast<LinuxLightPassiveClient*>(sender);
		return "[" + std::to_string(clients->passive_client_fd) + "]: " + data;
	};
	workers.accept_callback = [](PassiveClientBase* base) {
		LinuxLightPassiveClient* clients = dynamic_cast<LinuxLightPassiveClient*>(base);
		std::string echos = "Hello from server!";
		::send(clients->passive_client_fd, echos.data(), echos.size(), 0);
	};
	workers.close_client_callback = [](PassiveClientBase* base) {
		LinuxLightPassiveClient* clients = dynamic_cast<LinuxLightPassiveClient*>(base);
		std::cout << "Ok we close a client! with internal handle " << clients->passive_client_fd << std::endl;
	};
	workers.receiving_callback = [](PassiveClientBase* clients, std::string datas) {
		datas.resize(datas.size() + 1);
		datas[datas.size() - 1] = '\0';
		LinuxLightPassiveClient* _clients = dynamic_cast<LinuxLightPassiveClient*>(clients);
		std::cout << "Ok we have receive data from: " << datas << " from clients: " << _clients->passive_client_fd << std::endl;
		std::string echos = "Receiving datas: " + datas;
		::send(_clients->passive_client_fd, echos.data(), echos.size(), 0);
	};

	try {
		ServerSocketInterface interface { settings };
		interface.listen_at_port(12345, 5, workers);
	} catch (std::exception& e) {
		std::cerr << e.what();
	}

	while (1)
		;
}
```

### Client端

```cpp
#include "sockets_common.hpp"
#include "sockets_operation.h"
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

int main() {
	// try connect
	SocketsCommon::ClientProtocolSettings settings;
	settings.settings = {};
	settings.epoll_max_contains = 64;
	settings.buffer_length = 1024;
	ClientWorker worker;
	int i = 0;
	worker.receiving_callback = [&i](const std::string& value) {
		std::cout << "[" << i << "] " << value << std::endl;
		i++;
	};

	try {
		ClientInterface interface { settings };
		interface.connect_to("127.0.0.1", 12345);
		interface.async_send_raw_data("Hello You!");
		interface.async_receive_from(worker);
		// interface.close_self();
		std::string local;
		while (std::getline(std::cin, local)) {
			interface.async_send_raw_data(local);
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
```

​	嗯，看起来好多了。