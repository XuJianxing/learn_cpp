/*
 * @lc app=leetcode.cn id=104 lang=cpp
 *
 * [104] 二叉树的最大深度
 *
 * https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (79.03%)
 * Likes:    2142
 * Dislikes: 0
 * Total Accepted:    2.1M
 * Total Submissions: 2.7M
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * 给定一个二叉树 root ，返回其最大深度。
 * 
 * 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 
 * 
 * 输入：root = [3,9,20,null,null,15,7]
 * 输出：3
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = [1,null,2]
 * 输出：2
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中节点的数量在 [0, 10^4] 区间内。
 * -100 <= Node.val <= 100
 * 
 * 
 */

#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        // 广度优先遍历：每次从队列弹出一个节点，然后把子节点入队。
        // 如果遇到nullptr表示这一层结束了，那么剩余的都是下一层的了，给下一层加入nullptr
        if (root == nullptr) return 0;
        int count = 0;
        std::queue<TreeNode*> node_queue;
        node_queue.push(root);
        node_queue.push(nullptr);
        while (!node_queue.empty())
        {
            TreeNode* node = node_queue.front();
            node_queue.pop();
            if (node == nullptr)
            {
                count++;
                if (!node_queue.empty())
                {
                    node_queue.push(nullptr);
                }
            }
            else
            {
                if (node->left)
                {
                    node_queue.push(node->left);
                }
                if (node->right)
                {
                    node_queue.push(node->right);
                }
            }
        }
        return count;
    }

    // 去掉nullptr哨兵，因为记住了q.size，所以可以一次处理一整层
    int maxDepth1(TreeNode* root) {
        if (root == nullptr) return 0;
        std::queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();          // 当前层的节点数
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ++depth;
        }
        return depth;
    }

    // 深度优先遍历
    int maxDepth2(TreeNode* root) {
        if (root == nullptr) return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

};
// @lc code=end

/*
DFS 是"后序遍历"的思想——先得到左右子树的答案，再由子树答案推出当前节点的答案，
配合递归的调用栈自动完成"深入 + 回溯"。求最大深度只是它的一个典型应用。
*/
