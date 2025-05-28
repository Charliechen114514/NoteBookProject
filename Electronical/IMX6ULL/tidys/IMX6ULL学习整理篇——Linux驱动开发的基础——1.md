# Linux驱动开发框架基础——新旧字符设备驱动笔记整理（1）

​	前段时间是一直在学，没有整理笔记，这里把拉掉的课补上。整理一下笔记开发

## 前言

​	首先，各位需要知道的是。广义的说——Linux驱动开发的开发对象一般分成三个大类：字符设备，块设备和网络设备。实际上，Linux的驱动开发，笔者倾向于认为是在Linux的大框架下告知我们的Linux如何操作我们给定的设备。所以，想好我们如何操作设备是驱动开发的核心。也就是——我们如何告诉外界我们的设备的：**打开？关闭？读？写？以及其他的属性**。现在，我们就来开始尝试一下学习Linux驱动开发

## Linux的驱动开发是建立在LKM（Linux Kernel Module）上的

​	实际上，Linux的驱动开发是建立在LKM（Linux Kernel Module）上的，我必须再强调一次。一些朋友可能没有太多的接触内核，笔者也只是极端粗浅的接触过一点。实际上，LKM这个体系是为了缓解我们的设备日益增多导致内核体积快速膨胀的一个解决办法。你想想，我们的内核要具备通用性，就必须接受新设备的驱动，但是不是所有的用户，都有内核支持的所有设备，比如说，我的笔记本只有一种显卡，一种网卡，就完全没必要去让内核具备操作另一种显卡，网卡的能力：占地方也没处使。我不希望这些用不到的设备占据我们的内存，但是的确一部分人是需要的！这可咋办呢？

​	所以，我们就有了LKM体系。也就是说，**我们的驱动可以动态的加载进来，对于我们有的驱动，我们在系统开机，或者是设备热插拔进入的时候，加载我们的模块驱动**，让内核可以操纵我们的外设！从而让我们的内核具备非常强的灵活性！当然，LKM远比我说的要强大的多，这里只是给各位看官加点前菜。另外，当设备热插拔下去之后，我们也可以卸载驱动，让内核对外设的控制力从静态到动态。现在，我们就把内核和驱动特别种类的外设解耦合了。

​	**我们驱动开发的任务，就是提供模块文件给用户和内核，让内核通过我们的模块，得知操作外设的具体办法。**任何和内核相关的事情都已经被抽象为Linux的内核API直接调度就好。我们驱动开发人员完全可以少关心甚至是不关心内部实现（当然笔者的态度是——知道比不知道强，出问题了好想思路）

​	下面，笔者就开始简单的说一下模块开发的具体格式。

## 所以，一个Module要如何书写呢？

​	左工讲的非常的不错了。这里笔者按照自己的逻辑再梳理一下。

​	首先，我们的模块是动态插拔的，就必须像HAL_Init的函数和HAL_DeInit来告诉处理器如何处理加载和卸载的逻辑。就像我们插拔USB一样，插入的时候，我们可能要建立链接，通知应用程序插入事件和建一定的文件系统视图，卸载的时候要拆除链接，通知应用程序U盘拔出和拆除构建的文件系统等等。**这些都是伴随着模块的加载和卸载做的（注意不要和设备的打开和关闭混淆，这是两个不同的概念！）**

​	所以，我们写模块，一般而言——也要提供一个init和exit函数，来规定我们模块加载和卸载的动作（哦对了，一些模块可以无法卸载的！但是这个不属于我们讨论的范畴，笔者建议参考专门的LKM书籍，比如说Linux Kernel Programming进行系统的学习）。

​	我打算按照抛砖引玉的方式引出来我们的接口。

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");
static int __init chrdev_base_init(void)
{
    pr_info("Hello!This is a sample of printk!\n");
    return 0;
}

static void __exit chrdev_base_exit(void)
{
    pr_info("Goodbye!See you next time\n");
}

module_init(chrdev_base_init);
module_exit(chrdev_base_exit);
```

​	这就是一个最简单的模块的框架。先不着急，我们先看效果。

​	注意，我们需要写一份Makefile来调用我们的内核的Makefile完成构建。

```makefile
# 指向板子正在运行的内核源码
KDIR := /home/charliechen/linux_code_src/nxp
CURRENTDIR := $(shell pwd)
# 欸，别照着抄，自己先构建内核，然后指向基于NFS协议的Rootfs路径
RTFS_MODULE_TEST_PATH := ~/linux/nfs/rootfs/module_test/

obj-m := chrdev_base.o

.PHONY: all clean

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KDIR) M=$(CURRENTDIR) modules
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KDIR) M=$(CURRENTDIR) clean

upload:
	cp chrdev_base.ko $(RTFS_MODULE_TEST_PATH)
```

​	这个是一个参考的配置。谈不上优雅。实际上提供三个功能。

- all: 构建我们的模块，这里，我们指定了跟Linux内核模块构建一样的命令，实际上就是——补充构建我们写的内核源代码到一个可以被加载到**目标客户机的内核上的模块**
- clean: 清理，就是make clean的一个经典用法，注意最好使用内核的make clean!
- upload: 加载放到我们的nfs根文件系统上，nfs是动态的网络系统，所以我们一上传，板子那边就可以看到。

​	我们先构建，然后传到我们的板子上

```
make all
make upload
```

​	现在我们操作串口：

```shell
/module_do # ls
chrdev_base.ko
/module_do # insmod chrdev_base.ko 
Hello!This is a sample of printk!
/module_do # lsmod chrdev_base.ko 
Module                  Size  Used by    Tainted: G  
chrdev_base              705  0 
/module_do # rmmod chrdev_base.ko 
Goodbye!See you next time
```

> insmod是说：加载一个给定的模块文件
>
> lsmod是说：列举当前正在挂载的模块
>
> rmmod是说：移除一个给定的模块文件

​	尝鲜结束，下面就是认真的学习事件了。

## 刨析我们的最小模块源代码框架

​	非常短！但是必须按照这个框架作为基础一步一步扩展，这个框架非常重要以至于我必须再贴出来一次

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");
static int __init chrdev_base_init(void)
{
    pr_info("Hello!This is a sample of printk!\n");
    return 0;
}

static void __exit chrdev_base_exit(void)
{
    pr_info("Goodbye!See you next time\n");
}

module_init(chrdev_base_init);
module_exit(chrdev_base_exit);
```

module.h提供了一些模块相关的抽象机制，而kernel.h则是提供了内核支持的一些通用API。比如说我们下面谈论的pr_info。

> 提示：对了，正点原子的左工老师为了讲课，貌似没有配置c_cpp_properties.json，这里笔者再一次给出笔者的配置，配置结束后就不会有恼人的红线了：
>
> ```json
> {
>     "configurations": [
>         {
>             "name": "Linux",
>             "includePath": [
>                 "${workspaceFolder}/**",
>                 "/home/charliechen/linux_code_src/nxp/include", 
>                 "/home/charliechen/linux_code_src/nxp/arch/arm/include", 
>                 "/home/charliechen/linux_code_src/nxp/arch/arm/include/generated/"
>             ],
>             "defines": [                
>                 "__GNUC__",
>                 "__KERNEL__",
>                 "MODULE"
>             ],
>             "compilerPath": "/usr/bin/gcc",
>             "cStandard": "c11",
>             "cppStandard": "c++17",
>             "intelliSenseMode": "clang-x64"
>         }
>     ],
>     "version": 4
> }
> ```
>
> 不要照搬！！！！！！请你指向自己的内核构建根目录下的include, arch/arm/include和arm/include/generated/，注意内核必须先被构建，不然会缺少文件，没法开发内核模块！

​	MODULE_LICENSE是指定我们驱动代码的协议，你啥也不知道你就写GPL，跟内核的协议统一。不然就会炸Module Taint Kernel的错误。

​	MODULE_AUTHOR填写自己的开发名称——啊，你不是专业的就随便写几个字就好。

​	重点看下面的两个：

```c
static int __init chrdev_base_init(void)
{
    pr_info("Hello!This is a sample of printk!\n");
    return 0;
}

static void __exit chrdev_base_exit(void)
{
    pr_info("Goodbye!See you next time\n");
}

module_init(chrdev_base_init);
module_exit(chrdev_base_exit);
```

​	请注意，上面当中的`__init`标识符和`__exit`表述务必带上。我们的内核挂载和卸载是内存段敏感的。这两个函数会被放到特别的段叫init和exit段上，内核挂载，我们就执行放到`__init`段上的，被`module_init`声明的函数，卸载就是放到`__exit`段上函数，module_exit声明的函数上。这两个函数如你上面所见，是内核的构造和析构（insmod 和 rmmod）自动执行的！

​	此外，**内核对函数的私有还是公有是非常敏感的！对于私有函数必须带上static修饰符，对于导出的变量必须是无static修饰且被EXPORT_SYMBOL包裹放到内核特定的地址的位置上的！所以不要随意写代码！这不是规范问题而是技术问题！请不要违反，不要给自己埋坑！**

​	到这里，我们就把基本的元素说完了，下面我们进一步完善这个框架，让他逐渐可以使用

## 进一步搭建我们的字符设备开发框架

​	现在我们要进一步改造，让我们可以对字符设备做——打开操作，关闭操作，写操作和读操作。我们将会按照驱动LED作为一个模板。完成这个驱动的开发。

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");

// for the easy register_chardev, we have to specify the
// major dev number by ourselves, we shell use a intelligent
// char dev later
#define MAJOR_CHAR_DEV_N        (200)
#define CHRDEV_NAME             ("charliechen_chrdev")

/*
    when application wanna open the device
    which means ready to operate the device
    kernel will call the charliechen_chrdev_open
*/
static int charliechen_chrdev_open(struct inode* inode, struct file* file){
    pr_info("char device is open!\n");
    return 0;
}

/*
    when application wanna close the device
    which means finishing operating the device
    in current sessions, kernel will call 
    the charliechen_chrdev_release(not close)
*/
static int charliechen_chrdev_release(struct inode* inode, struct file* file){
    pr_info("char device is release!\n");
    return 0;
}

/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_read(
    struct file* file, char* buffer, size_t count, loff_t* pos)
{
    pr_info("ready to read the device\n");
    return 0;
}

/*
    write provides the functionalities
    of the device
*/
/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_write(
    struct file* file, const char* buffer, size_t count, loff_t* pos)
{
    pr_info("ready to write the device\n");
    return 0;
}

static struct file_operations 
my_chrdev_op = {
    .owner = THIS_MODULE,
    .open = charliechen_chrdev_open,
    .release = charliechen_chrdev_release,
    .read = charliechen_chrdev_read,
    .write = charliechen_chrdev_write,
};

static int __init chrdev_base_init(void)
{
    int result = 0;
    pr_info("Hello!This is a sample of printk!\n");
    pr_info("Ready to register the device\n");
    
    result = register_chrdev(MAJOR_CHAR_DEV_N, CHRDEV_NAME, &my_chrdev_op);
    if(result < 0){
        pr_warn("Error in registing char device\n");
        return -EINVAL;
    }
    
    return 0;
}

static void __exit chrdev_base_exit(void)
{
    pr_info("Goodbye!See you next time\n");
    unregister_chrdev(MAJOR_CHAR_DEV_N, CHRDEV_NAME);
}

module_init(chrdev_base_init);
module_exit(chrdev_base_exit);
```

​	我们很快看到了新的面孔。让我们盘点一下：

- register_chrdev和unregister_chrdev函数——注意，这两个函数只是作为学习的引子，实际开发中几乎被禁止使用了！

- file_operations是一个文件操作功能函数合集。是我们要完成填写的一个内容

- ```
  #define MAJOR_CHAR_DEV_N        (200)
  #define CHRDEV_NAME             ("charliechen_chrdev")
  ```

  是我们新添加稍后会使用到的定义

​	好，现在就让我们开始吧！

### 旧时代的残余：register_chrdev和unregister_chrdev

#### **`register_chrdev` 函数：**

```c
static inline int register_chrdev(unsigned int major, const char *name, const struct file_operations *fops)
```

- `major`：指定要注册的设备的主设备号。主设备号用于标识驱动程序类型。若设置为 0，内核将自动分配一个未使用的主设备号。
- `name`：指向设备名称的字符串指针，用于标识设备。
- `fops`：指向 `file_operations` 结构体的指针，该结构体包含设备的操作函数集合，如打开、读取、写入和释放等操作。

该函数返回一个整数值，表示注册操作的结果。成功时返回分配的主设备号，失败时返回负值。

#### **`unregister_chrdev` 函数：**

```c
static inline void unregister_chrdev(unsigned int major, const char *name)
```

- `major`：要注销的设备的主设备号。
- `name`：要注销的设备名称。

该函数用于从内核中注销先前注册的字符设备驱动，释放相关资源。

​	设备号，一个新的名词，关于这个事情，请你在板子的控制台上输入cat /proc/devices，这个是薄记了系统登级在案上的设备和它的号码。

```
module_do # cat /proc/devices
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  7 vcs
 10 misc
 13 input
 29 fb
 81 video4linux
 89 i2c
 90 mtd
116 alsa
128 ptm
136 pts
180 usb
189 usb_device
207 ttymxc
226 drm
250 ttyLP
251 watchdog
252 ptp
253 pps
254 rtc

...
```

​	如果你是硬件开发的老手，看到这些列举的东西会感觉回到了老家。对的！这些就是登记在案的驱动。前面的数字就是设备号，我们的内核按照设备号抓到**一簇设备**来，这一蔟设备代表使用同一种类型。比如说：我们上面你猜到了，就是讲200的设备号分配给我们的LED，现在内核一看到给定的设备号是200，就知道抓到的设备是LED！

### file_operations,告知上层和内核如何操作我们的驱动

​	我们的驱动设备，基本上都具备可读性，可写性，可以被打开，可以被关闭等等属性。啥，你说你来写？不用，Linux内核已经有了及其完备的文件系统抽象了，我们的设备被file_operations封装成了一个文件。办法就是告诉内核，你要按照咋read 咋write咋open咋release(这里对应了上层的close系统调用)。

​	我们register_chrdev函数的第三个参数就是告诉我们的设备如何操作。我们给结构体赋值的同时，就是告诉我们的内核如何操作我们的外设。注意的是——file_operations非常庞大，但是，你不赋值成员，说明你打算采用默认实现，内核内部自己有判断逻辑，非常感兴趣的朋友参考Linux的VFS体系，非常厚实，学到你满足的不想再看到VFS为止，哈哈！

```c
static struct file_operations 
my_chrdev_op = {
    .owner = THIS_MODULE,
    .open = charliechen_chrdev_open,
    .release = charliechen_chrdev_release,
    .read = charliechen_chrdev_read,
    .write = charliechen_chrdev_write,
};
```

​	笔者在上面就约束好了我们的驱动要如何被操作。其代码就在：

```c
/*
    when application wanna open the device
    which means ready to operate the device
    kernel will call the charliechen_chrdev_open
*/
static int charliechen_chrdev_open(struct inode* inode, struct file* file){
    pr_info("char device is open!\n");
    return 0;
}

/*
    when application wanna close the device
    which means finishing operating the device
    in current sessions, kernel will call 
    the charliechen_chrdev_release(not close)
*/
static int charliechen_chrdev_release(struct inode* inode, struct file* file){
    pr_info("char device is release!\n");
    return 0;
}

/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_read(
    struct file* file, char* buffer, size_t count, loff_t* pos)
{
    pr_info("ready to read the device\n");
    return 0;
}

/*
    write provides the functionalities
    of the device
*/
/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_write(
    struct file* file, const char* buffer, size_t count, loff_t* pos)
{
    pr_info("ready to write the device\n");
    return 0;
}
```

​	我们当然没有真正实现操作，只是写了一些logger函数观察。现在，我们还需要写一个用户程序来模拟我们的用户使用

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int check = 0;
    if(argc < 2){
        fprintf(stderr, "Hey, provide filename!\n");
        return -1;
    }

    char* filename = argv[1];
    check = open(filename, O_RDWR);
    if(check < 0){
        fprintf(stderr, "Hey, Error in open filename: %s!\n", filename);
        return -1;
    }
    char buffer[10];
    int result = read(check, buffer, 10);
    if(result < 0){
        fprintf(stderr, "Hey, Error in read! filename: %s!\n", filename);
        return -1;        
    }

    result = write(check, buffer, 10);
    if(result < 0){
        fprintf(stderr, "Hey, Error in write! filename: %s!\n", filename);
        return -1;        
    }    

    result = close(check);
    if(result < 0){
        fprintf(stderr, "Hey, Error in close device! filename: %s!\n", filename);
        return -1;        
    }        

    return 0;
}
```

​	可以凑合使用了！我们编译拷贝我们的应用程序和我们的模块到板子上

```
/module_do # ls
chrdev_application  chrdev_demo.ko
```

​	下一步，是创建用户态的操作句柄文件，使用的命令是mknod办法

```
mknod /dev/ccled c 200 0
```

​	也就是创建一个/dev/ccled文件，代表了一个主设备号为200次设备号为0的字符设备文件，对这个文件的读写将会自动转发到驱动模块上。也就是我们写的驱动上！

​	下面我们试一试：

```bash
/module_do # ls
chrdev_application  chrdev_demo.ko
/module_do # mknod /dev/ccled c 200 0
/module_do # lsmod
Module                  Size  Used by    Tainted: G  
/module_do # insmod chrdev_demo.ko 
Hello!This is a sample of printk!
Ready to register the device
/module_do # ./chrdev_application /dev/ccled 
char device is open!
ready to read the device
ready to write the device
char device is release!
/module_do # rmmod chrdev_demo.ko 
Goodbye!See you next time
```

​	我们的创建了一个/dev/ccled对应我们的字符设备，然后，我们挂载了内核模块（注意一定要应用程序操作之前挂载好模块，不然找不到我们的驱动，导致打开失败！）可以看到我们的应用程序一次打开，读，写和关闭我们的设备，看到日志中触发的输出。是不是有点感觉了？去试试！

## 来真的：实现一个可以传递信息的字符驱动

​	我知道你已经按耐不住了，我直接给你实现！

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");



// for the easy register_chardev, we have to specify the
// major dev number by ourselves, we shell use a intelligent
// char dev later
#define MAJOR_CHAR_DEV_N        (200)
#define CHRDEV_NAME             ("charliechen_chrdev")
#define BUFFER_X                (100)
static char read_buffer[BUFFER_X];
static char write_buffer[BUFFER_X];
static const char* kernel_info = "Hello!from chardev mornings!\n";

/*
    when application wanna open the device
    which means ready to operate the device
    kernel will call the charliechen_chrdev_open
*/
static int charliechen_chrdev_open(struct inode* inode, struct file* file){
    pr_info("char device is open!\n");
    return 0;
}

/*
    when application wanna close the device
    which means finishing operating the device
    in current sessions, kernel will call 
    the charliechen_chrdev_release(not close)
*/
static int charliechen_chrdev_release(struct inode* inode, struct file* file){
    pr_info("\nchar device is release!\n");
    return 0;
}

/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_read(
    struct file* file, char* buffer, size_t count, loff_t* pos)
{
    int ret = 0;
    memcpy(read_buffer, kernel_info, strlen(kernel_info));
    ret = copy_to_user(buffer, read_buffer, count);
    if(ret == 0){
        // null
    }else{
        pr_warn("Failed to handling the read session!\n");
    }
    return 0;
}

/*
    write provides the functionalities
    of the device
*/
/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_write(
    struct file* file, const char* buffer, size_t count, loff_t* pos)
{
    int ret = 0;
    ret = copy_from_user(write_buffer, buffer, count);
    if(ret == 0)
        pr_info("receive from write buffer: %s\n", write_buffer);
    else
        pr_warn("Failed to process write!\n");
    return 0;
}

static struct file_operations 
my_chrdev_op = {
    .owner = THIS_MODULE,
    .open = charliechen_chrdev_open,
    .release = charliechen_chrdev_release,
    .read = charliechen_chrdev_read,
    .write = charliechen_chrdev_write,
};

static int __init chrdev_base_init(void)
{
    int result = 0;
    pr_info("Hello!This is a sample of printk!\n");
    pr_info("Ready to register the device\n");
    
    result = register_chrdev(MAJOR_CHAR_DEV_N, CHRDEV_NAME, &my_chrdev_op);
    if(result < 0){
        pr_warn("Error in registing char device");
        return -EINVAL;
    }
    
    return 0;
}

static void __exit chrdev_base_exit(void)
{
    pr_info("Goodbye!See you next time\n");
    unregister_chrdev(MAJOR_CHAR_DEV_N, CHRDEV_NAME);
}

module_init(chrdev_base_init);
module_exit(chrdev_base_exit);
```

​	这里，我们重点改造的是模块的读写功能！

```c
/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_read(
    struct file* file, char* buffer, size_t count, loff_t* pos)
{
    int ret = 0;
    memcpy(read_buffer, kernel_info, strlen(kernel_info));
    ret = copy_to_user(buffer, read_buffer, count);
    if(ret == 0){
        // null
    }else{
        pr_warn("Failed to handling the read session!\n");
    }
    return 0;
}

/*
    write provides the functionalities
    of the device
*/
/*
    read provides the functionalities
    of the device
*/
static ssize_t charliechen_chrdev_write(
    struct file* file, const char* buffer, size_t count, loff_t* pos)
{
    int ret = 0;
    ret = copy_from_user(write_buffer, buffer, count);
    if(ret == 0)
        pr_info("receive from write buffer: %s\n", write_buffer);
    else
        pr_warn("Failed to process write!\n");
    return 0;
}
```

​	我们绕不过去函数的签名问题：

#### **`read` 函数：**

```c
ssize_t (*read) (struct file *filp, char __user *buf, size_t count, loff_t *pos);
```

- `filp`：指向表示已打开文件的 `struct file` 结构体的指针，包含文件的状态和配置信息。
- `buf`：指向用户空间缓冲区的指针，用于存放从设备读取的数据。
- `count`：请求读取的字节数。
- `pos`：指向文件偏移量的指针，表示从文件的哪个位置开始读取。

#### **`write` 函数：**

```c
ssize_t (*write) (struct file *filp, const char __user *buf, size_t count, loff_t *pos);
```

- `filp`：同样指向表示已打开文件的 `struct file` 结构体的指针。
- `buf`：指向用户空间缓冲区的指针，包含要写入设备的数据。
- `count`：请求写入的字节数。
- `pos`：指向文件偏移量的指针，表示从文件的哪个位置开始写入。

#### **`open` 函数：**

```c
int (*open) (struct inode *inode, struct file *filp);
```

- `inode`：指向表示文件的 `struct inode` 结构体的指针，包含文件的元数据信息。
- `filp`：指向表示已打开文件的 `struct file` 结构体的指针，包含文件的状态和配置信息。

`open` 函数在用户空间调用 `open()` 系统调用时被内核调用，用于执行设备特定的初始化操作。

#### **`release` 函数：**

```c
int (*release) (struct inode *inode, struct file *filp);
```

- `inode`：同样指向表示文件的 `struct inode` 结构体的指针。
- `filp`：指向表示已打开文件的 `struct file` 结构体的指针。

`release` 函数在用户空间调用 `close()` 系统调用时被内核调用，用于执行设备特定的清理操作。

### 提高警惕：用户态和内核态参数的传递不可以直接进行！

​	你会发现，我是用了两个看起来很多余的宏：copy_to_user和copy_from_user，这个是为什么呢？

​	我们知道：内核空间和用户空间在内存访问权限上存在严格的隔离，直接访问彼此的内存**可能导致安全问题或系统崩溃。**因此，这两个函数提供了一种安全的机制来进行数据拷贝。

​	我们的目的很简单：就是进行安全平稳的数据拷贝。

​	Linux 将内存分为内核空间和用户空间，以确保系统的稳定性和安全性。内核空间拥有最高权限，可以访问所有内存；而用户空间则受到限制，不能直接访问内核空间的内存。直接在内核中访问用户空间的指针可能导致非法内存访问，从而引发内核崩溃或安全漏洞。也就是实现安全的内存隔离下，对应接口的数据传递。

​	按照接口传递，我们就可以安全的检查我们传递的东西： `copy_to_user` 和 `copy_from_user` 在执行数据拷贝前，会对用户空间的指针进行检查，确保指针合法且可访问。这些检查包括验证指针是否指向有效的用户空间地址，是否存在越界等情况。这些函数通过调用内核提供的辅助函数，如 `access_ok`，来验证内存访问的合法性。如果我们发生了不该存在的异常，这些函数能够安全地捕获并处理这些异常，避免内核崩溃。这些函数使用了内核的异常表机制（`fixup` 和 `__ex_table`），在发生异常时跳转到预定义的处理代码，确保系统的稳定性。

#### **`copy_from_user` 函数：**

```c
unsigned long copy_from_user(void *to, const void __user *from, unsigned long n);
```

- **参数：**
  - `to`：指向内核空间目标缓冲区的指针，数据将被复制到此处。
  - `from`：指向用户空间源缓冲区的指针，数据将从此处读取。
  - `n`：要复制的字节数。
- **返回值：**
  - 返回未成功复制的字节数。如果返回值为 0，表示复制成功；如果返回值等于 `n`，表示复制失败。

#### **`copy_to_user` 函数：**

```c
unsigned long copy_to_user(void __user *to, const void *from, unsigned long n);
```

- **参数：**
  - `to`：指向用户空间目标缓冲区的指针，数据将被复制到此处。
  - `from`：指向内核空间源缓冲区的指针，数据将从此处读取。
  - `n`：要复制的字节数。
- **返回值：**
  - 返回未成功复制的字节数。如果返回值为 0，表示复制成功；如果返回值等于 `n`，表示复制失败。

#### 测试一下

​	点到为之，我们测试一下

##### 用户程序编写

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define ISSUE_BUFFER_N      (40)

static const char* user_data = "Hello from user!\n";

static void display_help(const char* app_name)
{
    fprintf(stderr, 
        "do: %s <dev_file> <operations>\n"
        "op: read : read the data from char dev\n"
        "op: write: write the data to char dev\n", app_name);
}

int main(int argc, char* argv[])
{
    int check = 0;
    if(argc != 3){
        display_help(argv[0]);
        return -1;
    }

    char* filename = argv[1];

    check = open(filename, O_RDWR);
    if(check < 0){
        fprintf(stderr, "Hey, Error in open filename: %s!\n", filename);
        return -1;
    }
    
    int result = 0;

    if(!strcmp(argv[2], "read")){
        // process reading issue
        printf("user process the read issue\n");
        char buffer[ISSUE_BUFFER_N];
        result = read(check, buffer, ISSUE_BUFFER_N);
        if(result < 0){
            fprintf(stderr, "Hey, Error in read! filename: %s!\n", filename);
            goto close_issue;   
        }
        printf("user receive from driver: %s\n", buffer);
        // done!
    }else if(!strcmp(argv[2], "write")){
        // process the write
        printf("user process the write issue\n\n\n");
        result = write(check, user_data, strlen(user_data));
        if(result < 0){
            fprintf(stderr, "Hey, Error in write! filename: %s!\n", filename);
            goto close_issue; 
        }    
    }else{
        display_help(argv[0]);
        goto close_issue;
    }

close_issue:
    result = close(check);
    if(result < 0){
        fprintf(stderr, "Hey, Error in close device! filename: %s!\n", filename);
        return -1;        
    }        

    return 0;
}
```

##### 实际使用测试

```
/module_test # ls
chrdev_application  chrdev_demo.ko
/module_test # insmod chrdev_demo.ko 
Hello!This is a sample of printk!
Ready to register the device
/module_test # ./chrdev_application /dev/ccled read
char device is open!
user process the read issue
char device is release!

user receive from driver: Hello!from chardev mornings!

/module_test # ./chrdev_application /dev/ccled write
char device is open!
user process the write issuereceive from write buffer: Hello from user!

char device is release!
/module_test # rmmod chrdev_demo.ko 
Goodbye!See you next time
/module_test # 
```



