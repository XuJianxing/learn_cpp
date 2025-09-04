#include <mutex>


/*
双重检查锁定 单例
*/
class Singleton {
public:
    static Singleton* getInstance() {
        if (instance == nullptr) { // 第一次检查
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) { // 第二次检查
                instance = new Singleton();
            }
        }
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {}
    ~Singleton() {}

    static Singleton* instance;
    static std::mutex mutex;
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

/*
为什么要检查两次

第一次检查（锁外检查）：

* 目的是为了避免不必要的加锁操作。
* 如果instance已经被初始化，直接返回实例，避免进入锁定区域，从而提高性能。
* 在大多数情况下，单例已经被创建，第一次检查可以避免锁的开销。

第二次检查（锁内检查）：
* 目的是为了确保线程安全。
* 当多个线程同时到达第一次检查并发现instance为nullptr时，它们会竞争进入锁定区域。
* 只有一个线程能够成功获取锁并进入锁定区域，其他线程会被阻塞。
* 第一个获取锁的线程会再次检查instance是否为nullptr，如果是，则创建实例。
* 其他被阻塞的线程在获取锁后，会发现instance已经被创建，从而避免重复创建实例。
*/

int main() {}

