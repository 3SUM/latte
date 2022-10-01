#pragma once

#include <cmath>
#include <concepts>
#include <functional>
#include <set>
#include <string>
#include <utility>

namespace latte {

static_assert(sizeof(float) * CHAR_BIT == 32, "32-bit floats required!");

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
    float grad;
    std::function<void()> _backward;
    std::set<std::pair<Value, Value>, Comparator> prev;
    std::string op;

   public:
    Value() = default;
    Value(T _data, std::pair<Value, Value> _prev = {Value(), Value()}, std::string _op = "") {
        data = _data;
        grad = 0.0;
        prev.insert(_prev);
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

    T get_data() const {
        return data;
    }

    std::set<std::pair<Value, Value>, Comparator> get_prev() const {
        return prev;
    }

    std::string get_op() const {
        return op;
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

}  // namespace latte