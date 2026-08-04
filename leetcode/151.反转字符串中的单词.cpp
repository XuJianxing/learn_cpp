/*
 * @lc app=leetcode.cn id=151 lang=cpp
 *
 * [151] 反转字符串中的单词
 *
 * https://leetcode.cn/problems/reverse-words-in-a-string/description/
 *
 * algorithms
 * Medium (59.73%)
 * Likes:    1434
 * Dislikes: 0
 * Total Accepted:    891.6K
 * Total Submissions: 1.5M
 * Testcase Example:  '"the sky is blue"'
 *
 * 给你一个字符串 s ，请你反转字符串中 单词 的顺序。
 * 
 * 单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
 * 
 * 返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
 * 
 * 注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "the sky is blue"
 * 输出："blue is sky the"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "  hello world  "
 * 输出："world hello"
 * 解释：反转后的字符串中不能存在前导空格和尾随空格。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：s = "a good   example"
 * 输出："example good a"
 * 解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 10^4
 * s 包含英文大小写字母、数字和空格 ' '
 * s 中 至少存在一个 单词
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 进阶：如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用 O(1) 额外空间复杂度的 原地 解法。
 * 
 */

#include <algorithm>
#include <string>
using namespace std;

/* ============================ 三种写法对比小结 ============================
 *
 * 三种写法均已用穷举对拍验证：字母表 {'a','b',' '}、长度 0~10 的全部 88573
 * 种输入（含空串、全空格、纯前导/尾随空格、连续多空格），与 istringstream
 * 切词后倒序拼接的参考解逐一比对，全部一致；编译期开启 -fsanitize=undefined
 * 与 -D_GLIBCXX_ASSERTIONS，无越界与未定义行为。
 *
 *   写法        时间   额外空间     特判        评价
 *   ----------------------------------------------------------------------
 *   v0(我的)    O(n)   O(n) 输出   i==1 特判   正确，但单词结算逻辑重复两遍
 *   A(选中)     O(n)   O(n) 输出   无          最好读，面试首选
 *   B(原地)     O(n)   O(1)        无          满足题目进阶要求
 *
 * 对拍踩坑记录：参考解一开始命名为 ref，在 using namespace std; 下被 std::ref
 * 通过重载决议抢走（非 const 左值传给 std::ref(T&) 是精确匹配，而自定义的
 * ref(const string&) 需要加 const 限定，属更差匹配），导致参考解从未被调用、
 * 报出大量假失败。自定义函数名要避开 std 里的常见短名（ref/data/size/begin…）。
 * ========================================================================= */

// @lc code=start
class Solution {
public:
    // ==================== 写法 A：最终选中 ====================
    // 思路：从右往左扫，每轮循环“先吃掉空格、再吃掉一个完整单词”。
    // 关键点：把v0 的“被动等空格触发结算”改成“主动跳空格 + 主动取单词”，
    //         于是开头的单词与中间的单词走同一条代码路径，
    //         in_word 标志位和 i==1 特判全部消失。
    // 关键点：下标用 int 而非 size_t，配合 i >= 0 判断，避免无符号下溢。
    // 关键点：用 append(s, pos, len) 直接从 s 拷贝，不像 substr 那样
    //         为每个单词构造一个临时 string，省掉 n 次分配。
    // 时间 O(n)，除返回值外 O(1) 额外空间。
    string reverseWords(string s) {
        string result;
        int i = (int)s.size() - 1;
        while (i >= 0)
        {
            while (i >= 0 && s[i] == ' ') --i;        // 跳过单词后面的空格
            if (i < 0) break;                          // 前面全是空格，扫完了
            int end = i;                               // 单词的最后一个字符
            while (i >= 0 && s[i] != ' ') --i;         // 退到单词前一个位置
            if (!result.empty()) result.push_back(' ');// 非首个单词才补分隔空格
            result.append(s, i + 1, end - i);          // 单词区间为 [i+1, end]
        }
        return result;
    }

    // ==================== 写法 v0：我的初版，留档 ====================
    // 思路同样是从右往左扫，但只在“遇到空格”时才结算一个单词。
    // 缺陷 1：字符串开头就是单词字符时没有空格来触发结算，只能补
    //         if (i == 1 && in_word) 特判，导致“补空格 + append”写了两遍。
    // 缺陷 2：end 是 int 而 i 是 size_t，end - i 会把 end 提升为无符号数。
    //         当前逻辑保证 end > i 才不出错，一旦改动就会得到天文数字。
    //         另外 end = i 是size_t -> int 的窄化转换。
    // 缺陷 3：substr 为每个单词构造临时 string，多了 n 次内存分配。
    // 结论：结果正确、复杂度也是 O(n)，但状态机比必要的复杂。
    string reverseWords_v0_mine(string s) {
        string result;
        bool in_word = false;
        int end = -1;
        for (size_t i = s.length(); i > 0; i--)
        {
            if (s[i - 1] == ' ' && in_word)
            {
                if (result.length()) result.push_back(' ');
                result.append(s.substr(i, end - i));
                in_word = false;
                continue;
            }
            if (s[i - 1] != ' ')
            {
                if (!in_word)
                {
                    end = i;
                    in_word = true;
                }
            }
            if (i == 1 && in_word)
            {
                if (result.length()) result.push_back(' ');
                result.append(s.substr(0, end));
            }
        }
        return result;
    }

    // ============ 写法 B：原地三步走，满足进阶的 O(1) 额外空间 ============
    // 思路：1) 原地压缩多余空格  2) 整体反转  3) 逐个单词再反转回来。
    // 美感在于用“两次反转的复合”把“整体倒序”和“单词内部正序”分离开，
    // 同样不需要任何边界特判。
    // s 是按值传参，本身已是一份可自由改写的副本，故无需再申请缓冲区。
    // 代价：三遍扫描，常数比 A 略大。
    string reverseWords_inplace(string s) {
        // 第1 步：双指针原地压缩，n 是写指针，最终即有效长度
        // 这一步其实是整体把句子和里面的单词往前搬。压缩前后空格和单词间空格，压缩并搬到最前，然后resize去掉尾部
        int n = 0;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            if (s[i] == ' ') continue;
            if (n != 0) s[n++] = ' ';                                  // 非首个单词前补一个空格
            while (i < (int)s.size() && s[i] != ' ') s[n++] = s[i++];  // 整词搬运
        }
        s.resize(n);

        // 第 2 步：整体反转，此时单词顺序已正确，但每个单词内部是倒的
        reverse(s.begin(), s.end());

        // 第 3 步：把每个单词内部再反转回来
        for (int i = 0; i < n; )
        {
            int j = i;
            while (j < n && s[j] != ' ') ++j;
            reverse(s.begin() + i, s.begin() + j);
            i = j + 1;    // 跳过分隔空格
        }
        return s;
    }
};
// @lc code=end

int main()
{
    Solution s;
    string str("the sky is blue");
    s.reverseWords(str);
    return 0;
}
