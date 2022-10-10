#pragma once

#include <chrono>
#include <concepts>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>

namespace latte {

template <typename T>
requires std::integral<T> || std::floating_point<T>
class Tensor {
   private:
    T* data;
    size_t rows;
    size_t cols;

   public:
    Tensor() = default;
    Tensor(size_t _rows, size_t _cols, T* _data = nullptr) {
        rows = _rows;
        cols = _cols;
        data = new T[rows * cols];

        if (_data) {
            std::memcpy(data, _data, rows * cols * sizeof(T));
        } else {
            memset(data, {}, rows * cols * sizeof(T));
        }
    }

    ~Tensor() {
        if (data) {
            delete data;
        }

        rows = 0;
        cols = 0;
        data = nullptr;
    }

    Tensor(const Tensor<T>& rhs) {
        rows = rhs.rows;
        cols = rhs.cols;
        data = new T[rows * cols];

        if (rhs.data) {
            std::memcpy(data, rhs.data, rows * cols * sizeof(T));
        } else {
            memset(data, {}, rows * cols * sizeof(T));
        }
    }

    const Tensor<T>& operator=(const Tensor<T>& rhs) {
        this->rows = rhs.rows;
        this->cols = rhs.cols;

        if (this->data) {
            delete data;
        }

        this->data = new T[this->rows * this->cols];
        if (rhs.data) {
            std::memcpy(this->data, rhs.data, this->rows * this->cols * sizeof(T));
        } else {
            memset(this->data, {}, this->rows * this->cols * sizeof(T));
        }

        return *this;
    }

    size_t get_rows() const {
        return rows;
    }

    size_t get_cols() const {
        return cols;
    }

    T* get_data() const {
        return data;
    }

    static Tensor zeros(size_t _rows, size_t _cols) {
        Tensor tensor = Tensor(_rows, _cols);
        for (size_t i = 0; i < _rows * _cols; i++) {
            tensor.data[i] = {};
        }
        return tensor;
    }

    static Tensor rand(size_t _rows, size_t _cols) {
        if (!std::is_floating_point<T>::value) {
            std::cout << "ERROR! Tensor::rand only supports floating-point types." << std::endl;
            return zeros(_rows, _cols);
        }

        Tensor tensor = Tensor(_rows, _cols);

        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto mt_rand = std::bind(std::uniform_real_distribution<T>(0, 1), std::mt19937(seed));
        for (size_t i = 0; i < _rows * _cols; i++) {
            tensor.data[i] = mt_rand();
        }
        return tensor;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tensor& t) {
        os << std::fixed << std::setprecision(4);
        for (size_t i = 0; i < t.rows * t.cols; i++) {
            if (i % t.cols == 0 && i != 0) {
                os << std::endl;
            }
            os << t.data[i] << " ";
        }
        return os;
    }
};

}  // namespace latte