# 网络编程系列：C++使用Linux的API快速获取网卡信息详解（AddressInfo）

## 前言

​	这个算是笔者新开的一个短期小坑？因为笔者决定制作一个小的网络库给我后面开发一些小玩具使用，因此，这里是一个文档存档，记录笔者思路用的小玩意。

## 如何在Linux下获取我们的网卡基本地址

​	一般而言，我们会使用一个好东西叫做`getifaddrs`，他的函数签名和说明笔者放到下面：

```c
/* Create a linked list of `struct ifaddrs' structures, one for each
   network interface on the host machine.  If successful, store the
   list in *IFAP and return 0.  On errors, return -1 and set `errno'.

   The storage returned in *IFAP is allocated dynamically and can
   only be properly freed by passing it to `freeifaddrs'.  */
extern int getifaddrs (struct ifaddrs **__ifap) __THROW;

/* Reclaim the storage allocated by a previous `getifaddrs' call.  */
extern void freeifaddrs (struct ifaddrs *__ifa)  __THROW;

```

​	这是两个C的API，前者获取我们的ifaddrs，后者将我们的申请给释放掉。这里，我们会得到一个ifaddrs链表，遍历这个链表后，我们就能如期的拿到外面想要的信息：

```c
/* The `getifaddrs' function generates a linked list of these structures.
   Each element of the list describes one network interface.  */
struct ifaddrs
{
  struct ifaddrs *ifa_next;	/* Pointer to the next structure.  */

  char *ifa_name;		/* Name of this network interface.  */
  unsigned int ifa_flags;	/* Flags as from SIOCGIFFLAGS ioctl.  */

  struct sockaddr *ifa_addr;	/* Network address of this interface.  */
  struct sockaddr *ifa_netmask; /* Netmask of this interface.  */
  union
  {
    /* At most one of the following two is valid.  If the IFF_BROADCAST
       bit is set in `ifa_flags', then `ifa_broadaddr' is valid.  If the
       IFF_POINTOPOINT bit is set, then `ifa_dstaddr' is valid.
       It is never the case that both these bits are set at once.  */
    struct sockaddr *ifu_broadaddr; /* Broadcast address of this interface. */
    struct sockaddr *ifu_dstaddr; /* Point-to-point destination address.  */
  } ifa_ifu;
  /* These very same macros are defined by <net/if.h> for `struct ifaddr'.
     So if they are defined already, the existing definitions will be fine.  */
# ifndef ifa_broadaddr
#  define ifa_broadaddr	ifa_ifu.ifu_broadaddr
# endif
# ifndef ifa_dstaddr
#  define ifa_dstaddr	ifa_ifu.ifu_dstaddr
# endif

  void *ifa_data;		/* Address-specific data (may be unused).  */
};
```

​	这是我们需要遍历的结构体成员。下面笔者一个一个说这些的

> ```c
> struct ifaddrs {
>     struct ifaddrs *ifa_next;   // 下一个节点指针，形成链表
>     char *ifa_name;             // 接口名称，如 "eth0"、"lo" 等
>     unsigned int ifa_flags;     // 接口标志（SIOCGIFFLAGS），如 IFF_UP、IFF_LOOPBACK 等
> 
>     struct sockaddr *ifa_addr;      // 接口地址，如 IPv4 或 IPv6 地址
>     struct sockaddr *ifa_netmask;   // 子网掩码
>     union {
>         struct sockaddr *ifu_broadaddr; // 广播地址（iff_flags 设置了 IFF_BROADCAST 时有效）
>         struct sockaddr *ifu_dstaddr;   // 点对点地址（iff_flags 设置了 IFF_POINTOPOINT 时有效）
>     } ifa_ifu;
> 
>     void *ifa_data;             // 接口附加信息（通常是系统内部使用，可以为 NULL）
> };
> ```
>
> ### 🔁 ifa_next
>
> - 类型：`struct ifaddrs*`
> - 说明：指向下一个 `ifaddrs` 节点，用于遍历链表。
>
> ------
>
> ### 🔠 ifa_name
>
> - 类型：`char*`
> - 说明：接口的名称，常见如 `"eth0"`、`"lo"`、`"wlan0"` 等。
>
> ------
>
> ### 🚩 ifa_flags
>
> - 类型：`unsigned int`
> - 说明：接口标志，来源于 `SIOCGIFFLAGS` ioctl。
> - 常见值（定义于 `<net/if.h>`）：
>   - `IFF_UP`：接口已启用。
>   - `IFF_LOOPBACK`：环回接口（如 lo）。
>   - `IFF_BROADCAST`：支持广播。
>   - `IFF_POINTOPOINT`：点对点链路。
>   - `IFF_MULTICAST`：支持多播。
>
> 可用 `ifa_flags & IFF_XXX` 判断特性。
>
> ------
>
> ### 🌐 ifa_addr
>
> - 类型：`struct sockaddr*`
> - 说明：接口的主地址（IP 地址），支持 IPv4（`AF_INET`）、IPv6（`AF_INET6`）等。
>
> ------
>
> ### 🎭 ifa_netmask
>
> - 类型：`struct sockaddr*`
> - 说明：接口的子网掩码。类型通常与 `ifa_addr` 相同。
>
> ------
>
> ### 📢 ifa_ifu 联合体（广播 / 点对点地址）
>
> ```c
> union {
>     struct sockaddr *ifu_broadaddr; // 广播地址
>     struct sockaddr *ifu_dstaddr;   // 点对点目的地址
> } ifa_ifu;
> ```
>
> > 只会有一个有效：
>
> - 如果 `ifa_flags & IFF_BROADCAST`，则 `ifu_broadaddr` 有效。
> - 如果 `ifa_flags & IFF_POINTOPOINT`，则 `ifu_dstaddr` 有效。
>
> 为方便使用，下面两个宏被定义（来自 `<net/if.h>`）：
>
> ```c
> #define ifa_broadaddr  ifa_ifu.ifu_broadaddr
> #define ifa_dstaddr    ifa_ifu.ifu_dstaddr
> ```
>
> ------
>
> ### 📎 ifa_data
>
> - 类型：`void*`
> - 说明：通常为 NULL，或指向某些协议相关的数据，系统依赖实现。
> - 很少使用，可忽略。
>
> 总而言之就是下面一张表：
>
> | 字段                            | 含义                       |
> | ------------------------------- | -------------------------- |
> | `ifa_next`                      | 链表下一项                 |
> | `ifa_name`                      | 接口名称                   |
> | `ifa_flags`                     | 接口属性（是否up、多播等） |
> | `ifa_addr`                      | 接口地址（IP）             |
> | `ifa_netmask`                   | 子网掩码                   |
> | `ifa_broadaddr` / `ifa_dstaddr` | 广播地址 / 点对点目的地址  |
> | `ifa_data`                      | 附加数据（可忽略）         |

​	这里是我看的一本书，叫做《Hands-On Network Programming with C》（Lewis Van Winkle著）的一个改编的小例子。

```c
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    struct ifaddrs *ifaddr, *ifa;
    char addr_buf[INET6_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return 1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) continue;

        int family = ifa->ifa_addr->sa_family;
        printf("Interface: %s\n", ifa->ifa_name);

        if (family == AF_INET || family == AF_INET6) {
            void *addr;
            if (family == AF_INET)
                addr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            else
                addr = &((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;

            inet_ntop(family, addr, addr_buf, sizeof(addr_buf));
            printf("  Address: %s\n", addr_buf);
        }

        printf("  Flags: 0x%x\n", ifa->ifa_flags);
    }

    freeifaddrs(ifaddr);
    return 0;
}
```

## 补充：如何在Linux下获取我们的网卡MAC地址

​	笔者的一位朋友跟我聊过Linux获取网卡的MAC地址的事情，这里只给出在Linux下快速获取我们的MAC地址，我们知道，上面的接口一定对MAC地址是无力的，很简单，因为它属于数据链路层/物理层的部分了，属于硬件的部分，要向硬件驱动要。

​	询问硬件驱动，我们很容易想到Linux下的通用接口ioctl，我们传入对应的property后，返回我们关心的数据。

```c
	const char* ifname = "wlan0"; // ifname 是接口名称，我们可以在上面的基础上进一步咨询MAC地址
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		return "";

	struct ifreq ifr;
	std::strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';

	if (ioctl(sock, SIOCGIFHWADDR, &ifr) != 0) {
		close(sock);
		return "";
	}

	close(sock); // 释放掉我们的socket
	// 我们到这里，就拿到了我们期待的MAC地址了
	unsigned char* mac = reinterpret_cast<unsigned char*>(ifr.ifr_hwaddr.sa_data);
```

## 构建基本的抽象

```c++
#pragma once
#include "common/protocals_enum.h"
#include <string>
#include <vector>

/**
 * @brief AddressInfo collects the net card's status
 *
 */
struct AddressInfo {
	ProtocolEnum::IPVersionType ip_version_type; ///< ip version type
	ProtocolEnum::TransferType transfer_type; ///< transfer type
	ProtocolEnum::NetState net_state; ///< network status, on or off
	ProtocolEnum::NetType net_type; ///< net type
	std::string address_string; ///< address
	std::string interface_string; ///< interface name
	std::string mac_addr; ///< mac if existed
};

/**
 * @brief AddressInfoQuery query the address info
 *
 */
struct AddressInfoQuery {
	static std::vector<AddressInfo> query_local(); ///< query local
};
```

​	我们需要做的就是封装上面的小例子，转化成一个得到的AddressInfo动态数组返回本地的信息。

```cpp
#include "address_iterator.h"
#include "common/protocals_enum.h"
#include "unistd.h"
#include <arpa/inet.h>
#include <cstring>
#include <ifaddrs.h>
#include <iomanip>
#include <net/if.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <sstream>
#include <stdexcept>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <vector>

namespace {
std::string get_mac_address_string(const char* ifname) {
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		return "";

	struct ifreq ifr;
	std::strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';

	if (ioctl(sock, SIOCGIFHWADDR, &ifr) != 0) {
		close(sock);
		return "";
	}

	close(sock);
	unsigned char* mac = reinterpret_cast<unsigned char*>(ifr.ifr_hwaddr.sa_data);

	std::ostringstream oss;
	oss << std::hex << std::setfill('0');
	for (int i = 0; i < 6; ++i) {
		oss << std::setw(2) << static_cast<int>(mac[i]);
		if (i != 5)
			oss << ":";
	}
	return oss.str();
}
}
std::vector<AddressInfo> AddressInfoQuery::query_local() {
	std::vector<AddressInfo> results;
	struct ifaddrs* ifaddr;
	if (::getifaddrs(&ifaddr) == -1) {
		throw std::invalid_argument("Can not candidate the getifaddrs");
	}

	for (ifaddrs* current = ifaddr; current != nullptr; current = current->ifa_next) {
		// now iterate the current sessions
		if (!current->ifa_addr)
			continue; // not in the scope
		AddressInfo info;
		info.interface_string = current->ifa_name;
		info.mac_addr = get_mac_address_string(current->ifa_name);
		int raw_family_type = current->ifa_addr->sa_family;
		if (raw_family_type == AF_INET || raw_family_type == AF_INET6) {
			char tmp_buffer[INET6_ADDRSTRLEN];
			void* src;

			if (raw_family_type == AF_INET) {
				src = &((struct sockaddr_in*)current->ifa_addr)->sin_addr;
				info.ip_version_type = ProtocolEnum::IPVersionType::IPv4;
			} else {
				src = &((struct sockaddr_in6*)current->ifa_addr)->sin6_addr;
				info.ip_version_type = ProtocolEnum::IPVersionType::IPv6;
			}

			inet_ntop(raw_family_type, src, tmp_buffer, sizeof(tmp_buffer));
			info.address_string = tmp_buffer;
		} else {
			info.address_string = current->ifa_addr->sa_data;
		}

		if (current->ifa_flags & IFF_UP) {
			info.net_state = ProtocolEnum::NetState::ON;
		} else {
			info.net_state = ProtocolEnum::NetState::OFF;
		}

		// types

		ProtocolEnum::NetType result = ProtocolEnum::NetType::Normal;

		if (current->ifa_flags & IFF_LOOPBACK)
			result = static_cast<ProtocolEnum::NetType>(result | ProtocolEnum::NetType::LoopBack);
		if (current->ifa_flags & IFF_BROADCAST)
			result = static_cast<ProtocolEnum::NetType>(result | ProtocolEnum::NetType::BroadCastable);
		if (current->ifa_flags & IFF_MULTICAST)
			result = static_cast<ProtocolEnum::NetType>(result | ProtocolEnum::NetType::MultiCastable);
		info.net_type = result;
		results.emplace_back(info);
	}

	::freeifaddrs(ifaddr);
	return results;
}

```

`query_local()` 方法是本模块的核心，它通过系统调用 `getifaddrs()` 获取本地所有网络接口的详细信息，并将其封装为 `std::vector<AddressInfo>` 返回。每个 `AddressInfo` 结构体代表一个网络接口。

###  `get_mac_address_string`的基本工作原理

#### 作用

此辅助函数用于根据网络接口的名称（例如 "eth0"）获取其对应的 **MAC 地址** 并以字符串形式返回。

#### 工作原理

1. **创建 Socket**: 它首先创建一个 `AF_INET` 类型的 `DGRAM` (数据报) socket。这个 socket 仅用于进行系统控制操作，不用于实际网络通信。
2. **准备 `ifreq` 结构体**: `struct ifreq` 是一个通用的网络设备控制结构体。函数将传入的接口名称拷贝到 `ifr.ifr_name` 字段。
3. **调用 `ioctl`**: 通过 `ioctl` 系统调用，并使用 `SIOCGIFHWADDR` 命令，向内核查询指定接口的硬件地址（MAC 地址）。查询结果会填充到 `ifr.ifr_hwaddr` 字段中。
4. **MAC 地址格式化**: 获取到原始的 MAC 地址（通常是 `unsigned char` 数组）后，函数会将其格式化为标准的十六进制冒号分隔字符串（例如 "00:11:22:AA:BB:CC"），并返回。
5. **错误处理**: 如果 socket 创建失败或 `ioctl` 调用失败，函数将返回空字符串。

### queryLocal方法的核心原理

#### 工作原理

1. **获取接口地址列表**:
   - 函数首先调用 `::getifaddrs(&ifaddr)` 系统函数。这是一个 POSIX 标准函数，用于获取系统中所有网络接口的配置信息，并以链表的形式存储在 `ifaddr` 指向的 `struct ifaddrs` 结构体中。
   - 如果 `getifaddrs()` 调用失败，将抛出 `std::invalid_argument` 异常，指示无法获取网络接口信息。
2. **遍历接口链表**:
   - 函数通过循环遍历 `ifaddr` 链表，`current` 指针逐个指向链表中的每个 `ifaddrs` 结构体，直到链表末尾 (`nullptr`)。
   - **跳过无效地址**: 在每次循环开始时，会检查 `current->ifa_addr` 是否为 `nullptr`。如果为 `nullptr`，则表示当前接口没有关联的地址信息（例如，某些虚拟接口或链路层接口可能没有IP地址），因此会跳过当前项。
3. **填充 `AddressInfo` 结构**: 对于每个有效的网络接口，函数会创建一个 `AddressInfo` 对象并填充其成员：
   - **`info.interface_string`**: 直接从 `current->ifa_name` 获取接口名称。
   - **`info.mac_addr`**: 调用前述的 `get_mac_address_string()` 辅助函数，传入接口名称以获取其 MAC 地址。
   - **IP 地址和版本 (`info.address_string`, `info.ip_version_type`)**:
     - 通过检查 `current->ifa_addr->sa_family` 来判断地址族是 IPv4 (`AF_INET`) 还是 IPv6 (`AF_INET6`)。
     - 根据地址族，将 `current->ifa_addr` 强制转换为 `struct sockaddr_in` 或 `struct sockaddr_in6`，并提取出 `sin_addr` 或 `sin6_addr`（即实际的 IP 地址）。
     - 使用 `inet_ntop()` 函数将二进制的 IP 地址转换为可读的字符串形式，存储在 `info.address_string` 中。
     - 设置 `info.ip_version_type` 为 `IPv4` 或 `IPv6`。
     - **其他地址族**: 如果 `sa_family` 既不是 `AF_INET` 也不是 `AF_INET6`（例如，`AF_PACKET` 用于链路层），则直接将 `current->ifa_addr->sa_data` 的内容（原始数据）赋给 `info.address_string`。
   - **网络状态 (`info.net_state`)**:
     - 通过检查 `current->ifa_flags` 中是否设置了 `IFF_UP` 标志来判断接口是否处于“启用”状态。
     - 相应地设置 `info.net_state` 为 `ProtocolEnum::NetState::ON` 或 `ProtocolEnum::NetState::OFF`。
   - **网络类型 (`info.net_type`)**:
     - 通过按位或 (`|`) 操作组合 `ProtocolEnum::NetType` 枚举值来表示接口支持的多种类型。
     - 检查 `ifa_flags` 中的 `IFF_LOOPBACK`（回环）、`IFF_BROADCAST`（广播能力）和 `IFF_MULTICAST`（多播能力）标志，并将相应的类型添加到 `info.net_type` 中。
4. **添加结果并释放资源**:
   - 填充完 `AddressInfo` 对象后，将其添加到 `results` 向量中。
   - 循环结束后，调用 `::freeifaddrs(ifaddr)` 释放由 `getifaddrs()` 分配的链表内存，防止内存泄漏。
   - 最后，返回包含所有查询结果的 `results` 向量。

------