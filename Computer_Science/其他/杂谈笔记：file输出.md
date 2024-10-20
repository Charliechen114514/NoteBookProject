# 杂谈笔记：一个debug记录之错误的ld interpreter

## 前因

​	笔者前段时间帮忙测试一位同学的校园网驱动程序的时候出现了一个非常有趣的问题：那就是这个文件被进程加载的时候出现了：

```
can not execuate the file, the request file is missing
```

​	的有趣错误。笔者检查了一下file命令的输出，大致格式如下：

```
demo: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=8233200d91ce5b352b50c14288246e5296c1749f, for GNU/Linux 3.2.0, with debug_info, not stripped
```

​	当然，这不是那份程序的输出。不过我们也是从这里的输出定位到了问题。常见的原因是ELF位数格式不匹配的问题。笔者这里的程序显得更加的刁钻：那就是程序是在NixOS下构建。任何熟悉NixOS的朋友会立刻认识到问题所在：那就是程序在其他人笔记本中构建的时候采用的interpreter信息是nix下被冠以hash code path指向的interpreter。这里的missing就会出现上面的问题！太简单了。这个可执行文件甚至被拦截在了成为进程之前了！因为他甚至没有找到这个可执行文件的解释器在何处！

## 具体解释

​	我们回到正题。那就是file的输出指代了什么信息呢？我们都知道file的一个功能就是查看文件的类型信息，和必要的加载信息。

```
➜  file demo
demo: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=8233200d91ce5b352b50c14288246e5296c1749f, for GNU/Linux 3.2.0, with debug_info, not stripped
```

- **ELF**: 这是文件的格式，表示它是一个可执行和可链接的格式，ELF格式相信任何熟悉Linux的人都不陌生！
- **64-bit**: 表示这个 ELF 文件是为 64 位架构设计的，适用于 x86-64 处理器。（一些朋友就会发现在64位平台编译的可执行文件在32位上跑不了，这个可以提前查看file命令解决，当然，配合uname -a来一起鉴定）
- **LSB**: 表示这个文件是“小端”格式（Least Significant Byte first），这是数据存储的字节序。（另一个就是MSB大端了，常见的大端机器就是IBM了，当然ARM架构的可以自己设置位进行说明）
- **pie**: 表示这个可执行文件是“位置无关的”（Position Independent Executable），可以在内存的任何位置加载运行，通常用于提高安全性。（位置无关是重要的安全措施，另一方面说明这个程序对内存的未知不敏感，所有的Symbol都不是硬编码的）
- **executable**: 表示这个文件是一个可执行文件。
- **x86-64**: 指定了文件是为 x86-64 架构（即 AMD64 或 Intel 64）编译的。
- **version 1 (SYSV)**: 指的是 ELF 文件格式的版本和 ABI（应用二进制接口），这里是 System V 的版本 1。
- **dynamically linked**: 表示该可执行文件是动态链接的，意味着它依赖于共享库（如 .so 文件）在运行时加载，而不是将所有代码静态链接到可执行文件中。（这就意味着我们需要后面请出interpreter做铺垫了）
- **interpreter /lib64/ld-linux-x86-64.so.2**: 指定了运行时链接器的路径，这个链接器会在程序启动时加载所需的共享库。（笔者当时就是这个指向了朋友开发的系统的解释器！）
- **BuildID[sha1]=8233200d91ce5b352b50c14288246e5296c1749f**: 这是一个唯一的标识符，用于标识这个构建版本，通常用于调试和符号表查找。
- **for GNU/Linux 3.2.0**: 指明了这个文件的目标操作系统和版本，表明它是为 GNU/Linux 3.2.0 版本构建的。
- **with debug_info**: 表示这个可执行文件包含调试信息，这些信息可以用于调试程序，提供源代码行号等。（其内含有debug信息！）
- **not stripped**: 表示这个文件没有被“剥离”，即调试信息和符号表仍然保留在可执行文件中，便于调试。通常，剥离操作会去除调试信息，以减小文件大小和保护源代码（当然使用strip指令就可以进行剥离，代价就是——程序无法调试了！）