/*
 * @lc app=leetcode.cn id=328 lang=cpp
 *
 * [328] 奇偶链表
 *
 * https://leetcode.cn/problems/odd-even-linked-list/description/
 *
 * algorithms
 * Medium (64.46%)
 * Likes:    878
 * Dislikes: 0
 * Total Accepted:    288.3K
 * Total Submissions: 447.3K
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * 给定单链表的头节点 head
 * ，将所有索引为奇数的节点和索引为偶数的节点分别分组，保持它们原有的相对顺序，然后把偶数索引节点分组连接到奇数索引节点分组之后，返回重新排序的链表。
 * 
 * 第一个节点的索引被认为是 奇数 ， 第二个节点的索引为 偶数 ，以此类推。
 * 
 * 请注意，偶数组和奇数组内部的相对顺序应该与输入时保持一致。
 * 
 * 你必须在 O(1) 的额外空间复杂度和 O(n) 的时间复杂度下解决这个问题。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 
 * 
 * 输入: head = [1,2,3,4,5]
 * 输出: [1,3,5,2,4]
 * 
 * 示例 2:
 * 
 * 
 * 
 * 
 * 输入: head = [2,1,3,5,6,4,7]
 * 输出: [2,3,6,7,1,5,4]
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * n ==  链表中的节点数
 * 0 <= n <= 10^4
 * -10^6 <= Node.val <= 10^6
 * 
 * 
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:

    // 提示：是链到最后一个奇数节点之后，而不是最终节点之后
    // 关键思维：中间节点本身没有移动操作，只有再拼接操作。唯一移动的只有偶数链头接到奇数链尾
    // 只需要各自把奇数链和偶数链串起来，然后首尾拼接就好了。所以只需要记住偶数链的头
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* odd = head;            // 奇数链尾
        ListNode* even = head->next;     // 偶数链尾
        ListNode* evenHead = even;       // 记住偶数链头

        while (even && even->next) {     // 长度>=3才会进循环
            odd->next = even->next;      // 奇数接到下一个奇数
            odd = odd->next;
            even->next = odd->next;      // 偶数接到下一个偶数
            even = even->next;
        }
        odd->next = evenHead;            // 拼接
        return head;
    }

};
// @lc code=end

/*
为什么没想到这个处理方法？我只是想到了一个节点一个节点的处理，同时又担心同时处理两个节点会出现空指针，不方便处理

这个很正常，你的第一反应其实是大多数人（包括一开始的我）都会有的思路。原因不是「没想到好方法」，而是**出发的心智模型不同**。

## 为什么你会想到「一个节点一个节点处理」

你脑子里默认的模型是**「遍历 + 摘除 + 插入尾部」**：

1. 有一个游标 `cur` 从头走到尾；
2. 遇到偶数节点，就把它「搬」到某个位置（最后一个奇数节点之后）。

这个模型下，你自然会担心两件事：

- 搬节点时要维护 `prev`、`end`、`cur` 三个指针，容易断链；
- 一次动两个指针害怕空指针。

所以你不是没想到，而是**被「搬动节点」这个框架困住了**，觉得「拆成两条链、同时维护两个指针」更危险。

## 关键在于换一个框架看这道题

这道题本质不是「搬动」，而是**「按奇偶分组，且组内保持原相对顺序」**。

而链表有一个特别好的性质：**在原链表里，奇数节点本来就是交替排列的**。也就是说：

- 第 1、3、5… 个节点天然就是奇数链的顺序；
- 第 2、4、6… 个节点天然就是偶数链的顺序。

所以你根本不需要「找到最后一个奇数节点」，也不需要「摘下来再插」——你只需要**一边走，一边把 `next` 重新指向下下个节点**，相当于把这条交替的链「梳」成两条独立的链。

一旦想到「梳成两条链」，双指针就是顺理成章的结果，而不是刻意的技巧。

## 关于你担心的空指针

你的担心是有道理的，但双指针法恰好有一个很优雅的不变量，让你不用额外处理空指针：

- `odd` 和 `even` 总是**成对**往前走；
- 每一轮处理「一个奇数 + 一个偶数」这一对；
- `even` 永远比 `odd` 更靠近链表末尾（因为偶数链的节点在位置上靠后）。

所以判断条件只需要写：

```cpp
while (even && even->next)
```

这一句就同时覆盖了：

- 链表为空（`head == nullptr`）→ 开头单独判断；
- 只有 1 个节点（`even == nullptr`）→ 不进入循环；
- 奇数个节点 → 最后一轮 `even->next == nullptr` 退出；
- 偶数个节点 → 最后 `even == nullptr` 退出。

你不需要额外去数 `length`，也不需要 `prev`、`end` 这些额外的指针。

## 一个可以复用的经验

以后遇到「把链表按某条件分成两组（或多组），且保持组内顺序」的题，优先考虑：

> **为每一组维护一个 `head` + `tail` 指针，边走边接到对应组的 `tail` 后面，最后拼接。**

而不是「在原链表上摘除再插入」。后者要处理游标和插入位置之间的相对移动，很容易像你现在这样踩到「游标追上了已经移动过的节点」的坑。

你现在能走到「发现 bug、复盘思路」这一步，比「直接背答案」有价值得多。这个 `even && even->next` 的双指针范式，之后做 `86.分隔链表`、`86` 同类的分组题会反复用到，记住它就行。
*/
