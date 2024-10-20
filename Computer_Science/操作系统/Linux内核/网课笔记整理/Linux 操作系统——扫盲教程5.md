# Linux 操作系统——扫盲教程5

## 更多的 Machine Related 指令

#### useradd

​	各位如果有自己装Linux发行版的经验，就会知道我们的操作系统需要注册一个用户，我们登陆上去操作我们的机器。这里，我们产生用户就是使用的useradd指令。他将会添加一个用户，更加具体的reference在

>[Linux useradd 命令 | 菜鸟教程 (runoob.com)](https://www.runoob.com/linux/linux-comm-useradd.html)

#### passwd

​	欸！密码呢？就是用passwd设置密码。我们的密码是存在passwd文件里的：各位可以看看图一新鲜！

```
➜  sudo cat /etc/passwd
[sudo] password for charliechen:
root:x:0:0:root:/root:/bin/bash
...
```

>[Linux passwd命令 | 菜鸟教程 (runoob.com)](https://www.runoob.com/linux/linux-comm-passwd.html)

>[Linux /etc/shadow（影子文件）内容解析（超详细） (biancheng.net)](https://c.biancheng.net/view/840.html)

#### ps

​	ps （英文全拼：process status）命令用于显示当前进程的状态，类似于 windows 的任务管理器。

```
➜  ps
    PID TTY          TIME CMD
    349 pts/0    00:00:00 bash
    622 pts/0    00:00:00 ps
```

​	我们可以在这里查看当前shell depatch的线程PID!

#### top

​	top命令经常用来监控linux的系统状况，是常用的性能分析工具，能够实时显示系统中各个进程的资源占用情况。

```
➜  top
top - 09:18:54 up 4 min,  1 user,  load average: 0.00, 0.01, 0.00
Tasks:  25 total,   1 running,  24 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  0.0 sy,  0.0 ni, 99.9 id,  0.1 wa,  0.0 hi,  0.0 si,  0.0 st
MiB Mem :   7870.3 total,   7055.6 free,    656.9 used,    395.2 buff/cache
MiB Swap:   2048.0 total,   2048.0 free,      0.0 used.   7213.4 avail Mem

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
      1 root      20   0   21648  13028   9564 S   0.0   0.2   0:00.44 systemd
      2 root      20   0    2616   1444   1320 S   0.0   0.0   0:00.00 init-systemd(Ub
      7 root      20   0    2616    132    132 S   0.0   0.0   0:00.00 init
     47 root      19  -1   42232  16244  15096 S   0.0   0.2   0:00.16 systemd-journal
     94 root      20   0   24056   6044   4876 S   0.0   0.1   0:00.15 systemd-udevd
    138 systemd+  20   0   21452  11932   9740 S   0.0   0.1   0:00.08 systemd-resolve
    139 systemd+  20   0   91020   6496   5652 S   0.0   0.1   0:00.07 systemd-timesyn
    183 root      20   0    4236   2688   2452 S   0.0   0.0   0:00.00 cron
    185 message+  20   0    9528   5180   4556 S   0.0   0.1   0:00.04 dbus-daemon
    196 root      20   0   17976   8328   7304 S   0.0   0.1   0:00.06 systemd-logind
    200 root      20   0 1756096  18044   9408 S   0.0   0.2   0:00.07 wsl-pro-service
    217 root       0 -20    2692     88      0 S   0.0   0.0   0:00.01 atopacctd
    224 syslog    20   0  222508   5356   4504 S   0.0   0.1   0:00.06 rsyslogd
    233 root       0 -20   11716  11700   5972 S   0.0   0.1   0:00.02 atop
    242 root      20   0  112784  24684  14856 S   0.0   0.3   0:00.06 unattended-upgr
    303 root      20   0    3160   1200   1116 S   0.0   0.0   0:00.00 agetty
    306 root      20   0    3116   1116   1024 S   0.0   0.0   0:00.00 agetty
    347 root      20   0    2628    124      0 S   0.0   0.0   0:00.00 SessionLeader
    348 root      20   0    2628    136      0 S   0.0   0.0   0:00.00 Relay(349)
    349 charlie+  20   0    6336   5588   3656 S   0.0   0.1   0:00.07 bash
    350 root      20   0    6696   4688   3904 S   0.0   0.1   0:00.01 login
    425 charlie+  20   0   20264  11588   9504 S   0.0   0.1   0:00.07 systemd
    429 charlie+  20   0   21148   1728      0 S   0.0   0.0   0:00.00 (sd-pam)                                         
```

#### nice

​	nice命令以更改过的优先序来执行程序，如果未指定程序，则会印出目前的排程优先序，内定的 adjustment 为 10，范围为 -20（最高优先序）到 19（最低优先序）。

#### pgrep

​	pgrep 命令允许用户在系统当前状态下查找正在运行的程序中的进程 ID。

#### ifconfig

​	查看自己的网络state的，这个命令很复杂，在这里不单独展开.

#### iostat

​	iostat是 I/O statistics（输入/输出统计）的缩写，iostat工具将对系统的磁盘操作活动进行监视。它的特点是汇报磁盘活动统计情况，同时也会汇报出CPU使用情况。iostat也有一个弱点，就是它不能对某个进程进行深入分析，仅对系统的整体情况进行分析

```
➜  iostat
Linux 5.15.153.1-microsoft-standard-WSL2 (Charliechen)  10/12/24        _x86_64_        (16 CPU)

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.13    0.00    0.16    0.07    0.00   99.64

Device             tps    kB_read/s    kB_wrtn/s    kB_dscd/s    kB_read    kB_wrtn    kB_dscd
sda               2.47       167.05         0.00         0.00      78661          0          0
sdb               0.22         4.73         0.01         0.00       2228          4          0
sdc              26.52       824.73        82.35      1426.55     388358      38776     671748
```

#### iotop

​	类似于top：

```
Total DISK READ:         0.00 B/s | Total DISK WRITE:         0.00 B/s
Current DISK READ:       0.00 B/s | Current DISK WRITE:       0.00 B/s
    TID  PRIO  USER     DISK READ DISK WRITE>    COMMAND                                                                      1 be/4 root        0.00 B/s    0.00 B/s init
      2 be/4 root        0.00 B/s    0.00 B/s init
      9 be/4 root        0.00 B/s    0.00 B/s init [Interop]
      7 be/4 root        0.00 B/s    0.00 B/s plan9 --control-socket 6 --log-level~erver-fd 7 --pipe-fd 9 --log-truncate      8 be/4 root        0.00 B/s    0.00 B/s plan9 --control-socket 6 --log-level~erver-fd 7 --pipe-fd 9 --log-truncate     47 be/3 root        0.00 B/s    0.00 B/s systemd-journald                                                               94 be/4 root        0.00 B/s    0.00 B/s systemd-udevd
    138 be/4 systemd-    0.00 B/s    0.00 B/s systemd-resolved
    139 be/4 systemd-    0.00 B/s    0.00 B/s systemd-timesyncd
    143 be/4 systemd-    0.00 B/s    0.00 B/s systemd-timesyncd [sd-resolve]
    183 be/4 root        0.00 B/s    0.00 B/s cron -f -P
    185 be/4 messageb    0.00 B/s    0.00 B/s @dbus-daemon --system --address=syst~le --systemd-activation --syslog-only    196 be/4 root        0.00 B/s    0.00 B/s systemd-logind
    200 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    247 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    248 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    249 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    250 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    252 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    258 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    259 be/4 root        0.00 B/s    0.00 B/s wsl-pro-service -vv
    217 be/0 root        0.00 B/s    0.00 B/s atopacctd
    224 be/4 syslog      0.00 B/s    0.00 B/s rsyslogd -n -iNONE
    253 be/4 syslog      0.00 B/s    0.00 B/s rsyslogd -n -iNONE [in:imuxsock]
```

>[在 Linux 中如何使用 iotop 和 iostat 监控磁盘 I/O 活动？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/64681360)

#### mpstat

​	mpstat是Multiprocessor Statistics的缩写，是实时系统监控工具。其报告与CPU的一些统计信息，这些信息存放在/proc/stat文件中。在多CPUs系统里，其不但能查看所有CPU的平均状况信息，而且能够查看特定CPU的信息。mpstat最大的特点是：可以查看多核心cpu中每个计算核心的统计数据；而类似工具vmstat只能查看系统整体cpu情况。

```
➜  mpstat
Linux 5.15.153.1-microsoft-standard-WSL2 (Charliechen)  10/12/24        _x86_64_        (16 CPU)

09:25:36     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
09:25:36     all    0.11    0.00    0.12    0.07    0.00    0.03    0.00    0.00    0.00   99.67
```

>[mpstat命令详解 - 马昌伟 - 博客园 (cnblogs.com)](https://www.cnblogs.com/machangwei-8/p/10388647.html)

#### vmstat

​	vmstat是Virtual Meomory Statistics（虚拟内存统计）的缩写，可对操作系统的虚拟内存、进程、CPU活动进行监控。是对系统的整体情况进行统计，不足之处是无法对某个进程进行深入分析。

```
➜  vmstat
procs -----------memory---------- ---swap-- -----io---- -system-- -------cpu-------
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st gu
 0  0      0 7285108   5780 337400    0    0   897   213  169    0  0  0 100  0  0  0
```

>[技术|vmstat：一个标准的报告虚拟内存统计工具 (linux.cn)](https://linux.cn/article-8157-1.html)