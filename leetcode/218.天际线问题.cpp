/*
 * @lc app=leetcode.cn id=218 lang=cpp
 *
 * [218] 天际线问题
 *
 * https://leetcode.cn/problems/the-skyline-problem/description/
 *
 * algorithms
 * Hard (56.01%)
 * Likes:    926
 * Dislikes: 0
 * Total Accepted:    64.1K
 * Total Submissions: 114.5K
 * Testcase Example:  '[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]'
 *
 * 城市的 天际线 是从远处观看该城市中所有建筑物形成的轮廓的外部轮廓。给你所有建筑物的位置和高度，请返回 由这些建筑物形成的 天际线 。
 * 
 * 每个建筑物的几何信息由数组 buildings 表示，其中三元组 buildings[i] = [lefti, righti, heighti]
 * 表示：
 * 
 * 
 * lefti 是第 i 座建筑物左边缘的 x 坐标。
 * righti 是第 i 座建筑物右边缘的 x 坐标。
 * heighti 是第 i 座建筑物的高度。
 * 
 * 
 * 你可以假设所有的建筑都是完美的长方形，在高度为 0 的绝对平坦的表面上。
 * 
 * 天际线 应该表示为由 “关键点” 组成的列表，格式 [[x1,y1],[x2,y2],...] ，并按 x 坐标 进行 排序
 * 。关键点是水平线段的左端点。列表中最后一个点是最右侧建筑物的终点，y 坐标始终为 0
 * ，仅用于标记天际线的终点。此外，任何两个相邻建筑物之间的地面都应被视为天际线轮廓的一部分。
 * 
 * 注意：输出天际线中不得有连续的相同高度的水平线。例如 [...[2 3], [4 5], [7 5], [11 5], [12 7]...]
 * 是不正确的答案；三条高度为 5 的线应该在最终输出中合并为一个：[...[2 3], [4 5], [12 7], ...]
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
 * 输出：[[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
 * 解释：
 * 图 A 显示输入的所有建筑物的位置和高度，
 * 图 B 显示由这些建筑物形成的天际线。图 B 中的红点表示输出列表中的关键点。
 * 
 * 示例 2：
 * 
 * 
 * 输入：buildings = [[0,2,3],[2,5,3]]
 * 输出：[[0,3],[5,0]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= buildings.length <= 10^4
 * 0 <= lefti < righti <= 2^31 - 1
 * 1 <= heighti <= 2^31 - 1
 * buildings 按 lefti 非递减排序
 * 
 * 做法备忘：
 * -- 暴力枚举解法不行，会超时。因为x坐标是在整个int正数范围内的，不能遍历建筑范围内的坐标来找最大值。 --
 * 
 * 有效做法：
 * 1. 只有建筑物进、出时才会产生天际线变化
 * 2. 所以不需要去判断每个x找出最高点，他题目只需要变化的起点就行了，所以只考虑变化的时机
 * 3. 从左到右扫描，每次建筑物进、出的变化时，考虑当前所有建筑的最高点。
 * 也就是维护一个当前扫过的建筑的高度集合，每次产生变化时去查一下最高的高度，如果变了，就把x和对应高度加入result
 */
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        if (buildings.empty()) return {};

        // 1. 拆事件：进入用-h，离开用 +h
        vector<pair<int, int>> events;
        events.reserve(buildings.size() * 2);
        for (const auto& b : buildings) {
            events.emplace_back(b[0], -b[2]);
            events.emplace_back(b[1], b[2]);
        }
        // 2. 按 (x, h) 字典序排：同 x 时进入先于离开，
        //    进入按高度降序，离开按高度升序 —— 保证同一 x 只产生一个关键点
        sort(events.begin(), events.end());

        // 3. 扫描线：multiset 维护当前活跃高度，0 代表地面
        // multiset是用来做：可重复集合 + 取最大 + 删任意一个，其他符合要求的数据结构也可以用
        multiset<int> heights{0};
        vector<vector<int>> result;
        int prev = 0;
        for (const auto& e : events) {
            if (e.second < 0) heights.insert(-e.second);
            else heights.erase(heights.find(e.second)); // 只删一个
            int cur = *heights.rbegin();
            if (cur != prev) {
                result.push_back({e.first, cur});
                prev = cur;
            }
        }
        return result;
    }
};
// @lc code=end

int main()
{
    Solution s;
    vector<vector<int>> buildings = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    // buildings = {{0,2147483647,2147483647}};
    s.getSkyline(buildings);
    return 0;
}
