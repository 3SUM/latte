#pragma once

#include <string>

namespace speedy {

template <class T>
class Value {
   private:
    T data;
    std::string op;

   public:
    Value() = delete;
    Value(T _data) : data(_data), op("") {}
    Value(T _data, std::string _op) : data(_data), op(_op) {}
};

}  // namespace speedy