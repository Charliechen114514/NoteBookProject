# C/C++网络编程之快速整理Socket编程模板

## 1. 几个重要的函数

```c
socket()      // 创建 socket，返回文件描述符  
bind()        // 绑定地址和端口  
listen()      // 监听端口（仅 TCP 服务端使用）  
accept()      // 接受客户端连接，返回新的 socket  
connect()     // 客户端连接服务器  
send()/recv() // TCP 发送/接收数据  
sendto()/recvfrom() // UDP 发送/接收数据  
close()       // 关闭 socket  
setsockopt()  // 设置 socket 参数（如端口复用 SO_REUSEADDR）  
```

## 2. TCP 通信流程

### 服务端流程：

1. socket()：创建一个套接字，基本上参数是：网络层协议版本，是否为面向连接的协议，默认的具体协议（一般直接给0让内核选）

   - AF_INET：网络层上使用IPv4
   - AF_INET6：网络层上使用IPv6
   - SOCK_STREAM：面向连接的套接字
   - SOCK_DGRAM：面向数据的套接字

2. bind()：绑定一个端口，这个时候实际上是尝试申请占用操作系统中的端口资源（一般IP绑定在本地中）

3. listen()：开放监听，这个时候我们就会开放网卡使用对应的物理端口监听使能到我们的虚拟进程端口上

   一般比较说的是——第二个参数是允许处理的连接数数量

4. accept()：允许我们的连接，这个是一个阻塞的调用。

5. recv()/send()：这里是数据的收发，也就是业务代码部分

6. close()：关闭和释放我们的连接

### 客户端流程：

1. socket()：同上
2. connect()：这里是连接一个指定的对象。
3. send()/recv()：同上
4. close()：同上

## 3. I/O 模型与并发方式

- 阻塞式：默认，recv/send 会阻塞等待
- 非阻塞式：立即返回
- select：监听多个 socket 的 I/O 状态
- epoll：高性能 I/O 多路复用（推荐 Linux 使用）

### 并发模型：

- 多线程：每连接一个线程
- 多进程：使用 fork
- I/O 多路复用：单线程 + select/epoll

## 4. 粘包与拆包问题

### 原因：

TCP 是字节流，没有边界，可能会粘在一起或被拆开。

### 解决：

- 包头 + 包体格式
- 定长协议
- 分隔符协议（如 \n）

## 5. Qt Socket 简述

```cpp
QTcpServer* server = new QTcpServer();
server->listen(QHostAddress::Any, 8888);

connect(server, &QTcpServer::newConnection, [&]() {
    QTcpSocket* client = server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, [=]() {
        QByteArray data = client->readAll();
        client->write(data);  // echo 回传
    });
});
```

## 6. TCP Echo 服务端（C语言）

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8888);

    bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_fd, 5);

    printf("等待连接...\n");
    int clnt_fd = accept(serv_fd, NULL, NULL);

    char buffer[1024] = {0};
    int n = read(clnt_fd, buffer, sizeof(buffer));
    write(clnt_fd, buffer, n);

    close(clnt_fd);
    close(serv_fd);
    return 0;
}
```

## 7. UDP 通信示例

### UDP 服务端：

```c
int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in serv_addr = {0};
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(8888);
serv_addr.sin_addr.s_addr = INADDR_ANY;

bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

char buf[1024];
struct sockaddr_in cli_addr;
socklen_t len = sizeof(cli_addr);
recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli_addr, &len);
sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&cli_addr, len);
```

## 8. 多线程 Echo Server（pthread）

```c
void* handle_client(void* arg) {
    int clnt_fd = *(int*)arg;
    char buf[1024];
    int n = read(clnt_fd, buf, sizeof(buf));
    write(clnt_fd, buf, n);
    close(clnt_fd);
    return NULL;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // bind + listen ...
    while (1) {
        int clnt_fd = accept(server_fd, NULL, NULL);
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, &clnt_fd);
        pthread_detach(tid);
    }
}
```

## 9. 多进程 Echo Server（fork）

```c
int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // bind + listen ...
    while (1) {
        int clnt_fd = accept(server_fd, NULL, NULL);
        if (fork() == 0) {
            char buf[1024];
            int n = read(clnt_fd, buf, sizeof(buf));
            write(clnt_fd, buf, n);
            close(clnt_fd);
            exit(0);
        }
        close(clnt_fd);
    }
}
```

## 10. select 示例（多路复用）

```c
fd_set readfds;
FD_ZERO(&readfds);
FD_SET(listen_fd, &readfds);
select(listen_fd + 1, &readfds, NULL, NULL, NULL);

if (FD_ISSET(listen_fd, &readfds)) {
    int clnt_fd = accept(listen_fd, NULL, NULL);
    FD_SET(clnt_fd, &readfds);
}
```

## 11. epoll 示例（高并发）

```c
int epfd = epoll_create(10);
struct epoll_event ev, events[10];
ev.events = EPOLLIN;
ev.data.fd = listen_fd;
epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &ev);

int nfds = epoll_wait(epfd, events, 10, -1);
for (int i = 0; i < nfds; ++i) {
    if (events[i].data.fd == listen_fd) {
        int clnt_fd = accept(listen_fd, NULL, NULL);
        ev.events = EPOLLIN;
        ev.data.fd = clnt_fd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_fd, &ev);
    } else {
        int n = read(events[i].data.fd, buf, sizeof(buf));
        write(events[i].data.fd, buf, n);
    }
}
```

