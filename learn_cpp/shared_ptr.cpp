#include <iostream>
#include <memory>

int main(int argc, char **argv) {

    // shared_ptr创建方法1 std::make_shared 
    std::shared_ptr<int> p = std::make_shared<int>(42);
    std::cout << "*p: " << *p << std::endl;

    *p = 54;
    {
        // shared_ptr创建方法2 直接构造
        std::shared_ptr<int> b(p);
        std::cout << "*b: " << *b << " *p: " << *p << std::endl;
        std::cout << "b: " << b << " b.use_count(): " << b.use_count() << std::endl;
        std::cout << "p: " << p << " p.use_count(): " << p.use_count() << std::endl;
        *b = 200;
    }

    std::cout << "*p: " << *p << std::endl;
    std::cout << "p.use_count(): " << p.use_count() << std::endl;

    return 0;
}

