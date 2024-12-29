# MIT实验笔记冲刺2 实验部分

​	下面就是实验的部分，Lab2中的实验有两个。一个是syscall implementations，另一个则是利用未抹除的内存内容来读取上一个内存留下的东西。

## 实现trace调用（系统调用跟踪（中等））

​	在此作业中，您将添加一个系统调用跟踪功能，该功能可能有助于您调试后续实验。您将创建一个新的跟踪系统调用来控制跟踪。它应该接受一个参数，即一个整数“掩码”，其位指定要跟踪哪些系统调用。例如，要跟踪 fork 系统调用，程序会调用 trace(1 << SYS_fork)，其中 SYS_fork 是 kernel/syscall.h 中的系统调用号。如果系统调用的编号在掩码中设置，则必须修改 xv6 内核以在每个系统调用即将返回时打印一行。该行应包含进程 ID、系统调用的名称和返回值；您不需要打印系统调用参数。跟踪系统调用应该为调用它的进程以及它随后分叉的任何子进程启用跟踪，但不应影响其他进程。

​	我们提供了一个跟踪用户级程序，该程序运行另一个启用跟踪的程序（请参阅 user/trace.c）。完成后，您应该看到如下输出：

```

$ trace 32 grep hello README
3: syscall read -> 1023
3: syscall read -> 966
3: syscall read -> 70
3: syscall read -> 0
$
$ trace 2147483647 grep hello README
4: syscall trace -> 0
4: syscall exec -> 3
4: syscall open -> 3
4: syscall read -> 1023
4: syscall read -> 966
4: syscall read -> 70
4: syscall read -> 0
4: syscall close -> 0
$
$ grep hello README
$
$ trace 2 usertests forkforkfork
usertests Starting
test forkforkfork: 407: syscall fork -> 408
408: syscall fork -> 409
409: syscall fork -> 410
410: syscall fork -> 411
409: syscall fork -> 412
410: syscall fork -> 413
409: syscall fork -> 414
411: syscall fork -> 415
...
$
```

​	在上面的第一个例子中，trace 调用 grep 仅跟踪 read 系统调用。32 是 1<<SYS_read。在第二个例子中，trace 在跟踪所有系统调用时运行 grep；2147483647 的所有 31 个低位均已设置。在第三个例子中，程序未被跟踪，因此没有打印任何跟踪输出。在第四个示例中，正在跟踪 usertests 中 forkforkfork 测试的所有后代的 fork 系统调用。如果您的程序的行为如上所示（尽管进程 ID 可能不同），则您的解决方案是正确的。

一些提示：

- 将 $U/_trace 添加到 Makefile 中的 UPROGS

- 运行 make qemu，您将看到编译器无法编译 user/trace.c，因为跟踪系统调用的用户空间存根尚不存在：将 trace 的原型添加到 user/user.h，将存根添加到 user/usys.pl，并将系统调用号添加到 kernel/syscall.h。Makefile 调用 perl 脚本 user/usys.pl，该脚本生成 user/usys.S，即实际的系统调用存根，它使用 RISC-V ecall 指令转换到内核。修复编译问题后，运行 trace 32 grep hello README；它将失败，因为您尚未在内核中实现系统调用。

- 在 kernel/sysproc.c 中添加一个 sys_trace() 函数，该函数通过在 proc 结构中的新变量中记住其参数来实现新的系统调用（请参阅 kernel/proc.h）。从用户空间检索系统调用参数的函数位于 kernel/syscall.c 中，您可以在 kernel/sysproc.c 中看到它们的使用示例。将您的新 sys_trace 添加到 kernel/syscall.c 中的 syscalls 数组中。

- 修改 fork()（请参阅 kernel/proc.c）以将跟踪掩码从父进程复制到子进程。
- 修改 kernel/syscall.c 中的 syscall() 函数以打印跟踪输出。您需要添加一个系统调用名称数组以进行索引。

​	本次实验的难度还好，只需要一步一步跟着走就好了。首先，我们需要做的就是在user.h加上原型：

> user.h（提供一个接口跳转）

```
...
/* trace call */
int trace(int);
```

> usys.pl
> 这个脚本生成riscv跳转汇编跳转道对应的systable上去

```
...
# trace call entry
entry("trace");
```

>syscall.h
>
>我们当然还需要系统调用号

```
// syscall of the trace
#define SYS_trace  22
```

​	然后辅助完成声明，以及我们需要trace实现的系统调用名称

```
// Prototypes for the functions that handle system calls.
...
extern uint64 sys_trace(void);

static const char* syscall_name_table[] = {
  "", /* blank syscall */
  "fork",
  "exit",
  "wait",
  "pipe",
  "read",
  "kill",
  "exec",
  "fstat",
  "chdir",
  "dup",
  "getpid",
  "sbrk",
  "sleep",
  "uptime",
  "open",
  "write",
  "mknod",
  "unlink",
  "link",
  "mkdir",
  "close",
  "trace",
};


// An array mapping syscall numbers from syscall.h
// to the function that handles the system call.
static uint64 (*syscalls[])(void) = {
...
// add this for the syscall callable
[SYS_trace]   sys_trace,
};
```

​	当然下一步就是要辅助记住我们设置的mask，这个需要在sys_trace中完成。第一步就是按照提示所说的，在proc上添加一个

```
struct proc{
...
	int proc_trace_mask; // using in sys_trace
};
```

​	在发起sys_trace的时候就为它赋值：

```
// trace the functions
uint64
sys_trace(void)
{
  /* fetch the params to gain the mask of trace */
  int mask = 0;
  /* browse the code of argint in syscall.c */
  argint(0, &mask);
  if(mask < 0){
    return -1;
  }

  myproc()->proc_trace_mask = mask;
  return 0;
}
```

​	以及fork的时候要拷贝我们的参数：

```
// Create a new process, copying the parent.
// Sets up child kernel stack to return as if from fork() system call.
int
fork(void)
{
	...
	/* copy the mask */
  np->proc_trace_mask = p->proc_trace_mask;

  return pid;
}
```

​	最后一步，魔改我们的syscall:

```
void
syscall(void)
{
  int num;
  struct proc *p = myproc();

  num = p->trapframe->a7;

  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    // Use num to lookup the system call function for num, call it,
    // and store its return value in p->trapframe->a0
    p->trapframe->a0 = syscalls[num]();

    // now trace the system call if is required
    if((1 << num) & p->proc_trace_mask){
      printf("%d: syscall %s -> %ld\n", 
            p->pid,                   // pid 
            syscall_name_table[num],  // system call name
            p->trapframe->a0);        // the return value
    }

  } else {
    printf("%d %s: unknown sys call %d\n",
            p->pid, p->name, num);
    p->trapframe->a0 = -1;
  }
}
```

​	完事！

```
== Test trace 32 grep == trace 32 grep: OK (3.8s) 
== Test trace close grep == trace close grep: OK (1.0s) 
== Test trace exec + open grep == trace exec + open grep: OK (1.0s) 
== Test trace all grep == trace all grep: OK (1.0s) 
== Test trace nothing == trace nothing: OK (1.0s) 
== Test trace children == trace children: OK (15.1s) 
```

## 攻击 xv6（中等）

​	xv6 内核将用户程序彼此隔离，并将内核与用户程序隔离。正如您在上面的作业中看到的，应用程序不能直接调用内核或其他用户程序中的函数；相反，交互只能通过系统调用进行。但是，如果系统调用的实现中存在错误，攻击者可能能够利用该错误打破隔离边界。为了了解如何利用错误，我们在 xv6 中引入了一个错误，您的目标是利用该错误诱使 xv6 泄露另一个进程的秘密。

​	错误是，在编译此实验时，省略了对 kernel/vm.c 中第 272 行的 memset(mem, 0, sz) 的调用以清除新分配的页面。同样，在为本实验编译 kernel/kalloc.c 时，省略了使用 memset 将垃圾放入空闲页面的两行。省略这 3 行（全部由 ifndef LAB_SYSCALL 标记）的净效果是新分配的内存保留了其先前使用的内容。

​	user/secret.c 在其内存中写入一个 8 字节的秘密，然后退出（释放其内存）。您的目标是向 user/attack.c 添加几行代码以查找 secret.c 先前执行写入内存的秘密，并将 8 个秘密字节写入文件描述符 2。如果 attacktest 打印：“OK：secret is ebb.ebb”，您将获得全部积分。（注意：每次运行 attacktest 时秘密可能不同。）

​	您可以修改 user/attack.c，但不能进行任何其他更改：您不能修改 xv6 内核源代码、secret.c、attacktest.c 等。

一些提示：

在 xv6 shell 中运行 attacktest。它应该输出以下内容：

```
$ attacktest
FAIL：没有/不正确的秘密
```

​	请注意，尽管删除了 3 行，但 xv6 似乎可以正常工作：它启动了 shell 并运行了 attacktest。事实上，如果你运行 usertests，它们中的大多数都会通过！阅读 user/attacktest.c。它生成一个随机的 8 字节字符串，并将其传递给程序 secret，后者将其写入其内存中。secret 退出后，attacktest 生成攻击并等待攻击将秘密字符串写入文件描述符 2。
阅读 user/secret.c 并思考如何诱骗 xv6 向 attack.c 透露秘密。通过在 xv6 shell 中运行 attacktest 来测试你的漏洞。
​	user/secret.c 将秘密字节复制到地址为页面开始后 32 字节的内存中。将 32 更改为 0，你应该会看到你的攻击不再起作用；为什么不呢？一些小错误不会直接影响正确性，但仍可能被利用来破坏安全性（如上文所述），这让内核编程变得具有挑战性。xv6 很可能存在此类错误，尽管我们尽量避免。真正的内核比 xv6 的代码行多得多，这类错误由来已久。例如，请参阅公开的 Linux 漏洞和如何报告漏洞。

​	笔者这里因为没有熟悉过risc-v架构的页表分配等，实际上参考的是这位大佬：

[xv6-lab-2024 lab2 Attack最详细解答_xv6 attack lab-CSDN博客](https://blog.csdn.net/weixin_42543071/article/details/143351746)

​	的解答，看官可以自行前往了解原理，笔者的实现放在这里：

```
#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int
main(int argc, char *argv[])
{
  if(argc != 1){
    printf("usage: attack");
    exit(0);
  }
  char *end = sbrk(PGSIZE*32);
  end = end + 16 * PGSIZE;			/* 为什么是第十七页参考推介的博客 */
  printf("secret: %s\n", end + 32);
  write(2, end+32, 8);
  exit(1);
}
```

