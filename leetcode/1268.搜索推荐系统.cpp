/*
 * @lc app=leetcode.cn id=1268 lang=cpp
 *
 * [1268] 搜索推荐系统
 *
 * https://leetcode.cn/problems/search-suggestions-system/description/
 *
 * algorithms
 * Medium (62.61%)
 * Likes:    227
 * Dislikes: 0
 * Total Accepted:    33.1K
 * Total Submissions: 52.8K
 * Testcase Example:  '["mobile","mouse","moneypot","monitor","mousepad"]\n"mouse"'
 *
 * 给你一个产品数组 products 和一个字符串 searchWord ，products  数组中每个产品都是一个字符串。
 * 
 * 请你设计一个推荐系统，在依次输入单词 searchWord 的每一个字母后，推荐 products 数组中前缀与 searchWord
 * 相同的最多三个产品。如果前缀相同的可推荐产品超过三个，请按字典序返回最小的三个。
 * 
 * 请你以二维列表的形式，返回在输入 searchWord 每个字母后相应的推荐产品的列表。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord
 * = "mouse"
 * 输出：[
 * ["mobile","moneypot","monitor"],
 * ["mobile","moneypot","monitor"],
 * ["mouse","mousepad"],
 * ["mouse","mousepad"],
 * ["mouse","mousepad"]
 * ]
 * 解释：按字典序排序后的产品列表是 ["mobile","moneypot","monitor","mouse","mousepad"]
 * 输入 m 和 mo，由于所有产品的前缀都相同，所以系统返回字典序最小的三个产品 ["mobile","moneypot","monitor"]
 * 输入 mou， mous 和 mouse 后系统都返回 ["mouse","mousepad"]
 * 
 * 
 * 示例 2：
 * 
 * 输入：products = ["havana"], searchWord = "havana"
 * 输出：[["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
 * 
 * 
 * 示例 3：
 * 
 * 输入：products = ["bags","baggage","banner","box","cloths"], searchWord =
 * "bags"
 * 
 * 输出：[["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
 * 
 * 
 * 示例 4：
 * 
 * 输入：products = ["havana"], searchWord = "tatiana"
 * 输出：[[],[],[],[],[],[],[]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= products.length <= 1000
 * 1 <= Σ products[i].length <= 2 * 10^4
 * products[i] 中所有的字符都是小写英文字母。
 * 1 <= searchWord.length <= 1000
 * searchWord 中所有字符都是小写英文字母。
 * 
 * 
 */

#include <algorithm>
#include <vector>
#include <string>
#include "208.实现-trie-前缀树.cpp"

using namespace std;

// @lc code=start
// ---------------------------------------------------------------------------
// 另一种解法：排序 + 二分（更常见、代码更短、额外空间 O(1)）
// 排序后所有以 prefix 开头的单词必然是数组中连续的一段，
// 用 lower_bound 定位这段的起点，往后取 3 个就是字典序最小的 3 个。
// ---------------------------------------------------------------------------
class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        std::sort(products.begin(), products.end());

        std::vector<std::vector<std::string>> result;
        result.reserve(searchWord.size());

        std::string prefix;
        // 前缀变长只会让候选集合变小，且仍然有序，所以左边界可以单调推进
        auto begin = products.begin();
        for (char c : searchWord)
        {
            prefix.push_back(c);
            // 第一个 >= prefix 的位置，就是"以 prefix 开头"的候选起点
            begin = std::lower_bound(begin, products.end(), prefix);

            std::vector<std::string> cur;
            for (auto it = begin; it != products.end() && cur.size() < 3; ++it)
            {
                // 逐字符比前 prefix.size() 位，不匹配说明这一段已经结束
                // C++ 20: if (it->starts_with(prefix))    // 最直接的接口
                // if (it->rfind(prefix, 0) == 0)    // 从位置 0 找 prefix，找到了就是 0
                if (it->compare(0, prefix.size(), prefix) != 0)  // < 0：子串字典序小于 str，>0就是子串字典序大于传入的比较串
                {
                    break;
                }
                cur.push_back(*it);
            }
            result.push_back(cur);
        }
        return result;
    }
};
// @lc code=end

// 常规的使用前缀树实现的做法
class SolutionTrie {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie trie;
        for (const auto& p : products)
        {
            trie.insert(p);
        }

        std::vector<std::vector<std::string>> result;
        result.reserve(searchWord.size());
        std::string prefix;
        for (char c : searchWord)
        {
            // 每多敲一个字母，就把当前前缀的推荐结果取出来
            prefix.push_back(c);
            result.push_back(trie.suggest(prefix, 3));
        }
        return result;
    }
};
