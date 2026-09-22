/*
 * @lc app=leetcode.cn id=901 lang=cpp
 *
 * [901] 股票价格跨度
 *
 * https://leetcode.cn/problems/online-stock-span/description/
 *
 * algorithms
 * Medium (64.47%)
 * Likes:    526
 * Dislikes: 0
 * Total Accepted:    116.7K
 * Total Submissions: 181K
 * Testcase Example:  '["StockSpanner","next","next","next","next","next","next","next"]\r\n' +
  '[[],[100],[80],[60],[70],[60],[75],[85]]\r'
 *
 * 设计一种算法，收集某支股票的每日价格报价，并返回该股票当前日期的 价格跨度。
 * 
 * 股票在某一天的 价格跨度 是指：从当天开始向前，连续的股票价格小于或等于当天价格的最大天数。
 * 
 * 
 * 例如，如果股票过去四天的价格为 [7,2,1,2]，今天的价格为 2，那么今天的价格跨度为 4，因为从今天开始向前，有连续 4 天的股票价格小于或等于
 * 2。
 * 同样，如果股票过去四天的价格为 [7,34,1,2]，今天的价格为 8，那么今天的价格跨度为 3，因为从今天开始向前，有连续 3 天的股票价格小于或等于
 * 8。
 * 
 * 
 * 实现 StockSpanner 类：
 * 
 * 
 * StockSpanner() 初始化该类的对象。
 * int next(int price) 给定今天的股票价格 price，返回今天股票价格的 价格跨度。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入
 * ["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
 * [[], [100], [80], [60], [70], [60], [75], [85]]
 * 输出
 * [null, 1, 1, 1, 2, 1, 4, 6]
 * 
 * 解释
 * StockSpanner stockSpanner = new StockSpanner();
 * stockSpanner.next(100); // 返回 1
 * stockSpanner.next(80);  // 返回 1
 * stockSpanner.next(60);  // 返回 1
 * stockSpanner.next(70);  // 返回 2
 * stockSpanner.next(60);  // 返回 1
 * stockSpanner.next(75);  // 返回 4，因为包含今天在内的最后 4 天的价格都小于或等于今天的价格 75。
 * stockSpanner.next(85);  // 返回 6
 * 
 * 
 * 
 * 
 * 约束条件：
 * 
 * 
 * 1 <= price <= 10^5
 * 最多会调用 10^4 次 next。
 * 
 * 
 */

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

// @lc code=start
class StockSpanner {
public:
    StockSpanner() {
    }

    /*
    实际上，往前连续小于等于今天的值，等价于从前往后一直到今天是遇到的第一个变大的值
    所以做法和每日温度一样
    而且假如今天是更大值，那今天就是分水岭。
    今天的价格跨度是从今天开始到之前所有小于等于今天的个数
    往后再来的数字如果更大，则更大的会囊括今天的范围并且开辟新范围，所以要把前面比他小的pop
    如果今天是更小值，则今天归属于之前的跨度范围，则进入排队（栈）中，他自己无法开辟新分水岭
    */
    int next(int price) {
        int span = 1;  // 跨度包含今天，今天自己算 1 天
        // 栈顶价格 <= 今天，说明它那一整段连续区间也都 <= 今天，直接合并过来
        // 等价于 739 题写法二的「利用已算出的答案跳跃」，避免一天一天往回枚举
        while (!st_.empty() && st_.back().first <= price) {
            span += st_.back().second;
            st_.pop_back();
        }
        st_.emplace_back(price, span);  // 栈中价格保持单调递减
        return span;
    }

private:
    // 单调递减栈：{当天的价格, 当天的跨度}
    vector<pair<int, int>> st_;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
// @lc code=end


int main()
{
    // 示例 1
    StockSpanner s;
    vector<int> prices{100, 80, 60, 70, 60, 75, 85};  // 期望 [1,1,1,2,1,4,6]
    for (int p : prices) cout << s.next(p) << " ";
    cout << endl;

    // 题目描述的两个例子
    StockSpanner s2;
    cout << s2.next(7) << " ";   // 1
    cout << s2.next(34) << " ";  // 2（7 <= 34，把 7 那天合并进来）
    cout << s2.next(1) << " ";   // 1
    cout << s2.next(2) << " ";   // 2（1 <= 2）
    cout << s2.next(8) << endl;  // 3：8(今天) + 2 + 1，被 34 挡住

    StockSpanner s3;
    cout << s3.next(7) << " ";   // 1
    cout << s3.next(2) << " ";   // 1
    cout << s3.next(1) << " ";   // 1
    cout << s3.next(2) << " ";   // 3
    cout << s3.next(2) << endl;  // 4（中文描述写 3，是翻译笔误，英文原文为 4）
    return 0;
}

