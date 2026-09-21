/*
 * @lc app=leetcode.cn id=338 lang=cpp
 *
 * [338] 比特位计数
 *
 * https://leetcode.cn/problems/counting-bits/description/
 *
 * algorithms
 * Easy (79.01%)
 * Likes:    1446
 * Dislikes: 0
 * Total Accepted:    411.6K
 * Total Submissions: 521.3K
 * Testcase Example:  '2'
 *
 * 给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数 ，返回一个长度为 n + 1 的数组 ans
 * 作为答案。
 * 
 * 不要使用内置函数来解决（例如，C++ 中的 __builtin_popcount）。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 2
 * 输出：[0,1,1]
 * 解释：
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 5
 * 输出：[0,1,1,2,1,2]
 * 解释：
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 * 3 --> 11
 * 4 --> 100
 * 5 --> 101
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= n <= 10^5
 * 
 * 
 * 
 * 
 * 进阶：
 * 
 * 
 * 很容易就能实现时间复杂度为 O(n log n) 的解决方案，你可以在线性时间复杂度 O(n) 内用一趟扫描解决此问题吗？
 * 
 * 
 * 
 */

#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    // 1. 使用传统方法，每个数字依次计算1的个数。O(n log n)
    // 一个数和自己减一的数求与，就等于消掉最后一位1，统计操作了几次就是有几个1
    vector<int> countBits(int n) {
        std::vector<int> result(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            result[i] = count_one(i);
        }
        return result;
    }

    // 后面时间优化为O(n)都是找数学规律；
    // 但是还有一个思想，就是利用已经计算出的结果，查表获得它的个数，再加上那个数和现在这个数的规律上的区别

    // 2. 找一个以前的数，但是这个数比当前的个数多1
    // 而且这个数是到目前为止，只有最高位是1的那个数。（也就是最高有效位）
    // 当前数减这个数，就等于只扣掉最高位的1以后的数，那扣完再补上1就行了
    vector<int> countBits_2(int n) {
        std::vector<int> bits(n + 1);
        int highBit = 0;
        for (int i = 1; i <= n; i++) {
            if ((i & (i - 1)) == 0) {
                highBit = i;
            }
            bits[i] = bits[i - highBit] + 1;
        }
        return bits;
    }

    // 3. 最低有效位
    // 将当前数右移一位，相当于除2，那肯定比原值小。
    // 而且如果原值是奇数，则多扣了一个1，偶数则没多扣。所以要考虑当前数的奇偶
    vector<int> countBits_3(int n) {
        std::vector<int> bits(n + 1);
        for (int i = 1; i <= n; i++) {
            bits[i] = bits[i >> 1] + (i & 1);
        }
        return bits;
    }

    // 4. 既然 和自己减一的数求与 就等于扣掉最低位的1
    // 那么扣掉以后再加1不就等于当前数的1个数了吗
    vector<int> countBits_4(int n) {
        std::vector<int> bits(n + 1);
        for (int i = 1; i <= n; i++) {
            bits[i] = bits[i & (i - 1)] + 1;
        }
        return bits;
    }


private:
    int count_one(int n)
    {
        int count = 0;
        while (n != 0)
        {
            n &= n - 1;
            count++;
        }
        return count;
    }
};
// @lc code=end

