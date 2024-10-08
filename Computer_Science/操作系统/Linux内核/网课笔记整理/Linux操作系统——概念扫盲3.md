# Linux概念扫盲 3

## 常见的Linux指令备忘

​	在我们进一步研究Linux之前，首先需要熟悉一些最为常见的指令。笔者混迹于一些常见的Linux交流群发现很多问题在各位新手如果能够理解什么是shell以及一些最为常见的指令的话，可以做到事半功倍的效果。因此，笔者出于这个目的，以及也是给自己作点备忘的打算，写一些常见的指令作为一定的备忘。

## pwd

​	pwd指代了我们的当前目录，看官启动默认位置的shell时，将会自动停留在自己的HOME目录下。这一点，只需要在启动的时候就输入pwd就会得以验证：

```
➜  pwd
/home/charliechen
```

​	pwd命令（全称：print working directory）就是一个这样非常简单的Linux命令，它的功能就是打印当前工作目录。

​	用处：当你在Linux终端中感到迷失时，pwd命令可以帮助你重新定位，显示你所在的目录。没了。

## ls

​	ls命令是list的缩写，是最常用的Linux命令之一，它用于列出指定目录下的文件和子目录及其属性信息。也就是很多Linux User调侃的习惯：登入系统，起手ls。他就是查看当前目录下有什么的一个指令。笔者在自己的WSL（当然各位可能是自己的笔记本主OS）中输入ls得到的是

```
➜  ls
demo  linux-programming  op  remote  shell
```

​	这也就对应于我们的实际情况：

```
➜  tree -L 1
.
├── demo
├── linux-programming
├── op
├── remote
└── shell

6 directories, 0 files
```

​	对于大部分的shell，目录会显示区别于文件的，不一样的颜色。当然，能有别的办法吗？

​	有！添加参数就好。参数列表可以见下面的Helps章节进行阅读。

​	笔者这里单拎出来-l, -h, -a三个参数，这是笔者最喜欢用的。参数之间大部分可以相互叠加使用。比如说：-l表达按照列表列出，-h表达参数信息按照人类可读的方式进行阅读。

```
➜  ls -lh
total 20K
drwxr-xr-x 4 charliechen charliechen 4.0K Aug 14 17:23 demo
drwxr-xr-x 2 charliechen charliechen 4.0K Sep 28 10:34 linux-programming
drwxr-xr-x 2 charliechen charliechen 4.0K Aug 21 10:59 op
drwxr-xr-x 3 charliechen charliechen 4.0K Sep 10 21:11 remote
drwxr-xr-x 3 charliechen charliechen 4.0K Sep  3 18:54 shell
```

​	第一个部分阐述的是这个文件的权限。这里可以参考扫盲2的用户权限模型的部分：[Linux操作系统——概念扫盲2-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/142746852)

​	对于第二个部分，则是阐述的是文件包含的子文件个数。这里我们查看两个例子：

```
ls -lh demo
-rw-r--r-- 1 charliechen charliechen  114 Aug 14 17:24 CMakeLists.txt
drwxr-xr-x 4 charliechen charliechen 4.0K Aug 14 17:26 build
-rw-r--r-- 1 charliechen charliechen   80 Aug 14 17:25 main.cpp
```

```
➜  ls -lh linux-programming/
total 20K
-rwxr-xr-x 1 charliechen charliechen 16K Sep 28 10:34 cr0
-rw-r--r-- 1 charliechen charliechen 138 Sep 28 10:34 cr0.c
```

​	很奇怪，怎么`ls -lh demo`就对不上个数呢？明明输出3个项目却告诉我们这里有四个子文件。很简单！这里存在隐藏的文件。这就是我们的-a参数的用武之地了

```
➜  ls -lah demo
total 24K
drwxr-xr-x  4 charliechen charliechen 4.0K Aug 14 17:23 .
drwxr-x--- 18 charliechen charliechen 4.0K Sep 28 10:32 ..
drwxr-xr-x  2 charliechen charliechen 4.0K Aug 14 17:14 .vscode
-rw-r--r--  1 charliechen charliechen  114 Aug 14 17:24 CMakeLists.txt
drwxr-xr-x  4 charliechen charliechen 4.0K Aug 14 17:26 build
-rw-r--r--  1 charliechen charliechen   80 Aug 14 17:25 main.cpp
```

​	可以看到：对于一般的隐藏文件会是以.起头，这样我们如果不添加-a参数，他们是不会显示出来的！

## cd

​	change diractory，更换（当前的）目录。有初学者问过我如何在命令行中进入其他文件夹，笔者就告诉他使用`cd + 文件夹名称`的办法。值得注意的是：这里的名称叫做路径是更加容易理解的。在Linux文件系统中，名称跟文件路径是等价的。当我们谈到名称的时候，就意味着实际上给指令提供文件路径也是合法的！

​	来看看cd的功效，配合pwd来展示效果！

```
➜  pwd
/home/charliechen
➜  cd linux-programming/
➜  pwd
/home/charliechen/linux-programming
```

## cat

​	cat（concatenate）命令用于连接文件并打印到标准输出设备上，它的主要作用是用于查看和连接文件。笔者最常用的是扫一眼一个非常简短的文本。比如说我想要看一眼cr0.c文件：

```
➜  cat cr0.c
#include <stdint.h>

static uint64_t get_cr0()
{
  __asm__ __volatile__("movq %cr0, %rax");
}

int main()
{
  uint64_t res = get_cr0();
}
```

​	他就会平凡的把文本进行输出。

## more

​	more 命令类似 cat ，不过会以一页一页的形式显示，更方便使用者逐页阅读，而最基本的指令就是按空白键（space）就往下一页显示，按 b 键就会往回（back）一页显示，而且还有搜寻字串的功能（与 vi 相似），使用中的说明文件，请按 h 。

​	当然，more实际上并不常用了现在。笔者建议长文件使用vim进行阅读就好。

## head, tail

​	head和tail功能类似，一个显示头，一个显示尾。

​	默认的，两者默认显示的行数都是10行。各位可以看看：

```
➜  cat test.c
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  printf("Hello, world");
  int rc = fork();
  if(rc < 0){
    fprintf(stderr, "Error inn calling fork");
    return 0;
  }
  else if(rc == 0){
    printf("Child process:> %d\n", (int)getpid());
  }else{
    printf("Parent process:> %d\n", (int)getpid());
  }



}
```

​	对于这个文本，我们来使用head来查看：

```
➜  head test.c
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  printf("Hello, world");
  int rc = fork();
  if(rc < 0){
```

​	tail来查看：

```
➜  tail test.c
  }
  else if(rc == 0){
    printf("Child process:> %d\n", (int)getpid());
  }else{
    printf("Parent process:> %d\n", (int)getpid());
  }



}
```

​	那能不能指定行数呢？行：

```
➜  head -n 15 test.c
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  printf("Hello, world");
  int rc = fork();
  if(rc < 0){
    fprintf(stderr, "Error inn calling fork");
    return 0;
  }
  else if(rc == 0){
    printf("Child process:> %d\n", (int)getpid());
```

​	tail同理，这里不再演示。

## grep

​	用正则表达式筛选显示内容的！理解它必须同时理解管道等概念。比如说，我们拿到一个很长的文本，需要快速定位一些内容：

```
# 查一下怎么快速列出人类可读的办法
➜  ls --help | grep human
  -h, --human-readable       with -l and -s, print sizes like 1K 234M 2G etc.
```

​	这就是一个例子：Linux grep (global regular expression) 命令用于查找文件里符合条件的字符串或正则表达式。grep 指令用于查找内容包含指定的范本样式的文件，如果发现某文件的内容符合所指定的范本样式，预设 grep 指令会把含有范本样式的那一列显示出来。若不指定任何文件名称，或是所给予的文件名为 **-**，则 grep 指令会从标准输入设备读取数据。

- `-i`：忽略大小写进行匹配。
- `-v`：反向查找，只打印不匹配的行。
- `-n`：显示匹配行的行号。
- `-r`：递归查找子目录中的文件。
- `-l`：只打印匹配的文件名。
- `-c`：只打印匹配的行数。

​	这是一些常见的参数。给位筛选日志的时候将会经常看到这样的搭配用法。



## find locate

​	都是用来查找的，find用途更加的广泛，它用来搜索指定的文件。可以使用不同的选项来过滤和限制查找的结果。

1. 路径 是要查找的目录路径，可以是一个目录或文件名，也可以是多个路径，多个路径之间用空格分隔，如果未指定路径，则默认为当前目录。

2. expression 是可选参数，用于指定查找的条件，可以是文件名、文件类型、文件大小等等。

匹配条件 中可使用的选项有二三十个之多，以下列出最常用的部份：

- -name pattern：按文件名查找，支持使用通配符 * 和 ?。
- -type type：按文件类型查找，可以是 f（普通文件）、d（目录）、l（符号链接）等。
- -size [+-]size[cwbkMG]：按文件大小查找，支持使用 + 或 - 表示大于或小于指定大小，单位可以是 c（字节）、w（字数）、b（块数）、k（KB）、M（MB）或 G（GB）。
- -mtime days：按修改时间查找，支持使用 + 或 - 表示在指定天数前或后，days 是一个整数表示天数。
- -user username：按文件所有者查找。
- -group groupname：按文件所属组查找。

find 命令中用于时间的参数如下：

- -amin n：查找在 n 分钟内被访问过的文件。
- -atime n：查找在 n\*24 小时内被访问过的文件。
- -cmin n：查找在 n 分钟内状态发生变化的文件（例如权限）。
- -ctime n：查找在 n\*24 小时内状态发生变化的文件（例如权限）。
- -mmin n：查找在 n 分钟内被修改过的文件。
- -mtime n：查找在 n*24 小时内被修改过的文件。

在这些参数中，n 可以是一个正数、负数或零。正数表示在指定的时间内修改或访问过的文件，负数表示在指定的时间之前修改或访问过的文件，零表示在当前时间点上修改或访问过的文件。

正数应该表示时间之前，负数表示时间之内。

例如：-mtime 0 表示查找今天修改过的文件，-mtime -7 表示查找一周以前修改过的文件。

关于时间 n 参数的说明：

+n：查找比 n 天前更早的文件或目录。

-n：查找在 n 天内更改过属性的文件或目录。

n：查找在 n 天前（指定那一天）更改过属性的文件或目录。

​	比如说这样用find是可以的：

```
➜  find / -name gcc 2>/dev/null
/usr/lib/gcc
/usr/libexec/gcc
/usr/bin/gcc
/usr/share/gcc
/usr/share/doc/gcc-13-base/gcc
/usr/share/doc/gcc
/usr/share/bash-completion/completions/gcc
```

​	这就表明在根目录下查找gcc,同时忽略了错误。（具体用法可以查看其他的博客）

​	而locate命令用于查找符合条件的文档，他会去保存文档和目录名称的数据库内，查找合乎范本样式条件的文档或目录。笔者用的比较少，这里建议了解即可。

## mv cp rm

mv：移动文件！用户可以使用该命令为文件或目录重命名或将文件由一个目录移入另一个目录中（该文件从原来的文件夹中消失）。

cp: 拷贝文件！该命令的功能是将给出的文件或目录拷贝到另一文件或目录中（该文件仍保存在原文件夹中）。

rm：很出名，就是删除文件。

## chmod

​	chmod（change mode）命令是控制用户对文件的权限的命令更改文件权限的指令。

```
chmod 644 file.txt 
```

​	是一个常见的指令，他将会更改目标的文件为自己可读可写，其他人均只可读！

> 三位数字中，三个数字依次代表u, g, o。u 表示该文件的拥有者，g 表示与该文件的拥有者属于同一个群体(group)者，o 表示其他以外的人。

- \+ 表示增加权限、- 表示取消权限、= 表示唯一设定权限。
- r 表示可读取，w 表示可写入，x 表示可执行，X 表示只有当该文件是个子目录或者该文件已经被设定过为可执行。

​	关于文件权限的查看，参看ls -l。

## ln

​	ln（link files）命令是一个非常重要命令，它的功能是为某一个文件在另外一个位置建立一个同步的链接。当我们需要在不同的目录，用到相同的文件时，我们不需要在每一个需要的目录下都放一个必须相同的文件，我们只要在某个固定的目录，放上该文件，然后在 其它的目录下用ln命令链接（link）它就可以，不必重复的占用磁盘空间。

```
ln -s log2013.log link2013
```

​	这条实际上就是创建快捷方式了，log2013.log失效了，link2023也就会失效。



# Helps

```
➜  ls --help
Usage: ls [OPTION]... [FILE]...
List information about the FILEs (the current directory by default).
Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

Mandatory arguments to long options are mandatory for short options too.
  -a, --all                  do not ignore entries starting with .
  -A, --almost-all           do not list implied . and ..
      --author               with -l, print the author of each file
  -b, --escape               print C-style escapes for nongraphic characters
      --block-size=SIZE      with -l, scale sizes by SIZE when printing them;
                             e.g., '--block-size=M'; see SIZE format below

  -B, --ignore-backups       do not list implied entries ending with ~
  -c                         with -lt: sort by, and show, ctime (time of last
                             change of file status information);
                             with -l: show ctime and sort by name;
                             otherwise: sort by ctime, newest first

  -C                         list entries by columns
      --color[=WHEN]         color the output WHEN; more info below
  -d, --directory            list directories themselves, not their contents
  -D, --dired                generate output designed for Emacs' dired mode
  -f                         list all entries in directory order
  -F, --classify[=WHEN]      append indicator (one of */=>@|) to entries WHEN
      --file-type            likewise, except do not append '*'
      --format=WORD          across -x, commas -m, horizontal -x, long -l,
                             single-column -1, verbose -l, vertical -C

      --full-time            like -l --time-style=full-iso
  -g                         like -l, but do not list owner
      --group-directories-first
                             group directories before files;
                             can be augmented with a --sort option, but any
                             use of --sort=none (-U) disables grouping

  -G, --no-group             in a long listing, don't print group names
  -h, --human-readable       with -l and -s, print sizes like 1K 234M 2G etc.
      --si                   likewise, but use powers of 1000 not 1024
  -H, --dereference-command-line
                             follow symbolic links listed on the command line
      --dereference-command-line-symlink-to-dir
                             follow each command line symbolic link
                             that points to a directory

      --hide=PATTERN         do not list implied entries matching shell PATTERN
                             (overridden by -a or -A)

      --hyperlink[=WHEN]     hyperlink file names WHEN
      --indicator-style=WORD
                             append indicator with style WORD to entry names:
                             none (default), slash (-p),
                             file-type (--file-type), classify (-F)

  -i, --inode                print the index number of each file
  -I, --ignore=PATTERN       do not list implied entries matching shell PATTERN
  -k, --kibibytes            default to 1024-byte blocks for file system usage;
                             used only with -s and per directory totals

  -l                         use a long listing format
  -L, --dereference          when showing file information for a symbolic
                             link, show information for the file the link
                             references rather than for the link itself

  -m                         fill width with a comma separated list of entries
  -n, --numeric-uid-gid      like -l, but list numeric user and group IDs
  -N, --literal              print entry names without quoting
  -o                         like -l, but do not list group information
  -p, --indicator-style=slash
                             append / indicator to directories
  -q, --hide-control-chars   print ? instead of nongraphic characters
      --show-control-chars   show nongraphic characters as-is (the default,
                             unless program is 'ls' and output is a terminal)

  -Q, --quote-name           enclose entry names in double quotes
      --quoting-style=WORD   use quoting style WORD for entry names:
                             literal, locale, shell, shell-always,
                             shell-escape, shell-escape-always, c, escape
                             (overrides QUOTING_STYLE environment variable)

  -r, --reverse              reverse order while sorting
  -R, --recursive            list subdirectories recursively
  -s, --size                 print the allocated size of each file, in blocks
  -S                         sort by file size, largest first
      --sort=WORD            sort by WORD instead of name: none (-U), size (-S),
                             time (-t), version (-v), extension (-X), width

      --time=WORD            select which timestamp used to display or sort;
                               access time (-u): atime, access, use;
                               metadata change time (-c): ctime, status;
                               modified time (default): mtime, modification;
                               birth time: birth, creation;
                             with -l, WORD determines which time to show;
                             with --sort=time, sort by WORD (newest first)

      --time-style=TIME_STYLE
                             time/date format with -l; see TIME_STYLE below
  -t                         sort by time, newest first; see --time
  -T, --tabsize=COLS         assume tab stops at each COLS instead of 8
  -u                         with -lt: sort by, and show, access time;
                             with -l: show access time and sort by name;
                             otherwise: sort by access time, newest first

  -U                         do not sort; list entries in directory order
  -v                         natural sort of (version) numbers within text
  -w, --width=COLS           set output width to COLS.  0 means no limit
  -x                         list entries by lines instead of by columns
  -X                         sort alphabetically by entry extension
  -Z, --context              print any security context of each file
      --zero                 end each output line with NUL, not newline
  -1                         list one file per line
      --help        display this help and exit
      --version     output version information and exit

The SIZE argument is an integer and optional unit (example: 10K is 10*1024).
Units are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).
Binary prefixes can be used, too: KiB=K, MiB=M, and so on.

The TIME_STYLE argument can be full-iso, long-iso, iso, locale, or +FORMAT.
FORMAT is interpreted like in date(1).  If FORMAT is FORMAT1<newline>FORMAT2,
then FORMAT1 applies to non-recent files and FORMAT2 to recent files.
TIME_STYLE prefixed with 'posix-' takes effect only outside the POSIX locale.
Also the TIME_STYLE environment variable sets the default style to use.

The WHEN argument defaults to 'always' and can also be 'auto' or 'never'.

Using color to distinguish file types is disabled both by default and
with --color=never.  With --color=auto, ls emits color codes only when
standard output is connected to a terminal.  The LS_COLORS environment
variable can change the settings.  Use the dircolors(1) command to set it.

Exit status:
 0  if OK,
 1  if minor problems (e.g., cannot access subdirectory),
 2  if serious trouble (e.g., cannot access command-line argument).

GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
Report any translation bugs to <https://translationproject.org/team/>
Full documentation <https://www.gnu.org/software/coreutils/ls>
or available locally via: info '(coreutils) ls invocation'
```





# Reference

[Linux pwd命令教程：如何查看当前工作目录（附实例教程和注意事项）_实验linux查看你当前的工作目录-CSDN博客](https://blog.csdn.net/u012964600/article/details/135240689#:~:text=pwd命令概述pwd#:~:text=pwd命令概述pwd)

