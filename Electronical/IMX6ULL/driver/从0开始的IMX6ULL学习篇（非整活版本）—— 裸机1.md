# 从0开始的IMX6ULL学习篇——裸机开发篇：Section I 环境开发与部署

​	因为笔者很快就要到参加工作的时间了，所以这里打算不去浪费时间折腾新工具，而是先把板子的知识点掌握了再进一步做迁移。

## 关于笔者的配置方案

​	首先，笔者是VMware WorkStation老用户了，所以这里给出VMware WorkStation的下载地址。

> [VMware Workstation Pro: Now Available Free for Personal Use - VMware Workstation Zealot](https://blogs.vmware.com/workstation/2024/05/vmware-workstation-pro-now-available-free-for-personal-use.html)

​	关于虚拟机，我们顺用Ubuntu16.04LTS版本，在这里下载：

> https://releases.ubuntu.com/16.04/ubuntu-16.04.7-desktop-amd64.iso

​	下载好了之后，随意找一篇博客跟着安装就好了。笔者是选择了USB接口为USB3.1协议，内存13G，8个核心的配置，这样自己后面使用起来会舒服一些。

## 讨论一些必要的安装

​	我们安装好虚拟机后，再原先的基础上，记得再重启一次，这是为了验证我们的open-vm-tools有没有安装成功。你也可以使用`sudo apt search open-vm-tools`的方式查看，这个工具是用来快速拖拽文件和从主机和虚拟机之间互相复制粘贴的好东西。

```
open-vm-tools/xenial-updates,now 2:10.2.0-3~ubuntu0.16.04.1 amd64 [installed]
  Open VMware Tools for virtual machines hosted on VMware (CLI)

open-vm-tools-desktop/xenial-updates,now 2:10.2.0-3~ubuntu0.16.04.1 amd64 [installed]
  Open VMware Tools for virtual machines hosted on VMware (GUI)
```

​	这两个都需要安装。在高版本的Ubuntu（笔者测试的是24.04版本）中，则需要自己手动安装，需要注意的是截至至目前（2025年2月26日），笔者不是很建议使用VMWare官方的安装方式进行安装。因为笔者执行脚本后发现SegmentFault了，不太清楚发生了什么，后面也就索性直接`sudo apt install open-vm-tools open-vm-tools-desktop`。朋友们如果使用的是高本版的Ubuntu，考虑一下这个方案然后重启虚拟机。

> 笔者给出一部分常用的apt包管理器的使用方法
>
> | 指令                        | 作用说明                         |
> | --------------------------- | -------------------------------- |
> | `apt update`                | 更新软件包列表                   |
> | `apt upgrade`               | 升级已安装的软件包               |
> | `apt full-upgrade`          | 升级软件包并自动处理依赖关系     |
> | `apt install <package>`     | 安装指定的软件包                 |
> | `apt remove <package>`      | 卸载指定的软件包（保留配置文件） |
> | `apt purge <package>`       | 卸载软件包并删除配置文件         |
> | `apt autoremove`            | 删除不再需要的依赖软件包         |
> | `apt search <keyword>`      | 搜索包含关键字的软件包           |
> | `apt show <package>`        | 显示软件包的详细信息             |
> | `apt list --installed`      | 列出已安装的软件包               |
> | `apt list --upgradable`     | 列出可升级的软件包               |
> | `apt edit-sources`          | 编辑 `sources.list` 文件         |
> | `apt clean`                 | 清理本地 `.deb` 缓存包           |
> | `apt autoclean`             | 清理过时的 `.deb` 缓存文件       |
> | `apt depends <package>`     | 显示软件包的依赖关系             |
> | `apt rdepends <package>`    | 显示反向依赖关系                 |
> | `apt policy <package>`      | 查看软件包的版本信息及来源       |
> | `apt-mark hold <package>`   | 标记软件包为“保持”，防止升级     |
> | `apt-mark unhold <package>` | 取消“保持”标记，允许升级         |
> | `apt-get install -f`        | 修复损坏的依赖关系               |

​	之后，是安装一些必须使用的依赖：

#### 安装NFS和SSH服务

​	使用高于Ubuntu18.04，也就是起步是20.04的的朋友请注意，NFS这个协议的支持在较新的Ubuntu中已经被移除了支持。也就是内核层中已经不再支持正点原子教程中的NFS了，后面我们传递UBoot和Linux内核的时候，就没办法使用NFS，而是TFTP传递了。

```
sudo apt-get install nfs-kernel-server rpcbind
```

​	我们开启nfs的支持，办法是设置一下我们的共享目录：

```
/pth/to/ur/shared_dirent *(rw,sync,no_root_squash)
```

**`/pth/to/ur/shared_dirent`**请指向你自己的共享目录（随意，笔者是指向了自己创建的一个目录），后面的权限不要自作聪明加空格。否则启动不了就老实了。（如果你出现了任何问题，再使用服务开启的时候，往往会提示你查看服务状态获取日志文件，比如说这个如果出现问题了，请自己按照上面的指示输入`sudo systemctl status nfs-kernel-server`）看看自己哪里犯蠢了。

​	然后刷新我们的服务。

```
sudo systemctl restart nfs-kernel-server
```

> 你可能看到我们亲爱的正点原子是
>
> ```
> sudo /etc/init.d/nfs-kernel-server restart 
> ```
>
> 评价是不好，最好使用systemctl的接口，这个东西统管了Ubuntu等发行版的的服务。

```
sudo apt-get install openssh-server 
```

​	上面我们下载了openssh，这个相当于ssh服务器了，我们可以使用SSH协议连接到我们的发行版上。

#### 开发工具

​	Ubuntu16.04给的GCC是老登级别的gcc5.4，但是为了防止出问题（高版本GCC会给你的生成文件整点烂活），笔者打算的是先学习过一次板子，也就顺从了使用GCC 4.9.4了：

> [Linaro Releases](https://releases.linaro.org/components/toolchain/binaries/4.9-2017.01/arm-linux-gnueabihf/)

​	下载后解压到一个文件夹上，然后笔者不同于一般教程，使用的是update alternatives来管理自己的自建软件。

```
sudo update-alternatives --install /usr/bin/arm-linux-gnueabihf-gcc arm-linux-gnueabihf-gcc /path/to/ur/arm-linux-gnueabihf-gcc 100
```

​	注册结束就可以直接使用`arm-linux-gnueabihf-gcc`了

```bash
charliechen@ubuntu:~$ arm-linux-gnueabihf-gcc -v
Using built-in specs.
COLLECT_GCC=arm-linux-gnueabihf-gcc
COLLECT_LTO_WRAPPER=/home/charliechen/linux/tools/arm-gcc/bin/../libexec/gcc/arm-linux-gnueabihf/4.9.4/lto-wrapper
Target: arm-linux-gnueabihf
Configured with: /home/tcwg-buildslave/workspace/tcwg-make-release/label/docker-trusty-amd64-tcwg-build/target/arm-linux-gnueabihf/snapshots/gcc-linaro-4.9-2017.01/configure SHELL=/bin/bash --with-mpc=/home/tcwg-buildslave/workspace/tcwg-make-release/label/docker-trusty-amd64-tcwg-build/target/arm-linux-gnueabihf/_build/builds/destdir/x86_64-unknown-linux-gnu --with-mpfr=/home/tcwg-buildslave/workspace/tcwg-make-release/label/docker-trusty-amd64-tcwg-build/target/arm-linux-gnueabihf/_build/builds/destdir/x86_64-unknown-linux-gnu --with-gmp=/home/tcwg-buildslave/workspace/tcwg-make-release/label/docker-trusty-amd64-tcwg-build/target/arm-linux-gnueabihf/_build/builds/destdir/x86_64-unknown-linux-gnu --with-gnu-as --with-gnu-ld --disable-libmudflap --enable-lto --enable-objc-gc --enable-shared --without-included-gettext --enable-nls --disable-sjlj-exceptions --enable-gnu-unique-object --enable-linker-build-id --disable-libstdcxx-pch --enable-c99 --enable-clocale=gnu --enable-libstdcxx-debug --enable-long-long --with-cloog=no --with-ppl=no --with-isl=no --disable-multilib --with-float=hard --with-mode=thumb --with-tune=cortex-a9 --with-arch=armv7-a --with-fpu=vfpv3-d16 --enable-threads=posix --enable-multiarch --enable-libstdcxx-time=yes --with-build-sysroot=/home/tcwg-buildslave/workspace/tcwg-make-release/label/docker-trusty-amd64-tcwg-build/target/arm-linux-gnueabihf/_build/sysroots/arm-linux-gnueabihf --with-sysroot=/home/tcwg-buildslave/workspace/tcwg-make-release/label/docker-trusty-amd64-tcwg-build/target/arm-linux-gnueabihf/_build/builds/destdir/x86_64-unknown-linux-gnu/arm-linux-gnueabihf/libc --enable-checking=release --disable-bootstrap --enable-languages=c,c++,fortran,lto --build=x86_64-unknown-linux-gnu --host=x86_64-unknown-linux-gnu --target=arm-linux-gnueabihf --prefix=/home/tcwg-buildslave/workspace/tcwg-make-release/label/docker-trusty-amd64-tcwg-build/target/arm-linux-gnueabihf/_build/builds/destdir/x86_64-unknown-linux-gnu
Thread model: posix
gcc version 4.9.4 (Linaro GCC 4.9-2017.01) 
```

#### 安装辅助的32位库

```
sudo apt-get install lsb-core lib32stdc++6 
```

`lsb-core` 是 **Linux Standard Base (LSB)** 规范的核心组件。LSB 旨在标准化 Linux 发行版，使软件可以在不同的 Linux 发行版之间更好地兼容。安装 `lsb-core` 通常意味着提供了一些 LSB 兼容性工具和库，以支持运行依赖于 LSB 规范的应用程序。

但需要注意，近年来 LSB 逐渐被弃用，许多现代 Linux 发行版（如 Ubuntu）已经移除了 `lsb-core`，改为使用更现代的打包和兼容性机制（如 Snap 或 Flatpak）。

`lib32stdc++6` 是 **32 位 GNU 标准 C++ 库** (`libstdc++`) 的 6.x 版本。它通常用于 64 位系统上运行 32 位应用程序。例如：

- 在 64 位 Linux 系统上运行 32 位编译的 C++ 程序。
- 运行依赖 32 位 C++ 库的旧版软件或游戏。

我们的IMX6ULL的架构是32位架构，毫无疑问的要要用32位的库。

#### 下载我们的VSCode

很简单，Ubuntu16.04太老了，实际上已经正在逐渐被淘汰，现在你直接下载1.94版本（就是2025年2月26日的最新下载板）是运行不了的（库极端的旧），下载老版本的Code可以解决你的问题：

```
wget https://vscode.download.prss.microsoft.com/dbazure/download/stable/a3db5be9b5c6ba46bb7555ec5d60178ecc2eaae4/code_1.32.3-1552606978_amd64.deb
```

​	之后就是使用dpkg安装到我们的包管理上

```
sudo dpkg -i code_1.32.3-1552606978_amd64.deb
```

​	完事之后，在shell上测试一下

```
code 
```

​	就会打开VSCode了。

#### 关于XShell和XFTP

​	我是使用这两个传递文件和打开shell，方便，感兴趣的朋友自己下着玩。笔者建议配置完环境之后直接下载一个工程试试看，能不能跑起来。