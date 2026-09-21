#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

/*
std::condition_variable 是条件变量，用于让一个线程等待某个条件成立，另一个线程在条件成立后通知它。

它通常和 std::mutex 一起使用。

典型用途
比如：
生产者放入数据
消费者没数据时睡眠等待
有数据时生产者通知消费者

它解决什么问题？
没有条件变量时，你可能会写成：

while (q.empty()) {
    // 一直空转检查
}
这会浪费 CPU。

condition_variable 可以让线程：

1. 条件不满足时睡眠
2. 被通知后再醒来检查

关键点：
一定要配合“条件判断”使用：

cv.wait(lock, predicate);

因为条件变量可能有：
虚假唤醒（spurious wakeup）
所以不能单纯认为“被唤醒就一定有数据”。
*/

std::mutex mtx;
std::condition_variable cv;
std::queue<int> q;
bool done = false;

void producer()
{
    for (int i = 1; i <= 5; ++i)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            q.push(i);
        }
        cv.notify_one();
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_one();
}

void consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [] {
            return !q.empty() || done;
        });

        if (!q.empty())
        {
            int v = q.front();
            q.pop();
            std::cout << "consume: " << v << std::endl;
        }
        else if (done)
        {
            break;
        }
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}
