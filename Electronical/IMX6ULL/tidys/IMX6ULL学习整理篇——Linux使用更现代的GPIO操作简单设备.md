# IMX6ULL学习篇——实战：使用设备树/Pinctl-gpio子系统驱动LED

## 前言

​	经过层层考验，我们即将接近现代的LED驱动的解决方案了。那就是使用最现代的方式开发一个简单的GPIO驱动外设。

​	如果您忘记了设备树的相关内容，请自行到笔者的上一篇博客复习

## 修改我们的设备树

​	我们现在修改我们的设备树，在根节点下，直接添加一个myled节点，我们做了如下的添加

```
	myled {
		#address-cells = <1>;
		#size-cells = <1>;
		compatible = "charlie-led";
		status = "okay";
		reg = <
			0x020C406C 0x04
			0x020E0068 0x04
			0x020E02F4 0x04
			0x0209C000 0x04
			0x0209C004 0x04
		>;
	};
```

1. `myled`：节点名称，表示这是一个LED设备。
2. `#address-cells = <1>`：
   - 指定子节点中"reg"属性的地址字段用1个32位数字表示。
3. `#size-cells = <1>`：
   - 指定子节点中"reg"属性的大小字段用1个32位数字表示。
4. `compatible = "charlie-led"`：
   - 驱动兼容性标识，表示这个设备与"charlie-led"驱动程序兼容。
5. `status = "okay"`：
   - 设备状态，表示这个设备处于启用状态。
6. `reg`属性：
   - 定义了5组寄存器地址和大小，每组包含：
     - 第一个数字是寄存器地址
     - 第二个数字是寄存器区域大小(这里是0x04表示4字节)
   - 具体地址：
     1. 0x020C406C - 大小为0x04
     2. 0x020E0068 - 大小为0x04
     3. 0x020E02F4 - 大小为0x04
     4. 0x0209C000 - 大小为0x04
     5. 0x0209C004 - 大小为0x04

然后重新编译我们的设备树文件

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- dtbs
```

​	将得到的设备树放置到我们的tftp文件夹目录下，之后使用这个新的设备树启动我们的Linux内核

​	启动成功后，在设备树的文件夹下：

```
cd /proc/device-tree/
/sys/firmware/devicetree/base # ls
#address-cells                 model
#size-cells                    myled
aliases                        name
backlight                      pxp_v4l2
chosen                         regulators
clocks                         reserved-memory
compatible                     soc
cpus                           sound
interrupt-controller@00a01000  spi4
memory
/sys/firmware/devicetree/base # cd myled/
/sys/firmware/devicetree/base/myled # ls
#address-cells  compatible      reg
#size-cells     name            status
```

​	可用看到我们的myled和下面的东西，这里都被读取到了。下面就是直接对设备树进行读取和编程。

## 方式1：使用读取的方式直接拿到寄存器的值

​	我们下面一个办法就是直接通过设备树，拿到LED外设GPIO寄存器的值

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <asm/mach/map.h>

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
    // node info
    struct device_node* node;
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

static void __enable_led_mappings(u32 regdata[10])
{
    int val = 0;
    pr_info("Ready to mappings the registers...\n");
    // LED_CCGR1 = ioremap(CCM_CCGR1_BASE, 4);
    // LEDBASE = ioremap(GPIO1_IOLED_BASE, 4);
    // LEDPAD_BASE = ioremap(GPIO1_IOPAD_BASE, 4);
    // LEDDR_BASE = ioremap(GPIO1_IODR_BASE, 4);
    // LEDGDIR_BASE = ioremap(GPIO1_GDIR_BASE, 4);
    LED_CCGR1 = ioremap(regdata[0], regdata[1]);
    LEDBASE = ioremap(regdata[2], regdata[3]);
    LEDPAD_BASE = ioremap(regdata[4], regdata[5]);
    LEDDR_BASE = ioremap(regdata[6], regdata[7]);
    LEDGDIR_BASE = ioremap(regdata[8], regdata[9]);
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
    u32 regdata[10];
    const char* compatible;
    const char* status_str;

    // fetch platform tree
    myled.node = of_find_node_by_path("/myled");
    if(myled.node == NULL){
        pr_warn("can not find the myled\n");
        return -EINVAL;
    }else{
        pr_info("find the myled in device tree!\n");
    }

    
    ret = of_property_read_string(myled.node, "status", &status_str);
    if(ret < 0){
        pr_warn("can not fetch the status node info");
        return EINVAL;
    }else{
        pr_info("status=%s\n", status_str);
    }

    
    ret = of_property_read_string(myled.node, "compatible", &compatible);
    if(ret < 0){
        pr_warn("can not fetch the status node info");
        return EINVAL;
    }else{
        pr_info("compatible=%s\n", status_str);
    }    

    
    ret = of_property_read_u32_array(myled.node, "reg", regdata, 10);
    if(ret < 0){
        pr_info("failed to fetch the reg device info!\n");
        return -EINVAL;
    }else{
        u8 i = 0;
        for(i = 0; i < 10; i+=2)
        {
            pr_info("reg data: %#X %#X\n", regdata[i], regdata[i + 1]);
        }
    }


    // create the led device
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
    __enable_led_mappings(regdata);
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

​	中间很长，但是只修改了led初始化的部分：

```c
    // fetch platform tree
    myled.node = of_find_node_by_path("/myled");
    if(myled.node == NULL){
        pr_warn("can not find the myled\n");
        return -EINVAL;
    }else{
        pr_info("find the myled in device tree!\n");
    }

    
    ret = of_property_read_string(myled.node, "status", &status_str);
    if(ret < 0){
        pr_warn("can not fetch the status node info");
        return EINVAL;
    }else{
        pr_info("status=%s\n", status_str);
    }

    
    ret = of_property_read_string(myled.node, "compatible", &compatible);
    if(ret < 0){
        pr_warn("can not fetch the status node info");
        return EINVAL;
    }else{
        pr_info("compatible=%s\n", status_str);
    }    

    
    ret = of_property_read_u32_array(myled.node, "reg", regdata, 10);
    if(ret < 0){
        pr_info("failed to fetch the reg device info!\n");
        return -EINVAL;
    }else{
        u8 i = 0;
        for(i = 0; i < 10; i+=2)
        {
            pr_info("reg data: %#X %#X\n", regdata[i], regdata[i + 1]);
        }
    }

```

​	读取设备树，第一件事情就是把节点找到了，然后这里，我们只是尝试读取设备树上的叶子节点的属性，这样来测试我们的设备树的节点读取是否成功，真正设计到驱动LED本身的，还是`of_property_read_u32_array`读取我们的寄存器的值，之后的事情就很简单了，我们直接使用这些地址进行映射。

​	编译下载得到：

```
/module_test # insmod led.ko 
find the myled in device tree!
status=okay
compatible=charlie-led
reg data: 0X20C406C 0X4
reg data: 0X20E0068 0X4
reg data: 0X20E02F4 0X4
reg data: 0X209C000 0X4
reg data: 0X209C004 0X4
Success in registering the device major=249, minor=0
Prepare to create the device class file...
Ready to mappings the registers...
mappings the registers done!
LED_CCGR1     ioremap to: f42c406c
LEDBASE       ioremap to: f42e0068
LEDPAD_BASE   ioremap to: f42e02f4
LEDDR_BASE    ioremap to: a08e6000
LEDGDIR_BASE  ioremap to: a08ee004
initialize the led registers
operations of led is accessable!
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
```

## 使用工具函数of_iomap直接映射

​	上面的方法还是很麻烦，我们可不可以直接一步到位呢？当然可以，使用of_iomap函数可以一步到位

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_address.h>

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
    struct device_node* node;
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
    LED_CCGR1 = of_iomap(myled.node, 0);
    LEDBASE = of_iomap(myled.node, 1);
    LEDPAD_BASE = of_iomap(myled.node, 2);
    LEDDR_BASE = of_iomap(myled.node, 3);
    LEDGDIR_BASE = of_iomap(myled.node, 4);
    // LED_CCGR1 = ioremap(regdata[0], regdata[1]);
    // LEDBASE = ioremap(regdata[2], regdata[3]);
    // LEDPAD_BASE = ioremap(regdata[4], regdata[5]);
    // LEDDR_BASE = ioremap(regdata[6], regdata[7]);
    // LEDGDIR_BASE = ioremap(regdata[8], regdata[9]);
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
    u32 regdata[10];
    const char* compatible;
    const char* status_str;

    // fetch platform tree
    myled.node = of_find_node_by_path("/myled");
    if(myled.node == NULL){
        pr_warn("can not find the myled\n");
        return -EINVAL;
    }else{
        pr_info("find the myled in device tree!\n");
    }

    
    ret = of_property_read_string(myled.node, "status", &status_str);
    if(ret < 0){
        pr_warn("can not fetch the status node info");
        return EINVAL;
    }else{
        pr_info("status=%s\n", status_str);
    }

    
    ret = of_property_read_string(myled.node, "compatible", &compatible);
    if(ret < 0){
        pr_warn("can not fetch the status node info");
        return EINVAL;
    }else{
        pr_info("compatible=%s\n", status_str);
    }    

    
    ret = of_property_read_u32_array(myled.node, "reg", regdata, 10);
    if(ret < 0){
        pr_info("failed to fetch the reg device info!\n");
        return -EINVAL;
    }else{
        u8 i = 0;
        for(i = 0; i < 10; i+=2)
        {
            pr_info("reg data: %#X %#X\n", regdata[i], regdata[i + 1]);
        }
    }


    // create the led device
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

```
/module_test # insmod led.ko 
find the myled in device tree!
status=okay
compatible=charlie-led
reg data: 0X20C406C 0X4
reg data: 0X20E0068 0X4
reg data: 0X20E02F4 0X4
reg data: 0X209C000 0X4
reg data: 0X209C004 0X4
Success in registering the device major=249, minor=0
Prepare to create the device class file...
Ready to mappings the registers...
mappings the registers done!
LED_CCGR1     ioremap to: f42c406c
LEDBASE       ioremap to: f42e0068
LEDPAD_BASE   ioremap to: f42e02f4
LEDDR_BASE    ioremap to: a08e6000
LEDGDIR_BASE  ioremap to: a08ee004
initialize the led registers
operations of led is accessable!
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
```

## 使用pinctl和gpio子系统——LED驱动

​	对于如何初始化LED灯所使用的GPIO，整个过程可以分为几个步骤。

首先需要修改设备树，添加相应的节点，其中最重要的是设置reg属性，这个属性包含了GPIO相关的寄存器信息。接下来要获取reg属性中的IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03和IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03这两个寄存器地址，并初始化它们，这两个寄存器用于设置GPIO1_IO03这个引脚的复用功能、上下拉、速度等参数。

在完成这一步后，由于GPIO1_IO03这个引脚已经被复用为GPIO功能，因此还需要设置GPIO1_IO03相关的GPIO寄存器，也就是GPIO1_DR和GPIO1_GDIR这两个寄存器。简单来说，第二步完成了对GPIO1_IO03引脚的初始化，设置其复用功能等属性，比如将其设置为GPIO功能；

而第三步则完成了对GPIO本身的初始化，设置其输入输出方向等。这个流程与STM32的开发类似，都是先设置引脚的复用功能、速度、上下拉等属性，再配置对应的GPIO功能。实际上，大多数32位SOC的引脚配置都遵循这个模式，因此Linux内核专门针对引脚配置开发了pinctrl子系统，针对GPIO配置开发了gpio子系统。我们综合应用起来，就能开发大部分的GPIO驱动的外设了。

​	要使用pinctrl 子系统，我们需要在设备树里面设置 PIN 的配置信息，毕竟 pinctrl 子系统要根据你提供的信息来配置 PIN 功能，一般会在设备树里面创建一个节点来描述 PIN 的配置信息。我们需要做的就是打开 imx6ull.dtsi 文件，找到一个叫做 iomuxc 的节点，我们实际上会向这里追加数据，但是不在这个文件加，而是在我们的自己的板子配置文件上加。

​	对于IMX6ULL，这个板子的配置实际上写在了iomuxc节点下的imx6ul-evk下，我们继续追加

```
				pinctrl_charliesled: ledgrp {
					fsl,pins = <
						MX6UL_PAD_GPIO1_IO03__GPIO1_IO03	0x10B0
					>;
				};
```

​	控制组加好了之后，我们就可以声明我们的GPIO设备的LED节点的信息

```
	charliesled {
		#address-cells = <1>;
		#size-cells = <1>;
		compatible = "charlies-gpioled";
		pinctrl-names = "default";
		pinctrl-0 = <&pinctrl_charliesled>;
		led-gpio = <&gpio1 3 GPIO_ACTIVE_LOW>;
		status = "okay";
	};
```

​	但是你需要注意的是——因为我们现在拿到的是原厂的板子，这个GPIO很有可能已经被复用了，因此，你需要做的是搜索一下板子上使用这个GPIO的设备，看看他是不是用在了自己的板子上

- 检查pinctrl 设置。 
- 如果这个 PIN 配置为 GPIO 的话，检查这个 GPIO 有没有被别的外设使用。 

​	我们就是需要做这两个事情.检查发现:

```
		pinctrl_tsc: tscgrp {
			fsl,pins = <
				MX6UL_PAD_GPIO1_IO01__GPIO1_IO01	0xb0
				MX6UL_PAD_GPIO1_IO02__GPIO1_IO02	0xb0
				/* MX6UL_PAD_GPIO1_IO03__GPIO1_IO03	0xb0 */
				MX6UL_PAD_GPIO1_IO04__GPIO1_IO04	0xb0
			>;
		};
```

和

```
&tsc {
	pinctrl-names = "default";
	pinctrl-0 = <&pinctrl_tsc>;
	/* xnur-gpio = <&gpio1 3 GPIO_ACTIVE_LOW>; */
	measure-delay-time = <0xffff>;
	pre-charge-time = <0xfff>;
	status = "okay";
};
```

​	一次出现了一些不该不限的东西,这些是我们使用的板子上没有的,可以安全的注释掉.

​	随后编译上传我们的设备树,查看是否正常.

### 使用GPIO驱动子系统为我们化简驱动

我们下面就来看看我们的Linux操作系统给我们提供了啥花活。`gpio_request`函数用于申请一个GPIO管脚，其原型为`int gpio_request(unsigned gpio, const char *label)`，其中gpio参数是要申请的GPIO标号（可通过`of_get_named_gpio`从设备树获取），label是为该GPIO指定的名称，返回0表示申请成功。当不再需要使用某个GPIO时，应调用`void gpio_free(unsigned gpio)`函数进行释放。  

要配置GPIO方向，可以使用`gpio_direction_input`和`gpio_direction_output`函数。`int gpio_direction_input(unsigned gpio)`将指定GPIO设置为输入模式，而`int gpio_direction_output(unsigned gpio, int value)`则将其设置为输出模式并设置初始输出值（value参数），两者都返回0表示成功。  

对于GPIO值的读写操作，`gpio_get_value`宏（实际调用`__gpio_get_value`函数）用于读取GPIO的当前值，其原型为`int __gpio_get_value(unsigned gpio)`，返回非负值表示读取到的电平状态。`gpio_set_value`宏（对应`__gpio_set_value`函数）用于设置GPIO输出电平，原型为`void __gpio_set_value(unsigned gpio, int value)`，无返回值。这些函数是GPIO子系统中最常用的API，涵盖了GPIO的申请、释放、方向配置及电平操作等基本功能。

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");

#define     LED_OFF_VALUE       (1)
#define     LED_ON_VALUE        (0)
#define     LED_CNT             (1)
#define     MY_LED_NAME         ("charliesled")


static struct charlies_led_dev {
    dev_t           devid;
    struct cdev     led_cdev;
    struct class*   led_class;
    struct device*  led_device;
    int     led_major;
    int     led_minor;
    struct device_node* device_node;
    int     led_gpio_n;
}charliesled_dev;

static void set_led_status(int value)
{
    int ret = 0;
    ret = gpio_direction_output(charliesled_dev.led_gpio_n, value);
    if(ret < 0){
        pr_warn("Can not set the led as turning off!\n");
    }
    return;
}

 static int led_open(struct inode *inode, struct file *filp)
 {
     filp->private_data = &charliesled_dev; 
     return 0;
 }
 

static ssize_t led_read(struct file* filp, char* buffer, 
    size_t count, loff_t* ppos){
    int ret = 0;
    const char* status = "opened";
    int gpio_current_value = 0;
    pr_info("Triggering the read gpio status of led!\n");
    gpio_current_value = gpio_get_value(charliesled_dev.led_gpio_n);
    if(gpio_current_value == LED_OFF_VALUE){
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
 
/* operations cached */
static char operations_cached[20];
static ssize_t led_write(struct file* filp,const char* buffer, 
    size_t count, loff_t* ppos)
{
    int check = 0;
    struct charlies_led_dev *dev = filp->private_data;
    pr_info("\nled device is ready writing!\n");
    check = copy_from_user(operations_cached, buffer, count);
    if(check < 0){
        pr_warn("Can not copy from user!\n");
        return -EFAULT;
    }

    if(!strcmp(operations_cached, "open")){
        gpio_set_value(dev->led_gpio_n, LED_ON_VALUE); 
    }else if(!strcmp(operations_cached, "close")){
        gpio_set_value(dev->led_gpio_n, LED_OFF_VALUE); 
    }else{
        pr_warn("Can not find the indications operations!\n"
                "check the business: %s", operations_cached);
    }
    memset(operations_cached, 0, 20);
    return 0;
}
 
static int led_release(struct inode *inode, struct file *filp)
{
    pr_info("Led device is released!\n");
    return 0;
}


static struct file_operations led_op = {
    .owner = THIS_MODULE,
	.open = led_open,
	.read = led_read,
	.write = led_write,
	.release = 	led_release,
};

static int fetch_from_device_tree(void)
{
    charliesled_dev.device_node = of_find_node_by_path("/charliesled");
    if(!charliesled_dev.device_node){
        pr_warn("Can not find the device node!\n");
        return -EINVAL;
    }else{
        pr_info("we have found the target node!\n");
    }

    charliesled_dev.led_gpio_n = of_get_named_gpio(charliesled_dev.device_node, "led-gpio", 0);
    if(charliesled_dev.led_gpio_n < 0){
        pr_warn("Can not find the led-gpio property!\n");
    }

    pr_info("successfully fetch the led-gpio: %d\n", charliesled_dev.led_gpio_n);

    pr_info("default we turn off the led");
    
    set_led_status(LED_ON_VALUE);

    return 0;
}

static int init_device(void)
{
    if(charliesled_dev.led_major){
        // the led device has been defined the value
        charliesled_dev.devid = MKDEV(charliesled_dev.led_major, 0);
        register_chrdev_region(charliesled_dev.devid, LED_CNT, MY_LED_NAME);
    }else{
        alloc_chrdev_region(&charliesled_dev.devid, 0, LED_CNT, MY_LED_NAME);
        charliesled_dev.led_major = MAJOR(charliesled_dev.devid);
        charliesled_dev.led_minor = MINOR(charliesled_dev.devid);
    }

    pr_info(
        "Device number requires succuss: major-id: %d, minor-id: %d\n", 
        charliesled_dev.led_major, charliesled_dev.led_minor
    );

    charliesled_dev.led_cdev.owner = THIS_MODULE;
    cdev_init(&charliesled_dev.led_cdev, &led_op);
    cdev_add(&charliesled_dev.led_cdev, charliesled_dev.devid, LED_CNT);

    pr_info("cdev init and add success!\n");

    charliesled_dev.led_class = class_create(THIS_MODULE, MY_LED_NAME);
    if(IS_ERR(charliesled_dev.led_class)){
        pr_info("class creation failed\n");
        return PTR_ERR(charliesled_dev.led_class);
    }

    pr_info("class creation success!\n");

    charliesled_dev.led_device = device_create(
        charliesled_dev.led_class, NULL, charliesled_dev.devid, NULL, MY_LED_NAME);
    if(IS_ERR(charliesled_dev.led_device)){
        pr_info("device creation failed\n");
        return PTR_ERR(charliesled_dev.led_device);
    }

    pr_info("device creation success!\n");

    return 0;
}

static int __init led_init(void)
{
    int ret;
    pr_info("Fetching from the device tree!\n");
    if(fetch_from_device_tree()){
        pr_warn("The fetch failed!\n");
        return -EINVAL;
    }
    pr_info("Successfully fetch from the device tree!\n");
    ret = init_device();
    pr_info("Device init finished!\n");
    return ret;
}

static void __exit led_exit(void)
{
    pr_info("LED Driver Exiting... turn off the device!\n");
    set_led_status(LED_OFF_VALUE);
    pr_info("Erase the device and classes...\n");

    device_destroy(charliesled_dev.led_class, charliesled_dev.devid);
    class_destroy(charliesled_dev.led_class);

    pr_info("Erase the cdev and release the dev id\n");
    cdev_del(&charliesled_dev.led_cdev);
    unregister_chrdev_region(charliesled_dev.devid, LED_CNT);

    pr_info("Module exit!\n");
}


module_init(led_init);
module_exit(led_exit);
```

​	现在我们可以测试,结果照常,这里就不展示了

### 再试一次:BEEP驱动

​	还是一样,我们第一步是编写pinctl的group

```
		pinctrl_charliesbeep: beepgrp {
			fsl,pins = <
				MX6ULL_PAD_SNVS_TAMPER1__GPIO5_IO01	0x10B0
			>;
		};	
```

​	然后下一步是

```
	charliesbeep {
		#address-cells = <1>;
		#size-cells = <1>;
		compatible = "charlies-gpiobeep";
		pinctrl-names = "default";
		pinctrl-0 = <&pinctrl_charliesbeep>;
		led-gpio = <&gpio5 1 GPIO_ACTIVE_LOW>;
		status = "okay";		
	};
```

​	经过我们的检查,实际上没有&gpio5 1和MX6ULL_PAD_SNVS_TAMPER1__GPIO5_IO01的冲突,咱们直接用就好了,下一步就是稍微小小的修改一下上一个LED的驱动即可:

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	
#include <asm/io.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen114514@demo.com>");

#define     BEEPOFF_VALUE       (1)
#define     BEEPON_VALUE        (0)
#define     BEEPCNT             (1)
#define     MY_BEEPNAME         ("charliesbeep")


static struct charlies_beep_dev {
    dev_t           devid;
    struct cdev     beep_cdev;
    struct class*   beep_class;
    struct device*  beep_device;
    int     beep_major;
    int     beep_minor;
    struct device_node* device_node;
    int     beep_gpio_n;
}charliesbeep_dev;

static void set_beep_status(int value)
{
    int ret = 0;
    ret = gpio_direction_output(charliesbeep_dev.beep_gpio_n, value);
    if(ret < 0){
        pr_warn("Can not set the led as turning off!\n");
    }
    return;
}

 static int beep_open(struct inode *inode, struct file *filp)
 {
     filp->private_data = &charliesbeep_dev; 
     return 0;
 }
 

static ssize_t beep_read(struct file* filp, char* buffer, 
    size_t count, loff_t* ppos){
    int ret = 0;
    const char* status = "opened";
    int gpio_current_value = 0;
    pr_info("Triggering the read gpio status of led!\n");
    gpio_current_value = gpio_get_value(charliesbeep_dev.beep_gpio_n);
    if(gpio_current_value == BEEPOFF_VALUE){
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
 
/* operations cached */
static char operations_cached[20];
static ssize_t beep_write(struct file* filp,const char* buffer, 
    size_t count, loff_t* ppos)
{
    int check = 0;
    struct charlies_beep_dev *dev = filp->private_data;
    pr_info("\nled device is ready writing!\n");
    check = copy_from_user(operations_cached, buffer, count);
    if(check < 0){
        pr_warn("Can not copy from user!\n");
        return -EFAULT;
    }

    if(!strcmp(operations_cached, "open")){
        gpio_set_value(dev->beep_gpio_n, BEEPON_VALUE); 
    }else if(!strcmp(operations_cached, "close")){
        gpio_set_value(dev->beep_gpio_n, BEEPOFF_VALUE); 
    }else{
        pr_warn("Can not find the indications operations!\n"
                "check the business: %s", operations_cached);
    }
    memset(operations_cached, 0, 20);
    return 0;
}
 
static int beep_release(struct inode *inode, struct file *filp)
{
    pr_info("Led device is released!\n");
    return 0;
}


static struct file_operations beep_op = {
    .owner = THIS_MODULE,
	.open = beep_open,
	.read = beep_read,
	.write = beep_write,
	.release = 	beep_release,
};

static int fetch_from_device_tree(void)
{
    charliesbeep_dev.device_node = of_find_node_by_path("/charliesbeep");
    if(!charliesbeep_dev.device_node){
        pr_warn("Can not find the device node!\n");
        return -EINVAL;
    }else{
        pr_info("we have found the target node!\n");
    }

    charliesbeep_dev.beep_gpio_n = of_get_named_gpio(charliesbeep_dev.device_node, "led-gpio", 0);
    if(charliesbeep_dev.beep_gpio_n < 0){
        pr_warn("Can not find the led-gpio property!\n");
    }

    pr_info("successfully fetch the led-gpio: %d\n", charliesbeep_dev.beep_gpio_n);

    pr_info("default we turn off the led");
    
    set_beep_status(BEEPOFF_VALUE);

    return 0;
}

static int init_device(void)
{
    if(charliesbeep_dev.beep_major){
        // the led device has been defined the value
        charliesbeep_dev.devid = MKDEV(charliesbeep_dev.beep_major, 0);
        register_chrdev_region(charliesbeep_dev.devid, BEEPCNT, MY_BEEPNAME);
    }else{
        alloc_chrdev_region(&charliesbeep_dev.devid, 0, BEEPCNT, MY_BEEPNAME);
        charliesbeep_dev.beep_major = MAJOR(charliesbeep_dev.devid);
        charliesbeep_dev.beep_minor = MINOR(charliesbeep_dev.devid);
    }

    pr_info(
        "Device number requires succuss: major-id: %d, minor-id: %d\n", 
        charliesbeep_dev.beep_major, charliesbeep_dev.beep_minor
    );

    charliesbeep_dev.beep_cdev.owner = THIS_MODULE;
    cdev_init(&charliesbeep_dev.beep_cdev, &beep_op);
    cdev_add(&charliesbeep_dev.beep_cdev, charliesbeep_dev.devid, BEEPCNT);

    pr_info("cdev init and add success!\n");

    charliesbeep_dev.beep_class = class_create(THIS_MODULE, MY_BEEPNAME);
    if(IS_ERR(charliesbeep_dev.beep_class)){
        pr_info("class creation failed\n");
        return PTR_ERR(charliesbeep_dev.beep_class);
    }

    pr_info("class creation success!\n");

    charliesbeep_dev.beep_device = device_create(
        charliesbeep_dev.beep_class, NULL, charliesbeep_dev.devid, NULL, MY_BEEPNAME);
    if(IS_ERR(charliesbeep_dev.beep_device)){
        pr_info("device creation failed\n");
        return PTR_ERR(charliesbeep_dev.beep_device);
    }

    pr_info("device creation success!\n");

    return 0;
}

static int __init beep_init(void)
{
    int ret;
    pr_info("Fetching from the device tree!\n");
    if(fetch_from_device_tree()){
        pr_warn("The fetch failed!\n");
        return -EINVAL;
    }
    pr_info("Successfully fetch from the device tree!\n");
    ret = init_device();
    pr_info("Device init finished!\n");
    return ret;
}

static void __exit beep_exit(void)
{
    pr_info("LED Driver Exiting... turn off the device!\n");
    set_beep_status(BEEPOFF_VALUE);
    pr_info("Erase the device and classes...\n");

    device_destroy(charliesbeep_dev.beep_class, charliesbeep_dev.devid);
    class_destroy(charliesbeep_dev.beep_class);

    pr_info("Erase the cdev and release the dev id\n");
    cdev_del(&charliesbeep_dev.beep_cdev);
    unregister_chrdev_region(charliesbeep_dev.devid, BEEPCNT);

    pr_info("Module exit!\n");
}


module_init(beep_init);
module_exit(beep_exit);
```

​	完事!