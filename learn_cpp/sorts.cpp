#include <iostream>
#include <vector>

/*
记录各种排序算法
*/

/*
1. 快排：partition + 递归左右子区间
partition做的事情是把当前选择的一个数，放到他该放的位置，并且左边都不大于他，右边都不小于他
然后递归左右子区间
*/
int partition(std::vector<int>& nums, int left, int right) {
    int pivot = nums[left];

    while (left < right) {
        while (left < right && nums[right] >= pivot) {
            --right;
        }
        nums[left] = nums[right];

        while (left < right && nums[left] <= pivot) {
            ++left;
        }
        nums[right] = nums[left];
    }

    nums[left] = pivot;
    return left; // pivot 的最终位置
}

void quickSort(std::vector<int>& nums, int left, int right) {
    if (left >= right) {
        return;
    }

    int p = partition(nums, left, right);

    quickSort(nums, left, p - 1);
    quickSort(nums, p + 1, right);
}

/*
引申出的“快速选择”算法：快速找到第k个位置的数应该是几，并且前面都不大于，后面都不小于
也就是 C++ 20 的 std::ranges::nth_element

std::nth_element(costs.begin(), costs.begin() + k, costs.end());

std::ranges::nth_element(costs, costs.begin() + k);
执行后 costs[k] 是排序后应该位于第 k 个位置的元素
*/
int quickSelect(std::vector<int>& nums, int k) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left <= right) {
        int p = partition(nums, left, right);

        if (p == k) {
            return nums[p];
        }

        if (k < p) {
            right = p - 1;
        } else {
            left = p + 1;
        }
    }

    throw std::out_of_range("k");
}
