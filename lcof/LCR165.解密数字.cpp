/*
 * @lc app=leetcode.cn id=LCR165 lang=cpp
 *
 * [LCR 165] 解密数字
 * （旧标题：剑指 Offer 46. 把数字翻译成字符串，slug 中的 lcof 后缀即来源于此）
 *
 * https://leetcode.cn/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/
 *
 * algorithms
 * Medium (56.28%)
 *
 * 现有一串神秘的密文 ciphertext，经调查，密文的特点和规则如下：
 * - 密文由非负整数组成
 * - 数字 0-25 分别对应字母 a-z
 *
 * 一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
 *
 * 示例 1：
 * 输入: ciphertext = 12258
 * 输出: 5
 * 解释: 12258 有 5 种不同的翻译，分别是 "bccfi"、"bwfi"、"bczi"、"mcfi" 和 "mzi"
 *
 * 提示：
 * 0 <= ciphertext < 2^31
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    int crackNumber(int ciphertext) {
        // 1) dp[i]：前 i 位数字的翻译种数。dp[0] = 1（空串 1 种：什么都不翻），dp[1] = 1。
        // 2) 第 i-1、i 位能合并成一个字符，当且仅当两位数 text[i-2..i-1] ∈ [10, 25]。
        //    下界取 10 而不是 06：前导 0 的 "06" 只能拆成 "0"+"6"，不能合并。
        // 3) dp[i] 只依赖 dp[i-1]、dp[i-2]，可以用两个变量滚动成 O(1) 空间（见下方注释）。
        const std::string text = std::to_string(ciphertext);
        const int n = static_cast<int>(text.length());

        /* 
        i 在 dp 里是数量，不是下标。但是在 text 中代表下标。
        用text中的前一位+当前位，计算dp的当前位。
        加上dp[0]空串的定义是为了代码简洁，不用再加特判了，让循环统一自洽
         */
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1];  // 第 i 位单独翻译
            // 合并成数字来统一判断，便捷的做法
            // 第一种是第i位单独翻，第二种是与前一位合并翻，这样的话就是再累加上前i-2位的种数
            const int two = (text[i - 2] - '0') * 10 + (text[i - 1] - '0');
            if (two >= 10 && two <= 25) {
                dp[i] += dp[i - 2];  // 与第 i-1 位合并成一个字符
            }
        }
        return dp[n];

        // O(1) 空间写法（与上面等价）：
        // int prev2 = 1, prev1 = 1;
        // for (int i = 2; i <= n; i++) {
        //     int cur = prev1;
        //     const int two = (text[i - 2] - '0') * 10 + (text[i - 1] - '0');
        //     if (two >= 10 && two <= 25) cur += prev2;
        //     prev2 = prev1; prev1 = cur;
        // }
        // return prev1;
    }
};
// @lc code=end

int main() {
    Solution s;
    cout << s.crackNumber(12258) << "  (期望 5)" << endl;
    cout << s.crackNumber(0) << "  (期望 1)" << endl;
    cout << s.crackNumber(25) << "  (期望 2: cf / z)" << endl;
    cout << s.crackNumber(506) << "  (期望 1: 50 和 06 都不合法)" << endl;
    cout << s.crackNumber(100) << "  (期望 2: baa / ka)" << endl;
    return 0;
}
