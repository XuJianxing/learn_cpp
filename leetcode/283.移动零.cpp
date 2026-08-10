/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 *
 * https://leetcode.cn/problems/move-zeroes/description/
 *
 * algorithms
 * Easy (63.76%)
 * Likes:    2964
 * Dislikes: 0
 * Total Accepted:    2.5M
 * Total Submissions: 3.9M
 * Testcase Example:  '[0,1,0,3,12]'
 *
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 
 * 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [0,1,0,3,12]
 * 输出: [1,3,12,0,0]
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [0]
 * 输出: [0]
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 
 * 1 <= nums.length <= 10^4
 * -2^31 <= nums[i] <= 2^31 - 1
 * 
 * 
 * 
 * 
 * 进阶：你能尽量减少完成的操作次数吗？
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int i = 0, j = 0;
        while (i < n && j < n)
        {
            // 找到第一个0
            while (i < n && nums[i] != 0)
            {
                i++;
            }
            // 从第一个0开始往后找第一个非0
            j = i + 1;
            while (j < n && nums[j] == 0)
            {
                j++;
            }
            if (i >= j) break;
            if (i < n && j < n)
            {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
};
// @lc code=end


int main()
{
    Solution s;
    vector<int> nums{0,1,0,3,12};
    vector<int> nums1{0};
    vector<int> nums2{0, 1};
    vector<int> nums3{1, 0};
    vector<int> nums4{1, 0, 1};
    s.moveZeroes(nums4);
    return 0;
}
