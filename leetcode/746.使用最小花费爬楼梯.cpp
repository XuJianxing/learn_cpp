/*
 * @lc app=leetcode.cn id=746 lang=cpp
 *
 * [746] 使用最小花费爬楼梯
 *
 * https://leetcode.cn/problems/min-cost-climbing-stairs/description/
 *
 * algorithms
 * Easy (68.06%)
 * Likes:    1806
 * Dislikes: 0
 * Total Accepted:    664.3K
 * Total Submissions: 976.3K
 * Testcase Example:  '[10,15,20]'
 *
 * 给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。
 * 
 * 一旦你支付此费用，即可选择向上爬 一个 或者 两个 台阶。
 * 
 * 你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
 * 
 * 请你计算并返回达到楼梯顶部的 最低 花费，即最后一步之后的那个位置（下标 cost.length）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：cost = [10,15,20]
 * 输出：15
 * 解释：你将从下标为 1 的台阶开始。
 * - 支付 15 ，向上爬两个台阶，到达楼梯顶部。
 * 总花费为 15 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：cost = [1,100,1,1,1,100,1,1,100,1]
 * 输出：6
 * 解释：你将从下标为 0 的台阶开始。
 * - 支付 1 ，向上爬两个台阶，到达下标为 2 的台阶。
 * - 支付 1 ，向上爬两个台阶，到达下标为 4 的台阶。
 * - 支付 1 ，向上爬两个台阶，到达下标为 6 的台阶。
 * - 支付 1 ，向上爬一个台阶，到达下标为 7 的台阶。
 * - 支付 1 ，向上爬两个台阶，到达下标为 9 的台阶。
 * - 支付 1 ，向上爬一个台阶，到达楼梯顶部。
 * 总花费为 6 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= cost.length <= 1000
 * 0 <= cost[i] <= 999
 * 
 * 
 */

#include <algorithm>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
/*
你在第 i 阶"选便宜的到达方式"不会埋雷，因为更便宜地站在同一个 i，后面想怎么走还怎么走，没有任何后遗症；
你"选便宜的下一阶"才会埋雷，因为便宜的下一阶可能通向昂贵的未来。
历史代价已经被压缩进 dp[i-1]、dp[i-2] 里了，所以这个"取最小"其实是全局信息的比较，不是鼠目寸光的贪心。
*/
/*
不是"到达 i 就必然付 cost[i]"，而是"只要 i 是你的落脚点、且你还要继续往上，cost[i] 就是你迟早要付的钱"
换一种口径就变成"到达时不加、离开时加"。不管怎样，这个位置没到顶，早晚会花费这些
*/
    int minCostClimbingStairs(vector<int>& cost) {
        // dp[i] = min(dp[i-1], dp[i-2]) + cost[i]，只依赖前两项，滚动成两个变量
        int dp_i_2 = cost[0];  // dp[0]
        int dp_i_1 = cost[1];  // dp[1]

        for (int i = 2; i < static_cast<int>(cost.size()); ++i) {
            int dp_i = min(dp_i_1, dp_i_2) + cost[i];
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        // 顶部是下标 n，可由 n-1 跨一步或 n-2 跨两步到达
        return min(dp_i_1, dp_i_2);
    }
};
// @lc code=end

// ---------------------------------------------------------------------------
// 未优化版 1：保留完整 dp 数组（O(n) 空间）
// 与优化版逐行对应，方便对照"滚动变量"到底省掉了什么。
// ---------------------------------------------------------------------------
class SolutionFullDp {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n);  // dp[i]：到达台阶 i 的最小累计花费

        dp[0] = cost[0];  // 允许从 0 起步，起步不额外收费
        dp[1] = cost[1];  // 允许从 1 起步

        for (int i = 2; i < n; ++i) {
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        }

        return min(dp[n - 1], dp[n - 2]);
    }
};

// ---------------------------------------------------------------------------
// 未优化版 2：自顶向下 + 记忆化（O(n) 空间 + 递归栈）
// f(i)：从台阶 i 出发到达顶部的最小花费，答案 = min(f(0), f(1))。
// 思路和优化版完全等价，只是方向相反，更容易看出"无后效性"：
// f(i) = cost[i] + min(f(i+1), f(i+2))，只取决于 i，与怎么走到 i 无关。
// ---------------------------------------------------------------------------
class SolutionMemo {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        n_ = cost.size();
        memo_.assign(n_, -1);
        return min(f(cost, 0), f(cost, 1));
    }

private:
    int n_;
    vector<int> memo_;

    int f(const vector<int>& cost, int i) {
        if (i >= n_) return 0;      // 越过顶部，不再付费
        if (memo_[i] != -1) return memo_[i];
        return memo_[i] = cost[i] + min(f(cost, i + 1), f(cost, i + 2));
    }
};

