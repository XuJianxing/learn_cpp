/*
 * @lc app=leetcode.cn id=1466 lang=cpp
 *
 * [1466] 重新规划路线
 *
 * https://leetcode.cn/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/description/
 *
 * algorithms
 * Medium (61.27%)
 * Likes:    271
 * Dislikes: 0
 * Total Accepted:    48.4K
 * Total Submissions: 79K
 * Testcase Example:  '6\n[[0,1],[1,3],[2,3],[4,0],[4,5]]'
 *
 * n 座城市，从 0 到 n-1 编号，其间共有 n-1
 * 条路线。因此，要想在两座不同城市之间旅行只有唯一一条路线可供选择（路线网形成一颗树）。去年，交通运输部决定重新规划路线，以改变交通拥堵的状况。
 * 
 * 路线用 connections 表示，其中 connections[i] = [a, b] 表示从城市 a 到 b 的一条有向路线。
 * 
 * 今年，城市 0 将会举办一场大型比赛，很多游客都想前往城市 0 。
 * 
 * 请你帮助重新规划路线方向，使每个城市都可以访问城市 0 。返回需要变更方向的最小路线数。
 * 
 * 题目数据 保证 每个城市在重新规划路线方向后都能到达城市 0 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
 * 输出：3
 * 解释：更改以红色显示的路线的方向，使每个城市都可以到达城市 0 。
 * 
 * 示例 2：
 * 
 * 
 * 
 * 输入：n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
 * 输出：2
 * 解释：更改以红色显示的路线的方向，使每个城市都可以到达城市 0 。
 * 
 * 示例 3：
 * 
 * 输入：n = 3, connections = [[1,0],[2,0]]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= n <= 5 * 10^4
 * connections.length == n-1
 * connections[i].length == 2
 * 0 <= connections[i][0], connections[i][1] <= n-1
 * connections[i][0] != connections[i][1]
 * 
 * 
 */

#include <vector>
#include <queue>
using namespace std;

// @lc code=start
class Solution {
public:
    // 简单思路：每一轮都完整扫一遍 connections 数组，找到“能和当前可达集合相连”的边，改方向或记录新可达城市，然后再扫下一轮。
    // 逻辑正确，但是仍然是在做从0向外逐层BFS，只是用“反复扫描数组”代替了邻接表。
    // 只要保证每条边最终被处理一次、方向都规整为“指向 0 的一侧”，结果就是最小修改数。这个思路没错。但最坏复杂度 O(n²)
    // 极端情况是一条链而且方向全反，这样每一轮只能推一层

    // 优化方式：建立一个无向邻接表，同时记录每条边的原始方向
    // 表的用处是：记录每个节点直接相连的节点，同时记录从当前节点到对应节点的原始输入边的方向
    // g[a] 里存 (b, 1)：表示原始边就是 a→b
    // 所以处理的是节点，而不是边。把每个节点都走过，则处理完成
    // 处理的过程是一个广度优先遍历，从0开始，走0能连接的节点，每走到一个节点，则把该节点能连接的节点加入队列，等待后续走到
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int,int>>> g(n); // {邻接点, 原始方向标记}
        for (auto& e : connections) {
            int a = e[0], b = e[1];
            g[a].push_back({b, 1}); // a -> b，方向朝外（远离0时需要反转）
            g[b].push_back({a, 0}); // b -> a，方向朝内
        }

        int ans = 0;
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, dir] : g[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                ans += dir;        // dir==1 表示原方向 u->v（远离根），需要反转
                q.push(v);
            }
        }
        return ans;
    }
};
// @lc code=end

