/*
 * @lc app=leetcode.cn id=334 lang=cpp
 *
 * [334] 递增的三元子序列
 *
 * https://leetcode.cn/problems/increasing-triplet-subsequence/description/
 *
 * algorithms
 * Medium (43.09%)
 * Likes:    932
 * Dislikes: 0
 * Total Accepted:    185.3K
 * Total Submissions: 430K
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * 给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列。
 * 
 * 如果存在这样的三元组下标 (i, j, k) 且满足 i < j < k ，使得 nums[i] < nums[j] < nums[k] ，返回
 * true ；否则，返回 false 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,2,3,4,5]
 * 输出：true
 * 解释：任何 i < j < k 的三元组都满足题意
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [5,4,3,2,1]
 * 输出：false
 * 解释：不存在满足题意的三元组
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [2,1,5,0,4,6]
 * 输出：true
 * 解释：其中一个满足题意的三元组是 (1, 4, 5)，因为 nums[1] == 1 < nums[4] == 4 < nums[5] ==
 * 6
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 5 * 10^5
 * -2^31 <= nums[i] <= 2^31 - 1
 * 
 * 
 * 
 * 
 * 进阶：你能实现时间复杂度为 O(n) ，空间复杂度为 O(1) 的解决方案吗？
 * 
 * 反思：
 * 我为什么没有自己想出来解法，我只想出了暴力解法，是因为我没有把问题转化为更简化的问题。
 * 我只想到了每个数字都比较一遍，但是没想到，只要左边最小值比当前值小，右边最大值比当前值大，那么这个组合就成立了
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:

    // 准备两个数组，一个是每个位置左边的最小值，另一个是每个位置右边的最大值
    // 然后依次比较，看是否存在
    // （或者两个数组存的是包含i位置的左右最小最大值，但是比较的时候用i-1 i i+1比较）
    bool increasingTriplet(vector<int>& nums) {
        auto length = nums.size();
        if (length < 3) return false;
        vector<int> left_min(length);
        vector<int> right_max(length);
        int min = nums[0];
        int max = nums[length - 1];
        left_min[0] = nums[0];
        for (size_t i = 1; i < length; i++)
        {
            left_min[i] = std::min(left_min[i - 1], nums[i - 1]);
        }
        right_max[length - 1] = nums[length - 1];
        for (size_t i = length - 1; i > 0; i--)
        {
            right_max[i - 1] = std::max(right_max[i], nums[i]);
        }
        for (size_t i = 0; i < length - 1; i++)
        {
            if (left_min[i] < nums[i] && nums[i] < right_max[i])
            {
                return true;
            }
        }
        return false;
    }

    // 方法2：贪心
    // 因为问题是判断存在与否，而不是要找出具体某个组合或者所有组合。
    // 因此我们只需要把问题放大，往极端方向考虑，只要左边
};
// @lc code=end


int main()
{
    Solution s;
    vector<int> nums{1,5,0,4,1,3};
    s.increasingTriplet(nums);
    return 0;
}
