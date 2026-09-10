/*
 * @lc app=leetcode.cn id=2462 lang=cpp
 *
 * [2462] 雇佣 K 位工人的总代价
 *
 * https://leetcode.cn/problems/total-cost-to-hire-k-workers/description/
 *
 * algorithms
 * Medium (44.61%)
 * Likes:    133
 * Dislikes: 0
 * Total Accepted:    33.9K
 * Total Submissions: 75.9K
 * Testcase Example:  '[17,12,10,2,7,2,11,20,8]\n3\n4'
 *
 * 给你一个下标从 0 开始的整数数组 costs ，其中 costs[i] 是雇佣第 i 位工人的代价。
 * 
 * 同时给你两个整数 k 和 candidates 。我们想根据以下规则恰好雇佣 k 位工人：
 * 
 * 
 * 总共进行 k 轮雇佣，且每一轮恰好雇佣一位工人。
 * 在每一轮雇佣中，从最前面 candidates 和最后面 candidates
 * 人中选出代价最小的一位工人，如果有多位代价相同且最小的工人，选择下标更小的一位工人。
 * 
 * 比方说，costs = [3,2,7,7,1,2] 且 candidates = 2 ，第一轮雇佣中，我们选择第 4 位工人，因为他的代价最小
 * [3,2,7,7,1,2] 。
 * 第二轮雇佣，我们选择第 1 位工人，因为他们的代价与第 4 位工人一样都是最小代价，而且下标更小，[3,2,7,7,2]
 * 。注意每一轮雇佣后，剩余工人的下标可能会发生变化。
 * 
 * 
 * 如果剩余员工数目不足 candidates 人，那么下一轮雇佣他们中代价最小的一人，如果有多位代价相同且最小的工人，选择下标更小的一位工人。
 * 一位工人只能被选择一次。
 * 
 * 
 * 返回雇佣恰好 k 位工人的总代价。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
 * 输出：11
 * 解释：我们总共雇佣 3 位工人。总代价一开始为 0 。
 * - 第一轮雇佣，我们从 [17,12,10,2,7,2,11,20,8] 中选择。最小代价是 2 ，有两位工人，我们选择下标更小的一位工人，即第 3
 * 位工人。总代价是 0 + 2 = 2 。
 * - 第二轮雇佣，我们从 [17,12,10,7,2,11,20,8] 中选择。最小代价是 2 ，下标为 4 ，总代价是 2 + 2 = 4 。
 * - 第三轮雇佣，我们从 [17,12,10,7,11,20,8] 中选择，最小代价是 7 ，下标为 3 ，总代价是 4 + 7 = 11 。注意下标为
 * 3 的工人同时在最前面和最后面 4 位工人中。
 * 总雇佣代价是 11 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：costs = [1,2,4,1], k = 3, candidates = 3
 * 输出：4
 * 解释：我们总共雇佣 3 位工人。总代价一开始为 0 。
 * - 第一轮雇佣，我们从 [1,2,4,1] 中选择。最小代价为 1 ，有两位工人，我们选择下标更小的一位工人，即第 0 位工人，总代价是 0 + 1 =
 * 1 。注意，下标为 1 和 2 的工人同时在最前面和最后面 3 位工人中。
 * - 第二轮雇佣，我们从 [2,4,1] 中选择。最小代价为 1 ，下标为 2 ，总代价是 1 + 1 = 2 。
 * - 第三轮雇佣，少于 3 位工人，我们从剩余工人 [2,4] 中选择。最小代价是 2 ，下标为 0 。总代价为 2 + 2 = 4 。
 * 总雇佣代价是 4 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= costs.length <= 10^5 
 * 1 <= costs[i] <= 10^5
 * 1 <= k, candidates <= costs.length
 * 
 * 
 */

#include <vector>
#include <algorithm>   // std::ranges::nth_element
#include <functional>  // std::greater
#include <numeric>     // std::reduce
#include <queue>       // std::priority_queue
#include <ranges>      // std::views

using namespace std;

// @lc code=start
class Solution {
public:
    // 一个需要理解的关键点：如果前后candidates没有剩余可纳入工人，说明不需要区分前后两个小根堆了，只需要一个堆就行了
    // 两个做法，1. 一个堆，维护前后双指针，统一加入一个堆中，但是堆中数据需要捆绑元素本身和下标为二元组才行。每次弹出一个并维护堆和指针
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int n = static_cast<int>(costs.size());
        // 堆里存 pair<代价, 下标>：pair 默认先比 first 再比 second，
        // 这样代价相同时下标更小的会优先被弹出。
        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> left_heap, right_heap;

        // left / right 分别指向"下一个待加入左/右堆"的下标
        int left = 0, right = n - 1;

        // 左侧最多放 candidates 个
        while (left <= right && left < candidates) {
            left_heap.emplace(costs[left], left);
            ++left;
        }
        // 右侧最多放 candidates 个（从右往左数）
        while (right >= left && n - 1 - right < candidates) {
            right_heap.emplace(costs[right], right);
            --right;
        }

        long long result = 0;
        for (int i = 0; i < k; ++i) {
            // 左堆代价 <= 右堆代价时取左（代价相同时左下标更小，符合题意）
            if (!left_heap.empty() && (right_heap.empty() || left_heap.top() <= right_heap.top())) {
                result += left_heap.top().first;
                left_heap.pop();
                if (left <= right) {           // 还有未入堆的工人
                    left_heap.emplace(costs[left], left);
                    ++left;
                }
            } else {
                result += right_heap.top().first;
                right_heap.pop();
                if (left <= right) {
                    right_heap.emplace(costs[right], right);
                    --right;
                }
            }
        }
        return result;
    }

    // 2. 前后两个堆，双指针
    // 选完以后从数组移除工人？不需要考虑，因为每次移动都把候选者加入堆中，只需要考虑堆中符合要求的人
    long long totalCost_21(vector<int>& costs, int k, int candidates) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> left_heap, right_heap;
        long long result = 0;
        int left = candidates - 1;
        int right = std::max(static_cast<int>(costs.size()) - candidates, candidates);
        for (int i = 0; i < candidates; i++)
        {
            left_heap.emplace(costs[i]);
        }
        for (int i = right; i < static_cast<int>(costs.size()); i++)
        {
            right_heap.emplace(costs[i]);
        }
        for (int i = 0; i < k; i++)
        {
            int min_k;
            if (!left_heap.empty() && (right_heap.empty() || left_heap.top() <= right_heap.top()))
            {
                min_k = left_heap.top();
                left_heap.pop();
                if (left + 1 < right)
                {
                    left++;
                    left_heap.emplace(costs[left]);
                }
            }
            else
            {
                min_k = right_heap.top();
                right_heap.pop();
                if (left + 1 < right)
                {
                    right--;
                    right_heap.push(costs[right]);
                }
            }
            result += min_k;
        }
        return result;
    }

    long long totalCost_22(vector<int>& costs, int k, int candidates) {
        int n = costs.size();
        std::priority_queue<int, std::vector<int>, std::greater<int>> left, right;

        int i = 0, j = n - 1;                    // 下一个待入左/右堆的下标

        // 左边最多塞 candidates 个
        while (i <= j && i < candidates) {
            left.push(costs[i++]);
        }
        // 右边最多塞 candidates 个，且不跟左边重叠
        while (j >= i && (n - 1 - j) < candidates) {
            right.push(costs[j--]);
        }

        long long ans = 0;
        while (k--) {
            // 左堆非空，且（右堆空 或 左堆顶更小）→ 取左；否则取右
            if (!left.empty() && (right.empty() || left.top() <= right.top())) {
                ans += left.top();
                left.pop();
                if (i <= j) left.push(costs[i++]);
            } else {
                ans += right.top();
                right.pop();
                if (i <= j) right.push(costs[j--]);
            }
        }
        return ans;
    }
    // 一些C++20的写法写的双堆，但是一开始把必然重叠的情况用 nth_element 单独处理，
    // 把“候选区间会重叠/耗尽”的情况提前处理掉了，根本不进后面的双堆循环。
    // 2*candidates + k > n 的含义是：左右两个候选区间加起来，再加上还要选的 k 个人，已经超过总人数 n。
    // 这意味着在 k 轮雇佣过程中，候选区间必然重叠甚至耗尽，此时每一轮其实都是在「所有剩余工人」里选最小，等价于直接选最小的 k 个人。
    // 排除这种情况以后，剩下的双堆肯定不会空，所以可以无脑走
    long long totalCost_20(vector<int>& costs, int k, int candidates) {
        std::size_t ans = 0, n = costs.size();
        if (candidates * 2 + k > n) {
            std::ranges::nth_element(costs, costs.begin() + k);           // C++ 20 std::ranges nth_element(<algorith>)
            return std::reduce(costs.cbegin(), costs.cbegin() + k, 0ll);  // C++ 17 std::reduce
        }

        std::priority_queue<int, std::vector<int>, std::greater<>> left, right;    // C++ 14 greater
        for (int i : costs | std::views::take(candidates)) left.push(i);           // C++ 20 Ranges Views
        for (int i : costs | std::views::reverse | std::views::take(candidates)) right.push(i);
        for (int i = candidates, j = n - 1 - candidates; k--;) {
            bool flg = left.top() <= right.top();
            auto& pq = flg ? left : right;          // 条件运算符选择容器
            ans += pq.top();
            pq.pop();
            if (i <= j) pq.push(costs[flg ? i++ : j--]);
        }
        return ans;
    }

};
// @lc code=end


int main()
{
    Solution s;
    // std::vector<int> costs{1,2,4,1};
    std::vector<int> costs{57,33,26,76,14,67,24,90,72,37,30};
    s.totalCost(costs, 11, 2);
}
