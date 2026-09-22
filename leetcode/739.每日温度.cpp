/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 *
 * https://leetcode.cn/problems/daily-temperatures/description/
 *
 * algorithms
 * Medium (69.70%)
 * Likes:    2214
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 1.5M
 * Testcase Example:  '[73,74,75,71,69,72,76,73]'
 *
 * 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i
 * 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: temperatures = [73,74,75,71,69,72,76,73]
 * 输出: [1,1,4,2,1,1,0,0]
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: temperatures = [30,40,50,60]
 * 输出: [1,1,1,0]
 * 
 * 
 * 示例 3:
 * 
 * 
 * 输入: temperatures = [30,60,90]
 * 输出: [1,1,0]
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= temperatures.length <= 10^5
 * 30 <= temperatures[i] <= 100
 * 
 * 
 */

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// @lc code=start
class Solution {
public:
    /*
    单调栈：每天向左认领还没答案的日子（还没遇到比他高的温度的时候）
    栈里每次遇到比栈顶低的温度时入栈

    单调栈适用场景：找左边/右边第一个比我大（或小）的元素
    同类题还有 496.下一个更大元素 I、503.下一个更大元素 II、42.接雨水、84.柱状图中最大的矩形。
    */
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        std::vector<int> answer(n, 0);
        // 因为要知道差几天，所以存下标
        std::vector<int> st;  // 单调栈：存下标，对应温度从底到顶严格递减

        for (int i = 0; i < n; ++i) {
            // 当前温度更高，说明它就是栈里那些日子等到的「下一个更高温度」
            while (!st.empty() && temperatures[i] > temperatures[st.back()]) {
                int day = st.back();
                st.pop_back();
                answer[day] = i - day;
            }
            st.push_back(i);  // 自己还没等到更高的，入栈等待
        }
        return answer;
    }
};
// @lc code=end

/*
写法二：从右往左 + 利用已算出的答案「跳跃」（比单调栈更贴近暴力的直觉）

暴力的内层循环是「一天一天往右挪」，而右边这些天的答案其实已经算好了：
如果 temperatures[j] <= temperatures[i]，那 j 这一天以及它到「下一个更高温度」
之间的所有日子，都不可能比 i 高，可以整段跳过去，直接落到 j 的下一个更高温度那天。
思路其实是对暴力的内层循环做剪枝

复杂度：每次跳跃温度都严格升高，本题温度只有 30~100，最多跳 71 次，整体 O(n)；
空间上不需要栈，只用到 answer 数组本身。
*/
class Solution2 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        std::vector<int> answer(n, 0);

        for (int i = n - 2; i >= 0; --i) {
            int j = i + 1;
            while (j < n && temperatures[j] <= temperatures[i]) {
                if (answer[j] == 0) {  // j 之后已经没有更高的了，i 也不可能有
                    j = n;
                    break;
                }
                j += answer[j];        // 整段跳到 j 的下一个更高温度那天
            }
            if (j < n) answer[i] = j - i;
        }
        return answer;
    }
};


int main()
{
    Solution s;
    Solution2 s2;
    vector<int> t1{73,74,75,71,69,72,76,73};
    vector<int> t2{30,40,50,60};
    vector<int> t3{30,60,90};
    // 两种写法结果应完全一致
    auto a1 = s.dailyTemperatures(t1);   // [1,1,4,2,1,1,0,0]
    auto a2 = s.dailyTemperatures(t2);   // [1,1,1,0]
    auto a3 = s.dailyTemperatures(t3);   // [1,1,0]
    auto b1 = s2.dailyTemperatures(t1);
    auto b2 = s2.dailyTemperatures(t2);
    auto b3 = s2.dailyTemperatures(t3);
    cout << boolalpha << (a1 == b1 && a2 == b2 && a3 == b3) << endl;
    for (int x : a1) cout << x << " ";
    cout << endl;
    for (int x : b1) cout << x << " ";
    cout << endl;
    return 0;
}

