# Leetcode Easy刷题：合并两个连续系列

## 1. 合并两个有序数组

​	我们下面准备聊的是合并两个连续数组：

> 给你两个按 **非递减顺序** 排列的整数数组 `nums1` 和 `nums2`，另有两个整数 `m` 和 `n` ，分别表示 `nums1` 和 `nums2` 中的元素数目。
>
> 请你 **合并** `nums2` 到 `nums1` 中，使合并后的数组同样按 **非递减顺序** 排列。
>
> **注意：**最终，合并后数组不应由函数返回，而是存储在数组 `nums1` 中。为了应对这种情况，`nums1` 的初始长度为 `m + n`，其中前 `m` 个元素表示应合并的元素，后 `n` 个元素为 `0` ，应忽略。`nums2` 的长度为 `n` 。

​	很显然，我们的第一个反应就是，

```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(const auto& each : nums2){
            nums1[m++] = each;
        }
        sort(nums1.begin(), nums1.end());
	}
}
```

​	我知道您可能开始笑了，的确，这样做很容易出现一个问题：他们本来就是有序的了，我们这样直接插入后打乱重拍，必然遇到的问题就是：对一个近似有序的数组搞快排实际上浪费大量的时间。因此，我们不妨改进一下。

​	思考下面的过程，我们的数组已经reserve了m + n个单位，所以内存的事情我们不需要担心，但是我们需要考虑的是，为什么不充分利用：已经有序的条件，我们直接搞插入呢？我们构思一下，我们最后所有的元素要存储在我们的nums1中，我们直接将nums2插入到nums1就好了，如何插入呢？

> - nums2的最后一个要是显著的大于nums1的最后一个，直接将nums2插入到当前我们正在处理的index的位置就好了
> - 如果小于，我们就拷贝nums1的最后一个。直到我们拷贝结束。
> - 但问题来了，如果我们的数组中全被拷贝完了我们的nums1，还剩下nums2咋办呢？直接继续向前拷贝表示的是直接填充就好了。

```cpp
        int index_of_num1 = m - 1; // index 1 points to the current handling session
        int index_of_num2 = n - 1; // index 2 points to the current handling session
        int index_of_tol = m + n - 1; // points to the last one
```

​	我们先把最后一个index给抓出来，index_of_tol实际上就是我们写入的位置（您可以改成write_index，看你）在循环拷贝（即：index_of_num1和index_of_num2都指向有效的位置的时候）时，检查我们的大小是否匹配，落入何种拷贝分支。

```cpp
        while(index_of_num2 >= 0 && index_of_num1 >= 0){
            if(nums2[index_of_num2] > nums1[index_of_num1]){ // copy the nums2
                // then it should be insert back
                nums1[index_of_tol] = nums2[index_of_num2];
                // nums2 is finished
                index_of_num2--;            
            }else if(nums2[index_of_num2] <= nums1[index_of_num1]){ 
                // should insert before, just place the nusm1
                nums1[index_of_tol] = nums1[index_of_num1];
                index_of_num1--;
            }

            // insert place also went back
            index_of_tol--;
        }
```

> 笔者不喜欢精凑的代码风格，因为实在是难以分析，相信伟大的编译器优化.png

​	但是还有问题，假如说我们的nums2还残存着比nums1最小的代码还要小的残留部分

```cpp
        while (index_of_num2 >= 0) {
            nums1[index_of_tol--] = nums2[index_of_num2--];
        }
```

​	于是我们拷贝！这样就OK了！

## 合并有序链表

​	数组我们可以使用下表滑动的方式，对于链表，我们完全可以考虑使用一个哑节点来简化边界条件，一般我们可以考虑自动创建和销会的对象，也就是在栈上创建。

> 将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        static constexpr signed int MIN_ONE = -101;
        ListNode dummy_one(MIN_ONE);
        ListNode* dummy_head = &dummy_one;
        ListNode* real_head = dummy_head;
        while(list1 && list2){
            // if we are also handling the l1 and l2
            if(list1->val <= list2->val){
                // now we should consider the list1 for insertion
                dummy_head->next = list1;
                list1 = list1->next;
            }else{
                dummy_head->next = list2;
                list2 = list2->next;   // alright, now to the next  
            }
            dummy_head = dummy_head->next;
        }

        // make the reserved
        while(list1){
            dummy_head->next = list1;
            list1 = list1->next;
            dummy_head = dummy_head->next;
        }

        while(list2){
            dummy_head->next = list2;
            list2 = list2->next;          
            dummy_head = dummy_head->next;  
        }
        return real_head->next;
    }
};
```

​	合并有序系列，更多的是考察使用若干游标指针进行插入合并。