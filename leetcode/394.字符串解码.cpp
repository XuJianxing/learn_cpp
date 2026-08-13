/*
 * @lc app=leetcode.cn id=394 lang=cpp
 *
 * [394] 字符串解码
 *
 * https://leetcode.cn/problems/decode-string/description/
 *
 * algorithms
 * Medium (61.76%)
 * Likes:    2263
 * Dislikes: 0
 * Total Accepted:    677.3K
 * Total Submissions: 1.1M
 * Testcase Example:  '"3[a]2[bc]"'
 *
 * 给定一个经过编码的字符串，返回它解码后的字符串。
 * 
 * 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
 * 
 * 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
 * 
 * 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
 * 
 * 测试用例保证输出的长度不会超过 10^5。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "3[a]2[bc]"
 * 输出："aaabcbc"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "3[a2[c]]"
 * 输出："accaccacc"
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：s = "2[abc]3[cd]ef"
 * 输出："abcabccdcdcdef"
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：s = "abc3[cd]xyz"
 * 输出："abccdcdcdxyz"
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 30
 * s 由小写英文字母、数字和方括号 '[]' 组成
 * s 保证是一个 有效 的输入。
 * s 中所有整数的取值范围为 [1, 300] 
 * 
 * 
 * 思路：
 * 一个重要前提：方括号[前一定有数字
 * 
 * 第一步：从结构特征判断"该用什么数据结构"
 * 注意顺序：最先遇到的 [ 是最后才被处理的，最先遇到的内容（外层的 3 和 a）要"先放一边"，等里层算完了再回来用。
 * "先放一边、后取出来用"就是**栈（后进先出）**的典型特征。所以判断出：需要栈来暂存外层信息。
 * 
 * 第二步：逐个字符扫描，按"当前字符是什么"分情况
 * 扫描时，任意时刻我只能看到当前一个字符。它能是什么？
 * 
 * 字符 含义                该做什么
 * 数字	接下来要重复的次数	但可能是多位（如 300），所以要累积：num = num * 10 + digit
 * [	进入新一层嵌套		把"之前累积的数字"和"之前的字符串"压栈暂存，然后清空，准备处理里层
 * ]	当前层结束			从栈顶取出数字 k 和上一层字符串 prev，拼成 prev + k*cur
 * 字母	当前层的普通内容	直接追加到当前累积串 cur
 * 
 * "累积"这种写法是为了处理多位数字和连续字母这两种边界情况。
 * 不需要用上一个字符是什么来推断状态，当前字符类型本身就能完整定义这个字符该干什么
 */

#include <string>
#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    string decodeString(string s) {
        std::vector<int> num_stack;          // 数字栈：存放重复次数 k
        std::vector<std::string> str_stack;  // 字符串栈：存放"["之前的累积串
        std::string cur;                     // 当前累积的字符串
        int num = 0;                         // 当前累积的数字

        for (auto &&c : s)
        {
            if (is_digit(c))
            {
                num = num * 10 + (c - '0');
            }
            else if (c == '[')
            {
                num_stack.push_back(num);
                str_stack.push_back(cur);
                num = 0;
                cur.clear();
            }
            else if (c == ']')
            {
                int k = num_stack.back();
                num_stack.pop_back();
                std::string prev = str_stack.back();
                str_stack.pop_back();

                std::string tmp;
                for (int i = 0; i < k; ++i)
                {
                    tmp += cur;
                }
                cur = prev + tmp;
            }
            else
            {
                cur.push_back(c);
            }
        }

        return cur;
    }

private:
    bool is_digit(char c)
    {
        if (c >= '0' && c <= '9')
        {
            return true;
        }
        return false;
    }
};
// @lc code=end

