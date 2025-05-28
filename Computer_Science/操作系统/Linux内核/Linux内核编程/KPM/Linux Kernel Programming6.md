# Linux Kernel Programming 6

## 所以，有没有类似于库功能一般的开发方式呢

​	用户模式和内核模式编程之间的主要区别之一是后者完全没有熟悉的“库”概念。

​	我们学过软件工程的朋友知道。对于一部分提供了更加通用功能的代码。比起来直接复制，我们更喜欢将这些通用功能集合在一起，构成一个叫做库的东西。

​	库本质上是 API 的集合或存档，方便开发人员实现这些重要目标：不重新发明轮子、软件重用、模块化、可移植性等。但是，我们的Linux内核中，因为本身就是一种最底层的软件，所以经典意义的库实际上很难说是存在的。我们的库本身按照源代码的形式放到了我们的构建中。

​	我们难道搞模块的开发就没办法了嘛？答案是——不是，还是有的

## 模式1：在源代码层次集合成单一模块

​	这个方式大家最熟悉了。我们编写多个函数放到不同的文件，也就是被抽象成不同的模块最终链接到一起完成了一个模块的构成。在内核Makefile上，我们的格式大致看起来是这样的：

```
obj-m      := projx.o 
projx-objs := prj1.o prj2.o prj3.o
```

​	我们最终产出的是一个叫做projx.ko的模块文件，其由obj-m约束。而projx-objs约定了projx.o由何些子目标文件集合。这样，我们就可以在逻辑意义（直接指定哪一个是我们的library，但是链接的时候按照若干普通的源文件链接）

### 库是由私有和共有接口的，那这种方式可以做到嘛

​	可以！当然，这个需要你使用的内核是2.6之后的。在之前，我们写入的所有的驱动都是直接安排进入内核，对于内核而言，我们的所有的symbols都是可见的。这非常的不安全，很难以保证符号的问题。所以在这之后，我们的模块的所有的符号默认都要求是文件私有的，自己内部使用的而不是暴露到内核层的。这样的事情，体现在我们编程的时候被要求使用static约束我们的符号。

​	那，我们要求一定要导出我们的符号，咋办呢？答案是不使用static，而且使用EXPORT_SYMBOL宏将符号导出到外面模块可以使用的地方

## 模式二：模块堆叠

​	模块堆叠是一个概念，在某种程度上，它为内核模块作者提供了“类似库”的功能。在这里，我们通常以这样的方式构建我们的项目或产品设计，即我们有一个或多个“核心”内核模块，其工作是充当某种库。它将包括将导出到项目中的其他内核模块（以及任何其他想要使用它们的人；上一节讨论了这一点）的数据结构和功能（函数/API）。也就说，我们是在二进制层次完成我们的依赖而不是源码层次。

​	从这个角度上看，这个方式更加像我们使用一个库在做开发。我们下面来测试一下是不是这样的

### library level module

​	我们写一个这样的应用。我们要从一个库模块获取点东西，比如说：

```c
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual MIT/GPL");

int exposed_int = 114514;
// symbols will be exported for usage
EXPORT_SYMBOL(exposed_int);

long fetch_key(long secret);

long fetch_key(long secret)
{
    long result;
    if(secret == 0x1919810){
        pr_info("Secret Accessed! Succesfully authentics!");
        result = 20040303;
    }else{
        pr_info("Secret mismatch! won't do anything...");
        result = 0;
    }
    return result;
}
EXPORT_SYMBOL(fetch_key);

static int __init lib_lkm_init(void)
{
	pr_info("inserted\n Symbols will be loaded into kernel\n");
	return 0;	/* success */
}
static void __exit lib_lkm_exit(void)
{
	pr_info("Goodbye Library LKM\n");
}

module_init(lib_lkm_init);
module_exit(lib_lkm_exit);
```

​	非常的简单，就是将我们的功能写入了模块当中，导出了一个函数fetch_key和exposed_int作为我们的导出符号给我们马上登场的应用层模块使用。

### user level module

```c
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual MIT/GPL");

extern long fetch_key(long secret);
extern int exposed_int;


static int __init user_lkm_init(void)
{
    pr_info("User kernel mod is inserted!");
    u64 remote_key = fetch_key(0x1919810);
    pr_info("Called fetch_key(), ret = 0x%llx = %llu\n", remote_key, remote_key);
    pr_info("We also fetch the remote exp int as %d, which is defined at remote", exposed_int);
    return 0;
}

static void __exit user_lkm_exit(void)
{
    pr_info("Goodbye, my friend! resp from %s", __func__);
}

module_init(user_lkm_init);
module_exit(user_lkm_exit);
```

​	对于用户层，我们实际上就是使用了Library Level的模块导出的功能。

​	现在我们写一个简单的MakeFile脚本编译一下：

```makefile
KDIR = /lib/modules/$(shell uname -r)/build
PWD            := $(shell pwd)
obj-m          := lib_lkm.o
obj-m          += user_lkm.o


.PHONY: all clean

all:
	make -C ${KDIR} M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
```

​	我们首先尝试一下，把应用层模块先挂上去：

```
$ sudo insmod user_lkm.ko
insmod: ERROR: could not insert module user_lkm.ko: Unknown symbol in module
```

​	显然这是很正常的，查看我们的dmesg看看它抱怨了什么呢？

```
[ 3906.476881] user_lkm: Unknown symbol exposed_int (err -2)
[ 3906.476896] user_lkm: Unknown symbol fetch_key (err -2)
```

​	啊哈，这是说明了我们存在没有被决议的符号，的确，因为我们甚至没有挂载我们的库模块。所以，让我们按照依赖顺序，依次挂载模块先。

```
[ 4004.228654] inserted
                Symbols will be loaded into kernel
[ 4009.852012] User kernel mod is inserted!
[ 4009.852015] Secret Accessed! Succesfully authentics!
[ 4009.852016] Called fetch_key(), ret = 0x131ca6f = 20040303
```

​	没问题！，现在我们的内核被正常的挂载了！

​	所以，我们猜测卸载的时候，也需要按照依赖链倒过来卸载。

```
$ sudo rmmod lib_lkm.ko 
rmmod: ERROR: Module lib_lkm is in use by: user_lkm
```

​	果然，因为我们的符号还在被依赖，所以：

```
[ 4004.228654] inserted
                Symbols will be loaded into kernel
[ 4009.852012] User kernel mod is inserted!
[ 4009.852015] Secret Accessed! Succesfully authentics!
[ 4009.852016] Called fetch_key(), ret = 0x131ca6f = 20040303
[ 4009.852019] We also fetch the remote exp int as 114514, which is defined at remote
[ 4106.987699] Goodbye, my friend! resp from user_lkm_exit
[ 4108.014042] Goodbye Library LKM
charliechen@charliechen-VMware-Virtual-
```

​	完美！