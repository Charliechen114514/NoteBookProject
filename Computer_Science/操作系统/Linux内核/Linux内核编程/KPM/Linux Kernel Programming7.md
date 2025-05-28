# Linux Kernel Programming 8

## 传递参数给我们的内核

​	先说我们怎么传递给已经写好的模块，首先呢，我们传递模块必须要使用的是显著的键值对格式——也就是`<key>=<value>`，比如说`pass=20`的方式传递给我们的内核

​	对于我们写模块的人而言，需要做的是使用一个宏标注，叫做module_params，这里看一个非常小的例子：

```c
#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("Charliechen");
MODULE_DESCRIPTION("This is a params passer demo");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");

static int pass;
module_param(pass, int, 0660);
MODULE_PARM_DESC(pass, "A Interger waiting passed");


static int __init params_init(void)
{
    pr_info("inserted the params\n");
    pr_info("The module you passed for the params:"
        "pass=%d\n", pass
    );
    return 0;
}

static void __exit params_exit(void)
{
    pr_info("Good Bye!\n");
}

module_init(params_init);
module_exit(params_exit);
```

​	可以看到，我们的参数声明就多了这三行：

```
static int pass;
module_param(pass, int, 0660);
MODULE_PARM_DESC(pass, "A Interger waiting passed");
```

​	分别是——参数本身这个变量，`module_param` 和 `MODULE_PARM_DESC`着三个部分。

​	`module_param` 就是一个用来声明模块参数的宏：

```
module_param(name, type, perm);
```

- **name**: 参数的名称，通常是一个变量的名称。
- **type**: 参数的类型，可以是 `int`, `charp`（字符串指针）, `bool`, `ushort`, `uint`, `ulong` 等。
- **perm**: 参数的权限，用于控制该参数在 `/sys/module/<module_name>/parameters/` 目录下的访问权限。常见的权限值包括：
  - `S_IRUGO`: 只读权限，所有用户可读。
  - `S_IWUSR`: 写权限，仅 root 用户可写。
  - `S_IRUGO | S_IWUSR`: 所有用户可读，仅 root 用户可写。

​	`MODULE_PARM_DESC` 宏用于为模块参数提供描述信息。我们可以使用modinfo工具查看我们手头的参数：

```
charliechen@charliechen-VMware-Virtual-Platform:~/kernel_test/4$ modinfo params.ko
filename:       /home/charliechen/kernel_test/4/params.ko
version:        0.2
license:        GPL
description:    This is a params passer demo
author:         Charliechen
srcversion:     EBDAB9DA969412E0DB52D9F
depends:        
retpoline:      Y
name:           params
vermagic:       6.11.0-17-generic SMP preempt mod_unload modversions 
parm:           pass:A Interger waiting passed (int)
```

​	我们编译一下这个小项目：

```c
KDIR ?= /lib/modules/$(shell uname -r)/build
PWD            := $(shell pwd)
FNAME_C			:= params
obj-m          += ${FNAME_C}.o

all:
	make -C $(KDIR) M=$(PWD) modules
.PHONY: clean

clean:
	make -C $(KDIR) M=$(PWD) clean
```

​	然后按照我们喜欢的方式挂载上去

```
sudo insmod params.ko pass=20
sudo dmesg
[  594.303070] inserted the params
[  594.303074] The module you passed for the params:pass=100
```

​	关于参数，我们还可以去/sys/module/下看看：

```
charliechen@charliechen-VMware-Virtual-Platform:/sys/module$ ls | grep params
params
```

​	进入我们的params后，你会发现有不少东西，我们关心的文件夹是parameters,进入这个文件夹，就会看到

```
charliechen@charliechen-VMware-Virtual-Platform:/sys/module/params/parameters$ ls -l
total 0
-rw-rw---- 1 root root 4096 Mar  8 18:42 pass
```

​	我们可以读取这个文件，看看里面写着啥：

```
charliechen@charliechen-VMware-Virtual-Platform:/sys/module/params/parameters$ sudo cat pass
100
```

​	啊哈，就是我们传递给这个模块的值

## 验证我们的参数

​	我们可以验证参数，办法是我们手动检查（这是一种办法）我们的参数是不是合法的，请看：

```
#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("Charliechen");
MODULE_DESCRIPTION("This is a params passer demo");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");

static int pass;
module_param(pass, int, 0660);
MODULE_PARM_DESC(pass, "A Interger waiting passed");

static int check;
module_param(check, int, 0660);
MODULE_PARM_DESC(check, "Authentics");

static int __init params_init(void)
{
    pr_info("inserted the params\n");
    pr_info("The module you passed for the params:"
        "pass=%d\n", pass
    );

    if (check < 1 || check > 100)
    {
        pr_warn("Wrong Password, die!");
        return -EINVAL;
    }
    
    return 0;
}

static void __exit params_exit(void)
{
    pr_info("Good Bye!\n");
}

module_init(params_init);
module_exit(params_exit);

```

​	参数不合法时，我们直接返回-EINVAL表达参数非法，当我们没有指定正确的参数的时候：

```
charliechen@charliechen-VMware-Virtual-Platform:~/kernel_test/4$ sudo insmod params.ko
insmod: ERROR: could not insert module params.ko: Invalid parameters
```

​	可以看到我们会触发检查。