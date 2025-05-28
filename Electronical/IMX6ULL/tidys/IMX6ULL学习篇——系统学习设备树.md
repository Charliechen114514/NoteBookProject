# IMX6ULL学习篇——系统学习设备树

​	这篇博客的目的是系统的整理一下设备树当中的一些非常基本的概念。基于之前的学习，我们已经至少掌握了字符设备的基本的框架，编写一个最简单的字符设备简单的流程。

​	但是我们知道，一个外设很有可能是非常复杂，带有的描述信息是非常繁多的，为了一定的可移植性（或者说，不要在代码里拉依托大的描述信息），我们会使用设备树本身来解耦合对设备的描述，这就是为什么我们要学习设备树。

## 啥是设备树

​	设备树，设备树，一颗描述设备的树！设备树是一种用来描述硬件信息的数据结构，对于内核而言，这是一个硬件的地图，找设备的时候，就会爬取这颗树获取到设备的一切信息。设备树的诞生原因笔者会在下面简单介绍。简单的说：它的核心思想是将硬件描述与操作系统内核分离开来。硬件信息不再写在内核代码中，而是放在一个单独的文件里，这个文件就是设备树文件（通常以`.dts`或`.dtsi`为后缀）。操作系统启动时，会读取这个文件，解析其中的内容，然后根据文件中的描述来初始化硬件。这样一来，硬件信息就变得非常灵活，开发者只需要修改设备树文件，而不需要动内核代码。

​	一棵树必然有一个根节点。这个根节点代表整个系统，下面有很多子节点，每个子节点代表一个硬件设备或一个硬件模块。比如，一个设备树文件可能会有一个根节点，下面有CPU节点、内存节点、外设节点（如UART、I2C、SPI等）。每个节点里会包含一些属性，用来描述这个设备的具体信息。比如，一个UART节点可能会包含设备的地址、中断号、时钟频率等信息。举个例子，假设你有一个嵌入式开发板，上面有一个ARM处理器、512MB的内存、一个UART串口和一个I2C接口。在没有设备树的情况下，你可能需要在内核代码中手动写出这些硬件的地址、中断号等信息。而有了设备树之后，你只需要在一个设备树文件中描述这些硬件，内核启动时会自动读取这个文件并初始化硬件。如果你换了一个开发板，硬件配置变了，你只需要修改设备树文件，而不需要重新编译内核。

​	这样看，设备树的作用就是让操作系统能够以一种灵活、标准化的方式了解和管理硬件资源。它把硬件信息从内核代码中分离出来，使得内核代码更加通用，硬件配置更加灵活。无论是移植内核到新的硬件平台，还是调试和维护系统，设备树都大大简化了这些工作。通过设备树，开发者可以更专注于软件的逻辑，而不需要为硬件的细节操心。你只需要查手册，嘎嘎按照设备树的语法编写设备树，你就可以让Linux在你的外设板子上启动了，多简单！

​	当然，我打算重复劳作一次，我们看看Device Tree Specification中的文档（笔者的文档使用的是比较新的V0.4版本，当然跟其他博客不太一样，大多数博客使用的版本是0.2版本）对Device Tree的介绍：

> A devicetree is a tree data structure with nodes that describe the devices in a system. Each node has property/value pairs 
> that describe the characteristics of the device being represented. Each node has exactly one parent except for the root node, 
> which has no parent.
> A device in this context may be an actual hardware device, such as a UART. It may be part of a hardware device, such as the 
> random-number generator in a TPM. It may also be a device provided through virtualisation, such as a protocol providing 
> access to an I2C device attached to a remote CPU. A device may include functions implemented by firmware running in 
> higher privilege levels or remote processors. There is no requirement that nodes in a device tree be a physical hardware 
> device, but generally they have some correlation to physical hardware devices. Nodes should not be designed for OS- or 
> project- specific purposes. They should describe something which can be implemented by any OS or project.
> A devicetree is often used to describe devices which cannot necessarily be dynamically detected by a client program. For 
> example, the architecture of PCI enables a client to probe and detect attached devices and thus devicetree nodes describing 
> PCI devices might not be required. However, a device node is often used to describe a PCI host bridge device in the system. 
> This node is required if the bridge cannot be detected by probing, but is otherwise optional. Also, a bootloader may do 
> PCI probing and produce a device tree containing the results of its scan, for passing to the Operating System.

​	笔者简单的翻译一下：

> 设备树是一种树形数据结构，其节点描述系统中的设备。每个节点都有属性/值对，用于描述所表示设备的特征。除了根节点之外，每个节点只有一个父节点，而根节点没有父节点。
> 在这种情况下，设备可能是实际的硬件设备，例如 UART。它可能是硬件设备的一部分，例如 TPM 中的随机数生成器。它也可能是通过虚拟化提供的设备，例如提供对连接到远程 CPU 的 I2C 设备的访问的协议。设备可能包括由在更高权限级别或远程处理器中运行的固件实现的功能。设备树中的节点不一定是物理硬件设备，但通常它们与物理硬件设备具有某种关联。节点不应设计用于特定于操作系统或项目的目的。它们应该描述可以由任何操作系统或项目实现的内容。
> 设备树通常用于描述客户端程序不一定能动态检测到的设备。例如，PCI 的架构使客户端能够探测和检测连接的设备，因此可能不需要描述 PCI 设备的设备树节点。但是，设备节点通常用于描述系统中的 PCI 主机桥设备。如果无法通过探测检测到桥，则需要此节点，否则是可选的。此外，引导加载程序可以执行 PCI 探测并生成包含其扫描结果的设备树，以传递给操作系统。

​	我想我说的很明白了。

## 所以，为什么要出现设备树

​	这个事情已经算是津津乐道了。我们知道，ARM的商业方式是——ARM公司授权架构，而我们的厂商利用ARM架构作为图纸特化自己的芯片，所以，我们的基于ARM架构的CPU信息实际上是五花八门，可以说是相同中存在不同，不同中又存在了一部分的相同的东西。

​	这是一个问题——在没有设备树之前，我们的板级BSP的外设信息是直接填写到内核里面去的。在ARM后来爆发式的发展，每年成十上百的新芯片都在诞生，争先恐后的往内核中提交代码。这些代码看起来只是对芯片的描述信息有所不同，但是因为外设之间存在差异，导致没法直接共用抽象，只好硬耦合在内核代码中。很快，内核就开始虚胖起来——举个例子，很难想象自己使用的是IMX6ULL，在拉取代码的时候百分之五十以上的时间在拉取跟自己板子完全没关系的东西。

​	这个问题不算大，顶多等久一点，但是问题在于，我们的ARM板子上的外设很有可能发生动态的调整，你的每一次轻微的调整——都需要重新编译一次内核，如果你不幸的把编译清理了——oh我的伙计，你就要重新等上几个小时了。这实在是太地狱了。另外一方面，我们的硬件和软件驱动直接被耦合在了一起，改的时候你要翻阅一大堆的文件抵达配置。。。

​	种种不适，导致我们的Linus Torvalds在2011年的3月17日在邮件列表中开喷：

> Gaah. Guys, this whole ARM thing is a f*cking pain in the ass.

​	好吧，我们必须看到，的确存在这样的问题——我们只是简单的复制粘贴，然后修改一下就提交到内核上去，实在是有点不太好。因此，我们需要做的事情就很简单，把设备描述从内核中解耦合出来！这就是设备树产生的重要缘由

## 设备树的文件系统层级介绍

​	之前的实验中，大伙多多少少也算接触了设备树这个概念，大家修订的文件是dts文件，也就是Device Tree Source文件，这是一个描述我们设备树的ASCII文本文件，也是满足一定语法的，满足何种语法，是我们等回会讨论的话题。我们的内核的Tools中存在一个非常重要的工具，叫DTC，Device Tree Compiler，负责编译我们的dts文件生成一个内核可以识别，可以读取信息的DTB（Device Tree Blob设备树块）文件，这个文件大家一下子看懂了，就是我们在使用uboot传递启动参数的时候，我们把设备块文件放置到物理地址83000000处启动起来的。

​	我们在`make all`的时候，就会根据我们的config，编译我们的内核，和编译我们对应的板子的设备树（这个设备树如果用的是人家的产品，编写人家写好的设备树，否则我们自己写）。

​	如果我们是在做开发，自己写设备树，内核已经编译过一次且保证不会修改，我们就可以使用`make dtbs`只编译设备树。

​	设备树的官方文档这样阐述我们的DTB, DTS和DTC

> DTB: Devicetree blob. Compact binary representation of the devicetree.(设备树的紧凑二进制表示。)
> DTC: Devicetree compiler. An open source tool used to create DTB files from DTS files.(用于从 DTS 文件创建 DTB 文件的开源工具。)
> DTS: Devicetree syntax. A textual representation of a devicetree consumed by the DTC. (DTC 使用的设备树的文本表示。)

## 设备树语法的分析若干

​	我们下面就来简单的看看设备树的语法。笔者看来的第一个反应就是有点类似于XML了，

```
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/dts-v1/;

#include <dt-bindings/input/input.h>
#include "imx6ull.dtsi"

/ {
	model = "Freescale i.MX6 ULL 14x14 EVK Board";
	compatible = "fsl,imx6ull-14x14-evk", "fsl,imx6ull";

	chosen {
		stdout-path = &uart1;
	};
	...
```

​	笔者随手截取了自己更改的一个DTS文件，可以看到我们的要素有这样的一些东西。

### 说一下/dts-v1/

​	这个玩意是一个声明，参考文档V4文档的第62页，我们的手册谈到了：

> /dts-v1/；应存在以将文件标识为版本 1 DTS（没有此标记的 dts 文件将被 dtc 视为过时的版本 0，该版本使用不同的整数格式以及其他细小但不兼容的更改）。

说白了，这是明确设备树源文件遵循的语法版本，确保解析工具能正确解释文件内容。所以如果您是编写设备树的原厂大佬，发现自己一直惯用的设备树语法过不去DTC，可以看看是不是这里出现了问题。

### #include，跟C语言的预处理一样含义的包含头文件

​	这是不是我们的C语言的预处理器吗，下此记得标明出处。好吧开个玩笑，当然，正儿八经的写法结合我们的V0.4手册（第59页）

> 可以从 DTS 文件包含其他源文件。包含文件的名称应以“.dtsi”结尾。包含的文件又可以包含其他文件。
> `/include/ "FILE"`

​	但是在这里，我们更习惯用#include来做这个事情，Linux下的DTC可以正确的处理：这里我们的语义相同：即include不关心文件后缀，只是把文件内容进行黏贴放置到预处理器的调用位置。

​	我们习惯上知道，自己家的芯片可能是派生的，所以回跟自己的派生芯片多少有些共同点，所以我们会include进来父芯片的内容，这就是dtsi文件的作用，我们看到，NXP官方基于IMX6ULL这个芯片派生出了很多个板子的配置，但是核心是我们的IMX6ULL大东西不会改变，因此，在imx6ull.dtsi文件中，就会存放我们的CPU不会变动，或者说BSP外设中的默认信息。

### 设备节点

​	我们下面就来看看我们的设备树.笔者推介您观察一下`arch/arm/boot/dts/imx6ull-14x14-evk.dts`文件,这个文件需要到NXP下下载他们裁剪的内核.

```
/ {
	model = "Freescale i.MX6 ULL 14x14 EVK Board";
	compatible = "fsl,imx6ull-14x14-evk", "fsl,imx6ull";

	chosen {
		stdout-path = &uart1;
	};

	memory {
		reg = <0x80000000 0x20000000>;
	};

	...
```

​	嗯,我们的/,表达的就是根节点,之后我们查找设备树解析出来的目录,就是/,其他的设备就会挂载到这个目录下,我们的驱动程序就可以去读取解析出来的信息,驱动程序就可以正确的拿到外设信息后操作我们的外设.

​	注意,我们的设备树当中呢,不是键值对,就是一个子树.你看:

```
	model = "Freescale i.MX6 ULL 14x14 EVK Board";
	compatible = "fsl,imx6ull-14x14-evk", "fsl,imx6ull";
```

​	就是一些键值对,我们的键就是model,值就是"Freescale i.MX6 ULL 14x14 EVK Board".你的阅读结果是——设备的model属性的值是"Freescale i.MX6 ULL 14x14 EVK Board"。很好！这里需要说明的是，这样的赋值，可以有三种。

> 1. 字符串：上面就是一个例子
> 2. 无符号整数：上述代码设置 reg 属性的值为 0，也可以设置为一组值：<0 0x123456 100>
> 3. 字符串列表 属性值也可以为字符串列表，字符串和字符串之间采用英文的逗号隔开

​	我们下面看chosen，嗯？这是啥意思呢？答案是，我们多加了父节点中的根节点设备树上chosen的信息，请看`arch/arm/boot/dts/imx6ul.dtsi`文件的内容

```
/ {
	aliases {
		can0 = &flexcan1;
		...
		usbphy1 = &usbphy2;
	};

	cpus {
		#address-cells = <1>;
		#size-cells = <0>;

		cpu0: cpu@0 {
			compatible = "arm,cortex-a7";
			device_type = "cpu";
			reg = <0>;
			clock-latency = <61036>; /* two CLK32 periods */
			operating-points = <
				/* kHz	uV */
				696000	1275000
				528000	1175000
				396000	1025000
				198000	950000
			>;
			...
		};
	};

	intc: interrupt-controller@00a01000 {
		compatible = "arm,cortex-a7-gic";
		#interrupt-cells = <3>;
		interrupt-controller;
		reg = <0x00a01000 0x1000>,
		      <0x00a02000 0x100>;
	};

	...
	
```

​	你搜索整个文件，会发现并没有chosen的信息，这个时候，我们的DTC就会把在自己特化的文件中对/的信息合并进入其他的include的文件对/的描述中去。

​	换而言之：你追加本来没有的键值对或者是子节点，这个东西就会在生成DTB之前合并起来，相当于追加信息的作用。

​	这个dtsi文件中又出现了一些新的写法：

#### 设备的标准描述办法

```
node-name@unit-address 
```

​	其中“node-name”是节点名字，为 ASCII 字符串，节点名字应该能够清晰的描述出节点的功能，比如“uart1”就表示这个节点是 UART1 外设。“unit-address”一般表示设备的地址或寄存器首地址，如果某个节点没有地址或者寄存器的话“unit-address”可以不要，比如“cpu@0”

​	你看，随手就可以找到一个例子：interrupt-controller@00a01000。



#### 别名：方便的重命名我们的设备

```
cpu0:cpu@0 
```

​	之后，我们访问cpu0，实际上就是在访问cpu@0。很简单，这里咱们就不再重复了。



### 几个比较经典的属性

​	我们下面就要介绍几个经典的属性，不是说因为我们不是干原厂的，这个就不用学，我们改设备树的时候，要知道常用的几个键值对中键的名称的含义，不然连去哪里改都不知道。

#### compatible

​	这个属性非常的重要！这说明了我们的这个设备树节点的配置是适用于哪一款外设的。我们驱动和设备树信息对接的时候，就会查compatible的信息，不对就用不了。

​	compatible属性值由一个或多个字符串组成，这些字符串定义设备的特定编程模型。客户端程序应使用此字符串列表来选择设备驱动程序。属性值由一个连接列表组成，列表以空字符结尾，从最具体到最通用。它们允许设备表达其与一系列类似设备的兼容性，从而可能允许单个设备驱动程序与多个设备匹配。

​	一个建议的建议的格式为“制造商，型号”，其中制造商是描述制造商名称的字符串（例如股票代码），型号指定型号。兼容字符串应仅由小写字母、数字和破折号组成，并且应以字母开头。单个逗号通常仅用于供应商前缀后。不应使用下划线。

​	我们举一个例子：

```
compatible = "fsl,imx6ull-14x14-evk", "fsl,imx6ull";
```

​	这就是说明我们的设备树会尝试查找我们的支持fsl,imx6ull-14x14-evk的一个驱动程序（关于具体查询，是后面我们慢慢编写基于设备树驱动的程序才会设计到），找不到就后退到fsl,imx6ull，意味着这里是存在优先级的，我们修改的时候也要按照匹配层次进行修改。一般驱动程序文件都会有一个OF 匹配表，此OF 匹配表保存着一些 compatible 值，如果设备节点的 compatible 属性值和 OF 匹配表中的任何一个值相等，那么就表示设备可以使用这个驱动

#### model

​	model 属性值是一个 `<string>`，用于指定设备制造商的型号。建议的格式为：“manufacturer,model”，其中，manufacturer 是描述制造商名称的字符串（例如股票代码），model 指定型号。这个没啥好说的，跟我们没啥关系

#### status

​	status 属性表示设备的运行状态。我们在设备树这一侧就可以进行静态的使能或者是失能我们的设备。缺少 status 属性时应视为该属性存在且值为“okay”。笔者从文档中摘出了常用的值，这里先放到下面供大家参考

| 值 (Value)   | 描述 (Description)                                           |
| ------------ | ------------------------------------------------------------ |
| `"okay"`     | 表示设备处于可操作状态。                                     |
| `"disabled"` | 表示设备当前不可操作，但未来可能变为可操作（例如，某些设备未插入或关闭）。具体含义需参考设备绑定文档。 |
| `"reserved"` | 表示设备可操作，但不应被使用。通常用于由其他软件组件（如平台固件）控制的设备。 |
| `"fail"`     | 表示设备不可操作。设备检测到严重错误，且在不修复的情况下不太可能恢复操作。 |
| `"fail-sss"` | 表示设备不可操作。设备检测到严重错误，且在不修复的情况下不太可能恢复操作。`sss` 部分为设备特定的错误代码，表示检测到的错误条件。 |

#### #address-cells，#size-cells

​	`#address-cells` 和 `#size-cells` 属性可用于设备树层次结构中具有子节点的任何设备节点，并描述应如何寻址子设备节点。#address-cells 属性定义用于对子节点的 reg 属性中的地址字段进行编码的 `<u32>` 单元数。#size-cells 属性定义用于对子节点的 reg 属性中的 size 字段进行编码的 `<u32> `单元数。说白了，就是这两个说明了我们要如何编写我们的reg属性字段：#address-cells 属性值决定了子节点 reg 属性中地址信息所占用的字长(32 位)，size-cells说明长度信息所占据的字长（32位）

​	#address-cells 和 #size-cells 属性不是从设备树中的祖先继承而来的。它们应被明确定义。符合 DTSpec 的启动程序应在所有具有子节点的节点上提供 #address-cells 和 #size-cells。如果缺失，客户端程序应假设 #address-cells 的默认值为 2，#size-cells 的默认值为 1。


```
soc {
	#address-cells = <1>;
	#size-cells = <1>;

	serial@4600 {
		compatible = "ns16550";
		reg = <0x4600 0x100>;
		clock-frequency = <0>;
		breaks = <0xA 0x8>;
		break-parent = <&ipic>;
	};
};
```

​	我们的soc 节点的 #address-cells 和 #size-cells 属性均设置为 1。这是啥意思呢？这个的意思就是我们的地址信息占用1个32位就够了（你看，0x4600说完了），长度也是1，你看，0x100也说完了。此设置指定需要一个单元来表示地址，需要一个单元来表示此节点的子节点的大小。串行设备 reg 属性必须遵循父 (soc) 节点中设置的此规范 - 地址由单个单元 (0x4600) 表示，大小由单个单元 (0x100) 表示。

#### reg

​	如果上面的描述您没有看明白，来看看这个

​	reg 属性描述设备资源在其父总线定义的地址空间内的地址。最常见的情况是，这意味着内存映射 IO 寄存器块的偏移量和长度，但在某些总线类型上可能具有不同的含义。根节点定义的地址空间中的地址是 CPU 实际地址。该值是一个 `<prop-encoded-array>`，由任意数量的地址和长度对 `<address length>` 组成。指定地址和长度所需的` <u32> `个单元数是总线特定的，由设备节点父级中的 #address-cells 和 #size-cells 属性指定。如果父节点为 #size-cells 指定了 0 值，则应省略 reg 值中的长度字段。

​	假设片上系统中的设备有两个寄存器块，一个 32 字节块位于 SOC 中的偏移量 0x3000，另一个 256 字节块位于偏移量 0xFE00。reg 属性将按以下方式编码（假设 #address-cells 和 #size-cells 值为 1）：

```
reg = <0x3000 0x20 0xFE00 0x100>;
```

#### ranges

​	想象一下，你有一个大房子（父地址空间），里面有很多房间（子地址空间）。每个房间都有自己的门牌号（子地址），但如果你想从外面找到某个房间，你需要知道它在大房子中的具体位置（父地址）。`ranges` 就像是一个“地址转换表”，它告诉你怎么把房间的门牌号（子地址）转换成大房子中的具体位置（父地址）。这就是ranges，相当于非常直白的把地址的映射给你坦白了。

​	所以，我们就需要知道——映射双方的起始地址和映射的长度，ranges的结构也就清晰了：

​	`ranges` 属性提供了一种定义总线地址空间（子地址空间）与总线节点父地址空间（父地址空间）之间映射或转换的方法。 `ranges` 属性的值格式为任意数量的三元组（`child-bus-address`, `parent-bus-address`, `length`）：  
- **`child-bus-address`** 是子总线地址空间内的物理地址。地址的单元格数量取决于总线，并可以从当前节点（即包含 `ranges` 属性的节点）的 `#address-cells` 属性中确定。  
- **`parent-bus-address`** 是父总线地址空间内的物理地址。地址的单元格数量取决于总线，并可以从定义父地址空间的节点的 `#address-cells` 属性中确定。  
- **`length`** 指定子地址空间中范围的大小。大小的单元格数量可以从当前节点（即包含 `ranges` 属性的节点）的 `#size-cells` 属性中确定。  

如果 `ranges` 属性被定义为 `<empty>`（空值），则表示父地址空间和子地址空间是相同的，不需要地址转换。 如果总线节点中不存在 `ranges` 属性，则假定该节点的子节点与父地址空间之间不存在映射关系。

```dts
soc {
    compatible = "simple-bus";
    #address-cells = <1>;
    #size-cells = <1>;
    ranges = <0x0 0xe0000000 0x00100000>;

    serial@4600 {
        device_type = "serial";
        compatible = "ns16550";
        reg = <0x4600 0x100>;
        clock-frequency = <0>;
        interrupts = <0xA 0x8>;
        interrupt-parent = <&ipic>;
    };
};
```

在 `soc` 节点中，`ranges` 属性被定义为：  
```dts
<0x0 0xe0000000 0x00100000>;
```
该属性值指定了一个 1024 KB 的地址空间范围，其中子节点在物理地址 `0x0` 处映射到父地址 `0xe0000000`。通过此映射，串行设备节点可以通过加载或存储地址 `0xe0004600` 进行访问，该地址是 `reg` 中指定的偏移量 `0x4600` 加上 `ranges` 中指定的 `0xe0000000` 映射的结果。

## 设备树的传递：Linux解析uboot等bootloader传递的DTB文件

​	我们的DTB文件解析步骤就是这样：

1. Bootloader 加载 DTB 文件并传递给内核。
2. 内核在早期阶段解析 DTB，获取关键信息（如内存布局和内核命令行参数）。
3. 内核在内存管理子系统初始化后，完整解析 DTB，构建设备树结构。
4. 将设备树中的设备节点注册为平台设备。
5. 驱动与设备匹配，完成设备的初始化。
6. 释放 DTB 文件占用的内存。

   在内核启动的早期阶段，我们的Linux会在下面调用这些函数：

#### 预备

   ##### **`setup_arch()`**
   - 这是架构相关的初始化函数，位于 `arch/arm/kernel/setup.c`（以 ARM 为例）。
   - 它会调用 `setup_machine_fdt()` 来解析 DTB。

   ##### **`setup_machine_fdt()`**
   - 该函数接收 DTB 的物理地址，并将其转换为虚拟地址。
   - 调用 `early_init_dt_scan()` 开始扫描 DTB。

   DTB 的解析分为两个阶段：早期解析和完整解析。

   ###### **阶段一：早期解析（`early_init_dt_scan()`）**

​	为了做好最初始化的准备，我们会解析三个东西，这些信息用于初始化内核的基本功能。

- 解析 `/chosen` 节点，获取内核命令行参数（`bootargs`）。
- 解析 `/memory` 节点，获取系统内存布局。
- 解析 `/reserved-memory` 节点，保留特定的内存区域。

   ###### **阶段二：完整解析（`unflatten_device_tree()`）**
   - 在内存管理子系统初始化之后，内核会进行完整的 DTB 解析。
   - 主要任务：
     - 将 DTB 文件从二进制格式转换为内核内部的设备树结构（`struct device_node`）。
     - 构建设备树的层次结构，将每个节点和属性映射到内核数据结构中。
     - 调用 `of_platform_populate()`，将设备树中的设备节点注册为平台设备。

#### **设备树到内核设备的映射**

   - **`of_platform_populate()`**：
     - 该函数遍历设备树中的节点，将支持的设备节点注册为平台设备。
     - 对于每个设备节点，内核会检查其 `compatible` 属性，并与驱动程序的 `of_match_table` 进行匹配。
   - **平台设备的创建**：
     - 对于每个匹配的设备节点，内核会创建一个 `platform_device` 结构体，并将其注册到内核的设备模型中。

####  **驱动匹配与初始化**

   - **驱动匹配**：
     - 内核会遍历已注册的平台设备，并与已加载的平台驱动程序进行匹配。
     - 匹配的依据是设备树节点的 `compatible` 属性和驱动程序的 `of_match_table`。
   - **设备初始化**：
     - 匹配成功后，内核会调用驱动程序的 `probe()` 函数，初始化设备并使其可用。

#### 释放与回收，完成DTB的使命

​	我们就会回收解析DTB占用的内存，现在设备就已经完成了挂载了。

## 驱动端：OF系列函数——用于查找我们的设备进行操作

​	下面的部分，看官可以不看了，我认为这属于用到在查的内容

Linux 内核提供了一系列用于操作设备树（Device Tree）的函数，这些函数通常以 `of_` 开头，用于查找节点、提取属性值以及进行地址转换等操作。下面我们以通俗易懂的方式整理这些函数的功能和用法。

### 查找节点的函数

1. **`of_find_node_by_name` 函数**  
   这个函数用于通过节点名称查找设备树中的节点。你可以指定从哪个节点开始查找（`from` 参数），如果传入 `NULL`，则从根节点开始查找。`name` 参数是要查找的节点名称。如果找到匹配的节点，函数会返回该节点的指针；如果找不到，则返回 `NULL`。
2. **`of_find_node_by_type` 函数**  
   这个函数通过 `device_type` 属性查找节点。`type` 参数是要查找的 `device_type` 属性值。和 `of_find_node_by_name` 类似，`from` 参数指定查找的起点，如果为 `NULL`，则从根节点开始查找。找到匹配的节点后返回节点指针，否则返回 `NULL`。
3. **`of_find_compatible_node` 函数**  
   这个函数根据 `device_type` 和 `compatible` 属性查找节点。`type` 参数是 `device_type` 属性值（可以为 `NULL`，表示忽略该属性），`compatible` 参数是 `compatible` 属性值。找到匹配的节点后返回节点指针，否则返回 `NULL`。
4. **`of_find_matching_node_and_match` 函数**  
   这个函数通过 `of_device_id` 匹配表查找节点。`matches` 参数是一个 `of_device_id` 匹配表，`match` 参数用于返回匹配到的 `of_device_id`。找到匹配的节点后返回节点指针，否则返回 `NULL`。
5. **`of_find_node_by_path` 函数**  
   这个函数通过路径查找节点。`path` 参数是节点的全路径（例如 `/backlight`）。找到匹配的节点后返回节点指针，否则返回 `NULL`。

### 提取属性值的函数

1. **`of_find_property` 函数**  
   这个函数用于查找指定节点的属性。`np` 参数是设备节点，`name` 参数是属性名称，`lenp` 参数用于返回属性值的字节数。找到属性后返回属性指针，否则返回 `NULL`。

2. **`of_property_count_elems_of_size` 函数**  
   这个函数用于获取属性中元素的数量。`propname` 参数是属性名称，`elem_size` 参数是每个元素的大小。函数返回属性中元素的数量。

3. **`of_property_read_u32_index` 函数**  
   这个函数用于从属性中读取指定索引的 `u32` 类型数据。`index` 参数是要读取的数据索引，`out_value` 参数用于返回读取到的值。函数返回 0 表示成功，返回负值表示失败。

4. **`of_property_read_u8_array`、`of_property_read_u16_array`、`of_property_read_u32_array`、`of_property_read_u64_array` 函数**  
   这些函数用于从属性中读取 `u8`、`u16`、`u32` 或 `u64` 类型的数组数据。`out_values` 参数用于返回读取到的数组值，`sz` 参数是要读取的数组元素数量。函数返回 0 表示成功，返回负值表示失败。

5. **`of_property_read_u8`、`of_property_read_u16`、`of_property_read_u32`、`of_property_read_u64` 函数**  
   这些函数用于读取属性中的单个 `u8`、`u16`、`u32` 或 `u64` 类型数据。`out_value` 参数用于返回读取到的值。函数返回 0 表示成功，返回负值表示失败。

6. **`of_property_read_string` 函数**  
   这个函数用于读取属性中的字符串值。`out_string` 参数用于返回读取到的字符串。函数返回 0 表示成功，返回负值表示失败。

### 其他常用函数

1. **`of_n_addr_cells` 函数**  
   这个函数用于获取节点的 `#address-cells` 属性值。`np` 参数是设备节点。函数返回 `#address-cells` 属性值。

2. **`of_n_size_cells` 函数**  
   这个函数用于获取节点的 `#size-cells` 属性值。`np` 参数是设备节点。函数返回 `#size-cells` 属性值。

3. **`of_device_is_compatible` 函数**  
   这个函数用于检查节点的 `compatible` 属性是否包含指定的字符串。`compat` 参数是要检查的字符串。函数返回正数表示包含，返回 0 表示不包含。

4. **`of_get_address` 函数**  
   这个函数用于获取节点的地址相关属性（如 `reg` 或 `assigned-addresses`）。`index` 参数是要读取的地址索引，`size` 参数用于返回地址长度，`flags` 参数用于返回地址标志。函数返回读取到的地址数据首地址，如果为 `NULL` 表示读取失败。

5. **`of_translate_address` 函数**  
   这个函数用于将设备树中的地址转换为物理地址。`in_addr` 参数是要转换的地址。函数返回转换后的物理地址，如果为 `OF_BAD_ADDR` 表示转换失败。

6. **`of_iomap` 函数**  
   这个函数用于将设备树中的地址映射为虚拟地址。`index` 参数指定要映射的地址段（如果 `reg` 属性有多段）。函数返回映射后的虚拟地址，如果为 `NULL` 表示映射失败。

下面的部分就属于函数的原型，摘选自of.h文件。

---

#### 查找节点的函数

1. **`of_find_node_by_name` 函数**  
   通过节点名称查找设备树中的节点。  
   **函数原型**：  
   ```c
   struct device_node *of_find_node_by_name(struct device_node *from, const char *name);
   ```
   - `from`：开始查找的节点，如果为 `NULL`，则从根节点开始查找。  
   - `name`：要查找的节点名称。  
   - **返回值**：找到的节点指针，如果为 `NULL` 表示查找失败。

2. **`of_find_node_by_type` 函数**  
   通过 `device_type` 属性查找节点。  
   **函数原型**：  
   ```c
   struct device_node *of_find_node_by_type(struct device_node *from, const char *type);
   ```
   - `from`：开始查找的节点，如果为 `NULL`，则从根节点开始查找。  
   - `type`：要查找的 `device_type` 属性值。  
   - **返回值**：找到的节点指针，如果为 `NULL` 表示查找失败。

3. **`of_find_compatible_node` 函数**  
   根据 `device_type` 和 `compatible` 属性查找节点。  
   **函数原型**：  
   ```c
   struct device_node *of_find_compatible_node(struct device_node *from, const char *type, const char *compatible);
   ```
   - `from`：开始查找的节点，如果为 `NULL`，则从根节点开始查找。  
   - `type`：要查找的 `device_type` 属性值（可以为 `NULL`，表示忽略该属性）。  
   - `compatible`：要查找的 `compatible` 属性值。  
   - **返回值**：找到的节点指针，如果为 `NULL` 表示查找失败。

4. **`of_find_matching_node_and_match` 函数**  
   通过 `of_device_id` 匹配表查找节点。  
   **函数原型**：  
   ```c
   struct device_node *of_find_matching_node_and_match(struct device_node *from, const struct of_device_id *matches, const struct of_device_id **match);
   ```
   - `from`：开始查找的节点，如果为 `NULL`，则从根节点开始查找。  
   - `matches`：`of_device_id` 匹配表。  
   - `match`：返回匹配到的 `of_device_id`。  
   - **返回值**：找到的节点指针，如果为 `NULL` 表示查找失败。

5. **`of_find_node_by_path` 函数**  
   通过路径查找节点。  
   **函数原型**：  
   ```c
   struct device_node *of_find_node_by_path(const char *path);
   ```
   - `path`：节点的全路径（例如 `/backlight`）。  
   - **返回值**：找到的节点指针，如果为 `NULL` 表示查找失败。

---

#### 提取属性值的函数

1. **`of_find_property` 函数**  
   查找指定节点的属性。  
   **函数原型**：  
   ```c
   struct property *of_find_property(const struct device_node *np, const char *name, int *lenp);
   ```
   - `np`：设备节点。  
   - `name`：属性名称。  
   - `lenp`：返回属性值的字节数。  
   - **返回值**：找到的属性指针，如果为 `NULL` 表示查找失败。

2. **`of_property_count_elems_of_size` 函数**  
   获取属性中元素的数量。  
   **函数原型**：  
   ```c
   int of_property_count_elems_of_size(const struct device_node *np, const char *propname, int elem_size);
   ```
   - `np`：设备节点。  
   - `propname`：属性名称。  
   - `elem_size`：每个元素的大小。  
   - **返回值**：属性中元素的数量。

3. **`of_property_read_u32_index` 函数**  
   从属性中读取指定索引的 `u32` 类型数据。  
   **函数原型**：  
   ```c
   int of_property_read_u32_index(const struct device_node *np, const char *propname, u32 index, u32 *out_value);
   ```
   - `np`：设备节点。  
   - `propname`：属性名称。  
   - `index`：要读取的数据索引。  
   - `out_value`：返回读取到的值。  
   - **返回值**：0 表示成功，负值表示失败。

4. **`of_property_read_u8_array`、`of_property_read_u16_array`、`of_property_read_u32_array`、`of_property_read_u64_array` 函数**  
   从属性中读取 `u8`、`u16`、`u32` 或 `u64` 类型的数组数据。  
   **函数原型**：  
   ```c
   int of_property_read_u8_array(const struct device_node *np, const char *propname, u8 *out_values, size_t sz);
   int of_property_read_u16_array(const struct device_node *np, const char *propname, u16 *out_values, size_t sz);
   int of_property_read_u32_array(const struct device_node *np, const char *propname, u32 *out_values, size_t sz);
   int of_property_read_u64_array(const struct device_node *np, const char *propname, u64 *out_values, size_t sz);
   ```
   - `np`：设备节点。  
   - `propname`：属性名称。  
   - `out_values`：返回读取到的数组值。  
   - `sz`：要读取的数组元素数量。  
   - **返回值**：0 表示成功，负值表示失败。

5. **`of_property_read_u8`、`of_property_read_u16`、`of_property_read_u32`、`of_property_read_u64` 函数**  
   读取属性中的单个 `u8`、`u16`、`u32` 或 `u64` 类型数据。  
   **函数原型**：  
   ```c
   int of_property_read_u8(const struct device_node *np, const char *propname, u8 *out_value);
   int of_property_read_u16(const struct device_node *np, const char *propname, u16 *out_value);
   int of_property_read_u32(const struct device_node *np, const char *propname, u32 *out_value);
   int of_property_read_u64(const struct device_node *np, const char *propname, u64 *out_value);
   ```
   - `np`：设备节点。  
   - `propname`：属性名称。  
   - `out_value`：返回读取到的值。  
   - **返回值**：0 表示成功，负值表示失败。

6. **`of_property_read_string` 函数**  
   读取属性中的字符串值。  
   **函数原型**：  
   ```c
   int of_property_read_string(struct device_node *np, const char *propname, const char **out_string);
   ```
   - `np`：设备节点。  
   - `propname`：属性名称。  
   - `out_string`：返回读取到的字符串。  
   - **返回值**：0 表示成功，负值表示失败。

---

#### 其他常用函数

1. **`of_n_addr_cells` 函数**  
   获取节点的 `#address-cells` 属性值。  
   **函数原型**：  
   ```c
   int of_n_addr_cells(struct device_node *np);
   ```
   - `np`：设备节点。  
   - **返回值**：`#address-cells` 属性值。

2. **`of_n_size_cells` 函数**  
   获取节点的 `#size-cells` 属性值。  
   **函数原型**：  
   ```c
   int of_n_size_cells(struct device_node *np);
   ```
   - `np`：设备节点。  
   - **返回值**：`#size-cells` 属性值。

3. **`of_device_is_compatible` 函数**  
   检查节点的 `compatible` 属性是否包含指定的字符串。  
   **函数原型**：  
   ```c
   int of_device_is_compatible(const struct device_node *device, const char *compat);
   ```
   - `device`：设备节点。  
   - `compat`：要检查的字符串。  
   - **返回值**：正数表示包含，0 表示不包含。

4. **`of_get_address` 函数**  
   获取节点的地址相关属性（如 `reg` 或 `assigned-addresses`）。  
   **函数原型**：  
   ```c
   const __be32 *of_get_address(struct device_node *dev, int index, u64 *size, unsigned int *flags);
   ```
   - `dev`：设备节点。  
   - `index`：要读取的地址索引。  
   - `size`：返回地址长度。  
   - `flags`：返回地址标志。  
   - **返回值**：读取到的地址数据首地址，如果为 `NULL` 表示读取失败。

5. **`of_translate_address` 函数**  
   将设备树中的地址转换为物理地址。  
   **函数原型**：  
   ```c
   u64 of_translate_address(struct device_node *dev, const __be32 *in_addr);
   ```
   - `dev`：设备节点。  
   - `in_addr`：要转换的地址。  
   - **返回值**：转换后的物理地址，如果为 `OF_BAD_ADDR` 表示转换失败。

6. **`of_iomap` 函数**  
   将设备树中的地址映射为虚拟地址。  
   **函数原型**：  
   ```c
   void __iomem *of_iomap(struct device_node *np, int index);
   ```
   - `np`：设备节点。  
   - `index`：要映射的地址段（如果 `reg` 属性有多段）。  
   - **返回值**：映射后的虚拟地址，如果为 `NULL` 表示映射失败。



# Reference

关于设备树的前因后果笔者的Reference

> [关于"this whole ARM thing is a f*cking pain in the ass"系列邮件读后感 - 知乎](https://zhuanlan.zhihu.com/p/594992091)
>
> [从Linus Torvalds一封发飙的电邮开始谈设备树究竟是棵什么树？ - 极术社区 - 连接开发者与智能计算生态](https://aijishu.com/a/1060000000156672)
>
> [LKML: Linus Torvalds: Re:omap changes for v2.6.39 merge window](https://lkml.org/lkml/2011/3/17/492)

设备树的文档本身：

[Specifications](https://www.devicetree.org/specifications/)

# Bonus

​	Linus Torvalds的评价：

> 伙计们，整个 ARM 的事情真是太烦人了。
>
> 你们需要停止互相踩脚趾。你对这些疯狂的时钟数据文件的更改不可能不断导致那些恼人的冲突，只是因为不同的 ARM 树中的不同人对一些随机设备进行了一些自慰重命名。说真的。
>
> arch/arm/mach-omap2/usb-musb.c 中的 usb_musb_init() 似乎也完全疯了。我想知道我错过了什么样的疯狂，只是因为我碰巧没有看到合并冲突，只是因为人们很幸运地没有在几行内触碰同一个文件。
>
> 有人需要控制 ARM 社区。我确实想做这些合并，只是为了看看事情有多糟糕，但伙计们，这太荒谬了。如此疯狂的改动本身就很烦人，但当我收到来自四个不同人的“独立”拉取请求，并且他们触及相同的文件时，这表明有些地方出了问题。
>
> 停止疯狂的重命名！就此打住。不要“仅仅因为”而重命名主板和驱动程序，至少在明显存在冲突时不要这么做。这样做毫无意义。我甚至没有谈论文件重命名（这种情况确实发生过，而且当其他人进行其他更改时，尝试解决冲突也会变得“有趣”），而是谈论愚蠢的“更改主板文件中的人性化名称，只是为了惹恼那些需要合并垃圾的人”。
>
> ARM 社区中的某个人真的需要站出来告诉人们不要再胡闹了。
>
> （我正在回复 omap 拉取请求，因为这是我最后做的，但我不知道该“怪罪”谁。我不关心。这真的不重要。我知道 ARM 供应商做了疯狂的事情，还没有弄清楚整个“平台”的事情，但你们需要反击那些给你们发送垃圾的人）。