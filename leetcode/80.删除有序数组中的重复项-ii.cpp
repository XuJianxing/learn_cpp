/*
 * @lc app=leetcode.cn id=80 lang=cpp
 *
 * [80] 删除有序数组中的重复项 II
 *
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/description/
 *
 * algorithms
 * Medium (63.45%)
 * Likes:    1409
 * Dislikes: 0
 * Total Accepted:    734.1K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,1,1,2,2,3]'
 *
 * 给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。
 * 
 * 不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
 * 
 * 
 * 
 * 说明：
 * 
 * 为什么返回数值是整数，但输出的答案是数组呢？
 * 
 * 请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
 * 
 * 你可以想象内部操作如下:
 * 
 * 
 * // nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
 * int len = removeDuplicates(nums);
 * 
 * // 在函数里修改输入数组对于调用者是可见的。
 * // 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
 * for (int i = 0; i < len; i++) {
 * print(nums[i]);
 * }
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,1,1,2,2,3]
 * 输出：5, nums = [1,1,2,2,3]
 * 解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3。 不需要考虑数组中超出新长度后面的元素。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [0,0,1,1,1,1,2,3,3]
 * 输出：7, nums = [0,0,1,1,2,3,3]
 * 解释：函数应返回新长度 length = 7, 并且原数组的前七个元素被修改为 0, 0, 1, 1, 2, 3,
 * 3。不需要考虑数组中超出新长度后面的元素。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 3 * 10^4
 * -10^4 <= nums[i] <= 10^4
 * nums 已按升序排列
 * 
 * 
 */

#include <iostream>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    // 做法一（推荐）：单写指针 i，拿 x 和「已保留区倒数第 k 个元素」nums[i-k] 比。
    // 数组有序，所以 nums[i-k] 是同值的最后一份配额；x 比它大 ⇒ 还没留够 k 个，必须收。
    // i < k 处理开头 k 个元素的边界。把 2 换成 k 就是通解（26 题 = k=1）。
    int removeDuplicates(vector<int>& nums) {
        const int k = 2;
        int i = 0;
        for (int x : nums)
        {
            // 判断是否不等于，这个动作表示需要收下这个数值。
            // 相反，相等的值，什么都没做，直接跳过了这轮循环，等于是丢弃了
            // i代表要保留的数量
            if (i < k || x != nums[i - k])
            {
                nums[i++] = x;   // 直接覆盖即可，题目只要求前 i 个正确，不需要 swap
            }
        }
        return i;
    }

    // 做法一的泛化版：最多保留 k 个重复项
    int removeDuplicatesK(std::vector<int>& nums, int k) {
        int i = 0;
        for (int x : nums)
        {
            if (i < k || x != nums[i - k])
            {
                nums[i++] = x;
            }
        }
        return i;
    }

    // 做法二：显式计数。count 记录当前值已连续出现的次数，超过 2 就跳过。
    // 注意比较对象是 nums[i-1]（已保留区的最后一个），而不是 nums[i+1]。
    int removeDuplicatesByCount(std::vector<int>& nums) {
        int i = 0;
        int count = 0;
        for (int x : nums)
        {
            if (i == 0 || x != nums[i - 1])
            {
                count = 1;       // 遇到新值，计数重置
            }
            else
            {
                count++;
            }
            if (count <= 2)
            {
                nums[i++] = x;
            }
        }
        return i;
    }

    // 做法三：经典快慢指针（下标版）。思路同做法一，只是把读写拆成两个下标。
    // slow/fast 都从 k 起步，天然跳过前 k 个元素，少一次边界判断。
    int removeDuplicatesByTwoPointers(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n <= 2) return n;
        int slow = 2;
        for (int fast = 2; fast < n; fast++)
        {
            if (nums[fast] != nums[slow - 2])
            {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
// @lc code=end

// 三种做法本质相同：O(n) 时间 / O(1) 额外空间。
// 反例说明为什么不能沿用 26 题的 swap 双指针：
//   [1,1,1,1]  -> swap 版本返回 1（应为 2），因为 i 从头到尾没动过
//   [1,2,2]    -> swap 版本返回 2（应为 3），nums[i]==nums[i+1] 判不出是否已留够 2 个
//   [1,1,1,2,2,3] -> swap 版本返回 4（应为 5），swap 把待处理区搅乱了

static void check(std::vector<int> nums)
{
    Solution s;

    std::vector<int> a = nums, b = nums, c = nums;
    int lenA = s.removeDuplicates(a);
    int lenB = s.removeDuplicatesByCount(b);
    int lenC = s.removeDuplicatesByTwoPointers(c);

    std::cout << "[";
    for (int i = 0; i < lenA; i++)
    {
        std::cout << a[i] << (i + 1 == lenA ? "" : ",");
    }
    std::cout << "]  len=" << lenA;

    bool ok = (lenA == lenB) && (lenA == lenC);
    for (int i = 0; ok && i < lenA; i++)
    {
        ok = (a[i] == b[i]) && (a[i] == c[i]);
    }
    std::cout << (ok ? "  OK" : "  MISMATCH") << std::endl;
}

int main()
{
    check({1, 1, 1, 2, 2, 3});          // 5, [1,1,2,2,3]
    check({0, 0, 1, 1, 1, 1, 2, 3, 3}); // 7, [0,0,1,1,2,3,3]
    check({1});                         // 1, [1]
    check({1, 1});                      // 2, [1,1]
    check({1, 1, 1, 1});                // 2, [1,1]
    check({1, 2, 2});                   // 3, [1,2,2]
    check({1, 1, 2, 2, 3, 3, 4});       // 7, [1,1,2,2,3,3,4]
    return 0;
}
