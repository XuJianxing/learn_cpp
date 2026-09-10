/*
 * @lc app=leetcode.cn id=2300 lang=cpp
 *
 * [2300] 咒语和药水的成功对数
 *
 * https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/description/
 *
 * algorithms
 * Medium (50.08%)
 * Likes:    210
 * Dislikes: 0
 * Total Accepted:    104.3K
 * Total Submissions: 208K
 * Testcase Example:  '[5,1,3]\n[1,2,3,4,5]\n7'
 *
 * 给你两个正整数数组 spells 和 potions ，长度分别为 n 和 m ，其中 spells[i] 表示第 i
 * 个咒语的能量强度，potions[j] 表示第 j 瓶药水的能量强度。
 * 
 * 同时给你一个整数 success 。一个咒语和药水的能量强度 相乘 如果 大于等于 success ，那么它们视为一对 成功 的组合。
 * 
 * 请你返回一个长度为 n 的整数数组 pairs，其中 pairs[i] 是能跟第 i 个咒语成功组合的 药水 数目。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：spells = [5,1,3], potions = [1,2,3,4,5], success = 7
 * 输出：[4,0,3]
 * 解释：
 * - 第 0 个咒语：5 * [1,2,3,4,5] = [5,10,15,20,25] 。总共 4 个成功组合。
 * - 第 1 个咒语：1 * [1,2,3,4,5] = [1,2,3,4,5] 。总共 0 个成功组合。
 * - 第 2 个咒语：3 * [1,2,3,4,5] = [3,6,9,12,15] 。总共 3 个成功组合。
 * 所以返回 [4,0,3] 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：spells = [3,1,2], potions = [8,5,8], success = 16
 * 输出：[2,0,2]
 * 解释：
 * - 第 0 个咒语：3 * [8,5,8] = [24,15,24] 。总共 2 个成功组合。
 * - 第 1 个咒语：1 * [8,5,8] = [8,5,8] 。总共 0 个成功组合。
 * - 第 2 个咒语：2 * [8,5,8] = [16,10,16] 。总共 2 个成功组合。
 * 所以返回 [2,0,2] 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == spells.length
 * m == potions.length
 * 1 <= n, m <= 10^5
 * 1 <= spells[i], potions[i] <= 10^5
 * 1 <= success <= 10^10
 * 
 * 
 */

#include <vector>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        // 思路：先排序，O(nlogn)，然后在排序后的potions里二分查找，找到第一个大于等于目标的位置，然后记录个数
        std::vector<int> result(spells.size());
        std::sort(potions.begin(), potions.end());
        int m = potions.size();
        // 标准的「找第一个 >= 目标」二分写法
        for (size_t i = 0; i < spells.size(); i++)
        {
            int left = 0, right = m - 1;  // left right要用int，防止0-1溢出
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (1LL * spells[i] * potions[mid] >= success)
                {
                    right = mid - 1;      // 满足，往左找更小的
                }
                else
                {
                    left = mid + 1;       // 不满足，往右找
                }
            }
            // 二分法找Lower bound的语义：循环退出时，left就是边界
            result[i] = m - left;  // left 就是第一个满足条件的位置
        }
        return result;
    }
    /*
    如果用Lower bound函数，对每个 spell，要找第一个满足 spell * potion >= success 的药水，等价于找第一个满足：
    potion >= ceil(success / spell)
    所以只需要算出一个整数阈值，再用 lower_bound 找第一个 >= 阈值 的位置即可。
    阈值要向上取整，不能用 success / spell（整除是向下取整，会漏边界），要用：
    long long threshold = (success + spell - 1) / spell;
     */
    vector<int> successfulPairs_2(vector<int>& spells, vector<int>& potions, long long success) {
        std::sort(potions.begin(), potions.end());
        int m = potions.size();
        std::vector<int> result(spells.size());

        for (int i = 0; i < (int)spells.size(); i++) {
            // 第一个满足 spell * potion >= success 的阈值
            long long threshold = (success + spells[i] - 1) / spells[i];
            // 找第一个 >= threshold 的位置
            auto it = std::lower_bound(potions.begin(), potions.end(), threshold);
            // it 到末尾的距离 = 满足条件的药水个数
            result[i] = potions.end() - it;
        }
        return result;
    }
};
// @lc code=end

/*
核心原因
1. 脑子里没有"lower_bound"这个概念，只有"二分"这个抽象词

你想到的是"用二分查找找位置"，然后现场去推边界。但真正熟练的人脑子里装的是具体套路：

二分本质就两种：找第一个满足条件的（lower_bound）、找最后一个满足条件的（upper_bound）。其余都是这两种的变形。

你写出来的是一堆特判（==、<、>、left == right、去重 while），本质上是边写边试，而不是套模板。

2. 被"等于 success"这个特殊情况带偏了

你的思路是"相乘等于 success 就算成功，所以要单独处理 multi == success"，于是拆成了三个分支，还为了处理重复值加了个 while (potions[mid] == potions[mid-1]) mid-- 去重。

但实际上，题目要的是 >= success。== 只是 >= 的一个子集，根本不需要单独处理。当你把判断条件统一成 multi >= success 时，==、去重这些分支全都自动消失了。

3. 对"循环不变量"不清晰

标准二分靠一个铁律兜底：

循环结束后，left 指向的就是答案（第一个满足条件的位置）。

所以它敢让循环自然退出，因为结果永远有保证。

你则是靠 left == right 的 break 来兜底，说明你对"退出时状态是什么"没想透。这才会漏掉 right 跳到 left - 1 直接退出、结果没赋值的情况。
*/

int main()
{
    Solution s;
    std::vector<int> spells{9,39};
    std::vector<int> potions{35,40,22,37,29,22};
    s.successfulPairs(spells, potions, 320);
}
