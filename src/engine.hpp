#pragma once

#include <cmath>
#include <concepts>
#include <set>
#include <string>
#include <utility>

namespace speedy {

template <typename T>
requires std::integral<T> || std::floating_point<T>
class Value {
   private:
    struct Comparator {
        bool operator()(const std::pair<Value, Value>& lhs,
                        const std::pair<Value, Value>& rhs) const {
            if (lhs.first.data == rhs.first.data) {
                return lhs.second.data < rhs.second.data;
            } else {
                return lhs.first.data < rhs.first.data;
            }
        }
    };

    T data{};
    std::set<std::pair<Value, Value>, Comparator> prev;
    std::string op;

   public:
    Value()=default;
    Value(T _data, std::string _op = "") : data(_data), op(_op) {}
    Value(T _data, std::pair<Value, Value> _children, std::string _op) {
        data = _data;
        prev.insert(_children);
        op = _op;
    }

    Value(const Value<T>& rhs) : data(rhs.data), op(rhs.op) {}

    const Value<T>& operator=(const Value<T>& rhs) {
        this->data = rhs.data;
        this->op = rhs.op;
        return *this;
    }

    friend Value operator+(const Value& lhs, const Value& rhs) {
        return Value(lhs.data + rhs.data, std::make_pair(lhs, rhs), "+");
    }

    friend Value operator-(const Value& lhs, const Value& rhs) {
        return Value(lhs.data - rhs.data, std::make_pair(lhs, rhs), "-");
    }

    friend Value operator*(const Value& lhs, const Value& rhs) {
        return Value(lhs.data * rhs.data, std::make_pair(lhs, rhs), "*");
    }

    friend Value operator/(const Value& lhs, const Value& rhs) {
        return Value(lhs.data / rhs.data, std::make_pair(lhs, rhs), "/");
    }

    bool operator!() const {
        return this->data == T();
    }

    Value pow(T _e) {
        return Value(std::pow(this->data, _e), std::make_pair(*this, Value(_e)), "**" + std::to_string(_e));
    }

    std::set<std::pair<Value, Value>, Comparator> get_children() const {
        return prev;
    }

    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        os << "Value (data = " << v.data << ")";
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const std::set<std::pair<Value, Value>, Comparator>& sp) {
        for (auto const& it : sp) {
            os << "{" << it.first << ", " << it.second << "} ";
        }
        return os;
    }
};

}  // namespace speedy