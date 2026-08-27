/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 *
 * https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
 *
 * algorithms
 * Medium (75.28%)
 * Likes:    3279
 * Dislikes: 0
 * Total Accepted:    1.3M
 * Total Submissions: 1.7M
 * Testcase Example:  '[3,5,1,6,2,0,8,null,null,7,4]\n5\n1'
 *
 * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 * 
 * 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x
 * 的深度尽可能大（一个节点也可以是它自己的祖先）。”
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * 输出：3
 * 解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * 输出：5
 * 解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：root = [1,2], p = 1, q = 2
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中节点数目在范围 [2, 10^5] 内。
 * -10^9 
 * 所有 Node.val 互不相同 。
 * p != q
 * p 和 q 均存在于给定的二叉树中。
 * 
 * 
 */

#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // 更优方式：
    /*
    * 核心思想：自底向上回溯。对每个节点：
    *   若 root 是 p 或 q 或空，直接返回
    *   递归左右子树，看 p、q 在哪一侧
    *   左右都非空 → 当前节点就是 LCA
    *   只有一侧非空 → 说明 p、q 都在那一侧，继续向上传递结果
    * 时间：O(n)，单次遍历
    * 空间：O(h)，h 为树高（只有递归栈，无需额外数组）
    */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 这一步很关键，这表示找到pq节点就结束，也就是让pq节点分立左右两边
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 前提是pq肯定要在树里才行
        if (left && right) return root;   // p、q 分居两侧
        return left ? left : right;       // 都在其中一侧
    }

    TreeNode* lowestCommonAncestor_2(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 自己想的思路：分别深度优先找到从根节点到p和q的路径，然后从根开始分别遍历，直到第一个不一样的节点为止
        if (root == nullptr || p == nullptr || q == nullptr) return nullptr;
        std::vector<TreeNode*> p_path;
        std::vector<TreeNode*> q_path;
        dfs(root, p, p_path);
        dfs(root, q, q_path);
        int i = 0;
        int length = std::min(p_path.size(), q_path.size());
        // 注意有可能一个路径是另一个路径的父路径，如果直接遍历路径找，有可能循环直接走到结束，没有任何处理
        while (i < length && p_path[i] == q_path[i]) {
            i++;
        }
        return p_path[i - 1];  // i 至少为 1（根一定相同）
    }

private:
    // 用 bool 返回值 + 命中即剪枝
    bool dfs(TreeNode* root, TreeNode* node, std::vector<TreeNode*>& path) {
        if (root == nullptr) return false;
        path.push_back(root);
        // 先判断是否可以结束
        if (root == node) return true;                    // 命中：保留 path，立即返回
        if (dfs(root->left,  node, path)) return true;    // 左子树找到，直接向上传（层层上传）
        if (dfs(root->right, node, path)) return true;    // 右子树找到，直接向上传
        path.pop_back();                                   // 都没找到：回溯
        return false;
    }

};
// @lc code=end

