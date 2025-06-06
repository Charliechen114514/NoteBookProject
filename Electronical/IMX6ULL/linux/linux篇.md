# IMX6ULL驱动开发Linux篇01

## 准备好编译Linux吧！

​	我们之前玩过UBoot，引导过正点原子搞好了的Linux，现在，我们尝试自己来配置一个从NXP厂商到正点原子开发板的Linux内核

​	拿到NXP的4.1.15的内核，第一件事情就是老样子配置（先试着跑一下，所以，咱们啥也不改）

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean 
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- imx_v7_mfg_defconfig 
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- all -j16
```

​	这一套组合小连招咱们已经非常熟悉了，等到编译完成之后，我们要做的事情就是将我们的zImage（arch/arm/boot）和设备树文件imx6ull-14x14-evk-emmc.dtb（arch/arm/boot/imx6ull-14x14-evk-emmc.dtb）拷贝到tftp目录下。然后修改我们的bootcmd为：

```
tftp 80800000 zImage; tftp 83000000 imx6ull-14x14-evk-emmc.dtb; bootz 80800000 - 83000000
```

> 当然，如果你是一套环境坐下来，为了彻底模拟环境，还需要我们做一个事情就是将bootargs清空，不然的话，内核启动直接就会找存储在EMMC中的设备树文件启动跑路了，这个不是我们预期的效果

​	下一步就是单走一个boot

```
Starting kernel ...

Booting Linux on physical CPU 0x0
Linux version 4.1.15 (charliechen@ubuntu) (gcc version 4.9.4 (Linaro GCC 4.9-2017.01) ) #1 SMP PREEMPT Sat Mar 8 15:10:46 PST 2025
...
Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(0,0)
---[ end Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(0,0)
random: nonblocking pool is initialized
```

​	啊哈，咱们没有根文件系统。但是不着急，我们先制作一份基于我们自己板子的开发板先。

## 所以，如何制作自己的板子的config呢？

​	当然，如果我们运气炸裂，最后配置上根文件系统可以一发入魂，但是这个往往是做不到的，我们经常都需要自己做一些更改。

​	步骤说起来，基本上就是两个步骤：

- 我们需要有自己的defconfig文件
- 和一个设备树文件dts，来描述自己的板子上有什么外设

啥，自己从头手写，错误的，直接找最相近的cv开改就完事了，下面跟上我的步伐：

### 修改defconfig文件

​	笔者后续可能会使用SD卡传递到板子上，我们的NXP官方有根据自己家的烧录做过mfgtools文件，自然，我们有一个相应的适配文件imx_v7_mfg_defconfig，所以魔改这个，当然，imx_v7_defconfig也是可以的，就是没办法扔到mfgtools搞烧写了。

```bash
charliechen@ubuntu:~/linux_code_src/nxp/arch/arm/configs$ cp imx_v7_mfg_defconfig imx6ull_charliechen_defconfig
charliechen@ubuntu:~/linux_code_src/nxp/arch/arm/configs$ ls *charliechen*
imx6ull_charliechen_defconfig
```

​	OK，到这里还是啥也不改。下一步，我们就是处理设备树的事情，这个事情，看自己的板子（型号啊外设啊，不同的dts基本上是师承的一个根dts），我是复制了imx6ull-14x14-evk.dts这个文件，当然是在arch/arm/boot/dts文件之下。

```
charliechen@ubuntu:~/linux_code_src/nxp/arch/arm/boot/dts$ cp imx6ull-14x14-evk.dts imx6ull-14x14-charliechen-emmc.dts
```

​	还有一个事情，修改Makefile（arch/arm/boot/dts下的Makefile文件），添加设备树文件进去，不然找不到的，在CONFIG_SOC_IMX6ULL那个地方，我们添加上自己的设备树文件，但是注意是dtb文件，因为这是编译的目标

```
	imx6ull-14x14-charliechen-emmc.dtb \
```

​	下一步，我们清理一下工程，之后

```
charliechen@ubuntu:~/linux_code_src/nxp$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- imx_charliechen_defconfig
  HOSTCC  scripts/basic/fixdep
  HOSTCC  scripts/kconfig/conf.o
  SHIPPED scripts/kconfig/zconf.tab.c
  SHIPPED scripts/kconfig/zconf.lex.c
  SHIPPED scripts/kconfig/zconf.hash.c
  HOSTCC  scripts/kconfig/zconf.tab.o
  HOSTLD  scripts/kconfig/conf
#
# configuration written to .config
#
```

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- all -j16
```

​	过一会就完事了，之后上传到板子上，记得更改bootcmd中dtb文件的名称，不然tftp找不到没法子了。

​	启动之后，可能会出现找不到设备树信息的问题，这里注意，如果你的板子先前烧到板子EMMC上整个uboot + linux + dtb的话，是可以启动的，因为EMMC的第二分区的确存放了我们的根文件系统，如果没有，那么，我们就必须改一下我们的dts文件，不然，稍后的bootargs就会没有起到作用。

```
&usdhc2 {
	pinctrl-names = "default", "state_100mhz", "state_200mhz";
	pinctrl-0 = <&pinctrl_usdhc2_8bit>;
	pinctrl-1 = <&pinctrl_usdhc2_8bit_100mhz>;
	pinctrl-2 = <&pinctrl_usdhc2_8bit_200mhz>;
	bus-width = <8>;
	non-removable;
	status = "okay";
};
```

​	把最后的usdhc2复制一份NXP中对EMMC设备特化的结果，结果肯定是可以启动成功的。

### 修改CPU的主频调度策略

​	启动成功之后，下一步，我们要做的事情是修改一下CPU的一些策略，关于策略问题，可以参考其他博客，笔者之后可能会写博客来进行介绍，但不是这里

​	我们

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
```

​	就会出现下面这样的图（笔者把光标移动到了CPU Power Management上了）

![image-20250309085245819](./linux篇/image-20250309085245819.png)

​	之后我们一路

```
CPU Power Management 
 -> CPU Frequency scaling 
 -> Default CPUFreq governor 
```

​	默认的情况下选择的是performance，意味着我们的CPU会一直按照最大的可允许功率运行，我们修改成ondemand，咱们还是按需求来，别让CPU这么幸苦。

![image-20250309090113838](./linux篇/image-20250309090113838.png)

​	之后就退出保存，我们重新编译生效

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- all -j16
```

​	上传上去，效果显著（看MIPS，也就是每百万条指令执行花费的秒数）

```
root@ATK-IMX6U:~# cat /proc/cpuinfo
processor	: 0
model name	: ARMv7 Processor rev 5 (v7l)
BogoMIPS	: 6.00
Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xc07
CPU revision	: 5

Hardware	: Freescale i.MX6 Ultralite (Device Tree)
Revision	: 0000
Serial		: 0000000000000000

```

​	这是之前CPU的参数

```
root@ATK-IMX6U:~# cat /proc/cpuinfo
processor	: 0
model name	: ARMv7 Processor rev 5 (v7l)
BogoMIPS	: 12.00
Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xc07
CPU revision	: 5

Hardware	: Freescale i.MX6 Ultralite (Device Tree)
Revision	: 0000
Serial		: 0000000000000000

```

### 调通网络驱动

```
		pinctrl_spi4: spi4grp {
                        fsl,pins = <
                                MX6ULL_PAD_BOOT_MODE0__GPIO5_IO10        0x70a1
                                MX6ULL_PAD_BOOT_MODE1__GPIO5_IO11        0x70a1
                                MX6ULL_PAD_SNVS_TAMPER7__GPIO5_IO07      0x70a1
                                MX6ULL_PAD_SNVS_TAMPER8__GPIO5_IO08      0x80000000
                        >;
                };
```

​	我们需要删除掉SNVS_TAMPER7 和 SNVS_TAMPER8这两个引脚。

```
	spi4 {
		compatible = "spi-gpio";
		pinctrl-names = "default";
		pinctrl-0 = <&pinctrl_spi4>;
		status = "okay";
		gpio-sck = <&gpio5 11 0>;
		gpio-mosi = <&gpio5 10 0>;
		num-chipselects = <1>;
		#address-cells = <1>;
		#size-cells = <0>;
```

​	下一步是在上面的spi4中，删除129行的pinctrl-assert-gpios和133行的cs-gpios = <&gpio5 7 0>; 

​	我们之后需要添加给iomuxc_snvs下面两个引脚信息

```
				pinctrl_enet1_reset: enet1resetgrp {
					fsl,pins = <
						MX6ULL_PAD_SNVS_TAMPER7__GPIO5_IO07		0x10B0
					>;
				};

				pinctrl_enet2_reset: enet2resetgrp {
					fsl,pins = <
						MX6ULL_PAD_SNVS_TAMPER8__GPIO5_IO08		0x10B0
					>;
```

​	最后看起来是这样的：

```
&iomuxc_snvs {
		pinctrl-names = "default_snvs";
        pinctrl-0 = <&pinctrl_hog_2>;
        imx6ul-evk 
		{
				pinctrl_hog_2: hoggrp-2 {
                        fsl,pins = <
                                MX6ULL_PAD_SNVS_TAMPER0__GPIO5_IO00      0x80000000
                        >;
                };

				pinctrl_dvfs: dvfsgrp {
                        fsl,pins = <
                                MX6ULL_PAD_SNVS_TAMPER3__GPIO5_IO03      0x79
                        >;
                };
		
				pinctrl_lcdif_reset: lcdifresetgrp {
                        fsl,pins = <
                                /* used for lcd reset */
                                MX6ULL_PAD_SNVS_TAMPER9__GPIO5_IO09  0x79
                        >;
                };

				pinctrl_spi4: spi4grp {
                        fsl,pins = <
                                MX6ULL_PAD_BOOT_MODE0__GPIO5_IO10        0x70a1
                                MX6ULL_PAD_BOOT_MODE1__GPIO5_IO11        0x70a1
                    	>;
                };

            	pinctrl_sai2_hp_det_b: sai2_hp_det_grp {
                        fsl,pins = <
                                MX6ULL_PAD_SNVS_TAMPER4__GPIO5_IO04   0x17059
                        >;
				};
				
				pinctrl_enet1_reset: enet1resetgrp {
					fsl,pins = <
						MX6ULL_PAD_SNVS_TAMPER7__GPIO5_IO07		0x10B0
					>;
				};

				pinctrl_enet2_reset: enet2resetgrp {
					fsl,pins = <
						MX6ULL_PAD_SNVS_TAMPER8__GPIO5_IO08		0x10B0
					>;
				};	
        };
};
```

​	检查一下enet1grp的默认值：

```
		pinctrl_enet1: enet1grp {
			fsl,pins = <
				MX6UL_PAD_ENET1_RX_EN__ENET1_RX_EN	0x1b0b0
				MX6UL_PAD_ENET1_RX_ER__ENET1_RX_ER	0x1b0b0
				MX6UL_PAD_ENET1_RX_DATA0__ENET1_RDATA00	0x1b0b0
				MX6UL_PAD_ENET1_RX_DATA1__ENET1_RDATA01	0x1b0b0
				MX6UL_PAD_ENET1_TX_EN__ENET1_TX_EN	0x1b0b0
				MX6UL_PAD_ENET1_TX_DATA0__ENET1_TDATA00	0x1b0b0
				MX6UL_PAD_ENET1_TX_DATA1__ENET1_TDATA01	0x1b0b0
				MX6UL_PAD_ENET1_TX_CLK__ENET1_REF_CLK1	0x4001b031
			>;
		};

		pinctrl_enet2: enet2grp {
			fsl,pins = <
				MX6UL_PAD_GPIO1_IO07__ENET2_MDC		0x1b0b0
				MX6UL_PAD_GPIO1_IO06__ENET2_MDIO	0x1b0b0
				MX6UL_PAD_ENET2_RX_EN__ENET2_RX_EN	0x1b0b0
				MX6UL_PAD_ENET2_RX_ER__ENET2_RX_ER	0x1b0b0
				MX6UL_PAD_ENET2_RX_DATA0__ENET2_RDATA00	0x1b0b0
				MX6UL_PAD_ENET2_RX_DATA1__ENET2_RDATA01	0x1b0b0
				MX6UL_PAD_ENET2_TX_EN__ENET2_TX_EN	0x1b0b0
				MX6UL_PAD_ENET2_TX_DATA0__ENET2_TDATA00	0x1b0b0
				MX6UL_PAD_ENET2_TX_DATA1__ENET2_TDATA01	0x1b0b0
				MX6UL_PAD_ENET2_TX_CLK__ENET2_REF_CLK2	0x4001b031
			>;
		};
```

​	看看最后的值是不是0x4001b031，一般是的，就不用改，不是改成这个。

```
&fec1 {
	pinctrl-names = "default";
	pinctrl-0 = <&pinctrl_enet1
				 &pinctrl_enet1_reset>;
	phy-mode = "rmii";
	phy-handle = <&ethphy0>;
	status = "okay";
};

&fec2 {
	pinctrl-names = "default";
	pinctrl-0 = <&pinctrl_enet2
				 &pinctrl_enet2_reset>;
```

​	依次对fec1和fec2，修改pinctrl-0加入pinctrl_enet1_reset,之后再添加下面的这些信息

```
&fec1 {
	pinctrl-names = "default";
	pinctrl-0 = <&pinctrl_enet1
				 &pinctrl_enet1_reset>;
	phy-mode = "rmii";
	phy-handle = <&ethphy0>;
	phy-reset-gpios = <&gpio5 7 GPIO_ACTIVE_LOW>;
	phy-reset-duration = <200>;
	status = "okay";
};

&fec2 {
	pinctrl-names = "default";
	pinctrl-0 = <&pinctrl_enet2
				 &pinctrl_enet2_reset>;
	phy-mode = "rmii";
	phy-handle = <&ethphy1>;
	phy-reset-gpios = <&gpio5 8 GPIO_ACTIVE_LOW>;
	phy-reset-duration = <200>;
	status = "okay";

	mdio {
		#address-cells = <1>;
		#size-cells = <0>;

		ethphy0: ethernet-phy@2 {
			compatible = "ethernet-phy-ieee802.3-c22";
			smsc,disable-energy-detect;
			reg = <2>;
		};

		ethphy1: ethernet-phy@1 {
			compatible = "ethernet-phy-ieee802.3-c22";
			smsc,disable-energy-detect;
			reg = <1>;
		};
	};
};
```

​	最后，我们要做的是——修改一下drivers/net/ethernet/freescale/fec_main.c

```c
static void fec_reset_phy(struct platform_device *pdev)
{
	int err, phy_reset;
	int msec = 1;
	struct device_node *np = pdev->dev.of_node;

	if (!np)
		return;

	err = of_property_read_u32(np, "phy-reset-duration", &msec);
	/* A sane reset duration should not be longer than 1s */
	if (!err && msec > 1000)
		msec = 1;

	phy_reset = of_get_named_gpio(np, "phy-reset-gpios", 0);
	if (!gpio_is_valid(phy_reset))
		return;

	err = devm_gpio_request_one(&pdev->dev, phy_reset,
				    GPIOF_OUT_INIT_LOW, "phy-reset");
	if (err) {
		dev_err(&pdev->dev, "failed to get phy-reset-gpios: %d\n", err);
		return;
	}
	msleep(msec);
	gpio_set_value(phy_reset, 1);
	msleep(200);
}
```

​	在代码的末尾修改一下，添加一个延时，这是要求的，网卡要求启动后150ms才可用。

​	在笔者使用的这个版本下的Linux会自动开启eth0，也就是我们的主网卡

```
root@ATK-IMX6U:~# ifconfig eth0 192.168.137.5
```

​	我们配置一下我们的IP，然后做的事情就是测试一下可不可以连到我们的板子上

```
root@ATK-IMX6U:~# ping 192.168.137.10
PING 192.168.137.10 (192.168.137.10) 56(84) bytes of data.
64 bytes from 192.168.137.10: icmp_seq=1 ttl=64 time=2.46 ms
64 bytes from 192.168.137.10: icmp_seq=2 ttl=64 time=1.33 ms
64 bytes from 192.168.137.10: icmp_seq=3 ttl=64 time=1.04 ms
64 bytes from 192.168.137.10: icmp_seq=4 ttl=64 time=0.762 ms
```

​	完事了