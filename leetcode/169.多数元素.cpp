/*
 * @lc app=leetcode.cn id=169 lang=cpp
 *
 * [169] 多数元素
 *
 * https://leetcode.cn/problems/majority-element/description/
 *
 * algorithms
 * Easy (67.33%)
 * Likes:    2735
 * Dislikes: 0
 * Total Accepted:    1.6M
 * Total Submissions: 2.4M
 * Testcase Example:  '[3,2,3]'
 *
 * 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
 * 
 * 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [3,2,3]
 * 输出：3
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [2,2,1,1,1,2,2]
 * 输出：2
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == nums.length
 * 1 <= n <= 5 * 10^4
 * -10^9 <= nums[i] <= 10^9
 * 输入保证数组中一定有一个多数元素。
 * 
 * 
 * 
 * 
 * 进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    // 如果用partition方式实现的话，无法一次就取到第n/2位置的值，所以你就需要循环多次取值直到找到对应位置
    // 这样的话，最坏可能到排序的O(nlogn)。针对本题，因为有大量相同值，partition一次只能归位1个，效率低

    // 直觉：众数票数过半，把所有"众数 vs 非众数"两两抵消，最后站着的只能是它。
    int majorityElement(std::vector<int>& nums) {
        int cand = 0, cnt = 0;
        for (int x : nums) {
            if (cnt == 0) cand = x;          // 票数归零，换人
            cnt += (x == cand) ? 1 : -1;     // 同阵营 +1，不同阵营抵消 -1
        }
        return cand;                          // 题目保证存在，无需二次校验
    }

    // 另外如果只是想"找第 n/2 小"，一行也行：
    // 平均 O(n) 最坏 O(n log n) 只定位第 k 个
    /*
        first   区间起始迭代器
        nth     目标位置——重排后，这个位置放的就是"整个区间排好序后该位置该有的元素"
        last    区间尾后迭代器（不含），即区间是 [first, last)
    注意：
        下标从 0 计：要"第 k 小"就传 begin() + (k - 1)，别写成 begin() + k。
        nth 必须落在 [first, last) 内，nth == last 属于越界，行为未定义。
        与 *nth 相等的元素怎么分布没规定，两边都可能出现（所以二分/去重类场合不能依赖两侧无等值）。
    */
    int majorityElement_2(std::vector<int>& nums) {
        std::nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
        return nums[nums.size() / 2];   // 中位数下标 == 众数
    }
};
// @lc code=end

