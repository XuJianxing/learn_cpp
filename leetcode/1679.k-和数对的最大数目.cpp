/*
 * @lc app=leetcode.cn id=1679 lang=cpp
 *
 * [1679] K 和数对的最大数目
 *
 * https://leetcode.cn/problems/max-number-of-k-sum-pairs/description/
 *
 * algorithms
 * Medium (61.09%)
 * Likes:    128
 * Dislikes: 0
 * Total Accepted:    68K
 * Total Submissions: 111.2K
 * Testcase Example:  '[1,2,3,4]\n5'
 *
 * 给你一个整数数组 nums 和一个整数 k 。
 * 
 * 每一步操作中，你需要从数组中选出和为 k 的两个整数，并将它们移出数组。
 * 
 * 返回你可以对数组执行的最大操作数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,2,3,4], k = 5
 * 输出：2
 * 解释：开始时 nums = [1,2,3,4]：
 * - 移出 1 和 4 ，之后 nums = [2,3]
 * - 移出 2 和 3 ，之后 nums = []
 * 不再有和为 5 的数对，因此最多执行 2 次操作。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [3,1,3,4,3], k = 6
 * 输出：1
 * 解释：开始时 nums = [3,1,3,4,3]：
 * - 移出前两个 3 ，之后nums = [1,4,3]
 * 不再有和为 6 的数对，因此最多执行 1 次操作。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= 10^9
 * 
 * 
 */

#include <vector>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:

    // 先排序然后双指针互相递进。复杂度O(nlogn)
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size() - 1;
        int result = 0;
        while (i < j)
        {
            int sum = nums[i] + nums[j];
            if (sum == k)
            {
                result++;
                i++;
                j--;
            }
            else if (sum < k)
            {
                i++;
            }
            else
            {
                j--;
            }
        }
        return result;
    }

    // 还有一种方法是用哈希表，扫描一遍数组，记录每个数字出现次数。
    // 然后再遍历一遍数组，在哈希表中查找有没有满足和为k的数字，有就对应出现次数-1，没有就下一个
};
// @lc code=end


int main()
{
    Solution s;
    vector<int> nums1{3,1,3,4,3};
    vector<int> nums2{1,2,3,4};
    s.maxOperations(nums1, 6);
    return 0;
}
