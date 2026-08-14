/*
 * @lc app=leetcode.cn id=933 lang=cpp
 *
 * [933] 最近的请求次数
 *
 * https://leetcode.cn/problems/number-of-recent-calls/description/
 *
 * algorithms
 * Easy (78.01%)
 * Likes:    291
 * Dislikes: 0
 * Total Accepted:    159.6K
 * Total Submissions: 204.6K
 * Testcase Example:  '["RecentCounter","ping","ping","ping","ping"]\n[[],[1],[100],[3001],[3002]]'
 *
 * 写一个 RecentCounter 类来计算特定时间范围内最近的请求。
 * 
 * 请你实现 RecentCounter 类：
 * 
 * 
 * RecentCounter() 初始化计数器，请求数为 0 。
 * int ping(int t) 在时间 t 添加一个新请求，其中 t 表示以毫秒为单位的某个时间，并返回过去 3000
 * 毫秒内发生的所有请求数（包括新请求）。确切地说，返回在 [t-3000, t] 内发生的请求数。
 * 
 * 
 * 保证 每次对 ping 的调用都使用比之前更大的 t 值。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：
 * ["RecentCounter", "ping", "ping", "ping", "ping"]
 * [[], [1], [100], [3001], [3002]]
 * 输出：
 * [null, 1, 2, 3, 3]
 * 
 * 解释：
 * RecentCounter recentCounter = new RecentCounter();
 * recentCounter.ping(1);     // requests = [1]，范围是 [-2999,1]，返回 1
 * recentCounter.ping(100);   // requests = [1, 100]，范围是 [-2900,100]，返回 2
 * recentCounter.ping(3001);  // requests = [1, 100, 3001]，范围是 [1,3001]，返回 3
 * recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002]，范围是
 * [2,3002]，返回 3
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= t <= 10^9
 * 保证每次对 ping 调用所使用的 t 值都 严格递增
 * 至多调用 ping 方法 10^4 次
 * 
 * 
 */

#include <vector>
#include <queue>

// @lc code=start
class RecentCounter {
public:
    RecentCounter() {
        pings.clear();
    }
    
    // lower_bound的手动写法：
    int ping(int t) {
        pings.push_back(t);
        int left = 0, right = pings.size();
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (pings[mid] < t - 3000)
                left = mid + 1;                // a[mid] 一定不是答案，排除
            else
                right = mid;                   // a[mid] 可能是答案，不能排除！
        }
        return pings.size() - left;            // 退出时 left == right，恰好是第一个 >= target 的下标
    }

    // 更好的写法：
    // 使用队列，并且每进入一个数，就已经可以处理当前队列了，因为现在的窗口期是已经固定的3000ms
    // 所以每次进入一个数，都可以去除掉前面已经不满足条件的数，这样队列内本身都是满足条件的数，不用再查找了
    int ping2(int t) {
        q.push(t);
        while (q.front() < t - 3000) q.pop();
        return q.size();
    }

    // 二分法可以使用库函数。。：
    int ping3(int t) {
        pings.push_back(t);
        auto it = std::lower_bound(pings.begin(), pings.end(), t - 3000);
        return pings.end() - it;
    }

private:
    std::vector<int> pings;
    std::queue<int> q;
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
// @lc code=end


int main()
{
    RecentCounter s;
    int res = s.ping(431);
    res = s.ping(837);
    res = s.ping(3620);
    res = s.ping(3837);
    return 0;
}
