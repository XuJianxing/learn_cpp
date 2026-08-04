/*
 * @lc app=leetcode.cn id=1071 lang=cpp
 *
 * [1071] 字符串的最大公因子
 *
 * https://leetcode.cn/problems/greatest-common-divisor-of-strings/description/
 *
 * algorithms
 * Easy (59.71%)
 * Likes:    487
 * Dislikes: 0
 * Total Accepted:    110.5K
 * Total Submissions: 185K
 * Testcase Example:  '"ABCABC"\n"ABC"'
 *
 * 对于字符串 s 和 t，只有在 s = t + t + t + ... + t + t（t 自身连接 1 次或多次）时，我们才认定 “t 能除尽
 * s”。
 * 
 * 给定两个字符串 str1 和 str2 。返回 最长字符串 x，要求满足 x 能除尽 str1 且 x 能除尽 str2 。
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：str1 = "ABCABC", str2 = "ABC"
 * 
 * 输出："ABC"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：str1 = "ABABAB", str2 = "ABAB"
 * 
 * 输出："AB"
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：str1 = "LEET", str2 = "CODE"
 * 
 * 输出：""
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：str1 = "AAAAAB", str2 = "AAA"
 * 
 * 输出：""
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= str1.length, str2.length <= 1000
 * str1 和 str2 由大写英文字母组成
 * 
 * 
 */

#include <string>
using namespace std;

// @lc code=start
class Solution {
public:

    bool canBeDivided(const string& base, const string& sub)
    {
        if (base.length() == 0 || sub.length() == 0)
        {
            return false;
        }
        if (base.length() % sub.length() != 0)
        {
            return false;
        }
        for (size_t i = 0; i < base.length(); i += sub.length())
        {
            if (base.substr(i, sub.length()) != sub)
            {
                return false;
            }
        }
        return true;
    }

    string gcdOfStrings(string str1, string str2) {
        string result;
        for (size_t i = 0; i <= str1.length() && i <= str2.length(); i++)
        {
            string sub = str1.substr(0, i);
            if (canBeDivided(str1, sub) && canBeDivided(str2, sub))
            {
                result = sub;
            }
        }
        return result;
    }
};
// @lc code=end

int main()
{
    Solution s;
    string s1 = "ABCABC";
    string s2 = "ABC";
    s.gcdOfStrings(s1, s2);
    return 0;
}
