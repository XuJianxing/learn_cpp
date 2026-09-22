/*
 * @lc app=leetcode.cn id=435 lang=cpp
 *
 * [435] 无重叠区间
 *
 * https://leetcode.cn/problems/non-overlapping-intervals/description/
 *
 * algorithms
 * Medium (53.52%)
 * Likes:    1299
 * Dislikes: 0
 * Total Accepted:    370.2K
 * Total Submissions: 691.1K
 * Testcase Example:  '[[1,2],[2,3],[3,4],[1,3]]'
 *
 * 给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回
 * 需要移除区间的最小数量，使剩余区间互不重叠 。
 * 
 * 注意 只在一点上接触的区间是 不重叠的。例如 [1, 2] 和 [2, 3] 是不重叠的。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: intervals = [[1,2],[2,3],[3,4],[1,3]]
 * 输出: 1
 * 解释: 移除 [1,3] 后，剩下的区间没有重叠。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: intervals = [ [1,2], [1,2], [1,2] ]
 * 输出: 2
 * 解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。
 * 
 * 
 * 示例 3:
 * 
 * 
 * 输入: intervals = [ [1,2], [2,3] ]
 * 输出: 0
 * 解释: 你不需要移除任何区间，因为它们已经是无重叠的了。
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 1 <= intervals.length <= 10^5
 * intervals[i].length == 2
 * -5 * 10^4 <= starti < endi <= 5 * 10^4
 * 
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    /*
    思路：
    1. 移除最少区间，等于保留最多区间
    2. 从左到右，右端点最早结束的区间，就是越小的区间，那就是越需要保留的，因为这样才能保留更多区间
    典型的「贪心选择性质」—— 每一步选结束最早的，绝不会比其他选择更差。
    它是「选课/会议室」类问题的通用模板
    所以可以按右端点排序，选右端点最小且不与已选区间冲突
    */
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 按右端点从小到大排序：优先保留结束早的区间
        std::sort(intervals.begin(), intervals.end(), 
            [](const std::vector<int>& a, const std::vector<int>& b) {
                // 不能写成 <=   等价元素会被判定为"互相小于"，破坏反对称性，
                // introsort 的 __unguarded_partition 里的指针可能直接跑出数组边界
                return a[1] < b[1];
            });

        int remove = 0;
        // rightEnd 记录当前保留下来的最后一个区间的右端点
        int rightEnd = intervals[0][0] - 1;   // 初始化为一个足够小的值

        for (const auto& it : intervals) {
            if (it[0] >= rightEnd) {
                // 不重叠，保留它，更新右端点
                rightEnd = it[1];
            } else {
                // 重叠，必须移除一个：移除当前的（保留结束更早的那个）
                remove++;
            }
        }
        return remove;
    }

    // 另一种等价写法：按左端点排序，冲突时移除右端点更大的那个
    int eraseOverlapIntervals_2(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        int remove = 0, rightEnd = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < rightEnd) {   // 重叠
                remove++;
                rightEnd = min(rightEnd, intervals[i][1]);  // 保留右端点更小的
            } else {
                rightEnd = intervals[i][1];
            }
        }
        return remove;
    }
};
// @lc code=end

