# std::priority_queue 优先队列（堆）笔记

## 一、基本概念

`std::priority_queue` 是 STL 中的**容器适配器（container adapter）**，不是真正的容器。它底层默认用 `std::vector` 实现一个**二叉堆**，特点是：队首（`top()`）始终是当前容器中"优先级最高"的元素。

- 头文件：`<queue>`
- 底层容器：默认 `std::vector<T>`
- 默认比较器：`std::less<T>`（大顶堆）

### 什么是容器适配器？

容器适配器 = 拿一个底层容器（如 `vector`/`deque`）+ 一套封装逻辑，改造成一个行为受限的、专门用途的数据结构（栈 / 队列 / 优先队列）。

- **适配（adapter）**：对已有容器做"包装改造"，让它对外表现出另一种数据结构的样子。
- **底层容器可选**：创建时由模板参数指定用哪个容器真正存数据。

STL 中的三个容器适配器：

| 适配器 | 底层容器 | 对外表现 |
|--------|----------|----------|
| `std::stack`（栈） | 默认 `deque`，可用 `vector`/`list` | 后进先出（LIFO） |
| `std::queue`（队列） | 默认 `deque`，可用 `list` | 先进先出（FIFO） |
| `std::priority_queue`（优先队列） | 默认 `vector`，可用 `deque` | 每次取优先级最高的元素 |

## 二、模板定义

```cpp
template<
    class T,                              // 元素类型
    class Container = std::vector<T>,     // 底层容器
    class Compare = std::less<T>          // 比较器
> class priority_queue;
```

## 三、四种使用方式

### 1. 默认大顶堆（内置类型）

```cpp
// 默认是大顶堆，比较器是 std::less
std::priority_queue<int> pq1;   // top() 返回最大值
```

### 2. 小顶堆（内置类型）

```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
// top() 返回最小值
```

### 3. pair 类型

```cpp
std::priority_queue<
    std::pair<int, int>,
    std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>
> pq2;   // 先按 first 比较，再按 second，取最小
```

### 4. 自定义类型 + 自定义比较器（重点）

```cpp
struct Node {
    int id;
    int distance;
};

// 自定义比较器：仿函数（重载 operator()）
// 名字叫什么无所谓，重点是可实例化、实例可调用
struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.distance > b.distance;  // 小顶堆
    }
};

std::priority_queue<Node, std::vector<Node>, Compare> pq3;
```

## 四、比较器规则（最容易混淆）

**priority_queue 的比较器语义与 `std::sort` 相反**：

| 比较器 | sort 效果 | priority_queue 效果 |
|--------|-----------|---------------------|
| `less`（默认） | 升序（小在前） | **大顶堆**（最大在 top） |
| `greater` | 降序（大在前） | **小顶堆**（最小在 top） |

记忆方式：比较器 `comp(a, b)` 返回 `true` 表示 `a` 的优先级"低于" `b`，即 `a` 应该排在 `b` 后面（更靠近堆底）。

```cpp
// 小顶堆：a > b 时，a 优先级更低 → a 放后面 → 小的在 top
bool operator()(const Node& a, const Node& b) const {
    return a.distance > b.distance;
}
```

## 五、常用操作

| 操作 | 说明 | 时间复杂度 |
|------|------|-----------|
| `push(x)` | 插入元素 | O(log n) |
| `emplace(args...)` | 原地构造并插入 | O(log n) |
| `pop()` | 移除队首（优先级最高）元素 | O(log n) |
| `top()` | 返回队首元素的引用（不删除） | O(1) |
| `empty()` | 是否为空 | O(1) |
| `size()` | 元素个数 | O(1) |

## 六、底层实现原理

`priority_queue` 本质是维护一个**二叉堆（binary heap）**，满足堆序性质（heap property）。

### 存储方式

用数组（`vector`）存储一棵**完全二叉树**，节点下标关系：

```
父节点：parent(i) = (i - 1) / 2
左孩子：left(i)   = 2 * i + 1
右孩子：right(i)  = 2 * i + 2
```

### 核心操作

- **push（插入）**：新元素放到数组末尾（`push_back`），然后执行**上浮（sift-up / percolate-up）**，与父节点比较并交换，直到满足堆序。
- **pop（删除队首）**：将堆顶与最后一个元素交换，删除末尾元素（`pop_back`），然后对新的堆顶执行**下沉（sift-down / percolate-down）**。

这两个操作各只需 O(log n) 次比较/交换，因为完全二叉树的高度是 log n。

## 七、常用场景

1. **Top K 问题**：求最大的 K 个元素 → 维护大小为 K 的**小顶堆**。
2. **第 K 大 / 第 K 小元素**（如 leetcode 215「数组中的第 K 个最大元素」）。
3. **Dijkstra 最短路径**：用小顶堆维护当前最短距离的节点（对应 `Node { id, distance }` 结构）。
4. **合并 K 个有序链表**。
5. **哈夫曼编码**：每次取两个最小权值节点。
6. **任务调度 / 定时器**：按时间排序，取最早到期的任务。

## 八、注意事项

- **没有迭代器，不能遍历**，只能访问 `top()` 元素。
- **不能随机访问**，没有 `operator[]` 和 `at()`。
- 若需要修改堆中某个元素的值，`priority_queue` 不直接支持，通常需要：删除重建，或用 `std::set` / `std::multiset` 替代，或在算法层面用「惰性删除」（配合外部标记数组）。
- 比较器 `operator()` 建议加 `const`。

## 九、容器适配器的两个关键问题

### 1. 如何屏蔽原有的函数能力？

关键在于：**适配器用"组合"（composition），而不是"继承"（inheritance）**。

```cpp
// 简化示意：priority_queue 内部是"持有"一个 vector，而不是"继承"它
template<class T, class Container = vector<T>, class Compare = less<T>>
class priority_queue {
private:
    Container c;          // ← 底层容器作为成员变量
    Compare comp;
public:
    // 只暴露这几个接口，其他 vector 的能力根本"不可见"
    void push(const T& x)      { c.push_back(x); /* 上浮 */ }
    void pop()                 { /* 交换+下沉 */ c.pop_back(); }
    const T& top() const       { return c.front(); }
    bool empty() const         { return c.empty(); }
    size_t size() const        { return c.size(); }
};
```

- 如果是 `public` 继承，父类（`vector`）的所有公共接口（`operator[]`、`begin()`、`at()` 等）都会自动暴露给子类。
- 但适配器把容器当作**私有成员变量**（`private: Container c;`），只在自己类里调用它，对外**只写有限的 `public` 成员函数**。
- 外部用户能调用的，只有适配器声明的那几个函数。

> 一句话：**继承会"全盘暴露"，组合则"想给什么才给什么"**。

### 2. 任何容器都可以用作底层容器吗？

**不是。** 每种适配器对底层容器有具体要求，必须满足特定接口能力，否则无法编译。

| 适配器 | 底层容器必须支持 | 可用容器 | 不可用原因 |
|--------|------------------|----------|-----------|
| `stack` | `push_back`、`pop_back`、`back` | `vector`、`deque`、`list` | 基本都行 |
| `queue` | `push_back`、`pop_front`、`front`、`back` | `deque`、`list` | `vector` 无 `pop_front` |
| `priority_queue` | 随机访问迭代器 + `front`、`push_back`、`pop_back` | `vector`（默认）、`deque` | `list` 只有双向迭代器 |

重点：`priority_queue` 内部靠堆算法维护顺序，而堆算法（`push_heap`/`pop_heap`）依赖**随机访问迭代器**（需要 O(1) 按下标访问、`i*2+1` 找孩子节点等）。因此：

- ✅ `vector`：随机访问迭代器，默认选择。
- ✅ `deque`：也提供随机访问迭代器，可用。
- ❌ `list`：只有双向迭代器，**无法随机访问**，不能用作 `priority_queue` 底层容器。
- ❌ 关联容器（`set`/`map`）、无序容器（`unordered_map`）等也不符合要求。

```cpp
#include <queue>
#include <list>
std::priority_queue<int, std::list<int>> pq; // 编译错误：list 不满足要求
```

> 一句话总结：**能用哪个容器取决于适配器需要哪些底层能力**，而 `priority_queue` 因依赖随机访问迭代器，基本只能选 `vector` 或 `deque`。
