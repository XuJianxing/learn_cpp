/*
 * @lc app=leetcode.cn id=443 lang=cpp
 *
 * [443] 压缩字符串
 *
 * https://leetcode.cn/problems/string-compression/description/
 *
 * algorithms
 * Medium (50.93%)
 * Likes:    457
 * Dislikes: 0
 * Total Accepted:    133K
 * Total Submissions: 261K
 * Testcase Example:  '["a","a","b","b","c","c","c"]'
 *
 * 给你一个字符数组 chars ，请使用下述算法压缩：
 * 
 * 从一个空字符串 s 开始。对于 chars 中的每组 连续重复字符 ：
 * 
 * 
 * 如果这一组长度为 1 ，则将字符追加到 s 中。
 * 否则，需要向 s 追加字符，后跟这一组的长度。
 * 
 * 
 * 压缩后得到的字符串 s 不应该直接返回 ，需要转储到字符数组 chars 中。需要注意的是，如果组长度为 10 或 10 以上，则在 chars
 * 数组中会被拆分为多个字符。
 * 
 * 请在 修改完输入数组后 ，返回该数组的新长度。
 * 
 * 你必须设计并实现一个只使用常量额外空间的算法来解决此问题。
 * 
 * 注意：数组中超出返回长度的字符无关紧要，应予忽略。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：chars = ["a","a","b","b","c","c","c"]
 * 输出：6
 * 解释：分组是 "aa"、"bb" 和 "ccc"，压缩为 "a2b2c3"。
 * 在原地修改输入数组之后，chars 的前 6 个字符应为 ["a","2","b","2","c","3"]。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：chars = ["a"]
 * 输出：1
 * 解释：唯一的组是 "a"，因为它是一个单独的字符，所以保持不变。
 * 在原地修改输入数组后，chars 的第一个字符应为 ["a"]。
 * 
 * 示例 3：
 * 
 * 
 * 输入：chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
 * 输出：4
 * 解释：分组是 "a" 和 "bbbbbbbbbbbb"，压缩为"ab12"。
 * 在对输入数组进行原地修改后，chars 的前 4 个字符应为 ["a","b","1","2"]。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= chars.length <= 2000
 * chars[i] 可以是小写英文字母、大写英文字母、数字或符号
 * 
 * 
 */

#include <vector>
#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = static_cast<int>(chars.size());
        int count = 1;
        int insert_i = 0;
        for (int i = 0; i < n; i++)
        {
            // i是当前分组的最后一个字符：下一个字符不同，或已到末尾
            // 这种判断方法可以让循环跑满，不用写边界特判情况
            if (i + 1 < n && chars[i] == chars[i + 1])
            {
                count++;
                continue;
            }

            chars[insert_i++] = chars[i];   // 无论分组多长，字符都要写
            if (count > 1)
            {
                for (const char c : std::to_string(count))
                {
                    chars[insert_i++] = c;
                }
                count = 1;
            }
        }
        return insert_i;
    }
};
// @lc code=end


int main()
{
    Solution s;
    vector<char> chars1{'a','a','b','b','c','c','c'};
    vector<char> chars2{'a'};
    vector<char> chars3{'a','b','b','b','b','b','b','b','b','b','b','b','b'};
    vector<char> chars4{'a','b','b','b','b','b','b','b','b','b','b','b','c'};
    vector<char> chars5{'a','b','b','b','b','b','b','b','b','b','b','c','c'};
    vector<char> chars6{'a','b','c'};
    s.compress(chars4);
    return 0;
}
