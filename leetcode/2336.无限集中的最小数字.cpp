/*
 * @lc app=leetcode.cn id=2336 lang=cpp
 *
 * [2336] 无限集中的最小数字
 *
 * https://leetcode.cn/problems/smallest-number-in-infinite-set/description/
 *
 * algorithms
 * Medium (71.20%)
 * Likes:    110
 * Dislikes: 0
 * Total Accepted:    47K
 * Total Submissions: 66.1K
 * Testcase Example:  '["SmallestInfiniteSet","addBack","popSmallest","popSmallest","popSmallest","addBack","popSmallest","popSmallest","popSmallest"]\n' +
  '[[],[2],[],[],[],[1],[],[],[]]'
 *
 * 现有一个包含所有正整数的集合 [1, 2, 3, 4, 5, ...] 。
 * 
 * 实现 SmallestInfiniteSet 类：
 * 
 * 
 * SmallestInfiniteSet() 初始化 SmallestInfiniteSet 对象以包含 所有 正整数。
 * int popSmallest() 移除 并返回该无限集中的最小整数。
 * void addBack(int num) 如果正整数 num 不 存在于无限集中，则将一个 num 添加 到该无限集中。
 * 
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 输入
 * ["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest",
 * "popSmallest", "addBack", "popSmallest", "popSmallest", "popSmallest"]
 * [[], [2], [], [], [], [1], [], [], []]
 * 输出
 * [null, null, 1, 2, 3, null, 1, 4, 5]
 * 
 * 解释
 * SmallestInfiniteSet smallestInfiniteSet = new SmallestInfiniteSet();
 * smallestInfiniteSet.addBack(2);    // 2 已经在集合中，所以不做任何变更。
 * smallestInfiniteSet.popSmallest(); // 返回 1 ，因为 1 是最小的整数，并将其从集合中移除。
 * smallestInfiniteSet.popSmallest(); // 返回 2 ，并将其从集合中移除。
 * smallestInfiniteSet.popSmallest(); // 返回 3 ，并将其从集合中移除。
 * smallestInfiniteSet.addBack(1);    // 将 1 添加到该集合中。
 * smallestInfiniteSet.popSmallest(); // 返回 1 ，因为 1 在上一步中被添加到集合中，
 * ⁠                                  // 且 1 是最小的整数，并将其从集合中移除。
 * smallestInfiniteSet.popSmallest(); // 返回 4 ，并将其从集合中移除。
 * smallestInfiniteSet.popSmallest(); // 返回 5 ，并将其从集合中移除。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= num <= 1000
 * 最多调用 popSmallest 和 addBack 方法 共计 1000 次
 * 
 * 
 */

#include <queue>
#include <set>

// @lc code=start
// ============ 简洁解法：直接用set，天然有序且去重 ============
class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() : cur(1) {}

    int popSmallest() {
        if (s.empty())
            return cur++;
        // set可以用begin()获得最小值，这个很关键
        int res = *s.begin();   // 最小元素
        s.erase(s.begin());
        return res;
    }

    void addBack(int num) {
        if (num < cur)
            s.insert(num);   // set 自动去重
    }

private:
    int cur;                  // 下一个未弹出的连续正整数
    std::set<int> s;          // 回填的小于 cur 的数
};

// ============ 个人解法：_min记录水位线，小顶堆存回填的数 ============
// 实测个人解法更少的时间空间消耗。因为：
// 1. set的红黑树，每个节点需要额外存储：父指针、左孩子指针、右孩子指针（3 个指针）、颜色标记 / 平衡信息、堆内存分配器的对齐和块头开销
// 而priority_queue 底层是 std::vector<int>，元素连续存放，一个 int 就是 4 字节，没有指针和分配开销。
// 2. set需要指针跳转，缓存未命中更频繁；需要旋转 + 重新染色来维持红黑树平衡；动态内存分配本身也有开销。
// 而连续数组，缓存友好，没有动态分配、没有指针、没有旋转。
class SmallestInfiniteSet2 {
public:
    SmallestInfiniteSet2() {
        _min = 1;
    }
    
    int popSmallest() {
        if (pq.empty())
        {
            return _min++;
        }
        int result = pq.top();
        while (!pq.empty() && pq.top() == result)
        {
            pq.pop();
        }
        return result;
    }
    
    void addBack(int num) {
        if (_min <= num)
            return;
        pq.emplace(num);
    }
private:
    int _min;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
// @lc code=end

