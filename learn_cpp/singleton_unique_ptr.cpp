#include <memory>
#include <mutex>


class Singleton {
public:
    static Singleton& getInstance() {
        std::call_once(initFlag, []() {
            instance.reset(new Singleton());
        });
        return *instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // 确保在程序结束时销毁单例对象
    // 如果析构函数是私有的，那么在程序结束时，Singleton 对象将无法被销毁
    ~Singleton() {}

private:
    Singleton() {}

    static std::unique_ptr<Singleton> instance;
    static std::once_flag initFlag;
};

std::unique_ptr<Singleton> Singleton::instance;
std::once_flag Singleton::initFlag;

/*
解释
std::unique_ptr:
std::unique_ptr<Singleton> 用于管理单例对象的生命周期。std::unique_ptr 会在程序结束时自动销毁对象，从而避免内存泄漏。

std::once_flag 和 std::call_once:
std::once_flag 是一个标志，用于确保初始化代码只执行一次。
std::call_once 确保传递的初始化函数只会被执行一次，即使在多线程环境中也是如此。

getInstance 方法:
getInstance 方法使用 std::call_once 来确保 instance 只被初始化一次。
std::call_once 接受一个标志和一个初始化函数。初始化函数在第一次调用时执行，并且只执行一次。

优点
线程安全：std::call_once 和 std::once_flag 确保了初始化代码的线程安全性。
自动销毁：std::unique_ptr 确保了单例对象在程序结束时自动销毁，避免了内存泄漏。
*/

int main() {}

