/*
 * @lc app=leetcode.cn id=1657 lang=cpp
 *
 * [1657] 确定两个字符串是否接近
 *
 * https://leetcode.cn/problems/determine-if-two-strings-are-close/description/
 *
 * algorithms
 * Medium (53.83%)
 * Likes:    180
 * Dislikes: 0
 * Total Accepted:    61.5K
 * Total Submissions: 114.2K
 * Testcase Example:  '"abc"\n"bca"'
 *
 * 如果可以使用以下操作从一个字符串得到另一个字符串，则认为两个字符串 接近 ：
 * 
 * 
 * 操作 1：交换任意两个 现有 字符。
 * 
 * 
 * 例如，abcde -> aecdb
 * 
 * 
 * 操作 2：将一个 现有 字符的每次出现转换为另一个 现有 字符，并对另一个字符执行相同的操作。
 * 
 * 例如，aacabb -> bbcbaa（所有 a 转化为 b ，而所有的 b 转换为 a ）
 * 
 * 
 * 
 * 
 * 你可以根据需要对任意一个字符串多次使用这两种操作。
 * 
 * 给你两个字符串，word1 和 word2 。如果 word1 和 word2 接近 ，就返回 true ；否则，返回 false 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：word1 = "abc", word2 = "bca"
 * 输出：true
 * 解释：2 次操作从 word1 获得 word2 。
 * 执行操作 1："abc" -> "acb"
 * 执行操作 1："acb" -> "bca"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：word1 = "a", word2 = "aa"
 * 输出：false
 * 解释：不管执行多少次操作，都无法从 word1 得到 word2 ，反之亦然。
 * 
 * 示例 3：
 * 
 * 
 * 输入：word1 = "cabbba", word2 = "abbccc"
 * 输出：true
 * 解释：3 次操作从 word1 获得 word2 。
 * 执行操作 1："cabbba" -> "caabbb"
 * 执行操作 2："caabbb" -> "baaccc"
 * 执行操作 2："baaccc" -> "abbccc"
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= word1.length, word2.length <= 10^5
 * word1 和 word2 仅包含小写英文字母
 * 
 * 核心思路：
 * 操作 1 让你可以任意重排（忽略顺序），
 * 操作 2 让你可以任意交换频率（频率多重集合不变，字符集合不变），
 * 所以最终只比较字符集合和频率多重集合即可。
 */

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:

    // 用数组做成字符字典，检查2点：
    // 1. 字符集合相同（都包含相同字符）；2. 字符出现的频率在排序后相同
    bool closeStrings(string word1, string word2) {
        vector<int> cnt1(26, 0), cnt2(26, 0);
        for (char c : word1) cnt1[c - 'a']++;
        for (char c : word2) cnt2[c - 'a']++;

        // ① 字符集合必须相同（不能创造新字符）
        for (int i = 0; i < 26; i++) {
            if ((cnt1[i] == 0) != (cnt2[i] == 0)) return false;
        }

        // ② 频率的多重集合必须相同（操作 2 只能交换频率）
        sort(cnt1.begin(), cnt1.end());
        sort(cnt2.begin(), cnt2.end());
        return cnt1 == cnt2;
    }
};
// @lc code=end


int main()
{
    Solution s;
    s.closeStrings("cabbba", "abbccc");
    return 0;
}
