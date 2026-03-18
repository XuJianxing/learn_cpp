// leetcode.cpp: 定义应用程序的入口点。
//

#include "leetcode.h"


#define CATCH_CONFIG_MAIN 1

int main()
{
    std::cout << "Hello CMake." << std::endl;
    std::cout << "ca: " << CATCH_CONFIG_MAIN << std::endl;
    #define CATCH_CONFIG_MAIN 2
    std::cout << "ca2: " << CATCH_CONFIG_MAIN << std::endl;
    double a = 0.1;
    double* p = &a;
    const int& b = a;
    return 0;
}
