#pragma once

#include <cmath>
#include <concepts>
#include <string>

namespace speedy {

template <typename T>
requires std::integral<T> || std::floating_point<T>
class Value {
   private:
    T data{};
    std::string op;

   public:
    Value() {};
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

    Value operator-(const Value& rhs) {
        return Value(this->data - rhs.data, "-");
    }

    Value operator*(const Value& rhs) {
        return Value(this->data * rhs.data, "*");
    }

    Value operator/(const Value& rhs) {
        return Value(this->data / rhs.data, "/");
    }

    bool operator!() const {
        return this->data == 0;
    }

    Value pow(T _e) {
        return Value(std::pow(this->data, _e), "**");
    }

    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        os << "Value (data = " << v.data << ")";
        return os;
    }
};

}  // namespace speedy