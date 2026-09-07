/*
 * @lc app=leetcode.cn id=1926 lang=cpp
 *
 * [1926] 迷宫中离入口最近的出口
 *
 * https://leetcode.cn/problems/nearest-exit-from-entrance-in-maze/description/
 *
 * algorithms
 * Medium (45.28%)
 * Likes:    154
 * Dislikes: 0
 * Total Accepted:    50.4K
 * Total Submissions: 111.1K
 * Testcase Example:  '[["+","+",".","+"],[".",".",".","+"],["+","+","+","."]]\n[1,2]'
 *
 * 给你一个 m x n 的迷宫矩阵 maze （下标从 0 开始），矩阵中有空格子（用 '.' 表示）和墙（用 '+' 表示）。同时给你迷宫的入口
 * entrance ，用 entrance = [entrancerow, entrancecol] 表示你一开始所在格子的行和列。
 * 
 * 每一步操作，你可以往 上，下，左 或者 右 移动一个格子。你不能进入墙所在的格子，你也不能离开迷宫。你的目标是找到离 entrance 最近
 * 的出口。出口 的含义是 maze 边界 上的 空格子。entrance 格子 不算 出口。
 * 
 * 请你返回从 entrance 到最近出口的最短路径的 步数 ，如果不存在这样的路径，请你返回 -1 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance
 * = [1,2]
 * 输出：1
 * 解释：总共有 3 个出口，分别位于 (1,0)，(0,2) 和 (2,3) 。
 * 一开始，你在入口格子 (1,2) 处。
 * - 你可以往左移动 2 步到达 (1,0) 。
 * - 你可以往上移动 1 步到达 (0,2) 。
 * 从入口处没法到达 (2,3) 。
 * 所以，最近的出口是 (0,2) ，距离为 1 步。
 * 
 * 
 * 示例 2：
 * 
 * 输入：maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
 * 输出：2
 * 解释：迷宫中只有 1 个出口，在 (1,2) 处。
 * (1,0) 不算出口，因为它是入口格子。
 * 初始时，你在入口与格子 (1,0) 处。
 * - 你可以往右移动 2 步到达 (1,2) 处。
 * 所以，最近的出口为 (1,2) ，距离为 2 步。
 * 
 * 
 * 示例 3：
 * 
 * 输入：maze = [[".","+"]], entrance = [0,0]
 * 输出：-1
 * 解释：这个迷宫中没有出口。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * maze.length == m
 * maze[i].length == n
 * 1 <= m, n <= 100
 * maze[i][j] 要么是 '.' ，要么是 '+' 。
 * entrance.length == 2
 * 0 <= entrancerow < m
 * 0 <= entrancecol < n
 * entrance 一定是空格子。
 * 
 * 
 */

#include <vector>
#include <array>
#include <queue>
using namespace std;

// @lc code=start
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        // BFS找无权图最短路径，因为逐层遍历，第一次遇到出口就是最短步数
        int m = maze.size();
        int n = maze[0].size();

        int start_x = entrance[0];
        int start_y = entrance[1];

        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::queue<std::pair<int, int>> q;
        q.push({start_x, start_y});
        visited[start_x][start_y] = true;

        // 四个方向：下、上、右、左
        const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        int steps = 0;
        // 从初始位置开始，对于每个位置，尝试四个方向找路径
        while (!q.empty()) {
            int size = q.size();
            // 一次处理完这一步数下的所有可能性
            for (int i = 0; i < size; ++i) {
                auto cur = q.front();
                q.pop();
                int x = cur.first;
                int y = cur.second;

                // 是出口：在边界上，且不是入口格子
                bool on_boundary = (x == 0 || y == 0 || x == m - 1 || y == n - 1);
                bool is_entrance = (x == start_x && y == start_y);
                if (on_boundary && !is_entrance) {
                    return steps;
                }

                for (auto& d : dirs) {
                    int nx = x + d[0];
                    int ny = y + d[1];
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if (maze[nx][ny] == '+' || visited[nx][ny]) continue;
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
            ++steps;
        }
        return -1;
    }
};
// @lc code=end

