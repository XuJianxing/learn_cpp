/*
 * @lc app=leetcode.cn id=1448 lang=cpp
 *
 * [1448] 统计二叉树中好节点的数目
 *
 * https://leetcode.cn/problems/count-good-nodes-in-binary-tree/description/
 *
 * algorithms
 * Medium (73.48%)
 * Likes:    222
 * Dislikes: 0
 * Total Accepted:    84.6K
 * Total Submissions: 115.2K
 * Testcase Example:  '[3,1,4,3,null,1,5]'
 *
 * 给你一棵根为 root 的二叉树，请你返回二叉树中好节点的数目。
 * 
 * 「好节点」X 定义为：从根到该节点 X 所经过的节点中，没有任何节点的值大于 X 的值。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：root = [3,1,4,3,null,1,5]
 * 输出：4
 * 解释：图中蓝色节点为好节点。
 * 根节点 (3) 永远是个好节点。
 * 节点 4 -> (3,4) 是路径中的最大值。
 * 节点 5 -> (3,4,5) 是路径中的最大值。
 * 节点 3 -> (3,1,3) 是路径中的最大值。
 * 
 * 示例 2：
 * 
 * 
 * 
 * 输入：root = [3,3,null,4,2]
 * 输出：3
 * 解释：节点 2 -> (3, 3, 2) 不是好节点，因为 "3" 比它大。
 * 
 * 示例 3：
 * 
 * 输入：root = [1]
 * 输出：1
 * 解释：根节点是好节点。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 二叉树中节点数目范围是 [1, 10^5] 。
 * 每个节点权值的范围是 [-10^4, 10^4] 。
 * 
 * 
 */

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
    int goodNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        int result = 0;
        dfs(root, root->val, result);
        return result;
    }

    // 方法2
    int goodNodes2(TreeNode* root) {
        if (root == nullptr) return 0;
        return dfs2(root, root->val);
    }
private:
    void dfs(TreeNode* root, int max, int& result)
    {
        if (root == nullptr) return;
        if (root->val >= max)
        {
            max = root->val;
            result++;
        }
        dfs(root->left, max, result);
        dfs(root->right, max, result);
    }

    // 另一种写法，用count局部变量
    // 表示：每个栈维护自己的count，互不干扰
    // 靠return把值逐层传回累加，更清晰地表达了“当前节点的结果 = 自身 + 左子树结果 + 右子树结果”
    // 更符合“自底向上”的递归思维
    int dfs2(TreeNode* node, int maxVal) {
        if (node == nullptr) return 0;

        int count = 0;
        if (node->val >= maxVal) {   // >= 是关键
            count = 1;
            maxVal = node->val;      // 更新路径最大值
        }

        count += dfs2(node->left, maxVal);
        count += dfs2(node->right, maxVal);
        return count;
    }
};
// @lc code=end

