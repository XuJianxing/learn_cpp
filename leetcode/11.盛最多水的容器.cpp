/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 *
 * https://leetcode.cn/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (61.87%)
 * Likes:    6029
 * Dislikes: 0
 * Total Accepted:    2.3M
 * Total Submissions: 3.7M
 * Testcase Example:  '[1,8,6,2,5,4,8,3,7]'
 *
 * 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
 * 
 * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 * 
 * 返回容器可以储存的最大水量。
 * 
 * 说明：你不能倾斜容器。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：[1,8,6,2,5,4,8,3,7]
 * 输出：49 
 * 解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 * 
 * 示例 2：
 * 
 * 
 * 输入：height = [1,1]
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == height.length
 * 2 <= n <= 10^5
 * 0 <= height[i] <= 10^4
 * 
 * 
 * 思路：
 * 第一性原则：怎么获得最大面积？肯定是左右离得越远的，边界高度越高的，面积越大
 * 从两边到中间，越向里走，高度小的越不能取，因为面积不可能因为高度变低了而增大，而且底长也变小了
 * 所以每次对于左右挡板，舍弃高度最低的挡板，向前移动，然后尝试获取更大面积
 * 
 * 疑问：
 * 为什么线性的步进能保证正确性，能保证不丢失必要的挡板判断？
 * https://leetcode.cn/problems/container-with-most-water/solutions/207215/sheng-zui-duo-shui-de-rong-qi-by-leetcode-solution
 * 
 * 两指针代表容器左右边界，假设高度为x、y，距离为t。不失一般性，假设x <= y
 * 那么假如不移动x，容器面积不可能大于当前面积。因为由最低挡板决定高度。
 * 换言之，不舍弃最低高度挡板，无法尝试获取更高挡板和水
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1;
        int max_area = 0;
        while (i < j)
        {
            int now_area = (j-i) * (std::min(height[i], height[j]));
            max_area = std::max(max_area, now_area);
            if (height[i] < height[j])
            {
                i++;
            }
            else
            {
                j--;
            }
        }
        return max_area;
    }
};
// @lc code=end


int main()
{
    Solution s;
    vector<int> nums1{1,2,3,0,0,0};
    vector<int> nums2{1,8,6,2,5,4,8,3,7};
    s.maxArea(nums2);
    return 0;
}
