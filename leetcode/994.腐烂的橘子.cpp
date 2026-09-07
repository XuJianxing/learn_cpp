/*
 * @lc app=leetcode.cn id=994 lang=cpp
 *
 * [994] 腐烂的橘子
 *
 * https://leetcode.cn/problems/rotting-oranges/description/
 *
 * algorithms
 * Medium (55.66%)
 * Likes:    1200
 * Dislikes: 0
 * Total Accepted:    515.4K
 * Total Submissions: 925.5K
 * Testcase Example:  '[[2,1,1],[1,1,0],[0,1,1]]'
 *
 * 在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：
 * 
 * 
 * 值 0 代表空单元格；
 * 值 1 代表新鲜橘子；
 * 值 2 代表腐烂的橘子。
 * 
 * 
 * 每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。
 * 
 * 返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
 * 输出：4
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
 * 输出：-1
 * 解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：grid = [[0,2]]
 * 输出：0
 * 解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 10
 * grid[i][j] 仅为 0、1 或 2
 * 
 * 
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

// @lc code=start
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        /*
        核心思路：多源 BFS（广度优先搜索）：初始所有烂橘子一起入队，等价于多个起点同时向外扩散。
        核心问题「新烂的橘子又马上扩散」的解法就一句话：
        每轮先记录 q.size()，只处理这一轮开始前就在队列里的橘子；新烂的橘子虽然也压入队列，但会在下一轮才被处理。
        */

        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;

        // 初始状态：所有腐烂橘子入队，统计新鲜橘子数量
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    ++fresh;
                }
            }
        }

        // 一开始就没有新鲜橘子，0 分钟即可
        if (fresh == 0) return 0;

        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int minutes = 0;

        while (!q.empty()) {
            int sz = q.size();      // 关键：固定本层（本分钟）腐烂橘子的数量
            bool rotted = false;    // 本分钟是否真的烂了橘子

            for (int i = 0; i < sz; ++i) {
                auto [x, y] = q.front();
                q.pop();

                for (auto& d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;
                        --fresh;
                        q.push({nx, ny});   // 新烂的橘子压入队尾，下一轮才处理
                        rotted = true;
                    }
                }
            }

            // 关键：如果现在是最后一轮，烂橘子依然会入队，但是已经没有橘子可烂了
            // 你无法提前知道没有橘子可烂了，所以最后一轮依然要跑，所以要记录这一轮是否真的烂了橘子
            if (rotted) ++minutes;
        }

        return fresh == 0 ? minutes : -1;
    }
};
// @lc code=end

