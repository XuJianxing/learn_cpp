#include <iostream>

size_t i = 1;

int main()
{
    // ���������
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

    // �ַ������ʼ����������ַ�������ֵ��ʼ���ַ����飬���Զ���ӿ��ַ���ĩβ��
    char a1[] = { 'C', '+', '+' };  // �б��ʼ�����޿��ַ�
    char a2[] = { 'C', '+', '+', '\0' };  // �ֶ��ӿ��ַ�
    char a3[] = "C++";  // �Զ���ӿ��ַ���ĩβ
    char a4[4] = "C++";  // �ַ����鳤��Ϊ4
    // ���3 4 4 4��
    std::cout << sizeof(a1) << " " << sizeof(a2) << " " << sizeof(a3) << " " << sizeof(a4) << std::endl;

    // �����ڱ�׼��û�п������죺
    int a5[] = { 1, 2, 3 };
    // int bad_a6[] = a5;  // û�����鿽����ֵ
    auto a6 = a5;  // a6��int*���ͣ���a5�ĵ�ַ
    std::cout << a6 << " " << *a6 << std::endl;

    // ������������������������η���������һ�ΰ󶨣�
    int* a7[10];  // ��СΪ10�����飬������ָ��int��ָ��
    // int&  bad_refs[10];  // ������ʹ�����õ�����
    // Parrayָ��һ������10������������ ������ӵ���ⷽʽ��Parray��һ��ָ�룬ָ���СΪ10��int���͵����飺
    int(*Parray)[10] = &arr;
    // arrRef����һ������10������������ arrRef��һ�����ã����õĶ�����һ����СΪ10��int���͵����飺
    int(&arrRef)[10] = arr;
    // ParrRef��һ����������ã������ں���10��ָ�루���ֿ��Դ���������ֿ�ʼ���������˳���Ķ������䣩
    int* (&ParrRef)[10] = a7;
    size_t i = 2;
}
