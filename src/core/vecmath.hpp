#pragma once
#include <cmath>
#include <string>
#include <cassert>

namespace tfrt {

    template <template <typename> class Child, typename T>
    class Tuple2 {
        public:
        T x{}, y{};

        Tuple2() = default;
        Tuple2(T x, T y) : x(x), y(y) {}

        static const int nDimensions = 2;

        template <typename U>
        auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})> {
            return {x + c.x, y + c.y};
        }

        template <typename U>
        Child<T>& operator+=(Child<U> c) {
            x += c.x;
            y += c.y;
            return static_cast<Child<T>&>(*this);
        }

        template <typename U>
        auto operator-(Child<U> c) const -> Child<decltype(T{} - U{})> {
            return {x - c.x, y - c.y};
        }

        template <typename U>
        Child<T>& operator-=(Child<U> c) {
            x -= c.x;
            y -= c.y;
            return static_cast<Child<T>&>(*this);
        }

        bool operator==(Child<T> c) const { return x == c.x && y == c.y; }
        bool operator!=(Child<T> c) const { return x != c.x || y != c.y; }

        template <typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})> {
            return {s * x, s * y};
        }

        template <typename U>
        Child<T>& operator*=(U s) {
            x *= s;
            y *= s;
            return static_cast<Child<T>&>(*this);
        }

        template <typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})> {
            return {x / d, y / d};
        }

        template <typename U>
        Child<T> &operator/=(U d) {
            x /= d;
            y /= d;
            return static_cast<Child<T>&>(*this);
        }

        Child<T> operator-() const { return {-x, -y}; }

        T operator[](int i) const {
            // Consider replacing assert with dcheck for runtime diagnostics in the future
            assert(i >= 0 && i <= 1);
            return (i == 0) ? x : y;
        }
 
        T& operator[](int i) {
            assert(i >= 0 && i <= 1);
            return (i == 0) ? x : y;
        }

        std::string ToString() const { return "x:" + std::to_string(x) + ",y:" + std::to_string(y); }
    };

    template <template <typename> class Child, typename T>
    class Tuple3{
        public:
        T x{}, y{}, z{};

        // constructor
        Tuple3() = default;
        Tuple3(T x, T y, T z) : x(x), y(y), z(z) {};

        // static dimension
        static const int nDimensions = 3;

        // plus operator
        template <typename U>
        auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})> {
            return {x + c.x, y + c.y, z + c.z};
        }

        template <typename U>
        Child<T>& operator+=(Child<U> c) {
            x += c.x;
            y += c.y;
            z += c.z;
            return static_cast<Child<T>&>(*this);
        }
        
        // index operator
        T operator[](int i) const {
            assert(i >= 0 && i <= 2);
            if (i == 0) return x;
            if (i == 1) return y;
            return z;
        }

        T& operator[](int i) {
            assert(i >= 0 && i <= 2);
            if (i == 0) return x;
            if (i == 1) return y;
            return z;
        }

        // minus operator
        template <typename U>
        auto operator-(Child<U> c) const -> Child<decltype(T{} - U{})> {
            return {x - c.x, y - c.y, z - c.z};
        }

        template <typename U>
        Child<T>& operator-=(Child<U> c) {
            x -= c.x;
            y -= c.y;
            z -= c.z;
            return static_cast<Child<T>&>(*this);
        }

        // equality operators
        template <typename U>
        bool operator==(Child<T> c) const { return x == c.x && y == c.y && z == c.z; }

        template <typename U>
        bool operator!=(Child<T> c) const { return x != c.x || y != c.y || z != c.z; }

        // multiply operator
        template <typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})> {
            return {x * s, y * s, z * s};
        }
        
        template <typename U>
        Child<T>& operator*=(U s) {
            x *= s;
            y *= s;
            z *= s;
            return static_cast<Child<T>&>(*this);
        }

        // division operator
        template <typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})> {
            return {x / d, y / d, z / d};
        }

        template <typename U>
        Child<T>& operator/=(U d) {
            x /= d;
            y /= d;
            z /= d;
            return static_cast<Child<T>&>(*this);
        }

        // negate operator
        Child<T> operator-() const { return {-x, -y, -z}; }

        // to string
        std::string ToString() const { 
            return "x:" + std::to_string(x) + ",y:" + std::to_string(y) + ",z:" + std::to_string(z); 
        }
    };
}