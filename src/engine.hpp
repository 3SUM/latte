#pragma once

#include <string>

namespace speedy {

template <class T>
class Value {
   private:
    T data;
    std::string op;

   public:
    Value(T _data) : data(_data), op("") {}
    Value(T _data, std::string _op) : data(_data), op(_op) {}
    Value(const Value<T>& rhs) : data(rhs.data), op(rhs.op) {}

    const Value<T>& operator=(const Value<T>& rhs) {
        this->data = rhs.data;
        this->op = rhs.op;
        return *this;
    }

    Value operator+(const Value& rhs) {
        return Value(this->data + rhs.data, "+");
    }

    Value operator*(const Value& rhs) {
        return Value(this->data * rhs.data, "*");
    }

    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        os << "Value (data = " << v.data << ")";
        return os;
    }
};

}  // namespace speedy