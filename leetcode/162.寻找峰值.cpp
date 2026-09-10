/*
 * @lc app=leetcode.cn id=162 lang=cpp
 *
 * [162] 寻找峰值
 *
 * https://leetcode.cn/problems/find-peak-element/description/
 *
 * algorithms
 * Medium (49.95%)
 * Likes:    1523
 * Dislikes: 0
 * Total Accepted:    563.8K
 * Total Submissions: 1.1M
 * Testcase Example:  '[1,2,3,1]'
 *
 * 峰值元素是指其值严格大于左右相邻值的元素。
 * 
 * 给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
 * 
 * 你可以假设 nums[-1] = nums[n] = -∞ 。
 * 
 * 你必须实现时间复杂度为 O(log n) 的算法来解决此问题。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,2,3,1]
 * 输出：2
 * 解释：3 是峰值元素，你的函数应该返回其索引 2。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,1,3,5,6,4]
 * 输出：1 或 5 
 * 解释：你的函数可以返回索引 1，其峰值元素为 2；
 * 或者返回索引 5， 其峰值元素为 6。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 1000
 * -2^31 <= nums[i] <= 2^31 - 1
 * 对于所有有效的 i 都有 nums[i] != nums[i + 1]
 * 
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
/*
二分查找中，只要坚持 left < right 作为循环条件，mid 就始终落在 [left, right-1] 区间内（不可能等于 right）。
因此访问 nums[mid + 1] 时，下标最多到 right，而 right 本身是合法下标，所以安全。

唯一要避免的错误：不要写成 while (left <= right)。那样当 left == right 时，mid == right，mid + 1 就会越界。
所以本题循环条件必须是 < 而不是 <=，这也是我们选择 left < right 的原因之一。
*/
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        // 二分查找：区间内一定存在峰值
        while (left < right) {
            int mid = left + (right - left) / 2;
            // 当前在上升坡，峰值一定在右边
            if (nums[mid] < nums[mid + 1]) {
                left = mid + 1;
            } else {
                // 当前在下降坡，峰值在左边（含 mid）
                right = mid;
            }
        }
        // 从左右逼近，二分使得O(logn)，逼近到波峰，就是峰值
        return left; // left == right 即为峰值索引
    }
};
// @lc code=end
