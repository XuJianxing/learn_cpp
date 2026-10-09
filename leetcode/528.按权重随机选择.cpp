/*
 * @lc app=leetcode.cn id=528 lang=cpp
 *
 * [528] 按权重随机选择
 *
 * https://leetcode.cn/problems/random-pick-with-weight/description/
 *
 * algorithms
 * Medium (50.05%)
 * Likes:    369
 * Dislikes: 0
 * Total Accepted:    73.6K
 * Total Submissions: 146.8K
 * Testcase Example:  '["Solution","pickIndex"]\n[[[1]],[]]'
 *
 * 给你一个 下标从 0 开始 的正整数数组 w ，其中 w[i] 代表第 i 个下标的权重。
 * 
 * 请你实现一个函数 pickIndex ，它可以 随机地 从范围 [0, w.length - 1] 内（含 0 和 w.length -
 * 1）选出并返回一个下标。选取下标 i 的 概率 为 w[i] / sum(w) 。
 * 
 * 
 * 
 * 
 * 
 * 例如，对于 w = [1, 3]，挑选下标 0 的概率为 1 / (1 + 3) = 0.25 （即，25%），而选取下标 1 的概率为 3 / (1
 * + 3) = 0.75（即，75%）。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：
 * ["Solution","pickIndex"]
 * [[[1]],[]]
 * 输出：
 * [null,0]
 * 解释：
 * Solution solution = new Solution([1]);
 * solution.pickIndex(); // 返回 0，因为数组中只有一个元素，所以唯一的选择是返回下标 0。
 * 
 * 示例 2：
 * 
 * 
 * 输入：
 * ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
 * [[[1,3]],[],[],[],[],[]]
 * 输出：
 * [null,1,1,1,1,0]
 * 解释：
 * Solution solution = new Solution([1, 3]);
 * solution.pickIndex(); // 返回 1，返回下标 1，返回该下标概率为 3/4 。
 * solution.pickIndex(); // 返回 1
 * solution.pickIndex(); // 返回 1
 * solution.pickIndex(); // 返回 1
 * solution.pickIndex(); // 返回 0，返回下标 0，返回该下标概率为 1/4 。
 * 
 * 由于这是一个随机问题，允许多个答案，因此下列输出都可以被认为是正确的:
 * [null,1,1,1,1,0]
 * [null,1,1,1,1,1]
 * [null,1,1,1,0,0]
 * [null,1,1,1,0,1]
 * [null,1,0,1,0,0]
 * ......
 * 诸若此类。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= w.length <= 10^4
 * 1 <= w[i] <= 10^5
 * pickIndex 将被调用不超过 10^4 次
 * 
 * 
 */

#include <vector>
#include <random>

using namespace std;

// @lc code=start
class Solution {
public:
    Solution(const std::vector<int>& w) {
        _prefix.reserve(w.size());
        long long acc = 0;
        for (int x : w) {
            acc += x;
            _prefix.push_back(static_cast<int>(acc));
        }
        // 分布与引擎都在构造时完成初始化
        _gen.seed(std::random_device{}());
        _dist = std::uniform_int_distribution<int>(1, static_cast<int>(acc));
    }

    // 找第一个 pre[i] >= x
    // lower_bound返回的是迭代器，所以还需要转换成整数
    // it - begin 是从begin到it的距离
    int pickIndex() {
        /*
        两个细节
        类型：it - pre.begin() 的类型是 ptrdiff_t （64 位有符号），赋给 int 会窄化。
        本题 n ≤ 10⁴ 无所谓，严谨点写 static_cast<int>(...)。

        越界：如果 x 比所有元素都大，lower_bound 返回 end()，而 end() - begin() == size()，得到的下标是 n——越界。
        所以 uniform_int_distribution 的范围必须严格是 [1, total]，一旦写成默认范围 [0, INT_MAX]，就会静默返回越界下标。
        */
        return std::lower_bound(_prefix.begin(), _prefix.end(), _dist(_gen))
             - _prefix.begin();
    }

private:
    std::vector<int> _prefix;
    std::mt19937 _gen;
    std::uniform_int_distribution<int> _dist{1, 1};  // 占位，构造体内被覆盖

public:
    int pickIndex(const std::vector<int>& weights) {
        long long sum = std::accumulate(weights.begin(), weights.end(), 0LL);

        // 1. 引擎：负责产生随机比特
        std::random_device rd;      // 真随机种子（硬件熵源）
        std::mt19937 gen(rd());     // 梅森旋转引擎，最常用
        // 2. 分布：负责把比特映射成 [1, sum] 的均匀整数
        std::uniform_int_distribution<int> dist(1, static_cast<int>(sum));
        // 3. 调用分布，传入引擎
        int x = dist(gen);

        long long weight = 0;
        for (size_t i = 0; i < weights.size(); i++)
        {
            weight += weights[i];
            if (weight >= x)
                return i;
        }
        return -1;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
// @lc code=end

