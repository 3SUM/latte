#include <iostream>
#include "engine.hpp"

using namespace speedy;

int main() {
    Value<int> a(10);
    Value<int> b(15);
    Value<int> c(5);
    Value<int> d = a * b;
    Value<int> e = d / c;
    Value<int> f = e + 5 - 20;
    Value<int> h = f.pow(2);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << h << std::endl;
    return 0;
}
