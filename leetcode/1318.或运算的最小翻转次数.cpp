/*
 * @lc app=leetcode.cn id=1318 lang=cpp
 *
 * [1318] 或运算的最小翻转次数
 *
 * https://leetcode.cn/problems/minimum-flips-to-make-a-or-b-equal-to-c/description/
 *
 * algorithms
 * Medium (70.16%)
 * Likes:    98
 * Dislikes: 0
 * Total Accepted:    25.5K
 * Total Submissions: 36.4K
 * Testcase Example:  '2\n6\n5'
 *
 * 给你三个正整数 a、b 和 c。
 * 
 * 你可以对 a 和 b 的二进制表示进行位翻转操作，返回能够使按位或运算   a OR b == c  成立的最小翻转次数。
 * 
 * 「位翻转操作」是指将一个数的二进制表示任何单个位上的 1 变成 0 或者 0 变成 1 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：a = 2, b = 6, c = 5
 * 输出：3
 * 解释：翻转后 a = 1 , b = 4 , c = 5 使得 a OR b == c
 * 
 * 示例 2：
 * 
 * 输入：a = 4, b = 2, c = 7
 * 输出：1
 * 
 * 
 * 示例 3：
 * 
 * 输入：a = 1, b = 2, c = 3
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= a <= 10^9
 * 1 <= b <= 10^9
 * 1 <= c <= 10^9
 * 
 * 
 */

#include <bitset>
#include <string>

// @lc code=start
class Solution {
public:
    int minFlips(int a, int b, int c) {
        // 指定32位宽度，自动补零
        std::bitset<32> a2(a);
        std::bitset<32> b2(b);
        std::bitset<32> c2(c);
        // 转换为字符串
        std::string a2s = a2.to_string();
        std::string b2s = b2.to_string();
        std::string c2s = c2.to_string();
        int result = 0;
        for (std::size_t i = 0; i < a2s.length(); i++)
        {
            int ai = a2s[i] - '0';
            int bi = b2s[i] - '0';
            int ci = c2s[i] - '0';
            // 要加括号，因为 或 比 == 优先级低
            if ((ai | bi) == ci) continue;
            if (ci == 0)
            {
                // 目标位为 0，a、b 中为 1 的都得翻成 0
                result += ai + bi;
            }
            else
            {
                // 目标位为 1 且 a|b == 0，说明 a、b 都是 0，翻任意一个即可
                result += 1;
            }
        }
        return result;
    }

    int minFlips_2(int a, int b, int c) {
        // XOR 的特性：两位相同得 0，不同得 1
        // 先求出最直接结果中每个不一致的位数
        // 然后额外处理 a b都是1但是c要求是0 的位 （因为最终结果的不一致，没法说明a b是要改1次还是2次）
        return __builtin_popcount((a | b) ^ c)      // a|b 与 c 不同的位，翻一次
            + __builtin_popcount((a & b) & ~c);    // a、b 都是 1 但 c 是 0，需再翻一次
    }

};
// @lc code=end

