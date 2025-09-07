# 我的LeetCode刷题指南：链表部分

## 前言

​	首先笔者的刷题来自于：[图解算法数据结构 - LeetBook - 力扣（LeetCode）全球极客挚爱的技术成长平台](https://leetcode.cn/leetbook/read/illustration-of-algorithm/55187i/)，这里笔者会慢慢整理自己的刷题日志，发布成一个合集日志供自己和其他人学习和参考。

​	关于链表，笔者在之前的博客中说到过：[从0到1的数据结构教程：单链表-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/146850082)，笔者这里不再打算重复造轮子了。对链表概念还不清晰的朋友请到这里复习。

​	笔者的习惯的工作语言是C++，所以所有的题集的答案都是使用C++书写的

## 🔗 链表专题笔记

------

### 🧱 基础知识

- 单向链表（`ListNode`）：每个节点包含 `val` 和 `next`
- 双向链表：每个节点包含 `prev`, `next`
- 虚拟头节点（dummy head）：常用于链表插入、删除时简化边界处理
- 快慢指针：常用于判断环、找中点、删除倒数第 k 个节点等

------

### 📌 常见链表题型分类与模板

#### 1. 📥 反转链表

- **题型示例：** LeetCode 206. 反转链表
- **解法一：迭代法**

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

- **解法二：递归法**

#### 2. 🔁 判断链表是否有环

- **题型示例：** LeetCode 141. 环形链表
- **快慢指针法：**

```cpp
bool hasCycle(ListNode *head) {	// 既然有环，那么，快指针走了两圈的时候，慢指针刚好一圈，这个时候正好会交于同一个点，反之，出现nullptr说明我们的指针是有边界的
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

#### 3. 🚮 删除链表中的节点

- **删除指定值节点：** 遍历 + 记录前一个节点
- **删除倒数第 n 个节点（LeetCode 19）：** 快慢指针法

#### 4. 📌 查找链表交点

- **题型示例：** LeetCode 160
- **解法：** 长度对齐后同步走，或双指针互换起点

#### 5. 🧬 复制含随机指针的链表

- **题型示例：** LeetCode 138
- **方法一：哈希表法**
- **方法二：链表穿插法（O(1) 空间）**

#### 6. ➕ 合并两个有序链表

- **题型示例：** LeetCode 21
- **递归 or 迭代均可**

#### 7. 🔄 链表分割/重排/奇偶分组等变形

- 分隔链表（86）
- 反转部分链表（92）
- K 个一组翻转链表（25）
- 奇偶链表重排（328）

------

### 📚 推荐刷题顺序

| 难度   | 题目                    | 技巧点             |
| ------ | ----------------------- | ------------------ |
| 🟢 简单 | 206. 反转链表           | 基础指针操作       |
| 🟢 简单 | 21. 合并两个有序链表    | 递归/迭代          |
| 🟡 中等 | 19. 删除倒数第 N 个节点 | 快慢指针           |
| 🟡 中等 | 160. 相交链表           | 长度对齐或双指针   |
| 🔴 困难 | 138. 复制带随机指针链表 | 哈希 or 原地插入法 |
| 🔴 困难 | 25. K 个一组翻转        | 递归/区间处理      |

------

### 🔍 面试技巧总结

- ✅ 熟练掌握常见链表模板，如反转、双指针等
- ✅ 善用 dummy 节点简化边界条件
- ✅ 提高链表模拟能力，尤其处理 random、区间翻转等复杂结构

------

### 📌 附：常用 ListNode 定义

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```



## 📚 题目：书店倒序书单（链表逆序输出）

### 🧩 题目描述

书店店员有一张链表形式的书单，每个节点代表一本书，节点中的值表示书的编号。为了更方便整理书架，店员需要将书单倒过来排列，从最后一本书开始依次放回书架。

**输入：** 单链表 `head`
 **输出：** `vector<int>` 类型的书单编号列表，倒序排列

------

### ✅ 解题思路一：使用栈

#### 思路解析

- 利用栈的 **后进先出（LIFO）** 特性，可以轻松实现链表的逆序输出。
- 先遍历链表，将每个节点的值压入栈中；
- 再依次从栈中弹出元素，添加到结果数组中。

#### 时间复杂度 & 空间复杂度

- **时间复杂度：** O(n)
- **空间复杂度：** O(n)（栈和结果数组的空间）

#### 代码实现（C++）

```cpp
class Solution {
public:
    vector<int> reverseBookList(ListNode* head) {
        ListNode* next = head;
        stack<int> __result;
        vector<int> result;

        while (next) {
            __result.push(next->val);  // 值入栈
            next = next->next;
        }

        while (!__result.empty()) {
            result.emplace_back(__result.top());  // 出栈到结果
            __result.pop();
        }

        return result;
    }
};
```

------

### 🔁 解题思路二：递归实现逆序（函数调用栈）

#### 思路解析

- 利用函数调用栈，先递归到底，再回溯时收集值；
- 注意递归版本可能造成 **栈溢出**（尤其是长链表）。

#### 时间复杂度 & 空间复杂度

- **时间复杂度：** O(n)
- **空间复杂度：** O(n)（递归栈空间）

#### 代码实现（C++）

```cpp
class Solution {
public:
    vector<int> result;
    vector<int> reverseBookList(ListNode* head) {
        if (head) {
            reverseBookList(head->next);
            result.push_back(head->val);
        }
        return result;
    }
};
```

------

### 📝 总结

- 利用 **栈** 是处理链表逆序输出最直接的方法；
- 面试中如要求“原地”操作，请改用**双指针翻转链表**；
- 递归法虽然代码简洁，但需注意栈空间限制。

## 🧹 删除链表节点

### 🧩 题目描述

给定一个单向链表 `head` 和一个整数 `val`，删除链表中值等于 `val` 的**第一个节点**，返回删除后的头节点。

------

### 💡 解题思路

- 单向链表不支持直接回退，因此我们需要维护一个 `prev` 指针。
- 遍历时记录：
  - 当前节点 `finder`
  - 前一个节点 `prev_one`
- 如果目标值是头节点：
  - 直接返回 `head->next`
- 否则：
  - 执行 `prev_one->next = finder->next`

------

### 🧪 示例

| 输入                      | 输出    | 说明              |
| ------------------------- | ------- | ----------------- |
| head = [4,5,1,9], val = 5 | [4,1,9] | 删除值为 5 的节点 |
| head = [4,5,1,9], val = 1 | [4,5,9] | 删除值为 1 的节点 |



------

### ✅ 代码实现（C++）

```cpp
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* finder = head;
        ListNode* prev_one = nullptr;

        while (finder) {
            if (finder->val == val) {
                break; // 找到了目标节点
            }
            prev_one = finder;
            finder = finder->next;
        }

        if (!prev_one) {
            // 如果要删除的是头结点
            return finder->next;
        }

        // 跳过目标节点
        prev_one->next = finder->next;
        return head;
    }
};
```

------

### 📈 时间复杂度 & 空间复杂度

- **时间复杂度：** O(n)，最坏情况要遍历整个链表
- **空间复杂度：** O(1)，只使用了两个辅助指针

------

### 📝 总结

- 这类题核心是理解链表指针的**断链**与**重连**
- 特别注意：若删除的是头结点，要特别处理

## 🏋️‍♂️ 核心肌群训练编号倒序记录（反转链表）

### 🧩 题目描述

给定一个头节点为 `head` 的单链表，表示一系列核心肌群训练编号，请你将这些训练编号**倒序**保存并返回新的链表。

------

### 🧪 示例

| 输入        | 输出        |
| ----------- | ----------- |
| [1,2,3,4,5] | [5,4,3,2,1] |
| [1,2]       | [2,1]       |
| []          | []          |



------

### ✅ 解题思路

#### 方法一：**头插法**构建新链表

- 初始新链表为空
- 遍历原链表，创建新节点并**插入到新链表头部**
- 每次插入的节点成为新的链表头，最后完成倒序

#### 注意事项：

- 新建节点（深拷贝），不修改原链表
- 如果原链表为空，直接返回 `nullptr`

------

### 🧠 时间复杂度 & 空间复杂度

- **时间复杂度：** O(n) — 遍历所有节点一次
- **空间复杂度：** O(n) — 新建链表所占空间

------

### 💻 代码实现（C++）

```cpp
class Solution {
public:
    ListNode* trainningPlan(ListNode* head) {
        if (!head)
            return nullptr;

        ListNode* current = head;
        ListNode* reversed = nullptr;

        while (current) {
            ListNode* newNode = new ListNode(current->val);
            newNode->next = reversed;
            reversed = newNode;
            current = current->next;
        }

        return reversed;
    }
};
```

------

### 🔁 方法二（拓展）：原地反转链表（不创建新节点）

如果题目允许你修改原链表，可以使用**原地翻转链表**，节省空间：

```cpp
class Solution {
public:
    ListNode* trainningPlan(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;

        while (current) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        return prev;
    }
};
```

- **时间复杂度：** O(n)
- **空间复杂度：** O(1)

------

### 📝 总结

- 若 **保留原链表结构**：使用**新链表 + 头插法**
- 若 **允许就地修改**：使用**原地反转链表**
- 注意处理边界情况（空链表）

------

## 🏋️ 查找倒数第 `cnt` 个核心肌群训练项目编号

### 🧩 题目描述

给定一个单向链表 `head`，其中每个节点表示一个核心肌群训练项目的编号。请你查找并返回**倒数第 `cnt` 个节点**（从 1 开始计数）的节点指针。

------

### 🧪 示例

| 输入                      | 输出 |
| ------------------------- | ---- |
| head = [2,4,7,8], cnt = 1 | 8    |
| head = [2,4,7,8], cnt = 2 | 7    |

------

### ✅ 解题思路一：使用栈

#### 🌟 思路解析

- 遍历链表并将每个节点指针压入栈中
- 栈的特点是**后进先出**，因此最后一个元素正是倒数第一个
- 从栈中弹出 `cnt - 1` 个元素后，栈顶即为倒数第 `cnt` 个节点

#### ✅ 时间复杂度 & 空间复杂度

- 时间复杂度：O(n)
- 空间复杂度：O(n)

------

### 💻 代码实现（C++）

```cpp
class Solution {
public:
    ListNode* trainingPlan(ListNode* head, int cnt) {
        stack<ListNode*> nodes;

        // Step 1: 遍历链表，将所有节点压入栈中
        while (head) {
            nodes.push(head);
            head = head->next;
        }

        // Step 2: 弹出 cnt-1 次
        for (int i = 1; i < cnt; i++) {
            if (!nodes.empty()) nodes.pop();
        }

        // Step 3: 返回栈顶即为倒数第 cnt 个节点
        return nodes.empty() ? nullptr : nodes.top();
    }
};
```

------

### 🔁 解法二：双指针法（快慢指针）【推荐优化】

#### 🌟 思路解析

- 让第一个指针先走 `cnt` 步
- 然后第二个指针和第一个指针一起走
- 当第一个指针到达链表末尾时，第二个指针刚好在倒数第 `cnt` 个位置

#### ✅ 优点

- 时间复杂度：O(n)
- 空间复杂度：**O(1)**（无需额外空间）

#### ✅ C++ 实现

```cpp
class Solution {
public:
    ListNode* trainingPlan(ListNode* head, int cnt) {
        ListNode* fast = head;
        ListNode* slow = head;

        // fast 先走 cnt 步
        for (int i = 0; i < cnt; ++i) {
            fast = fast->next;
        }

        // fast 与 slow 同步移动
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        return slow;
    }
};
```

------

### 📝 总结

| 方法     | 时间复杂度 | 空间复杂度 | 适用场景           |
| -------- | ---------- | ---------- | ------------------ |
| 栈法     | O(n)       | O(n)       | 简单直观           |
| 双指针法 | O(n)       | O(1)       | 面试推荐、空间优化 |

## 🔗 合并两个有序链表（训练计划合并）

### 🧩 题目描述

给定两个以有序链表形式记录的训练计划 `l1` 和 `l2`，请将这两个训练项目编号的链表合并成一个升序的新链表，并返回其头节点。

> 注意：新链表通过拼接原链表中的所有节点组成。

------

### 🧪 示例

| 输入                       | 输出          |
| -------------------------- | ------------- |
| l1 = [1,2,4], l2 = [1,3,4] | [1,1,2,3,4,4] |
| l1 = [], l2 = []           | []            |
| l1 = [], l2 = [0]          | [0]           |



------

### ✅ 解题思路：递归合并链表

#### 🌟 核心思路

- 比较两个链表的当前节点 `val`
- 谁小就把谁作为当前节点，并递归处理其 `next` 与另一个链表
- 递归结束条件是某一链表为空，返回另一个链表

------

### 💻 代码实现（C++）

```
class Solution {
public:
    ListNode* trainningPlan(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        else if (!l2) return l1;

        if (l1->val < l2->val) {
            l1->next = trainningPlan(l1->next, l2);
            return l1;
        } else {
            l2->next = trainningPlan(l1, l2->next);
            return l2;
        }
    }
};
```

------

### 🔁 迭代解法（非递归）

如担心递归栈过深，可使用迭代方式更安全：

```
class Solution {
public:
    ListNode* trainningPlan(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        // 拼接剩余部分
        tail->next = l1 ? l1 : l2;

        return dummy.next;
    }
};
```

------

### ⏱ 时间 & 空间复杂度分析

| 方法 | 时间复杂度 | 空间复杂度 | 说明             |
| ---- | ---------- | ---------- | ---------------- |
| 递归 | O(n + m)   | O(n + m)   | 调用栈空间       |
| 迭代 | O(n + m)   | O(1)       | 原地合并，无需栈 |



------

### 📝 总结

- 递归写法优雅，逻辑清晰，但存在栈溢出风险（大数据时不推荐）
- 面试中更推荐迭代写法，稳健且性能更佳
- 本题核心是：**利用两个指针**遍历并合并d

------

## 🔗 找出两个训练计划链表的第一个相交项目编号（链表相交）

### 🧩 题目描述

教练为两位学员制定了两套训练计划 `l1` 和 `l2`，前半段热身部分不同，但从某个节点开始，**正式训练项目完全一致**（即链表相交）。请找出第一个正式训练项目的编号（即第一个相交节点）。

若两条链表不相交，则返回 `nullptr`。

------

### 🧪 示例

#### 示例 1

```
输入：intersectVal = 8
listA = [4,1,8,4,5]
listB = [5,0,1,8,4,5]
skipA = 2
skipB = 3
输出：8
```

#### 示例 2

```
输入：intersectVal = 2
listA = [0,9,1,2,4]
listB = [3,2,4]
skipA = 3
skipB = 1
输出：2
```

#### 示例 3

```
输入：intersectVal = 0
listA = [2,6,4]
listB = [1,5]
输出：null
```

------

### ✅ 解题思路：对齐链表长度 + 同步遍历

#### 🌟 思路解析

- 获取两个链表的长度 `lenA` 和 `lenB`
- 让较长链表先走 `|lenA - lenB|` 步，使两链表“对齐”
- 然后两个指针一起走，直到找到**相同节点（地址相等）**或到达末尾

------

### 💻 代码实现（C++）

```cpp
class Solution {
public:
    int length(ListNode* head) {
        int res = 0;
        while (head) {
            head = head->next;
            res++;
        }
        return res;
    }

    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int lenA = length(headA);
        int lenB = length(headB);

        // 对齐起点
        while (lenA > lenB) {
            headA = headA->next;
            lenA--;
        }
        while (lenB > lenA) {
            headB = headB->next;
            lenB--;
        }

        // 同步前进，直到相交或为空
        while (headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }

        return headA; // 或 nullptr
    }
};
```

------

### 🧠 时间复杂度 & 空间复杂度

| 项目 | 复杂度                        |
| ---- | ----------------------------- |
| 时间 | O(n + m) — 遍历两个链表各一次 |
| 空间 | O(1) — 只使用常量级指针       |

------

### 📌 其它做法（拓展）：双指针不对齐法

利用两个指针分别从 `headA` 和 `headB` 开始，走到末尾后**跳到对方的链表头**继续走，最终一定会在交点处同步：

```cpp
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* a = headA;
        ListNode* b = headB;

        while (a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }

        return a;
    }
};
```

#### ✅ 特点

- **不显式计算长度**
- 简洁优雅，最推荐！

------

### 📝 总结

- 判断链表相交，需要比较的是 **节点地址（指针）** 而不是节点值
- 方法一：计算长度，前进差值，再同步遍历
- 方法二：双指针法，走完两轮后对齐同步点

## 🧬 复制含随机指针的复杂链表（`copyRandomList`）

### 🧩 题目描述

给定一个**复杂链表**，其中每个节点除了有一个 `next` 指针，还有一个 `random` 指针，指向链表中任意节点或 `null`。

请**深拷贝**整个链表，并返回新链表的头节点。

------

### 🧪 示例

输入格式为 `[val, random_index]`，`random_index` 表示该节点 `random` 指向的节点下标。

#### 示例 1：

```
输入：[[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
```

#### 示例 2：

```
输入：[[1,1],[2,1]]
输出：[[1,1],[2,1]]
```

#### 示例 3：

```
输入：[[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
```

#### 示例 4：

```
输入：[]
输出：[]
```

------

### ✅ 解题思路：哈希表映射法（原节点 → 克隆节点）

#### 🌟 核心逻辑：

1. 第一次遍历：复制所有节点的值（不管 `random`），并建立映射 `old → new`
2. 第二次遍历：为每个新节点设置 `random` 指针，利用哈希表查找

------

### 💻 C++ 实现（你已写出的代码）

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        std::map<Node*, Node*> nodeMap;

        // Step 1: 复制节点，建立映射
        Node* oldNode = head;
        Node* newHead = new Node(oldNode->val);
        nodeMap[oldNode] = newHead;

        Node* newNode = newHead;
        oldNode = oldNode->next;

        while (oldNode) {
            Node* clone = new Node(oldNode->val);
            nodeMap[oldNode] = clone;
            newNode->next = clone;
            newNode = newNode->next;
            oldNode = oldNode->next;
        }

        // Step 2: 设置 random 指针
        oldNode = head;
        newNode = newHead;

        while (oldNode) {
            newNode->random = oldNode->random ? nodeMap[oldNode->random] : nullptr;
            oldNode = oldNode->next;
            newNode = newNode->next;
        }

        return newHead;
    }
};
```

------

### ⏱ 时间 & 空间复杂度分析

| 项目       | 复杂度                  |
| ---------- | ----------------------- |
| 时间复杂度 | O(n)                    |
| 空间复杂度 | O(n) — 由于使用了哈希表 |



------

### 🧠 拓展解法：**不使用额外空间（链表穿插法）**

#### 步骤：

1. 在每个原节点后面插入克隆节点（A→A'→B→B'...）
2. 设置克隆节点的 `random`：`A'->random = A->random->next`
3. 拆分两个链表

#### C++ 实现（进阶）

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        // Step 1: 复制每个节点，插入原节点后
        Node* cur = head;
        while (cur) {
            Node* clone = new Node(cur->val);
            clone->next = cur->next;
            cur->next = clone;
            cur = clone->next;
        }

        // Step 2: 设置 random 指针
        cur = head;
        while (cur) {
            if (cur->random)
                cur->next->random = cur->random->next;
            cur = cur->next->next;
        }

        // Step 3: 拆分两个链表
        cur = head;
        Node* cloneHead = head->next;
        Node* cloneCur = cloneHead;

        while (cur) {
            cur->next = cur->next->next;
            if (cloneCur->next)
                cloneCur->next = cloneCur->next->next;
            cur = cur->next;
            cloneCur = cloneCur->next;
        }

        return cloneHead;
    }
};
```

------

### 📝 总结

| 方法               | 时间复杂度 | 空间复杂度 | 特点                 |
| ------------------ | ---------- | ---------- | -------------------- |
| 哈希表映射法       | O(n)       | O(n)       | 简单易写             |
| 原地穿插法（进阶） | O(n)       | O(1)       | 面试高频考法，省空间 |