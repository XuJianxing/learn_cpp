/*
 * @lc app=leetcode.cn id=238 lang=cpp
 *
 * [238] 除了自身以外数组的乘积
 *
 * https://leetcode.cn/problems/product-of-array-except-self/description/
 *
 * algorithms
 * Medium (77.72%)
 * Likes:    2286
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 1.4M
 * Testcase Example:  '[1,2,3,4]'
 *
 * 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。
 * 
 * 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
 * 
 * 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [1,2,3,4]
 * 输出: [24,12,8,6]
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [-1,1,0,-3,3]
 * 输出: [0,0,9,0,0]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= nums.length <= 10^5
 * -30 <= nums[i] <= 30
 * 输入 保证 数组 answer[i] 在  32 位 整数范围内
 * 
 * 
 * 
 * 
 * 进阶：你可以在 O(1) 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组 不被视为 额外空间。）
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    // 双指针左右各遍历一遍，中间乘积结果记录到answer上。具体没看懂原理
    vector<int> productExceptSelf(vector<int>& nums) {
        std::vector<int> answer(nums.size(), 1);
        int left = 0, right = nums.size() - 1;
        int lp = 1, rp = 1;
        while (right >= 0 && left < nums.size()) {
            answer[right] *= rp;
            answer[left] *= lp;
            lp *= nums[left++];
            rp *= nums[right--];
        }
        return answer;
    }

    // 直观的做法：左右各遍历一遍，将每个位置的到这个位置为止的
    // 左边的乘积和右边的乘积都记录到对应数组的对应位置。
    // 最后统一过一遍每个位置算一下左边和右边的乘积
    vector<int> productExceptSelf2(vector<int>& nums) {
        std::vector<int> left(nums.size(), 1);
        std::vector<int> right(nums.size(), 1);
        std::vector<int> result(nums.size());
        for (size_t i = 1; i < nums.size(); i++)
        {
            left[i] = left[i - 1] * nums[i - 1];
        }
        for (int i = nums.size() - 1; i > 0; i--)
        {
            right[i - 1] = right[i] * nums[i];
        }
        for (size_t i = 0; i < nums.size(); i++)
        {
            result[i] = left[i] * right[i];
        }
        return result;
    }

};
// @lc code=end


int main()
{
    Solution s;
    vector<int> nums{1,2,3,4};
    s.productExceptSelf2(nums);
    return 0;
}
