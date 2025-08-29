#include <iostream>

size_t i = 1;

int main()
{
    // 数组的声明
    constexpr int count = 42;
    const int ct = 42;
    unsigned int cnt = 42;
    constexpr unsigned int size = 42;
    int arr[10];
    int right[count];
    int right2[ct];
    // int bad[cnt];
    int ial1[ct] = { 1, 2, 3 };
    int ia2[] = { 1, 2, 3 };

    // 字符数组初始化（如果用字符串字面值初始化字符数组，会自动添加空字符到末尾）
    char a1[] = { 'C', '+', '+' };  // 列表初始化，无空字符
    char a2[] = { 'C', '+', '+', '\0' };  // 手动加空字符
    char a3[] = "C++";  // 自动添加空字符到末尾
    char a4[4] = "C++";  // 字符数组长度为4
    // 输出3 4 4 4：
    std::cout << sizeof(a1) << " " << sizeof(a2) << " " << sizeof(a3) << " " << sizeof(a4) << std::endl;

    // 数组在标准里没有拷贝构造：
    int a5[] = { 1, 2, 3 };
    // int bad_a6[] = a5;  // 没有数组拷贝赋值
    auto a6 = a5;  // a6是int*类型，是a5的地址
    std::cout << a6 << " " << *a6 << std::endl;

    // 复杂数组的声明：（类型修饰符从右向左一次绑定）
    int* a7[10];  // 大小为10的数组，类型是指向int的指针
    // int&  bad_refs[10];  // 不允许使用引用的数组
    // Parray指向一个含有10个整数的数组 这个句子的理解方式：Parray是一个指针，指向大小为10的int类型的数组：
    int(*Parray)[10] = &arr;
    // arrRef引用一个含有10个整数的数组 arrRef是一个引用，引用的对象是一个大小为10的int类型的数组：
    int(&arrRef)[10] = arr;
    // ParrRef是一个数组的引用，数组内含有10个指针（这种可以从数组的名字开始由内向外的顺序阅读这个语句）
    int* (&ParrRef)[10] = a7;
    size_t i = 2;
}
