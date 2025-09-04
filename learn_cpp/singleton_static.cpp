
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance; // 线程安全的静态局部变量
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {}
    ~Singleton() {}
};

/*
线程安全的静态局部变量初始化
在C++11之前，静态局部变量的初始化在多线程环境中可能会导致竞争条件（race condition）。多个线程可能会同时尝试初始化同一个静态局部变量，从而导致未定义行为。

C++11标准通过引入以下保证来解决这个问题：

原子性：静态局部变量的初始化是原子操作。编译器会确保在任何时刻，只有一个线程能够执行静态局部变量的初始化代码。
一次性：静态局部变量的初始化只会被执行一次。即使有多个线程同时访问该变量，初始化代码也只会被执行一次，其他线程会等待初始化完成。
*/

int main() {}

