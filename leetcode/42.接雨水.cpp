/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 *
 * https://leetcode.cn/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (66.07%)
 * Likes:    6432
 * Dislikes: 0
 * Total Accepted:    1.9M
 * Total Submissions: 2.9M
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出：6
 * 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：height = [4,2,0,3,2,5]
 * 输出：9
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == height.length
 * 1 <= n <= 2 * 10^4
 * 0 <= height[i] <= 10^5
 * 
 * 
 */

#include <algorithm>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    // 做法1：一个位置能接多少雨水，是由这个位置的左边最大值和右边最大值共同决定的
    // 即 water[i] = min(preMax[i], sufMax[i]) - height[i]
    // 时间复杂度 O(n)，空间复杂度 O(n)
    int trap(vector<int>& height) {
        int n = height.size();
        // preMax[i]：height[0..i] 的最大值，sufMax[i]：height[i..n-1] 的最大值
        std::vector<int> preMax(n), sufMax(n);
        preMax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            preMax[i] = std::max(preMax[i - 1], height[i]);
        }
        sufMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            sufMax[i] = std::max(sufMax[i + 1], height[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += std::min(preMax[i], sufMax[i]) - height[i];
        }
        return ans;
    }

    // 做法2：相向双指针，把做法1的两个数组压缩成两个变量
    // 时间复杂度 O(n)，空间复杂度 O(1)
    //
    // 【难点】做法1要拿到「全局」的左右最大值才能结算，双指针凭什么边走边结算？
    //   维护 preMax = height[0..l] 的最大值，sufMax = height[r..n-1] 的最大值。
    //   注意这只是「目前已扫过的」左右最大值，并不是 l 位置真正的右边最大值。
    //
    // 【关键结论】但这并不妨碍结算：
    //   若 preMax < sufMax：l 右侧已扫到的最高柱子是 sufMax，既然 sufMax > preMax，
    //     那 l 真正的「右边最大值」必然 >= sufMax > preMax，
    //     于是 min(左最大, 右最大) 一定就是 preMax —— 水位被左侧短板卡死，可以立刻结算 l。
    //     （右边再高也没用，木桶的短板是 preMax）
    //   若 preMax >= sufMax：对称地，r 真正的「左边最大值」必然 >= preMax >= sufMax，
    //     于是位置 r 的水位就是 sufMax，可以立刻结算 r。
    //
    // 所以每轮都能确定「其中一侧」的水位：谁小就结算谁，然后该侧指针内移。
    // 两个指针相向而行，共走 n 步，每步 O(1)，总时间 O(n)。
    //
    // 【为什么 l <= r 而不是 l < r】l == r 时仍要结算一次该位置，
    //   此时 preMax == sufMax == 全局最大值，加的是 maxH - height[l] = 0，不影响结果，
    //   写成 l <= r 逻辑更统一，不必特殊处理中间那一根柱子。
    int trap2(vector<int>& height) {
        int l = 0, r = (int)height.size() - 1;
        int preMax = 0, sufMax = 0;  // 分别是 [0..l] 和 [r..n-1] 的最大值
        int ans = 0;
        while (l <= r) {
            // 先更新两侧最大值，再判断结算哪一侧
            preMax = std::max(preMax, height[l]);
            sufMax = std::max(sufMax, height[r]);
            if (preMax < sufMax) {
                ans += preMax - height[l];  // 左短板，水位 = preMax
                ++l;
            } else {
                ans += sufMax - height[r];  // 右短板，水位 = sufMax
                --r;
            }
        }
        return ans;
    }

    // 做法3：单调栈，换一个视角——不按「列」纵向累加，而是按「层」横向累加
    // 时间复杂度 O(n)（每根柱子入栈一次、出栈一次），空间复杂度 O(n)
    //
    // 【思路】做法1/2 是一列一列地算：water[i] = 水位 - height[i]。
    //   单调栈则是一层一层地算：每当遇到一根「更高」的柱子，就说明它和左边某个更高的柱子
    //   之间形成了一个凹槽，把这个凹槽的积水一次性算出来。
    //
    // 【栈的维护】栈里存下标，且保证 height[st[0]] > height[st[1]] > ... （严格递减）。
    //   遍历到 i 时，只要 height[i] > height[栈顶]，就说明栈顶这根柱子被困住了，
    //   右边出现了比它高的柱子 i，左边是栈里它下面那根（新的栈顶），于是形成一个凹槽。
    //
    // 【一次弹出的积水怎么算】
    //   bottom = 弹出的槽底（凹槽的最低处）
    //   left   = 弹出后的新栈顶，即凹槽的左边界
    //   i      = 凹槽的右边界（当前这根更高的柱子）
    //   宽 w = i - left - 1
    //   高 h = min(height[left], height[i]) - height[bottom]   ← 依然是木桶原理
    //   贡献 = w * h，即横向一层一层的矩形面积
    //
    // 【注意点】
    //   1. 弹出后若栈为空，说明左边没有任何更高的柱子，凹槽没有左边界，兜不住水，直接 break。
    //   2. 循环条件是 while 而不是 if：一根高柱子可能同时填平好几个凹槽（如示例 [4,2,0,3,2,5] 中
    //      最后的 5），需要连续弹出直到栈空或栈顶不再低于 height[i]。
    //   3. 条件是 > 而不是 >=：相等高度的柱子不构成凹槽，保持严格递减即可，
    //      用 > 让相同高度的柱子都留在栈里，由它们共同作为边界，结果不变。
    int trap3(vector<int>& height) {
        std::vector<int> st;  // 存下标，对应高度严格单调递减
        int ans = 0;
        for (int i = 0; i < (int)height.size(); ++i) {
            while (!st.empty() && height[i] > height[st.back()]) {
                int bottom = st.back();
                st.pop_back();
                if (st.empty()) {
                    break;  // 左边没有更高的柱子，形不成凹槽，兜不住水
                }
                int left = st.back();
                int w = i - left - 1;
                int h = min(height[left], height[i]) - height[bottom];
                ans += w * h;
            }
            st.push_back(i);
        }
        return ans;
    }
};
// @lc code=end

