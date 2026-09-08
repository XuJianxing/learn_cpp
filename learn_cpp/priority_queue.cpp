#include <queue>
#include <vector>

/*
堆 笔记
*/

// 自定义结构的使用方式
struct Node {
    int id;
    int distance;
};

// 自定义数据结构的自定义比较器
struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        // 小顶堆
        return a.distance > b.distance;
    }
};

int main()
{
    // 默认是大顶堆，比较器是 std::less
    std::priority_queue<int> pq1;

    // 小顶堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>
    > pq2;

    std::priority_queue<Node, std::vector<Node>, Compare> pq3;

}
