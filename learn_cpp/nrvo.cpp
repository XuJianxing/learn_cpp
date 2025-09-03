#include <iostream>

/*
 * NRVO:
 * 当一个函数的返回值是当前函数内的一个局部变量，且该局部变量的类型和返回值一致时，
 * 编译器会将该变量直接在函数的返回值接收处构造，不会发生拷贝和移动
*/

struct Noisy {
  Noisy() { std::cout << "constructed at " << this << '\n'; }
  Noisy(const Noisy&) { std::cout << "copy-constructed\n"; }
  Noisy(Noisy&&) { std::cout << "move-constructed\n"; }
  ~Noisy() { std::cout << "destructed at " << this << '\n'; }
};

Noisy f() {
  std::cout << "fff" << std::endl;
  Noisy v = Noisy();
  std::cout << "fffvvv" << std::endl;
  return v;
}

void g(Noisy arg) { std::cout << "&arg = " << &arg << '\n'; }

int main() {
  Noisy v = f();
  std::cout << "mainvf" << std::endl;
  g(f());
}

