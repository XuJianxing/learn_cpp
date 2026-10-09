/*
 * @lc app=leetcode.cn id=274 lang=cpp
 *
 * [274] H 指数
 *
 * https://leetcode.cn/problems/h-index/description/
 *
 * algorithms
 * Medium (46.84%)
 * Likes:    657
 * Dislikes: 0
 * Total Accepted:    364.6K
 * Total Submissions: 777.5K
 * Testcase Example:  '[3,0,6,1,5]'
 *
 * 给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。
 * 
 * 根据维基百科上 h 指数的定义：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，并且 至少 有 h
 * 篇论文被引用次数大于等于 h 。如果 h 有多种可能的值，h 指数 是其中最大的那个。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：citations = [3,0,6,1,5]
 * 输出：3 
 * 解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
 * 由于研究者有 3 篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用 不多于 3 次，所以她的 h 指数是 3。
 * 
 * 示例 2：
 * 
 * 
 * 输入：citations = [1,3,1]
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == citations.length
 * 1 <= n <= 5000
 * 0 <= citations[i] <= 1000
 * 
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    // 核心：把"求最大的 h"翻译成一个可判定的条件
    //   h 成立  <=>  引用数 >= h 的论文至少有 h 篇
    // 而 h 最大只可能是 n（论文总数），所以答案就在 0..n 之间。

    // ---------------------------------------------------------------
    // 解法一（推荐）：计数排序 / 桶，O(n) 时间 + O(n) 空间
    //
    // 直觉：h 最大不超过 n，所以"引用 1000 次"和"引用 n+1 次"在本题里
    // 完全等价——反正都不会把 h 抬到 n 以上。于是把 > n 的统统塞进
    // 第 n 号桶（"截断"），只需要 n+1 个桶。
    //
    // bucket[c] = 恰好被引用 c 次的论文数（c == n 时表示"被引用 >= n 次"）
    // 再从大到小累加：sum = 引用数 >= i 的论文总数
    // 第一个满足 sum >= i 的 i 就是答案（从大到小枚举，所以第一个就是最大 h）
    // ---------------------------------------------------------------
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> bucket(n + 1, 0);           // 0..n 共 n+1 个桶
        for (int c : citations) {
            bucket[min(c, n)]++;                // 超过 n 的一律并入 n 号桶
        }

        int sum = 0;                            // 当前已累计的论文数
        for (int i = n; i >= 0; --i) {
            sum += bucket[i];                   // sum == 引用数 >= i 的论文总数
            if (sum >= i) return i;             // 满足定义，且 i 从大到小，即最大 h
        }
        return 0;
    }

    // ---------------------------------------------------------------
    // 解法二：排序 + 从后往前扫，O(n log n) 时间 + O(1) 额外空间
    //
    // 升序排好后，citations[n - h] 是"最大的 h 篇里被引用最少的那篇"。
    // 它 >= h 就说明确实有 h 篇论文引用数 >= h。
    // ---------------------------------------------------------------
    int hIndex_sort(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int n = citations.size();
        int h = 0;
        // 从后往前：第 1 篇、第 2 篇……看能不能撑起 h = 1, 2, ...
        for (int i = n - 1; i >= 0; --i) {
            if (citations[i] > h) h++;          // 用 > 而非 >=，避免引用数相等时重复计数
        }
        return h;
    }
};
// @lc code=end

