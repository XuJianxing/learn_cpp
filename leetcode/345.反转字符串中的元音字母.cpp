/*
 * @lc app=leetcode.cn id=345 lang=cpp
 *
 * [345] 反转字符串中的元音字母
 *
 * https://leetcode.cn/problems/reverse-vowels-of-a-string/description/
 *
 * algorithms
 * Easy (57.00%)
 * Likes:    395
 * Dislikes: 0
 * Total Accepted:    251.3K
 * Total Submissions: 440.9K
 * Testcase Example:  '"IceCreAm"'
 *
 * 给你一个字符串 s ，仅反转字符串中的所有元音字母，并返回结果字符串。
 * 
 * 元音字母包括 'a'、'e'、'i'、'o'、'u'，且可能以大小写两种形式出现不止一次。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "IceCreAm"
 * 
 * 输出："AceCreIm"
 * 
 * 解释：
 * 
 * s 中的元音是 ['I', 'e', 'e', 'A']。反转这些元音，s 变为 "AceCreIm".
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "leetcode"
 * 
 * 输出："leotcede"
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 3 * 10^5
 * s 由 可打印的 ASCII 字符组成
 * 
 * 
 */

#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    bool isVowel(char c) {
        return string("aeiouAEIOU").find(c) != string::npos;
    }

    string reverseVowels(string s) {
        string vowels;
        for (const auto& c : s)
        {
            if (isVowel(c))
            {
                vowels.push_back(c);
            }
        }
        
        int j = vowels.length() - 1;
        for (size_t i = 0; i < s.length(); i++)
        {
            if (isVowel(s[i]))
            {
                s[i] = vowels[j];
                j--;
            }
        }
        return s;
    }
};
// @lc code=end

