/*
 * @lc app=leetcode.cn id=136 lang=cpp
 *
 * [136] 只出现一次的数字
 *
 * https://leetcode.cn/problems/single-number/description/
 *
 * algorithms
 * Easy (76.91%)
 * Likes:    3515
 * Dislikes: 0
 * Total Accepted:    1.5M
 * Total Submissions: 2M
 * Testcase Example:  '[2,2,1]'
 *
 * 给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
 * 
 * 你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。
 * 
 * 
 * 
 * 
 * 
 * 示例 1 ：
 * 
 * 
 * 输入：nums = [2,2,1]
 * 
 * 输出：1
 * 
 * 
 * 示例 2 ：
 * 
 * 
 * 输入：nums = [4,1,2,1,2]
 * 
 * 输出：4
 * 
 * 
 * 示例 3 ：
 * 
 * 
 * 输入：nums = [1]
 * 
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 3 * 10^4
 * -3 * 10^4 <= nums[i] <= 3 * 10^4
 * 除了某个元素只出现一次以外，其余每个元素均出现两次。
 * 
 * 
 * 
 * 
 */

#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    // 最直接做法是使用容器辅助处理数组
    /* 
    异或运算的性质：
    1. 任何数和 0 做异或运算，结果仍然是原来的数
    2. 任何数和其自身做异或运算，结果是 0
    3. 异或运算满足交换律和结合律
     */
    int singleNumber(vector<int>& nums) {
        int single = 0;
        for (int num : nums) {
            single ^= num;
        }
        return single;
    }
};
// @lc code=end

