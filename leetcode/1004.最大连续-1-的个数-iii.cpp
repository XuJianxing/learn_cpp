/*
 * @lc app=leetcode.cn id=1004 lang=cpp
 *
 * [1004] 最大连续1的个数 III
 *
 * https://leetcode.cn/problems/max-consecutive-ones-iii/description/
 *
 * algorithms
 * Medium (62.09%)
 * Likes:    856
 * Dislikes: 0
 * Total Accepted:    246.3K
 * Total Submissions: 396.7K
 * Testcase Example:  '[1,1,1,0,0,0,1,1,1,1,0]\n2'
 *
 * 给定一个二进制数组 nums 和一个整数 k，假设最多可以翻转 k 个 0 ，则返回执行操作后 数组中连续 1 的最大个数 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,1,1,0,0,0,1,1,1,1,0], K = 2
 * 输出：6
 * 解释：[1,1,1,0,0,1,1,1,1,1,1]
 * 粗体数字从 0 翻转到 1，最长的子数组长度为 6。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
 * 输出：10
 * 解释：[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 * 粗体数字从 0 翻转到 1，最长的子数组长度为 10。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * nums[i] 不是 0 就是 1
 * 0 <= k <= nums.length
 * 
 * 思路：
 * 所谓的“翻转0的个数”，也就是在一个窗口内，0的个数不超过k个。
 * 如果超过k个，则需要向右继续滑动，左边移动缩窗，右边继续探测找更大长度
 * 问题一说到大数组中的连续子数组问题，就可以考虑滑动窗口
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:

    /*
    核心代码逻辑：
    right 遍历数组，遇到 0 就 zeroCount++
    当 zeroCount > k，while 循环收缩 left，left 指向的如果是 0 则 zeroCount--
    每次循环末尾，窗口内 0 的个数一定 ≤ k，用 right - left + 1 更新最大值
    */
    int longestOnes(vector<int>& nums, int k) {
        int left = 0;
        int zeroCount = 0;
        int maxLen = 0;

        for (int right = 0; right < nums.size(); ++right) {
            // 新进入窗口的元素如果是 0，计数增加
            if (nums[right] == 0) {
                ++zeroCount;
            }

            // 窗口内 0 的个数超过了 k，收缩左边界
            // 因为 right 每次只移一格，zeroCount 最多 k+1，所以 if 足够
            if (zeroCount > k) {
                if (nums[left] == 0) {
                    --zeroCount;
                }
                ++left;
            }

            // 此时窗口内 0 的个数 ≤ k，更新最大长度
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
// @lc code=end

