// g++ -std=c++20 -O3 main.cpp && ./a.out
#include <iostream>

#include "engine.hpp"

using namespace latte;

int main() {
    Value a(2.0);
    Value b(-3.0);
    Value c(10.0);
    Value d = a * b + c;
    Value e = d.pow(2);
    d.set_label("d");
    e.set_label("e");
    std::cout << d << std::endl;
    std::cout << d.get_prev() << std::endl;
    std::cout << e << std::endl;
    std::cout << e.get_prev() << std::endl;
    return 0;
}
