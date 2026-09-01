/*
 * @lc app=leetcode.cn id=547 lang=cpp
 *
 * [547] 省份数量
 *
 * https://leetcode.cn/problems/number-of-provinces/description/
 *
 * algorithms
 * Medium (62.90%)
 * Likes:    1287
 * Dislikes: 0
 * Total Accepted:    384.8K
 * Total Submissions: 611.8K
 * Testcase Example:  '[[1,1,0],[1,1,0],[0,0,1]]'
 *
 * 
 * 
 * 有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c
 * 间接相连。
 * 
 * 省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。
 * 
 * 给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而
 * isConnected[i][j] = 0 表示二者不直接相连。
 * 
 * 返回矩阵中 省份 的数量。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：isConnected = [[1,0,0],[0,1,0],[0,0,1]]
 * 输出：3
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * n == isConnected.length
 * n == isConnected[i].length
 * isConnected[i][j] 为 1 或 0
 * isConnected[i][i] == 1
 * isConnected[i][j] == isConnected[j][i]
 * 
 * 
 * 
 * 
 */

#include <queue>
#include <string>
#include <unordered_set>
using namespace std;

// @lc code=start
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        // std::pair没有提供哈希函数
        // 一开始自己的想法：
        // 对于每个城市，记录这个城市可以去哪些城市，然后对于每个可达城市都继续广度优先遍历并走过去
        // 在走的过程中标记已去过的路径，防止重复走，这样之后，以一个城市为开头的所有可达城市就都走过一遍了
        // 下一轮到下一个城市，如果这个城市还有可以去的城市，说明这个城市是新节点的开始城市，可以增加计数
        std::unordered_set<std::string> visited;
        std::queue<size_t> togo;
        int count = 0;
        for (size_t i = 0; i < isConnected.size(); i++)
        {
            for (size_t j = i; j < isConnected[i].size(); j++)
            {
                if (isConnected[i][j])
                {
                    std::string visit(std::to_string(i) + "," + std::to_string(j));
                    if (!visited.contains(visit))
                    {
                        togo.emplace(j);
                        visited.emplace(visit);
                    }
                }
            }
            if (!togo.empty())
            {
                count++;
            }
            while (!togo.empty())
            {
                auto to = togo.front();
                togo.pop();
                for (size_t k = 0; k < isConnected[to].size(); k++)
                {
                    if (isConnected[to][k])
                    {
                        auto a = std::min(to, k);
                        auto b = std::max(to, k);
                        std::string visit(std::to_string(a) + "," + std::to_string(b));
                        if (!visited.contains(visit))
                        {
                            togo.emplace(k);
                            visited.emplace(visit);
                        }
                    }
                }
            }
        }
        return count;
    }

    // 上面思路是用[字符串标记边]来做连通分量计数，既慢又容易错。
    // 这道题标准做法是用一个 vector<bool> 标记「节点」是否访问过，DFS/BFS 都行：
    // 核心区别：标记的是城市节点，而不是城市之间的边，这样每个连通分量只计数一次，逻辑也清晰很多。
    int findCircleNum_2(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++count;
                queue<int> q;
                q.push(i);
                visited[i] = true;
                while (!q.empty()) {
                    int cur = q.front(); q.pop();
                    for (int j = 0; j < n; ++j) {
                        if (isConnected[cur][j] && !visited[j]) {
                            visited[j] = true;
                            q.push(j);
                        }
                    }
                }
            }
        }
        return count;
    }

};
// @lc code=end

