# Leetcode刷题系列——模拟篇（队列和栈的相互模拟）

## 前言

​	虽然笔者认为，在实际工程上，使用别的数据结构进行对我们正在学习的数据结构模拟是一个纯多此一举的事情。但是如果是出于学习的目的，这样做实际上是双向的巩固了我们正在使用的和被模拟的数据结构的特征。为此，笔者认为在学习阶段这样做实际上是存在意义的。这也是为什么这篇博客存在的一个意义所在。

## 两个基本的数据结构——队列和栈

​	队列和栈我相信是大家非常熟悉的数据结构了，

- 栈的特性：**后进先出 (LIFO)**
- 队列的特性：**先进先出 (FIFO)**

​	LIFO和FIFO特性是我们解决相互模拟的一个非常重要的出发点。我们的核心处理思路就是采用两个这样的数据结构进行简单的相互模拟。

#### 可看可不看：简单的说一说队列和栈的最小基本接口

#### 📌 `std::stack<T>` 的接口

- **构造**：`stack<int> s;`
- **核心操作**
  - `s.push(x)` ：入栈（拷贝/移动）
  - `s.pop()` ：出栈（不返回值）
  - `s.top()` ：访问栈顶元素（返回引用，可读可写）
- **容量相关**
  - `s.empty()` ：是否为空
  - `s.size()` ：元素个数

⚠️ 注意：`pop()` 不返回元素，只是删除，想要值要先 `top()`。

#### 📌 `std::queue<T>` 的接口

（头文件 `<queue>`，底层通常用 `deque` 实现）

- **构造**：`queue<int> q;`
- **核心操作**
  - `q.push(x)` ：入队（加到队尾）
  - `q.pop()` ：出队（删除队头元素，不返回值）
  - `q.front()` ：访问队头元素
  - `q.back()` ：访问队尾元素
- **容量相关**
  - `q.empty()` ：是否为空
  - `q.size()` ：元素个数

## [LeetCode 225. 用队列实现栈](https://leetcode.cn/problems/implement-stack-using-queues/)

请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（`push`、`top`、`pop` 和 `empty`）。

实现 `MyStack` 类：

- `void push(int x)` 将元素 x 压入栈顶。
- `int pop()` 移除并返回栈顶元素。
- `int top()` 返回栈顶元素。
- `boolean empty()` 如果栈是空的，返回 `true` ；否则，返回 `false` 。

**注意：**

- 你只能使用队列的标准操作 —— 也就是 `push to back`、`peek/pop from front`、`size` 和 `is empty` 这些操作。
- 你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。

**示例：**

```
输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False
```

**提示：**

- `1 <= x <= 9`
- 最多调用`100` 次 `push`、`pop`、`top` 和 `empty`
- 每次调用 `pop` 和 `top` 都保证栈不为空

### 说明

​	队列如何模拟栈呢？我们知道，队列是一个经典的FIFO操作，想要实现一个LIFO操作，很简单，咱们就拿出来一个辅助的队列，存储不是最后一个的元素，再把最后一个元素拿到手就好了，处理完事之后再将辅助队列和我们的原先队列交换一下就好了。

```cpp
class MyStack {
    queue<int> q1, q2;

public:
    MyStack() {}

    void push(int x) { q1.emplace(x); }

    int pop() {
        while (q1.size() > 1) {
            q2.emplace(q1.front());
            q1.pop();
        }

        int val = q1.front();
        q1.pop();
        swap(q1, q2);
        return val;
    }

    int top() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        int val = q1.front();
        q2.push(val);
        q1.pop();
        swap(q1, q2);
        return val;
    }

    bool empty() { return q1.empty(); }
};
```

​	还好，这个是不难以理解的，

```
        while (q1.size() > 1) {
            q2.emplace(q1.front());
            q1.pop();
        }
```

​	这个小片段是将我们的其他元素先缓存到其他的队列里取，然后操作最后一个元素。你看，这样FIFO就会变成了LIFO，虽然纯折磨。

## [232. 用栈实现队列 - 力扣（LeetCode）](https://leetcode.cn/problems/implement-queue-using-stacks/description/)

请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（`push`、`pop`、`peek`、`empty`）：

实现 `MyQueue` 类：

- `void push(int x)` 将元素 x 推到队列的末尾
- `int pop()` 从队列的开头移除并返回元素
- `int peek()` 返回队列开头的元素
- `boolean empty()` 如果队列为空，返回 `true` ；否则，返回 `false`

**说明：**

- 你 **只能** 使用标准的栈操作 —— 也就是只有 `push to top`, `peek/pop from top`, `size`, 和 `is empty` 操作是合法的。
- 你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

 

**示例 1：**

```
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
```

 

**提示：**

- `1 <= x <= 9`
- 最多调用 `100` 次 `push`、`pop`、`peek` 和 `empty`
- 假设所有操作都是有效的 （例如，一个空的队列不会调用 `pop` 或者 `peek` 操作）

### 说明

​	这个呢，思路是类似的，但是实现稍微有点不一样，是这样的，我们现在需要的是LIFO转FIFO，实际上就是需要使用另一个栈倒腾出来第一个元素，但是需要注意的是，当我们需要倒腾拿出来第一个元素，我们实际上必然也会拿到第二、三个元素。。。所以，我们并不需要交换两个栈，直接化简操作辅助栈即可。

```cpp
class MyQueue {
    stack<int> left_one, right_one;
public:
    MyQueue() {
    }
    
    void push(int x) {
        left_one.emplace(x);
    }
    
    int pop() {
        if(right_one.empty()){
            while(!left_one.empty()){
                right_one.emplace(left_one.top());
                left_one.pop();
            }
        }
        int val = right_one.top();
        right_one.pop();
        return val;
    }
    
    int peek() {
        if(right_one.empty()){
            while(!left_one.empty()){
                right_one.emplace(left_one.top());
                left_one.pop();
            }
        }
        return right_one.top();
    }
    
    bool empty() {
        return left_one.empty() && right_one.empty();
    }
};
```

