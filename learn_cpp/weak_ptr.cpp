#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

/* 
下面的代码示例演示的案例是将 weak_ptr 用于确保正确删除具有循环依赖项的对象。 
在检查此示例时，假设仅在考虑替代解决方案后创建该示例。 这些 Controller 对象表示计算机进程的一些方面，它们独立运行。
每个控制器必须随时能够查询其他控制器的状态，每个控制器都包含一个专用 vector<weak_ptr<Controller>>，用于实现此目的。
每个向量都包含一个循环引用，因此，使用 weak_ptr 实例而不是 shared_ptr。
*/
class Controller
{
public:
    int Num;
    std::wstring Status;
    std::vector<std::weak_ptr<Controller>> others;
    explicit Controller(int i) : Num(i), Status(L"On")
    {
        std::wcout << L"Creating Controller" << Num << std::endl;
    }

    ~Controller()
    {
        std::wcout << L"Destroying Controller" << Num << std::endl;
    }

    // Demonstrates how to test whether the
    // pointed-to memory still exists or not.
    void CheckStatuses() const
    {
        for_each(others.begin(), others.end(), [](std::weak_ptr<Controller> wp) {
            auto p = wp.lock();
            if (p)
            {
                std::wcout << L"Status of " << p->Num << " = " << p->Status << std::endl;
            }
            else
            {
                std::wcout << L"Null object" << std::endl;
            }
        });
    }
};

void RunTest()
{
    std::vector<std::shared_ptr<Controller>> v{
       std::make_shared<Controller>(0),
       std::make_shared<Controller>(1),
       std::make_shared<Controller>(2),
       std::make_shared<Controller>(3),
       std::make_shared<Controller>(4),
    };

    // Each controller depends on all others not being deleted.
    // Give each controller a pointer to all the others.
    for (int i = 0; i < v.size(); ++i)
    {
        for_each(v.begin(), v.end(), [&v, i](std::shared_ptr<Controller> p) {
            if (p->Num != i)
            {
                v[i]->others.push_back(std::weak_ptr<Controller>(p));
                std::wcout << L"push_back to v[" << i << "]: " << p->Num << std::endl;
            }
        });
    }

    for_each(v.begin(), v.end(), [](std::shared_ptr<Controller> &p) {
        std::wcout << L"use_count = " << p.use_count() << std::endl;
        p->CheckStatuses();
    });
}

int main()
{
    RunTest();
    std::wcout << L"Press any key" << std::endl;
    char ch;
    std::cin.getline(&ch, 1);
}

