#include <functional>
#include <iostream>

#include "incubate/bind_first.hpp"

void print2(int a, int b) {
  std::cout << a << std::endl;
  std::cout << b << std::endl;
}

void print3(int a, int b, int c) {
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
}

int main() { 
  auto a = BindFirst_cpp11(print2, 1); // std::bind(print2, 1, std::placeholders::_1);
  auto b = BindFirst_cpp11(print3, 1); // std::bind(print3, 1, std::placeholders::_1, std::placeholders::_2);
  a(2);
  b(2,3);
  auto c = BindFirst_cpp14(print2, 1);
  auto d = BindFirst_cpp14(print3, 1);
  c(2);
  d(2,3);
}
