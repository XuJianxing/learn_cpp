/*
 * @lc app=leetcode.cn id=643 lang=cpp
 *
 * [643] 子数组最大平均数 I
 *
 * https://leetcode.cn/problems/maximum-average-subarray-i/description/
 *
 * algorithms
 * Easy (44.44%)
 * Likes:    451
 * Dislikes: 0
 * Total Accepted:    243.7K
 * Total Submissions: 548.2K
 * Testcase Example:  '[1,12,-5,-6,50,3]\n4'
 *
 * 给你一个由 n 个元素组成的整数数组 nums 和一个整数 k 。
 * 
 * 请你找出平均数最大且 长度为 k 的连续子数组，并输出该最大平均数。
 * 
 * 任何误差小于 10^-5 的答案都将被视为正确答案。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,12,-5,-6,50,3], k = 4
 * 输出：12.75
 * 解释：最大平均数 (12-5-6+50)/4 = 51/4 = 12.75
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [5], k = 1
 * 输出：5.00000
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == nums.length
 * 1 <= k <= n <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        for (size_t i = 0; i < k; i++)
        {
            sum += nums[i];
        }
        int max_sum = sum;
        for (int i = 0; i < static_cast<int>(nums.size()) - k; i++)
        {
            sum = sum - nums[i] + nums[i + k];
            if (sum > max_sum)
            {
                max_sum = sum;
            }
        }
        return static_cast<double>(max_sum) / k;
    }
};
// @lc code=end


int main()
{
    Solution s;
    vector<int> nums1{0,1,1,3,3};
    vector<int> nums2{1,8,6,2,5,4,8,3,7};
    s.findMaxAverage(nums1, 4);
    return 0;
}
