# 我的LeetCode刷题笔记——树（1）

## 📚 前导知识总结：掌握「Z 字形层序遍历」的基础

------

### 🌲 1. 二叉树基本概念

- **二叉树（Binary Tree）**：每个节点最多有两个子节点（分别为左子节点和右子节点）。
- **根节点（Root）**：树的最顶层节点。
- **叶子节点（Leaf）**：没有任何子节点的节点。
- **层级结构（Level）**：根节点为第 0 层，它的子节点为第 1 层，以此类推。

------

### 🔁 2. 二叉树遍历方式概览

| 遍历方式 | 特点                 | 实现方法 |
| -------- | -------------------- | -------- |
| 前序遍历 | 根 -> 左 -> 右       | DFS      |
| 中序遍历 | 左 -> 根 -> 右       | DFS      |
| 后序遍历 | 左 -> 右 -> 根       | DFS      |
| 层序遍历 | 按层从上到下逐层访问 | BFS      |

------

### 🚀 3. 层序遍历（Level Order Traversal）

- 层序遍历是一种 **广度优先搜索（BFS）**。
- 核心数据结构是 **队列（queue）**。
- 按层访问节点，逐层记录每一层所有节点的值。

#### 示例代码框架：

```cpp
queue<TreeNode*> q;
q.push(root);
while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
        TreeNode* node = q.front(); q.pop();
        // 处理 node
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

------

### ⚡ 4. Z 字形层序遍历（Zigzag Level Order）

在层序遍历的基础上增加一个“**方向交替**”的逻辑：

- 第一层从左到右；
- 第二层从右到左；
- 第三层再从左到右；
- 依此类推，形成类似 “Z” 字的形状。

#### 关键实现技巧：

- 使用 `bool` 标志变量 `left_to_right` 控制每层方向；
- 使用 `reverse()` 反转当前层结果，或在加入结果时使用 `deque` 的头尾插入控制顺序；
- 每层遍历完成后切换方向标志。

------

### 🧠 5. 为什么要掌握这类变形 BFS？

- 许多实际问题（如矩阵遍历、图搜索）都以 BFS 为基础；
- 面试常考各种层序变形（如求每层最大值、锯齿形遍历、偶数层处理等）；
- 扎实掌握基本 BFS 框架 + 控制细节（如顺序/反转）是刷题的核心技能。

------

### 🧩 本题关联的知识点回顾：

| 知识点              | 说明                                         |
| ------------------- | -------------------------------------------- |
| 二叉树建模          | 用数组 `[8,17,21,18,null,null,6]` 表示树结构 |
| BFS 层序遍历        | 使用队列实现层级访问                         |
| Z 字形输出          | 控制每层输出方向，形成锯齿形排列             |
| 时间/空间复杂度分析 | 提高代码性能意识                             |

------

### ✅ 建议刷题顺序（逐步加深）：

1. **基础层序遍历**
   - 例题：LeetCode 102. 二叉树的层序遍历
2. **Z 字形层序遍历（本题）**
   - 例题：LeetCode 103. Binary Tree Zigzag Level Order Traversal
3. **每层最大值 / 求和 / 最小值**
   - 例题：LeetCode 515. 在每个树行中找最大值
4. **自下而上层序遍历**
   - 例题：LeetCode 107. Binary Tree Level Order Traversal II



## 🧩 题目描述：遍历圣诞树1

给定一棵表示圣诞树的**二叉树**，每个节点代表该位置挂的彩灯颜色编号（一个整数）。请**从上到下、从左到右**返回每一层的彩灯编号排列。

------

### ✅ 示例：

**输入：**

```cpp
root = [8,17,21,18,null,null,6]
```

对应的树结构为：

```
        8
       / \
     17   21
     /      \
   18        6
```

**输出：**

```
[8, 17, 21, 18, 6]
```

------

### 💡 解题思路：

本题是典型的**层序遍历（BFS）**问题。核心思想是：

1. 使用一个队列（`deque`）来按层逐个处理每个节点；
2. 每次从队列中取出当前节点，将其值加入结果数组；
3. 如果当前节点存在左/右子节点，则将其加入队列，等待后续遍历。

------

### 📌 代码详解：

```cpp
class Solution {
public:
    vector<int> decorateRecord(TreeNode* root) {
        deque<TreeNode*> iterating_queue; // 队列用于按层遍历
        vector<int> result {}; // 存放结果

        iterating_queue.push_back(root); // 将根节点加入队列

        while(!iterating_queue.empty()){ // 队列不空就继续处理
            TreeNode* front_one = iterating_queue.front(); // 获取当前队首元素
            
            if(!front_one) { // 如果是空节点，跳过
                iterating_queue.pop_front();
                continue;
            }

            // 左右子节点入队
            if(front_one->left){
                iterating_queue.push_back(front_one->left);
            }
            if(front_one->right){
                iterating_queue.push_back(front_one->right);
            }

            result.push_back(front_one->val); // 保存当前节点的值
            iterating_queue.pop_front(); // 弹出当前节点
        }

        return result;
    }
};
```

------

### 🧠 时间与空间复杂度：

- **时间复杂度：** O(n)，每个节点遍历一次；
- **空间复杂度：** O(n)，最坏情况下队列中可能存储 n 个节点（如完全二叉树的最后一层）。

------

### 📎 备注：

- 本实现不会漏掉任一非空节点，且保证输出顺序是**从上到下、从左到右**；
- 空节点会被跳过，符合题意。



------

## 🧩 遍历圣诞树2

给定一棵代表圣诞树的**二叉树**，每个节点值表示该处彩灯的颜色编号。请**按层级从左到右**返回每一层的彩灯颜色编号，每层结果为一个数组，整体结果是二维数组。

------

### ✅ 示例：

**输入：**

```cpp
root = [8,17,21,18,null,null,6]
```

构建的二叉树如下：

```
        8
       / \
     17   21
     /      \
   18        6
```

**输出：**

```cpp
[[8], [17, 21], [18, 6]]
```

------

### 💡 解题思路：

本题本质上是经典的 **二叉树层序遍历（BFS）**。我们使用一个队列按层依次遍历，并在每层遍历时将结果单独存入一个数组，最终组合为二维数组返回。

------

### 📌 代码详解：

```cpp
class Solution {
public:
    vector<vector<int>> decorateRecord(TreeNode* root) {
        queue<TreeNode*> que;         // 用于层序遍历的队列
        vector<vector<int>> res;      // 最终结果

        if(root) que.push(root);      // 非空根节点入队

        while(!que.empty()) {
            vector<int> tmp;          // 存储当前层的节点值
            int n = que.size();       // 当前层的节点数量

            for(int i = 0; i < n; ++i) {
                TreeNode* node = que.front(); que.pop();
                tmp.push_back(node->val);     // 加入当前层的结果

                if(node->left) que.push(node->left);   // 左子节点入队
                if(node->right) que.push(node->right); // 右子节点入队
            }

            res.push_back(tmp); // 当前层结束，加入总结果
        }

        return res;
    }
};
```

------

### 🧠 时间与空间复杂度：

- **时间复杂度：** O(n)
   每个节点入队、出队各一次，n 为节点总数；
- **空间复杂度：** O(n)
   最多 n 个节点同时存在于队列中（完全二叉树最后一层时）；

------

### 🔎 总结：

该解法简洁高效，利用 BFS 遍历二叉树结构并按层收集结果，非常适用于层级输出的问题。

如果你想扩展为**自上而下或自下而上**排序，或者加入 **Z字形遍历**（之字形层序遍历），也可以很方便在这个基础上修改实现。欢迎继续提问！

当然可以！以下是你这道题（Z 字形层序遍历）的**高质量题解**，适合用于刷题笔记、提交备注，或者分享给他人。

------

## 🧩 遍历圣诞树3

一棵圣诞树被建模为一棵二叉树，根节点为 `root`，每个节点上的值代表该位置装饰彩灯的颜色编号。

请你按如下规则返回圣诞树的彩灯装饰顺序：

- 第一层：从左到右记录；
- 第二层：从右到左记录；
- 第三层：从左到右；
- 依此类推，**每一层的顺序与上一层相反**。

------

### ✅ 示例：

**输入：**

```
root = [8,17,21,18,null,null,6]
```

对应二叉树结构：

```
        8
       / \
     17   21
     /      \
   18        6
```

**输出：**

```
[[8], [21, 17], [18, 6]]
```

------

## 💡 解题思路：

这是一道典型的**二叉树层序遍历（BFS）**变形题。我们按层遍历节点值的同时，根据当前层的顺序需求（从左到右或从右到左）来调整输出结果。

### 算法步骤：

1. 使用一个 `deque`（双端队列）或 `queue` 存储当前层待处理节点；
2. 每次处理当前层所有节点，并将它们的子节点入队；
3. 对当前层的值进行处理：
   - 如果该层应该**从右到左**，则将结果 `reverse`；
4. 将处理完的当前层值加入最终结果；
5. 切换下一层方向标志。

------

## ✅ 代码实现（C++）

```cpp
class Solution {
public:
    vector<vector<int>> decorateRecord(TreeNode* root) {
        vector<vector<int>> res;
        deque<TreeNode*> queue;
        if(root) queue.push_back(root);

        bool shell_reverse = true; // 用于控制是否翻转当前层

        while(!queue.empty()){
            vector<int> current_session;
            int size = queue.size();

            for(int i = 0; i < size; i++){
                TreeNode* front_one = queue.front();
                queue.pop_front();

                current_session.push_back(front_one->val);

                if(front_one->left) queue.push_back(front_one->left);
                if(front_one->right) queue.push_back(front_one->right);
            }

            res.push_back(current_session);
        }

        // 根据层数反转部分层的值
        for(int i = 0; i < res.size(); i++) {
            shell_reverse = !shell_reverse;
            if(shell_reverse) {
                reverse(res[i].begin(), res[i].end());
            }
        }

        return res;
    }
};
```

------

## ⏱️ 复杂度分析：

- **时间复杂度：** O(n)
   每个节点仅访问一次。
- **空间复杂度：** O(n)
   队列和结果数组最大可能存储所有节点。

------

## 📌 总结：

- 本题是经典层序遍历的升级版，利用反转控制实现“Z字形”输出；
- 使用一个布尔变量或层数判断即可控制每层输出顺序；
- 是 BFS 在实际应用中的一个很典型变形，刷题时很有代表性。

