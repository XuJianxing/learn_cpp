#include <iostream>
#include <memory>
#include <string>

class Foo {
public:
    Foo() = default;
    Foo(int x) : x(x) {}

private:
    int x;
};

int main(int argc, char **argv) {
    // unique_ptr创建方法1 make_unique 
    std::unique_ptr<int> p1 = std::make_unique<int>(42);
    std::cout << "*p1: " << *p1 << std::endl;

   // unique_ptr创建方法2 std::move 
    std::unique_ptr<std::string> p2 = std::make_unique<std::string>("hello");
    std::unique_ptr<std::string> p2_2 = std::move(p2);

    // unique_ptr创建方法3 new
    std::unique_ptr<Foo> p3(new Foo());
    std::unique_ptr<Foo> p4 = std::make_unique<Foo>(Foo());

    // unique_ptr创建方法4 创建数组对象
    std::unique_ptr<Foo[]> p5(new Foo[10]);
    std::unique_ptr<Foo[]> p6 = std::make_unique<Foo[]>(10);

    std::string *s = new std::string("hello");
    return 0;
}

