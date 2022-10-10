// g++ -std=c++20 -O3 main.cpp && ./a.out
#include <iostream>

#include "tensor.hpp"

using namespace latte;

int main() {
    Tensor<float> A = Tensor<float>::rand(4, 4);
    Tensor<float> B = Tensor<float>::rand(4, 4);

    Tensor<float> A1 = A;
    Tensor<float> B1 = B;

    Tensor<int> A2 = Tensor<int>::zeros(2, 2);
    Tensor<float> B2 = Tensor<float>::zeros(2, 2);

    std::cout << "A\n"
              << A << "\n\n";
    std::cout << "A1\n"
              << A1 << "\n\n";
    std::cout << "B\n"
              << B << "\n\n";
    std::cout << "B1\n"
              << B1 << "\n\n";
    std::cout << "A2\n"
              << A2 << "\n\n";
    std::cout << "B2\n"
              << B2 << "\n\n";

    return 0;
}
