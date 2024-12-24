# Linux驱动开发之应用层 1

## 操作GPIO

​	首先，请将你的板子调整到

```
root@ATK-IMX6U:~# ls
driver  org  shell
root@ATK-IMX6U:~# ls /sys/class/gpio/
export  gpiochip0  gpiochip128  gpiochip32  gpiochip64  gpiochip96  unexport
```

​	可以看到该目录下包含两个文件 export、unexport 以及 5 个 gpiochipX（X 等于 0、32、64、96、128）命名的文件夹。 
​	gpiochipX：当前SoC 所包含的GPIO 控制器，I.MX6UL/I.MX6ULL 一共包含了5 个GPIO控制器，分别为GPIO1、GPIO2、GPIO3、GPIO4、GPIO5，在这里分别对应 gpiochip0、gpiochip32、gpiochip64、gpiochip96、gpiochip128 这 5 个文件夹，每一个gpiochipX 文件夹用来管理一组GPIO。随便进入到其中某个目录下，可以看到这些目录下包含了如下文件：

​	我们随心的进入一个gpiochip：

```
root@ATK-IMX6U:/sys/class/gpio# cd gpiochip0
root@ATK-IMX6U:/sys/class/gpio/gpiochip0# ls
base  device  label  ngpio  power  subsystem  uevent
```

​	在这个目录我们主要关注的是 base、label、ngpio 这三个属性文件，这三个属性文件均是只读、不可写。 

​	base：与 gpiochipX 中的 X 相同，表示该控制器所管理的这组 GPIO 引脚中最小的编号。每一个 GPIO引脚都会有一个对应的编号，Linux 下通过这个编号来操控对应的GPIO 引脚。

```
root@ATK-IMX6U:/sys/class/gpio/gpiochip0# cat base
0
```

​	label：该组GPIO 对应的标签，也就是名字。 

```
root@ATK-IMX6U:/sys/class/gpio/gpiochip0# cat label 
209c000.gpio
```

​	ngpio：该控制器所管理的GPIO 引脚的数量（所以引脚编号范围是：base ~ base+ngpio-1）

```
root@ATK-IMX6U:/sys/class/gpio/gpiochip0# cat ngpio 
32
```

​	export：这是一个只写的文件。用于将指定编号的 GPIO 引脚导出。在使用GPIO 引脚之前，需要将其导出，导出成功之后才能使用它。注意 export 文件是只写文件，不能读取，将一个指定的编号写入到 export 文件中即可将对应的GPIO 引脚导出，我们只需要往里写编号就可以导出GPIO接口了

```
root@ATK-IMX6U:/sys/class/gpio# echo 0 > export 
root@ATK-IMX6U:/sys/class/gpio# ls
export  gpio0  gpiochip0  gpiochip128  gpiochip32  gpiochip64  gpiochip96  unexport
```

​	unexport：将导出的GPIO 引脚删除。当使用完GPIO 引脚之后，我们需要将导出的引脚删除，同样该文件也是只写文件、不可读，譬如： 

```
root@ATK-IMX6U:/sys/class/gpio# echo 0 > unexport 
root@ATK-IMX6U:/sys/class/gpio# ls
export  gpiochip0  gpiochip128  gpiochip32  gpiochip64  gpiochip96  unexport
```

> Tips：需要注意的是，并不是所有 GPIO 引脚都可以成功导出，**如果对应的 GPIO 已经在内核中被使用了，那便无法成功导出**，打印如下信息： 
>
> ```
> root@ATK-IMX6U:/sys/class/gpio# echo 3 > export 
> -sh: echo: write error: Device or resource busy
> ```
>
> 那也就是意味着该引脚已经被内核使用了，譬如某个驱动使用了该引脚，那么将无法导出成功！ 

​	我们下面来看看导出来的东西有啥！

```
root@ATK-IMX6U:/sys/class/gpio# ls gpio0
active_low  device  direction  edge  power  subsystem  uevent  value
```

​	我们主要关心的文件是 active_low、direction、edge 以及 value 这四个属性文件

direction：配置GPIO 引脚为输入或输出模式。该文件可读、可写，读表示查看 GPIO 当前是输入还是输出模式，写表示将GPIO 配置为输入或输出模式；读取或写入操作可取的值为"out"（输出模式）和"in"（输入模式）

value：在 GPIO 配置为输出模式下，向 value 文件写入"0"控制 GPIO 引脚输出低电平，写入"1"则控制GPIO 引脚输出高电平。在输入模式下，读取value 文件获取GPIO 引脚当前的输入电平状态。

​	下面就是速速编程的时间了：

> gpio读取电平：

```
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static char gpio_path[100];

static int8_t gpio_config(const char* attr, const char* val)
{
    char file_path[100];

    sprintf(file_path, "%s/%s", gpio_path, attr);

    int fd = open(file_path, O_WRONLY);

    if(fd < 0){
        perror("Can not open file: ");
        return fd;
    }

    int len = strlen(val);
    if(len != write(fd, val, len)){
        perror("Can not write: ");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int8_t export_out(const char* gpio)
{
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if(fd < 0){
        perror("Can not open file");
        exit(-1);
    }

    int len = strlen(gpio);
    if(len != write(fd, gpio, len)){
        perror("write error");
        close(fd);
        exit(-1);
    }

    close(fd);

    return 0;

}



int main(int argc, char* argv[])
{
    char file_path[100];
    char val;
    if(argc != 2){
        fprintf(stderr, "usage: %s <gpio>\n", argv[0]);
        exit(-1);
    }


    sprintf(gpio_path, "/sys/class/gpio/gpio%s", argv[1]);

    if(access(gpio_path, F_OK)){
        export_out(argv[1]);
    }

    if(gpio_config("direction", "in"))
        exit(-1);
    
    if(gpio_config("active_low", "0"))
        exit(-1);
    
    if(gpio_config("edge", "none"))
        exit(-1);

    sprintf(file_path, "%s/%s", gpio_path, "value");

    int fd = open(file_path, O_RDONLY);
        if(fd < 0){
        perror("Can not open file");
        exit(-1);
    }

    if(0 > read(fd, &val, 1)){
        perror("read error");
        close(fd);
        return -1;
    }

    printf("value: %c\n", val);
    close(fd);
    return 0;
}
```

```
root@ATK-IMX6U:~/app# ./gpio
usage: ./gpio <gpio>
root@ATK-IMX6U:~/app# ./gpio 1
value: 0
```

> gpio设置电平

```
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static char gpio_path[100];

static int8_t gpio_config(const char* attr, const char* val)
{
    char file_path[100];

    sprintf(file_path, "%s/%s", gpio_path, attr);

    int fd = open(file_path, O_WRONLY);

    if(fd < 0){
        perror("Can not open file: ");
        return fd;
    }

    int len = strlen(val);
    if(len != write(fd, val, len)){
        perror("Can not write: ");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int8_t export_out(const char* gpio)
{
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if(fd < 0){
        perror("Can not open file");
        exit(-1);
    }

    int len = strlen(gpio);
    if(len != write(fd, gpio, len)){
        perror("write error");
        close(fd);
        exit(-1);
    }

    close(fd);

    return 0;

}

int main(int argc, char* argv[])
{
    char file_path[100];
    char val;
    if(argc != 3){
        fprintf(stderr, "usage: %s <gpio>\n", argv[0]);
        exit(-1);
    }


    sprintf(gpio_path, "/sys/class/gpio/gpio%s", argv[1]);

    if(access(gpio_path, F_OK)){
        export_out(argv[1]);
    }

    if(gpio_config("direction", "out"))
        exit(-1);
    
    if(gpio_config("active_low", "0"))
        exit(-1);
    
    if(gpio_config("value", argv[2]))
        exit(-1);

    return 0;
}
```

```
root@ATK-IMX6U:~/app# ./gpio_output 
usage: ./gpio_output <gpio>
root@ATK-IMX6U:~/app# ./gpio_output 1 1
root@ATK-IMX6U:~/app# ./gpio 1
value: 1
root@ATK-IMX6U:~/app# ./gpio_output 1 0
root@ATK-IMX6U:~/app# ./gpio 1
value: 0
```

