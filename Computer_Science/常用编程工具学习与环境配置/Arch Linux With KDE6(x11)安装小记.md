>

# 虚拟机Arch Linux With KDE6(x11)安装小记

## 写在前言

​	此篇博客记载了笔者安装ArchLinux的基础步骤和安装教程，供各位看官参考和评判。

​	环境：Windows11下的VMWare虚拟机安装2024年3月初发行的Linux 6.8.1Kernel，安装的固件类型是**UEFI安装**而不是BIOS安装

​	配置导向：

> 分区简单：UEFI分区（300M） + Swap(4G) + FileSystem(Btrfs)(75.6G)

## Base

### I. 开始

​	在安装结束VMWare虚拟机之后，诸位如果想要下载Arch Linux ISO，可以前往：

> [`Arch Linux - Downloads`](https://archlinux.org/download/)
>
> 下的中国源：
>
> - [`aliyun.com`](https://mirrors.aliyun.com/archlinux/iso/2024.03.01/)
> - ...
>
> 进行下载

​	下载结束之后，记住自己存放的ISO的位置，随后打开VMWare WorkStation，走过一次典型的虚拟机安装教程。这里给出笔者的配置：

![image-20240319194216766](./Arch Linux With KDE6(x11)安装小记/image-20240319194216766.png)

​	值得注意的是，请务必保证自己的内存不要小于1GB，否则Arch Linux Installer将会无法装进内存导致无法安装！

​	**请设置我们的开机方式为UEFI而不是BIOS!当然想要查询BIOS方式也有专门的博客进行介绍**

​	我们的第一步就是禁用refleactor服务（它会自己更新 `mirrorlist`（软件包管理器 `pacman` 的软件源）），因为一些原因，他可能会误删我们手动配置好的国内源！（但是笔者的三次安装中两次我没有禁，事实上没有什么太大的影响，不过，如果发现下载速度过慢了还是禁掉！然后手动配置国内源）

```
systemctl stop reflector.service
```

​	Systemd是一个系统管理守护进程、工具和库的集合，可以简单的认为：他就是我们系统守护进程的管理器。

![img](./Arch Linux With KDE6(x11)安装小记/bg2016030703.png)

```
# 立即启动一个服务
$ sudo systemctl start apache.service
# 立即停止一个服务
$ sudo systemctl stop apache.service
# 设置服务开机自启动
$ sudo systemctl enable some.service
# 重启一个服务
$ sudo systemctl restart apache.service
# 杀死一个服务的所有子进程
$ sudo systemctl kill apache.service
# 重新加载一个服务的配置文件
$ sudo systemctl reload apache.service
# 重载所有修改过的配置文件
$ sudo systemctl daemon-reload
# 显示某个 Unit 的所有底层参数
$ systemctl show httpd.service
# 显示某个 Unit 的指定属性的值
$ systemctl show -p CPUShares httpd.service
# 设置某个 Unit 的指定属性
$ sudo systemctl set-property httpd.service CPUShares=500
```

​	如你所见，这些指令在我们的配置路途上将会常常遇到。我们这里就是设置reflector服务程序暂停。

​	良好的习惯是：看我们的服务有没有真正暂停，确保我们这一步正确

```
systemctl status reflector.service
```

​	预期的讲：status应该是failed的！

### II. 网络

​	下一步，我们再三的确认我们的启动方式是UEFI方式，很简单：

```
ls /sys/firmware/efi/efivars
```

​	在这里，如果你的shell可以自动补全上述的路径，实际上就是说明我们的确是UEFI方式启动。输出一下

![image-20240319122704119](./Arch Linux With KDE6(x11)安装小记/image-20240319122704119.png)

​	下一步，就是连接网络，对于虚拟机，我们无需关心，只需要确认我们的桥接或者是NAT方式的连接使得虚拟机可以利用主机的网络配置向外交互就行：

```
ping baidu.com # PING一下看看
```

​	![image-20240319123856904](./Arch Linux With KDE6(x11)安装小记/image-20240319123856904.png)

​	ping不同，可以首先尝试重启虚拟机，或者检查一下在主机上的VMWare网络服务是否开启，没有开启开一下（这里不再赘述如何打开服务了，抛hostname无法解析可能是DNS配置出现问题）

### III.开启NTP时钟校验

​	大部分软件可能对事件敏感，这里启动一下ntp时钟校验

```
timedatectl set-ntp true
```

> timedatectl也是systemd的一个子集指令集

```
timedatectl status 
```

![image-20240319124014490](./Arch Linux With KDE6(x11)安装小记/image-20240319124014490.png)

### IV. 设置国内源

​	使用 `vim` 编辑器修改 `/etc/pacman.d/mirrorlist` 文件。将 `pacman` 软件仓库源更换为国内软件仓库镜像源：

```
vim /etc/pacman.d/mirrorlist
```

​	一些常见的国内源

```
Server = https://mirrors.ustc.edu.cn/archlinux/$repo/os/$arch # 中国科学技术大学开源镜像站
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch # 清华大学开源软件镜像站
```

![image-20240319124141856](./Arch Linux With KDE6(x11)安装小记/image-20240319124141856.png)

> 使用Vim：摁一下 `i` 进入输入模式，输入结束之后ESC键摁一下回到命令行模式，输入 `:wq` 表示`write and quit`

### V. 配置分区与文件系统

​	下一步就是查看一下文件块的信息如何了：

![image-20240319124204765](./Arch Linux With KDE6(x11)安装小记/image-20240319124204765.png)

​	可以看到我们的sda0就是我们的目标硬盘，对他分区！

```
cfdisk /dev/sda
```

​	对了，一些博主喜欢使用fdisk干分区，我的评价是：喜欢命令行就那样做，担心出错就这个。

​	选择gpt分区后，开始分区。

> 选择Free Space之后，光标会提示你输入大小：只需要数字 + 单位即可，然后分完之后光标切到type处选择对应的type就行

具体如何分，笔者的配置是如下的：

> sda1 : EFI System	300M
>
> sda2：Linux Swap	4G
>
> sda3：Linux filesystem 75.7G

![image-20240319124300888](./Arch Linux With KDE6(x11)安装小记/image-20240319124300888.png)

​	分完长上面那样，然后光标选中write后提示你输入yes表示确认，随后quit处出cfdisk

​	我们使用fdisk确认我们的分区：

![image-20240319124423859](./Arch Linux With KDE6(x11)安装小记/image-20240319124423859.png)

​	很好！

​	下一步就是格式化各个文件块：

> 使用FAT32格式格式化EFI引导
>
> ```
> mkfs.fat -F32 /dev/sda1
> ```
>
> 使用swap格式格式化swap分区
>
> ```
> mkswap /dev/sda2
> ```
>
> 我们这次选用的是较新的btrfs文件系统格式化剩下的硬盘
>
> ```
> mkfs.btrfs -L ArchLinux /dev/sda3
> ```
>
> - `-L` 选项后指定该分区的 `LABLE`，这里以 `ArchLinux` 为例，也可以自定义，但不能使用特殊字符以及空格，且最好有意义

![image-20240319124557960](./Arch Linux With KDE6(x11)安装小记/image-20240319124557960.png)

```
btrfs的特性：
首先是扩展性 (scalability) 相关的特性，btrfs 最重要的设计目标是应对大型机器对文件系统的扩展性要求。 Extent，B-Tree 和动态 inode 创建等特性保证了 btrfs 在大型机器上仍有卓越的表现，其整体性能而不会随着系统容量的增加而降低。

其次是数据一致性 (data integrity) 相关的特性。系统面临不可预料的硬件故障，Btrfs 采用 COW 事务技术来保证文件系统的一致性。 btrfs 还支持 checksum，避免了 silent corrupt 的出现。而传统文件系统则无法做到这一点。

第三是和多设备管理相关的特性。 Btrfs 支持创建快照 (snapshot)，和克隆 (clone) 。 btrfs 还能够方便的管理多个物理设备，使得传统的卷管理软件变得多余。

最后是其他难以归类的特性。这些特性都是比较先进的技术，能够显著提高文件系统的时间 / 空间性能，包括延迟分配，小文件的存储优化，目录索引等。
```

> 一些ref:
>
> [Linux 文件系统的未来 btrfs - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/61407714)
>
> [Btrfs 与 Ext4 - 功能、优势和劣势_btrfs和ext4-CSDN博客](https://blog.csdn.net/taoxicun/article/details/122878090)

​	下一步就是创建子卷：创建之前，我们需要挂载一下分区：

```
mount -t btrfs -o compress=zstd /dev/sda3 /mnt
```

![image-20240319124700796](./Arch Linux With KDE6(x11)安装小记/image-20240319124700796.png)

> mount作为挂载指令：你可以认为挂载是将设备等视作文件往里刻录东西之前的准备操作，就像你插入优盘Windows来对他进行操作的预备工作那样理解

​	我们使用的是btrfs来操作，所以后面的参数就是指定我们如何压缩存储到磁盘上面的：

>- zstd
>- lzo
>- zlib

​	这些算法是可以被选择的，你可以查看后选择你希望的算法进行压缩

```
btrfs subvolume create /mnt/@ # 创建 / 目录子卷
btrfs subvolume create /mnt/@home # 创建 /home 目录子卷
btrfs subvolume list -p /mnt
```

![image-20240319124804747](./Arch Linux With KDE6(x11)安装小记/image-20240319124804747.png)

​	在挂载时，挂载是有顺序的，需要从根目录开始挂载。使用如下命令挂载子卷：

```
mount -t btrfs -o subvol=/@,compress=zstd /dev/sda3 /mnt # 挂载 / 目录
mkdir /mnt/home # 创建 /home 目录
mount -t btrfs -o subvol=/@home,compress=zstd /dev/sda3 /mnt/home # 挂载 /home 目录
mkdir -p /mnt/boot/efi # 创建 /boot/efi 目录
mount /dev/sda1 /mnt/boot/efi # 挂载 /boot/efi 目录
swapon /dev/sda2 # 挂载交换分区
df -h # 查看挂载情况
free -h # 查看交换是否开启
```

![image-20240319125104714](./Arch Linux With KDE6(x11)安装小记/image-20240319125104714.png)

![image-20240319125121138](./Arch Linux With KDE6(x11)安装小记/image-20240319125121138.png)	

### VI. 安装系统

​	开始安装系统！

```
pacstrap /mnt base base-devel linux linux-firmware btrfs-progs
# 如果使用btrfs文件系统，额外安装一个btrfs-progs包
```

- `base-devel` —— `base-devel` 在 `AUR` 包的安装过程中是必须用到的
- `linux` —— 内核软件包，这里建议先不要替换为其它内核

![image-20240319125232674](./Arch Linux With KDE6(x11)安装小记/image-20240319125232674.png)

​	以及请务必安装下面的东西，这是为了稍后操作方便

```
pacstrap /mnt networkmanager vim sudo 
```

​	至于：

```
pacstrap /mnt zsh zsh-completions
```

​	中是喜欢bash还是zsh还是fish啥的，看自己需求来。个人当时这里看到missing class的zsh很帅就安装了zsh(划去

###  VII.生成 fstab 文件

​	`fstab` 用来定义磁盘分区。它是 Linux 系统中重要的文件之一。使用 `genfstab` 自动根据当前挂载情况生成并写入 `fstab` 文件：

```
genfstab -U /mnt > /mnt/etc/fstab
```

​	复查一下 `/mnt/etc/fstab` 确保没有错误：

```
cat /mnt/etc/fstab
```

![image-20240319125705793](./Arch Linux With KDE6(x11)安装小记/image-20240319125705793.png)

### VIII. 切换root与配置新root

​	很快了！

```
arch-chroot /mnt
```

![image-20240319125729743](./Arch Linux With KDE6(x11)安装小记/image-20240319125729743.png)

​	首先在 `/etc/hostname` 设置主机名：

```
vim /etc/hostname
```

> 这个看自己喜欢啥名字都行！这是我的：
>
> ```
> ArchLinux
> ```

1. 接下来在 `/etc/hosts` 设置与其匹配的条目：

```
vim /etc/hosts
```

加入如下内容：

![image-20240319125917955](./Arch Linux With KDE6(x11)安装小记/image-20240319125917955.png)

```
127.0.0.1   localhost
::1         localhost
127.0.1.1   ArchLinux.localdomain ArchLinux
```

> 某些情况下如不设置主机名，在 KDE 下可能会存在网络情况变更时无法启动 GUI 应用的问题，在终端中出现形如 `No protocol specified qt.qpa.xcb: could not connect to display` 的错误。这种情况极为少见。

​	设置时区，在 `/etc/localtime` 下用 `/usr` 中合适的时区创建符号链接：

```
ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
```

​	以及同步一下硬件时钟

```
hwclock --systohc
```

![image-20240319130026863](./Arch Linux With KDE6(x11)安装小记/image-20240319130026863.png)

### IX. 设置 locale

​	`Locale` 决定了软件使用的语言、书写习惯和字符集。编辑 `/etc/locale.gen`，去掉 `en_US.UTF-8 UTF-8` 以及 `zh_CN.UTF-8 UTF-8` 行前的注释符号（`#`）：

```
vim /etc/locale.gen
```

> 在命令行模式下输入/ + 查询前缀可以快速定位！摁Enter表示接受查询让光标不再跟着走！

​	然后生成locale文件：

```
locale-gen
```

![image-20240319130143841](./Arch Linux With KDE6(x11)安装小记/image-20240319130143841.png)

​	为防止奇怪的乱码出现：

```
echo 'LANG=en_US.UTF-8'  > /etc/locale.conf
```

### X.为 root 用户设置密码

```
passwd root
```

### XI.**安装微码与引导（容易出错）**

​	安装对应芯片制造商的微码（自行查询自己的cpu是base what的）

```
pacman -S intel-ucode # Intel
pacman -S amd-ucode # AMD
```

​	安装引导包

```
pacman -S grub efibootmgr
```

`-S` 选项后指定要通过 `pacman` 包管理器安装的包：

- `grub` —— 启动引导器
- `efibootmgr` —— `efibootmgr` 被 `grub` 脚本用来将启动项写入 NVRAM

​	安装 `GRUB` 到 `EFI` 分区：

```
grub-install --target=x86_64-efi --efi-directory=/boot/efi --bootloader-id=ARCH
```

- `--efi-directory=/boot`/efi —— **将 `grubx64.efi` 安装到之前的指定位置（EFI 分区）**
- `--bootloader-id=ARCH` —— 取名为 `ARCH`

![image-20240319130516016](./Arch Linux With KDE6(x11)安装小记/image-20240319130516016.png)

​	如果出来似乎不是efi分区的错误，要么看自己的efi挂载在哪里了，要么看看自己有没有分efi出来（乐）

​	最后生成 `GRUB` 所需的配置文件：

```
grub-mkconfig -o /boot/grub/grub.cfg
```

![image-20240319192613536](./Arch Linux With KDE6(x11)安装小记/image-20240319192613536.png)

​	完事：

```
exit # 退回安装环境
umount -R /mnt # 卸载新分区
reboot # 重启
```

​	重启后使用 root 账户登录系统：

![image-20240319192703265](./Arch Linux With KDE6(x11)安装小记/image-20240319192703265.png)

![image-20240319192725987](./Arch Linux With KDE6(x11)安装小记/image-20240319192725987.png)

​	设置开机自启并立即启动 networkmanager 服务，即可连接网络：

```
systemctl enable --now NetworkManager # 设置开机自启并立即启动 NetworkManager 服务
```

​	ping一下网络？

![image-20240319192803637](./Arch Linux With KDE6(x11)安装小记/image-20240319192803637.png)

### Fin.整个花活

```
pacman -S neofetch
```

![image-20240319192825175](./Arch Linux With KDE6(x11)安装小记/image-20240319192825175.png)

​	完事咯！

## KDE6 安装配置

​	哈？不稀罕命令行？来整KDE6!

![image-20240319192953511](./Arch Linux With KDE6(x11)安装小记/image-20240319192953511.png)

​	先更新一下包管理！

​	注意，我们的KDE进入需要一个User用户，在Linux下添加一个用户的方式是：

```
useradd -m edit_UserName
```

​	比如说：

![image-20240319193142194](./Arch Linux With KDE6(x11)安装小记/image-20240319193142194.png)

​	下面为他设置密码：

```
passwd edit_UserName
```

​	给我们新建的用户一个可以使用sudo的机会

```
vim /etc/sudoers
```

​	在这个配置文件中写入：用户名称 `ALL=(ALL)ALL`

![image-20240319193241453](./Arch Linux With KDE6(x11)安装小记/image-20240319193241453.png)

​	下面就是安装大的：

```
pacman -S xorg plasma kde-applications
```

![image-20240319193401104](./Arch Linux With KDE6(x11)安装小记/image-20240319193401104.png)

> PS:一些老教程要求你也安装plasma-wayland-session，但是现在已经转正进入plasma了，不要安装了：
>
> 参考博客`:>`
>
> [install archlinux kde error target not found plasma-wayland-session / Arch Linux Guided Installer / Arch Linux Forums](https://bbs.archlinux.org/viewtopic.php?pid=2156234)

​	好了喝口茶吧，得个几分钟。

```
systemctl enable sddm.service # 启用显示管理器
systemctl status NetworkManager.service # 检查网络管理器服务，确认他已经开启开机自启动
```

​	重启：

```
reboot
```

​	好了！使用你刚刚创建的用户登录它！结束KDE的基础配置！

## KDE进阶配置

​	到这里，如果你还想继续配置可以继续跟随我的步伐：

### I. 设置屏幕分辨率

打开`System Setting（桌面底下从左向右数第二个） -> Display and Monitor -> Display Configuration`

### II. archlinuxcn源

​	该仓库是由archlinux中文社区驱动的一个非官方的软件仓库。编辑`/etc/pacman.conf：`

```text
sudo vim /etc/pacman.conf
-------------------------------------------
# 在最后添加
[archlinuxcn]
Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
```

​	![image-20240319195728856](./Arch Linux With KDE6(x11)安装小记/image-20240319195728856.png)

​	顺嘴一提：如果你只是一个普通用户，不需要强验证ringKey的话，考虑将SigLevel设置为Never（虚拟机不怕（乐））

![image-20240319195626822](./Arch Linux With KDE6(x11)安装小记/image-20240319195626822.png)

​	否则等会下包的时候会频繁的要求你添加信任的开发者。

### III. 安装中文字体 + fcitx5输入法

​	下一步就是安装中文字体和fcitx5输入法了。请注意的是，这里有两套诸位可以选择的配置：

> fcitx + sogoupinyin

```
yay -S fcitx fcitx-im fcitx-configtool fcitx-sogoupinyin
```

> fcitx5（笔者的配置是这个）

```
yay -S fcitx5-im fcitx5-chinese-addons
```

​	注意到fcitx5-im里就包含了：

>- fcitx5
>- fcitx5-configtool
>- fcitx5-gtk
>- fcitx5-qt

​	然后，我们还要让fcitx在xwindows加载的时候就启用，所以，一个快捷的方式就是直接在用户目录下写一个.xprofile文件：

```
vim ~/.xprofile
```

​	写下这些东西：

```
GTK_IM_MODULE=fcitx5
QT_IM_MODULE=fcitx5
XMODIFIERS="@im=fcitx5"
```

​	关于xprofile文件的性质：可以参考archWiki:[xprofile - ArchWiki (archlinux.org)](https://wiki.archlinux.org/title/Xprofile)

​	这里检查的方式就是直接`reboot`让环境重新加载读取配置文件

​	这里，可能还会发现存在一些乱码（比如说region and language设置切换语言的时候简体中文的简这个字是方框），我们需要下载开源的好用字体：

> 下载一个中文字体：

>- `wqy-microhei`(笔者选择了这个)
>- `wqy-microhei-lite`
>- `wqy-bitmapfont`
>- `wqy-zenhei`
>- `ttf-arphic-ukai`
>- `ttf-arphic-uming`
>- `adobe-source-han-sans-cn-fonts`
>- `adobe-source-han-serif-cn-fonts`
>- `noto-fonts-cjk`

​	下载一个nerd-fonts字体：

![image-20240320121517131](./Arch Linux With KDE6(x11)安装小记/image-20240320121517131.png)

​	笔者这里选择的是40（jb家的hhh）

​	下载的方式就是

```
yay -S wqy-microhei
```

```
yay -S nerd-fonts #然后询问下载哪个的时候选择40（内存土豪全下我没意见）
```

​	nerd-fonts会在后面我们配置`fish + oh-my-posh`的时候会用到。

### IV. firefox + 配置代理

​	我们来配置代理：当然，笔者出于简单的考虑选择的是`clash-verge`

```
yay -S clash-verge firefox # firefox是浏览器，我喜欢这个（
```

​	下好了之后启动它直接GUI操作：

> 这里塞订阅

![image-20240320121944803](./Arch Linux With KDE6(x11)安装小记/image-20240320121944803.png)

> 在这里启动

![image-20240320122008635](./Arch Linux With KDE6(x11)安装小记/image-20240320122008635.png)

​	选择打开系统代理之后，就可以直接google了（在刚刚下载好的浏览器里直接正常操作）：

![image-20240320122142376](./Arch Linux With KDE6(x11)安装小记/image-20240320122142376.png)

​	但是我们的代理没法在终端使用，这个问题我们放在下一个section讲：

### V. `fish + oh-my-posh`

​	来了来了，我们首先先下载fish

```
yay -S fish unzip wget # unzip是后面我们为oh-my-posh服务的，wget是后面我们下载zip包服务的
```

​	下一步，就是更改我们的Konsole启动的默认配置（笔者这里的shell已经是fish了）

![image-20240320122501233](./Arch Linux With KDE6(x11)安装小记/image-20240320122501233.png)

​	在设置那里选择配置Konsole,切换到配置方案页面。咱们新建一个配置方案：

![image-20240320122615093](./Arch Linux With KDE6(x11)安装小记/image-20240320122615093.png)

​	在外观上，设置字体（选择你自己下的Nerd Font即可）：

![image-20240320123941804](./Arch Linux With KDE6(x11)安装小记/image-20240320123941804.png)

​	现在新建一个标签页：很好，就长这样

![image-20240319220024290](./Arch Linux With KDE6(x11)安装小记/image-20240319220024290.png)

​	下一步就是拉取oh-my-posh

```
curl -s https://ohmyposh.dev/install.sh | sudo bash -s
```

​	接着我们下载主题：

```
# 创建主题存放文件夹，读者可以根据需要自定义存放位置，
# 如果自定义修改位置，那么后续的命令也需要做出相应更改
mkdir ~/.poshthemes
# 获取主题zip文件并存放至对应主题文件夹（如果使用该命令下载zip较慢，
# 可以通过复制该URL使用“github文件加速下载下载”文件
wget https://github.com/JanDeDobbeleer/oh-my-posh/releases/latest/download/themes.zip -O ~/.poshthemes/themes.zip
# 解压主题压缩包文件
unzip ~/.poshthemes/themes.zip -d ~/.poshthemes
# 将所有主题文件设置可读权限
chmod u+rw ~/.poshthemes/*.omp.*
# 删除主题压缩包
rm ~/.poshthemes/themes.zip
```

```bash
# 注意“~/.poshthemes/jandedobbeleer.omp.json”，根据实际安装情况选择读者自己设置的 oh-my-posh 主题位置而定，在此仅作为参考。
# 下面是一个例子
oh-my-posh init fish --config ~/.poshthemes/jandedobbeleer.omp.json | source
```

> 注意
>
> 主题可以在[官网](https://ohmyposh.dev/docs/themes)查看，当读者看到适合自己的主题时，可以暂时通过命令“oh-my-posh init fish --config ~/.poshthemes/看到的主题名.omp.json | source”查看使用效果，如果合适则直接将该命令添加到fish的配置文件中即可。

​	笔者这里选择的是blueish主题

```
oh-my-posh init fish --config ~/.poshthemes/blueish.omp.json | source
```

​	然后把上面的命令写入：

```
~/.config/fish/config.fish
```

![image-20240320123810913](./Arch Linux With KDE6(x11)安装小记/image-20240320123810913.png)

​	然后开一个终端就行，如果没问题，就会是这样的

![image-20240320123910399](./Arch Linux With KDE6(x11)安装小记/image-20240320123910399.png)

### VI. 配置终端代理

​	这一步请确保IV步骤已经完成！

​	实质上就是向终端启动文件写入两个alias就行：

![image-20240319221426461](./Arch Linux With KDE6(x11)安装小记/image-20240319221426461.png)

​	注意后面的http_proxy和https_proxy的端口号请看自己的代理软件的端口号。

​	在我们没有开启代理之前，我们测试一下：

```
curl google.com
```

![image-20240320124330709](./Arch Linux With KDE6(x11)安装小记/image-20240320124330709.png)

​	现在打开代理，确保自己的alias已经配置好并被终端读取

![image-20240320124414719](./Arch Linux With KDE6(x11)安装小记/image-20240320124414719.png)

​	完事！

### VII. 配置lunar vim

​	首先先下载neovim

```
yay -S neovim
```

​	![image-20240320130206684](./Arch Linux With KDE6(x11)安装小记/image-20240320130206684.png)

​	之后下载脚本开始配置

```
curl https://raw.githubusercontent.com/LunarVim/LunarVim/release-1.3/neovim-0.9/utils/installer/install.sh > install.sh
chmod 777 ./install.sh && ./install.sh
```

​	配置结束，按照脚本的提示，我们为了不污染环境，在config.fish文件下再alias一个指令

![image-20240320130635235](./Arch Linux With KDE6(x11)安装小记/image-20240320130635235.png)

```
alias lvim=/path/to/your/vim/according/2/your/shellscript
```

​	新开一个

```
lvim
```

![image-20240320130750175](./Arch Linux With KDE6(x11)安装小记/image-20240320130750175.png)

## WHOLE_REFERENCE

> **Base:**[archlinux 基础安装 | archlinux 简明指南 (icekylin.online)](https://arch.icekylin.online/guide/rookie/basic-install.html)

>**KDE_Base**[如何在 Arch Linux 上正确安装和设置 KDE Plasma？ | Linux 中国 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/144122288)
>
>**输入法：**
>
>1. [Archlinux安装和配置fcitx5 - 可乐klelee - 博客园 (cnblogs.com)](https://www.cnblogs.com/klelee/p/archlinux-fcitx5.html)
>2. [Arch Linux + KDE 配置&美化（持续更新~） - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/558354279)
>
>**字体**
>
>[Arch（KDE Plasma）中文化_arch 中文字体-CSDN博客](https://blog.csdn.net/qingtian805/article/details/123187337)
>
>**Fish Shell + Oh My Posh**
>
>1. [如何在 Linux 中安装、配置和使用 Fish Shell？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/59439573)
>2. [fish shell](https://fishshell.com/)
>3. [Home | Oh My Posh](https://ohmyposh.dev/)
>4. [Linux终端下使用Fish shell并美化 - 木木亚伦 - 博客园 (cnblogs.com)](https://www.cnblogs.com/aaroncoding/p/17118251.html)
>
>**lunar vim**
>
>[Installation | LunarVim](https://www.lunarvim.org/docs/installation)