# LeetCode 二叉树的最近的公共祖先

​	这是笔者刷的一个最近的公共祖先的问题。

> 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
>
> [百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

​	嗯，实际上我们可以从小的开始思考我们的思路，事情如下：

> 1. 对于非自己的叶子节点，其公共祖先就是nullptr，因为实在不是自己的交集嘛！
>
> 2. 对于是自己的目标的叶子节点，返回自己即可，因为自己是自己的最近公共祖先
>
> 3. 对于返回，我们假定在左子树上找到了公共祖先，就承接上，返回出去（这是2的延拓）；反之，返回右子树的，因为若返回了空，情况就会递归回退到1上了
> 4. 如果是我们的右子树上也找到了公共祖先，说明，我们现在出现了p和q节点的祖先都在root的左右两侧，那显然祖先就在我们的root上了了，返回出去！

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) // not the case for p and q, these is empty
            return nullptr; // view as not in
        if(root == p || root == q) return root; // if is self, return self

        TreeNode* left_common = lowestCommonAncestor(root->left, p, q);
        TreeNode* right_common = lowestCommonAncestor(root->right, p, q);

        if(!left_common) // then it is in right
            return right_common;
        if(!right_common)
            return left_common;

        return root; // common session;
    }
};
```

