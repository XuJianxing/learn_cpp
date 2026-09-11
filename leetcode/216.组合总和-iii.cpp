/*
 * @lc app=leetcode.cn id=216 lang=cpp
 *
 * [216] 组合总和 III
 *
 * https://leetcode.cn/problems/combination-sum-iii/description/
 *
 * algorithms
 * Medium (71.32%)
 * Likes:    992
 * Dislikes: 0
 * Total Accepted:    566.3K
 * Total Submissions: 794.2K
 * Testcase Example:  '3\n7'
 *
 * 找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
 * 
 * 
 * 只使用数字1到9
 * 每个数字 最多使用一次 
 * 
 * 
 * 返回 所有可能的有效组合的列表 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: k = 3, n = 7
 * 输出: [[1,2,4]]
 * 解释:
 * 1 + 2 + 4 = 7
 * 没有其他符合的组合了。
 * 
 * 示例 2:
 * 
 * 
 * 输入: k = 3, n = 9
 * 输出: [[1,2,6], [1,3,5], [2,3,4]]
 * 解释:
 * 1 + 2 + 6 = 9
 * 1 + 3 + 5 = 9
 * 2 + 3 + 4 = 9
 * 没有其他符合的组合了。
 * 
 * 示例 3:
 * 
 * 
 * 输入: k = 4, n = 1
 * 输出: []
 * 解释: 不存在有效的组合。
 * 在[1,9]范围内使用4个不同的数字，我们可以得到的最小和是1+2+3+4 = 10，因为10 > 1，没有有效的组合。
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 2 <= k <= 9
 * 1 <= n <= 60
 * 
 * 
 */

#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        dfs(1, k, n, path, result);   // start=1, 还要选 k 个, 还差 n
        return result;
    }

    /*
    因为候选集只有 9 个数，直接位掩码枚举 1~9 的所有子集（2^9 = 512 个）（平铺开而非DFS）
    没有任何递归、没有 start、没有剪枝，纯粹两层循环 —— 因为 2^9 的搜索空间小到可以暴力穷举。
    递归 + start 那套写法是为了候选集很大时（比如 120、1100）才必须的。
    */
    vector<vector<int>> combinationSum3_2(int k, int n) {
        std::vector<std::vector<int>> res;
        for (int mask = 0; mask < (1 << 9); mask++) {
            if (__builtin_popcount(mask) != k) continue;
            int sum = 0; 
            std::vector<int> path;
            for (int i = 0; i < 9; i++)
                if (mask >> i & 1)
                {
                    sum += i + 1;
                    path.push_back(i + 1);
                }
            if (sum == n)
                res.push_back(path);
        }
        return res;
    }

private:
    void dfs(int start, int k, int target, std::vector<int>& path, std::vector<std::vector<int>>& result)
    {
        // 名额用完，只看和够不够
        if (path.size() == k)
        {
            if (target == 0) result.push_back(path);
            return;
        }
        for (int i = start; i <= 9; i++)
        {
            if (i > target) break;           // 剪枝：i 递增，后面只会更大
            path.push_back(i);
            dfs(i + 1, k, target - i, path, result);  // 起点右移 = 去重
            path.pop_back();
        }
    }
};
// @lc code=end

int main()
{
    Solution s;
    s.combinationSum3(3, 7);
}
