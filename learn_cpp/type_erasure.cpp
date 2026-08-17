/*
一、问题： std::function<void(int)> 为什么能装下完全不同类型的可调用对象？

std::function<void(int)> f;
f = somFunc;                    // 函数指针类型
f = [x](int){ ... };            // lambda类型（每个都不同）
f = Functor{};                  // 仿函数类型

这些对象类型各不相同、大小各异，却能存进同一个 function 里。这就是类型擦除——"擦除"掉具体类型，只保留统一的调用接口。

二、核心思想：多态 + 统一接口
类型擦除的本质是用继承多态隐藏具体类型


类型擦除的核心机制：

要素		作用						对应代码
抽象基类	定义统一调用接口				CallableBase::call()
模板派生类	包装具体类型，"记住"真实类型	CallableImpl<F>
基类指针	对外只暴露统一接口，隐藏类型	CallableBase* ptr

构造时: 具体类型F → new CallableImpl<F> → 存进基类指针 (擦除类型)
调用时: 基类指针 → 虚函数call() → 多态调用回真实对象 (还原调用)

类型擦除是C++实现"运行时多态但不需要共同基类"的重要手段。
*/
#include <iostream>

// 目标：模拟 std::function<void(int)>，手写一个简化的 std::function
class MyFunction {
    // ===== 1. 抽象基类：统一的调用接口 =====
    struct CallableBase {
        virtual void call(int) = 0;          // 统一调用接口
        virtual CallableBase* clone() = 0;   // 用于拷贝
        virtual ~CallableBase() = default;
    };

    // ===== 2. 模板派生类：包装具体类型 =====
    template<typename F>
    struct CallableImpl : CallableBase {
        F func;   // 存放真正的可调用对象（类型被封装在这）
        
        CallableImpl(F f) : func(f) {}
        
        void call(int x) override {
            func(x);        // 调用真实对象
        }
        CallableBase* clone() override {
            return new CallableImpl(func);
        }
    };

    CallableBase* ptr = nullptr;   // 只持有基类指针（类型被擦除！）

public:
    // ===== 3. 模板构造：接受任意可调用对象 =====
    template<typename F>
    MyFunction(F f) {
        ptr = new CallableImpl<F>(f);  // 具体类型F在此被"装箱"
    }

    // ===== 4. 统一调用 =====
    void operator()(int x) {
        ptr->call(x);   // 通过虚函数多态调用
    }

    ~MyFunction() { delete ptr; }
    // (拷贝、移动构造略)
};

void func(int x) { std::cout << "函数:" << x << std::endl; }

int main() {
    MyFunction f1 = func;                       // 装函数
    MyFunction f2 = [](int x){ std::cout << "lambda:" << x << " " << std::endl; };  // 装lambda
    int a = 123;
    MyFunction f3 = [a](int x){ std::cout << "lambda:" << x << " " << a << std::endl; };  // 装带捕获lambda
    
    f1(10);   // 函数:10
    f2(20);   // lambda:20
    f3(30);
}
