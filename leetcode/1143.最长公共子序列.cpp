/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 *
 * [1143] 最长公共子序列
 *
 * https://leetcode.cn/problems/longest-common-subsequence/description/
 *
 * algorithms
 * Medium (67.76%)
 * Likes:    1955
 * Dislikes: 0
 * Total Accepted:    907.1K
 * Total Submissions: 1.3M
 * Testcase Example:  '"abcde"\n"ace"'
 *
 * 给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
 * 
 * 一个字符串的 子序列
 * 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
 * 
 * 
 * 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
 * 
 * 
 * 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：text1 = "abcde", text2 = "ace" 
 * 输出：3  
 * 解释：最长公共子序列是 "ace" ，它的长度为 3 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：text1 = "abc", text2 = "abc"
 * 输出：3
 * 解释：最长公共子序列是 "abc" ，它的长度为 3 。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：text1 = "abc", text2 = "def"
 * 输出：0
 * 解释：两个字符串没有公共子序列，返回 0 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * text1 和 text2 仅由小写英文字符组成。
 * 
 * 
 */

#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    /* 
    考虑从头开始字符串每增加一个字符，都可能新增更长子序列，并且因为子序列可以不连续，所以每来一个字符都可以在之前最长的基础上累计，所以可以是动态规划问题
    两个字符串取子序列，因为要分别考虑每个字符串的不同子长度，分别从头开始增加字符，所以是一个二维DP问题

    dp[i][j]表示text1的长度为i的前缀 与 text2的长度为j的前缀 的最长公共子序列
    所以i或j为0时表示空串，所以dp[i][j]=0 (i==0||j==0)
    考虑ij都大于0的情况：
    如果text1[i−1] == text2[j−1]，就等于多了一个公共字符，那就是子序列长度+1了。
    那就是两个字符串都去掉当前字符时的最长值+1，也就是 dp[i][j] = dp[i−1][j−1] + 1
    否则，就用两个字符串的之前的前缀的最大公共子序列长度作为当前长度的字符串的最长公共子序列长度
    也就是二维数组左边或上边的最大值：dp[i][j] = max(dp[i−1][j], dp[i][j−1])
     */
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
        // 注意，i j是长度，而不是下标，因此当下标取值时需要-1
        for (int i = 1; i <= m; i++) {
            char c1 = text1.at(i - 1);
            for (int j = 1; j <= n; j++) {
                char c2 = text2.at(j - 1);
                if (c1 == c2) {
                    // 不能取上面或者左面，因为这两个地方已经消费过这个新字符了，必须要取左上都不包含该字符的位置
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};
// @lc code=end

