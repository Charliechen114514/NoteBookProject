# 我的Leetcode刷题笔记：数组

## 前言

​	这里是关于数组部分的一些刷题笔记，当然，这里更多的是考察双指针法的使用。笔者这里给出的是自己当时做题的时候的题解。一部分笔记是GPT委托整理的，放在这里供笔者后续的学习和参考

------

# 📘数组专题 · 前导知识总结

数组是编程中最基础、最常见的数据结构之一，也是各类算法题的高频考点。掌握数组题的核心思想与技巧，能显著提升刷题效率和代码质量。

------

## ✅一、常见题型分类

| 类型              | 代表题目                | 常用技巧                  |
| ----------------- | ----------------------- | ------------------------- |
| 排序与查重        | 查找文件副本            | 排序 + 相邻判断 / 哈希集  |
| 前缀 / 后缀积处理 | 排除当前值的乘积        | 前缀积、后缀积 / 除法优化 |
| 滑动窗口 / 双指针 | 连续子数组之和为 target | 双指针、等差公式          |
| 二维遍历          | 螺旋遍历矩阵            | 层次遍历 + 边界控制       |
| 分类重排          | 奇偶分类重排            | 双指针 / 快慢指针         |

------

## ✅二、核心技术要点整理

### 1. **排序 + 相邻比较**

- 用于快速检测重复元素；
- **复杂度：O(n log n)**；
- 示例：查找文件副本。

```cpp
sort(arr.begin(), arr.end());
for (int i = 1; i < arr.size(); ++i)
    if (arr[i] == arr[i - 1]) return arr[i];
```

------

### 2. **哈希集合**

- 用于 O(1) 查重或查找；
- 时间复杂度更优，适合大数据量场景；
- 示例：重复 ID 检测。

```cpp
unordered_set<int> seen;
for (int num : arr)
    if (!seen.insert(num).second) return num;
```

------

### 3. **前缀积 / 总乘积除法法**

- 用于排除某个元素计算积的场景；
- 特别注意元素为 0 的特殊处理；
- 示例：排除当前值的乘积构造。

```cpp
total_product /= arr[i]; // 如果没有 0，可以直接使用
```

------

### 4. **滑动窗口 / 双指针**

- 用于连续子数组或窗口性问题；
- 多用于查找**连续**且满足条件的片段；
- 示例：连续整数和为 target 的组合。

```cpp
int start = 1, end = 2;
while (start < end) {
    int sum = (start + end) * (end - start + 1) / 2;
    if (sum == target) // 记录解
    else if (sum < target) end++;
    else start++;
}
```

------

### 5. **模拟二维结构遍历**

- 对于矩阵类问题，合理控制边界；
- 常用于螺旋遍历、矩阵填充等；
- 示例：螺旋遍历矩阵。

```cpp
int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
while (true) {
    // 向右、向下、向左、向上
    // 每走完一圈后缩小边界
}
```

------

### 6. **分类重排（稳定性 vs 高效）**

- 一类移动到前面、另一类移到后面；
- 可使用快慢指针（稳定）或双指针交换（更快）；
- 示例：奇偶分离排序。

```cpp
int write = 0;
for (int read = 0; read < n; read++)
    if (arr[read] 是奇数)
        swap(arr[write++], arr[read]);
```

------

## 🔍三、数组刷题技巧建议

- **先暴力，再优化**：不要一开始追求最优解，先写出正确逻辑；
- **边界控制**：尤其在二维/滑动窗口题型中，需小心越界；
- **特殊值考虑**：0、负数、重复值、空数组等都是常见陷阱；
- **模板积累**：双指针、前缀积、哈希等都是经典套路，需掌握模板。

------

## 📌四、推荐 LeetCode 同类题目练习（可按模块刷）

| 题型          | 推荐题目（LeetCode 编号）                      |
| ------------- | ---------------------------------------------- |
| 排除自身乘积  | 238. Product of Array Except Self              |
| 重复元素检测  | 287. Find the Duplicate Number                 |
| 螺旋矩阵      | 54. Spiral Matrix / 59. Spiral Matrix II       |
| 连续区间求和  | 167. Two Sum II / 829. Consecutive Numbers Sum |
| 奇偶/分类重排 | 905. Sort Array by Parity！                    |





## 🏋️‍♂️调整训练项目顺序

### ✅题目描述：

给定一个整数数组 `actions`，表示一系列训练项目的编号。为了增强训练趣味性，需要将 **奇数编号的训练项目** 移动到 **偶数编号训练项目** 的前面，返回调整后的数组（**不要求保持原顺序**）。

------

## 💡思路解析：

本质上是一个“**奇偶分组**”的问题：将所有奇数移到数组前面，偶数放在后面。

### 🧠 解题思路：

1. **遍历数组**，遇到奇数就将其移到前面。
2. 使用双指针技巧：
   - `read_pos`：用于遍历数组；
   - `write_pos`：记录下一个奇数应当放的位置；
   - 每次发现奇数时，将其与当前位置 `write_pos` 的元素交换，然后将 `write_pos++`。
3. 最终可保证奇数在前、偶数在后（顺序可能会变，但符合题意）。

------

## 📦复杂度分析：

- **时间复杂度**：O(n)，仅需遍历一次数组；
- **空间复杂度**：O(1)，就地修改原数组，无需额外空间。

------

## ✅代码实现（C++）：

```cpp
class Solution {
public:
    vector<int> trainingPlan(vector<int>& actions) {
        int write_pos = 0;
        for(int read_pos = 0; read_pos < actions.size(); ++read_pos){
            if(actions[read_pos] % 2 == 1){
                std::swap(actions[write_pos++], actions[read_pos]);
            }
        }
        return actions;
    }
};
```

------

## 🧪测试用例：

| 输入          | 输出          | 说明               |
| ------------- | ------------- | ------------------ |
| `[1,2,3,4,5]` | `[1,3,5,2,4]` | 奇数排前，偶数排后 |
| `[2,4,6]`     | `[2,4,6]`     | 全为偶数，顺序不变 |
| `[1,3,5]`     | `[1,3,5]`     | 全为奇数，顺序不变 |
| `[]`          | `[]`          | 空数组             |
| `[0,1]`       | `[1,0]`       | 奇数 1 移到前面    |



------

## 🧠补充优化思考：

- 如果需要**保持原有相对顺序**（即稳定排序），则此解法不适用，应使用额外数组或`stable_partition`。
- 本题未要求稳定性，因此当前解法最优。

------

## 📁题目解析：寻找连续正整数和为 target 的所有组合

### ✅题目描述：

给定一个正整数 `target`，请找出所有 **至少包含两个连续正整数** 的组合，使得其总和恰好等于 `target`。

------

## 💡思路解析：

这道题的关键在于**寻找所有满足条件的连续整数序列**。可以采用 **双指针 + 等差数列求和公式** 来高效解题。

------

### 🧠 解题思路：

#### ✅核心思想：**滑动窗口 + 等差求和公式**

1. 使用两个指针 `start` 和 `end` 表示一个区间的起始和结束；

2. 在每次循环中，利用公式计算 `[start, end]` 区间的和：

   sum=(start+end)×(end−start+1)2\text{sum} = \frac{(start + end) \times (end - start + 1)}{2}

3. 根据 sum 与 target 的比较：

   - 如果相等，说明找到一组解，保存，并右移 `start`；
   - 如果小于 target，右移 `end` 扩大区间；
   - 如果大于 target，右移 `start` 缩小区间。

4. 终止条件为 `start < end`，因为至少要两个数。

------

## 📦复杂度分析：

- **时间复杂度**：O(√target)，因为最坏情况最多尝试到 `(start + start + 1) / 2 > target`；
- **空间复杂度**：O(1)，仅使用了常数级辅助变量，除结果外。

------

## ✅代码实现（C++）：

```cpp
class Solution {
public:
    vector<vector<int>> fileCombination(int target) {
        vector<vector<int>> result;
        int start = 1, end = 2;

        while (start < end) {
            int sum = (start + end) * (end - start + 1) / 2;

            if (sum == target) {
                vector<int> seq;
                for (int i = start; i <= end; ++i)
                    seq.push_back(i);
                result.push_back(seq);
                start++;
            } else if (sum < target) {
                end++;
            } else {
                start++;
            }
        }

        return result;
    }
};
```

------

## 🧪示例测试：

| 输入          | 输出                  |
| ------------- | --------------------- |
| `target = 12` | `[[3,4,5]]`           |
| `target = 18` | `[[3,4,5,6],[5,6,7]]` |
| `target = 9`  | `[[2,3,4],[4,5]]`     |
| `target = 1`  | `[]`（至少两个数）    |

------

## 🔍可扩展思考：

- 如果目标是所有长度为 *k* 的连续子序列和为 target，可以设公式直接解；
- 若允许负数或非连续整数组合，该方法需调整。

------

## 🧬题目解析：排除个体后的乘积统计

### ✅题目描述

给定一个数组 `arrayA`，其中 `arrayA[i]` 表示第 i 个生物群体的数量。

你需要返回一个新数组 `arrayB`，其中 `arrayB[i]` 表示将第 i 个群体的数量从整体中移除后，**其余所有群体数量的乘积**。

------

## 💡解题思路

这是一个经典的数组构造问题：**“除自身以外的乘积”**，核心逻辑是：

- 对于每个元素，结果是：`总乘积 / arrayA[i]`（前提是所有元素都非 0）；
- 需要特殊处理 0 的情况：
  - 若 `arrayA` 中有 **两个及以上 0**，那么任何位置去掉一个元素后，其它都包含一个或两个 0，乘积一定为 0；
  - 若 **只有一个 0**，那么仅当当前元素就是 0 时，结果是其他非零元素的乘积，其余位置结果为 0；
  - 若 **没有 0**，就正常用总乘积除以当前元素。

------

## 🧠算法实现细节

1. **预处理阶段**：
   - 统计数组中为 0 的数量；
   - 同时计算所有非零元素的乘积（`total_product`）；
2. **结果构建阶段**：
   - 遍历每个元素，根据上述 0 的个数分情况处理，填入结果数组。

------

## 📦复杂度分析

- **时间复杂度**：O(n)，遍历两次数组；
- **空间复杂度**：O(n)，用于构建结果数组。

------

## ✅代码实现（C++）

```cpp
class Solution {
public:
    vector<int> statisticalResult(vector<int>& arrayA) {
        int zero_count = 0;
        long long total_product = 1;

        for (int num : arrayA) {
            if (num == 0) {
                zero_count++;
            } else {
                total_product *= num;
            }
        }

        vector<int> result(arrayA.size(), 0);
        for (int i = 0; i < arrayA.size(); i++) {
            if (zero_count > 1) {
                result[i] = 0; // 两个及以上 0，所有位置都是 0
            } else if (zero_count == 1) {
                if (arrayA[i] == 0)
                    result[i] = total_product;
                else
                    result[i] = 0;
            } else {
                result[i] = total_product / arrayA[i];
            }
        }

        return result;
    }
};
```

------

## 🧪示例验证

输入：

```cpp
arrayA = [2, 4, 6, 8, 10]
```

计算过程：

- 总乘积：2×4×6×8×10 = **3840**
- 每个位置除以对应元素：

| i    | arrayA[i] | total / arrayA[i] | arrayB[i] |
| ---- | --------- | ----------------- | --------- |
| 0    | 2         | 3840 / 2          | 1920      |
| 1    | 4         | 3840 / 4          | 960       |
| 2    | 6         | 3840 / 6          | 640       |
| 3    | 8         | 3840 / 8          | 480       |
| 4    | 10        | 3840 / 10         | 384       |

输出：

```cpp
[1920, 960, 640, 480, 384]
```

------

## 🧠进阶思考

如果不允许使用除法操作（如 LeetCode 类题），可通过构造前缀积 + 后缀积的方式来实现，这将使用更巧妙的空间换时间策略。

------

## 📄题目解析：寻找文件副本

### ✅题目描述：

在设备中记录了 `n` 个文件的编号，存于数组 `documents`。若某个编号在数组中出现超过一次，则说明该文件存在副本。请返回 **任意一个存在副本的文件 ID**。

------

## 💡解题思路：

### ✅思路 1：排序 + 相邻元素判断

1. 对 `documents` 排序；
2. 遍历数组，若相邻两个元素相等，则说明是副本；
3. 返回任意找到的重复 ID。

### ⏱️时间复杂度：

- 排序：O(n log n)
- 遍历查找：O(n)
- 总体时间：**O(n log n)**

------

### ✅思路 2：哈希集合（更高效）

1. 使用 `unordered_set` 记录已经出现的文件 ID；
2. 每遍历一个文件 ID，如果已存在于集合中，则说明是副本；
3. 否则将其加入集合中；
4. 返回任一重复值。

#### ⏱️时间复杂度：

- 遍历一次：O(n)
- 空间复杂度：O(n)
- 适合 **时间更敏感场景**。

```cpp
class Solution {
public:
    int findRepeatDocument(vector<int>& documents) {
        unordered_set<int> seen;
        for (int doc : documents) {
            if (seen.count(doc)) return doc;
            seen.insert(doc);
        }
        return -1; // 理论上不应到达这里
    }
};
```

------

### ✅思路 3（进阶）：原地交换/标记法（适用于 0 ≤ documents[i] ≤ n - 1）

利用数组索引来“标记”元素出现过：

1. 遍历 `documents`，对于每个元素 `val = abs(documents[i])`；
2. 判断 `documents[val]` 是否为负数（是否已访问过）；
   - 是，则说明重复；
   - 否，将其变为负数标记。
3. 注意恢复或取绝对值避免越界。

```cpp
class Solution {
public:
    int findRepeatDocument(vector<int>& documents) {
        for (int i = 0; i < documents.size(); ++i) {
            int val = abs(documents[i]);
            if (documents[val] < 0) return val;
            documents[val] *= -1;
        }
        return -1;
    }
};
```

#### ⏱️时间复杂度：

- 时间：O(n)
- 空间：O(1)（在原数组上操作）
- 适用于 **不在意原数组破坏的情况**

------

## ✅总结对比

| 方法        | 时间复杂度 | 空间复杂度 | 是否修改原数组  | 说明                   |
| ----------- | ---------- | ---------- | --------------- | ---------------------- |
| 排序 + 遍历 | O(n log n) | O(1)       | ✅               | 简洁通用，适合多数场景 |
| 哈希集合    | O(n)       | O(n)       | ❌               | 更快，适合高效查重     |
| 原地标记    | O(n)       | O(1)       | ✅（破坏原数组） | 最优解，需注意副作用   |

------

## 示例演示：

输入：

```cpp
documents = [2, 5, 3, 0, 5, 0]
```

可能输出：

```
5 或 0（都符合题意）
```

------

## 🌀题目解析：二维数组的螺旋遍历

### ✅题目描述

给定一个二维数组 `array`，请按“螺旋顺序”返回遍历结果。

螺旋顺序定义为：从左上角开始，按照 **右 → 下 → 左 → 上** 的顺序循环进入更小的矩形层，直到所有元素被访问。

------

## 💡思路解析

我们可以用**四个边界变量** `top, bottom, left, right` 控制每一层的遍历范围，每次顺着螺旋方向：

1. **向右遍历**：`top` 固定，`i` 从 `left` 到 `right`
2. **向下遍历**：`right` 固定，`i` 从 `top+1` 到 `bottom`
3. **向左遍历**：`bottom` 固定，`i` 从 `right-1` 到 `left`
4. **向上遍历**：`left` 固定，`i` 从 `bottom-1` 到 `top+1`

> 每走完一圈（外层），就把 `top`、`bottom`、`left`、`right` 分别向中间收缩。

### 🧱边界判断：

每次走完一层后，要判断是否越界（即 `top > bottom` 或 `left > right`），防止重复访问或访问非法区域。

------

## ✅代码实现（C++）

你写的实现非常严谨，下面是加了注释的版本：

```cpp
class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array) {
        if (array.empty() || array[0].empty()) return {};
        
        int top = 0, bottom = array.size() - 1;
        int left = 0, right = array[0].size() - 1;
        vector<int> result;

        while (true) {
            // → 从左到右
            for (int i = left; i <= right; ++i)
                result.push_back(array[top][i]);
            if (++top > bottom) break;

            // ↓ 从上到下
            for (int i = top; i <= bottom; ++i)
                result.push_back(array[i][right]);
            if (--right < left) break;

            // ← 从右到左
            for (int i = right; i >= left; --i)
                result.push_back(array[bottom][i]);
            if (--bottom < top) break;

            // ↑ 从下到上
            for (int i = bottom; i >= top; --i)
                result.push_back(array[i][left]);
            if (++left > right) break;
        }

        return result;
    }
};
```

------

## 📦复杂度分析

- **时间复杂度**：O(m × n)，每个元素只访问一次
- **空间复杂度**：O(1)，除结果数组外使用常数辅助空间

------

## 🧪示例演示

### 示例 1：

```cpp
输入：[[1,2,3],[8,9,4],[7,6,5]]
输出：[1,2,3,4,5,6,7,8,9]
```

### 示例 2：

```cpp
输入：[[1,2,3,4],
      [12,13,14,5],
      [11,16,15,6],
      [10,9,8,7]]
输出：[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
```

------

## 🧠进阶思考

- 可拓展为“矩阵蛇形填数”、“螺旋生成矩阵”（LeetCode 59）；
- 可考虑用方向数组（dx, dy）+ 访问标记方式实现更通用的螺旋控制；

