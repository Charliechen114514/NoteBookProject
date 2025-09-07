# 我的Leetcode刷题笔记：栈和队列

------

# 📚 栈与队列知识前导总结（附高频题型）

在实际算法题中，**栈（Stack）**和**队列（Queue）**是两种最基础也最常用的数据结构。它们不仅在基础操作中频繁出现，还广泛用于高级题型的设计（如滑动窗口、单调结构、双堆等）。

## 🧱 基本定义

| 数据结构               | 结构特点           | 操作方式                                      | STL 实现类               |
| ---------------------- | ------------------ | --------------------------------------------- | ------------------------ |
| 栈 Stack               | 后进先出（LIFO）   | push / pop / top                              | `std::stack<T>`          |
| 队列 Queue             | 先进先出（FIFO）   | push / pop / front                            | `std::queue<T>`          |
| 双端队列 Deque         | 两端可进出         | push_front / push_back / pop_front / pop_back | `std::deque<T>`          |
| 优先队列 PriorityQueue | 自动排序队列（堆） | top / push / pop                              | `std::priority_queue<T>` |

------

## 💡 栈 & 队列在经典题中的应用总结

### ✅ 1. 最小栈（Min Stack）

> 🧩 **题目名称：设计一个支持获取最小值的栈**

- 使用两个栈：
  - 一个正常存储所有元素；
  - 一个辅助栈实时维护当前“最小值”；
- 每次 push/pop 都要判断是否更新辅助栈；
- 所有操作时间复杂度 O(1)。

🔧 STL 用法：

```cpp
std::stack<int> stk, minStk;
```

------

### ✅ 2. 验证出栈顺序（Stack Sequences）

> 🧩 **题目名称：图书入架出架顺序合法性判断**

- 模拟入栈过程；
- 每次 push 后尝试尽量多的 pop（匹配目标出栈序列）；
- 最终若栈为空，则序列合法；
- 利用栈判断排列合法性，是经典模拟题。

🔧 STL 用法：

```cpp
std::stack<int> stk;
```

------

### ✅ 3. 滑动窗口最大值（Sliding Window Maximum）

> 🧩 **题目名称：海拔观测望远镜最大值**

- 使用**单调队列**（单调递减）快速获取滑窗最大值；
- 每次移动窗口时，自动维护队列单调性；
- 时间复杂度 O(n)，常见于窗口型问题。

🔧 STL 用法：

```cpp
std::deque<int> dq;
```

------

### ✅ 4. 自助结账系统（队列最大值）

> 🧩 **题目名称：支持 O(1) 获取最大值的队列**

- 与滑动窗口思路相同；
- 结合普通队列 + 单调队列，支持：
  - 入队
  - 出队
  - 获取最大值
- 所有操作均摊 O(1)。

🔧 STL 用法：

```cpp
std::deque<int> flows, maxQueue;
```

------

### ✅ 5. 数据流中位数（Median Finder）

> 🧩 **题目名称：支持插入与查找中位数**

- 使用两个堆（最大堆 + 最小堆）：
  - 小的一半存在最大堆；
  - 大的一半存在最小堆；
- 插入时保持两个堆大小平衡；
- 中位数就是堆顶或两个堆顶平均值。

🔧 STL 用法：

```cpp
std::priority_queue<int> maxHeap; // 默认大顶堆
std::priority_queue<int, vector<int>, greater<int>> minHeap; // 小顶堆
```

------

## 📌 模板与技巧对照表

| 题型           | 核心结构        | 是否单调   | 是否辅助栈/堆 | 查值复杂度      |
| -------------- | --------------- | ---------- | ------------- | --------------- |
| 最小栈         | 栈 + 辅助栈     | 否         | 是            | O(1) getMin     |
| 栈序列验证     | 栈              | 否         | 否            | O(n)            |
| 滑动窗口最大值 | 单调队列        | 是（递减） | 否            | O(1)            |
| O(1)最大值队列 | 队列 + 单调队列 | 是         | 是            | O(1) getMax     |
| 数据流中位数   | 最大堆 + 最小堆 | 否         | 是            | O(1) findMedian |

------

## 📚 STL 容器复习提示

| 容器                | 特性                                       |
| ------------------- | ------------------------------------------ |
| `stack<T>`          | 只能尾部插入/删除，底层一般基于 deque 实现 |
| `queue<T>`          | 普通 FIFO 队列，底层也是 deque             |
| `deque<T>`          | 双端队列，两端都可以插入和删除             |
| `priority_queue<T>` | 默认是大顶堆，支持自定义比较器构建小顶堆   |

------

## 🎯 总结建议

- 栈/队列问题的本质是**“顺序控制”与“范围控制”**；
- 单调结构（如单调栈/单调队列）非常适用于滑窗问题；
- 多数高级栈/队列设计题都可归纳为 **维护某种最值、顺序或窗口性质**；
- 掌握 STL 的堆、队列和 deque 操作非常关键。

# 📚 借还书操作

图书馆借还书操作由两个**栈式书车**组成，但要满足队列（先进先出）的行为：

- `push(bookID)`：将图书归还（放入队尾）；
- `pop()`：借出图书（取出最早归还的一本）；
- 如果没有书可借，返回 `-1`。

即我们需要用 **两个栈（后进先出）** 模拟一个 **队列（先进先出）**。

------

## 🔍 解题思路：两个栈实现队列

用两个栈：

- `inStack`：用于入队（归还图书）；
- `outStack`：用于出队（借书）；

每次执行 `pop()` 时：

1. 如果 `outStack` 非空，直接 `pop`；
2. 如果为空，就把 `inStack` 中所有元素依次弹出并压入 `outStack`（完成“倒序”）；
3. 然后再从 `outStack` 弹出队首元素；
4. 如果两个栈都为空，返回 `-1`。

### ✅ 为什么这么做？

栈是 **后进先出（LIFO）**，两个栈“互相倒转”一次后，顺序就变成了 **先进先出（FIFO）**。

------

## 🧠 示例解析

```text
push(1)      => inStack: [1]
push(2)      => inStack: [1, 2]
pop()        => outStack为空 => 倒入后变成 [2, 1] => pop() 返回 1
```

------

## ✅ C++ 实现（标准双栈解法）

```cpp
class BookQueue {
private:
    stack<int> inStack;
    stack<int> outStack;

public:
    BookQueue() {}

    void push(int bookID) {
        inStack.push(bookID);
    }

    int pop() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }

        if (outStack.empty()) return -1;

        int bookID = outStack.top();
        outStack.pop();
        return bookID;
    }
};
```

------

## 🧩 用 vector + index 模拟队列 ✅

用 `vector` + `available_index` 也能工作，是一种 **懒惰删除**策略：

- `push`：尾部添加；
- `pop`：用下标模拟队首；
- 每次出队只是移动索引，而不是真正 `erase()`，避免频繁移动。

### 👍 优点：

- 简洁、高效、易写；
- 适合这题，尤其不要求真的释放元素；

### 👎 缺点：

- 长时间不清理会导致 vector 积累大量不可用元素（可手动触发清理）；
- 如果是严格 O(1) 空间或长期运行的系统，这不是最优。

------

## ✅ C++ 实现（当前方案，略优化）

```cpp
class BookQueue {
public:
    BookQueue() {}

    void push(int bookID) {
        arr.push_back(bookID);
    }

    int pop() {
        if (index >= arr.size()) return -1;
        return arr[index++];
    }

private:
    vector<int> arr;
    int index = 0;
};
```

------

## 📈 复杂度分析（双栈解法）

| 操作     | 时间复杂度     |
| -------- | -------------- |
| `push()` | O(1)           |
| `pop()`  | Amortized O(1) |
| `get()`  | O(1)           |

> 每个元素只会从 `inStack` 压入一次，从 `outStack` 弹出一次，总次数最多两次。

------

## ✅ 总结

| 方法           | 空间复杂度       | 特点                         |
| -------------- | ---------------- | ---------------------------- |
| 双栈           | O(n)             | 通用、安全、高效，是推荐方式 |
| vector + index | O(n)，有内存浪费 | 简洁快速，适合一轮性模拟     |

# 📝 最小栈

设计一个支持以下操作的栈数据结构，并且这些操作的**时间复杂度都是 O(1)**：

- `push(val)`：将元素 `val` 推入栈中；
- `pop()`：移除栈顶元素；
- `top()`：获取栈顶元素；
- `getMin()`：获取栈中的最小元素。

> 题目保证 `pop`、`top` 和 `getMin` 操作总是在非空栈上调用。

------

## 💡 解题思路：辅助栈同步最小值

我们在维护正常栈的同时，再**使用一个辅助栈 `minStack` 来记录每个时刻的最小值**。

### ✅ 操作规则如下：

- 当我们往主栈 `stack` 压入元素时，检查 `minStack` 是否为空，或当前元素是否比栈顶小；
  - 如果小于或等于当前最小值，也将它压入 `minStack`；
- 当我们从主栈弹出元素时：
  - 如果弹出的元素等于 `minStack` 栈顶，也要将 `minStack` 弹出（保持同步）；
- 获取最小值时，只需返回 `minStack.top()`；
- 所有操作都保持 O(1) 时间复杂度。

------

## 📦 示例

```
MinStack minStack;
minStack.push(-2);   // minStack: [-2]
minStack.push(0);    // minStack: [-2]
minStack.push(-3);   // minStack: [-2, -3]
minStack.getMin();   // return -3
minStack.pop();      // pop -3 => minStack: [-2]
minStack.top();      // return 0
minStack.getMin();   // return -2
```

------

## ✅ C++ 实现代码

```cpp
class MinStack {
private:
    stack<int> _minStack;  // 辅助栈：记录最小值历史
    stack<int> _helper;    // 主栈：正常存储所有元素

public:
    MinStack() {}

    void push(int val) {
        if (_minStack.empty() || val <= _minStack.top()) {
            _minStack.push(val);
        }
        _helper.push(val);
    }

    void pop() {
        if (_helper.top() == _minStack.top()) {
            _minStack.pop();
        }
        _helper.pop();
    }

    int top() {
        return _helper.top();
    }

    int getMin() {
        return _minStack.top();
    }
};
```

------

## ⏱️ 复杂度分析

| 操作   | 时间复杂度 | 空间复杂度 |
| ------ | ---------- | ---------- |
| push   | O(1)       | O(n)       |
| pop    | O(1)       | O(n)       |
| top    | O(1)       | O(1)       |
| getMin | O(1)       | O(1)       |



------

## 🌟 总结

- 关键点在于用一个辅助栈记录“历史最小值”；
- 所有操作都可在 O(1) 时间完成；
- 是栈类设计题中非常经典的一道，建议掌握。

------

# 📚 题目：验证图书出入书架顺序（栈序列）

## 📝 题目描述

图书馆的书架只能按**栈的规则**来放入（先进后出）和取出。你需要验证一个给定的图书编号入栈顺序 `putIn`，能否通过一系列**合法的 push/pop 操作**得到指定的出栈顺序 `takeOut`。

> 每个书籍编号唯一，且 `putIn` 是 `takeOut` 的排列。

------

## 🧠 解题思路

这是典型的栈序列匹配问题（Leetcode 原题：946. Validate Stack Sequences），我们模拟整个入栈和出栈过程：

- 用一个栈模拟书架；
- 每放入一个书籍 `x`，我们检查是否可以从栈顶按顺序弹出；
- 直到栈顶不等于当前出栈顺序 `takeOut[cur]`；
- 如果最终栈为空，说明出栈顺序合法。

------

## ✅ C++ 实现代码

```cpp
class Solution {
public:
    bool validateBookSequences(vector<int>& putIn, vector<int>& takeOut) {
        stack<int> _stack;
        int cur = 0;
        for (int book : putIn) {
            _stack.push(book);
            // 尝试将栈顶元素与 takeOut[cur] 匹配
            while (!_stack.empty() && _stack.top() == takeOut[cur]) {
                _stack.pop();
                cur++;
            }
        }
        return _stack.empty();
    }
};
```

------

## 📊 时间与空间复杂度分析

| 复杂度     | 分析                             |
| ---------- | -------------------------------- |
| 时间复杂度 | O(n)，每个元素最多进栈出栈各一次 |
| 空间复杂度 | O(n)，辅助栈最多 n 个元素        |

------

## ✅ 示例解析

### 示例 1

```text
putIn = [6,7,8,9,10,11]
takeOut = [9,11,10,8,7,6]

操作过程：
push 6
push 7
push 8
push 9 -> pop 9
push 10
push 11 -> pop 11 -> pop 10 -> pop 8 -> pop 7 -> pop 6 ✅
```

合法，返回 true。

### 示例 2

```text
putIn = [6,7,8,9,10,11]
takeOut = [11,9,8,10,6,7]

操作过程：
push 6
push 7
push 8
push 9
push 10
push 11 -> pop 11
-> 栈顶是 10，但 takeOut[1] 是 9 ❌，不匹配
```

不合法，返回 false。

------

## 🧩 总结

- 使用栈模拟 push/pop 操作是解决栈序列验证类问题的标准方法；
- 每次入栈后，尽量多地匹配出栈元素；
- 最终栈为空，则说明 `takeOut` 是合法的出栈序列。

当然可以！下面是你**原始代码**的完整版本，我已经为你添加了**详细注释**，指出了其**运行逻辑、优点、缺点**，并在后面**合并了推荐的正确做法**，方便你作为完整题解或笔记使用。

------

# 🧩 最大海拔

给定海拔数组 `heights`，望远镜的视野为一个长度为 `limit` 的连续窗口。请你返回每一个窗口中的**最高海拔值**。

------

## 🧪 原始实现代码（含注释 + 缺点说明）

```cpp
class Solution {
public:
    vector<int> maxAltitude(vector<int>& heights, int limit) {
        if (heights.empty()) return {};

        vector<int> res;

        // 枚举所有滑动窗口的起点 i
        for (int i = 0; i <= heights.size() - limit; i++) {
            stack<int> stk;

            // 遍历当前窗口的每个元素
            for (int j = 0; j < limit; j++) {
                int current = heights[i + j];
                
                // 栈空则直接放入
                if (stk.empty()) {
                    stk.push(current);
                } else {
                    // 如果当前元素比栈顶大，则放入（试图保持最大值在栈顶）
                    if (stk.top() < current) {
                        stk.push(current);
                    }
                }
            }

            // 每个窗口返回栈顶元素（期望是最大值）
            res.emplace_back(stk.top());
        }

        return res;
    }
};
```

### ✅ 优点：

- 思路清晰：使用栈来“保存最大值”；
- 能通过样例（在某些数据下工作正常）；
- 时间复杂度为 O(n × limit)，当 `n` 较小时可接受。

### ❌ 缺点：

1. **栈没有保留窗口中所有元素**，只能记录最后一个更大的值，可能导致错误：
   - 如果最大值出现在前面、后面都是较小值，它就会被丢掉。
2. **没有处理窗口中多个值比较的完整性**，栈设计成了非完整滑窗处理；
3. **时间复杂度较高**：O(n × limit)，极端情况会超时；
4. 实际上你只用到了 `stk.top()`，没有用 `stack` 的意义（更适合用变量 `maxVal`）。

------

## ✅ 推荐改法：使用单调队列（正确 + 高效）

```cpp
class Solution {
public:
    vector<int> maxAltitude(vector<int>& heights, int limit) {
        vector<int> res;
        deque<int> dq;  // 存储元素索引，保持对应值单调递减

        for (int i = 0; i < heights.size(); ++i) {
            // 维护递减队列：移除所有小于当前元素的值
            while (!dq.empty() && heights[dq.back()] <= heights[i]) {
                dq.pop_back();
            }

            // 加入当前索引
            dq.push_back(i);

            // 移除不在窗口范围内的索引（滑出左边界）
            if (dq.front() <= i - limit) {
                dq.pop_front();
            }

            // 当前窗口形成后，记录最大值
            if (i >= limit - 1) {
                res.push_back(heights[dq.front()]);
            }
        }

        return res;
    }
};
```

### ✅ 优点：

- 时间复杂度为 O(n)，适合大数据；
- 使用双端队列维护滑动窗口最大值，是业界标准解法；
- 保证窗口中最大值始终在队首，且窗口自动滑动。

------

## 🎯 总结

| 版本       | 是否推荐 | 时间复杂度   | 说明                         |
| ---------- | -------- | ------------ | ---------------------------- |
| 原始栈版本 | ❌ 不推荐 | O(n × limit) | 逻辑错误风险高、效率低       |
| 单调队列版 | ✅ 推荐   | O(n)         | 正确、高效、滑动窗口模板题解 |

你的实现是**完全正确的最优解**，并且符合**所有题目要求：功能正确、时间复杂度 O(1) 均摊**。

下面我将为你撰写一个**完整的题解说明**，包括：

- 💡 题目解读
- 🧠 解题思路
- ✅ 代码详解（你写的代码 + 注释）
- ⏱️ 复杂度分析
- 🧩 总结

------

# 📚 自助结账系统设计（队列 + 获取最大值）题解

## 💡 题目理解

实现一个支持以下操作的“结账商品队列”：

- `add(value)`：将商品价格加入队尾；
- `remove()`：移除队首商品价格；
- `get_max()`：获取当前所有商品中的最高价格。

**要求**：所有操作时间复杂度为 O(1)（均摊）。

------

## 🧠 解题思路：单调队列维护最大值

这类问题本质是一个支持 **获取当前队列最大值的滑动窗口问题**，经典做法是使用**单调队列（Monotonic Queue）**。

### 数据结构设计：

- `flows`：普通队列，保存真实的商品价格；
- `maxOne`：单调递减队列，维护当前窗口的最大值。

### 操作规则：

- `add(value)`：
  - 正常放入 `flows`；
  - 在 `maxOne` 中移除所有尾部小于 `value` 的元素（因为它们永远不可能成为最大值）；
  - 将 `value` 加入 `maxOne` 尾部；
- `get_max()`：
  - 返回 `maxOne.front()`，始终是当前队列最大值；
- `remove()`：
  - 弹出 `flows.front()`；
  - 如果这个值恰好是 `maxOne.front()`，也同步弹出它。

------

## ✅ C++ 实现（含注释）

```cpp
class Checkout {
    deque<int> maxOne;   // 单调队列，维护最大值
    deque<int> flows;    // 普通队列，保存所有价格

public:
    Checkout() {}

    // 返回当前队列最大价格
    int get_max() {
        if (maxOne.empty()) return -1;
        return maxOne.front();
    }

    // 添加商品价格
    void add(int value) {
        flows.push_back(value);

        // 维护 maxOne 为单调递减队列
        while (!maxOne.empty() && maxOne.back() < value) {
            maxOne.pop_back();
        }

        maxOne.push_back(value);
    }

    // 移除最早加入的商品价格
    int remove() {
        if (flows.empty()) return -1;

        int res = flows.front();
        flows.pop_front();

        // 如果该元素是最大值，也要同步移除
        if (!maxOne.empty() && res == maxOne.front()) {
            maxOne.pop_front();
        }

        return res;
    }
};
```

------

## 📈 复杂度分析

| 操作        | 时间复杂度    | 空间复杂度 |
| ----------- | ------------- | ---------- |
| `add()`     | **O(1)** 均摊 | O(n)       |
| `remove()`  | **O(1)**      | O(n)       |
| `get_max()` | **O(1)**      | O(1)       |

> 解释：`add()` 中的 `while` 每个元素最多被插入/删除一次，均摊时间复杂度是 O(1)。

------

## 🔍 示例解析

### 示例 1

```text
操作：["Checkout","add","add","get_max","remove","get_max"]
输入：[[],[4],[7],[],[],[]]
输出：[null,null,null,7,4,7]

状态变化：
add(4) -> flows: [4], maxOne: [4]
add(7) -> flows: [4, 7], maxOne: [7]   // 4被淘汰
get_max() -> 7
remove() -> 返回4, flows: [7], maxOne: [7]
get_max() -> 7
```

------

## 🧩 总结

- 使用**两个队列**即可支持 O(1) 获取最大值的队列；
- 维护一个**单调递减队列**是解决此类问题的关键技巧；
- 是滑动窗口最大值的经典变体，建议掌握。

------

# 📊 数据流的中位数（Median Finder）题解

## 📝 题目描述

设计一个支持以下操作的数据结构：

- `addNum(int num)`：从数据流中添加一个整数；
- `findMedian()`：返回目前所有元素的中位数。

> - 若总数为奇数，返回中间值；
> - 若为偶数，返回中间两个数的平均值。

------

## 🧠 解题思路：双堆维护中位数

我们使用两个堆：

| 堆名         | 类型       | 存储         | 性质                           |
| ------------ | ---------- | ------------ | ------------------------------ |
| `less_one`   | 最大堆 max | 较小一半的数 | 堆顶是这部分的最大值           |
| `larger_one` | 最小堆 min | 较大一半的数 | 堆顶是这部分的最小值（更大区） |

通过维护两个堆的**大小差最多为 1**，我们可以随时 O(1) 获取中位数。

------

### ✅ 插入规则：

- 初始时两个堆都为空；
- 每次插入数字：
  - 如果 `less_one.size() == larger_one.size()`，新数先进入 `less_one`（最大堆），再把堆顶放入 `larger_one`（最小堆）；
  - 如果不相等，新数先进入 `larger_one`，堆顶放入 `less_one`；
- 保证：`less_one.size() <= larger_one.size()`，差值最多 1。

------

### ✅ 查找中位数规则：

- 若元素总数为奇数：返回 `larger_one.top()`；
- 若为偶数：取两个堆顶平均值。

------

## ✅ C++ 实现（含注释）

```cpp
class MedianFinder {
public:
    // 小的一半：最大堆（大顶堆）
    priority_queue<int> less_one;

    // 大的一半：最小堆（小顶堆）
    priority_queue<int, vector<int>, greater<int>> larger_one;

    MedianFinder() {}

    void addNum(int num) {
        // 当前总数为偶数，插入后需要让 larger_one 比 less_one 多一个
        if (less_one.size() == larger_one.size()) {
            less_one.push(num);
            larger_one.push(less_one.top());
            less_one.pop();
        }
        // 当前总数为奇数，插入后需要平衡
        else {
            larger_one.push(num);
            less_one.push(larger_one.top());
            larger_one.pop();
        }
    }

    double findMedian() {
        if (less_one.size() == larger_one.size()) {
            return (less_one.top() + larger_one.top()) / 2.0;
        } else {
            return larger_one.top();
        }
    }
};
```

------

## ⏱️ 复杂度分析

| 操作         | 时间复杂度 |
| ------------ | ---------- |
| `addNum`     | O(log n)   |
| `findMedian` | O(1)       |

> 因为堆的插入/删除是 O(log n)，但中位数始终是两个堆顶，O(1) 可得。

------

## ✅ 示例分析

输入：

```
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
```

执行过程：

```
add(1) => less: [], larger: [1]       中位数：1
add(2) => less: [1], larger: [2]      中位数：(1+2)/2 = 1.5
add(3) => less: [1], larger: [2,3]    中位数：2
```

输出：`[null,null,null,1.5,null,2.0]`

------

## 🧩 总结

- 使用两个堆维护中位数是本题的标准解法；
- 插入时动态平衡大小；
- 查找中位数时直接读取堆顶即可；
- **非常经典的题目，建议完全掌握**。