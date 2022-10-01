#pragma once

#include <cmath>
#include <concepts>
#include <functional>
#include <iomanip>
#include <set>
#include <string>
#include <utility>
#include <vector>

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
    std::function<void()> backward;
    std::set<std::pair<Value, Value>, Comparator> prev;
    char op;
    std::string label;

   public:
    Value() = default;
    Value(T _data, std::pair<Value, Value> _prev = {Value(), Value()}, char _op = '\0') {
        data = _data;
        grad = 0.0;
        prev.insert(_prev);
        op = _op;
        label = "";

        if (_prev.first.data != T() && _prev.second.data != T()) {
            switch (op) {
                case '+':
                    backward = [&_prev, this]() { _prev.first.grad += grad; _prev.second.grad += grad; };
                    break;
                case '*':
                    backward = [&_prev, this]() { _prev.first.grad += _prev.second.data * grad; _prev.second.grad += _prev.first.data * grad; };
                    break;
                default:
                    break;
            }
        }
    }

    Value(const Value<T>& rhs) : data(rhs.data), op(rhs.op) {}

    const Value<T>& operator=(const Value<T>& rhs) {
        this->data = rhs.data;
        this->op = rhs.op;
        return *this;
    }

    friend Value operator+(const Value& lhs, const Value& rhs) {
        return Value(lhs.data + rhs.data, std::make_pair(lhs, rhs), '+');
    }

    friend Value operator-(const Value& lhs, const Value& rhs) {
        return Value(lhs.data - rhs.data, std::make_pair(lhs, rhs), '-');
    }

    friend Value operator*(const Value& lhs, const Value& rhs) {
        return Value(lhs.data * rhs.data, std::make_pair(lhs, rhs), '*');
    }

    friend Value operator/(const Value& lhs, const Value& rhs) {
        return Value(lhs.data / rhs.data, std::make_pair(lhs, rhs), '/');
    }

    bool operator!() const {
        return this->data == T();
    }

    Value pow(T _e) {
        return Value(std::pow(this->data, _e), std::make_pair(*this, Value(_e)), '^');
    }

    T get_data() const {
        return data;
    }

    std::set<std::pair<Value, Value>, Comparator> get_prev() const {
        return prev;
    }

    char get_op() const {
        return op;
    }

    void set_label(const std::string _label) {
        label = _label;
    }

    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        os << std::fixed;
        os << std::setprecision(2);

        if (v.label != "") {
            os << "Value " << v.label << " (data = " << v.data << ", grad = " << v.grad << ")";
        } else {
            os << "Value (data = " << v.data << ", grad = " << v.grad << ")";
        }

        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const std::set<std::pair<Value, Value>, Comparator>& sp) {
        for (auto const& it : sp) {
            os << "{" << it.first << ", " << it.second << "}";
        }
        return os;
    }
};

}  // namespace latte