# 快速入门Socket编程——封装一套便捷的Socket编程——导论

## 前言

​	这里是笔者打算做的Socket编程的第二部分，也就是核心的讨论我们Socket编程本身。

## 导论

​	我们知道，一个经典的服务器套接字的处理流程是如下的：

1. 创建一个指定传输层和网络层协议的套接字（socket）
2. 申请和绑定操作系统到指定的端口上（bind）
3. 运行使能申请到的资源，也就是监听（listen）
4. 接受和开启对客户端之间的通信（accept后做read && write。完成业务后如果需要关闭则关闭之）

​	对于客户端，事情就会简单一些，我们只需要创建套接字（socket）后指定要连接的远程对象就好（connect），之后就可以跟服务器之间做IO通信了。

​	那么，我们就是准备好做封装。封装之前就需要了解一下基本的系统API，这里需要注意的是，我们只讨论Linux系列的Socket API，尽管Windows在一定层次上对我们的Socket编程接口存在兼容，但是仍有不少的差距（比如说必须加载Socket编程库，完事后还有Cleanup，关闭套接字的API也跟Linux的存在差距）

## socket创建一个套接字

```c
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```

​	这个API实际上就是创建了一个指定了IP版本协议，传输层协议簇和传输层协议的API，

​	domain参数描述的是我们的IP网络层协议采用的决定，这个参数指定了套接字使用的**地址族**（Address Family），它决定了套接字可以与哪种类型的网络进行通信。最常见的选项有：

- **`AF_INET`**：用于 **IPv4** 协议。这是目前最常用的选项，它允许您使用 32 位的 IP 地址进行通信。
- **`AF_INET6`**：用于 **IPv6** 协议。如果您需要使用 128 位的 IP 地址，则应选择此选项。
- **`AF_UNIX`**：用于 **本地进程间通信**（IPC）。它不涉及网络，而是在同一台机器的不同进程间进行通信，效率更高。

​	一般而言，我们会采用的是AF_INET，这个我想大家最熟悉。

​	type定义了套接字的**服务类型**，也就是数据传输的方式。这里说的是传输层我们采纳的协议控制。

- **`SOCK_STREAM`**：**流式套接字**。它提供**可靠的、面向连接的**通信服务，使用 **TCP** (Transmission Control Protocol) 协议。数据会按顺序、无差错地传输，适用于网页浏览、文件传输等需要高可靠性的场景。（面向连接的）
- **`SOCK_DGRAM`**：**数据报套接字**。它提供**不可靠的、无连接的**通信服务，使用 **UDP** (User Datagram Protocol) 协议。数据报可能会丢失、重复或乱序到达，但它具有低延迟的特点，适用于实时音视频、在线游戏等对实时性要求高但允许少量数据丢失的场景。（面向数据的）
- **`SOCK_RAW`**：**原始套接字**。这种类型的套接字允许您直接访问 IP 层，可以自己构造 IP 数据包，常用于网络协议分析工具（如 `ping`）或一些特殊的网络应用。

​	对于protocol这个参数用于指定在特定的协议族和套接字类型下的具体协议。通常情况下，咱都是将其设置为 `0`。

当 `protocol` 为 `0` 时，系统会根据 `domain` 和 `type` 的组合**自动选择**最合适的默认协议。例如：

- `socket(AF_INET, SOCK_STREAM, 0)`：系统会自动选择 **TCP** 协议。
- `socket(AF_INET, SOCK_DGRAM, 0)`：系统会自动选择 **UDP** 协议。

只有在某些特殊情况下（例如使用 `SOCK_RAW`），您才需要显式指定协议编号。

## bind监听一个端口

​	bind在我导论的时候就说过，实际上就是申请且绑定应用程序需要的端口。它负责将一个创建好的套接字（Socket）与一个特定的**本地 IP 地址和端口号**关联起来。简单来说，**就是给你的套接字在网络世界中“分配一个门牌号”。**

​	

```c
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

​	bind函数的接口比较复杂，第一个填入的就是套接字的文件描述符，这个没啥可说的，因为我们就是需要我们的套接字具备可用的端口。

​	需要知道的是这类API都会返回负数表示失败，所以可以检查一下，这个函数很容易失败，因为我们要是退出服务的时候没有正确的释放端口资源（或者说，存在比较长的TIME_WAIT的端口），就会没办法进行再次绑定。

​	`struct sockaddr *addr`是一个指向 `struct sockaddr` 类型常量的指针。`struct sockaddr` 是一个通用的套接字地址结构体，但它是一个**泛型结构**，实际使用中，我们通常会将其转换为更具体的地址结构体，例如：

- **`struct sockaddr_in`**：用于 **IPv4** 地址。
- **`struct sockaddr_in6`**：用于 **IPv6** 地址。
- **`struct sockaddr_un`**：用于 **UNIX 域套接字**（本地进程间通信）。

这个结构体中包含了我们希望绑定的 **IP 地址**和**端口号**。

```c
#include <netinet/in.h> // 包含 sockaddr_in 的定义
#include <arpa/inet.h>  // 包含 inet_addr() 和 htons()

struct sockaddr_in {
    sa_family_t    sin_family; // 地址族，通常设置为 AF_INET
    in_port_t      sin_port;   // 端口号，必须是网络字节序
    struct in_addr sin_addr;   // IP 地址，必须是网络字节序
    // char           sin_zero[8]; // 填充字节，通常不需要显式设置
};
struct in_addr {
    in_addr_t s_addr; // 32位IPv4地址
};
```

在设置 `sin_port` 和 `sin_addr` 时，请务必注意**字节序转换**。网络上的数据传输通常使用**网络字节序**（大端字节序），而我们的主机可能使用**主机字节序**（大端或小端）。为了确保不同系统间的兼容性，必须进行转换：

- **`htons()`** (host to network short): 将主机字节序的短整型（通常是端口号）转换为网络字节序。
- **`htonl()`** (host to network long): 将主机字节序的长整型（通常是 IP 地址）转换为网络字节序。
- **`inet_addr()`** 或 **`inet_pton()`**: 将点分十进制的 IP 地址字符串转换为网络字节序的二进制形式，并存储到 `in_addr.s_addr` 中。

​	所以，我们可能需要正确的转换排序的大小端格式，这个时候，咱们的确需要做的就是htons或者是htonl。

​	剩下的参数填写的是采用的结构体的大小，这个是纯粹方便正确的转换的，填写sizeof的结果就完事了

> 题外话：避免“地址已使用”错误 (EADDRINUSE)：
>
> 在服务器程序中，当程序崩溃或异常退出时，操作系统可能不会立即释放绑定的端口，导致在短时间内重新启动程序时报告“地址已使用”错误。为了避免这个问题，通常会在 bind() 之前设置套接字的**SO_REUSEADDR 选项**，允许重新使用处于 TIME_WAIT 状态的本地地址。这通过 setsockopt() 函数实现。
>
> ```c
> int optval = 1;
> if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
>     perror("setsockopt SO_REUSEADDR failed");
>     // 处理错误
> }
> ```
>
> 这样的话，我们就不会再次触发端口已经绑定的问题。

> bind的本质是**为服务器指定监听地址和端口**：对于服务器程序而言，`bind()` 是必不可少的一步。它告诉操作系统，这个套接字将监听哪个 IP 地址上的哪个端口号。只有绑定了地址和端口，客户端才能找到并连接到服务器。
>
> - **IP 地址**：
>   - 如果您想让服务器监听所有可用的网络接口（即所有本机 IP 地址），可以将 `sin_addr.s_addr` 设置为 `INADDR_ANY`（通常是 `0.0.0.0`，经过 `htonl()` 转换后）。
>   - 如果您想让服务器只监听特定的一个 IP 地址，可以将其设置为该 IP 地址的 `inet_addr()` 转换结果。
> - **端口号**：
>   - 端口号范围是 `0` 到 `65535`。
>   - `0-1023` 是**知名端口**，通常由系统服务占用，需要 root 权限才能绑定。
>   - `1024-49151` 是**注册端口**。
>   - `49152-65535` 是**动态/私有端口**，通常用于客户端的临时端口。
>   - 作为服务器，您通常会选择一个大于 `1023` 的固定端口号。

## listen：将通信激活到监听状态

​	我们知道，下一步就是驱动我们的网卡监听外部信息，去尝试捕捉潜在的客户端的连接。

```c
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```

​	这是我们的API接口，sockfd是已经通过 `socket()` 函数创建并**通过 `bind()` 函数绑定了本地地址和端口号**的套接字文件描述符。`listen()` 函数将使这个特定的套接字开始监听网络连接。

> **注意：** 只有流式套接字（`SOCK_STREAM`）才需要调用 `listen()`。数据报套接字（`SOCK_DGRAM`）是无连接的，因此不需要监听。这个算是一个需要注意的点！

#### `backlog`（待处理连接队列的最大长度）

​	这个参数是 `listen()` 函数的核心，它指定了系统可以为这个套接字**排队等待接受的连接请求数量**。为了理解 `backlog`，我们需要知道 TCP 连接建立的**三次握手**过程。当一个客户端发起连接请求时，它会向服务器发送一个 `SYN` 报文。此时，操作系统会创建一个连接，并将其放在一个**半连接队列**（`SYN queue`）中。当服务器收到客户端的 `ACK` 报文，完成三次握手后，这个连接会被从半连接队列移动到**全连接队列**（`accept queue`）。

**`backlog` 参数的真正作用就是限制这个“全连接队列”的最大长度。**

- **如果全连接队列已满**：当有新的客户端连接完成三次握手时，操作系统会忽略其 `ACK` 报文，导致客户端最终超时，认为连接失败。
- **`backlog` 的值**：
  - 历史上，不同的操作系统对 `backlog` 的解释和实现有所不同。在现代 Linux 系统中，`backlog` 参数主要控制的就是全连接队列的最大长度。
  - **如何选择 `backlog` 的值？** 应该根据你的**服务器性能和预期的并发连接数**来决定。如果你的服务器可能在短时间内收到大量的连接请求，一个较大的 `backlog` 值可以防止新连接被拒绝，直到你的程序有时间调用 `accept()` 来处理它们。
  - 如果 `backlog` 值设置为 `0`，某些系统**可能将其视为默认值**，而另一些系统则可能导致无法接受任何连接。因此，最好设置一个合理的值，例如 `10`、`128` 或 `SOMAXCONN`（通常是系统定义的最大值）。

## accept：接受一个客户端的连接

在 Linux 网络编程中，`accept()` 函数是服务器程序接收客户端连接的“握手”操作。在 `listen()` 函数使套接字进入监听状态并准备好连接队列后，`accept()` 的作用就是**从这个队列中取出最靠前的一个连接请求，并创建一个新的套接字**专门用于与该客户端进行通信。

`accept()` 函数的原型定义在 `<sys/socket.h>` 头文件中：

```c
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

**`accept()` 是一个阻塞函数**。这意味着如果当前全连接队列中没有等待的连接，它会**一直阻塞**在那里，直到有新的客户端连接完成三次握手。如果 `sockfd` 被设置为非阻塞模式，`accept()` 会立即返回 `-1`，并设置 `errno` 为 `EAGAIN` 或 `EWOULDBLOCK`。成功时，它返回一个**新的套接字文件描述符**，这个描述符专门用来与发起连接的客户端进行数据传输。失败时，它返回 `-1`。

#### 1. `sockfd`（监听套接字文件描述符）

这是通过 `socket()` 和 `bind()` 创建，并用 `listen()` 进入监听状态的**服务器监听套接字**。`accept()` 不会在这个套接字上进行数据收发，它只是用它来接收连接请求。

#### 2. `addr`（客户端地址结构体）

这是一个指向 `struct sockaddr` 类型结构体的指针。`accept()` 函数会**填充这个结构体**，存储发起连接的**客户端的地址信息**，包括其 IP 地址和端口号。

通常，您会声明一个 `struct sockaddr_in`（用于 IPv4）类型的变量，然后将其地址强制转换为 `struct sockaddr *` 传递给 `accept()`。

#### 3. `addrlen`（地址结构体长度）

这是一个指向 `socklen_t` 类型的指针。在调用 `accept()` 之前，您需要将 `addrlen` 指向的变量设置为 `addr` 结构体的**初始大小**。`accept()` 函数执行完毕后，它会**更新** `addrlen` 指向的值，使其反映出 `addr` 结构体中实际存储的有效字节数。

​	下面的代码就是一个最简单的服务器端的通信代码：

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    // ... socket() 和 bind() 和 listen() ...
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // ... bind and listen ...

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // 4. 持续接受连接
    while (1) {
        printf("Waiting for a connection...\n");
        
        // 接受一个连接，如果队列为空则阻塞
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("accept failed");
            // 可以选择继续循环或者退出
            continue;
        }

        // 打印客户端信息
        printf("Connection accepted from %s:%d\n", 
               inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        // 在这里，服务器可以使用 new_socket 与客户端进行通信
        read(new_socket, buffer, 1024);
        printf("Client sent: %s\n", buffer);

        const char *hello = "Hello from server";
        send(new_socket, hello, strlen(hello), 0);
        printf("Hello message sent\n");

        // 通信结束后，关闭新套接字
        close(new_socket);
        printf("Connection closed.\n");
    }

    close(server_fd);
    return 0;
}
```

## 题外话：TCP 三次握手与 Linux Socket API

### 客户端 (Client)



1. **`connect()`** 函数调用：当客户端调用 `connect()` 函数时，操作系统会**发送第一个 SYN 包**给服务器，请求建立连接。此时，客户端进入 `SYN_SENT` 状态，等待服务器的回应。
2. **`connect()`** 函数返回：客户端的 `connect()` 函数会**阻塞**（在默认情况下），直到收到服务器的 **SYN-ACK 包**和客户端自己的 **ACK 包**成功发送后，也就是三次握手完成，`connect()` 函数才会返回。此时，连接已经建立，客户端进入 `ESTABLISHED` 状态。

### 服务器端 (Server)

1. **`listen()`** 函数调用：`listen()` 函数本身只是告诉操作系统，这个套接字已准备好接受连接。它会设置一个**待处理连接队列**，但并不会立即开始三次握手。
2. **接收 SYN 包**：当客户端调用 `connect()` 发送第一个 SYN 包后，服务器端的操作系统内核会**被动地接收这个 SYN 包**。内核会回应一个 **SYN-ACK 包**，并创建连接的半连接状态，将其放入**半连接队列**中。这个过程是由内核自动完成的，不涉及任何应用程序级别的 API 调用。
3. **接收 ACK 包并移动到全连接队列**：当服务器收到客户端发来的最后一个 ACK 包后，三次握手完成。操作系统会将该连接从半连接队列中**移动到全连接队列**（`backlog`）。这个过程也是由内核自动完成的。
4. **`accept()`** 函数调用：服务器调用 `accept()` 函数时，它会**从全连接队列中取出一个已经完成三次握手的连接**。如果队列为空，`accept()` 会阻塞等待。当 `accept()` 成功返回时，就意味着它已经拿到一个建立好的连接，可以开始进行数据通信了。

​	**换而言之，所有的三次握手不发生在accept中，对于服务器端，他早在accept返回之前就完成了连接（因为如果没有完成，他会等待直到连接完成后，才会取出来这个套接字返回进行IO操作，三次握手的主动方在客户端的connect上，connect调用发起的时候进行第一次SYN握手，等待服务器完成接受SYN报文且回复ACK-SYN报文，connect接受到这个报文后再次回复好ACK才会跳出connect函数准备进行通信**

### 总结

| 三次握手步骤   | 客户端 API                                    | 服务器端 API                                | 备注                                               |
| -------------- | --------------------------------------------- | ------------------------------------------- | -------------------------------------------------- |
| **第一次握手** | `connect()` 内部发送 **SYN** 包               | 内核被动接收                                | 客户端发起连接请求                                 |
| **第二次握手** | 内核被动接收 **SYN-ACK** 包                   | 内核被动发送 **SYN-ACK** 包                 | 服务器确认收到，并回应确认和自己的连接请求         |
| **第三次握手** | 内核被动发送 **ACK** 包  `connect()` **返回** | 内核被动接收 **ACK** 包  连接进入全连接队列 | 客户端确认，连接建立，服务器端可被 `accept()` 接收 |

因此，三次握手这个复杂的协议过程，在 Linux C Socket 编程中，被巧妙地封装在了 **`connect()`** 和 **`accept()`** 这两个 API 的**阻塞**行为中。`connect()` 阻塞直到连接建立，而 `accept()` 阻塞直到有完成握手的连接可以被接受。

## 客户端的connect函数

​	我们这里再把最后的connect函数说一下：

`connect()` 函数的原型定义在 `<sys/socket.h>` 头文件中：

```C
#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

**`connect()` 是一个阻塞函数**（在默认情况下）。它会一直等待，直到连接建立成功或发生错误。成功时，它返回 `0`；失败时，返回 `-1`，并设置全局变量 `errno`。

#### 1. `sockfd`（套接字文件描述符）

这是通过 `socket()` 函数创建的套接字文件描述符。`connect()` 函数将使用这个套接字来发起连接请求。

#### 2. `addr`（服务器地址结构体）

这是一个指向 `struct sockaddr` 类型常量的指针。它包含了你想要连接的**服务器的地址信息**，包括其 IP 地址和端口号。

与 `bind()` 类似，实际使用中我们会用更具体的地址结构体，如 `struct sockaddr_in`（用于 IPv4），并将其地址强制转换为 `struct sockaddr *`。

**`struct sockaddr_in` 结构体示例：**

```C
struct sockaddr_in {
    sa_family_t    sin_family; // 地址族，通常为 AF_INET
    in_port_t      sin_port;   // 服务器端口号，网络字节序
    struct in_addr sin_addr;   // 服务器IP地址，网络字节序
};
```

**关键点：** 在填充这个结构体时，必须使用**网络字节序**。你需要将服务器的端口号和 IP 地址从主机字节序转换过来，通常使用 `htons()` 和 `inet_addr()`/`inet_pton()` 函数。



#### 3. `addrlen`（地址结构体长度）



这个参数指定了 `addr` 指向的地址结构体的**实际大小**。通常使用 `sizeof(struct sockaddr_in)`。

------



### `connect()` 的作用和流程



当客户端调用 `connect()` 函数时，会触发以下一系列事件：

1. **发送 SYN 包**：`connect()` 函数内部，操作系统会向服务器端的 IP 地址和端口号发送一个 TCP **`SYN`**（同步）报文，发起三次握手。
2. **等待 SYN-ACK**：`connect()` 函数会**阻塞**，等待服务器端的 `SYN-ACK`（同步-确认）报文。
3. **发送 ACK 包**：当收到 `SYN-ACK` 后，客户端操作系统会发送一个 **`ACK`**（确认）报文给服务器。
4. **连接建立**：三次握手完成。此时，`connect()` 函数返回 `0`，表示连接已成功建立。

**如果 `connect()` 失败了，通常会有以下原因：**

- **`ECONNREFUSED`**：服务器端没有监听该端口（即没有调用 `listen()`），或者该端口上有防火墙阻止连接。
- **`ETIMEDOUT`**：连接超时。服务器可能因为网络问题无法到达，或者服务器没有回应。
- **`ENETUNREACH`**：无法到达网络。
- **`EADDRINUSE`**：客户端的本地地址或端口已被使用。

------



### 客户端的 `bind()` 和 `connect()`

一个有趣的细节是，客户端在调用 `connect()` 之前，**通常不需要调用 `bind()`**。

- **如果未调用 `bind()`**：操作系统会在 `connect()` 内部自动为客户端套接字分配一个可用的**临时（匿名）端口号**和本地 IP 地址。
- **如果调用了 `bind()`**：客户端可以指定一个特定的本地 IP 地址和端口号来发起连接。这在某些特殊应用场景下可能有用，但大部分情况下并不需要。

------

​	客户端经典的通信流程：

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1" // 服务器IP地址
#define PORT 8080             // 服务器端口号

int main() {
    int client_fd;
    struct sockaddr_in server_addr;

    // 1. 创建套接字
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    // 2. 准备服务器地址结构体
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // 将IP地址字符串转换为网络字节序
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("invalid address/address not supported");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // 3. 连接到服务器
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Successfully connected to server at %s:%d\n", SERVER_IP, PORT);

    // 4. 在这里进行数据通信（send/recv）...
    const char *message = "Hello from client";
    send(client_fd, message, strlen(message), 0);
    printf("Message sent to server\n");

    // 5. 关闭套接字
    close(client_fd);
    return 0;
}
```