#include <iostream>
#include "engine.hpp"

using namespace speedy;

int main() {
    Value a(10);
    Value b(15);
    Value c(5);
    Value d = a * b;
    Value e = d / c;
    Value f = e + 5 - 20;
    Value h = f.pow(2);
    Value<int> hh;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << h << std::endl;
    std::cout << hh << std::endl;

    // Due to c++20 concepts, Value class does not accept strings
    //Value<std::string> error;
    return 0;
}
