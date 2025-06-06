# Linux内核的新数据结构 - maple tree

从外部看，Linux 内核的内部结构似乎比较稳定，尤其是在内存管理子系统等子系统中。但是，开发人员有时需要更换内部接口来解决长期存在的问题。其中一个问题是用于保护基本内存管理结构（包括页表和虚拟内存区域 (VMA)）的锁的争用。Liam Howlett 和 Matthew Wilcox 一直在开发一种称为“枫树”的新数据结构，以取代当前用于 VMA 的数据结构。内部内核结构的这一潜在重大变化最近已发布在大量补丁集中以供审查。

Linux 是一个虚拟内存系统。每个进程的地址空间包含由 vm_area_struct 结构表示的多个虚拟内存区域。每个 VMA 代表一个连续的地址空间块，并代表相同类型的内存范围，这些内存可能是匿名内存（不受文件支持）、内存映射文件，甚至是设备内存。从进程的角度来看，虚拟内存区域是连续的，而支持物理内存可能不是连续的。此外，地址空间在 VMA 之间包含空洞；当内核需要添加新的映射区域时（例如，加载库或响应 mmap() 调用时），它会填充这些空块（为未映射的“保护”页面留出空间以捕获缓冲区溢出）。

几乎系统中可以执行的任何操作都涉及内存，因此对表示 VMA 的结构的操作必须快速。这些操作包括查找（找出哪个 VMA 对应于给定的虚拟地址，找出内存是否已映射，或为新内存区域定位空隙）和修改（例如，增加堆栈）。

VMA 当前存储在经过修改的红黑树 (rbtree) 中，并带有一个额外的双向链表，允许内核遍历进程地址空间中的所有 VMA。内核开发人员一段时间以来一直对这种数据结构不满意，原因有很多：rbtree 不能很好地支持范围，它们很难以无锁方式处理（rbtree 的平衡操作同时影响多个项目），并且 rbtree 遍历效率低下，这就是存在额外链接列表的原因。

VMA 上的操作受锁（特别是读取器/写入器信号量）保护，该锁包含在 struct mm_struct 中。此锁被称为 mmap_sem，直到 2020 年 6 月在 5.8 版本中将其重命名为 mmap_lock。这次重命名是将锁包装在 API 中的努力的一部分，希望将来可以简化它的替换。

用户，尤其是那些在大型系统中使用线程应用程序的用户，经常会遇到此锁的争用。内核开发人员已经多次讨论过这个问题，在 2019 年 Linux 存储、文件系统和内存管理峰会 (LFSMM) 上至少有三场会议讨论了这个问题。问题的核心是，许多操作都需要锁，包括几乎所有涉及页表和 VMA 的操作。还有其他相关结构受到 mmap_lock 的有效保护（但这一事实缺乏文档记录，这又是一个难题）。除了从 mmap_lock 中分离出不相关的结构外，开发人员还在考虑使用允许无锁访问 VMA 的结构或使用某种类型的范围锁。枫树是当时提出的解决方案之一，但当时它处于早期开发阶段，代码尚未可用。

## 介绍枫树

枫树（名称可能指的是枫叶的形状，有多个方向）在重要方面与红黑树不同。它们属于 B 树家族，因此它们的节点可以包含两个以上的元素 — 叶节点最多 16 个元素，内部节点最多 10 个元素。使用 B 树还意味着不需要创建新节点，因为节点可能包含空槽，这些空槽可以随着时间的推移填充而无需额外分配。每个节点最多需要 256 个字节，这是流行缓存行大小的倍数。节点中元素数量的增加和缓存对齐的大小意味着在遍历树时缓存未命中的次数更少。

对枫树中搜索的改进支持也来自 B 树结构。在 B 树中，每个节点都包含键，称为“枢轴”，将节点分成子树。给定键之前的子树仅包含低于或等于键的值，而键之后的子树仅包含高于键（且低于下一个键）的值。

当然，枫树被设计为以无锁方式工作，使用读取-复制-更新 (RCU)。枫树是一种通用结构，可用于不同的内核子系统；第一种用途是替换红黑树和链接列表来管理 VMA。其中一位作者 Liam Howlett 解释了设计的原因在博客文章中。

Maple 树提供两种 API：简单 API 和高级 API。简单 API 使用 mtree_ 前缀作为其函数，主要结构 struct maple_tree 定义如下：

```
struct maple_tree {
	spinlock_t ma_lock;
	unsigned int ma_flags;
	void __rcu *ma_root;
};
```

静态初始化程序是 DEFINE_MTREE(name) 和 MTREE_INIT(name, flags)，后者从当前定义的两个标志中获取标志的位掩码。 MAPLE_ALLOC_RANGE 表示该树将用于分配范围，并且它应该管理分配之间的间隙； MAPLE_USE_RCU 为多个读取器激活 RCU 模式。使用 mtree_init() 可以使用相同的标志进行动态初始化：

```
void mtree_init(struct maple_tree *mt, unsigned int ma_flags);
```

开发人员可以使用以下方法释放整个树：

```
void mtree_destroy(struct maple_tree *mt);
```

有三个函数用于向树中添加条目：mtree_insert()、mtree_insert_range() 和 mtree_store_range()。前两个函数仅在条目之前不存在时添加条目，而第三个函数可以覆盖现有条目。它们定义如下：

```
int mtree_insert(struct maple_tree *mt, unsigned long index,
void *entry, gfp_t gfp);
int mtree_insert_range(struct maple_tree *mt, unsigned long first,
unsigned long last, void *entry, gfp_t gfp);
int mtree_store_range(struct maple_tree *mt, unsigned long first,
unsigned long last, void *entry, gfp_t gfp);
```

mtree_insert() 接受指向树 mt 的指针、条目索引的整数键、指向条目的指针以及新树节点的内存分配标志 gfp（如果需要）。mtree_insert_range() 使用给定的数据条目插入从第一个到最后一个的范围。如果成功，这些函数返回零，否则返回负值，如果该键已经存在，则返回 -EEXIST。最后，mtree_store_range() 接受与 mtree_insert_range() 相同的参数；不同之处在于它会替换相应键的任何现有条目。

有两个函数可用于从树中获取条目或删除条目：

```
void *mtree_load(struct maple_tree *mt, unsigned long index);
void *mtree_erase(struct maple_tree *mt, unsigned long index);
```

要读取条目，开发人员应使用 mtree_load()，它接受指向树 mt 的指针和请求值索引的键。该函数返回指向条目的指针，如果在树中未找到该键，则返回 NULL。使用 mtree_erase() 从树中删除条目时，使用相同的语法。它从树中删除给定的键并返回关联的条目，如果未找到这样的值，则返回 NULL。

简单 API 的功能远不止上述内容，包括 mtree_alloc_range()，用于从键空间分配范围。高级 API（使用 mas_ 前缀）添加了迭代器函数，用于遍历整个树，或使用状态变量访问下一个和上一个元素。通过这种细粒度控制，开发人员可以根据需要恢复搜索。API 还允许开发人员查找空白区域或复制树。

## 替换 VMA rbtree（以及更多）

补丁集不仅包含对枫树的介绍。值得注意的是，该补丁集的很大一部分添加和更新了测试，考虑到更改的影响以及新数据结构未来的重要性，这是一个受欢迎的补充。

在这组补丁中的 70 个补丁中，所有 VMA 操作都使用枫树来替换红黑树，其中一个补丁从 VMA 中删除了红黑树的使用。补丁集的另一部分导致删除了 VMA 链接列表。此删除需要修改内核代码中直接使用 VMA 列表的各个位置：架构代码、核心转储和程序加载例程、一些设备驱动程序，当然还有内存管理代码。补丁集还删除了 VMA 缓存（它跟踪每个进程最近访问的 VMA 以加快查找速度），因为使用枫树的实现速度更快，不再需要缓存。

附信中包含了一些性能结果，这些结果有点难以解释。一些微基准测试显示性能有所提高，而一些（数量较少）则有所下降。内核编译时间与 vanilla 5.10 内核相似，但执行了更多指令（可能与添加的代码有关）。Howlett 要求开发人员对结果提供见解。

## 当前状态和后续步骤

Maple 树目前处于 RFC 阶段，存在一些限制；例如，该实现不支持 32 位系统或非 MMU 平台。但是，代码是可用的，内核开发人员可以研究它以决定这是否是他们想要删除 mmap_lock 的方向（因为此补丁集中未删除锁）。根据补丁集的大小，审查可能需要一些时间才能完成。