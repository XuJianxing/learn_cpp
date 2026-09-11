/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 *
 * https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (63.83%)
 * Likes:    3301
 * Dislikes: 0
 * Total Accepted:    1.4M
 * Total Submissions: 2.2M
 * Testcase Example:  '"23"'
 *
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
 * 
 * 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：digits = "23"
 * 输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：digits = "2"
 * 输出：["a","b","c"]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= digits.length <= 4
 * digits[i] 是范围 ['2', '9'] 的一个数字。
 * 
 * 
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// @lc code=start
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        std::vector<string> result;
        if (digits.size() == 0) return result;
        std::string now_str;
        dfs(digits, 0, now_str, result);
        return result;
    }

    // BFS做法
    // 递归本质是「对每一位做一次笛卡尔积」，所以能平铺成迭代。
    // 把结果集当成一个「当前层」，每处理一个数字就把整层乘上该数字的字母集：
    vector<string> letterCombinations_2(string digits) {
        if (digits.empty()) return {};
        vector<string> res{""};              // 种子：空串
        for (char d : digits) {
            vector<string> next;
            next.reserve(res.size() * char_map[d].size());
            for (const string& s : res)
                for (char c : char_map[d])
                    next.push_back(s + c);   // 或 s.push_back(c)/pop_back() 复用
            res.swap(next);
        }
        return res;
    }

private:
    // 比哈希查找更快
    const std::vector<std::string> letters{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    std::unordered_map<char, std::vector<char>> char_map
    {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}},
    };
    void dfs(const std::string& digits, int pos, std::string& now_str, std::vector<std::string>& result)
    {
        for (auto &&i : letters[digits[pos] - '0'])
        {
            now_str.push_back(i);
            if (pos + 1 < digits.length())
                dfs(digits, pos + 1, now_str, result);
            else
                result.push_back(now_str);
            now_str.pop_back();
        }
    }
};
// @lc code=end

