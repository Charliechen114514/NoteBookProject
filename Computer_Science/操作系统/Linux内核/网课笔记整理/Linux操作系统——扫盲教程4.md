# Linux操作系统——扫盲教程4

## 在Linux下阅读Linux的源码

​	我们很快就要正式开始Linux内核的学习了！学习源码绝对逃不了阅读源码。想要舒服的阅读源码也是有一番讲究。笔者这里采用的配置是：Vscode + GGlobal/GTags的办法来阅读C/C++的代码。下面给一下配置方法。

### 笔者的环境

1. Ubuntu发行版，运行在WSL上，意味着我可以使用VSCode远程连到WSL上直接在Windows下舒舒服服看源码

### 第一步：下载Global

​	请各位在自己所用的包管理器上搜索global这个package。笔者运行的Ubuntu只需要：

```
sudo apt install global
```

​	就可以fetch到这个包。

​	随后在VSCode中下载global 插件。现到这里。

### 第二步：fetch Linux源码

​	WSL上笔者采用的办法是wget：

```
wget url/to/linux/source/code
```

​	笔者想要看看最新的Linux内核实现，因此下载的是6.11.2的源码：

```
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.11.2.tar.xz
```

​	下载后解压：

```
tar -xf https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.11.2.tar.xz
```

​	笔者将之移动到了这个文件夹：

```
mv ./linux-6.11.2/* ./linux_source_code/
```

​	这个linux_source_code就是我们的内核源码文件夹了。

### 第三步：修改inotify参数

​	由于inotify 是 Linux 下监控文件变化的工具，当系统的文件发生变化时，可以发送通知到应用层。这是为什么呢？这是因为我们想要加载各个符号之间的关系的时候很有可能超出本来系统设置的默认inotify文件数目导致下层系统调用失败返回ENOSPC。这就需要我们调大它同时能监控的文件数量

​	调整`/etc/sysctl.conf` 文件，追加一行：

```
fs.inotify.max_user_watches=524288
```

​	生效我们的更改：

```
sudo sysctl -p
```

### 第四步：配置我们的Code下的Global工具使之生效

​	我们需要新建一个.vscode文件夹（如果有就直接进去），进入后新建一个settings.json

```
{
	"gnuGlobal.globalExecutable": "/usr/bin/global",
    "gnuGlobal.gtagsExecutable": "/usr/bin/gtags",
    "gnuGlobal.objDirPrefix": "/home/charliechen/linux_source_code/.global",
}
```

​	怎么看globalExecutable在哪呢？很简单：whereis global和whereis gtags就完事了。

​	生成的中间依赖文件视各位看官而定，笔者偷懒放到源码目录底下的.global文件夹了（没有的新建，确保存在这个中间文件夹存在就行）

​	检查我们的插件是不是工作正常：F1打开工作区输入Show GNU Global Version，看看你的右下角有没有出版本信息。

​	有的话执行 `Rebuild Gtags Database`，稍等片刻，你的.global文件夹会特别巨大。里面存储的就是各个符号之间的依赖关系。

### (选择)可是我的符号加载还是缓慢

​	笔者的原因是Intellesence C/C++在作祟，因为它也在解析所有的符号。测试的办法就是讲自己的光标移动到任何符号上，发现“正在加载”就说明Global几乎没有工作，需要禁用Intellesence C/C++。它的符号解析实在不敢恭维，让我们的Global插件工作即可



# Reference

[阅读 Linux 内核源码的正确姿势 - 个人文章 - SegmentFault 思否](https://segmentfault.com/a/1190000039302294)