# IMX6ULL学习整理篇——Linux驱动开发的基础2 老框架的一次实战：LED驱动

​	在上一篇博客中，我们实现了从0开始搭建的字符设备驱动框架，但是这个框架还是空中楼阁，没有应用，很难说明我们框架的正确性。这里，我们就准备好驱动正点原子开发板上的一个LED小灯外设。他被接在了GPIO01_IO03上。

## 开始之前，复习一下架构体系对外设的地址处理

​	毫无疑问，任何一个搞过单片机的朋友都知道：在 ARM 架构中，外设的地址处理主要通过内存映射（Memory-Mapped I/O）方式进行。这意味着，外设的寄存器被映射到处理器的内存地址空间，CPU 可以像访问内存一样访问这些外设寄存器。这个技术连x86开始就在使用了！每个外设的寄存器都被分配了特定的物理地址，处理器通过读写这些地址来控制外设的操作。这种方式简化了处理器与外设之间的通信，因为不需要专门的 I/O 指令，统一了内存和外设的访问方式。

​	当然，对于我们复杂的ARM芯片上的主板一般还有MMU内存管理单元。我们的地址访问都被认为是一个虚拟地址时，这个时候MMU 会根据页表将其转换为相应的物理地址。这不仅实现了内存的虚拟化，还允许操作系统为不同的应用程序提供独立的地址空间，提高了系统的安全性和稳定性。

​	关于虚拟内存和物理内存，复习微机原理可以帮助你理解这些知识，笔者这里是驱动笔记整理，不是计算机体系架构笔记整理，所以请你自行翻阅相关的知识！

​	这也就意味着，我们没法子直接拿物理地址访问我们的GPIO寄存器了，那咋办呢？答案是：Linux考虑到了这类情况，提供了一组API，让我们添加IO设备的外设地址映射，告诉我们我们操作的虚拟地址是哪个！

## ioremap和iounmap函数

​	在 Linux 内核中，`ioremap` 和 `iounmap` 函数用于在内核虚拟地址空间中映射和解除映射物理 I/O 内存区域，以便内核能够安全地访问硬件设备的寄存器或内存。`ioremap` 函数用于将指定的物理地址范围映射到内核的虚拟地址空间，使内核能够通过虚拟地址访问对应的物理 I/O 内存区域。

```c
void __iomem *ioremap(resource_size_t phys_addr, unsigned long size);
```

​	其中：`phys_addr`是要映射的物理起始地址。`size`：要映射的内存区域大小。成功时，返回指向映射后虚拟地址空间的指针；失败时，返回 `NULL`。调用 `ioremap` 后，内核可以通过返回的虚拟地址指针访问对应的物理 I/O 内存区域。

​	`iounmap` 函数用于解除先前通过 `ioremap` 建立的映射关系，释放对应的虚拟地址空间。

```c
void iounmap(void __iomem *addr);
```

​	这里的`addr`：要解除映射的虚拟地址，即先前 `ioremap` 的返回值。调用 `iounmap` 后，内核将不再能够通过该虚拟地址访问对应的物理 I/O 内存区域。

​	当然笔者提醒：

- 在访问硬件设备的寄存器或内存时，必须先使用 `ioremap` 将物理地址映射到内核虚拟地址空间，然后通过返回的虚拟地址进行读写操作。
- 在不再需要访问该 I/O 内存区域时，应调用 `iounmap` 解除映射，以释放资源。
- 直接访问物理地址可能导致不可预期的行为，因此应始终通过 `ioremap` 和 `iounmap` 函数进行 I/O 内存的映射和解除映射。

## read蔟函数和write蔟函数——操作我们的IO设备

​	拿到地址了，咋写呢？别自己手搓，我们的Linux还是给我们提供了API：在 Linux 内核中，`readb`、`readw`、`readl` 以及 `writeb`、`writew`、`writel` 等函数用于在内存映射的 I/O 空间中读取和写入数据。

**读取操作函数：`readb`、`readw`、`readl` 函数用于从内存映射的 I/O 空间读取 8 位、16 位和 32 位的数据。**

`readb`：从指定的内存映射 I/O 地址读取 8 位（1 字节）数据。

```c
unsigned char readb(const volatile void __iomem *addr);
```

`readw`：从指定的内存映射 I/O 地址读取 16 位（2 字节）数据。

```c
unsigned short readw(const volatile void __iomem *addr);
```

`readl`：从指定的内存映射 I/O 地址读取 32 位（4 字节）数据。

```c
unsigned int readl(const volatile void __iomem *addr);
```

**写入操作函数：**`writeb`、`writew`、`writel` 函数用于向内存映射的 I/O 空间写入 8 位、16 位和 32 位的数据。

`writeb`：向指定的内存映射 I/O 地址写入 8 位（1 字节）数据。

```c
void writeb(u8 value, volatile void __iomem *addr);
```

`writew`：向指定的内存映射 I/O 地址写入 16 位（2 字节）数据。

```c
void writew(u16 value, volatile void __iomem *addr);
```

`writel`：向指定的内存映射 I/O 地址写入 32 位（4 字节）数据。

```c
void writel(u32 value, volatile void __iomem *addr);
```

- `addr`：指向内存映射 I/O 空间中目标地址的指针。
- `value`：要写入的数据。

## 编程，启动！

​	具体是啥地址，这个事情三个字：翻手册。没了，还不懂看如何裸机驱动LED，这就跟LKM驱动开发半毛钱关系没有了

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");


#define LED_MAJOR_DEV_N         (114)
#define LED_DEV_NAME            ("charlies_led")

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

static struct file_operations led_ops = {
    .owner = THIS_MODULE,
    .read = led_read,
    .write = led_write,
    .open = led_open,
    .release = led_close
};

static int __init led_init(void)
{
    int result = 0;
    pr_info("LED Device is setting up\n");
    result = register_chrdev(LED_MAJOR_DEV_N, LED_DEV_NAME, &led_ops);
    if(result < 0){
        pr_warn("can not register the device!\n");
        return -EIO;
    }
    __enable_led_mappings();
    return 0;
}

static void __exit led_exit(void)
{
    unregister_chrdev(LED_MAJOR_DEV_N, LED_DEV_NAME);
    __disable_led_mappings();
    pr_info("LED Device is unhooked!\n");
}

module_init(led_init);
module_exit(led_exit);
```

## 书写测试程序

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define ISSUE_BUFFER_N      (40)

static void display_help(const char* app_name)
{
    fprintf(stderr, 
        "do: %s <dev_file> <operations>\n"
        "op: read : read the data from char dev\n"
        "op: write: write the data to char dev:\n"
        "   open: turn on the led\n"
        "   close: turn off the led\n", app_name);
}

int main(int argc, char* argv[])
{
    int check = 0;
    if(argc < 3){
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
        printf("args: %d\n", argc);
        if(argc != 4){
            display_help(argv[0]);
            goto close_issue;
        }

        printf("user process the write issue: %s\n", argv[3]);
        result = write(check, argv[3], strlen(argv[3]));
        if(result < 0){
            fprintf(stderr, "Hey, Error in write! filename: %s!\n", filename);
            goto close_issue; 
        }    
    }else{
        fprintf(stderr, "Unknown options!\n");
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

​	无比怀念CLI框架的一天.jpg

​	下面我们测试一下：

## 测试

```
/module_test # ls
chrdev_application  led.ko
/module_test # mknod /dev/ccled c 114 0
/module_test # insmod led.ko 
LED Device is setting up
Ready to mappings the registers...
mappings the registers done!
LED_CCGR1     ioremap to: f42c406c
LEDBASE       ioremap to: f42e0068
LEDPAD_BASE   ioremap to: f42e02f4
LEDDR_BASE    ioremap to: a092e000
LEDGDIR_BASE  ioremap to: a0936004
initialize the led registers
operations of led is accessable!
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
user process the write issue: 
led device is ready writing!
close

led device is released!
/module_test # rmmod led.ko 
set the led turning off...
set the led turning off done!
Ready to unmappings the registers...
unmappings the registers done
LED Device is unhooked!
```

![c63e6313b086fe8da5cf360471774c7](./IMX6ULL学习整理篇——Linux驱动开发的基础——2/c63e6313b086fe8da5cf360471774c7.jpg)

![3796633c24a3d6ce7c6bd4aae7d7472](./IMX6ULL学习整理篇——Linux驱动开发的基础——2/3796633c24a3d6ce7c6bd4aae7d7472.jpg)