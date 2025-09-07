# Leetcode Easy题小解（C++语言描述）

# 相交链表

给你两个单链表的头节点 `headA` 和 `headB` ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 `null` 。

图示两个链表在节点 `c1` 开始相交**：**

[![img](./Leetcode Easy题小解（C++语言描述）/160_statement.png)](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/14/160_statement.png)

题目数据 **保证** 整个链式结构中不存在环。

**注意**，函数返回结果后，链表必须 **保持其原始结构** 。

## 方法一：使用unordered_set存储元素查询是否重复

​	有一个招数就是使用unordered_set存储一下我们的一个链表的元素，然后，去用另一个链表遍历查看我们的元素是否在unordered_set种已经出现过了。

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> sets;
        // init the sets to get the count;

        while(headA)
        {
            sets.insert(headA);
            headA = headA->next; // go ahead;
        }

        while(headB)
        {
            if(sets.count(headB)){
                // owns the count, and returns;
                return headB;
            }
            headB = headB->next;
        }

        return nullptr;

    }
};
```

​	这种方式最直观，也是笔者的第一反应。

## 方法2：快慢指针判决

​	下面我们来看快慢指针的办法进行求解。我们知道，假设A链表的长度是`a`，B链表的长度是`b`，公共部分设成`c`，那么显然，我们快慢指针的判别法可以是这样的：即尝试两个指针都走一次A，B链表，当走到我们的焦点的时候，我们发现：

```
A: 走了 a + (b - c)
B: 走了 b + (a - c)
```

​	我们高兴的发现两个指针走的部署相等，因此实际上，我们完全就让快慢指针在交点处相等了。

```c
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;

        while(curA != curB)
        {
            curA = (curA ? curA->next : headB); // 空了咱们去B
            curB = (curB ? curB->next : headA); // 空了咱们去A
        }

        return curA;
    }
};
```

# 链表反转

给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
```

​	反转链表比较简单，我们实际上的难点在于，我们不能立马修改当前遍历节点的下一个节点，需要做缓存

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head; // stop with null and only

        ListNode* current = head;
        ListNode* prev = nullptr;
        ListNode* next_one;
        while(current)
        {
            // cached the next one
            next_one = current->next;
            // modify the next one's next to the cur to reverse
            current->next = prev;
            // restore caches
            prev = current;
            current= next_one;
        }
        return prev;
    }
};
```

​	就可以看到，我们做的实际上就是简单的swap操作，没啥好说的。

## 判断回文链表

​	给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。

​	嘛！显然，咱们没法逆序遍历链表，有一种偷懒的办法兄弟们，那就是用一下栈这个特性。我们知道栈是一个经典的FILO结构，我们按照遍历顺序压栈我们的单链表遍历结果，之后我们只需要再遍历一下链表，跟我们的栈进行对比

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<int> caches;
        ListNode* cached_head = head;
        while(head){
            caches.push(head->val);
            head = head->next;
        }     

        while(cached_head)
        {
            if(cached_head->val != caches.top()){
                return false;
            }
            cached_head = cached_head->next;
            caches.pop();
        }
        return true;
    }
};
```

# 前K系列：找出前K个高频元素

​	给你一个整数数组 `nums` 和一个整数 `k` ，请你返回其中出现频率前 `k` 高的元素。你可以按 **任意顺序** 返回答案。

​	其实回答很简单，那就是第一步是统计我们的元素个数，我们可以使用的是unordered_map来做这个事情，其键值对我们采用的是：`{`元素，个数`}`键值对。之后咱们做的事情就是塞到大根堆进行默认的排序。需要注意的是，咱们的大根堆对pair的排序看的是第一个数大不大，所以咱们往队列里push我们的东西的时候，是需要我们调换一下键值对的顺序的。

```c
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counters; // <nums, count>

        for(const auto& num : nums)
        {
            counters[num]++;
        }

        // next, we shell check and reordered as prioirty queue
        priority_queue<pair<int, int>> pq;

        for(const auto& each : counters){
            pq.push({each.second, each.first});
        }

        vector<int> result;
        for(int i = 0; i < k; i++)
        {
            result.emplace_back(pq.top().second);
            pq.pop();
        }
        return result;
    }
};
```

​	可以看到我们的priority_queue自动帮助我们处理排序的事情了。如果是小K个，那么我们只需要换`greater<int>`就好了

# 第K系列：使用Ｏ（N）复杂度寻找第K个大小的数字

## 可以用sort等嘛？

​	不能，因为std::sort是完全快排，实际上复杂度是`O(NlogN)`，我们需要改进成快速选择的方式进行改进

```c++
class Solution {
public:
    int partition(vector<int>& nums, int left, int right)
    {
        int pivot = nums[right];
        int i = left;
        for(int j = left; j < right; j++)
        {
            if(nums[j] <= pivot){
                swap(nums[i], nums[j]);
                i++;
            }
        }

        swap(nums[i], nums[right]);
        return i; // return new pivot
    }

    int quick_selection(vector<int>& n, int left, int right, int k_smallest){
        if (left == right) return n[left];

        int pivot = partition(n, left, right);

        if(pivot == k_smallest){
            return n[pivot];
        }else if (pivot < k_smallest){
            // left
            return quick_selection(n, pivot + 1, right, k_smallest);
        }else{
            return quick_selection(n, left, pivot - 1, k_smallest);
        }
    }


    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int target = n - k; // 第 k 大 → 第 n - k 小
        return quick_selection(nums, 0, n - 1, target);
    }
};
```

------



### 1. `findKthLargest` 函数：“化大为小，找对目标”



想象你有一堆扑克牌，现在让你找出第 3 大的那张牌。

```cpp
int findKthLargest(vector<int>& nums, int k) {
    int n = nums.size();
    // 关键一步：把“找第k大”转换成“找第(n-k)小”
    int target = n - k; // 例如，有5张牌，找第1大（最大的），就是找第5-1=4小的（也就是索引为4的，如果从0开始数）
                        // 找第3大，就是找第5-3=2小的（也就是索引为2的）
    return quick_selection(nums, 0, n - 1, target);
}
```

- **它的任务：** 你告诉我，你想要这堆牌里第几大的牌。
- **它的聪明之处：** 它会偷偷地把你的要求“翻译”一下。比如，如果你说要找第 3 大的牌，它会心想：“哦，这不就是说，在所有牌都排好序之后，从最小的开始数，第 (N−3) 张牌吗？”（N 是总牌数）。
- **委托任务：** 翻译完之后，它就把这个“找第 N−k 小的牌”的任务，交给下一级的专家 `quick_selection` 去办了。

------



### 2. `partition` 函数：“分堆、找个好位置”



这个函数是整个算法的“幕后功臣”，它每次的作用是：随机挑一个“参考牌”，然后把其他牌根据这个参考牌分成两堆。

```cpp
int partition(vector<int>& nums, int left, int right)
{
    int pivot = nums[right]; // 选定最右边的牌作为“参考牌”（基准值）
    int i = left;            // i 指针：表示“比参考牌小的牌”的区域的右边界

    // j 指针从左边开始遍历，但不到right（因为right是参考牌）
    for(int j = left; j < right; j++)
    {
        if(nums[j] <= pivot){ // 如果当前牌（nums[j]）比“参考牌”小或者相等
            swap(nums[i], nums[j]); // 就把这张牌挪到“比参考牌小的区域”里去
            i++;                     // “比参考牌小的区域”的边界就往右扩大一格
        }
    }

    // 循环结束后，i 指向的位置，就是所有“比参考牌小的牌”后面紧跟着的位置
    // 也就是说，i左边的牌都 <= pivot，i右边的牌都 > pivot (暂时)
    swap(nums[i], nums[right]); // 把“参考牌”（nums[right]）放到 i 指向的位置
                                 // 这样，i位置的牌就是新的参考牌，它左边的都比它小，右边的都比它大

    return i; // 返回这个“参考牌”最终所在的位置（索引）
}
```

- **它的任务：** 拿到一堆牌（一个子数组），然后重新整理一下这堆牌。

- **怎么整理：**

  1. 它先从这堆牌的最右边挑一张牌，把它作为**“参考牌” (pivot)**。
  2. 它有一个**“小牌区”的边界 `i`**，最开始在最左边。
  3. 然后它从最左边开始，一张一张地看牌 (`j` 遍历)：
     - 如果它看的这张牌比“参考牌”小（或者一样大），那么这张牌就应该放在“小牌区”里。它就会把这张牌和“小牌区”边界 `i` 上的牌交换一下位置。然后，“小牌区”的边界 `i` 就往右移一位。
     - 如果它看的这张牌比“参考牌”大，它就不管，继续看下一张。
  4. 当所有牌都看完了（`j` 走到了 `right - 1`），这时候，从起始位置到 `i-1` 的所有牌都比“参考牌”小或相等。`i` 指向的牌和 `i` 右边的牌都比“参考牌”大（或者还没有处理的牌）。
  5. 最后，它会把最开始选定的那张**“参考牌”**（原来在 `right` 位置）放到 `i` 所指的位置上。

- 结果： partition 函数执行完后，数组就变成这样：

  [小于等于参考牌的牌 | 参考牌本身 | 大于参考牌的牌]

  而且，返回的 i 就是这个**“参考牌”最终所在的位置**。这个位置非常重要，因为它告诉我们“参考牌”在整个排序好之后，会处于哪个确切的索引。

------



### 3. `quick_selection` 函数：“缩小范围，直到找到”



这是递归寻找目标牌的主管。

```cpp
int quick_selection(vector<int>& n, int left, int right, int k_smallest){
    if (left == right) return n[left]; // 如果只剩一张牌了，那这张牌就是答案，直接返回

    int pivot_index = partition(n, left, right); // 调用 partition，找到“参考牌”的新位置

    if(pivot_index == k_smallest){
        // 情况1：运气真好！“参考牌”的位置正好就是我们要找的第k_smallest小牌的位置！
        return n[pivot_index]; // 找到了，直接返回这张牌
    }else if (pivot_index < k_smallest){
        // 情况2：“参考牌”的位置比我们想找的牌的位置靠左了
        // 说明我们想找的牌在“参考牌”的右边那堆牌里
        return quick_selection(n, pivot_index + 1, right, k_smallest); // 递归去右边那堆牌里找
    }else{
        // 情况3：“参考牌”的位置比我们想找的牌的位置靠右了
        // 说明我们想找的牌在“参考牌”的左边那堆牌里
        return quick_selection(n, left, pivot_index - 1, k_smallest); // 递归去左边那堆牌里找
    }
}
```

- **它的任务：** 在指定的牌堆范围 (`left` 到 `right`) 里，找到“翻译”后的那个 `k_smallest` 索引的牌。
- **怎么找：**
  1. **基地情况：** 如果这堆牌里只剩下一张牌了（`left == right`），那这张牌肯定就是我们要找的，直接拿走。
  2. **分区：** 否则，它会调用 `partition` 函数，把当前这堆牌重新分一下，得到一个**“参考牌”的新位置 `pivot_index`**。
  3. **判断：**
     - **正好找到！** 如果这个 `pivot_index` 恰好就是我们要找的 `k_smallest` 索引，那太好了！`pivot_index` 上的那张牌就是答案，直接返回！
     - **找错了，往右边找！** 如果 `pivot_index` 比 `k_smallest` 小，说明“参考牌”排得太靠左了，我们要找的牌肯定在它的右边那堆牌里。所以，它会**只**在 `pivot_index + 1` 到 `right` 的范围里，继续用同样的方法找 `k_smallest` 索引的牌。
     - **找错了，往左边找！** 如果 `pivot_index` 比 `k_smallest` 大，说明“参考牌”排得太靠右了，我们要找的牌肯定在它的左边那堆牌里。所以，它会**只**在 `left` 到 `pivot_index - 1` 的范围里，继续用同样的方法找 `k_smallest` 索引的牌。

------

**这个算法的核心思想就是：**

1. 我有一堆乱序的牌。
2. 我想找到第 N−k 小的那张牌。
3. 我随机（这里是选最右边）挑一张牌作为“参考牌”。
4. 我把所有比“参考牌”小的牌挪到它左边，所有比它大的牌挪到它右边。然后把“参考牌”放到它最终该去的位置。
5. 现在“参考牌”的位置确定了。
6. 我就看这个“参考牌”的位置是不是我想要的那个第 N−k 小的索引。
   - 如果是，那我就找到了！
   - 如果不是，我就只去“参考牌”的左边那堆牌或者右边那堆牌里继续找（因为我知道我要的牌肯定在那一堆里），另一堆牌就完全不用管了。
7. 这样，每次都能排除掉一部分不需要查找的牌，大大提高了效率。

它和快速排序最大的不同是，快速排序要排序两边，而快速选择只排序包含目标元素的那一边，所以平均情况下比完全排序要快得多。



