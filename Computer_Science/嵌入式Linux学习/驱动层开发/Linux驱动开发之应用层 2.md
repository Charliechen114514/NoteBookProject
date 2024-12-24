# Lionux驱动开发应用层 2 点亮一个LED

## 先来聊聊sysfs

​	我们下面首先简单聊一下sysfs。他很重要的原因是因为我们跟底下的设备打交道，就是可以透过我们的sysfs来操作我们底层的设备，

​	**sysfs**是Linux内核中的一个虚拟文件系统，用于提供内核对象、设备驱动、内核参数以及其他内核空间信息与用户空间之间的交互接口。sysfs通过在文件系统中创建一系列虚拟文件和目录，允许用户空间程序访问和控制内核的各种设置和信息。sysfs的出现，极大地简化了内核和用户空间之间的交互方式，尤其是在硬件管理、内核配置和设备管理等方面。sysfs通过提供一个结构化的接口，使得用户无需直接与复杂的内核代码交互即可进行设备控制、驱动配置和调试。

​	sysfs本质上是通过内核模块将内核空间的信息暴露到用户空间，具体来说，它利用文件系统的接口机制，通过将内核的数据结构映射为文件系统的文件和目录结构来实现。这些文件和目录实际上并不对应实际的磁盘文件，而是虚拟文件，读取或写入这些文件时，内核会根据文件内容执行相应的操作。sysfs的目录结构类似于Unix的文件系统层级，通常包含以下几个重要部分：

| 目录              | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| **/sys/class**    | 包含与设备类别相关的文件夹。例如，`/sys/class/net`用于网络接口，`/sys/class/block`用于块设备等。 |
| **/sys/devices**  | 表示系统中所有设备的层级结构。每个设备都对应一个目录，设备的属性、状态信息等存放在对应的目录下。 |
| **/sys/kernel**   | 包含内核相关的参数和信息，例如内存、内核版本等。             |
| **/sys/fs**       | 包含与文件系统相关的信息。                                   |
| **/sys/module**   | 包含当前加载的内核模块信息。                                 |
| **/sys/power**    | 包含与电源管理相关的信息和设置。                             |
| **/sys/firmware** | 包含与固件相关的信息。                                       |

​	在sysfs中，每个目录和文件都对应着内核中的某个对象或参数。例如，网络设备的状态可以在`/sys/class/net/eth0`目录下找到，通过读取或修改该目录中的文件，用户就可以获取或修改网卡的配置信息。

#### sysfs的具备的优势

​	无非就是下面四个点：

**简化内核与用户空间的交互**：sysfs为内核空间和用户空间提供了一个简单而一致的接口。用户空间程序通过标准的文件系统API（如`open`、`read`、`write`）与内核进行交互，而不需要了解内核内部的复杂数据结构和API。

**统一管理**：sysfs将不同类型的设备和内核信息按照逻辑分组，提供了一个统一的管理接口，使得用户可以方便地获取和控制系统中的各种设备和内核参数。

**灵活性和扩展性**：设备驱动可以在sysfs中创建自定义的文件和目录，从而暴露设备的特定信息或控制接口。这使得sysfs具有很强的灵活性，可以适应不同类型的设备和需求。

**实时性**：通过sysfs，用户空间可以动态获取设备的状态信息，这对于需要实时监控或调试的场景非常有用。

## LED在哪里？

​	所以我们回到我们的主题：我们的LED在哪里呢？

​	我们使用正点原子的板子，只提供了一个LED默认的用以操作。这里我们在`/sys/class/leds`可以找到我们的说法。

```
root@ATK-IMX6U:~/app# cd /sys/class/
root@ATK-IMX6U:/sys/class# ls
ata_device  bluetooth  hwmon      leds      net           rc           scsi_host   ubi
ata_link    dma        i2c-dev    mdio_bus  power_supply  regulator    sound       udc
ata_port    drm        icm20608   mem       ppp           rfkill       spidev      vc
backlight   firmware   ieee80211  misc      pps           rtc          spi_master  video4linux
bdi         gpio       input      mmc_host  ptp           scsi_device  thermal     vtconsole
block       graphics   lcd        mtd       pwm           scsi_disk    tty         watchdog
root@ATK-IMX6U:/sys/class# cd leds
root@ATK-IMX6U:/sys/class/leds# ls
beep  mmc0::  mmc1::  sys-led
```

​	进入sys-led文件夹，就可以看到如下的东西：

```
root@ATK-IMX6U:/sys/class/leds/sys-led# ls -lh
total 0
-rw-r--r-- 1 root root 4.0K Jul 30 09:55 brightness
lrwxrwxrwx 1 root root    0 Jul 30 09:55 device -> ../../../leds
-r--r--r-- 1 root root 4.0K Jul 30 09:55 max_brightness
drwxr-xr-x 2 root root    0 Jul 30 09:55 power
lrwxrwxrwx 1 root root    0 Jul 30 09:55 subsystem -> ../../../../../class/leds
-rw-r--r-- 1 root root 4.0K Jul 30 09:55 trigger
-rw-r--r-- 1 root root 4.0K Jul 30 09:55 uevent
```

​	如果只是想要控制LED的输出状态，我们只需要关心这些就OK：

- brightness：翻译过来就是亮度的意思，该属性文件可读可写；所以这个属性文件是用于设置 LED的亮度等级或者获取当前LED 的亮度等级，譬如 brightness 等于 0 表示LED 灭，brightness 为正整数表示LED 亮，其值越大、LED 越亮；对于 PWM 控制的LED 来说，这通常是适用的，因为它存在亮度等级的问题，不同的亮度等级对应不同的占空比，自然LED 的亮度也是不同的；但对于GPIO控制（控制 GPIO 输出高低电平）的 LED 来说，通常不存在亮度等级这样的说法，只有 LED 亮（brightness 等于 0）和 LED 灭（brightness 为非 0 值的正整数）两种状态，ALPHA/Mini I.MX6U
  开发板上的这颗LED 就是如此，所以自然就不存在亮度等级一说，只有亮和灭两种亮度等级。 
- max_brightness：该属性文件只能被读取，不能写，用于获取 LED 设备的最大亮度等级。 
- trigger：触发模式，该属性文件可读可写，读表示获取LED 当前的触发模式，写表示设置LED 的触发模式。不同的触发模式其触发条件不同，LED 设备会根据不同的触发条件自动控制其亮、灭状态，通过cat 命令查看该属性文件，可获取LED 支持的所有触发模式以及LED 当前被设置的触发模式 

​	我们当然可以查看我们的trigger文件来看看到底是什么：

```
root@ATK-IMX6U:/sys/class/leds/sys-led# cat trigger 
none rc-feedback nand-disk mmc0 mmc1 timer oneshot [heartbeat] backlight gpio 
```

​	方括号（[heartbeat]）括起来的表示当前LED 对应的触发模式，none 表示无触发，常用的触发模式包括none（无触发）、mmc0（当对 mmc0 设备发起读写操作的时候 LED 会闪烁）、timer（LED 会有规律的一亮一灭，被定时器控制住）、heartbeat（心跳呼吸模式，LED 模仿人的心跳呼吸那样亮灭变化）

​	现在，我们就可以试试看操作一下：

```
root@ATK-IMX6U:/sys/class/leds/sys-led# echo "none" > trigger
root@ATK-IMX6U:/sys/class/leds/sys-led# echo "backlight" > trigger
root@ATK-IMX6U:/sys/class/leds/sys-led# cat trigger
none rc-feedback nand-disk mmc0 mmc1 timer oneshot heartbeat [backlight] gpio 
root@ATK-IMX6U:/sys/class/leds/sys-led# echo "oneshot" > trigger
root@ATK-IMX6U:/sys/class/leds/sys-led# cat trigger
none rc-feedback nand-disk mmc0 mmc1 timer [oneshot] heartbeat backlight gpio 
root@ATK-IMX6U:/sys/class/leds/sys-led# echo "timer" > trigger
root@ATK-IMX6U:/sys/class/leds/sys-led# echo "1" > brightness 
root@ATK-IMX6U:/sys/class/leds/sys-led# echo "0" > brightness 
```

​	可以观察板子的现象，变化还是很明显的。我们下面写代码玩！

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static const char* LED_TRIGGER_FILE = "/sys/class/leds/sys-led/trigger";
static const char* LED_BRIGHTNESS_FILE = "/sys/class/leds/sys-led/brightness";
static const char* ON = "1";
static const char* OFF = "0";


static void inline inform_usage(const char* app_name)
{
    fprintf(stderr, "usage:> \n"
    "brightness control: %s <on|off>\n"
    "trigger mode control: %s <trigger> <type>\n", app_name, app_name);
}

static u_int8_t inline control_trigger_type_interface(const char* instructions_type)
{
    int fd = open(LED_TRIGGER_FILE, O_WRONLY);
    if(fd < 0) {
        perror("open file:> ");
        return 0;
    }
    int len = strlen(instructions_type);
    if(len != write(fd, instructions_type, len)){
        perror("write error");
        return 0;
    }
    return 1;
}


static u_int8_t inline control_brightness_impl(const char* value)
{
    int fd = open(LED_BRIGHTNESS_FILE, O_WRONLY);
    if(fd < 0) {
        perror("open file:> ");
        return 0;
    }
    if(!control_trigger_type_interface("none")) 
        return 0;
    if( 1 != write(fd, value, 1)){
        perror("write led brigtness");
        return 0;
    }
    close(fd);
    return 1;
}

static u_int8_t inline control_brightness_interface(const char* instructions)
{
    const char* ptr_at_what = ON;
    if(!strcmp(instructions, "on")){
        return control_brightness_impl(ptr_at_what);
    }else if(!strcmp(instructions, "off")){
        ptr_at_what = OFF;
        return control_brightness_impl(ptr_at_what);
    }else{
        fprintf(stderr, "invalid argument! rejection!");
        return 0;
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 3){
        inform_usage(argv[0]);
        return -1;
    }

    if(argc == 2 && !control_brightness_interface(argv[1])){
        inform_usage(argv[0]);
    }

    if(argc == 3){
        if(strcmp("trigger", argv[1])){
            inform_usage(argv[0]);
            return -1;
        }
        else{
            control_trigger_type_interface(argv[2]);
        }
    }

}
```

​	代码并不复杂，就是对文件进行读写操作！现在可以把文件上传到板子上（如何上传，如何调试请参考笔者的博文：[嵌入式Linux应用层开发——调试专篇（关于使用GDB调试远程下位机开发板的应用层程序办法 + VSCode更好的界面调试体验提升）-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/144446814)）