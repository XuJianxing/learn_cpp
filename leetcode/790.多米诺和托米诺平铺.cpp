/*
 * @lc app=leetcode.cn id=790 lang=cpp
 *
 * [790] 多米诺和托米诺平铺
 *
 * https://leetcode.cn/problems/domino-and-tromino-tiling/description/
 *
 * algorithms
 * Medium (51.61%)
 * Likes:    471
 * Dislikes: 0
 * Total Accepted:    58.5K
 * Total Submissions: 113.4K
 * Testcase Example:  '3'
 *
 * 有两种形状的瓷砖：一种是 2 x 1 的多米诺形，另一种是形如 "L" 的托米诺形。两种形状都可以旋转。
 * 
 * 
 * 
 * 给定整数 n ，返回可以平铺 2 x n 的面板的方法的数量。返回对 10^9 + 7 取模 的值。
 * 
 * 平铺指的是每个正方形都必须有瓷砖覆盖。两个平铺不同，当且仅当面板上有四个方向上的相邻单元中的两个，使得恰好有一个平铺有一个瓷砖占据两个正方形。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 
 * 
 * 输入: n = 3
 * 输出: 5
 * 解释: 五种不同的方法如上所示。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: n = 1
 * 输出: 1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 1000
 * 
 * 
 */

#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    int numTilings(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;
        if (n == 3) return 5;
        std::vector<long long> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;
        /*
        看不懂，想不清楚，直接记答案吧
        n = 1 → 1
        n = 2 → 2
        n = 3 → 5
        n = 4 → 11
        n = 5 → 24
        f(n) = 2 × f(n−1) + f(n−3)
        */
        for (int i = 4; i <= n; ++i) {
            dp[i] = (2 * dp[i - 1] + dp[i -3]) % 1000000007;
        }
        return dp[n];
    }
};
// @lc code=end

