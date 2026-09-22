/*
 * @lc app=leetcode.cn id=452 lang=cpp
 *
 * [452] 用最少数量的箭引爆气球
 *
 * https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/description/
 *
 * algorithms
 * Medium (53.67%)
 * Likes:    1190
 * Dislikes: 0
 * Total Accepted:    427.7K
 * Total Submissions: 795.8K
 * Testcase Example:  '[[10,16],[2,8],[1,6],[7,12]]'
 *
 * 有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend]
 * 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。
 * 
 * 一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足
 * xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。
 * 
 * 给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：points = [[10,16],[2,8],[1,6],[7,12]]
 * 输出：2
 * 解释：气球可以用2支箭来爆破:
 * -在x = 6处射出箭，击破气球[2,8]和[1,6]。
 * -在x = 11处发射箭，击破气球[10,16]和[7,12]。
 * 
 * 示例 2：
 * 
 * 
 * 输入：points = [[1,2],[3,4],[5,6],[7,8]]
 * 输出：4
 * 解释：每个气球需要射出一支箭，总共需要4支箭。
 * 
 * 示例 3：
 * 
 * 
 * 输入：points = [[1,2],[2,3],[3,4],[4,5]]
 * 输出：2
 * 解释：气球可以用2支箭来爆破:
 * - 在x = 2处发射箭，击破气球[1,2]和[2,3]。
 * - 在x = 4处射出箭，击破气球[3,4]和[4,5]。
 * 
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 1 <= points.length <= 10^5
 * points[i].length == 2
 * -2^31 <= xstart < xend <= 2^31 - 1
 * 
 * 
 */

#include <vector>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    // 做法一：按右端点排序，直接模拟射箭过程
    // 贪心：第一箭一定射在「右端点最小的区间」的右端点上。
    //       射在这里能顺带引爆尽可能多的气球，且不比射在更左边差（交换论证）。
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        std::sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int arrows = 1;
        int arrowPos = points[0][1];    // 第一箭的位置

        for (int i = 1; i < (int)points.size(); i++) {
            // 注意是 > ：端点相接（xstart == arrowPos）也算被打中
            if (points[i][0] > arrowPos) {
                arrows++;
                arrowPos = points[i][1];    // 补一箭，射在它的右端点
            }
        }
        return arrows;
    }

    // 做法二：按左端点排序，维护当前这组气球的「公共交集」
    // 一组气球能被同一支箭引爆 <=> 它们存在公共点 <=> 交集非空。
    // 按起点排序后，交集左边界恒为当前区间的起点，所以只需跟踪一个 minEnd。
    int findMinArrowShotsByStart(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        std::sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        int arrows = 1;
        int minEnd = points[0][1];      // 当前组公共交集的右边界

        for (int i = 1; i < (int)points.size(); i++) {
            if (points[i][0] <= minEnd) {
                // 有公共点，同一支箭搞定，交集继续缩窄
                minEnd = std::min(minEnd, points[i][1]);
            } else {
                // 交集空了，必须另射一箭，用当前区间另起一组
                arrows++;
                minEnd = points[i][1];
            }
        }
        return arrows;
    }
};
// @lc code=end

