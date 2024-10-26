# Linux Kernel Programming

## Before everything begins

​	在我们开始之前，我们首先需要配置一下虚拟环境（笔者不太敢拿自己的笔记本直接冒险，因此，打算配置一个虚拟机梭哈）

- 需要下载VirtualBox作为一个虚拟机的托管平台
- 需要下载Ubuntu镜像（当然这个随你啦）

## 笔者的环境

​	老样子，笔者必须给出自己的环境如何：

> 一个普通的，操作系统为Linux发行版Arch Linux的笔记本：
>
> ```
> ➜  uname -a
> Linux ArchLinux 6.11.5-arch1-1 #1 SMP PREEMPT_DYNAMIC Tue, 22 Oct 2024 18:31:38 +0000 x86_64 GNU/Linux
> ```

## 关于如何在Arch Linux下载Virtual Box

​	如何下载请看AUR（不是），你可以搜索任何你正在使用的包管理，如何下载，比如说笔者的：

```
yay -Ss virtualbox
```

​	当然yay告诉我一大堆，或者拿不准是哪个，看看这个也是可以的：

>https://cn.linux-console.net/?p=22258

## 下载一个镜像，然后开启一个简单的虚拟机

​	这个不想赘述，我认为水平到玩内核的同志们不会搞不定这个！笔者玩的是Ubuntu的内核（因为实在是方便）

## 在Ubuntu虚拟机下东西

​	笔者这里想要强调的是：在之后如果没有特殊说明，一律认为是在虚拟机下操作 :)

​	你所需要做的事情也很简单：

```
sudo apt install bison build-essential flex libncurses5-dev ncurses-dev libelf-dev libssl-dev tar util-linux xz-utils
```

​	这些是你必须要有的，如果想要开发内核的话:)