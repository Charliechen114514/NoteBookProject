# IMX6ULL学习整理篇——Linux驱动开发的基础3：向新框架迁移

## 前言

​	笔者说过，咱们之前使用的框架是老框架，开发是不推介使用的。我们学习只是为了先入门，理解一下流程，下面，我们来学习一下新框架字符设备的注册办法。

## 老字符设备框架为什么不好？

​	两个原因：

- **设备号分配的局限性：** 使用 `register_chrdev` 时，开发者需要指定主设备号（`major`）。如果将 `major` 参数设置为 0，系统会动态分配一个未使用的主设备号。然而，这种方式可能导致设备号冲突，或者占用不必要的次设备号范围，造成资源浪费。 
- **资源管理的复杂性：** `register_chrdev` 函数在注册字符设备时，会自动分配并注册一个字符设备结构（`cdev`）。这种自动管理方式可能导致资源管理上的复杂性，增加了驱动程序的维护难度。 
- 没有剥离：申请设备号和建立对字符设备管理的分离，造成很高的耦合。

​	举个例子，我只是想点一个LED，结果把所有主设备号为114下的次设备号全给占用了，而且，还不够智能。所以，我们需要一个资源分配更加细腻的框架，这就是为什么我们要向新框架迁移的原因。不必担心，改动几乎不大。这就是抽象的好处。

## 所以，在新的框架中，我们如何改进我们的程序？

### 善用结构体完成我们的抽象

​	我们可以使用结构体来增加自己的实现，而无需改动接口来完成我们的抽象。这一点，笔者设计了一个结构体。

```c
/* we use a device struct */
typedef struct __myled {
    struct cdev char_dev_handle;
    dev_t       dev_id;
    int         major;
    int         minor;
}MyLED;

static MyLED myled;
```

​	关于cdev，我们下面会展开详细的介绍，这里先不着急说明。

### 使用register_chrdev_region和alloc_chrdev_region函数来完善我们的申请机制，使用unregister_chrdev_region来完成设备号的归还

​	`register_chrdev_region` 和 `alloc_chrdev_region` 是用于分配和注册字符设备号的两个重要函数。它们的主要区别在于设备号的分配方式：`register_chrdev_region` 需要开发者提供主设备号，而 `alloc_chrdev_region` 则由内核动态分配主设备号。

#### **`register_chrdev_region` 函数：**

该函数用于在已知主设备号的情况下，注册一组连续的字符设备号。当开发者已经确定要使用的主设备号且确保其未被占用时，使用此函数。需要注意的是，使用前应检查 `/proc/devices` 以确保所选的主设备号未被占用。

```c
int register_chrdev_region(dev_t from, unsigned count, const char *name);
```

- `from`：要分配的设备编号范围的起始值，包含主设备号和次设备号。
- `count`：需要分配的连续设备号的数量。
- `name`：与设备号关联的设备名称。

#### **`alloc_chrdev_region` 函数：**

该函数用于在主设备号未知的情况下，向内核动态申请未被占用的设备号。当开发者不确定或不关心具体的主设备号时，使用此函数让内核自动分配一个未被使用的主设备号。这种方式更简便，避免了手动选择主设备号可能引发的冲突。

```c
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
```

- `dev`：指向 `dev_t` 类型的指针，用于存储分配到的设备号。
- `baseminor`：次设备号的起始值。
- `count`：需要分配的连续设备号的数量。
- `name`：与设备号关联的设备名称。

#### `unregister_chrdev_region` 函数

`unregister_chrdev_region` 函数用于释放之前通过 `register_chrdev_region` 或 `alloc_chrdev_region` 分配的设备号。 

```c
void unregister_chrdev_region(dev_t from, unsigned count);
```

- `from`：要释放的设备号范围的起始值，通常使用 `MKDEV(major, minor)` 宏来生成。
- `count`：需要释放的连续设备号的数量。

在字符设备驱动程序的卸载函数中，`unregister_chrdev_region` 通常与 `cdev_del` 搭配使用，以确保设备号和字符设备对象都被正确释放，避免资源泄漏。 通过正确使用 `unregister_chrdev_region`，可以确保字符设备驱动在卸载时释放相应的设备号资源，维护系统资源的有效管理。

### 使用cdev体系升级我们的字符设备管理

​	现在，需要出场我们的cdev体系下的函数了。一般的，我们实际上就是用下面这三个函数完成管理一个字符设备：`cdev_init`、`cdev_add` 和 `cdev_del` 

#### **`cdev_init` 函数：**

`cdev_init` 用于初始化 `cdev` 结构体，并将其与文件操作结构体（`file_operations`）关联。我们在注册字符设备之前，必须先初始化 `cdev` 结构体，并将其与相应的文件操作函数关联。

```c
void cdev_init(struct cdev *cdev, const struct file_operations *fops);
```

- `cdev`：指向需要初始化的 `cdev` 结构体的指针。
- `fops`：指向实现该设备操作的 `file_operations` 结构体的指针。

#### **`cdev_add` 函数：**

`cdev_add` 将初始化后的 `cdev` 结构体添加到内核，使其在系统中生效。在初始化 `cdev` 结构体后，调用 `cdev_add` 将其注册到内核，使设备可供用户空间访问。

```c
int cdev_add(struct cdev *p, dev_t dev, unsigned count);
```

- `p`：指向已初始化的 `cdev` 结构体的指针。
- `dev`：设备号，包含主设备号和次设备号。
- `count`：要注册的连续设备号的数量。

- 成功时返回 0；失败时返回负的错误码。

#### **`cdev_del` 函数：**

`cdev_del` 从内核中移除已注册的 `cdev` 结构体，通常在驱动卸载时调用。在卸载字符设备驱动时，调用 `cdev_del` 从内核中移除设备，释放资源。

```c
void cdev_del(struct cdev *p);
```

- `p`：指向要删除的 `cdev` 结构体的指针。

## 实际升级的结果

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");

#define LED_DEV_NAME            ("charlies_led")
#define LED_DEV_N               (1)
/* 
    LED Physical Address 
        See the manual
*/
#define CCM_CCGR1_BASE          (0x020C406C)
#define GPIO1_IOLED_BASE        (0x020E0068)
#define GPIO1_IOPAD_BASE        (0x020E02F4)
#define GPIO1_IODR_BASE         (0x0209C000)
#define GPIO1_GDIR_BASE         (0x0209C004)

/* mappings of the io phe*/
static void* __iomem LED_CCGR1;
static void* __iomem LEDBASE;
static void* __iomem LEDPAD_BASE;
static void* __iomem LEDDR_BASE;
static void* __iomem LEDGDIR_BASE;

/* we use a device struct */
typedef struct __myled {
    struct cdev char_dev_handle;
    dev_t       dev_id;
    int         major;
    int         minor;
}MyLED;

static MyLED myled;

/* operations cached */
static char operations_cached[20];


static void __led_turn_on(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    val &= ~(1 << 3);
    writel(val, LEDDR_BASE);
}

static void __led_turn_off(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    val |= (1 << 3);
    writel(val, LEDDR_BASE);
}

static u8 __fetch_led_status(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    return !(val & (1 << 3));
}

static void __enable_led_mappings(void)
{
    int val = 0;
    pr_info("Ready to mappings the registers...\n");
    LED_CCGR1 = ioremap(CCM_CCGR1_BASE, 4);
    LEDBASE = ioremap(GPIO1_IOLED_BASE, 4);
    LEDPAD_BASE = ioremap(GPIO1_IOPAD_BASE, 4);
    LEDDR_BASE = ioremap(GPIO1_IODR_BASE, 4);
    LEDGDIR_BASE = ioremap(GPIO1_GDIR_BASE, 4);
    pr_info("mappings the registers done!\n");

    pr_info("LED_CCGR1     ioremap to: %p\n", LED_CCGR1);
    pr_info("LEDBASE       ioremap to: %p\n", LEDBASE);
    pr_info("LEDPAD_BASE   ioremap to: %p\n", LEDPAD_BASE);
    pr_info("LEDDR_BASE    ioremap to: %p\n", LEDDR_BASE);
    pr_info("LEDGDIR_BASE  ioremap to: %p\n", LEDGDIR_BASE);

    pr_info("initialize the led registers\n");
    
    val = readl(LED_CCGR1);
    // clear the bits
    val &= ~(3 << 26);
    val |= (3 << 26);
    writel(val, LED_CCGR1);

    writel(0x5, LEDBASE);
    writel(0x10B0, LEDPAD_BASE);

    val = readl(LEDGDIR_BASE);
    val |= 1 << 3;
    writel(val, LEDGDIR_BASE);

    pr_info("operations of led is accessable!\n");
}

static void __disable_led_mappings(void)
{
    __led_turn_off();
    pr_info("set the led turning off...\n");
    pr_info("set the led turning off done!\n");
    pr_info("Ready to unmappings the registers...\n");    
    iounmap(LED_CCGR1);
    iounmap(LEDBASE);
    iounmap(LEDPAD_BASE);
    iounmap(LEDDR_BASE);
    iounmap(LEDGDIR_BASE);
    pr_info("unmappings the registers done\n");
}


static ssize_t led_read(struct file* filp, char* buffer, 
    size_t count, loff_t* ppos)
{
    const char* status = "opened";
    int ret = 0;
    pr_info("\nled device is reading!\n");
    if(!__fetch_led_status()){
        status = "closed";
    } 
    ret = copy_to_user(buffer, status, strlen(status));
    if(ret < 0)
    {
        pr_warn("Copy to the user failed\n");
        return -EFAULT;
    }
    return 0;
}

static ssize_t led_write(struct file* filp,const char* buffer, 
    size_t count, loff_t* ppos)
{
    int check = 0;
    pr_info("\nled device is ready writing!\n");
    check = copy_from_user(operations_cached, buffer, count);
    if(check < 0){
        pr_warn("Can not copy from user!\n");
        return -EFAULT;
    }

    if(!strcmp(operations_cached, "open")){
        __led_turn_on();
    }else if(!strcmp(operations_cached, "close")){
        __led_turn_off();
    }else{
        pr_warn("Can not find the indications operations!\n"
                "check the business: %s", operations_cached);
    }
    return 0;
}

static int led_open(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is opened!\n");
    return 0;
}

static int led_close(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is released!\n");
    return 0;
}

static const struct file_operations led_ops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_close,
    .write = led_write,
    .read = led_read
};


/* register the device */
static int __init led_init(void)
{
    int ret = 0;
    if(myled.major){
        myled.dev_id = MKDEV(myled.major, 0);
        ret = register_chrdev_region(myled.dev_id, LED_DEV_N, LED_DEV_NAME);
    }else{
        ret = alloc_chrdev_region(&myled.dev_id, 0, LED_DEV_N, LED_DEV_NAME);
        myled.major = MAJOR(myled.dev_id);
        myled.minor = MINOR(myled.dev_id);
    }

    if(ret < 0){
        pr_warn("Error in registering the device! Failed to register the region\n");
        return -EIO;
    }

    pr_info("Success in registering the device major=%d, minor=%d\n",
            myled.major, myled.minor);
    myled.char_dev_handle.owner = THIS_MODULE;
    cdev_init(&(myled.char_dev_handle), &led_ops);
    ret = cdev_add(&(myled.char_dev_handle), myled.dev_id, LED_DEV_N);
    __enable_led_mappings();
    return 0;
}

static void __exit led_deinit(void)
{
    cdev_del(&(myled.char_dev_handle));
    unregister_chrdev_region(myled.dev_id, LED_DEV_N);
    __disable_led_mappings();
    pr_info("Successfully unregister the device\n");
}

module_init(led_init);
module_exit(led_deinit);
```

​	重点看看led_init和led_deinit函数，我们改造的区域就在这里。

## 测试

​	用户程序不用改，直接拿来用，现象和上一篇博客是一致的！

```
/module_test # ls
chrdev_application  led.ko
/module_test # insmod led.ko
Success in registering the device major=249, minor=0
Ready to mappings the registers...
mappings the registers done!
LED_CCGR1     ioremap to: f42c406c
LEDBASE       ioremap to: f42e0068
LEDPAD_BASE   ioremap to: f42e02f4
LEDDR_BASE    ioremap to: a09e6000
LEDGDIR_BASE  ioremap to: a09ee004
initialize the led registers
operations of led is accessable!
/module_test # mknod /dev/ccled c 249 0
/module_test # ./chrdev_application /dev/ccled read

led device is opened!
user process the read issue
led device is reading!

user receive from driver: closed
led device is released!
v 
/module_test # ./chrdev_application /dev/ccled write open

led device is opened!
args: 4
led device is ready writing!

user process the write issue: o
led device is released!
pen
/module_test # ./chrdev_application /dev/ccled write close

led device is opened!
args: 4
led device is ready writing!

user process the write issue: c
led device is released!
lose
/module_test # rmmod led.ko 
set the led turning off...
set the led turning off done!
Ready to unmappings the registers...
unmappings the registers done
Successfully unregister the device
```

## 使用device类将我们的创建设备文件自动化

​	妈蛋！实在太麻烦了，我们还要看申请到了啥设备号才能创建设备文件，多麻烦啊，能不能自动申请呢？答案是可以的！

### device文件框架

​	在之前的 Linux 驱动开发实验中，我们在使用 `modprobe` 加载驱动程序后，需要通过 `mknod` 命令手动创建设备节点。然而，通过在驱动程序中实现自动创建设备节点的功能，我们可以在使用 `modprobe` 加载驱动模块成功后，自动在 `/dev` 目录下创建相应的设备文件。

#### **mdev 机制**

​	在 Linux 系统中，`udev` 是一个用户空间程序，用于动态管理设备文件的创建与删除。它能够检测系统中的硬件设备状态，根据变化来创建或删除设备文件。例如，当使用 `modprobe` 命令成功加载驱动模块后，`udev` 会自动在 `/dev` 目录下创建对应的设备节点文件；使用 `rmmod` 命令卸载驱动模块后，`udev` 会删除 `/dev` 目录下的相应设备节点文件。在嵌入式 Linux 中，`busybox` 提供了一个简化版的 `udev`，称为 `mdev`。`mdev` 适用于嵌入式环境，用于实现设备节点文件的自动创建与删除。Linux 系统中的热插拔事件也由 `mdev` 管理。

​	为了使 `mdev` 管理热插拔事件，需要在系统启动脚本（例如 `/etc/init.d/rcS`）中添加如下语句：

```bash
echo /sbin/mdev > /proc/sys/kernel/hotplug
```

上述命令设置热插拔事件由 `mdev` 来管理。

**创建和删除类**

要实现自动创建设备节点的功能，首先需要在驱动程序的入口函数中创建一个类（`class`）。`class` 是一个结构体，定义在内核头文件 `include/linux/device.h` 中。这个class可以认为是内核类的父类！可以使用 `class_create` 函数来创建类，其宏定义如下：

```c
#define class_create(owner, name)     \
({                                        \
  static struct lock_class_key __key; \
  __class_create(owner, name, &__key);    \
})
```

展开宏后，函数原型为：

```c
struct class *__class_create(struct module *owner, const char *name,
                                  struct lock_class_key *key);
```

其中，参数 `owner` 一般为 `THIS_MODULE`，参数 `name` 是类的名称。返回值是指向结构体 `class` 的指针，即创建的类。在卸载驱动程序时，需要删除创建的类，使用 `class_destroy` 函数，其原型为：

```c
void class_destroy(struct class *cls);
```

参数 `cls` 是要删除的类。

**创建设备**

创建好类后，还需要在该类下创建设备。可以使用 `device_create` 函数在类下创建设备，其原型为：

```c
struct device *device_create(struct class *class,
                              struct device *parent,
                              dev_t devt,
                              void *drvdata,
                              const char *fmt, ...);
```

- `class`：设备要创建在哪个类下。
- `parent`：父设备，通常为 `NULL`，表示没有父设备。
- `devt`：设备号。
- `drvdata`：设备可能会使用的一些数据，通常为 `NULL`。
- `fmt`：设备名称，如果设置为 `xxx`，则会生成 `/dev/xxx` 这个设备文件。

返回值是创建的设备指针。同样地，在卸载驱动时，需要删除创建的设备，使用 `device_destroy` 函数，其原型为：

```c
void device_destroy(struct class *class, dev_t devt);
```

参数 `class` 是要删除的设备所处的类，参数 `devt` 是要删除的设备号。

## 完善我们的设备驱动

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");

#define LED_DEV_NAME            ("charlies_led")
#define LED_DEV_N               (1)
/* 
    LED Physical Address 
        See the manual
*/
#define CCM_CCGR1_BASE          (0x020C406C)
#define GPIO1_IOLED_BASE        (0x020E0068)
#define GPIO1_IOPAD_BASE        (0x020E02F4)
#define GPIO1_IODR_BASE         (0x0209C000)
#define GPIO1_GDIR_BASE         (0x0209C004)

/* mappings of the io phe*/
static void* __iomem LED_CCGR1;
static void* __iomem LEDBASE;
static void* __iomem LEDPAD_BASE;
static void* __iomem LEDDR_BASE;
static void* __iomem LEDGDIR_BASE;

/* we use a device struct */
typedef struct __myled {
    struct cdev char_dev_handle;
    dev_t       dev_id;
    int         major;
    int         minor;
    struct class*   led_class_handle; 
    struct device*  led_handle_device;
}MyLED;

static MyLED myled;

/* operations cached */
static char operations_cached[20];


static void __led_turn_on(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    val &= ~(1 << 3);
    writel(val, LEDDR_BASE);
}

static void __led_turn_off(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    val |= (1 << 3);
    writel(val, LEDDR_BASE);
}

static u8 __fetch_led_status(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    return !(val & (1 << 3));
}

static void __enable_led_mappings(void)
{
    int val = 0;
    pr_info("Ready to mappings the registers...\n");
    LED_CCGR1 = ioremap(CCM_CCGR1_BASE, 4);
    LEDBASE = ioremap(GPIO1_IOLED_BASE, 4);
    LEDPAD_BASE = ioremap(GPIO1_IOPAD_BASE, 4);
    LEDDR_BASE = ioremap(GPIO1_IODR_BASE, 4);
    LEDGDIR_BASE = ioremap(GPIO1_GDIR_BASE, 4);
    pr_info("mappings the registers done!\n");

    pr_info("LED_CCGR1     ioremap to: %p\n", LED_CCGR1);
    pr_info("LEDBASE       ioremap to: %p\n", LEDBASE);
    pr_info("LEDPAD_BASE   ioremap to: %p\n", LEDPAD_BASE);
    pr_info("LEDDR_BASE    ioremap to: %p\n", LEDDR_BASE);
    pr_info("LEDGDIR_BASE  ioremap to: %p\n", LEDGDIR_BASE);

    pr_info("initialize the led registers\n");
    
    val = readl(LED_CCGR1);
    // clear the bits
    val &= ~(3 << 26);
    val |= (3 << 26);
    writel(val, LED_CCGR1);

    writel(0x5, LEDBASE);
    writel(0x10B0, LEDPAD_BASE);

    val = readl(LEDGDIR_BASE);
    val |= 1 << 3;
    writel(val, LEDGDIR_BASE);

    pr_info("operations of led is accessable!\n");
}

static void __disable_led_mappings(void)
{
    __led_turn_off();
    pr_info("set the led turning off...\n");
    pr_info("set the led turning off done!\n");
    pr_info("Ready to unmappings the registers...\n");    
    iounmap(LED_CCGR1);
    iounmap(LEDBASE);
    iounmap(LEDPAD_BASE);
    iounmap(LEDDR_BASE);
    iounmap(LEDGDIR_BASE);
    pr_info("unmappings the registers done\n");
}


static ssize_t led_read(struct file* filp, char* buffer, 
    size_t count, loff_t* ppos)
{
    const char* status = "opened";
    int ret = 0;
    pr_info("\nled device is reading!\n");
    if(!__fetch_led_status()){
        status = "closed";
    } 
    ret = copy_to_user(buffer, status, strlen(status));
    if(ret < 0)
    {
        pr_warn("Copy to the user failed\n");
        return -EFAULT;
    }
    return 0;
}

static ssize_t led_write(struct file* filp,const char* buffer, 
    size_t count, loff_t* ppos)
{
    int check = 0;
    pr_info("\nled device is ready writing!\n");
    check = copy_from_user(operations_cached, buffer, count);
    if(check < 0){
        pr_warn("Can not copy from user!\n");
        return -EFAULT;
    }

    if(!strcmp(operations_cached, "open")){
        __led_turn_on();
    }else if(!strcmp(operations_cached, "close")){
        __led_turn_off();
    }else{
        pr_warn("Can not find the indications operations!\n"
                "check the business: %s", operations_cached);
    }
    return 0;
}

static int led_open(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is opened!\n");
    return 0;
}

static int led_close(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is released!\n");
    return 0;
}

static const struct file_operations led_ops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_close,
    .write = led_write,
    .read = led_read
};


/* register the device */
static int __init led_init(void)
{
    int ret = 0;
    if(myled.major){
        myled.dev_id = MKDEV(myled.major, 0);
        ret = register_chrdev_region(myled.dev_id, LED_DEV_N, LED_DEV_NAME);
    }else{
        ret = alloc_chrdev_region(&myled.dev_id, 0, LED_DEV_N, LED_DEV_NAME);
        myled.major = MAJOR(myled.dev_id);
        myled.minor = MINOR(myled.dev_id);
    }

    if(ret < 0){
        pr_warn("Error in registering the device! Failed to register the region\n");
        return -EIO;
    }

    pr_info("Success in registering the device major=%d, minor=%d\n",
            myled.major, myled.minor);
    myled.char_dev_handle.owner = THIS_MODULE;
    cdev_init(&(myled.char_dev_handle), &led_ops);
    ret = cdev_add(&(myled.char_dev_handle), myled.dev_id, LED_DEV_N);
    __enable_led_mappings();
    pr_info("Prepare to create the device class file...\n");
    myled.led_class_handle = class_create(THIS_MODULE, LED_DEV_NAME);
    if(IS_ERR(myled.led_class_handle)){
        return PTR_ERR(myled.led_class_handle);
    }
    myled.led_handle_device = device_create(
        myled.led_class_handle, NULL, myled.dev_id, "%s", LED_DEV_NAME
    );
    if(IS_ERR(myled.led_handle_device)){
        return PTR_ERR(myled.led_handle_device);
    }
    return 0;
}

static void __exit led_deinit(void)
{
    pr_info("Ready to remove the hook of the device operating file\n");
    device_destroy(myled.led_class_handle, myled.dev_id);
    class_destroy(myled.led_class_handle);
    pr_info("Ready to release the char dev handle\n");
    cdev_del(&(myled.char_dev_handle));
    pr_info("Ready to unhook the device region\n");
    unregister_chrdev_region(myled.dev_id, LED_DEV_N);
    __disable_led_mappings();
    pr_info("Successfully unregister the device\n");
}

module_init(led_init);
module_exit(led_deinit);
```

## 测试

```
/module_test # ls
chrdev_application  led.ko
/module_test # insmod led.ko 
Success in registering the device major=249, minor=0
Ready to mappings the registers...
mappings the registers done!
LED_CCGR1     ioremap to: f42c406c
LEDBASE       ioremap to: f42e0068
LEDPAD_BASE   ioremap to: f42e02f4
LEDDR_BASE    ioremap to: a09f6000
LEDGDIR_BASE  ioremap to: a09fe004
initialize the led registers
operations of led is accessable!
Prepare to create the device class file...
/module_test # ls /dev | grep charlies_led
charlies_led
/module_test # ./chrdev_application /dev/charlies_led read

led device is opened!
user process the read issue
led device is reading!

user receive from driver: closed
led device is released!
v 
/module_test # ./chrdev_application /dev/charlies_led write open

led device is opened!
args: 4
led device is ready writing!

user process the write issue: o
led device is released!
pen
/module_test # ./chrdev_application /dev/charlies_led write close

led device is opened!
args: 4
led device is ready writing!

user process the write issue: c
led device is released!
lose
/module_test # rmmod led.ko 
Ready to remove the hook of the device operating file
Ready to release the char dev handle
Ready to unhook the device region
set the led turning off...
set the led turning off done!
Ready to unmappings the registers...
unmappings the registers done
Successfully unregister the device
/module_test # ls /dev | grep charlies_led
```

​	可以看到我们自动创建了设备文件！太裤了！

## 最后的完善：正式化我们的字符设备

### 设置私有成员

​	我们知道Linux给我们的设备提供了文件的抽象，这里，我们看到了open和release中，可以指定操作具体的设备名称，办法就是设置file结构体中的private_data，也就是设置私有成员。

```c
static int led_open(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is opened!\n");
    filp->private_data = &myled; // private data here
    return 0;
}

static int led_close(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is released!\n");
    return 0;
}
```

​	这样我们就可以在多设备中区分我们再操作哪一个设备了，当然LED我们看不出来。

### 设置基于goto的rollback机制

​	我们多步申请资源的时候，出现了其中一步资源申请失败的场景时，就要回退。我们C语言只可使用rollback机制来进行回退，请看VCR：

```c
/* register the device */
static int __init led_init(void)
{
    int ret = 0;
    if(myled.major){
        myled.dev_id = MKDEV(myled.major, 0);
        ret = register_chrdev_region(myled.dev_id, LED_DEV_N, LED_DEV_NAME);
    }else{
        ret = alloc_chrdev_region(&myled.dev_id, 0, LED_DEV_N, LED_DEV_NAME);
        myled.major = MAJOR(myled.dev_id);
        myled.minor = MINOR(myled.dev_id);
    }

    if(ret < 0){
        pr_warn("Error in registering the device! Failed to register the region\n");
        goto failed_register_chrdev_region;
    }

    pr_info("Success in registering the device major=%d, minor=%d\n",
            myled.major, myled.minor);
    myled.char_dev_handle.owner = THIS_MODULE;
    cdev_init(&(myled.char_dev_handle), &led_ops);
    ret = cdev_add(&(myled.char_dev_handle), myled.dev_id, LED_DEV_N);
    
    if(ret < 0){
        pr_warn("Failed to add chardev into the kernel_list!\n");
        goto failed_add_chardev;
    }

    pr_info("Prepare to create the device class file...\n");
    myled.led_class_handle = class_create(THIS_MODULE, LED_DEV_NAME);
    if(IS_ERR(myled.led_class_handle)){
        // class creation failed, rollback!
        pr_warn("Failed to create the led class handle...\n");
        goto failed_create_class;
    }
    myled.led_handle_device = device_create(
        myled.led_class_handle, NULL, myled.dev_id, "%s", LED_DEV_NAME
    );
    if(IS_ERR(myled.led_handle_device)){
        pr_warn("Failed to create the led device ...\n");
        goto failed_create_device;
    }
    __enable_led_mappings();
    return 0;

failed_create_device:
    class_destroy(myled.led_class_handle);
failed_create_class:
    cdev_del(&(myled.char_dev_handle));
failed_add_chardev:
    unregister_chrdev_region(myled.dev_id, LED_DEV_N);
failed_register_chrdev_region:
    return -EIO;
}
```

​	这种方法在 Linux 内核开发中被广泛采用，旨在确保在初始化过程中一旦发生错误，能够有序地释放已分配的资源，避免资源泄漏。函数开始时，尝试使用 `register_chrdev_region` 或 `alloc_chrdev_region` 注册字符设备区域，具体取决于是否已分配主设备号 (`myled.major`)。如果注册失败（即 `ret < 0`），函数会记录警告信息，并跳转到标签 `failed_register_chrdev_region`，在该标签处，函数返回 `-EIO` 错误码，表示输入/输出错误。如果设备区域注册成功，函数继续初始化字符设备结构（`cdev_init`）并将其添加到内核（`cdev_add`）。如果 `cdev_add` 失败，函数会记录警告信息，并跳转到标签 `failed_add_chardev`。在该标签处，函数调用 `unregister_chrdev_region` 注销之前注册的字符设备区域，以释放资源，然后返回错误码。接下来，函数尝试创建设备类（`class_create`）。如果创建失败，函数会记录警告信息，并跳转到标签 `failed_create_class`。在该标签处，函数首先调用 `cdev_del` 删除已添加的字符设备，然后调用 `unregister_chrdev_region` 注销字符设备区域，最后返回错误码。如果设备类创建成功，函数继续创建设备（`device_create`）。如果设备创建失败，函数会记录警告信息，并跳转到标签 `failed_create_device`。在该标签处，函数首先调用 `class_destroy` 销毁已创建的设备类，然后跳转到 `failed_create_class` 标签，执行后续的资源释放操作。

## 走到这里，我们最后的成果

```
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");

#define LED_DEV_NAME            ("charlies_led")
#define LED_DEV_N               (1)
/* 
    LED Physical Address 
        See the manual
*/
#define CCM_CCGR1_BASE          (0x020C406C)
#define GPIO1_IOLED_BASE        (0x020E0068)
#define GPIO1_IOPAD_BASE        (0x020E02F4)
#define GPIO1_IODR_BASE         (0x0209C000)
#define GPIO1_GDIR_BASE         (0x0209C004)

/* mappings of the io phe*/
static void* __iomem LED_CCGR1;
static void* __iomem LEDBASE;
static void* __iomem LEDPAD_BASE;
static void* __iomem LEDDR_BASE;
static void* __iomem LEDGDIR_BASE;

/* we use a device struct */
typedef struct __myled {
    struct cdev char_dev_handle;
    dev_t       dev_id;
    int         major;
    int         minor;
    struct class*   led_class_handle; 
    struct device*  led_handle_device;
}MyLED;

static MyLED myled;

/* operations cached */
static char operations_cached[20];


static void __led_turn_on(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    val &= ~(1 << 3);
    writel(val, LEDDR_BASE);
}

static void __led_turn_off(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    val |= (1 << 3);
    writel(val, LEDDR_BASE);
}

static u8 __fetch_led_status(void)
{
    u32 val = 0;
    val = readl(LEDDR_BASE);
    return !(val & (1 << 3));
}

static void __enable_led_mappings(void)
{
    int val = 0;
    pr_info("Ready to mappings the registers...\n");
    LED_CCGR1 = ioremap(CCM_CCGR1_BASE, 4);
    LEDBASE = ioremap(GPIO1_IOLED_BASE, 4);
    LEDPAD_BASE = ioremap(GPIO1_IOPAD_BASE, 4);
    LEDDR_BASE = ioremap(GPIO1_IODR_BASE, 4);
    LEDGDIR_BASE = ioremap(GPIO1_GDIR_BASE, 4);
    pr_info("mappings the registers done!\n");

    pr_info("LED_CCGR1     ioremap to: %p\n", LED_CCGR1);
    pr_info("LEDBASE       ioremap to: %p\n", LEDBASE);
    pr_info("LEDPAD_BASE   ioremap to: %p\n", LEDPAD_BASE);
    pr_info("LEDDR_BASE    ioremap to: %p\n", LEDDR_BASE);
    pr_info("LEDGDIR_BASE  ioremap to: %p\n", LEDGDIR_BASE);

    pr_info("initialize the led registers\n");
    
    val = readl(LED_CCGR1);
    // clear the bits
    val &= ~(3 << 26);
    val |= (3 << 26);
    writel(val, LED_CCGR1);

    writel(0x5, LEDBASE);
    writel(0x10B0, LEDPAD_BASE);

    val = readl(LEDGDIR_BASE);
    val |= 1 << 3;
    writel(val, LEDGDIR_BASE);

    pr_info("operations of led is accessable!\n");
}

static void __disable_led_mappings(void)
{
    __led_turn_off();
    pr_info("set the led turning off...\n");
    pr_info("set the led turning off done!\n");
    pr_info("Ready to unmappings the registers...\n");    
    iounmap(LED_CCGR1);
    iounmap(LEDBASE);
    iounmap(LEDPAD_BASE);
    iounmap(LEDDR_BASE);
    iounmap(LEDGDIR_BASE);
    pr_info("unmappings the registers done\n");
}


static ssize_t led_read(struct file* filp, char* buffer, 
    size_t count, loff_t* ppos)
{
    const char* status = "opened";
    int ret = 0;
    pr_info("\nled device is reading!\n");
    if(!__fetch_led_status()){
        status = "closed";
    } 
    ret = copy_to_user(buffer, status, strlen(status));
    if(ret < 0)
    {
        pr_warn("Copy to the user failed\n");
        return -EFAULT;
    }
    return 0;
}

static ssize_t led_write(struct file* filp,const char* buffer, 
    size_t count, loff_t* ppos)
{
    int check = 0;
    pr_info("\nled device is ready writing!\n");
    check = copy_from_user(operations_cached, buffer, count);
    if(check < 0){
        pr_warn("Can not copy from user!\n");
        return -EFAULT;
    }

    if(!strcmp(operations_cached, "open")){
        __led_turn_on();
    }else if(!strcmp(operations_cached, "close")){
        __led_turn_off();
    }else{
        pr_warn("Can not find the indications operations!\n"
                "check the business: %s", operations_cached);
    }
    return 0;
}

static int led_open(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is opened!\n");
    filp->private_data = &myled; /* 设置私有数据 */
    return 0;
}

static int led_close(struct inode* inode, struct file* filp)
{
    pr_info("\nled device is released!\n");
    return 0;
}

static const struct file_operations led_ops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_close,
    .write = led_write,
    .read = led_read
};


/* register the device */
static int __init led_init(void)
{
    int ret = 0;
    if(myled.major){
        myled.dev_id = MKDEV(myled.major, 0);
        ret = register_chrdev_region(myled.dev_id, LED_DEV_N, LED_DEV_NAME);
    }else{
        ret = alloc_chrdev_region(&myled.dev_id, 0, LED_DEV_N, LED_DEV_NAME);
        myled.major = MAJOR(myled.dev_id);
        myled.minor = MINOR(myled.dev_id);
    }

    if(ret < 0){
        pr_warn("Error in registering the device! Failed to register the region\n");
        goto failed_register_chrdev_region;
    }

    pr_info("Success in registering the device major=%d, minor=%d\n",
            myled.major, myled.minor);
    myled.char_dev_handle.owner = THIS_MODULE;
    cdev_init(&(myled.char_dev_handle), &led_ops);
    ret = cdev_add(&(myled.char_dev_handle), myled.dev_id, LED_DEV_N);
    
    if(ret < 0){
        pr_warn("Failed to add chardev into the kernel_list!\n");
        goto failed_add_chardev;
    }

    pr_info("Prepare to create the device class file...\n");
    myled.led_class_handle = class_create(THIS_MODULE, LED_DEV_NAME);
    if(IS_ERR(myled.led_class_handle)){
        // class creation failed, rollback!
        pr_warn("Failed to create the led class handle...\n");
        goto failed_create_class;
    }
    myled.led_handle_device = device_create(
        myled.led_class_handle, NULL, myled.dev_id, "%s", LED_DEV_NAME
    );
    if(IS_ERR(myled.led_handle_device)){
        pr_warn("Failed to create the led device ...\n");
        goto failed_create_device;
    }
    __enable_led_mappings();
    return 0;

failed_create_device:
    class_destroy(myled.led_class_handle);
failed_create_class:
    cdev_del(&(myled.char_dev_handle));
failed_add_chardev:
    unregister_chrdev_region(myled.dev_id, LED_DEV_N);
failed_register_chrdev_region:
    return -EIO;
}

static void __exit led_deinit(void)
{
    pr_info("Ready to remove the hook of the device operating file\n");
    device_destroy(myled.led_class_handle, myled.dev_id);
    class_destroy(myled.led_class_handle);
    pr_info("Ready to release the char dev handle\n");
    cdev_del(&(myled.char_dev_handle));
    pr_info("Ready to unhook the device region\n");
    unregister_chrdev_region(myled.dev_id, LED_DEV_N);
    __disable_led_mappings();
    pr_info("Successfully unregister the device\n");
}

module_init(led_init);
module_exit(led_deinit);
```

## 测试

```
/module_test # ls
chrdev_application  led.ko
/module_test # insmod led.ko 
Success in registering the device major=249, minor=0
Ready to mappings the registers...
mappings the registers done!
LED_CCGR1     ioremap to: f42c406c
LEDBASE       ioremap to: f42e0068
LEDPAD_BASE   ioremap to: f42e02f4
LEDDR_BASE    ioremap to: a09f6000
LEDGDIR_BASE  ioremap to: a09fe004
initialize the led registers
operations of led is accessable!
Prepare to create the device class file...
/module_test # ls /dev | grep charlies_led
charlies_led
/module_test # ./chrdev_application /dev/charlies_led read

led device is opened!
user process the read issue
led device is reading!

user receive from driver: closed
led device is released!
v 
/module_test # ./chrdev_application /dev/charlies_led write open

led device is opened!
args: 4
led device is ready writing!

user process the write issue: o
led device is released!
pen
/module_test # ./chrdev_application /dev/charlies_led write close

led device is opened!
args: 4
led device is ready writing!

user process the write issue: c
led device is released!
lose
/module_test # rmmod led.ko 
Ready to remove the hook of the device operating file
Ready to release the char dev handle
Ready to unhook the device region
set the led turning off...
set the led turning off done!
Ready to unmappings the registers...
unmappings the registers done
Successfully unregister the device
/module_test # ls /dev | grep charlies_led
```

​	现象一致！