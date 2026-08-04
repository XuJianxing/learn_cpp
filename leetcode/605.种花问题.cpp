/*
 * @lc app=leetcode.cn id=605 lang=cpp
 *
 * [605] 种花问题
 *
 * https://leetcode.cn/problems/can-place-flowers/description/
 *
 * algorithms
 * Easy (32.30%)
 * Likes:    806
 * Dislikes: 0
 * Total Accepted:    284.9K
 * Total Submissions: 881.9K
 * Testcase Example:  '[1,0,0,0,1]\n1'
 *
 * 假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。
 * 
 * 给你一个整数数组 flowerbed 表示花坛，由若干 0 和 1 组成，其中 0 表示没种植花，1 表示种植了花。另有一个数 n
 * ，能否在不打破种植规则的情况下种入 n 朵花？能则返回 true ，不能则返回 false 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：flowerbed = [1,0,0,0,1], n = 1
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：flowerbed = [1,0,0,0,1], n = 2
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= flowerbed.length <= 2 * 10^4
 * flowerbed[i] 为 0 或 1
 * flowerbed 中不存在相邻的两朵花
 * 0 <= n <= flowerbed.length
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    // 贪心：从左到右，只要当前位置能种就立刻种（最左优先不会让答案变差）
    // 时间 O(len)，空间 O(1)，不修改入参
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (n <= 0) return true;

        const int m = static_cast<int>(flowerbed.size());
        int count = 0;

        for (int i = 0; i < m; ++i)
        {
            if (flowerbed[i] == 1) continue;

            // 核心关键：i == 0 和 i == m - 1 直接把左右边界考虑进了，不用再单独写左右边界位置的判断了。
            // 而且同时又限制了短数组的情况，因为短数组也会因i满足限制而短路判断。很优雅。
            bool leftEmpty  = (i == 0)     || (flowerbed[i - 1] == 0);
            bool rightEmpty = (i == m - 1) || (flowerbed[i + 1] == 0);

            if (leftEmpty && rightEmpty)
            {
                if (++count >= n) return true;   // 够了就提前退出
                // 手动i+1就相当于把数组i位置置1了，跳过不看了
                ++i;                             // 在 i 种下花，i+1 必然不能再种，直接跳过
            }
        }
        return count >= n;
    }
};
// @lc code=end

