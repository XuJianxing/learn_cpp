/*
 * @lc app=leetcode.cn id=135 lang=cpp
 *
 * [135] 分发糖果
 *
 * https://leetcode.cn/problems/candy/description/
 *
 * algorithms
 * Hard (48.77%)
 * Likes:    1812
 * Dislikes: 0
 * Total Accepted:    509.9K
 * Total Submissions: 1M
 * Testcase Example:  '[1,0,2]'
 *
 * n 个孩子站成一排。
 * 
 * 给你一个整数数组 ratings 表示每个孩子的评分。
 * 
 * 你需要按照以下要求，给这些孩子分发糖果：
 * 
 * 
 * 每个孩子 至少 分配到 1 个糖果。
 * 相邻两个孩子中，评分 更高 的那个会获得更多的糖果。
 * 
 * 
 * 请你给每个孩子分发糖果，计算并返回需要准备的 最少 糖果数目。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：ratings = [1,0,2]
 * 输出：5
 * 解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：ratings = [1,2,2]
 * 输出：4
 * 解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
 * ⁠    第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n == ratings.length <= 5 * 10^4
 * 0 <= ratings[i] <= 5 * 10^4
 * 
 * 
 */

#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    /*
    一个孩子同时被左邻居和右邻居约束，两个方向各扫一遍，然后逐点取 max：
        left[i]：只考虑"我比左边高"这一条链
        right[i]：只考虑"我比右边高"这一条链
        candy[i] = max(left[i], right[i])
    */
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        // left[i]: 只考虑「从左往右」的约束（ratings[i] > ratings[i-1] 时 left[i] > left[i-1]）
        // right[i]: 只考虑「从右往左」的约束（ratings[i] > ratings[i+1] 时 right[i] > right[i+1]）
        // 两个约束互不冲突，取 max 即同时满足，且是逐点最小值 => 总数最小

        // 第一遍是结算右边依赖左边的那类（升序对）
        // 注意是if，也就是不满足这个顺序的先不处理
        std::vector<int> left(n, 1);
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1])
                left[i] = left[i - 1] + 1;
        }

        // 第二遍是处理左边依赖右边的那些
        std::vector<int> right(n, 1);
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1])
                right[i] = right[i + 1] + 1;
        }

        long long ans = 0;  // n=5e4 全单调时约为 1.25e9，用 long long 更稳妥
        for (int i = 0; i < n; ++i)
            ans += std::max(left[i], right[i]);
        return (int)ans;
    }

    // 进阶：O(1) 空间
    // 把数组看成交替的升段/降段，up / down 记录当前段长度，peak 记录峰值。
    // 降段长度超过升段时，峰值会被"抬高"（否则峰值左侧的约束不满足）：
    int candy_O1(vector<int>& r) {
        int n = r.size(), up = 0, down = 0, peak = 0;
        long long ans = 1;
        for (int i = 1; i < n; ++i) {
            if (r[i] > r[i - 1]) {
                up++;
                down = 0;
                peak = up;
                ans += 1 + up;
            }
            else if (r[i] == r[i - 1]) {
                up = down = peak = 0;
                ans += 1;
            }
            else {
                down++;
                up = 0;
                ans += 1 + down + (down >= peak ? 1 : 0);
            }
        }
        return (int)ans;
    }

    // 方法二：O(1) 额外空间
    // 核心洞察：
    // 糖果数组长得像连绵的山，每座山 = 一个升段 + 一个降段，段内是等差数列，用求和公式直接算，不用存数组
    int candyO1(vector<int>& r) {
        int n = r.size();
        long long ans = n;          // 每人保底 1 颗
        int i = 1;
        while (i < n) {
            if (r[i] == r[i - 1]) {   // 相等处断开
                ++i;
                continue;
            }
            int up = 0;
            while (i < n && r[i] > r[i - 1]) {   // 爬升
                ++up;
                ans += up;
                ++i;
            }
            int down = 0;
            while (i < n && r[i] < r[i - 1]) { // 下滑
                ++down;
                ans += down;
                ++i;
            }
            ans -= std::min(up, down);   // 峰顶被两边重复计算的部分
        }
        return (int)ans;
    }

};
// @lc code=end

