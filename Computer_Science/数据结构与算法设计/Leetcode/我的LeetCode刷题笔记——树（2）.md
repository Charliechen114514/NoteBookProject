# Leetcode刷题笔记：树（2）

------

## 1. 二叉树基本概念

- **节点（Node）**包含值 `val` 和两个指针：`left`（左子树）和 `right`（右子树）；
- **空树**指根节点为空，深度为0；
- **深度（高度）**是根节点到最深叶子节点的最长路径长度；
- **二叉搜索树（BST）**是特殊的二叉树，左子树所有节点值小于根节点值，右子树所有节点值大于根节点值。

------

## 2. 二叉树遍历方式

- **前序遍历**：根 → 左 → 右；
- **中序遍历**：左 → 根 → 右；
- **后序遍历**：左 → 右 → 根；
- **层序遍历（BFS）**：按层自上而下访问。

------

## 3. 常见问题类型与技巧

### 3.1 判断子树关系

- 递归比较两个节点及其子树是否结构和值完全一致；
- 遍历大树的每个节点，寻找与小树根节点匹配的子树。

### 3.2 二叉树左右翻转

- 利用递归后序遍历，交换每个节点的左右子节点指针；
- 可实现树结构的镜像变换。

### 3.3 判断轴对称树

- 判断左子树和右子树是否镜像对称；
- 递归比较左子树的左节点与右子树的右节点，左子树的右节点与右子树的左节点。

### 3.4 二叉搜索树与链表转换

- 利用BST的中序遍历特性得到递增序列；
- 就地将节点通过左右指针转化为双向循环链表。

### 3.5 第 K 大节点查找

- 利用BST的**反中序遍历**（右 → 根 → 左）得到降序序列；
- 可通过计数剪枝优化空间和时间。

### 3.6 计算树的层级数

- 递归计算左右子树深度的最大值加1；
- 也可用层序遍历统计层数。

### 3.7 判断平衡二叉树

- 递归计算子树高度，同时判断子树是否平衡；
- 优化版本通过后序遍历一次计算高度和判定。

------

## 4. 解题技巧总结

- **递归遍历是基础**：掌握递归的设计和终止条件，理解如何自底向上或自顶向下传递信息。
- **剪枝优化**：遇到不满足条件的情况，及时返回，避免无谓计算。
- **利用BST性质**：中序遍历的有序性为搜索和排序类题目提供便利。
- **空间优化**：根据题目要求选择递归或迭代，甚至Morris遍历实现O(1)空间。
- **链表与树的转换**：树节点指针可灵活变为链表指针，题目中经常用此技巧。

------

## 5. 复杂度考虑

- 遍历类操作时间复杂度通常是 O(n)，n为节点数；
- 空间复杂度由递归深度（树高度）或辅助数据结构决定；
- 在二叉树问题中，平衡树高度为 O(log n) 能显著降低空间复杂度。

# ✅ 子树判断

给定两棵二叉树 `tree1` 和 `tree2`，判断 `tree2` 是否是 `tree1` 的某个**子树**。
 “子树”在这里的定义是：以 `tree1` 的某个节点为根的子树，其**结构和节点值**必须与 `tree2` 完全相同。

**注意：**

- 空树不能作为子树进行匹配。
- 匹配时必须**结构一致 + 节点值一致**。

------

## 🧠 解题思路

这是一道**树的遍历 + 递归判断结构**的问题，思路如下：

1. **主函数思路（isSubStructure）**：
   - 遍历 tree1 的每个节点；
   - 如果某个节点值和 tree2 根节点值相等，则进一步判断两个树是否完全相同。
2. **辅助函数（isSubTree）**：
   - 判断以当前节点为根的两棵树是否**结构完全相同且节点值一致**。

------

## ✅ 修正后的代码

```cpp
class Solution {
public:
    // 判断两棵树是否完全相同（结构 + 值）
    bool isSameTree(TreeNode* A, TreeNode* B){
        if (!A && !B) return true;
        if (!A || !B) return false;
        if (A->val != B->val) return false;
        return isSameTree(A->left, B->left) && isSameTree(A->right, B->right);
    }

    // 遍历 tree1 的每个节点，查找匹配子树
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root || !subRoot) return false;
        return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};
```

------

## 🧮 复杂度分析

- **时间复杂度：** O(m * n)
  - `m` 是 tree1 的节点数，`n` 是 tree2 的节点数；
  - 最坏情况要对 tree1 的每个节点都尝试匹配一次 tree2。
- **空间复杂度：** O(h)
  - `h` 为树的最大深度，用于递归调用栈。

------

## 🧪 测试示例回顾

### 示例 1：

```text
tree1 = [1,7,5]
tree2 = [6,1]
输出：false
```

### 示例 2：

```text
tree1 = [3,6,7,1,8]
tree2 = [6,1]
输出：true
```

------

# 🧠翻转二叉树

> 给定一棵二叉树，请**左右翻转**它，也就是对每一个节点：交换它的左子树和右子树，最终返回新的根节点。

------

## ✅ 示例说明

### 输入：

```
          5
        /   \
       7     9
      / \   / \
     8   3 2   4
```

### 输出（左右翻转后）：

```
          5
        /   \
       9     7
      / \   / \
     4   2 3   8
```

### 输出层序遍历为：

```
[5, 9, 7, 4, 2, 3, 8]
```

------

## ✅ 解题思路

这实际上是一个**递归后序遍历**的题：

- 对当前节点的左右子树进行递归翻转；
- 然后**交换**当前节点的 `left` 和 `right` 指针。

### 🔁 步骤：

1. 递归终止条件：节点为空，返回空。
2. 对左右子树分别调用 `flipTree`。
3. 交换 `left` 和 `right`。
4. 返回当前节点。

------

## ✅ 正确代码

```cpp
class Solution {
public:
    TreeNode* flipTree(TreeNode* root) {
        if (!root) return nullptr;

        TreeNode* left = flipTree(root->left);
        TreeNode* right = flipTree(root->right);

        root->left = right;
        root->right = left;

        return root;
    }
};
```

------

## 📊 复杂度分析

- **时间复杂度：** O(n)
  - 每个节点访问一次。
- **空间复杂度：** O(h)
  - 递归栈深度为树的高度，最坏为 O(n)，平均为 O(log n)。

------

## 🧪 测试样例

```cpp
// 示例输入: [5,7,9,8,3,2,4]
// 构造原树并翻转后验证层序遍历是否为 [5,9,7,4,2,3,8]
```

# ✅ 判断一棵二叉树是否**轴对称**

设计一个函数判断一棵二叉树是否**轴对称**（Symmetric Tree）。

即对于一棵树，判断其**左子树和右子树是否互为镜像**。

------

## 🧠 解题思路

### 思考“轴对称”的本质：

一棵树是对称的，当且仅当：

> 左子树与右子树互为镜像。

### 镜像条件：

- 两个节点都为空 → ✅
- 一个为空，一个不为空 → ❌
- 两者值不等 → ❌
- 递归检查：
  - `left->left` vs `right->right`
  - `left->right` vs `right->left`

------

## ✅ 代码

```cpp
class Solution {
public:
    // 判断两个子树是否为镜像结构
    bool checkSub(TreeNode* left, TreeNode* right)
    {
        if(left && !right) return false;
        if(!left && right) return false;
        if(!left && !right) return true;
        if(left->val != right->val) return false;

        // 左左对右右，左右对右左
        return checkSub(left->left, right->right) && checkSub(left->right, right->left);
    }

    bool checkSymmetricTree(TreeNode* root) {
        if(!root) return true;  // 空树是对称的
        return checkSub(root->left, root->right);
    }
};
```

------

## 📊 复杂度分析

- **时间复杂度：** O(n)
  - 访问每个节点一次。
- **空间复杂度：** O(h)
  - 递归栈深度，最坏为 O(n)，平均为 O(log n)。

------

## 🧪 示例

```text
输入：
    1
   / \
  2   2
 / \ / \
3  4 4  3

输出：true

输入：
    1
   / \
  2   2
   \   \
   3    3

输出：false
```

------

## 📌 拓展：迭代版

如你希望写成非递归版本，也可以使用队列来实现：

```cpp
bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);
    while (!q.empty()) {
        TreeNode* left = q.front(); q.pop();
        TreeNode* right = q.front(); q.pop();
        if (!left && !right) continue;
        if (!left || !right || left->val != right->val) return false;
        q.push(left->left);
        q.push(right->right);
        q.push(left->right);
        q.push(right->left);
    }
    return true;
}
```

------

当然可以！以下是**合并后的完整版题解**，包含：

- ✅ 题目解析
- 🧠 中序递归解法（你已实现的方式）
- 🔁 迭代写法（显式栈）
- 🌱 Morris Traversal 解法（O(1) 空间）
- 📊 复杂度分析
- 🧪 测试示例

------

# 🏷️题目：二叉搜索树转双向循环链表

## ✅ 题目要求

将一棵**二叉搜索树（BST）\**就地（in-place）转化为一个\**已排序的双向循环链表**。

### ✅ 要求：

- 每个节点的 `left` 指针为前驱，`right` 为后继；
- 转换后链表是**循环的**；
- **原地转换**，不新建额外节点；
- 返回链表中**最小节点**指针（即升序链表的头）。

------

## 🧠 解题思路

### ✨ 核心性质：

- **BST 的中序遍历**是**升序序列**；
- 可以用中序遍历将节点按顺序连接成链表。

### 🛠️ 转换方式：

1. 中序遍历（递归或迭代）；
2. 每访问一个节点，令其与前一个节点双向连接；
3. 最终将头尾连接，形成**循环链表**。

------

## ✍️ 方案一：递归中序遍历（推荐 ✅）

```cpp
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr) return nullptr;

        dfs(root);

        // 收尾连接
        head->left = pre;
        pre->right = head;

        return head;
    }

private:
    Node* head = nullptr;  // 最小节点（链表头）
    Node* pre = nullptr;   // 中序遍历的前一个节点

    void dfs(Node* cur) {
        if (!cur) return;

        dfs(cur->left);

        // 串联前驱和当前节点
        if (pre) {
            pre->right = cur;
            cur->left = pre;
        } else {
            head = cur; // 第一个访问到的节点为最小节点
        }

        pre = cur;

        dfs(cur->right);
    }
};
```

------

## 🔁 方案二：迭代中序遍历（显示栈）

```cpp
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return nullptr;

        stack<Node*> stk;
        Node* cur = root;
        Node* head = nullptr;
        Node* pre = nullptr;

        while (cur || !stk.empty()) {
            while (cur) {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top(); stk.pop();

            if (pre) {
                pre->right = cur;
                cur->left = pre;
            } else {
                head = cur;
            }

            pre = cur;
            cur = cur->right;
        }

        // 收尾连接
        head->left = pre;
        pre->right = head;

        return head;
    }
};
```

------

## 🌱 方案三：Morris 中序遍历（O(1) 空间）

> 使用 Morris Traversal 实现中序遍历，不需要递归或栈。

```cpp
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return nullptr;

        Node* cur = root;
        Node* pre = nullptr;
        Node* head = nullptr;

        while (cur) {
            if (!cur->left) {
                if (pre) {
                    pre->right = cur;
                    cur->left = pre;
                } else {
                    head = cur;
                }
                pre = cur;
                cur = cur->right;
            } else {
                Node* pred = cur->left;
                while (pred->right && pred->right != cur) {
                    pred = pred->right;
                }

                if (!pred->right) {
                    pred->right = cur;
                    cur = cur->left;
                } else {
                    pred->right = nullptr;

                    if (pre) {
                        pre->right = cur;
                        cur->left = pre;
                    } else {
                        head = cur;
                    }
                    pre = cur;
                    cur = cur->right;
                }
            }
        }

        // 收尾连接
        head->left = pre;
        pre->right = head;

        return head;
    }
};
```

------

## 📊 复杂度分析

| 方法       | 时间复杂度 | 空间复杂度  |
| ---------- | ---------- | ----------- |
| 递归       | O(n)       | O(h) 递归栈 |
| 迭代（栈） | O(n)       | O(h) 显式栈 |
| Morris     | O(n)       | O(1)        |

其中，`h` 是树的高度，最坏为 `O(n)`，平均为 `O(log n)`。

------

## 🧪 示例

输入 BST：

```
      4
     / \
    2   5
   / \
  1   3
```

输出：双向循环链表（按右指针遍历）：

```
1 <-> 2 <-> 3 <-> 4 <-> 5
^                       |
|_______________________|
```

------

# ✅ 找出 **第 `cnt` 大** 的员工编号。

给定一棵 **二叉搜索树（BST）**，每个节点代表一名员工编号，要求找出 **第 `cnt` 大** 的员工编号。

### ✅ BST 的性质：

- 中序遍历（左→根→右）得到的是 **升序序列**；
- 反中序遍历（右→根→左）得到的是 **降序序列**；
  - 第 `cnt` 大的节点就是**反中序遍历的第 `cnt` 个节点**。

------

## ✍️ （中序遍历+数组保存）

```cpp
class Solution {
public:
    vector<int> res;

    void inOrder(TreeNode* node){
        if(node->left) inOrder(node->left);
        res.push_back(node->val);
        if(node->right) inOrder(node->right);
    }

    int findTargetNode(TreeNode* root, int cnt) {
        inOrder(root);
        return res[res.size() - cnt];
    }
};
```

### ✅ 优点：

- 利用了 BST 的中序遍历特性。
- 实现简洁清晰。

### ⚠️ 问题：

- 中序遍历会保存**整个节点数组**，空间复杂度为 O(n)；
- 无法提前剪枝（即便找到目标也仍然遍历后续节点）。

------

## 🚀 推荐：反中序剪枝法（空间更优）

只遍历到第 `cnt` 个节点即可，无需存数组。

```cpp
class Solution {
public:
    int res = -1;     // 用于记录第 cnt 大的值
    int count = 0;    // 当前访问了几个节点

    void reverseInOrder(TreeNode* node, int cnt) {
        if (!node || count >= cnt) return;

        reverseInOrder(node->right, cnt);

        count++;
        if (count == cnt) {
            res = node->val;
            return;
        }

        reverseInOrder(node->left, cnt);
    }

    int findTargetNode(TreeNode* root, int cnt) {
        reverseInOrder(root, cnt);
        return res;
    }
};
```

------

## 📊 复杂度分析

| 方法              | 时间复杂度 | 空间复杂度 |
| ----------------- | ---------- | ---------- |
| 中序 + 全数组存储 | O(n)       | O(n)       |
| 反中序 + 剪枝优化 | O(h + cnt) | O(h)       |

其中：

- `n` 是节点总数；
- `h` 是树的高度，平均 O(log n)，最坏 O(n)。

------

## 🧪 测试示例

```text
输入 BST：
        5
       / \
      3   8
     / \   \
    2   4   10

中序遍历： [2, 3, 4, 5, 8, 10]
cnt = 2

输出：8（第2大的值）
```

------

# ✅ 求解二叉树高度

某公司组织架构以**二叉树**形式存储，求该公司的**层级数**。

### 举例：

```
         CEO
        /   \
     CTO     CFO
    /           \
Engineer      Finance
```

这棵树的层级数为 **3**。

------

## 🧠 解题思路

> 树的“层级数”就是树的**最大深度**，即从根节点到最深叶子节点路径上的节点数。

可以使用 **递归 DFS** 实现：

1. 如果当前节点为空，深度为 0；
2. 递归获取左子树和右子树的最大深度；
3. 当前节点的深度 = `max(左, 右) + 1`。

------

## ✅ 代码实现（你的代码）

```cpp
class Solution {
public:
    int calculateDepth(TreeNode* root) {
        if (!root) return 0;
        return max(calculateDepth(root->left), calculateDepth(root->right)) + 1;
    }
};
```

------

## 📊 复杂度分析

- **时间复杂度：** O(n)
   遍历每个节点一次。
- **空间复杂度：**
  - 最坏 O(n)：树为单链时递归栈深度；
  - 平均 O(log n)：平衡树的递归栈深度。

------

## 🔁 拓展：迭代层序遍历（BFS 写法）

可选写法，利用队列按层处理：

```cpp
class Solution {
public:
    int calculateDepth(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;

        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                TreeNode* node = q.front(); q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            depth++;
        }
        return depth;
    }
};
```

好的！以下是结合你代码的完整题解，并补充了优化方案，整理成结构化的内容，适合面试笔记或复习。

------

# 判断二叉树是否为平衡二叉树

------

## 题目描述

给定一棵二叉树的根节点，判断该树是否为**平衡二叉树**。

**平衡二叉树定义：** 对于二叉树中的任意节点，其左右子树的深度差不超过1。

------

## 解题思路

1. **递归计算节点高度**
    对于当前节点，递归计算其左右子树高度。
2. **判断平衡条件**
    如果当前节点左右子树高度差超过1，则该树不平衡。
3. **递归判断左右子树**
    需要保证当前节点左右子树都是平衡的。

------

## 代码实现（递归判断）

```cpp
class Solution {
public:
    // 计算树高度
    int height(TreeNode* root){
        if(!root) return 0;
        return max(height(root->left), height(root->right)) + 1;
    }

    // 判断平衡
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        return abs(height(root->left) - height(root->right)) <= 1
               && isBalanced(root->left)
               && isBalanced(root->right);
    }
};
```

### 代码说明：

- `height` 函数返回以 `root` 为根的子树高度；
- `isBalanced` 函数先判断当前节点左右子树高度差是否符合要求，再递归判断左右子树是否平衡。

------

## 该方法的问题

- **重复计算子树高度**，导致时间复杂度较高；
- 最坏情况下会达到 O(n²)，不适合节点数较大的情况。

------

## 优化方案：后序遍历一趟计算

结合高度计算与平衡判断，使用后序遍历：

- 用特殊返回值 `-1` 表示不平衡；
- 遍历过程中一旦发现不平衡即停止。

```cpp
class Solution {
public:
    int checkHeight(TreeNode* root) {
        if(!root) return 0;

        int left = checkHeight(root->left);
        if(left == -1) return -1;

        int right = checkHeight(root->right);
        if(right == -1) return -1;

        if(abs(left - right) > 1) return -1;

        return max(left, right) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }
};
```

------

## 复杂度分析

| 方法                 | 时间复杂度 | 空间复杂度  |
| -------------------- | ---------- | ----------- |
| 递归分治（你的代码） | O(n²)      | O(h) 递归栈 |
| 优化后序遍历         | O(n)       | O(h) 递归栈 |

其中，`h` 为树的高度。

