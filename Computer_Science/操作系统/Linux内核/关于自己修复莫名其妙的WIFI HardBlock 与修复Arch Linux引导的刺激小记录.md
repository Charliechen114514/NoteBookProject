# 关于自己修复莫名其妙的WIFI HardBlock 与修复Arch Linux引导的刺激小记录

​	事情的起因是打算更新一下自己的小系统，但是出现了一个严重的问题：那就是自己的WIFI不认识了，查询自己的WIFI怎么回事：

```
rfkill list all
```

​	会告知我：所有的网络都被hard block了。也就是说，要不就是自己的硬件出了问题，要不就是自己的模块没有正确的挂载导致自己的驱动挂了。

​	其实一个正确的办法是重新initcpio和initramfs，就是自己在pacman -S linux下系统自己重新挂载一次模块就能解决的事情，我自己以为是自己的UEFI启动把WIFI Switch关掉了。

​	就在这个时候我犯了一键大错：我自己点击了Load Default摁扭把所有的引导都抹干净了！导致我的Arch Linux找不到再哪里了。

​	修复这个问题很简单：

## 修复系统

​	自己重新刻录一个可以启动系统的U盘，把他查到自己的出事故的笔记本。这个时候会检测到存在ArchLinux操作系统的。所以这个时候进入安装界面，怎么做呢？很简单

- 把自己的分区重新挂载
- 然后重新生成启动文件

​	这个事情分文件系统。笔者使用的文件系统时btrfs。这个就要麻烦一些了：

> [Arch Linux With KDE6(x11)安装小记-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/136873390)

​	笔者在几个月前的博客记录了自己的btrfs安装时候的输入的指令，只需要照着自己的重新输入一次就好了。

```
mount -t btrfs -o subvol=/@,compress=zstd /dev/sda3 /mnt # 挂载 / 目录
mount -t btrfs -o subvol=/@home,compress=zstd /dev/sda3 /mnt/home # 挂载 /home 目录
mount /dev/sda1 /mnt/boot/efi # 挂载 /boot/efi 目录,这一步现在看来是关键
swapon /dev/sda2 # 挂载交换分区
```

下一步也是最关键的：看看我们能不能进入这个已经丢失的系统，原则上来讲肯定可以：

```
arch-chroot /mnt
```

​	非常好！自己ls了一下，发现自己的home目录等什么也没有丢失！说明系统完全可以恢复正常。

​	下一步就是我的WIFI问题，最粗暴的直接刷新自己的cpio和ramfs，重新挂载WIFI模块。

```
pacman -S linux
...
reinstalling linux...
...
```

​	OK，现在就是重新生成Grub引导记录了：

```
grub-install --target=x86_64-efi --efi-directory=/boot/efi --bootloader-id=ARCH
```

​	笔者当时挂载的区域在这里，现在我们重新生成一次grub引导就好了。

​	Ok，现在我们退出去

```
exit
umount -R /mnt
reboot
```

​	记得把自己的U盘拔掉，让grub引导工作。完成后就会看到熟悉的Grub引导界面，然后进入等自己的操作系统接管电脑就好了。

​	