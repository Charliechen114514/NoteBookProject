# 深入理解Linux内核和驱动开发1：理解printk和派生的宏

## 先说一说printk

​	printk是一个初入驱动，大伙很快就会接触的一个函数。这个函数，如果你熟悉C语言编程的话，会立马想到一个标准C的printf，或者是如果喜欢现代C++的朋友，会想到std::print，当然，这里的printk在大多数的场景下，同printf几乎完全一致。它同样支持大部分场景下的格式化的字符串输出，从而方便我们在内核调试和追踪的时候查看系统容的状态，或者说，这就是日志的一个根基。

​	因此，完全介绍printk的源码级别的工作原理，就显得离题了，大部分的朋友也不关心这个（大部分人只是想直到如何使用）。基于此，我们直接说它跟printf不太一样的地方吧！

### 日志登级的控制

​	printk和派生的宏的一个重要同printf的区别在于——他是支持日志等级的区分的。因此，几个重要的子问题应运而生——如何使用等级化的日志打印？如何设置内核输出的日志等级的下限从而方便我们的调试？

​	让我们现来看看printk支持的的等级吧！

| 名称         | 字符串 | 别名函数                                                     |
| :----------- | :----- | :----------------------------------------------------------- |
| KERN_EMERG   | “0”    | [`pr_emerg()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_emerg) |
| KERN_ALERT   | “1”    | [`pr_alert()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_alert) |
| KERN_CRIT    | “2”    | [`pr_crit()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_crit) |
| KERN_ERR     | “3”    | [`pr_err()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_err) |
| KERN_WARNING | “4”    | [`pr_warn()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_warn) |
| KERN_NOTICE  | “5”    | [`pr_notice()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_notice) |
| KERN_INFO    | “6”    | [`pr_info()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_info) |
| KERN_DEBUG   | “7”    | [`pr_debug()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_debug) and [`pr_devel()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_devel) 若定义了DEBUG |
| KERN_DEFAULT | “”     |                                                              |
| KERN_CONT    | “c”    | [`pr_cont()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_cont) |

```
#define	KERN_EMERG	"<0>"	/* system is unusable			*/
#define	KERN_ALERT	"<1>"	/* action must be taken immediately	*/
#define	KERN_CRIT	"<2>"	/* critical conditions			*/
#define	KERN_ERR	"<3>"	/* error conditions			*/
#define	KERN_WARNING	"<4>"	/* warning conditions			*/
#define	KERN_NOTICE	"<5>"	/* normal but significant condition	*/
#define	KERN_INFO	"<6>"	/* informational			*/
#define	KERN_DEBUG	"<7>"	/* debug-level messages			*/
```

​	这些就是支持的等级，**日志级别指定了一条消息的重要性。内核根据日志级别和当前 *console_loglevel* （一个内核变量）决定是否立即显示消息（将其打印到当前控制台）。如果消息的优先级比 *console_loglevel* 高（日志级别值较低），消息将被打印到控制台。（这一部分是笔者摘自printk文档的）**

​	其中，KERN_DEFAULT是我们内核默认的一个等级，可以设置，默认的情况下，大部分朋友直接使用我们的printk后装入格式化的字符串，就是使用默认的可见的日志登级在控制台上输出我们的信息。实际上我们的printk的最标准的格式还是：

```
printk(KERN_INFO "Message: %s\n", arg);
```

​	每一次写KERN_INFO等等级控制的宏实在是很麻烦，由此，我们选择上面笔者给出的栏目的最右一侧的一系列的宏，他们简化了我们的复杂的printk书写，现代内核社区也推介使用后面这些一眼可以看到想要使用的日志Level的宏

### 查看和修改我们的日志等级

​	控制台如何显示，显示哪些等级的信息，是内核进行控制，那我们如何进行操作呢？答案是使用最为推介的，修改`/proc/sys/kernel/printk`的办法。

​	我们先说说`/proc/sys/kernel/printk`的内容有啥吧！

```
$ cat /proc/sys/kernel/printk
4        4        1        7
```

​	笔者的Ubuntu上位机得到的结果是这样的，一些发行版或者是自己手搓的Linux发行版也许会有大大小小的差异。但是不管怎么说，这个数字的意思是这样的：`*current*, *default*, *minimum* `和` *boot-time-default`*，依次的意思是

- 当前的***控制台日志级别***，老样子，我们主要盖顶改动的是这个，只有优先级高于这个级别（这里是4，表达的是，KERN_WARNING和更加紧急的信息）会被打印
- 我们***默认消息日志级别***，这里就是我们的KERN_DEFAULT的动态设置的地方了，默认的情况下，当我们直接给printk塞上字符串，使用的就是这个等级的日志打印
- ***最小控制台日志级别，控制台日志级别可被设置的最小值（最高优先级）***，意思就是，我们自己设置printk的打印的Level中，最高优先级设置的天花板在那里，这里显然，我们使用pr_emerg自然也就是无效的
- 系统启动时内核使用的初始控制台日志级别。在启动完成后，此值会被 `current` 覆盖。也就是说，我们默认打开所有系统启动的日志，笔者自己也是这样做的，方便观察系统的启动是否正常

## 关于printk的一部分尾巴

> 除了比等效的[`printk()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.printk)调用更简洁之外，它们还可以通过[`pr_fmt()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_fmt)宏为格式字符串使用一个通用 的定义。**例如，在源文件的顶部（在任何 `#include` 指令之前）定义这样的内容:**
>
> ```
> #define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__
> ```
>
> 会在该文件中的每一条 pr_*() 消息前加上发起该消息的模块和函数名称。这里是直接覆盖了默认的pr_fmt的定义做到的
>
> 为了调试，还有两个有条件编译的宏： [`pr_debug()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_debug)和[`pr_devel()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_devel)，除非定义了 `DEBUG` (或者在[`pr_debug()`](https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_debug)的情况下定义了 `CONFIG_DYNAMIC_DEBUG` )，否则它们不会被编译。

## 驱动开发中更加应该使用的dev_*宏

​	然而，大部分情况下，我们作为驱动开发，可能更加喜欢使用的是dev\_\*宏，这个是老内核所没有的，新内核中所有驱动都在使用的是dev\_\*宏。那问题来了，有什么好处可以让我们选择使用dev日志输出宏而不是别的呢？答案是：**自动附加设备上下文信息**（如设备名称、总线地址等），使得日志更具可读性和调试价值。这一点，我们就知道我们没有必要手搓基于printk的自动化的格式化打印了，人家内核做好了。

```
dev_emerg(dev, fmt, ...)    // 最高优先级（系统不可用）
dev_alert(dev, fmt, ...)
dev_crit(dev, fmt, ...)
dev_err(dev, fmt, ...)      // 错误
dev_warn(dev, fmt, ...)     // 警告
dev_notice(dev, fmt, ...)   // 普通但重要的事件
dev_info(dev, fmt, ...)     // 提示信息
dev_dbg(dev, fmt, ...)      // 调试信息（最低优先级）
```

​	这个事情是类似的，我们的日志宏本身派生于printk一样的日志系统基础，自然也就有了这些标准的日志等级属性的问题。但是我们还需要留意的是参数多了一个dev，这个dev，实际上就是`struct device`结构体的指针，我们的**自动附加设备上下文信息**就是从这里获取的，提供这个也是很自然的事情

```c
static int my_driver_probe(struct platform_device *pdev) {
    struct my_device *dev;
    struct device *hwdev = &pdev->dev;

    dev = devm_kzalloc(hwdev, sizeof(*dev), GFP_KERNEL);
    if (!dev) {
        dev_err(hwdev, "Failed to allocate device memory\n");
        return -ENOMEM;
    }

    dev_info(hwdev, "Device probed (vendor=%04x)\n", read_vendor_id());
    return 0;
}
```

​	这就是一个例子。

## Bonus：一些细节的指引

- `dev_*` 宏定义在头文件 **`include/linux/dev_printk.h`** 中：

  ```
  #define dev_emerg(dev, fmt, ...) \
  	dev_printk_index_wrap(_dev_emerg, KERN_EMERG, dev, dev_fmt(fmt), ##__VA_ARGS__)
  #define dev_crit(dev, fmt, ...) \
  	dev_printk_index_wrap(_dev_crit, KERN_CRIT, dev, dev_fmt(fmt), ##__VA_ARGS__)
  #define dev_alert(dev, fmt, ...) \
  	dev_printk_index_wrap(_dev_alert, KERN_ALERT, dev, dev_fmt(fmt), ##__VA_ARGS__)
  #define dev_err(dev, fmt, ...) \
  	dev_printk_index_wrap(_dev_err, KERN_ERR, dev, dev_fmt(fmt), ##__VA_ARGS__)
  #define dev_warn(dev, fmt, ...) \
  	dev_printk_index_wrap(_dev_warn, KERN_WARNING, dev, dev_fmt(fmt), ##__VA_ARGS__)
  #define dev_notice(dev, fmt, ...) \
  	dev_printk_index_wrap(_dev_notice, KERN_NOTICE, dev, dev_fmt(fmt), ##__VA_ARGS__)
  #define dev_info(dev, fmt, ...) \
  	dev_printk_index_wrap(_dev_info, KERN_INFO, dev, dev_fmt(fmt), ##__VA_ARGS__)
  ```

  最终调用 `dev_printk_emit()`，将设备信息与日志消息拼接。

#### **(2) 设备信息的生成**

- 设备标识信息通过 `dev_driver_string(dev)` 生成，例如：
  - PCI 设备：`pci 0000:00:1a.0`
  - USB 设备：`usb 1-1.2`

#### **(3) 资源管理集成**

- `dev_*` 宏常与 `devm_*` 资源管理函数（如 `devm_kzalloc()`）配合使用。若资源分配失败，`dev_err()` 可以直接关联到具体设备



# 参考

[使用printk记录消息 — The Linux Kernel documentation](https://www.kernel.org/doc/html/latest/translations/zh_CN/core-api/printk-basics.html)