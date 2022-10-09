// g++ -std=c++20 -O3 main.cpp && ./a.out
#include <iostream>

#include "engine.hpp"

using namespace latte;

int main() {
    Value a(2.0);
    Value b(-3.0);
    Value c(10.0);
    Value d = a * b + c;
    d.set_label("d");
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << d.get_prev() << std::endl;
    return 0;
}
