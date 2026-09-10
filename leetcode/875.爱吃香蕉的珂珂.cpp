/*
 * @lc app=leetcode.cn id=875 lang=cpp
 *
 * [875] 爱吃香蕉的珂珂
 *
 * https://leetcode.cn/problems/koko-eating-bananas/description/
 *
 * algorithms
 * Medium (50.51%)
 * Likes:    763
 * Dislikes: 0
 * Total Accepted:    214.4K
 * Total Submissions: 424.2K
 * Testcase Example:  '[3,6,7,11]\n8'
 *
 * 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 h 小时后回来。
 * 
 * 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。如果这堆香蕉少于 k
 * 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  
 * 
 * 珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
 * 
 * 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：piles = [3,6,7,11], h = 8
 * 输出：4
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：piles = [30,11,23,4,20], h = 5
 * 输出：30
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：piles = [30,11,23,4,20], h = 6
 * 输出：23
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= piles.length <= 10^4
 * piles.length <= h <= 10^9
 * 1 <= piles[i] <= 10^9
 * 
 * 
 */

#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// @lc code=start
class Solution {
public:
    // 最开始思路错了，以为答案一定会出现在数组中的某个数值，但是实际上根本不是这样的，
    // 因为k可以是任何值，但一定要取到最小。所以应该直接在最大值和1的范围内二分，找最小值
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1, hi = 0;
        hi = *std::max_element(piles.begin(), piles.end());

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            long long time = 0;
            for (int p : piles) {
                /*
                原始写法其实是：
                    int q = p / mid;
                    int r = p % mid;
                    int result = (r == 0) ? q : q + 1;
                但是为了更简洁，观察到了，其实主要是在处理加上mid之后的区分，那可以直接加mid-1
                因为如果正好整除mid，加了mid-1不影响；如果有余数，哪怕只余1，加了mid-1正好除法结果多+1
                */
                time += (p + mid - 1LL) / mid; // 等价于 ceil(p / mid)，但是返回值是double，没有整型类型
            }
            if (time <= h)
            {
                hi = mid;        // 能吃完，尝试更小速度
            }
            else
            {
                lo = mid + 1;    // 吃不完，需要更快
            }
        }
        return lo;
    }

};
// @lc code=end

int main()
{
    Solution s;
    std::vector<int> piles{3,6,7,11};
    s.minEatingSpeed(piles, 8);
    std::vector<int> piles2{312884470};
    s.minEatingSpeed(piles2, 312884469);
    std::vector<int> piles3{82,37};
    s.minEatingSpeed(piles3, 6);
    std::vector<int> piles4{805306368,805306368,805306368};
    s.minEatingSpeed(piles3, 1000000000);
}
