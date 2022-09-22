#include <iostream>
#include "engine.hpp"

using namespace speedy;

int main() {
    Value<int> a(10);
    Value<int> b(15);
    Value<int> c = a + b;
    Value<int> d(c);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    return 0;
}
