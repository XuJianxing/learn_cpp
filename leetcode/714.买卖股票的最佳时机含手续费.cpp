/*
 * @lc app=leetcode.cn id=714 lang=cpp
 *
 * [714] 买卖股票的最佳时机含手续费
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
 *
 * algorithms
 * Medium (77.62%)
 * Likes:    1192
 * Dislikes: 0
 * Total Accepted:    358.4K
 * Total Submissions: 461.6K
 * Testcase Example:  '[1,3,2,8,4,9]\n2'
 *
 * 给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。
 * 
 * 你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
 * 
 * 返回获得利润的最大值。
 * 
 * 注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
 * 输出：8
 * 解释：能够达到的最大利润:  
 * 在此处买入 prices[0] = 1
 * 在此处卖出 prices[3] = 8
 * 在此处买入 prices[4] = 4
 * 在此处卖出 prices[5] = 9
 * 总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8
 * 
 * 示例 2：
 * 
 * 
 * 输入：prices = [1,3,7,5,10,3], fee = 3
 * 输出：6
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= prices.length <= 5 * 10^4
 * 1 <= prices[i] < 5 * 10^4
 * 0 <= fee < 5 * 10^4
 * 
 * 
 */

#include <algorithm>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    /*
    每天结束时只有两种状态：持有股票 / 不持有股票，所以是「状态机 DP」
    （买卖股票系列 121/122/123/188/309/714 都是这个套路）

    hold: 第 i 天结束后【持有】股票时，手里的最大现金（可以是负数，因为买入花了钱）
    cash: 第 i 天结束后【不持有】股票时，手里的最大现金

    状态转移，每天只有四种选择：
    1) 昨天持有，今天不动   -> hold 保持 hold
    2) 昨天空仓，今天买入   -> hold = cash - prices[i]
    3) 昨天空仓，今天不动   -> cash 保持 cash
    4) 昨天持有，今天卖出   -> cash = hold + prices[i] - fee
    取每种状态下的最大值即可：
        hold = max(hold, cash - prices[i])
        cash = max(cash, hold + prices[i] - fee)
    手续费一笔交易只付一次，放在卖出时扣（放在买入时扣 -fee 完全等价）

    注意：两个转移都要用【昨天】的 hold/cash 来算，否则会出现"当天买当天卖"，
    所以先用临时变量保存旧值再更新

    初始：第 0 天买入则 hold = -prices[0]，什么都不做则 cash = 0
    答案：cash（最后还握着股票没法变现，一定不优于卖掉）
     */
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int hold = -prices[0]; // 第 0 天买入
        int cash = 0;          // 第 0 天什么都不做
        for (int i = 1; i < n; i++) {
            int prevHold = hold;
            int prevCash = cash;
            // 今天结束后仍持有：昨天就持有不动 / 昨天空仓今天买入
            hold = std::max(prevHold, prevCash - prices[i]);
            // 今天结束后不持有：昨天就空仓不动 / 昨天持有今天卖出（付手续费）
            cash = std::max(prevCash, prevHold + prices[i] - fee);
        }
        return cash;
    }
};
// @lc code=end

/*
为什么能想到使用 hold 和 cash 来递推呢？
因为如果想要状态转移走下去，就需要知道下一步有哪些操作可选。
如果只有一个“当前利润”，我们会发现无法递推下去，因为你不知道现在有没有持有股票
知道现在持有股票才能知道买卖，后续可选操作完全不同
1. 为什么不直接用bool记录现在是否持有股票？
因为首先你没法决定今天是否继续持有股票，因为交易还没结束
其次，这是一个动态过程，每天都可能持有或不持有。你需要区分两种情况分别计算今天的最大利润

2. 为什么不需要记录买入价卖出价，不知道这个怎么知道能赚多少钱？
因为首先，卖出价就是今天的价格，因为交易到今天截至（每天都可能是DP终点），你必须卖出才能最大利润
然后，买入价就已经计算到成本里了，已经记录到hold中了。买了以后，你就不用关心成本价了，只需要关心 账面与股价

所以这个问题其实是两个状态同时DP进行。今天持有or不持有，对应分别的最优结果
*/
