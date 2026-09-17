/*
 * @lc app=leetcode.cn id=62 lang=cpp
 *
 * [62] 不同路径
 *
 * https://leetcode.cn/problems/unique-paths/description/
 *
 * algorithms
 * Medium (70.40%)
 * Likes:    2382
 * Dislikes: 0
 * Total Accepted:    1.3M
 * Total Submissions: 1.8M
 * Testcase Example:  '3\n7'
 *
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
 * 
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
 * 
 * 问总共有多少条不同的路径？
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：m = 3, n = 7
 * 输出：28
 * 
 * 示例 2：
 * 
 * 
 * 输入：m = 3, n = 2
 * 输出：3
 * 解释：
 * 从左上角开始，总共有 3 条路径可以到达右下角。
 * 1. 向右 -> 向下 -> 向下
 * 2. 向下 -> 向下 -> 向右
 * 3. 向下 -> 向右 -> 向下
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：m = 7, n = 3
 * 输出：28
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：m = 3, n = 3
 * 输出：6
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= m, n <= 100
 * 题目数据保证答案小于等于 2 * 10^9
 * 
 * 
 */

#include <algorithm>
#include <vector>

// @lc code=start
class Solution {
public:
    /* 
    走到终点一定会向下走m-1步，向右走n-1步。所以不同的走法其实就是你如何分配每一步的选择，不同的选择组合出不同的走法
     */
    int uniquePaths(int m, int n) {
        // C(n, k) = C(m+n-2, m-1) = (m+n-2)! / ((m-1)! * (n-1)!)
        long long res = 1;                       // 中间要先乘再除，乘了以后可能马上超出了，除了又回去了
        int k = std::min(m - 1, n - 1);          // 取较小的那个，循环次数更少
        /* 
        1. 
        令 k = min(m - 1, n - 1), N = m + n - 2
        则 C(N, k) = (N-k+1)*(N-k+2)...N / 1*2...k    这时候已经约掉了(m-1)!或者(n-1)!
        分子分母都是k个因子
        2. 为什么每轮都可以除？
        因为C(n, k) = C(n-1, k-1) * n / k
        所以从头开始计算累乘，而且每一步都是组合数
        比如：C(3,1) -> C(4,2) -> C(5,3) -> C(6,4) -> C(7,5)...
         */
        for (int i = 1; i <= k; ++i) {
            res = res * (m + n - 2 - k + i) / i;
        }
        return res;
    }

    int uniquePaths_c(int m, int n) {
        if (m > n) std::swap(m, n);
        long long ans = 1;
        for (int x = n, y = 1; y < m; ++x, ++y) {
            ans = ans * x / y;
        }
        return ans;
    }

    /* 
    二维DP：到达格子 (i,j) 的最后一步只可能来自上方 (i-1,j) 或左方 (i,j-1)，所以：
    dp[i][j] = dp[i-1][j] + dp[i][j-1]
     */
    int uniquePaths_dp(int m, int n) {
        std::vector<std::vector<int>> f(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i) {
            f[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            f[0][j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
        return f[m - 1][n - 1];
    }

    /* 
    dp中的滚动值推广到二维可以是滚动数组
    内层循环里 dp[j] += dp[j-1]，dp[j] 更新前是「上一行的上方值」，dp[j-1] 更新后是「本行左方值」。

    因为外层循环：每一次循环就是推进一层，和上面的二维数组是一样的做法，每一次循环就是推进一层
    内层循环就是从左到右处理当前层和上一层，还没更新的当前值i，就是上一层。更新后的i-1就是更新后的左方值

    另一种解释法：这样做其实在算： 新的一行 = 上一行的前缀和
     */
    int uniquePaths_dp_2(int m, int n) {
        if (m < n) std::swap(m, n);
        std::vector<int> f(n, 1);
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                f[j] += f[j-1];
            }
        }
        return f[n - 1];
    }
};
// @lc code=end

