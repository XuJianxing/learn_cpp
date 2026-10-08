/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 *
 * https://leetcode.cn/problems/jump-game/description/
 *
 * algorithms
 * Medium (45.18%)
 * Likes:    3330
 * Dislikes: 0
 * Total Accepted:    1.7M
 * Total Submissions: 3.7M
 * Testcase Example:  '[2,3,1,1,4]'
 *
 * 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 
 * 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [2,3,1,1,4]
 * 输出：true
 * 解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [3,2,1,0,4]
 * 输出：false
 * 解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^4
 * 0 <= nums[i] <= 10^5
 * 
 * 
 */

#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    /*
    核心观察：不需要真的模拟每一步跳到哪，只需要维护一个「可达边界」maxReach。

    从左到右遍历 i，maxReach 表示目前所有 0..i 的位置中，能跳到的最远下标。
    如果 i > maxReach，说明连 i 这个位置都到不了，后面更到不了 → false。
    否则用 i + nums[i] 更新 maxReach。
    一旦 maxReach >= n-1 → true。
    */
     bool canJump(vector<int>& nums) {
        int n = nums.size();
        int maxReach = 0;                       // 当前能到达的最远下标
        for (int i = 0; i < n; ++i) {
            if (i > maxReach) return false;     // 连 i 都到不了，断层了
            maxReach = max(maxReach, i + nums[i]);  // 维护现在能达到的最远位置
            if (maxReach >= n - 1) return true; // 已覆盖终点
        }
        return true;                            // n == 1 时走到这里
    }
};
// @lc code=end

