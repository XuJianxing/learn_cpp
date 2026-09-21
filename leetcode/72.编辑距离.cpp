/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 *
 * https://leetcode.cn/problems/edit-distance/description/
 *
 * algorithms
 * Medium (64.15%)
 * Likes:    3973
 * Dislikes: 0
 * Total Accepted:    936.1K
 * Total Submissions: 1.5M
 * Testcase Example:  '"horse"\n"ros"'
 *
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
 * 
 * 你可以对一个单词进行如下三种操作：
 * 
 * 
 * 插入一个字符
 * 删除一个字符
 * 替换一个字符
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：word1 = "horse", word2 = "ros"
 * 输出：3
 * 解释：
 * horse -> rorse (将 'h' 替换为 'r')
 * rorse -> rose (删除 'r')
 * rose -> ros (删除 'e')
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：word1 = "intention", word2 = "execution"
 * 输出：5
 * 解释：
 * intention -> inention (删除 't')
 * inention -> enention (将 'i' 替换为 'e')
 * enention -> exention (将 'n' 替换为 'x')
 * exention -> exection (将 'n' 替换为 'c')
 * exection -> execution (插入 'u')
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= word1.length, word2.length <= 500
 * word1 和 word2 由小写英文字母组成
 * 
 * 
 */

#include <string>

using namespace std;

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    /*
    两个串的问题，状态直接套模板：
    dp[i][j] 表示 word1 的前 i 个字符 变成 word2 的前 j 个字符 所需的最少操作数

    递推从「最后一步」入手：把两个串上下对齐，最后一列只有三种形态
        (word1[i-1],  -         )  删除 word1[i-1]   -> dp[i-1][j] + 1
        (  -        , word2[j-1])  插入 word2[j-1]   -> dp[i][j-1] + 1
        (word1[i-1], word2[j-1])  替换(不等)或不动(相等) -> dp[i-1][j-1] + (相等 ? 0 : 1)
    最后一列穷举完了没有第四种，三种取 min 就是答案

    base case：
        dp[i][0] = i  word2 是空串，把 word1 全删掉
        dp[0][j] = j  word1 是空串，把 word2 全插进来

    计算顺序：dp[i][j] 依赖的三个前驱 (i-1,j) (i,j-1) (i-1,j-1) 的规模都更小，
    所以 i、j 两重循环从小到大即可
     */
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        // base case：其中一个串为空
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i; // word2 为空，全删
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j; // word1 为空，全插
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 三种「最后一步」取最小，没有 if / else 分支
                dp[i][j] = std::min({
                    dp[i - 1][j] + 1,                                         // 删除 word1[i-1]
                    dp[i][j - 1] + 1,                                         // 插入 word2[j-1]
                    dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1) // 替换 / 相等时不动
                });
            }
        }
        return dp[m][n];
    }
};
// @lc code=end

/*
DP 万能五步填空法
	步骤				做什么											填空句式
1. 认题型			求最值/计数 + 可拆成规模更小的同类问题					——
2. 定状态			dp[?] = ?											见下方"状态模板"
3. 想最后一步		要得到 dp[i]，最后一步操作可能是什么？					题目给了几种操作，就几种
4. 写转移			每种最后一步 → 对应一个更小的子问题 → 取 min/max/+		dp[i] = min(所有候选)
5. 定 base + 顺序	i=0 是什么；保证依赖已算好								——

DP 能递推的充要条件是「子问题规模严格变小 + 最后一步可穷举」

这道题能这么递推下去，核心要解决的疑虑：DP正确性
1. 从单字符串的递推过程来看，最小改动次数确实可能变大/变小，但是当前列的结果只和前驱的状态做三种操作后获得（增删改）
原理同数学归纳法
2. 实际上将word1变成word2，你必须要处理每个字符，不可跳过
*/
