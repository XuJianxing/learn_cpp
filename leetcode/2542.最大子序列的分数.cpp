/*
 * @lc app=leetcode.cn id=2542 lang=cpp
 *
 * [2542] 最大子序列的分数
 *
 * https://leetcode.cn/problems/maximum-subsequence-score/description/
 *
 * algorithms
 * Medium (54.05%)
 * Likes:    131
 * Dislikes: 0
 * Total Accepted:    16.2K
 * Total Submissions: 29.9K
 * Testcase Example:  '[1,3,3,2]\n[2,1,3,4]\n3'
 *
 * 给你两个下标从 0 开始的整数数组 nums1 和 nums2 ，两者长度都是 n ，再给你一个正整数 k 。你必须从 nums1 中选一个长度为 k
 * 的 子序列 对应的下标。
 * 
 * 对于选择的下标 i0 ，i1 ，...， ik - 1 ，你的 分数 定义如下：
 * 
 * 
 * nums1 中下标对应元素求和，乘以 nums2 中下标对应元素的 最小值 。
 * 用公式表示： (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] ,
 * nums2[i1], ... ,nums2[ik - 1]) 。
 * 
 * 
 * 请你返回 最大 可能的分数。
 * 
 * 一个数组的 子序列 下标是集合 {0, 1, ..., n-1} 中删除若干元素得到的剩余集合，也可以不删除任何元素。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
 * 输出：12
 * 解释：
 * 四个可能的子序列分数为：
 * - 选择下标 0 ，1 和 2 ，得到分数 (1+3+3) * min(2,1,3) = 7 。
 * - 选择下标 0 ，1 和 3 ，得到分数 (1+3+2) * min(2,1,4) = 6 。
 * - 选择下标 0 ，2 和 3 ，得到分数 (1+3+2) * min(2,3,4) = 12 。
 * - 选择下标 1 ，2 和 3 ，得到分数 (3+3+2) * min(1,3,4) = 8 。
 * 所以最大分数为 12 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
 * 输出：30
 * 解释：
 * 选择下标 2 最优：nums1[2] * nums2[2] = 3 * 10 = 30 是最大可能分数。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == nums1.length == nums2.length
 * 1 <= n <= 10^5
 * 0 <= nums1[i], nums2[j] <= 10^5
 * 1 <= k <= n
 * 
 * 
 */

#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
using namespace std;

// @lc code=start
class Solution {
public:
    // 思路：排序 + 小顶堆，绕开枚举所有组合
    // 关键点：数字都是正整数，只有这样才能排序做，否则相乘的结果（正负）无法保证了
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();

        // 按下标建立索引，再按 nums2 的值从大到小排序
        std::vector<int> idx(n);
        // 初始化idx数组，从0开始递增填值
        std::iota(idx.begin(), idx.end(), 0);
        // 把下标排序，但是要按数组中值本身的大小，排下标
        std::sort(idx.begin(), idx.end(), [&](int a, int b) {
            return nums2[a] > nums2[b];
        });

        // 小顶堆：维护已选集合中 nums1 的值，堆顶是最小的（用于淘汰）
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        long long sum = 0;
        long long ans = 0;

        for (int i : idx) {
            sum += nums1[i];
            pq.push(nums1[i]);

            // 堆内元素超过 k 个，弹出最小的那个
            if ((int)pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }

            // 堆内恰好 k 个时，当前元素是这 k 个里 nums2 最小的（降序遍历）
            if ((int)pq.size() == k) {
                ans = max(ans, sum * (long long)nums2[i]);
            }
        }

        return ans;
    }
};
// @lc code=end


#include <limits>
#include <iostream>

// ============ 通用版：枚举出所有"选 k 个位置"的组合 ============
// 把每个组合的下标放进 chosen 里，所有结果记录到result里，供你处理
void dfsSelect(const vector<int>& nums, int k, int start, vector<int>& chosen, vector<vector<int>>& result)
{
    if ((int)chosen.size() == k) {          // 已经选满 k 个
        result.push_back(chosen);           // 记录这个组合
        return;
    }
    // 从某位置开始，选剩余所需个数的位置
    // 剪枝：剩余位置不够选满 k 个，直接停止
    for (int i = start; i <= (int)nums.size() - (k - chosen.size()); ++i) {
        chosen.push_back(i);                // 选下标 i

        dfsSelect(nums, k, i + 1, chosen, result);

        // 回溯：push_back 选、递归、pop_back 撤销，这是 DFS 枚举组合的标准三板斧。
        chosen.pop_back();                  // 回溯，撤销选择
    }
}

int main()
{
    // 两种枚举 `C(n, k)` 组合所有可能性的做法：
    // 1. 位掩码（bitmask）——枚举所有子集再筛：用一个整数 mask 的每一位表示"这个下标选不选"。从 0 到 2^n - 1 遍历所有子集，再筛出二进制中 1 的个数等于 k 的那些。
    // 这种做法的前提：小数据，暴力验证，n不能超过数值的位数
    int k = 4;
    int n = 8;
    long long ans = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) != k) continue;   // 只保留选了 k 个的
        long long sum = 0;
        int mn = std::numeric_limits<int>::max();
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {                        // 第 i 位是 1 表示选了 i
                // do something
            }
        }
        ans = max(ans, sum * mn);
    }

    // 2. DFS回溯——直接生成 C(n, k) 个组合
    vector<int> nums = {10, 20, 30, 40};
    vector<vector<int>> result;
    vector<int> chosen;
    dfsSelect(nums, 3, 0, chosen, result);

    for (auto& c : result) {
        std::cout << "下标: ";
        for (int i : c) std::cout << i << " ";
        std::cout << "  对应值: ";
        for (int i : c) std::cout << nums[i] << " ";
        std::cout << std::endl;
    }

    // 测试本题
    std::vector<int> nums1 = {1, 3, 3, 2};
    std::vector<int> nums2 = {2, 1, 3, 4};
    Solution s;
    std::cout << "最大分数: " << s.maxScore(nums1, nums2, 3) << std::endl;

}
