# Linux内核源码阅读——CFS调度

​	我们思考的问题很简单：用户进程的页表何时分配？CFS是什么，里面的概念如何呢？

​	Linux操作系统是一个通用操作系统，是最大力度支持几乎所有形式的进程：比如说RT进程，交互进程，批处理等。

- 交互进程：与外界交互的进程，比如说鼠标，键盘等，比如说我们开一个shell终端启动的进程，在执行过程中，需要与用户进行交互操作，可以运行于前台，也可以运行在后台。

- 批处理进程：该进程是一个进程集合，负责按顺序启动其他的进程。
- 实时进程：非常强调实时性，也就是说我们要求必须在若干时间内完成任务。
- 守护进程：守护进程是一直运行的一种进程，经常在linux系统启动时启动，在系统关闭时终止。它们独立于控制终端并且周期性的执行某种任务或等待处理某些发生的事件。例如httpd进程，一直处于运行状态，等待用户的访问。还有经常用的crond进程，这个进程类似与windows的计划任务，可以周期性的执行用户设定的某些任务。

​	调度上分为Deadline, RealTime，CFS和idel四种：

#### Deadline Scheduling

​	Deadline Scheduling 主要用于**实时系统**，其目标是确保任务在规定的截止时间内完成。任务通常由两个关键参数定义：执行时间和截止时间。调度算法根据任务的紧迫性（即截止时间）来决定哪个任务应当被优先执行。最常见的策略是最早截止时间优先（EDF）调度，它会选择下一个截止时间最早的任务进行调度。

​	他的特征很简单：**实时性**：能够满足实时任务的时间要求，确保任务在截止时间前完成；**灵活性**：在动态环境中能够适应任务的变化；**高效性**：在可调度任务的情况下，EDF 能实现最大的 CPU 利用率。

​	同时还需注意的是：调度上不可以**超负荷**：在系统超负荷时，可能会导致任务未能按时完成，且难以进行分析；对于动态系统，实现和维护都比较复杂，需要考虑到任务间的相互影响。也就是说进程协作很差。

#### Real-Time Scheduling

​	实时调度是一种广泛用于嵌入式系统和操作系统的调度策略，专门设计用来处理时间敏感的任务。实时调度可以分为硬实时调度和软实时调度。硬实时调度要求任务必须在规定的时间内完成，而软实时调度则允许一定的延迟。

​	这种伴随场景可以反过来猜出我们的这样的调度是具备**适应性强**：能够适应各种不同的实时需求，适合多种实时应用；以及**关键任务保证可靠的**：确保重要任务的执行，适合于医疗、航空等安全关键领域。

​	但是这样的调度是非硬实时的，意味着：当多个任务竞争资源时，可能导致延迟，相应的硬件开销也不小

#### Completely Fair Scheduler (CFS)

​	CFS 是 Linux 操作系统的调度算法，它的核心理念是“完全公平”。CFS 通过维护一个红黑树来跟踪进程的运行时间，每个进程在其“虚拟运行时间”上进行比较，以确定下一个应该执行的进程。CFS 确保所有任务的运行时间比例相等，因此其设计目标是优化系统的响应时间和吞吐量。

​	正如Fair所说，它保证每个任务都能公平地获取 CPU 时间，避免某些任务饥饿。同时也能确保相当出色的交互性。保证我们可以快速跟系统进行交互。

​	然而，他对短任务不太友好：可能会引入额外的延迟。相较于传统的调度算法，CFS 的实现较为复杂，需要更多的管理和维护。

#### Idle Scheduling

​	Idle Scheduling 是一种低优先级调度策略，主要在系统 CPU 空闲时调度低优先级任务。这种策略的核心是充分利用系统空闲时间，以执行背景任务或低优先级的计算。一般在系统空闲时执行这些任务，而不会干扰到高优先级任务的执行。

​	特点是简单的：**资源利用率高**：充分利用 CPU 空闲时间，提高整体资源利用率。**不会影响高优先级任务**：低优先级任务的执行不会对实时任务的响应产生影响。

​	所以，这样的调度策略跟RT调度冲突：可能会导致低优先级任务在高负载情况下得不到及时执行。以及在高负载时可能存在延迟，影响低优先级任务的及时性。

​	有这些调度策略，怎么使用呢？很简单：对于用户层那就是设置就行：对应的宏是：

1. **SCHED_NORMAL**: 默认的时间共享调度策略，通常用于非实时任务。
2. **SCHED_FIFO**: 实时调度策略，具有最高优先级，适用于需要严格实时性的任务。FIFO 策略是先到先服务的。
3. **SCHED_RR**: 实时调度策略，采用轮转的方式，每个任务在其时间片内运行，时间片用完后，任务会被置于队尾。
4. **SCHED_BATCH**: 针对批处理任务的调度策略，允许这些任务在系统负载较高时使用更多的 CPU 资源。
5. **SCHED_IDLE**: 用于低优先级的任务，系统空闲时运行这些任务，适用于后台工作。
6. **SCHED_DEADLINE**:这就是死期调度

## 开看源码

​	让我们移步到

>include/uapi/linux/sched.h

```
/*
 * Scheduling policies
 */
#define SCHED_NORMAL		0
#define SCHED_FIFO		1
#define SCHED_RR		2
#define SCHED_BATCH		3
/* SCHED_ISO: reserved but not implemented yet */
#define SCHED_IDLE		5
#define SCHED_DEADLINE		6

/* Can be ORed in to make sure the process is reverted back to SCHED_NORMAL on fork */
#define SCHED_RESET_ON_FORK     0x40000000

/*
 * For the sched_{set,get}attr() calls
 */
#define SCHED_FLAG_RESET_ON_FORK	0x01
#define SCHED_FLAG_RECLAIM		0x02
#define SCHED_FLAG_DL_OVERRUN		0x04
#define SCHED_FLAG_KEEP_POLICY		0x08
#define SCHED_FLAG_KEEP_PARAMS		0x10
#define SCHED_FLAG_UTIL_CLAMP_MIN	0x20
#define SCHED_FLAG_UTIL_CLAMP_MAX	0x40

#define SCHED_FLAG_KEEP_ALL	(SCHED_FLAG_KEEP_POLICY | \
				 SCHED_FLAG_KEEP_PARAMS)

#define SCHED_FLAG_UTIL_CLAMP	(SCHED_FLAG_UTIL_CLAMP_MIN | \
				 SCHED_FLAG_UTIL_CLAMP_MAX)

#define SCHED_FLAG_ALL	(SCHED_FLAG_RESET_ON_FORK	| \
			 SCHED_FLAG_RECLAIM		| \
			 SCHED_FLAG_DL_OVERRUN		| \
			 SCHED_FLAG_KEEP_ALL		| \
			 SCHED_FLAG_UTIL_CLAMP)
```

​	这里就给出了所有的调度策略。我们就是使用这里指示的内容设置我们应该如何设置调度策略。

​	很好，我们知道了调度策略，调度呢？

​	先不着急，我们知道想要调度，就必须量化每一个调度实体的指标如何。任何搞过Linux编程的都知道一个东西叫做nice值！

​	我们都知道nice值的范围是- 19 到 20，事实上，nice值有140个。但是低nice值（0 - 99）分配给了实时进程去了。从100开始才是用户进程的nice值。

​	nice值就是内核在使用的吗？非也！让我们打开源文件定位到文件：

>include/linux/sched.h

```
struct task_struct {
	...
	int				on_rq;

	int				prio;
	int				static_prio;
	int				normal_prio;
	unsigned int			rt_priority;
	...
```

​	在这里！我们的static_prio和normal_prio就是在描述我们的进程优先级问题。

>**`int prio;`**
>
>- 表示当前进程的调度优先级。调度器使用这个值来决定哪个进程将获得 CPU 资源。
>
>**`int static_prio;`**
>
>- 表示进程的静态优先级。这个优先级通常在进程创建时根据其 nice 值或调度策略设定，且在运行时不会改变。
>
>**`int normal_prio;`**
>
>- 这是正常优先级，通常用于时间共享进程，受 nice 值的影响。它可能在进程的生命周期中变化，特别是在调度策略调整时。
>
>**`unsigned int rt_priority;`**
>
>- 表示实时优先级，仅适用于实时进程（如 SCHED_FIFO 和 SCHED_RR）。实时优先级通常在 1 到 99 之间，值越小表示优先级越高。

​	OK，我想大家猜出来nice值是怎么回事了：

>include/linux/sched.h

```
/**
 * task_nice - return the nice value of a given task.
 * @p: the task in question.
 *
 * Return: The nice value [ -20 ... 0 ... 19 ].
 */
static inline int task_nice(const struct task_struct *p)
{
	return PRIO_TO_NICE((p)->static_prio);
}
```

```

#define MAX_NICE	19
#define MIN_NICE	-20
#define NICE_WIDTH	(MAX_NICE - MIN_NICE + 1)

/*
 * Priority of a process goes from 0..MAX_PRIO-1, valid RT
 * priority is 0..MAX_RT_PRIO-1, and SCHED_NORMAL/SCHED_BATCH
 * tasks are in the range MAX_RT_PRIO..MAX_PRIO-1. Priority
 * values are inverted: lower p->prio value means higher priority.
 */

#define MAX_RT_PRIO		100

#define MAX_PRIO		(MAX_RT_PRIO + NICE_WIDTH)
#define DEFAULT_PRIO		(MAX_RT_PRIO + NICE_WIDTH / 2)

/*
 * Convert user-nice values [ -20 ... 0 ... 19 ]
 * to static priority [ MAX_RT_PRIO..MAX_PRIO-1 ],
 * and back.
 */
#define NICE_TO_PRIO(nice)	((nice) + DEFAULT_PRIO)
#define PRIO_TO_NICE(prio)	((prio) - DEFAULT_PRIO)
```

​	可以看到我们的nice值就是简单的做了线性映射。这也就是static_prio的作用，给我们的进程先给予一个最基本的初始优先级。下一步就是移交给normal_prio来计算给予不同调度策略得到的优先级。

​	那调度策略的事情又该如何量化呢？答案是load_weight结构体：

```
struct load_weight {
	unsigned long			weight;
	u32				inv_weight;
};
```

​	这里我们需要一个计算矩阵：

>kernel/sched/core.c

```

/*
 * Nice levels are multiplicative, with a gentle 10% change for every
 * nice level changed. I.e. when a CPU-bound task goes from nice 0 to
 * nice 1, it will get ~10% less CPU time than another CPU-bound task
 * that remained on nice 0.
 *
 * The "10% effect" is relative and cumulative: from _any_ nice level,
 * if you go up 1 level, it's -10% CPU usage, if you go down 1 level
 * it's +10% CPU usage. (to achieve that we use a multiplier of 1.25.
 * If a task goes up by ~10% and another task goes down by ~10% then
 * the relative distance between them is ~25%.)
 */
const int sched_prio_to_weight[40] = {
 /* -20 */     88761,     71755,     56483,     46273,     36291,
 /* -15 */     29154,     23254,     18705,     14949,     11916,
 /* -10 */      9548,      7620,      6100,      4904,      3906,
 /*  -5 */      3121,      2501,      1991,      1586,      1277,
 /*   0 */      1024,       820,       655,       526,       423,
 /*   5 */       335,       272,       215,       172,       137,
 /*  10 */       110,        87,        70,        56,        45,
 /*  15 */        36,        29,        23,        18,        15,
};

/*
 * Inverse (2^32/x) values of the sched_prio_to_weight[] array, pre-calculated.
 *
 * In cases where the weight does not change often, we can use the
 * pre-calculated inverse to speed up arithmetics by turning divisions
 * into multiplications:
 */
const u32 sched_prio_to_wmult[40] = {
 /* -20 */     48388,     59856,     76040,     92818,    118348,
 /* -15 */    147320,    184698,    229616,    287308,    360437,
 /* -10 */    449829,    563644,    704093,    875809,   1099582,
 /*  -5 */   1376151,   1717300,   2157191,   2708050,   3363326,
 /*   0 */   4194304,   5237765,   6557202,   8165337,  10153587,
 /*   5 */  12820798,  15790321,  19976592,  24970740,  31350126,
 /*  10 */  39045157,  49367440,  61356676,  76695844,  95443717,
 /*  15 */ 119304647, 148102320, 186737708, 238609294, 286331153,
};

```

​	现在我们只需要查表做映射即可。

```
void set_load_weight(struct task_struct *p, bool update_load)
{
	int prio = p->static_prio - MAX_RT_PRIO;
	struct load_weight lw;

	if (task_has_idle_policy(p)) {
		lw.weight = scale_load(WEIGHT_IDLEPRIO);
		lw.inv_weight = WMULT_IDLEPRIO;
	} else {
		lw.weight = scale_load(sched_prio_to_weight[prio]);
		lw.inv_weight = sched_prio_to_wmult[prio];
	}

	/*
	 * SCHED_OTHER tasks have to update their load when changing their
	 * weight
	 */
	if (update_load && p->sched_class == &fair_sched_class)
		reweight_task(p, &lw);
	else
		p->se.load = lw;
}
```

​	下一步就是使用prio结合CFS的特点定位进程的真正优先级了：

>include/linux/sched.h

```
struct sched_entity {
	/* For load-balancing: */
	struct load_weight		load;
	struct rb_node			run_node;
	u64				deadline;
	u64				min_vruntime;

	struct list_head		group_node;
	unsigned int			on_rq;

	u64				exec_start;
	u64				sum_exec_runtime;
	u64				prev_sum_exec_runtime;
	u64				vruntime;
	s64				vlag;
	u64				slice;

	u64				nr_migrations;

#ifdef CONFIG_FAIR_GROUP_SCHED
	int				depth;
	struct sched_entity		*parent;
	/* rq on which this entity is (to be) queued: */
	struct cfs_rq			*cfs_rq;
	/* rq "owned" by this entity/group: */
	struct cfs_rq			*my_q;
	/* cached value of my_q->h_nr_running */
	unsigned long			runnable_weight;
#endif

#ifdef CONFIG_SMP
	/*
	 * Per entity load average tracking.
	 *
	 * Put into separate cache line so it does not
	 * collide with read-mostly values above.
	 */
	struct sched_avg		avg;
#endif
};
```

​	vruntime表达的是进程的运行虚拟时间。它比实际的运行时间就多加考虑了一个要素：那就是进程的优先级。比如说如果我们想要根据进程的运行时间调度，优先级较高的进程（nice 值低）会有较低的 `vruntime`，使得它们更容易被调度。

#### 计算方法

**权重计算**：

- 每个进程的权重 `weight` 是基于其 nice 值计算得出的： 
  $$
  weight=MAX\_PRI−nice\_value
  $$
  其中 `MAX_PRI` 通常为 40。

**倒数权重**：

- 计算进程的 `inv_weight`（倒数权重）： 
  $$
  inv\_weight = \frac{1}{weight}
  $$
  

**vruntime 增加**：在进程运行时，`vruntime` 的增加量是基于 `inv_weight` 的： 
$$
delta\_vruntime=delta\_time×inv\_weight
$$
这里 `delta_time` 是进程在 CPU 上实际运行的时间。CFS 在调度时选择具有最低 `vruntime` 的进程进行执行。现在我们就是按照vruntime对CFS调度树进行调度移动节点。从而实现了CFS调度

>kernel/sched/fair.c

```
/*
 * delta_exec * weight / lw.weight	计算公式就在这里。
 *   OR
 * (delta_exec * (weight * lw->inv_weight)) >> WMULT_SHIFT
 *
 * Either weight := NICE_0_LOAD and lw \e sched_prio_to_wmult[], in which case
 * we're guaranteed shift stays positive because inv_weight is guaranteed to
 * fit 32 bits, and NICE_0_LOAD gives another 10 bits; therefore shift >= 22.
 *
 * Or, weight =< lw.weight (because lw.weight is the runqueue weight), thus
 * weight/lw.weight <= 1, and therefore our shift will also be positive.
 */
static u64 __calc_delta(u64 delta_exec, unsigned long weight, struct load_weight *lw)
{
	u64 fact = scale_load_down(weight);
	u32 fact_hi = (u32)(fact >> 32);
	int shift = WMULT_SHIFT;
	int fs;

	__update_inv_weight(lw);

	if (unlikely(fact_hi)) {
		fs = fls(fact_hi);
		shift -= fs;
		fact >>= fs;
	}

	fact = mul_u32_u32(fact, lw->inv_weight);

	fact_hi = (u32)(fact >> 32);
	if (fact_hi) {
		fs = fls(fact_hi);
		shift -= fs;
		fact >>= fs;
	}

	return mul_u64_u32_shr(delta_exec, fact, shift);
}

/*
 * delta /= w
 */
static inline u64 calc_delta_fair(u64 delta, struct sched_entity *se)
{
	if (unlikely(se->load.weight != NICE_0_LOAD))
		delta = __calc_delta(delta, NICE_0_LOAD, &se->load);

	return delta;
}
```

​	这就是来头。

> 注意到技巧：内核为了节约时间，不会采用耗费时间的除法操作而是直接采用打表的方式直接给出权重的倒数从而进行方便的运算。

## CFS数据结构

​	关于CFS数据结构设计简单的说一嘴：在我们的sched.h下定义了一系列的结构体：

### rq

​	先来说说rq: running queue队列：

```
/*
 * This is the main, per-CPU runqueue data structure.
 *
 * Locking rule: those places that want to lock multiple runqueues
 * (such as the load balancing or the thread migration code), lock
 * acquire operations must be ordered by ascending &runqueue.
 */
struct rq {
	/* runqueue lock: */
	raw_spinlock_t		__lock; // 运行队列的锁，确保对运行队列的操作是线程安全的。

	unsigned int		nr_running; // 表示当前可运行的进程数量。
#ifdef CONFIG_NUMA_BALANCING	// 这里表达是如果配置了NUMA负载均衡（一大堆CPU需要协调调度）
	unsigned int		nr_numa_running; // 这些是与非统一内存访问（NUMA）相关的字段，用于优化进程在多处理器系统中的调度。
	unsigned int		nr_preferred_running; // 这些是与非统一内存访问（NUMA）相关的字段，用于优化进程在多处理器系统中的调度。
	unsigned int		numa_migrate_on;
#endif
#ifdef CONFIG_NO_HZ_COMMON	// 用于处理无时钟更新的调度情况。无关时钟配置！
#ifdef CONFIG_SMP
	unsigned long		last_blocked_load_update_tick;
	unsigned int		has_blocked_load;
	call_single_data_t	nohz_csd;
#endif /* CONFIG_SMP */
	unsigned int		nohz_tick_stopped;
	atomic_t		nohz_flags;
#endif /* CONFIG_NO_HZ_COMMON */

#ifdef CONFIG_SMP	// 用于支持对称多处理（SMP），跟踪状态和进程迁移。
	unsigned int		ttwu_pending;
#endif
	u64			nr_switches;

#ifdef CONFIG_UCLAMP_TASK
	/* Utilization clamp values based on CPU's RUNNABLE tasks */
	struct uclamp_rq	uclamp[UCLAMP_CNT] ____cacheline_aligned;
	unsigned int		uclamp_flags;
#define UCLAMP_FLAG_IDLE 0x01
#endif
	// cfs, rt, 和 dl 分别代表完全公平调度、实时调度和延迟调度的就绪队列。
	struct cfs_rq		cfs;
	struct rt_rq		rt;
	struct dl_rq		dl;

#ifdef CONFIG_FAIR_GROUP_SCHED
	/* list of leaf cfs_rq on this CPU: */
	struct list_head	leaf_cfs_rq_list;
	struct list_head	*tmp_alone_branch;
#endif /* CONFIG_FAIR_GROUP_SCHED */

	/*
	 * This is part of a global counter where only the total sum
	 * over all CPUs matters. A task can increase this counter on
	 * one CPU and if it got migrated afterwards it may decrease
	 * it on another CPU. Always updated under the runqueue lock:
	 */
	/*
	nr_uninterruptible：表示当前在不可中断状态下的进程数量。
	curr：指向当前正在运行的任务的指针。
	idle：指向空闲进程的指针。
	stop：指向停止进程的指针。
	clock_update_flags：用于更新时钟的标志。
	clock：表示当前时钟的值。
	*/ 
	unsigned int		nr_uninterruptible;

	struct task_struct __rcu	*curr;
	struct task_struct	*idle;
	struct task_struct	*stop;
	unsigned long		next_balance;
	struct mm_struct	*prev_mm;

	unsigned int		clock_update_flags;
	u64			clock;
	/* Ensure that all clocks are in the same cache line */
	u64			clock_task ____cacheline_aligned;
	u64			clock_pelt;
	unsigned long		lost_idle_time;
	u64			clock_pelt_idle;
	u64			clock_idle;
#ifndef CONFIG_64BIT
	u64			clock_pelt_idle_copy;
	u64			clock_idle_copy;
#endif

	atomic_t		nr_iowait;

#ifdef CONFIG_SCHED_DEBUG	// debug用的
	u64 last_seen_need_resched_ns;
	int ticks_without_resched;
#endif

#ifdef CONFIG_MEMBARRIER	// 内存屏障开了吗？
	int membarrier_state;
#endif

#ifdef CONFIG_SMP	// SMP支持
	struct root_domain		*rd;
	struct sched_domain __rcu	*sd;

	unsigned long		cpu_capacity;

	struct balance_callback *balance_callback;

	unsigned char		nohz_idle_balance;
	unsigned char		idle_balance;

	unsigned long		misfit_task_load;

	/* For active balancing */
	int			active_balance;
	int			push_cpu;
	struct cpu_stop_work	active_balance_work;

	/* CPU of this runqueue: */
	int			cpu;
	int			online;

	struct list_head cfs_tasks;

	struct sched_avg	avg_rt;
	struct sched_avg	avg_dl;
#ifdef CONFIG_HAVE_SCHED_AVG_IRQ
	struct sched_avg	avg_irq;
#endif
#ifdef CONFIG_SCHED_HW_PRESSURE
	struct sched_avg	avg_hw;
#endif
	u64			idle_stamp;
	u64			avg_idle;

	/* This is used to determine avg_idle's max value */
	u64			max_idle_balance_cost;

#ifdef CONFIG_HOTPLUG_CPU
	struct rcuwait		hotplug_wait;
#endif
#endif /* CONFIG_SMP */

// 这里如果开启中断时间记载的话：
// prev_irq_time：上一个中断时间。psi_irq_time：与压力指标相关的IRQ时间。
#ifdef CONFIG_IRQ_TIME_ACCOUNTING
	u64			prev_irq_time;
	u64			psi_irq_time;
#endif
#ifdef CONFIG_PARAVIRT
	u64			prev_steal_time;
#endif
#ifdef CONFIG_PARAVIRT_TIME_ACCOUNTING
	u64			prev_steal_time_rq;
#endif

// CPU负载计算：calc_load_update：记录负载计算的更新状态。calc_load_active：表示当前活动的负载值。
	/* calc_load related fields */
	unsigned long		calc_load_update;
	long			calc_load_active;

#ifdef CONFIG_SCHED_HRTICK
#ifdef CONFIG_SMP
	call_single_data_t	hrtick_csd;
#endif
	struct hrtimer		hrtick_timer;
	ktime_t			hrtick_time;
#endif
// rq_sched_info：调度信息结构体，包含延迟统计等。yld_count、sched_count、sched_goidle：分别表示调用 sys_sched_yield() 的次数、调度次数和空闲次数。
#ifdef CONFIG_SCHEDSTATS
	/* latency stats */
	struct sched_info	rq_sched_info;
	unsigned long long	rq_cpu_time;
	/* could above be rq->cfs_rq.exec_clock + rq->rt_rq.rt_runtime ? */

	/* sys_sched_yield() stats */
	unsigned int		yld_count;

	/* schedule() stats */
	unsigned int		sched_count;
	unsigned int		sched_goidle;

	/* try_to_wake_up() stats */
	unsigned int		ttwu_count;
	unsigned int		ttwu_local;
#endif

#ifdef CONFIG_CPU_IDLE
	/* Must be inspected within a RCU lock section */
	struct cpuidle_state	*idle_state;
#endif

#ifdef CONFIG_SMP
	unsigned int		nr_pinned;
#endif
	unsigned int		push_busy;
	struct cpu_stop_work	push_work;

// 追踪核心调度：core_task_seq、core_pick_seq、core_cookie 等字段用于跟踪核心调度的状态。
#ifdef CONFIG_SCHED_CORE
	/* per rq */
	struct rq		*core;
	struct task_struct	*core_pick;
	unsigned int		core_enabled;
	unsigned int		core_sched_seq;
	struct rb_root		core_tree;

	/* shared state -- careful with sched_core_cpu_deactivate() */
	unsigned int		core_task_seq;
	unsigned int		core_pick_seq;
	unsigned long		core_cookie;
	unsigned int		core_forceidle_count;
	unsigned int		core_forceidle_seq;
	unsigned int		core_forceidle_occupation;
	u64			core_forceidle_start;
#endif

	/* Scratch cpumask to be temporarily used under rq_lock */
	cpumask_var_t		scratch_mask;

#if defined(CONFIG_CFS_BANDWIDTH) && defined(CONFIG_SMP)
	call_single_data_t	cfsb_csd;
	struct list_head	cfsb_csd_list;
#endif
};
```

>这些比较重要：
>
>`nr_running`：表示当前可运行的进程数量。这是一个无符号整数，通常用于调度器确定是否有进程可以被调度执行。
>
>`cfs`：这是一个 `cfs_rq` 类型的结构体，代表完全公平调度（CFS）算法的就绪队列。CFS 是 Linux 内核中的一种调度算法，旨在公平地分配 CPU 时间给所有可运行的进程。
>
>`rt`：这是一个 `rt_rq` 类型的结构体，代表实时调度（RT）队列。实时调度用于优先处理时间敏感的任务，以确保它们在特定的时间内得到执行。
>
>`dl`：这是一个 `dl_rq` 类型的结构体，代表延迟调度（Deadline）队列。它用于调度那些有截止时间要求的任务，确保这些任务能够在其规定的时间内完成。

​	这个是针对每一个cpu都有的结构体，意思是每一个CPU都会维护这样的一个队列

### sched_entity

​	我们管理的是调度实体（线程甚至可能更小！），从而引入调度实体的概念。CFS调度器使用sched_entity达到PELT(per entity load tracking)，即se级别的负载跟踪。调度实体记录权重信息、运行时间信息、负载信息等。

>include/linux/sched.h

```
// 被调度实体（包括两种：①与进程一一对应的调度实体，即一个进程一个调度实体；②组调度实体，一个组对应一个调度实体，一个组里可能包含多个进程(即当前group se包含多个task se)）。
struct sched_entity {
	/* For load-balancing: */
	struct load_weight		load;  // 权重信息，用于计算虚拟时间。

	/*
	 * runnable_weight指可运行权重，该概念主要针对group se提出。
	 * 针对task se来说，runnable_weight的值就是和进程权重weight相等。
	 * 针对group se，runnable_weight总是小于等于weight （其实这话说的像废话，因为一个group se中还有可能存在running状态的task se）。
	 */
	unsigned long			runnable_weight;  // 在所有可运行进程中所占的权重。
	struct rb_node			run_node;  // 调度实体作为一个节点插入到CFS的红黑树中。CFS调度器的每个就绪队列维护了一颗红黑树，上面挂满了就绪等待执行的task，run_node就是挂载点。
	struct list_head		group_node;  // 当前调度实体属于哪一个调度组，是rq中cfs_tasks链表的挂载点。
	unsigned int			on_rq;  // 是否在就绪队列上。进程加入到就绪队列，该位置被置为1；退出就绪队列，被置为0。

	u64				exec_start;  // 上次启动时间
	u64				sum_exec_runtime;  // 当前进程总的CPU消耗时间，这个是真实的CPU消耗时间。
	u64				vruntime;  // 虚拟运行时间
	u64				prev_sum_exec_runtime;  // 进程撤销时会将sum_exec_runtime保存到prev_sum_exec_runtime中。

	u64				nr_migrations;

	struct sched_statistics		statistics;

#ifdef CONFIG_FAIR_GROUP_SCHED  // 组调度启用宏
	int				depth;  // 调度实体的嵌套深度，比如cpu rq的顶层调度实体为task se，则depth等于0；若为greou se中的task调度实体，则此时的task se中的depth为1。
	struct sched_entity		*parent;  // 当前调度实体是task调度实体时，parent指向包含此task调度实体的group调度实体。
	/* rq on which this entity is (to be) queued: */
	struct cfs_rq			*cfs_rq;  // 所属的就绪队，即指向group调度实体的就绪队列cfs_rq。
	/* rq "owned" by this entity/group: */
	struct cfs_rq			*my_q;  // group调度实体的就绪队列。
#endif

#ifdef CONFIG_SMP
	/*
	 * Per entity load average tracking.
	 *
	 * Put into separate cache line so it does not
	 * collide with read-mostly values above.
	 */
	struct sched_avg		avg;  // 负载信息
#endif
};
```

### cfs_rq

​	这个就是cfs队列的实现：

>include/linux/sched.h

```
struct cfs_rq {
	struct load_weight	load;  // 就绪队列权重，即就绪队列管理的所有调度实体权重之和。
	unsigned long		runnable_weight;  // 针对group se提出,是实体权重的一部分，表示rq中可运行实体的权重总和。对于task se来说，runnable_weight就是se的weight，二者的值完全一样。
	unsigned int		nr_running;  // 就绪队列上调度实体的个数（包括task se和group se，比如task se个数为9，group se个数为1，则nr_running为10）。

	// 就绪队列上真实的调度实体的个数（比如当前调度队列上task se个数为9，group se个数为1（group se中包含9个task se，则），则h_nr_running为18）
	unsigned int		h_nr_running;  /* SCHED_{NORMAL,BATCH,IDLE} */  
	unsigned int		idle_h_nr_running; /* SCHED_IDLE */

	u64			exec_clock;

	/*
	 * cfs_rq（csf run queue）中的每一个进程都有一个虚拟时钟，vruntime。
	 * 如果一个进程得以执行，随着时间的增加（一个一个tick的到来），其vruntime将不断增大。
	 * 没有得到执行的进程vruntime不变。调度器总是选择vruntime最小的那个进程来运行(即红黑树最左边的进程)。这就是所谓的“完全公平”。
	 * 为了区别不同优先级的进程，优先级高的进程vruntime增长得慢，以至于它们可以得到更多的运行时间。
	*/
	u64			min_vruntime;  // 跟踪就绪队列上所有调度实体的最小虚拟运行时间。
#ifndef CONFIG_64BIT
	u64			min_vruntime_copy;
#endif

	struct rb_root_cached	tasks_timeline;  // 按照虚拟时间大小排序的红黑树（虚拟运行时间最小的在红黑树的最左边）。

	/*
	 * 'curr' points to currently running entity on this cfs_rq.
	 * It is set to NULL otherwise (i.e when none are currently running).
	 */
	//  sched_entity：可被内核调度的实体
	struct sched_entity	*curr;  // 就绪队列的当前执行进程的可调度实体
	struct sched_entity	*next;
	struct sched_entity	*last;
	struct sched_entity	*skip;

#ifdef	CONFIG_SCHED_DEBUG
	unsigned int		nr_spread_over;
#endif

#ifdef CONFIG_SMP
	/*
	 * CFS load tracking
	 */
	struct sched_avg	avg;  // 负载信息
#ifndef CONFIG_64BIT
	u64			load_last_update_time_copy;
#endif


    /*
	 * 当一个任务退出或者唤醒后迁移到到其他cpu上的时候，那么原本所在CPU的cfs rq上需要移除该任务带来的负载。
	 * 由于持rq锁问题，所以先把移除的负载记录在这个removed成员中，适当的时机再更新之。删除记录函数 remove_entity_load_avg()，实际删除函数 update_cfs_rq_load_avg()。
	 */
	struct {
		raw_spinlock_t	lock ____cacheline_aligned;
		int		nr;
		unsigned long	load_avg;
		unsigned long	util_avg;
		unsigned long	runnable_sum;
	} removed;

#ifdef CONFIG_FAIR_GROUP_SCHED

    /*
	 * 指该group cfs_rq已经向 task group 的load_avg同步的负载值。
	 * 因为tg是一个全局共享变量，多个cpu会同时访问，为了避免严重的资源竞争，group cfs_rq的负载贡献值（运行就更新）不会立即就更新到tg->load_avg（task group的负载总和）。
	 * 而是等到差值大到一定程度，才会再次同步到tg->load_avg；
	 */
	unsigned long		tg_load_avg_contrib;
	long			propagate;
	long			prop_runnable_sum;

	/*
	 *   h_load = weight * f(tg)
	 *
	 * Where f(tg) is the recursive weight fraction assigned to
	 * this group.
	 */
	unsigned long		h_load;
	u64			last_h_load_update;
	struct sched_entity	*h_load_next;
#endif /* CONFIG_FAIR_GROUP_SCHED */
#endif /* CONFIG_SMP */

#ifdef CONFIG_FAIR_GROUP_SCHED
	struct rq		*rq;	/* CPU runqueue to which this cfs_rq is attached ,此cfs_rq附加到的CPU运行队列,即cfs队列所在的全局就绪队列*/

	/*
	 * leaf cfs_rqs are those that hold tasks (lowest schedulable entity in
	 * a hierarchy). Non-leaf lrqs hold other higher schedulable entities
	 * (like users, containers etc.)
	 *
	 * leaf_cfs_rq_list ties together list of leaf cfs_rq's in a CPU.
	 * This list is used during load balance.
	 */
	int			on_list;
	struct list_head	leaf_cfs_rq_list;

	// tg指向就绪队列包含的调度实体属于的task group。
	struct task_group	*tg;	/* group that "owns" this runqueue */  

#ifdef CONFIG_CFS_BANDWIDTH
	int			runtime_enabled;
	s64			runtime_remaining;

	u64			throttled_clock;
	u64			throttled_clock_task;
	u64			throttled_clock_task_time;
	int			throttled;
	int			throttle_count;
	struct list_head	throttled_list;
#endif /* CONFIG_CFS_BANDWIDTH */
#endif /* CONFIG_FAIR_GROUP_SCHED */
};

```

​	每一个成员的含义：

>**load**
>
>- 类型：`struct load_weight`
>- 含义：表示就绪队列中所有调度实体的权重总和，影响调度时的负载均衡。
>
>**runnable_weight**
>
>- 类型：`unsigned long`
>- 含义：就绪队列中可运行调度实体的总权重。对于任务调度实体（task se），该值等于其权重；对于组调度实体（group se），是组内所有任务的权重总和。
>
>**nr_running**
>
>- 类型：`unsigned int`
>- 含义：当前就绪队列上调度实体的数量，包括任务和组调度实体的总和。
>
>**h_nr_running**
>
>- 类型：`unsigned int`
>- 含义：就绪队列上真实的调度实体数量，包括组调度实体中的任务。
>
>**idle_h_nr_running**
>
>- 类型：`unsigned int`
>- 含义：针对空闲调度策略（SCHED_IDLE）的就绪队列中调度实体的数量。
>
>**exec_clock**
>
>- 类型：`u64`
>- 含义：记录调度实体的执行时钟，跟踪运行的时间。
>
>**min_vruntime**
>
>- 类型：`u64`
>- 含义：跟踪就绪队列中所有调度实体的最小虚拟运行时间。调度器选择 `vruntime` 最小的实体运行，以实现公平调度。
>
>**tasks_timeline**
>
>- 类型：`struct rb_root_cached`
>- 含义：红黑树结构，按虚拟运行时间排序，便于高效选择和调度最小 `vruntime` 的实体。
>
>**curr**
>
>- 类型：`struct sched_entity*`
>- 含义：指向当前在该就绪队列上执行的调度实体。如果没有正在执行的实体，该值为 NULL。
>
>**next**
>
>- 类型：`struct sched_entity*`
>- 含义：指向下一个将要执行的调度实体。
>
>**last**
>
>- 类型：`struct sched_entity*`
>- 含义：指向上一个执行的调度实体。
>
>**skip**
>
>- 类型：`struct sched_entity*`
>- 含义：用于调度优化的指针，这个被只想的对象不参与调度
>
>**nr_spread_over**
>
>- 类型：`unsigned int`
>- 含义：在调度调试中使用的计数器，跟踪调度实体的分布情况。
>
>**avg**
>
>- 类型：`struct sched_avg`
>- 含义：每个调度实体的负载平均信息，用于分析和优化CPU负载。
>
>**removed**
>
>- 类型：结构体
>- 含义：跟踪已移除负载的信息，以便在适当时机更新CFS调度队列的负载。
>
>**tg_load_avg_contrib**
>
>- 类型：`unsigned long`
>- 含义：表示组调度实体对任务组负载平均的贡献，避免频繁更新。
>
>**propagate**
>
>- 类型：`long`
>- 含义：用于在负载更新时进行传播的值。
>
>**prop_runnable_sum**
>
>- 类型：`long`
>- 含义：表示可运行任务的总和，用于调度决策。
>
>**h_load**
>
>- 类型：`unsigned long`
>- 含义：表示与权重相关的负载值，考虑任务组的权重分配。
>
>**last_h_load_update**
>
>- 类型：`u64`
>- 含义：记录上次负载更新的时间，用于调度时的负载跟踪。
>
>**h_load_next**
>
>- 类型：`struct sched_entity*`
>- 含义：指向下一个需要更新负载的调度实体。
>
>**rq**
>
>- 类型：`struct rq*`
>- 含义：指向与该CFS调度队列相关联的CPU运行队列。
>
>**on_list**
>
>- 类型：`int`
>- 含义：指示该CFS调度队列是否在某个列表中，通常用于负载均衡。
>
>**leaf_cfs_rq_list**
>
>- 类型：`struct list_head`
>- 含义：链接到CPU中的叶子CFS调度队列，用于负载均衡的目的。
>
>**tg**
>
>- 类型：`struct task_group*`
>- 含义：指向当前调度队列所属的任务组，管理相关任务。
>
>**runtime_enabled**
>
>- 类型：`int`
>- 含义：指示调度实体的运行时间控制是否启用。
>
>**runtime_remaining**
>
>- 类型：`s64`
>- 含义：表示剩余的运行时间，用于调度控制。
>
>**throttled_clock** 等相关字段
>
>- 类型：`u64` 和 `int`
>- 含义：用于跟踪被限制（throttled）任务的时间和次数，管理任务的调度行为。

​	非常长！

# Reference

>https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.11.2.tar.xz
>
>[完全公平调度器 — The Linux Kernel documentation](https://docs.kernel.org/6.11/translations/zh_CN/scheduler/sched-design-CFS.html)
>
>[Linux内核源码分析-进程调度(二)-常用数据结构_linux调度器源码分析(二)-CSDN博客](https://blog.csdn.net/weixin_40179091/article/details/130377051)
>
>chatgpt帮助我节省了一些时间打字