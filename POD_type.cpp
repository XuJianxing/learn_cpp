#include <iostream>

struct MyPodType {
    int a;
    char b;
    /* 加了自定义构造函数以后，就不是POD类型了
    MyPodType(int aa, char bb)
    {
        a = aa;
        b = bb;
    }
    */
};

typedef int StandardLayout3[10];

static_assert(std::is_pod<MyPodType>::value, "MyPodType should be a POD type");

int main()
{
    std::cout << "POD type" << std::endl;
    StandardLayout3 sd{1,2,3,4,5,6,7,8,9,0};
    std::cout << sizeof(sd) << std::endl;
    std::cout << sizeof(sd[1]) << std::endl;
    return 0;
}
