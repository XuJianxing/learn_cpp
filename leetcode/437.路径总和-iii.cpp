/*
 * @lc app=leetcode.cn id=437 lang=cpp
 *
 * [437] 路径总和 III
 *
 * https://leetcode.cn/problems/path-sum-iii/description/
 *
 * algorithms
 * Medium (49.19%)
 * Likes:    2348
 * Dislikes: 0
 * Total Accepted:    678.5K
 * Total Submissions: 1.4M
 * Testcase Example:  '[10,5,-3,3,2,null,11,3,-2,null,1]\n8'
 *
 * 给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
 * 
 * 路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
 * 输出：3
 * 解释：和等于 8 的路径有 3 条，如图所示。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * 输出：3
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 二叉树的节点个数的范围是 [0,1000]
 * -10^9  
 * -1000  
 * 
 * 
 */

#include <vector>
#include <unordered_map>

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
    // 最优解：前缀和+哈希表，O(n)
    int pathSum_best(TreeNode* root, int targetSum) {
        std::unordered_map<long long, int> prefix;
        prefix[0] = 1;   // 空路径前缀和为 0，处理"路径从根开始"的情况
        return dfs_best(root, 0, targetSum, prefix);
    }

    int pathSum(TreeNode* root, int targetSum) {
        // 思路：深度遍历过程中，维护已走路径的节点数组，每走一个节点，从当前开始往前回溯一遍数组并求和
        // 每求和遇到目标值，则数量+1
        if (root == nullptr) return 0;
        std::vector<int> path;
        return dfs(root, targetSum, path);
    }

private:
    int dfs_best(TreeNode* node, long long curSum, int targetSum,
            std::unordered_map<long long, int>& prefix) {
        if (node == nullptr) return 0;

        curSum += node->val;

        // 原理：前缀和出现的次数正好与该节点到当前节点的路径和targetSum的次数相同

        // "某条路径和为 targetSum" ⟺ "它的起点的父节点的前缀和 == curSum - targetSum"。

        // 不同的路径 → 起点不同 → 起点父节点不同 → 对应不同的前缀和节点（不重）
        // 每条满足条件的路径都能找到对应（不漏）
        int count = prefix[curSum - targetSum];  // 以当前节点为终点的路径数

        prefix[curSum]++;                        // 记录当前前缀和
        count += dfs_best(node->left, curSum, targetSum, prefix);
        count += dfs_best(node->right, curSum, targetSum, prefix);
        prefix[curSum]--;                        // 回溯，撤销当前路径的影响

        return count;
    }

    int dfs(TreeNode* root, int target_sum, std::vector<int>& path)
    {
        if (root == nullptr) return 0;
        path.push_back(root->val);
        long long sum = 0;  // sum会溢出，所以需要64位才行
        int count = 0;
        for (auto it = path.rbegin(); it != path.rend(); it++)
        {
            sum += *it;
            if (sum == target_sum)
            {
                count++;
            }
        }
        count += dfs(root->left, target_sum, path);
        count += dfs(root->right, target_sum, path);

        // 必须的操作：回溯，当前节点结束了，返回的时候，需要弹出当前节点，
        // 否则就不对了，因为传的是引用。如果是值传递的话反而是对的，不需要pop了
        path.pop_back();
        return count;
    }
};
// @lc code=end

