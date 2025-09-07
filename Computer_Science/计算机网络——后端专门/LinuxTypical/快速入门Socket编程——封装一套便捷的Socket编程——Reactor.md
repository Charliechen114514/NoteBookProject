# 快速入门Socket编程——封装一套便捷的Socket编程——Reactor 设计模式

​	我们下面来聊一聊基于Epoll的Reactor 设计模式，这里构成了笔者设计的核心思路。

​	我们可以直到**Reactor 模式**是一种典型的 **事件驱动（Event-Driven）设计模式**。我们一次性的监听多个 I/O 句柄的事件（可读、可写、异常）。这实际上是一种I/O 多路复用机制

> **I/O 多路复用机制**（如 `select`、`poll`、`epoll`）:**一个进程或线程可以同时监视多个文件描述符（File Descriptor, FD），并在其中任何一个文件描述符就绪（ready for I/O）时，得到通知并进行相应的操作，而无需阻塞在单个 I/O 操作上。**

​	当我们监听到了事件的来源的时候，我们就会Reactor **分发（dispatch）事件**到对应的 **Handler（事件处理器）**。

**一句话理解：**

> Reactor 模式中，**应用程序主动从内核查询事件，然后调用回调函数处理**。

------

## **Reactor 模式的角色**

1. **Reactor（事件分发器）**
   - 负责监听事件并分发给对应的 Handler。
2. **Handle（句柄）**
   - I/O 资源，如 `socket_fd`。
3. **Event Handler（事件处理器）**
   - 负责响应某个 I/O 事件的回调函数

------

### **Reactor 的典型工作流程**

​	在笔者之后全面的介绍代码的时候，会详细的说明，这里给出一个片段：

```cpp
void LinuxServerSocket::start_workloop(const ServerWorkers& worker) {
    internal_worker = worker;
    std::vector<epoll_event> events(max_epoll_contains);
    while (!shell_terminate) {
        int nfds = epoll_wait(epfd, events.data(), max_epoll_contains, -1);
        for (int i = 0; i < nfds; ++i) {
            int current_fd = events[i].data.fd;
            if (current_fd == socket_fd) {
                handle_new_connections(); // 新连接 -> accept_callback
            } else {
                react_clients(current_fd); // 数据 -> receiving_callback
            }
        }
    }
}
```

​	这里就是一个经典的Reactor设计模式代码的流程：

1. 注册事件：Reactor 注册 socket 和其关注的事件（如 EPOLLIN）。
2. 等待事件：调用 `epoll_wait()`（或 select/poll）。
3. 事件分发：将就绪事件分发给对应的事件处理器。
4. 执行回调：事件处理器完成业务逻辑。

​	在上面这里的 `epoll_wait()` 是 **Synchronous Event Demultiplexer**（同步事件分发器），`accept_callback` 和 `receiving_callback` 是事件处理器。

------

### **1.4 Reactor 的特点**

- **被动反应**：Reactor 是“被动”的，只能处理已就绪的事件。
- **同步 I/O**：内核只负责通知“可读/可写”，真正的 `read()/write()` 由应用程序完成。
- **适合高并发 I/O**：结合 epoll，可以处理成千上万的连接。

------

# **补充：Proactor 设计模式**

### **Proactor 的定义**

- **Proactor 模式**是一种**异步非阻塞 I/O** 模型。它的核心思想是：当 I/O 操作**完成**后，才通知应用程序，并把操作结果（包括读取的数据或写入的字节数）一并传递给应用程序。

  可以把 Proactor 模式想象成一个“送餐上门系统”：

  1. **你（应用程序）** 去餐厅点餐并付款。
  2. **老板（操作系统）** 告诉你：“饭好了会给你送过来。”
  3. **你在座位上（应用程序继续做其他事情）** 不用管。
  4. **饭好了，服务员把餐端到你面前（I/O 操作完成，操作系统通知应用程序并传递结果）**。

**一句话理解：**

> Proactor 模式中，**应用程序只提交操作请求，内核在后台完成 I/O 后直接调用回调通知**。

------

#### **核心组件：**

- **异步操作发起者 (Asynchronous Operation Initiator)**：应用程序发起异步 I/O 操作（例如，`aio_read`，在 Windows 上是 `ReadFileEx`）。
- **异步事件多路分发器 (Asynchronous Event Demultiplexer)**：操作系统内核负责管理和完成异步 I/O 操作。
- **完成处理器 (Completion Handler)**：操作系统在 I/O 操作完成后，会调用应用程序注册的这个回调函数，并将操作结果（如读取到的数据）作为参数传递给它。

#### **工作流程：**

1. 应用程序发起一个异步 I/O 操作（例如，`read` 到某个缓冲区）。
2. 操作系统内核接管这个 I/O 操作，立即返回，应用程序可以继续执行其他任务。
3. 当 I/O 操作在内核中**完全完成**后（数据已经读取到缓冲区，或者数据已经发送完毕），内核会通知应用程序。
4. 操作系统调用应用程序注册的**完成处理器**，将 I/O 操作的结果传递给它。

### **Proactor 的工作流程**

1. 应用程序发起异步操作（如 `aio_read()` 或 Windows IOCP 的 `ReadFileEx()`）。
2. 内核异步完成 I/O。
3. 内核通知应用程序（通过回调、完成端口等机制）。
4. 应用程序直接处理已完成的数据，无需再调用 `read()`。

------

### **Reactor vs Proactor 对比**

| 特点           | Reactor                    | Proactor                  |
| -------------- | -------------------------- | ------------------------- |
| **I/O 类型**   | 同步非阻塞 I/O             | 异步 I/O                  |
| **谁执行 I/O** | 应用程序主动 `read/write`  | 内核完成 I/O              |
| **触发时机**   | 通知“就绪”                 | 通知“完成”                |
| **常用平台**   | epoll (Linux)、select/poll | IOCP (Windows)、POSIX AIO |

**类比：**

- Reactor：门铃响了，你要去开门拿快递。
- Proactor：快递小哥直接把快递送进家里，你只需处理包裹。

------

#### **为什么项目选择 Reactor**

- Linux 原生提供的 `epoll` 是 **就绪通知** 模型，不会替咱们完成 `recv()`。
- Proactor 在 Linux 中实现比较复杂，需要 `io_uring` 或 POSIX AIO，而 `epoll` + Reactor 模式成熟且高效。

