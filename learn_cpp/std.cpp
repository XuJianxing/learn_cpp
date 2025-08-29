#include <iostream>
#include <cctype>
#include <ctype.h>
#include <string>
#include <vector>


// 用迭代器实现二分查找
std::vector<int>::const_iterator iterator_binary_search(const std::vector<int>& source, int sought)
{
    auto begin = source.begin();
    auto end = source.end();
    auto mid = source.begin() + (end - begin) / 2;
    while (mid != end && *mid != sought)
    {
        if (sought < *mid)
            end = mid;
        else
            begin = mid + 1;
        mid = begin + (end - begin) / 2;
    }
    return mid;
}

int main()
{
    // std::string:
    std::cout << "std::string:" << std::endl;;
    std::string s("你好!");
    std::cout << s.size() << std::endl;

    // std::vector
    std::cout << "std::vector:" << std::endl;
    std::vector<float> vec{0, 1, 2, 3};
    vec.push_back(4);
    std::cout << "size: " << vec.size() << " capacity: " << vec.capacity() << std::endl;

    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        *it = 2 **it;
    }
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << " ";
    }

    iterator_binary_search({}, 1);

    // std::cout << std::endl;
}
