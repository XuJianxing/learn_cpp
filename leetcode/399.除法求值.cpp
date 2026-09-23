/*
 * @lc app=leetcode.cn id=399 lang=cpp
 *
 * [399] 除法求值
 *
 * https://leetcode.cn/problems/evaluate-division/description/
 *
 * algorithms
 * Medium (59.71%)
 * Likes:    1286
 * Dislikes: 0
 * Total Accepted:    152.6K
 * Total Submissions: 255.4K
 * Testcase Example:  '[["a","b"],["b","c"]]\n' +
  '[2.0,3.0]\n' +
  '[["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]'
 *
 * 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和
 * values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。
 * 
 * 另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj
 * = ? 的结果作为答案。
 * 
 * 返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0
 * 替代这个答案。
 * 
 * 注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
 * 
 * 注意：未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries =
 * [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
 * 输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
 * 解释：
 * 条件：a / b = 2.0, b / c = 3.0
 * 问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
 * 结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
 * 注意：x 是未定义的 => -1.0
 * 
 * 示例 2：
 * 
 * 
 * 输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
 * queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
 * 输出：[3.75000,0.40000,5.00000,0.20000]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：equations = [["a","b"]], values = [0.5], queries =
 * [["a","b"],["b","a"],["a","c"],["x","y"]]
 * 输出：[0.50000,2.00000,-1.00000,-1.00000]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= equations.length <= 20
 * equations[i].length == 2
 * 1 <= Ai.length, Bi.length <= 5
 * values.length == equations.length
 * 0.0 < values[i] <= 20.0
 * 1 <= queries.length <= 20
 * queries[i].length == 2
 * 1 <= Cj.length, Dj.length <= 5
 * Ai, Bi, Cj, Dj 由小写英文字母与数字组成
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
// ============ 解法一：BFS（建图 + 搜索，直观） ============
/*
复杂度
建图：O(E)，E = equations.length（每条建 2 条边）。
每个 query 一次 BFS：最坏遍历全图 O(V + E)，V ≤ 2E ≤ 40。
总计 O(Q · (V + E))，Q ≤ 20，规模极小，完全够用。
*/
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 1. 建图：graph[a][b] 表示 a / b 的值
        unordered_map<string, unordered_map<string, double>> graph;
        for (int i = 0; i < (int)equations.size(); ++i) {
            const string& a = equations[i][0];
            const string& b = equations[i][1];
            double v = values[i];
            graph[a][b] = v;        // a / b = v
            graph[b][a] = 1.0 / v;  // b / a = 1/v
        }

        vector<double> ans;
        ans.reserve(queries.size());

        // 2. 对每个 query 做一次 BFS，边权相乘
        for (auto& q : queries) {
            const string& c = q[0];
            const string& d = q[1];

            if (graph.find(c) == graph.end() || graph.find(d) == graph.end()) {
                ans.push_back(-1.0);
                continue;
            }
            if (c == d) {
                ans.push_back(1.0);
                continue;
            }

            // 1. 防止死循环：图里有环（a→b→a），不标记会无限转圈。
            // 2. 保证「首达即最终值」：题目保证输入无矛盾，所以到达同一节点的所有路径算出的比值必然相同（例如 a→b→c 得到 a/c=6，a→d→e→c 也一定是 6）。
            // 因此第一次到达某个节点时算出的 cur 就是它的唯一正确值，没必要再被第二条路径更新一遍，直接剪掉即可。
            unordered_map<string, bool> visited;
            queue<pair<string, double>> qq;
            // c是代求表达式的分子，所以从它开始走搜索路径
            qq.push({c, 1.0});
            visited[c] = true;

            bool found = false;
            while (!qq.empty()) {
                auto [node, cur] = qq.front();
                qq.pop();

                if (node == d) {
                    ans.push_back(cur);
                    found = true;
                    break;
                }

                // 只根据已给出的equation做查找，而不是新造，而且也无法新造计算等式。
                // 因为一条路径的开头和结尾节点一定要在路径中出现过才能算出来
                for (auto& [nxt, w] : graph[node]) {
                    if (visited[nxt]) continue;
                    visited[nxt] = true;
                    qq.push({nxt, cur * w});
                }
            }
            if (!found) ans.push_back(-1.0); // 走不通（不在同一连通分量）
        }

        return ans;
    }

// ============ 解法二：带权并查集（最优） ============
private:
    unordered_map<string, string> parent;
    unordered_map<string, double> weight; // weight[x] = x / parent[x]

    // 查找根，路径压缩时维护 weight
    string find(const string& x) {
        if (parent[x] != x) {
            string p = parent[x];
            string root = find(p);
            weight[x] *= weight[p]; // 此时 weight[p] 已是 p / root
            parent[x] = root;
        }
        return parent[x];
    }

    // 已知 a / b = v，把 a 所在集合合并到 b 所在集合
    void unite(const string& a, const string& b, double v) {
        string ra = find(a);
        string rb = find(b);
        if (ra == rb) return;

        // weight[a] = a/ra, weight[b] = b/rb
        // 由 a/b = v 推出 ra/rb = v * weight[b] / weight[a]
        parent[ra] = rb;
        weight[ra] = v * weight[b] / weight[a];
    }

public:
    vector<double> calcEquation_2(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 1. 初始化：每个变量自成集合，weight = 1.0
        for (auto& e : equations) {
            for (auto& s : e) {
                if (parent.find(s) == parent.end()) {
                    parent[s] = s;
                    weight[s] = 1.0;
                }
            }
        }

        // 2. 合并所有等式关系
        for (int i = 0; i < (int)equations.size(); ++i) {
            unite(equations[i][0], equations[i][1], values[i]);
        }

        // 3. 回答每个 query
        vector<double> ans;
        for (auto& q : queries) {
            const string& c = q[0];
            const string& d = q[1];

            // 变量未出现
            if (parent.find(c) == parent.end() || parent.find(d) == parent.end()) {
                ans.push_back(-1.0);
                continue;
            }
            // 不在同一集合，无法确定
            if (find(c) != find(d)) {
                ans.push_back(-1.0);
                continue;
            }
            // c/d = (c/root) / (d/root) = weight[c] / weight[d]
            ans.push_back(weight[c] / weight[d]);
        }
        return ans;
    }
};
// @lc code=end

