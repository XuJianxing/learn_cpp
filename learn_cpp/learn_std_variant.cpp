#include <iostream>
#include <variant>

int main(int argc, char **argv) {
    std::variant<int, double> myVariant = 42;

    int intValue = std::get<int>(myVariant);
    std::cout << "Integer value: " << intValue << std::endl;

    myVariant = 3.14;

    // 使用 std::get 获取 double 类型的值
    double doubleValue = std::get<double>(myVariant);
    std::cout << "Double value: " << doubleValue << std::endl;

    myVariant = 42;

    if (std::holds_alternative<int>(myVariant)) {
        int intValue = std::get<int>(myVariant);
        std::cout << "Integer holds_alternative value: " << intValue << std::endl;
    }
    return 0;
}

