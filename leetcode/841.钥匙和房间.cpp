/*
 * @lc app=leetcode.cn id=841 lang=cpp
 *
 * [841] 钥匙和房间
 *
 * https://leetcode.cn/problems/keys-and-rooms/description/
 *
 * algorithms
 * Medium (71.54%)
 * Likes:    436
 * Dislikes: 0
 * Total Accepted:    153.6K
 * Total Submissions: 214.7K
 * Testcase Example:  '[[1],[2],[3],[]]'
 *
 * 有 n 个房间，房间按从 0 到 n - 1 编号。最初，除 0
 * 号房间外的其余所有房间都被锁住。你的目标是进入所有的房间。然而，你不能在没有获得钥匙的时候进入锁住的房间。
 * 
 * 当你进入一个房间，你可能会在里面找到一套 不同的钥匙，每把钥匙上都有对应的房间号，即表示钥匙可以打开的房间。你可以拿上所有钥匙去解锁其他房间。
 * 
 * 给你一个数组 rooms 其中 rooms[i] 是你进入 i 号房间可以获得的钥匙集合。如果能进入 所有 房间返回 true，否则返回
 * false。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：rooms = [[1],[2],[3],[]]
 * 输出：true
 * 解释：
 * 我们从 0 号房间开始，拿到钥匙 1。
 * 之后我们去 1 号房间，拿到钥匙 2。
 * 然后我们去 2 号房间，拿到钥匙 3。
 * 最后我们去了 3 号房间。
 * 由于我们能够进入每个房间，我们返回 true。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：rooms = [[1,3],[3,0,1],[2],[0]]
 * 输出：false
 * 解释：我们不能进入 2 号房间。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == rooms.length
 * 2 <= n <= 1000
 * 0 <= rooms[i].length <= 1000
 * 1 <= sum(rooms[i].length) <= 3000
 * 0 <= rooms[i][j] < n
 * 所有 rooms[i] 的值 互不相同
 * 
 * 
 */

#include <queue>
#include <unordered_set>

using namespace std;

// @lc code=start
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // 直接思路，已达理论最优，但是还可以优化常数项
        std::queue<int> to_go;
        std::unordered_set<int> gone;
        to_go.emplace(0);
        while (!to_go.empty())
        {
            int room = to_go.front();
            to_go.pop();
            for (auto &&i : rooms[room])
            {
                if (!gone.contains(i))
                {
                    to_go.emplace(i);
                }
            }
            gone.emplace(room);
        }
        for (int i = 0; i < static_cast<int>(rooms.size()); i++)
        {
            if (!gone.contains(i))
            {
                return false;
            }
        }
        return true;
    }

    bool canVisitAllRooms_2(vector<vector<int>>& rooms) {
        /*
        可以优化的点（不影响复杂度，但常数更小、更简洁）
        unordered_set<int> → vector<bool>（或 vector<char>） n ≤ 1000，房间编号是连续的整数，用数组访问是 O(1) 且比哈希快、省内存。哈希表在这里完全没必要。

        入队时就标记，而不是出队时才标记 你当前是 gone.emplace(room) 放在 for 循环之后，这会导致同一个房间被重复入队（比如多个房间都持有同一把钥匙）。虽然不会死循环，但会重复处理，浪费常数时间。正确姿势是入队那一刻就标记 visited。

        用计数器代替最后的 for 循环 每访问一个新房间就 count++，最后直接 return count == rooms.size()，省掉一遍遍历。

        static_cast<int> 可省 用 size_t i 循环即可，或直接换计数器法后完全不需要。

        注意 std::unordered_set::contains 是 C++20 特性，如果评测环境是 C++17 会编译不过。
        */
        int n = rooms.size();
        std::vector<bool> visited(n, false);
        std::queue<int> q;
        q.push(0);
        visited[0] = true;          // 入队即标记
        int count = 1;

        while (!q.empty()) {
            int room = q.front(); q.pop();
            for (int next : rooms[room]) {
                if (!visited[next]) {
                    visited[next] = true;  // 入队即标记，避免重复入队
                    q.push(next);
                    ++count;
                }
            }
        }
        return count == n;
    }

};
// @lc code=end

