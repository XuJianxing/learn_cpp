#include <atomic>
#include <mutex>

/*
内存模型和指令重排序
需要注意的是，双重检查锁定在某些情况下可能会受到内存模型和指令重排序的影响。在某些编译器和硬件平台上，编译器和处理器可能会对指令进行重排序，从而导致双重检查锁定失效。

为了解决这个问题，可以使用C++11引入的std::atomic和内存序（memory order）来确保内存操作的顺序性和可见性。
*/
class Singleton {
public:
    static Singleton* getInstance() {
        Singleton* temp = instance.load(std::memory_order_acquire);
        if (temp == nullptr) { // 第一次检查
            std::lock_guard<std::mutex> lock(mutex);
            temp = instance.load(std::memory_order_relaxed);
            if (temp == nullptr) { // 第二次检查
                temp = new Singleton();
                instance.store(temp, std::memory_order_release);
            }
        }
        return temp;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {}
    ~Singleton() {}

    static std::atomic<Singleton*> instance;
    static std::mutex mutex;
};

std::atomic<Singleton*> Singleton::instance(nullptr);
std::mutex Singleton::mutex;

int main() {}

