# Linux内核深入学习（3）——内核常见的数据结构1链表

## 前言

​	我们的常用的数据结构，一个是我们的list，另一个是笔者打算之后介绍的rb_tree，也就是红黑树。这里我们先从链表开始说起。

### 内核的链表是双循环链表

​	双循环链表是一种常见的数据结构，它在计算机科学中扮演着灵活组织数据的角色。想象一条由许多环节连接而成的链条，每个环节不仅知道自己的下一个环节在哪里，还能记住前一个环节的位置。这种链条首尾相接，形成一个闭环，就像游乐场的环形小火车，无论从哪个车厢出发，都能沿着轨道绕回起点。这就是双循环链表最直观的样貌。

​	每个节点都像一个小型数据仓库，存储着有价值的信息，同时携带着两把钥匙：一把指向它的前驱节点，另一把指向后继节点。这种双向连接的特性让数据访问变得自由灵活。当我们需要查找某个数据时，既可以从头节点顺时针寻找，也能反向逆时针回溯。这种双向性在需要频繁前后移动的场景中尤其有用，比如音乐播放器的播放列表，既支持切到下一首歌，也能随时返回上一曲。

​	与传统链表不同，双循环链表的首尾节点通过指针紧紧相扣。当链表为空时，头节点的前后指针都指向自己，就像一个孤独的哨兵静静守护着空荡的城堡。随着数据节点的加入，这个闭环会逐渐扩展，但始终保持着循环的特性。这样的设计消除了链表头尾的边界感，使得所有节点都处于平等的位置，操作时无需特别处理首尾边界条件，这在某些算法实现中能显著简化代码逻辑。

​	插入和删除操作是双循环链表的拿手好戏。要新增一个节点，只需调整相邻节点的指针指向，就像在铁链中间插入新环节时重新焊接两端的连接点。删除节点时同样优雅，断开目标节点与邻居的连接后，前后节点会自然牵起手来，整个过程不需要大规模移动数据。这种高效的重构能力让它在需要频繁修改数据的场景中表现出色，比如实时更新的缓存系统或动态规划的解决方案。

​	这里，我们的内核采用的就是经典的双循环链表。很快，我们就来看看内核时如何抽象的。

### list head是什么

```
struct list_head {
	struct list_head *next, *prev;
};
```

​	我们知道，数据结构本身跟数据自身的属性是没有关系的，换而言之，数据本身的组织不应当被采取的容器所影响。你看，C++的`std::list<T>`是使用泛型这样做到的，那问题来了，C咋办呢？我们总不能强硬的将每一个我们关心成一条链的数据结构都整出来重复的链表代码吧！那太冗余！

​	为此，我们的做法是——希望让每一个使用链表组织的数据内部，**侵入一个链表的节点结构体，想要找到链表上的存储的数据，只需要反推这个链表所在的位置对应的偏移头，偏移节点所在结构体的偏移量就能拿到原本结构的头**

```
+===========================+ <===== get the struct itself
|						  |
|	int xxx;			   |
|						  |
|---------------------------| <==== Offset of the struct list_head
| 						  |
| 	struct list_head	    |
|---------------------------|
....
```

​	为此，只需要将list_head的地址剪掉list_head的offset就能拿到结构体了！就是这个原理！现在，我们就能将数据本身和链表解耦合开来了！

### 初始化

- **静态初始化**
   使用宏 `LIST_HEAD(name)` 可在编译期声明并初始化一个空链表头：

  ```
  LIST_HEAD(my_list);
  ```

  等价于：

  ```
  struct list_head my_list = { &my_list, &my_list };
  ```

  我们来看看实际上是如何做的：

  ```
  #define LIST_HEAD_INIT(name) { &(name), &(name) }
  
  #define LIST_HEAD(name) \
  	struct list_head name = LIST_HEAD_INIT(name)
  ```

  嗯很，就是静态的初始化结构体嘛！没啥新鲜的！

- **动态初始化**
   对于已声明的 `struct list_head head;`，可在运行期调用：

  ```
  INIT_LIST_HEAD(&head);
  ```

  将其 `next` 和 `prev` 指向自身，实现空表状态

  ```
  static inline void INIT_LIST_HEAD(struct list_head *list)
  {
  	WRITE_ONCE(list->next, list);
  	WRITE_ONCE(list->prev, list);
  }
  ```

  ​	这里的write_once是一次赋值大小检查和一次真正的赋值行为封装宏。

### 核心操作函数

核心操作都在 `include/linux/list.h` 及 `lib/list.c`（旧版中为 `lib/list.c`，新版本都为宏实现）中定义，主要包括：

- **添加节点**

  - `list_add(new, head)`：将 `new` 添加到 `head` 之后，常用于栈（LIFO）场景。
  - `list_add_tail(new, head)`：将 `new` 添加到 `head` 之前，实现队列（FIFO）效果

  ```c
  /*
   * Insert a new entry between two known consecutive entries.
   *
   * This is only for internal list manipulation where we know
   * the prev/next entries already!
   */
  static inline void __list_add(struct list_head *new,
  			      struct list_head *prev,
  			      struct list_head *next)
  {
  	if (!__list_add_valid(new, prev, next))
  		return;
  
  	next->prev = new;
  	new->next = next;
  	new->prev = prev;
  	WRITE_ONCE(prev->next, new);
  }
  
  /**
   * list_add - add a new entry
   * @new: new entry to be added
   * @head: list head to add it after
   *
   * Insert a new entry after the specified head.
   * This is good for implementing stacks.
   */
  static inline void list_add(struct list_head *new, struct list_head *head)
  {
  	__list_add(new, head, head->next);
  }
  ```

  ​	我们的内核喜欢使用`__T`和`T`隔离实现，这样的方式来保证API的稳定，内部函数`__list_add`如同精密的手术刀，负责在已知的相邻节点`prev`与`next`之间嵌入新节点`new`。它先通过`__list_add_valid`进行安全性校验，随后像编织绳索般调整指针：先将新节点的`next`与`next`节点挂钩，再将新节点的`prev`与`prev`节点相连，最后用`WRITE_ONCE`确保前驱节点的`next`指针原子性地指向新节点，防止多线程环境下的数据竞争。

  外层函数`list_add`则是面向开发者的友好接口，它将新节点直接插入到链表头节点`head`之后。

- **删除节点**

  - `list_del(entry)`：将 `entry` 从所属链表中移除，内部调用 `__list_del(entry->prev, entry->next)` 并将 `entry` 指针置为 UNDEFINED。
  - `list_del_init(entry)`：移除后重新初始化该节点，使其成为单节点空链表。

  ```c
  /*
   * Delete a list entry by making the prev/next entries
   * point to each other.
   *
   * This is only for internal list manipulation where we know
   * the prev/next entries already!
   */
  static inline void __list_del(struct list_head * prev, struct list_head * next)
  {
  	next->prev = prev;
  	WRITE_ONCE(prev->next, next);
  }
  
  /*
   * Delete a list entry and clear the 'prev' pointer.
   *
   * This is a special-purpose list clearing method used in the networking code
   * for lists allocated as per-cpu, where we don't want to incur the extra
   * WRITE_ONCE() overhead of a regular list_del_init(). The code that uses this
   * needs to check the node 'prev' pointer instead of calling list_empty().
   */
  static inline void __list_del_clearprev(struct list_head *entry)
  {
  	__list_del(entry->prev, entry->next);
  	entry->prev = NULL;
  }
  
  static inline void __list_del_entry(struct list_head *entry)
  {
  	if (!__list_del_entry_valid(entry))
  		return;
  
  	__list_del(entry->prev, entry->next);
  }
  
  /**
   * list_del - deletes entry from list.
   * @entry: the element to delete from the list.
   * Note: list_empty() on entry does not return true after this, the entry is
   * in an undefined state.
   */
  static inline void list_del(struct list_head *entry)
  {
  	__list_del_entry(entry);
  	entry->next = LIST_POISON1;
  	entry->prev = LIST_POISON2;
  }
  ```

  **基础指针调整 (`__list_del`)**
  内部函数，通过直接操作相邻节点的指针完成删除：

  - 将后驱节点 `next` 的 `prev` 指向当前节点的前驱 `prev`
  - 使用 `WRITE_ONCE` 宏原子性地更新前驱节点 `prev` 的 `next` 指向 `next`
    此操作仅解除目标节点与链表的连接，不修改目标节点自身指针，适用于已知前后节点的场景。

  **清除前向指针 (`__list_del_clearprev`)**
  在基础删除后，显式将目标节点的 `prev` 置为 `NULL`。该设计针对网络模块的 per-cpu 链表优化，牺牲 `list_empty` 的可用性来减少一次写操作，调用方需通过检测 `prev` 是否为空判断节点状态。

  **带校验的删除 (`__list_del_entry`)**
  对外部暴露的安全接口：

  - 先通过 `__list_del_entry_valid` 验证节点合法性（防止无效操作）
  - 再调用基础 `__list_del` 执行指针调整
    提供基本的防错机制，确保节点确实存在于链表中。

  **完全节点隔离 (`list_del`)**
  标准删除接口：

  - 调用 `__list_del_entry` 解除节点与链表的关联
  - 将节点的 `next`/`prev` 赋值为 `LIST_POISON`（特殊标记值，通常为非法地址）
  - 使被删节点进入"毒化"状态：既无法通过常规方法访问链表，又能在调试时触发错误显式暴露悬空指针访问。

- **移动与拼接**

  - `list_move(entry, head)`、`list_move_tail(entry, head)`：分别将单节点移到另一链表的 head 之后或之前。

  - `list_splice(list, head)`、`list_splice_tail(list, head)`：将整个链表拼接到目标链表中，原链表保留或变为空链表（视 API 而定）

    ```c
    /**
     * list_move - delete from one list and add as another's head
     * @list: the entry to move
     * @head: the head that will precede our entry
     */
    static inline void list_move(struct list_head *list, struct list_head *head)
    {
    	__list_del_entry(list);
    	list_add(list, head);
    }
    
    /**
     * list_move_tail - delete from one list and add as another's tail
     * @list: the entry to move
     * @head: the head that will follow our entry
     */
    static inline void list_move_tail(struct list_head *list,
    				  struct list_head *head)
    {
    	__list_del_entry(list);
    	list_add_tail(list, head);
    }
    ```

    **`list_move`**
    将节点从原链表删除，并插入到目标头节点之后（成为新链表的第一个节点）。
    内部调用 `__list_del_entry` 删除节点，再通过 `list_add` 将其添加到目标位置。

    **`list_move_tail`**
    将节点从原链表删除，并插入到目标头节点之前（成为新链表的最后一个节点）。
    同样先删除节点，再通过 `list_add_tail` 将其添加到目标链表的末尾。

    ```c
    static inline void __list_splice(const struct list_head *list,
    				 struct list_head *prev,
    				 struct list_head *next)
    {
    	struct list_head *first = list->next;
    	struct list_head *last = list->prev;
    
    	first->prev = prev;
    	prev->next = first;
    
    	last->next = next;
    	next->prev = last;
    }
    
    /**
     * list_splice - join two lists, this is designed for stacks
     * @list: the new list to add.
     * @head: the place to add it in the first list.
     */
    static inline void list_splice(const struct list_head *list,
    				struct list_head *head)
    {
    	if (!list_empty(list))
    		__list_splice(list, head, head->next);
    }
    
    /**
     * list_splice_tail - join two lists, each list being a queue
     * @list: the new list to add.
     * @head: the place to add it in the first list.
     */
    static inline void list_splice_tail(struct list_head *list,
    				struct list_head *head)
    {
    	if (!list_empty(list))
    		__list_splice(list, head->prev, head);
    }
    
    ```

    **`__list_splice` (内部函数)**
    核心功能是将源链表 `list` 的全部节点插入到目标位置 `prev` 和 `next` 之间。

    - 获取源链表的首节点 `first` (`list->next`) 和尾节点 `last` (`list->prev`)
    - 将 `first` 的 `prev` 指向目标前驱节点 `prev`，同时 `prev` 的 `next` 指向 `first`
    - 将 `last` 的 `next` 指向目标后继节点 `next`，同时 `next` 的 `prev` 指向 `last`
      通过 4 次指针操作完成两个链表的无缝衔接。

    **`list_splice`**
    将源链表 `list` 拼接到目标链表 `head` 之后（插入到 `head` 和 `head->next` 之间）。

    - 先检查源链表是否非空 (`list_empty` 判断)
    - 调用 `__list_splice(list, head, head->next)` 实现拼接
      典型应用场景是栈的合并，新链表节点会出现在目标链表头部之后。

    **`list_splice_tail`**
    将源链表 `list` 拼接到目标链表 `head` 之前（插入到 `head->prev` 和 `head` 之间）。

    - 同样先检查源链表非空
    - 调用 `__list_splice(list, head->prev, head)` 实现拼接
      适用于队列操作，新链表节点会出现在目标链表尾部。

- **遍历宏**

  - `list_for_each(pos, head)`：以 `struct list_head *pos` 形式遍历所有节点。
  - `list_for_each_entry(entry, head, member)`：直接以外层结构指针形式遍历，内置 `container_of` 安全转换，推荐使用 

  ```c
  /**
   * list_for_each	-	iterate over a list
   * @pos:	the &struct list_head to use as a loop cursor.
   * @head:	the head for your list.
   */
  #define list_for_each(pos, head) \
  	for (pos = (head)->next; !list_is_head(pos, (head)); pos = pos->next)
  
  /**
   * list_for_each_reverse - iterate backwards over a list
   * @pos:	the &struct list_head to use as a loop cursor.
   * @head:	the head for your list.
   */
  #define list_for_each_reverse(pos, head) \
  	for (pos = (head)->prev; pos != (head); pos = pos->prev)
  /**
   * list_for_each_entry	-	iterate over list of given type
   * @pos:	the type * to use as a loop cursor.
   * @head:	the head for your list.
   * @member:	the name of the list_head within the struct.
   */
  #define list_for_each_entry(pos, head, member)				\
  	for (pos = list_first_entry(head, typeof(*pos), member);	\
  	     !list_entry_is_head(pos, head, member);			\
  	     pos = list_next_entry(pos, member))
  
  /**
   * list_for_each_entry_reverse - iterate backwards over list of given type.
   * @pos:	the type * to use as a loop cursor.
   * @head:	the head for your list.
   * @member:	the name of the list_head within the struct.
   */
  #define list_for_each_entry_reverse(pos, head, member)			\
  	for (pos = list_last_entry(head, typeof(*pos), member);		\
  	     !list_entry_is_head(pos, head, member); 			\
  	     pos = list_prev_entry(pos, member))
  ```

  ​	这些就是典型的使用for爬取链表，当然，还是很简单的，这里不做讲解

# 红黑树

​	红黑树是一个非常经典也是非常难懂的数据结构，它的数据结构定义在`include/linux/rbtree_types.h`上，同时，操作则是在`include/linux/rbtree.h`

## 啥是红黑树？

​	红黑树红黑树首先是一个树，他是从二叉树中飞叉出来的一个数据结构，对于最朴实的二叉树（只有本体，左子节点指针、右子节点指针），他还多了父节点指针以及颜色标识。其中颜色标识是红黑树的亮点！

​	我们关心的是红黑树在静态上颜色必须满足的规则！这些规则实则保证树一定是近似平衡的

1. **根节点恒黑**：整棵树的顶点必须为黑色，这为颜色调整提供了基准点。
2. **叶子（NIL）皆黑**：所有空节点被视为黑色叶子，统一了路径计算的终点。
3. **红节点无赤子**：红色节点的子节点必须为黑色，防止连续红色节点破坏平衡。
4. **黑高恒定**：从任意节点到其所有叶子节点的路径包含相同数量的黑色节点（称为黑高）。
5. **新叶染红**：插入的新节点初始化为红色，最小化对黑高的影响。

这些规则共同作用，确保从根到叶子的最长路径不超过最短路径的两倍。数学证明表明，含有n个节点的红黑树高度始终满足h ≤ 2log₂(n+1)，这为各项操作的对数时间复杂度提供了理论保证。

### 插入操作可能出现的操作：

当新节点以红色身份加入红黑树时，可能引发两种冲突场景：双红冲突（父节点同为红色）与根节点变色。插入后的平衡调整如同精密的机械校准，包含三种基本操作：

**颜色翻转（Recoloring）**
当**新节点的父节点和叔节点均为红色**时，执行祖父节点变红、父叔节点染黑的色彩变换。这种操作如同电路中的信号传递，将颜色冲突向上层转移，可能递归触发新的调整。

**单旋转（Rotation）**
当双红节点形成线性结构（左-左或右-右排列），需进行单旋操作。以左旋为例：祖父节点变为父节点的右子，原父节点右子变为祖父节点的左子，同时更新颜色标记。这种操作在常数时间内重构局部结构，恢复颜色约束。

**双旋转（Double Rotation）**
当冲突节点呈折线排列（左-右或右-左），需先对父节点执行单旋转换为线性结构，再对祖父节点进行反向旋转。这种复合操作虽然步骤较多，但时间复杂度仍保持为O(1)。

### 删除操作

节点删除引发的平衡破坏更为复杂，特别是移除黑色节点时可能导致黑高失衡。删除算法需要处理四种主要情形：

**情形1：后继为红色**
当被删节点的继承者（右子树最小节点）为红色时，直接将其染黑即可保持黑高。这种简单情况约占总删除操作的40%。

**情形2：远侄子为红**
若被删节点的兄弟节点存在红色远侄子（与兄弟同侧的侄子），执行颜色传递与单旋转。例如右兄弟的右子为红时，将兄弟颜色传给父节点，远侄子染黑，并进行左旋。

**情形3：近侄子为红**
当仅有近侄子（与兄弟异侧的侄子）为红色时，需先旋转兄弟节点转换为情形2，再按情形2处理。这种两步调整确保颜色分布符合规则。

**情形4：兄弟节点为黑**
当兄弟节点及其子节点均为黑色时，将兄弟染红并将失衡向上传递。这种情形可能递归至根节点，最终通过全局调整恢复平衡。

删除操作的调整过程同样自底向上进行，平均需要1.5次旋转操作。算法通过精心设计的条件判断与状态转移，确保每次调整都在局部范围内完成，避免全局重构带来的性能损耗。

## Linux对红黑树的抽象

​	在`include/linux/rbtree_types.h`中

```c
/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef _LINUX_RBTREE_TYPES_H
#define _LINUX_RBTREE_TYPES_H

struct rb_node {
	unsigned long  __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));
/* The alignment might seem pointless, but allegedly CRIS needs it */

struct rb_root {
	struct rb_node *rb_node;
};
#define RB_ROOT (struct rb_root) { NULL, }
#endif
```

​	笔者稍微略去了一些没有关系的数据结构，这就是咱们的红黑树。可以看到，Linux对红黑树做的操作很简单，就比正常的红黑树多了父亲节点和对应的颜色，需要注意的是——你可能会问父亲节点呢？答案是使用位运算将父指针与颜色信息打包在同一字段内，**减少内存占用和缓存失误率**。

​	这里也就能看到了我们的红黑树的静态初始化，实际上就是将整个结构体制空。

```
struct rb_root mytree = RB_ROOT;
```

等同于将 `mytree.rb_node = NULL`，表示空树状态。如需在运行时初始化，亦可将 `struct rb_root` 置零或直接赋值 `RB_ROOT`。插入前，宿主结构体的 `struct rb_node node;` 无需特别初始化，仅在调用 `rb_link_node()` 后才需设置父子指针，由后续重平衡函数处理颜色位和指针调整。

### 核心API与操作

#### 插入操作

- 首先沿树搜索合适插入位置，记录目标父节点和插入点指针地址。换而言之，我们需要自己连接两个子节点，内核不负责比较大小决定插入到哪里，整个数据结构只负责维护平衡，所以需要我们自己找出来预计的插入的节点位置。
- 调用 `rb_link_node(&data->node, parent, new_link)` 建立节点与父关系。
- 随后调用 `rb_insert_color(&data->node, &mytree)` 执行必要的旋转与重着色操作，恢复红黑树性质。

```
static inline void rb_link_node(struct rb_node *node, struct rb_node *parent,
				struct rb_node **rb_link)
{
	node->__rb_parent_color = (unsigned long)parent;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}
```

**1. rb_link_node() 函数**  
- 将新节点 `node` 初步链接到树结构中  
- `node->__rb_parent_color` 存储父节点指针（通过强制类型转换）并默认颜色为红（最低位为0）  
- 清空新节点的左右子节点指针  
- 通过 `*rb_link` 将新节点挂载到父节点的正确位置（左/右子节点指针）  

```c
static __always_inline void
__rb_insert(struct rb_node *node, struct rb_root *root,
	    void (*augment_rotate)(struct rb_node *old, struct rb_node *new))
{
	struct rb_node *parent = rb_red_parent(node), *gparent, *tmp;

	while (true) {
		/*
		 * Loop invariant: node is red.
		 */
		if (unlikely(!parent)) {
			/*
			 * The inserted node is root. Either this is the
			 * first node, or we recursed at Case 1 below and
			 * are no longer violating 4).
			 */
			rb_set_parent_color(node, NULL, RB_BLACK);
			break;
		}

		/*
		 * If there is a black parent, we are done.
		 * Otherwise, take some corrective action as,
		 * per 4), we don't want a red root or two
		 * consecutive red nodes.
		 */
		if(rb_is_black(parent))
			break;

		gparent = rb_red_parent(parent);

		tmp = gparent->rb_right;
		if (parent != tmp) {	/* parent == gparent->rb_left */
			if (tmp && rb_is_red(tmp)) {
				/*
				 * Case 1 - node's uncle is red (color flips).
				 *
				 *       G            g
				 *      / \          / \
				 *     p   u  -->   P   U
				 *    /            /
				 *   n            n
				 *
				 * However, since g's parent might be red, and
				 * 4) does not allow this, we need to recurse
				 * at g.
				 */
				rb_set_parent_color(tmp, gparent, RB_BLACK);
				rb_set_parent_color(parent, gparent, RB_BLACK);
				node = gparent;
				parent = rb_parent(node);
				rb_set_parent_color(node, parent, RB_RED);
				continue;
			}

			tmp = parent->rb_right;
			if (node == tmp) {
				/*
				 * Case 2 - node's uncle is black and node is
				 * the parent's right child (left rotate at parent).
				 *
				 *      G             G
				 *     / \           / \
				 *    p   U  -->    n   U
				 *     \           /
				 *      n         p
				 *
				 * This still leaves us in violation of 4), the
				 * continuation into Case 3 will fix that.
				 */
				tmp = node->rb_left;
				WRITE_ONCE(parent->rb_right, tmp);
				WRITE_ONCE(node->rb_left, parent);
				if (tmp)
					rb_set_parent_color(tmp, parent,
							    RB_BLACK);
				rb_set_parent_color(parent, node, RB_RED);
				augment_rotate(parent, node);
				parent = node;
				tmp = node->rb_right;
			}

			/*
			 * Case 3 - node's uncle is black and node is
			 * the parent's left child (right rotate at gparent).
			 *
			 *        G           P
			 *       / \         / \
			 *      p   U  -->  n   g
			 *     /                 \
			 *    n                   U
			 */
			WRITE_ONCE(gparent->rb_left, tmp); /* == parent->rb_right */
			WRITE_ONCE(parent->rb_right, gparent);
			if (tmp)
				rb_set_parent_color(tmp, gparent, RB_BLACK);
			__rb_rotate_set_parents(gparent, parent, root, RB_RED);
			augment_rotate(gparent, parent);
			break;
		} else {
			tmp = gparent->rb_left;
			if (tmp && rb_is_red(tmp)) {
				/* Case 1 - color flips */
				rb_set_parent_color(tmp, gparent, RB_BLACK);
				rb_set_parent_color(parent, gparent, RB_BLACK);
				node = gparent;
				parent = rb_parent(node);
				rb_set_parent_color(node, parent, RB_RED);
				continue;
			}

			tmp = parent->rb_left;
			if (node == tmp) {
				/* Case 2 - right rotate at parent */
				tmp = node->rb_right;
				WRITE_ONCE(parent->rb_left, tmp);
				WRITE_ONCE(node->rb_right, parent);
				if (tmp)
					rb_set_parent_color(tmp, parent,
							    RB_BLACK);
				rb_set_parent_color(parent, node, RB_RED);
				augment_rotate(parent, node);
				parent = node;
				tmp = node->rb_left;
			}

			/* Case 3 - left rotate at gparent */
			WRITE_ONCE(gparent->rb_right, tmp); /* == parent->rb_left */
			WRITE_ONCE(parent->rb_left, gparent);
			if (tmp)
				rb_set_parent_color(tmp, gparent, RB_BLACK);
			__rb_rotate_set_parents(gparent, parent, root, RB_RED);
			augment_rotate(gparent, parent);
			break;
		}
	}
}
```

**2. __rb_insert() 函数**  
循环处理红黑树插入后的平衡调整，主要处理三种经典情况：

**Case 1：叔父节点为红色**  
- 执行颜色翻转：父节点、叔节点变黑，祖父节点变红  
- 将当前节点指针上移至祖父节点，继续向上递归调整  
- 例如当新节点n的父p和叔u均为红色时：  
  ```text
      G(B)            G(R)  
     /  \            /  \  
    p(R) u(R)  →   p(B) u(B)  
   /              /  
  n(R)          n(R)  
  ```

**Case 2：叔父为黑且形成三角结构**  
- 先通过单旋转转换为线性结构  
- 例如新节点n是父p的右子时：  
  对p执行左旋，使n成为p的父节点  
  ```text
      G             G  
     /             /  
    p(R)   →     n(R)  
     \          /  
     n(R)     p(R)  
  ```

**Case 3：叔父为黑且形成线性结构**  
- 对祖父节点执行单旋转并重新着色  
- 例如左-左结构时：  
  对G执行右旋，p成为新父节点，G变红，p变黑  
  ```text
      G(B)          p(B)  
     /            /   \  
    p(R)   →    n(R)  G(R)  
   /  
  n(R)  
  ```

**关键实现细节**  
- `WRITE_ONCE` 宏确保指针修改的原子性，防止并发访问问题  
- `augment_rotate` 回调函数用于处理旋转时的额外数据结构维护（如AVL树的高度更新）  
- 颜色信息通过 `__rb_parent_color` 的最低比特位存储（0:红，1:黑）  
- 循环通过向上遍历（`node = gparent`）处理颜色冲突传播  
- 最终根节点强制设为黑色保持规则  

#### **删除节点**

- 直接调用 `rb_erase(&victim->node, &mytree)`，内核自动完成平衡调整并移除节点。
- 若仅需替换节点，可使用 `rb_replace_node(&old->node, &new->node, &mytree)`，但需保证键不变，否则树结构将被破坏。

```c
void rb_erase(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *rebalance;
	rebalance = __rb_erase_augmented(node, root, &dummy_callbacks);
	if (rebalance)
		____rb_erase_color(rebalance, root, dummy_rotate);	/* need balance */
}
```

```c
static __always_inline struct rb_node *
__rb_erase_augmented(struct rb_node *node, struct rb_root *root,
		     const struct rb_augment_callbacks *augment)
{
	struct rb_node *child = node->rb_right;
	struct rb_node *tmp = node->rb_left;
	struct rb_node *parent, *rebalance;
	unsigned long pc;

	if (!tmp) {
		/*
		 * Case 1: node to erase has no more than 1 child (easy!)
		 *
		 * Note that if there is one child it must be red due to 5)
		 * and node must be black due to 4). We adjust colors locally
		 * so as to bypass __rb_erase_color() later on.
		 */
		pc = node->__rb_parent_color;
		parent = __rb_parent(pc);
		__rb_change_child(node, child, parent, root);
		if (child) {
			child->__rb_parent_color = pc;
			rebalance = NULL;
		} else
			rebalance = __rb_is_black(pc) ? parent : NULL;
		tmp = parent;
	} else if (!child) {
		/* Still case 1, but this time the child is node->rb_left */
		tmp->__rb_parent_color = pc = node->__rb_parent_color;
		parent = __rb_parent(pc);
		__rb_change_child(node, tmp, parent, root);
		rebalance = NULL;
		tmp = parent;
	} else {
		struct rb_node *successor = child, *child2;

		tmp = child->rb_left;
		if (!tmp) {
			/*
			 * Case 2: node's successor is its right child
			 *
			 *    (n)          (s)
			 *    / \          / \
			 *  (x) (s)  ->  (x) (c)
			 *        \
			 *        (c)
			 */
			parent = successor;
			child2 = successor->rb_right;

			augment->copy(node, successor);
		} else {
			/*
			 * Case 3: node's successor is leftmost under
			 * node's right child subtree
			 *
			 *    (n)          (s)
			 *    / \          / \
			 *  (x) (y)  ->  (x) (y)
			 *      /            /
			 *    (p)          (p)
			 *    /            /
			 *  (s)          (c)
			 *    \
			 *    (c)
			 */
			do {
				parent = successor;
				successor = tmp;
				tmp = tmp->rb_left;
			} while (tmp);
			child2 = successor->rb_right;
			WRITE_ONCE(parent->rb_left, child2);
			WRITE_ONCE(successor->rb_right, child);
			rb_set_parent(child, successor);

			augment->copy(node, successor);
			augment->propagate(parent, successor);
		}

		tmp = node->rb_left;
		WRITE_ONCE(successor->rb_left, tmp);
		rb_set_parent(tmp, successor);

		pc = node->__rb_parent_color;
		tmp = __rb_parent(pc);
		__rb_change_child(node, successor, tmp, root);

		if (child2) {
			rb_set_parent_color(child2, parent, RB_BLACK);
			rebalance = NULL;
		} else {
			rebalance = rb_is_black(successor) ? parent : NULL;
		}
		successor->__rb_parent_color = pc;
		tmp = successor;
	}

	augment->propagate(tmp, NULL);
	return rebalance;
}
```

**基础流程**

1. **确定实际删除节点**
   - 若目标节点有两个子节点，寻找右子树的最小节点（后继节点）作为实际删除节点
   - 通过`augment->copy`将后继节点数据复制到原节点位置，物理上删除后继节点

**三种删除情形**
**情形1：单子节点删除**

- 当被删节点只有左/右单个子节点时：
  a. 用子节点直接替换被删节点
  b. 若子节点为红（根据红黑树规则必为红），染黑即可保持平衡
  c. 若子节点不存在且被删节点为黑，标记需要后续平衡(`rebalance`)

**情形2：后继为右子节点**

- 当后继节点是被删节点的直接右子时：
  a. 用后继节点替换被删节点
  b. 处理原后继节点的右子树
  c. 若原后继节点为黑且无子节点，标记需要平衡

**情形3：后继位于右子树深层**

- 当后继节点位于右子树的最左端时：
  a. 将后继节点提升到被删节点位置
  b. 原后继节点的右子接管其原位置
  c. 调整父子指针关系，维护树形结构

**关键操作细节**

- `__rb_change_child`：安全更新父节点对子节点的引用
- `WRITE_ONCE`：确保指针修改的原子性，防止并发问题
- `__rb_parent_color`：通过位操作同时存储父指针和颜色信息
- `augment`回调：用于维护额外数据（如子树大小等增强信息）

**平衡标记传递**

- `rebalance`变量标记需要开始重新平衡的起始节点
- 若删除黑节点导致黑高失衡，返回待平衡节点供后续`__rb_erase_color`处理
- 通过颜色判断决定是否需要触发平衡调整流程

```c
static __always_inline void
____rb_erase_color(struct rb_node *parent, struct rb_root *root,
	void (*augment_rotate)(struct rb_node *old, struct rb_node *new))
{
	struct rb_node *node = NULL, *sibling, *tmp1, *tmp2;

	while (true) {
		/*
		 * Loop invariants:
		 * - node is black (or NULL on first iteration)
		 * - node is not the root (parent is not NULL)
		 * - All leaf paths going through parent and node have a
		 *   black node count that is 1 lower than other leaf paths.
		 */
		sibling = parent->rb_right;
		if (node != sibling) {	/* node == parent->rb_left */
			if (rb_is_red(sibling)) {
				/*
				 * Case 1 - left rotate at parent
				 *
				 *     P               S
				 *    / \             / \
				 *   N   s    -->    p   Sr
				 *      / \         / \
				 *     Sl  Sr      N   Sl
				 */
				tmp1 = sibling->rb_left;
				WRITE_ONCE(parent->rb_right, tmp1);
				WRITE_ONCE(sibling->rb_left, parent);
				rb_set_parent_color(tmp1, parent, RB_BLACK);
				__rb_rotate_set_parents(parent, sibling, root,
							RB_RED);
				augment_rotate(parent, sibling);
				sibling = tmp1;
			}
			tmp1 = sibling->rb_right;
			if (!tmp1 || rb_is_black(tmp1)) {
				tmp2 = sibling->rb_left;
				if (!tmp2 || rb_is_black(tmp2)) {
					/*
					 * Case 2 - sibling color flip
					 * (p could be either color here)
					 *
					 *    (p)           (p)
					 *    / \           / \
					 *   N   S    -->  N   s
					 *      / \           / \
					 *     Sl  Sr        Sl  Sr
					 *
					 * This leaves us violating 5) which
					 * can be fixed by flipping p to black
					 * if it was red, or by recursing at p.
					 * p is red when coming from Case 1.
					 */
					rb_set_parent_color(sibling, parent,
							    RB_RED);
					if (rb_is_red(parent))
						rb_set_black(parent);
					else {
						node = parent;
						parent = rb_parent(node);
						if (parent)
							continue;
					}
					break;
				}
				/*
				 * Case 3 - right rotate at sibling
				 * (p could be either color here)
				 *
				 *   (p)           (p)
				 *   / \           / \
				 *  N   S    -->  N   sl
				 *     / \             \
				 *    sl  sr            S
				 *                       \
				 *                        sr
				 *
				 * Note: p might be red, and then both
				 * p and sl are red after rotation(which
				 * breaks property 4). This is fixed in
				 * Case 4 (in __rb_rotate_set_parents()
				 *         which set sl the color of p
				 *         and set p RB_BLACK)
				 *
				 *   (p)            (sl)
				 *   / \            /  \
				 *  N   sl   -->   P    S
				 *       \        /      \
				 *        S      N        sr
				 *         \
				 *          sr
				 */
				tmp1 = tmp2->rb_right;
				WRITE_ONCE(sibling->rb_left, tmp1);
				WRITE_ONCE(tmp2->rb_right, sibling);
				WRITE_ONCE(parent->rb_right, tmp2);
				if (tmp1)
					rb_set_parent_color(tmp1, sibling,
							    RB_BLACK);
				augment_rotate(sibling, tmp2);
				tmp1 = sibling;
				sibling = tmp2;
			}
			/*
			 * Case 4 - left rotate at parent + color flips
			 * (p and sl could be either color here.
			 *  After rotation, p becomes black, s acquires
			 *  p's color, and sl keeps its color)
			 *
			 *      (p)             (s)
			 *      / \             / \
			 *     N   S     -->   P   Sr
			 *        / \         / \
			 *      (sl) sr      N  (sl)
			 */
			tmp2 = sibling->rb_left;
			WRITE_ONCE(parent->rb_right, tmp2);
			WRITE_ONCE(sibling->rb_left, parent);
			rb_set_parent_color(tmp1, sibling, RB_BLACK);
			if (tmp2)
				rb_set_parent(tmp2, parent);
			__rb_rotate_set_parents(parent, sibling, root,
						RB_BLACK);
			augment_rotate(parent, sibling);
			break;
		} else {
			sibling = parent->rb_left;
			if (rb_is_red(sibling)) {
				/* Case 1 - right rotate at parent */
				tmp1 = sibling->rb_right;
				WRITE_ONCE(parent->rb_left, tmp1);
				WRITE_ONCE(sibling->rb_right, parent);
				rb_set_parent_color(tmp1, parent, RB_BLACK);
				__rb_rotate_set_parents(parent, sibling, root,
							RB_RED);
				augment_rotate(parent, sibling);
				sibling = tmp1;
			}
			tmp1 = sibling->rb_left;
			if (!tmp1 || rb_is_black(tmp1)) {
				tmp2 = sibling->rb_right;
				if (!tmp2 || rb_is_black(tmp2)) {
					/* Case 2 - sibling color flip */
					rb_set_parent_color(sibling, parent,
							    RB_RED);
					if (rb_is_red(parent))
						rb_set_black(parent);
					else {
						node = parent;
						parent = rb_parent(node);
						if (parent)
							continue;
					}
					break;
				}
				/* Case 3 - left rotate at sibling */
				tmp1 = tmp2->rb_left;
				WRITE_ONCE(sibling->rb_right, tmp1);
				WRITE_ONCE(tmp2->rb_left, sibling);
				WRITE_ONCE(parent->rb_left, tmp2);
				if (tmp1)
					rb_set_parent_color(tmp1, sibling,
							    RB_BLACK);
				augment_rotate(sibling, tmp2);
				tmp1 = sibling;
				sibling = tmp2;
			}
			/* Case 4 - right rotate at parent + color flips */
			tmp2 = sibling->rb_right;
			WRITE_ONCE(parent->rb_left, tmp2);
			WRITE_ONCE(sibling->rb_right, parent);
			rb_set_parent_color(tmp1, sibling, RB_BLACK);
			if (tmp2)
				rb_set_parent(tmp2, parent);
			__rb_rotate_set_parents(parent, sibling, root,
						RB_BLACK);
			augment_rotate(parent, sibling);
			break;
		}
	}
}
```

这段代码实现了红黑树删除节点后的再平衡逻辑（即红黑树删除算法中的颜色调整阶段），通过处理四种经典情况恢复红黑树的平衡性。整个函数以被删节点的父节点 `parent` 为起点，逐步向上调整直至满足红黑树规则。

**循环条件**  
- 当前节点 `node` 为黑色（初始时为被删节点的替代节点）
- `parent` 不为空（未到达根节点）
- 经过 `parent` 和 `node` 的路径黑高比其他路径少1

**四大处理情形**  
**情形1：兄弟节点为红色**  
- 执行左旋/右旋将兄弟节点变为黑色  
- 例如当 `node` 是左子且兄弟为红时：  
  对父节点左旋，原兄弟节点成为新祖父，其左子变为新兄弟  
  旋转后兄弟节点必为黑，进入后续情形处理  

**情形2：兄弟及其子节点均为黑色**  
- 将兄弟节点染红，使经过父节点的路径黑高减1  
- 若父节点原为红色：  
  - 直接染黑父节点，补足黑高，终止调整  
- 若父节点原为黑色：  
  - 将 `node` 上移至父节点，继续向上递归调整  

**情形3：兄弟为黑且远侄子为黑**  
- 通过旋转将远侄子变为红色  
- 例如当 `node` 是左子且兄弟的右子为黑时：  
  对兄弟节点右旋，使兄弟的左子（原红）成为新兄弟  
  旋转后进入情形4处理  

**情形4：兄弟为黑且远侄子为红**  
- 对父节点左旋/右旋，并通过颜色调整补足黑高  
  例如：  
  1. 兄弟的远侄子染黑  
  2. 父节点染黑  
  3. 兄弟节点继承原父节点颜色  
  4. 旋转操作将子树黑高恢复  
  此情形可彻底消除黑高失衡，结束调整循环  

### 实现细节  
1. **方向对称处理**  
   - 代码分为 `node == parent->rb_left` 和 `node == parent->rb_right` 两个镜像分支  
   - 每个分支内处理逻辑对称，但旋转方向相反  

2. **原子写操作**  
   - 使用 `WRITE_ONCE` 宏保证指针修改的原子性  
   - 防止多线程环境下的内存访问冲突  

3. **颜色传播**  
   - `rb_set_parent_color` 同时设置父指针和颜色  
   - 颜色信息通过指针变量的最低比特位存储（0:红，1:黑）  

4. **增强回调**  
   - `augment_rotate` 函数指针用于维护额外数据结构  
   - 在旋转时同步更新附加信息（如子树统计值）  

### 调整示例  
以 `node` 为左子且兄弟为黑为例：  
```text
初始状态（情形4）:
      P(B)              P(B)
     /   \             /   \
   N(B)  S(B)  →     N(B)  S(B)
          \                 \
          Sr(R)            Sr(R)

处理步骤:
1. 左旋父节点 P  
2. 将 S 染为 P 的原色  
3. 将 P 染黑  
4. 将 Sr 染黑  

最终状态:
      S(P_color)
     /   \
   P(B)  Sr(B)
  /
N(B)
```

### 终止条件  
- **情形2**中父节点为红时直接染黑终止  
- **情形4**通过旋转重构后完全恢复平衡  
- 调整传递至根节点时自动结束  

## 遍历

- **按序访问**

  - `rb_first(&mytree)` 返回最小节点；
  - `rb_next(node)` 返回在中序遍历下的后继节点；
  - `rb_last()` 和 `rb_prev()` 类似操作；
     通过循环可轻松实现排序访问：

  ```
  for (node = rb_first(&mytree); node; node = rb_next(node))
      process(rb_entry(node, struct mytype, node));
  ```

- **查找**
   红黑树不提供通用查找函数，用户需自行编写：

  ```
  struct mytype *my_search(struct rb_root *root, key_t key) {
      struct rb_node *n = root->rb_node;
      while (n) {
          data = rb_entry(n, struct mytype, node);
          if (key < data->key) n = n->rb_left;
          else if (key > data->key) n = n->rb_right;
          else return data;
      }
      return NULL;
  }
  ```
