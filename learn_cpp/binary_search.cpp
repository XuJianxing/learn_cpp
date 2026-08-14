#include <iostream>
#include <vector>

/*
    二分法常见写法模板
    模板 A：left < right 搭配 right = mid（lower_bound，找第一个 >= target 的位置）
    模板 B：left <= right 搭配 right = mid - 1（lower_bound 的闭区间写法）
    模板 C：纯二分查找（精确查找 target，找到返回下标，找不到返回 -1）
        闭区间写法 [left, right]
        开区间写法 [left, right)
*/
int lower_bound1(std::vector<int> arr, int target)
{
    int left = 0, right = arr.size();           // 注意 right 初始是 n，不是 n-1
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;  // a[mid] 一定不是答案，排除
        else right = mid;                       // a[mid] 可能是答案，不能排除！
    }
    return left;  // 退出时 left == right，恰好是第一个 >= target 的下标
}

int lower_bound2(std::vector<int> arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;                 // 这里用 mid-1 是合法的
    }
    return left;  // 退出时 left = right + 1，也恰好是第一个 >= target 的下标
}

// 模板 C：纯二分查找（精确查找）
// 找到 target 返回其下标；找不到返回 -1。

// 闭区间写法：搜索范围 [left, right]，两端都包含
int binary_search_closed(std::vector<int> arr, int target)
{
    int left = 0, right = arr.size() - 1;   // [left, right]
    while (left <= right) {                 // 区间非空才继续
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;                      // 找到，直接返回
        else if (arr[mid] < target)
            left = mid + 1;                  // target 在右半区
        else
            right = mid - 1;                 // target 在左半区（mid 已排除）
    }
    return -1;                               // 区间为空，说明不存在
}

// 开区间写法：搜索范围 [left, right)，左闭右开
int binary_search_open(std::vector<int> arr, int target)
{
    int left = 0, right = arr.size();        // [left, right)，right 是越界下标
    while (left < right) {                   // 区间非空才继续
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;                      // 找到，直接返回
        else if (arr[mid] < target)
            left = mid + 1;                  // target 在右半区
        else
            right = mid;                     // target 在左半区，right 本身已不含 mid
    }
    return -1;                               // 区间为空，说明不存在
}

int main()
{
    // 二分查找的前提：数组必须有序（非降序）
    std::vector<int> arr{1,2,2,2,3,4,4,5,6,7,8};

    // 注意：这两个模板是 lower_bound，返回"第一个 >= target"的下标，不是精确查找
    std::cout << lower_bound1(arr, 2) << std::endl;  // 1（第一个 2 的下标，而非任意 2）
    std::cout << lower_bound1(arr, 3) << std::endl;  // 4
    std::cout << lower_bound2(arr, 0) << std::endl;  // 0（所有元素都 >= 0）
    std::cout << lower_bound1(arr, 9) << std::endl;  // 11（= size，说明不存在，都 < 9）
    std::cout << lower_bound2(arr, 4) << std::endl;  // 5

    // 纯二分查找：精确查找（闭区间 + 开区间）
    std::cout << binary_search_closed(arr, 4) << std::endl;  // 5（找到，返回下标）
    std::cout << binary_search_open(arr, 1)   << std::endl;  // 0
    std::cout << binary_search_closed(arr, 9) << std::endl;  // -1（不存在）
    std::cout << binary_search_open(arr, 9)   << std::endl;  // -1（不存在）
    std::cout << binary_search_closed(arr, 2) << std::endl;  // 多个 2 时返回哪一个由二分路径决定，不固定
    std::cout << binary_search_open(arr, 2)   << std::endl;
    return 0;
}
