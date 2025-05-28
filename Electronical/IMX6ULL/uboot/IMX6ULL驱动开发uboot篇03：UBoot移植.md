# IMX6ULL驱动开发uboot篇03：UBoot移植

​	咱们使用的是正点魔改的，这一次我们从NXP原厂商这里开始一步步开始慢慢做移植。

​	我们的第一件事情就是拿到厂商本来的UBoot，然后按照一个经典的姿势准备编译

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_14x14_evk_emmc_defconfig 
make V=1 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j16 
```

​	下一步就是上传到我们的SD卡上，当然咋搞是无所谓的，反正笔者发现imxdownload似乎有点小问题，所以笔者就决定使用mfgtools来解决了。

```
CPU:   Freescale i.MX6ULL rev1.1 69 MHz (running at 396 MHz)
CPU:   Industrial temperature grade (-40C to 105C) at 55C
Reset cause: POR
Board: MX6ULL 14x14 EVK
I2C:   ready
DRAM:  512 MiB
MMC:   FSL_SDHC: 0, FSL_SDHC: 1
*** Warning - bad CRC, using default environment

Display: TFT43AB (480x272)
Video: 480x272x24
In:    serial
Out:   serial
Err:   serial
switch to partitions #0, OK
mmc0 is current device
Net:   Board Net Initialization Failed
No ethernet found.
Normal Boot
Hit any key to stop autoboot:  0 

```

​	作为移植的第一步，是检查自己的根本环境有没有准确。

### 检查MMC列表

​	使用mmc list指令来确保

```
=> mmc list
FSL_SDHC: 0 (SD)
FSL_SDHC: 1
```

​	第一步是切换设备，比如说，我们看看SD卡的驱动是否正常

```
=> mmc dev 0
switch to partitions #0, OK
mmc0 is current device
=> mmc info
Device: FSL_SDHC
Manufacturer ID: 6f
OEM: 303
Name: SDABC 
Tran Speed: 50000000
Rd Block Len: 512
SD version 3.0
High Capacity: Yes
Capacity: 58.2 GiB
Bus Width: 4-bit
Erase Group Size: 512 Bytes
```

​	符合我使用的SD卡信息，我们再换到EMMC里去

```
=> mmc dev 1 
switch to partitions #0, OK
mmc1(part 0) is current device
=> mmc info
Device: FSL_SDHC
Manufacturer ID: 15
OEM: 100
Name: 8GTF4 
Tran Speed: 52000000
Rd Block Len: 512
MMC version 4.0
High Capacity: Yes
Capacity: 7.3 GiB
Bus Width: 8-bit
Erase Group Size: 512 KiB
```

​	OK，这里说明EMMC驱动也是正常的（笔者的板子是8GB的EMMC）

### 检查显示设备

​	笔者的显示设备是LCD显示屏，令人伤心的是——显然不太多，笔者上面出现了重复的NXP。这是因为样例的板子跟我们正点的板子不是一样的。所以这个需要更改。

### 检查网络

​	正点原子开发板的网络芯片复位引脚和 NXP 官方开发板不一样，果然我们看到输出的信息中，他就说明网络的初始化是失败的。

​	所以我们需要做的就是修改这些内容：LCD和网络

## 开始我们的移植征程

### 复制一份默认配置，修改内容

​	我们复制一份我们正在使用的默认配置

```
cd configs 
cp mx6ull_14x14_evk_emmc_defconfig mx6ull_charliechen_emmc_config
```

​	做一点小修改，实际上就是指向的文件夹需要改一下

```
CONFIG_SYS_EXTRA_OPTIONS="IMX_CONFIG=board/freescale/mx6ull_charliechen_emmc/imximage.cfg,MX6ULL_EVK_EMMC_REWORK"
CONFIG_ARM=y
CONFIG_ARCH_MX6=y
CONFIG_TARGET_MX6ULL_CHARLIECHEN_EMMC=y
CONFIG_CMD_GPIO=y
```

### 复制一份config文件

​	下一步就是修改config.h文件，回到项目的根目录下

```
cp include/configs/mx6ullevk.h include/configs/mx6ull_charliechen_emmc.h
```

​	然后记得修改防止重定义的宏。

### 复制一份板级文件夹并做修改

```
cd board/freescale/ 
cp mx6ullevk/ -r mx6ull_charliechen_emmc
```

​	注意的是要修改指向你自己配置文件的那一个，不然到时候找不到。

#### 修改Makefile

​	下一步我们找Makefile，然后需要注意的是，我们修改一下mx6ullevk.c的名称，笔者改成了：mx6ull_charliechen_emmc.c，然后就是修改makefile，不然找不到目标Makefile报错。

```
# (C) Copyright 2015 Freescale Semiconductor, Inc.
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-y  := mx6ull_charliechen_emmc.o

extra-$(CONFIG_USE_PLUGIN) :=  plugin.bin
$(obj)/plugin.bin: $(obj)/plugin.o
	$(OBJCOPY) -O binary --gap-fill 0xff $< $@
```

#### 修改imximage.cfg文件

​	修改plugin指向的位置

```
PLUGIN	board/freescale/board/freescale/mx6ull_charliechen_emmc/plugin.bin 0x00907000
```

#### 修改Kconfig文件

​	修改一下Kconfig文件。

```
if TARGET_MX6ULL_CHARLIECHEN_EMMC

config SYS_BOARD
	default "mx6ull_charliechen_emmc"

config SYS_VENDOR
	default "freescale"

config SYS_SOC
	default "mx6

config SYS_CONFIG_NAME
	default "mx6ull_charliechen_emmc"

endif

```

#### 修改MAINTAINERS文件

​	也就是添加是何种SOC，以及板子的配置，名称。

```
MX6ULLEVK BOARD
M:	Peng Fan <peng.fan@nxp.com>
S:	Maintained
F:	board/freescale/mx6ull_charliechen_emmc/
F:	include/configs/mx6ull_charliechen_emmc.h
```

#### 修改U-Boot图形化文件

​	在原先的9x9_EVK后面呢，我们添加一个

```
config TARGET_MX6ULL_CHARLIECHEN_EMMC
	bool "Support mx6ull_charliechen_emmc"
	select MX6ULL
	select DM
	select DM_THERMAL
```

​	然后再最后一行添加

```
source "board/freescale/mx6ull_charliechen_emmc/Kconfig"
```

## 下一步，修改LCD驱动

​	我们下一步，就是修改LCD参数的部分，就在我们那个唯一的C文件当中，在文件的第780行。我们需要修改一些参数：笔者使用的LCD是4.3寸的，正点中已经填好了参数吗

```
       {
        .bus = MX6UL_LCDIF1_BASE_ADDR,
        .addr = 0,
        .pixfmt = 24,
        .detect = NULL,
        .enable = do_enable_parallel_lcd,
        .mode   = {
                .name           = "ATK4384",
                .xres           = 800,
                .yres           = 480,
                .pixclock       = 10119,
                .left_margin    = 210,
                .right_margin   = 46,
                .upper_margin   = 22,
                .lower_margin   = 23,
                .hsync_len      = 20,
                .vsync_len      = 3,
                .sync           = 0,
                .vmode          = FB_VMODE_NONINTERLACED
               }
       }
```

​	我们修改好之后，就可以先移植到我们的板子上看看现象。上电之后发现屏幕是挂的，注意，我们需要修改一下panel参数：ATK4384，然后保存，之后掉电重启一下。就会发现背光亮了。说明驱动成功。

## 网络驱动



​	我们来到mx6ull_charliechen_emmc.h文件，按照预期，我们是需要修改：

- 修改ENET1 网络 PHY 的地址。 
- 修改ENET2 网络 PHY 的地址。 
- 使能REALTEK 公司的 PHY 驱动。 

​	但是，由于我们开发板上 SR8201F 的 PHY 地址和默认的配置一样，因此只需要是使能REALTEK 公司的 PHY 驱动，大家如果使用的其他品牌的开发板，那么就要根据实际情况来修 改对应的 ENET1 和ENET2 网络 PHY 地址。 

​	下一步，就是修改驱动代码了：删除 uboot 中74LV595 的驱动代码 

​	IOX 开头的宏定义是 74LV595 的相关 GPIO，因为 NXP 官方 I.MX6ULL EVK 开发板使用74LV595 来扩展 IO，两个网络的复位引脚就是由 74LV595 来控制 的。正点原子的I.MX6U-ALPHA 开发板并没有使用 74LV595，所以需要修改：

​	将

```
#define IOX_SDI IMX_GPIO_NR(5, 10) 
#define IOX_STCP  IMX_GPIO_NR(5, 7) 
#define IOX_SHCP  IMX_GPIO_NR(5, 11) 
#define IOX_OE IMX_GPIO_NR(5, 8)
```

​	改成：

```
#define ENET1_RESET IMX_GPIO_NR(5, 7) 
#define ENET2_RESET IMX_GPIO_NR(5, 8)
```

​	我们删除跟74LV595相关的代码

```
static iomux_v3_cfg_t const iox_pads[] = { 
    /* IOX_SDI */ 
    MX6_PAD_BOOT_MODE0__GPIO5_IO10 | MUX_PAD_CTRL(NO_PAD_CTRL), 
    /* IOX_SHCP */ 
    MX6_PAD_BOOT_MODE1__GPIO5_IO11 | MUX_PAD_CTRL(NO_PAD_CTRL), 
    /* IOX_STCP */ 
    MX6_PAD_SNVS_TAMPER7__GPIO5_IO07 | MUX_PAD_CTRL(NO_PAD_CTRL), 
    /* IOX_nOE */ 
    MX6_PAD_SNVS_TAMPER8__GPIO5_IO08 | MUX_PAD_CTRL(NO_PAD_CTRL), 
}; 

...
static void iox74lv_init(void) 
{ 
    int i; 
  	gpio_direction_output(IOX_OE, 0); 
 
    for (i = 7; i >= 0; i--) { 
        gpio_direction_output(IOX_SHCP, 0); 
        gpio_direction_output(IOX_SDI, seq[qn_output[i]][0]); 
        udelay(500); 
        gpio_direction_output(IOX_SHCP, 1); 
        udelay(500); 
    } 
 
    ...... 
    /* 
     * shift register will be output to pins 
     */ 
    gpio_direction_output(IOX_STCP, 1); 
}; 
 
void iox74lv_set(int index) 
{ 
    int i; 
 
    for (i = 7; i >= 0; i--) { 
        gpio_direction_output(IOX_SHCP, 0); 
 
        if (i == index) 
            gpio_direction_output(IOX_SDI, seq[qn_output[i]][0]); 
        else 
            gpio_direction_output(IOX_SDI, seq[qn_output[i]][1]); 
        udelay(500); 
        gpio_direction_output(IOX_SHCP, 1); 
        udelay(500); 
    } 
    ...... 
    /* 
      * shift register will be output to pins 
      */ 
    gpio_direction_output(IOX_STCP, 1); 
};   
```

​	全部删掉

​	然后

```
int board_init(void) 
{ 
	...... 
	// imx_iomux_v3_setup_multiple_pads(iox_pads, ARRAY_SIZE(iox_pads));  
    // iox74lv_init(); 
    ...... 
    return 0; 
} 
```

​	注释掉这两句话。

​	下一步，我们在mx6ull_charliechen_emmc.c找到fec1_pads，一个iomux_v3_cfg_t结构体数组

```
/*
 * pin conflicts for fec1 and fec2, GPIO1_IO06 and GPIO1_IO07 can only
 * be used for ENET1 or ENET2, cannot be used for both.
 */
static iomux_v3_cfg_t const fec1_pads[] = {
	MX6_PAD_GPIO1_IO06__ENET1_MDIO | MUX_PAD_CTRL(MDIO_PAD_CTRL),
	MX6_PAD_GPIO1_IO07__ENET1_MDC | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_TX_DATA0__ENET1_TDATA00 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_TX_DATA1__ENET1_TDATA01 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_TX_EN__ENET1_TX_EN | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_TX_CLK__ENET1_REF_CLK1 | MUX_PAD_CTRL(ENET_CLK_PAD_CTRL),
	MX6_PAD_ENET1_RX_DATA0__ENET1_RDATA00 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_RX_DATA1__ENET1_RDATA01 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_RX_ER__ENET1_RX_ER | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_RX_EN__ENET1_RX_EN | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_SNVS_TAMPER7__GPIO5_IO07 | MUX_PAD_CTRL(NO_PAD_CTRL),
};

static iomux_v3_cfg_t const fec2_pads[] = {
	MX6_PAD_GPIO1_IO06__ENET2_MDIO | MUX_PAD_CTRL(MDIO_PAD_CTRL),
	MX6_PAD_GPIO1_IO07__ENET2_MDC | MUX_PAD_CTRL(ENET_PAD_CTRL),

	MX6_PAD_ENET2_TX_DATA0__ENET2_TDATA00 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET2_TX_DATA1__ENET2_TDATA01 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET2_TX_CLK__ENET2_REF_CLK2 | MUX_PAD_CTRL(ENET_CLK_PAD_CTRL),
	MX6_PAD_ENET2_TX_EN__ENET2_TX_EN | MUX_PAD_CTRL(ENET_PAD_CTRL),

	MX6_PAD_ENET2_RX_DATA0__ENET2_RDATA00 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET2_RX_DATA1__ENET2_RDATA01 | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET2_RX_EN__ENET2_RX_EN | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET2_RX_ER__ENET2_RX_ER | MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_SNVS_TAMPER8__GPIO5_IO08 | MUX_PAD_CTRL(NO_PAD_CTRL),
};

```

​	注意两个结构体的尾端，都添加上了GPIO的初始化。然后在：setup_iomux_fec中添加一部分复位代码

```
static void setup_iomux_fec(int fec_id)
{
	if (fec_id == 0) 
	{
		imx_iomux_v3_setup_multiple_pads(fec1_pads, ARRAY_SIZE(fec1_pads));
		gpio_direction_output(ENET1_RESET, 1); 
		gpio_set_value(ENET1_RESET, 0);
		mdelay(20);
		gpio_set_value(ENET1_RESET, 1);
	}
	else
	{
		imx_iomux_v3_setup_multiple_pads(fec2_pads, 
			                         ARRAY_SIZE(fec2_pads)); 
		gpio_direction_output(ENET2_RESET, 1); 
		gpio_set_value(ENET2_RESET, 0); 
		mdelay(20); 
		gpio_set_value(ENET2_RESET, 1); 
	}
	mdelay(150);
}
```

​	改完了，看看效果，我们还是老样子，看看日志：

```
U-Boot 2016.03 (Mar 07 2025 - 00:13:11 -0800)

CPU:   Freescale i.MX6ULL rev1.1 69 MHz (running at 396 MHz)
CPU:   Industrial temperature grade (-40C to 105C) at 53C
Reset cause: POR
Board: MX6ULL 14x14 EVK
I2C:   ready
DRAM:  512 MiB
MMC:   FSL_SDHC: 0, FSL_SDHC: 1
Display: ATK4384 (800x480)
Video: 800x480x24
In:    serial
Out:   serial
Err:   serial
switch to partitions #0, OK
mmc0 is current device
Net:   FEC1
Error: FEC1 address not set.
```

​	认出来我们的网卡啦！我们修改，保存一下配置：

```
setenv ethaddr b8:ae:1d:01:00:00 
setenv gatewayip 192.168.137.1
setenv netmask 255.255.255.0
setenv ipaddr 192.168.137.4
saveenv
```

​	真令人激动：

```
=> ping 192.168.137.10
Using FEC1 device
host 192.168.137.10 is alive
=> ping 192.168.137.1 
Using FEC1 device
host 192.168.137.1 is alive
```

​	到此为止，网络也移植成功了。我们测试一下加载内核：

```
setenv serverip 192.168.137.10
saveenv
tftp 80800000 zImage
Using FEC1 device
TFTP from server 192.168.137.10; our IP address is 192.168.137.4
Filename 'zImage'.
Load address: 0x80800000
Loading: #################################################################
	 #################################################################
	 #################################################################
	 ...
```

​	我们加载一下环境变量

```
setenv bootargs 'console=ttymxc0,115200 root=/dev/mmcblk1p2 rootwait rw'
setenv bootcmd 'tftp 80800000 zImage; tftp 83000000 imx6ull-14x14-emmc-7-800x480-c.dtb; bootz 80800000 - 83000000' 
```

​	完事！