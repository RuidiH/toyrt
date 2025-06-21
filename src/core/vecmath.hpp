#pragma once
#include <cmath>
#include <string>

#ifndef DCHECK
#ifdef NDEBUG
#define DCHECK(x) ((void)0)
#else
#include <cassert>
#define DCHECK(x) assert(x)
#endif
#endif

#ifndef DCHECK_NE
#define DCHECK_NE(a, b) DCHECK((a) != (b))
#endif

namespace tfrt
{

    using Float = float;

    inline bool IsNaN(float v) { return std::isnan(v); }

    template <template <class> class Child, typename T>
    class Tuple2
    {
    public:
        T x{}, y{};
        static const int nDimensions = 2;

    public:
        // constructors
        Tuple2() = default;
        Tuple2(T x, T y) : x(x), y(y) { DCHECK(!HasNaN()); }

        bool HasNaN() const { return IsNaN(x) || IsNan(y); }

        // addition
        template <typename U>
        auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})>
        {
            DCHECK(!c.HasNaN());
            return {x + c.x, y + c.y};
        }

        template <typename U>
        Child<T> &operator+=(Child<U> c)
        {
            DCHECK(!c.HasNaN());
            x += c.x;
            y += c.y;
            return static_cast<Child<T> &>(*this);
        }

        // substraction
        template <typename U>
        auto operator-(Child<U> c) const -> Child<decltype(T{} - U{})>
        {
            DCHECK(!c.HasNan());
            return {x - c.x, y - c.y};
        }

        template <typename U>
        Child<T> &operator-=(Child<U> c)
        {
            DCHECK(!c.HasNan());
            x -= c.x;
            y -= c.y;
            return static_cast<Child<T> &>(*this);
        }

        // equality
        bool operator==(Child<T> c) const { return x == c.x && y == c.y; }
        bool operator!=(Child<T> c) const { return x != c.x || y != c.y; }

        // multiplication by scalar
        template <typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})>
        {
            return {s * x, s * y};
        }

        template <typename U>
        Child<T> &operator*=(U s)
        {
            DCHECK(!IsNaN(s));
            x *= s;
            y *= s;
            return static_cast<Child<T> &>(*this);
        }

        // division by scalar
        template <typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})>
        {
            DCHECK(d != 0 && !IsNaN(d));
            return {x / d, y / d};
        }

        template <typename U>
        Child<T> &operator/=(U d)
        {
            DCHECK_NE(d, 0);
            DCHECK(!IsNaN(d));
            x /= d;
            y /= d;
            return static_cast<Child<T> &>(*this);
        }

        // negate
        Child<T> operator-() const { return {-x, -y}; }

        // index access
        T operator[](int i) const
        {
            DCHECK(i >= 0 && i <= 1);
            return (i == 0) ? x : y;
        }

        T &operator[](int i)
        {
            DCHECK(i >= 0 && i <= 1);
            return (i == 0) ? x : y;
        }

        std::string ToString() const { return "x:" + std::to_string(x) + ",y:" + std::to_string(y); }
    };

    template <template <class> class C, typename T, typename U>
    inline auto operator*(U s, Tuple2<C, T> t) -> C<decltype(T{} * U{})>
    {
        DCHECK(!t.HasNaN());
        return t * s;
    }

    template <template <class> class C, typename T>
    inline C<T> Abs(Tuple2<C, T> t)
    {
        using std::abs;
        return {abs(t.x), abs(t.y)};
    }

    template <template <class> class C, typename T>
    inline C<T> Ceil(Tuple2<C, T> t)
    {
        using std::ceil;
        return {ceil(t.x), ceil(t.y)};
    }

    template <template <class> class C, typename T>
    inline C<T> Floor(Tuple2<C, T> t)
    {
        using std::floor;
        return {floor(t.x), floor(t.y)};
    }

    template <template <class> class C, typename T>
    inline auto Lerp(Float t, Tuple2<C, T> t0, Tuple2<C, T> t1)
    {
        return (1 - t) * t0 + t * t1;
    }

    template <template <class> class C, typename T>
    inline C<T> min(Tuple2<C, T> t0, Tuple2<C, T> t1)
    {
        using std::min;
        return {min(t0.x, t1.x), min(t0.y, t1.y)};
    }

    template <template <class> class C, typename T>
    inline C<T> max(Tuple2<C, T> t0, Tuple2<C, T> t1)
    {
        using std::max;
        return {max(t0.x, t1.x), max(t0.y, t1.y)};
    }

    // TODO: Implement later
    // FMA() {}
    // minComponentValue() {}
    // minComponentIndex() {}
    // Permute() {}
    // HProd() {}

    template <template <class> class Child, typename T>
    class Tuple3
    {
    public:
        T x{}, y{}, z{};
        // static dimension
        static const int nDimensions = 3;

    public:
        // constructor
        Tuple3() = default;
        Tuple3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaN()); };

        bool HasNaN() const { return IsNaN(x) || IsNaN(y) || IsNaN(z); }

        // plus operator
        template <typename U>
        auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})>
        {
            DCHECK(!c.HasNaN());
            return {x + c.x, y + c.y, z + c.z};
        }

        template <typename U>
        Child<T> &operator+=(Child<U> c)
        {
            DCHECK(!c.HasNaN());
            x += c.x;
            y += c.y;
            z += c.z;
            return static_cast<Child<T> &>(*this);
        }

        // index operator
        T operator[](int i) const
        {
            DCHECK(i >= 0 && i <= 2);
            if (i == 0)
                return x;
            if (i == 1)
                return y;
            return z;
        }

        T &operator[](int i)
        {
            DCHECK(i >= 0 && i <= 2);
            if (i == 0)
                return x;
            if (i == 1)
                return y;
            return z;
        }

        // minus operator
        template <typename U>
        auto operator-(Child<U> c) const -> Child<decltype(T{} - U{})>
        {
            DCHECK(!c.HasNaN());
            return {x - c.x, y - c.y, z - c.z};
        }

        template <typename U>
        Child<T> &operator-=(Child<U> c)
        {
            DCHECK(!c.HasNaN());
            x -= c.x;
            y -= c.y;
            z -= c.z;
            return static_cast<Child<T> &>(*this);
        }

        // equality operators
        template <typename U>
        bool operator==(Child<T> c) const { return x == c.x && y == c.y && z == c.z; }

        template <typename U>
        bool operator!=(Child<T> c) const { return x != c.x || y != c.y || z != c.z; }

        // multiply operator
        template <typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})>
        {
            return {x * s, y * s, z * s};
        }

        template <typename U>
        Child<T> &operator*=(U s)
        {
            DCHECK(IsNaN(s));
            x *= s;
            y *= s;
            z *= s;
            return static_cast<Child<T> &>(*this);
        }

        // division operator
        template <typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})>
        {
            DCHECK_NE(d, 0);
            return {x / d, y / d, z / d};
        }

        template <typename U>
        Child<T> &operator/=(U d)
        {
            DCHECK_NE(d, 0);
            x /= d;
            y /= d;
            z /= d;
            return static_cast<Child<T> &>(*this);
        }

        // negate operator
        Child<T> operator-() const { return {-x, -y, -z}; }

        // to string
        std::string ToString() const
        {
            return "x:" + std::to_string(x) + ",y:" + std::to_string(y) + ",z:" + std::to_string(z);
        }
    };

    template <template <class> class C, typename T, typename U>
    inline auto operator*(U s, Tuple3<C, T> t) -> C<decltype(T{} * U{})>
    {
        return t * s;
    }

    template <template <class> class C, typename T>
    inline C<T> Abs(Tuple3<C, T> t)
    {
        using std::abs;
        return {abs(t.x), abs(t.y), abs(t.z)};
    }

    template <template <class> class C, typename T>
    inline C<T> Ceil(Tuple3<C, T> t)
    {
        using std::ceil;
        return {ceil(t.x), ceil(t.y), ceil(t.z)};
    }

    template <template <class> class C, typename T>
    inline C<T> Lerp(Float t, Tuple3<C, T> t0, Tuple3<C, T> t1)
    {
        return (1 - t) * t0 + t * t1;
    }

    template <template <class> class C, typename T>
    inline C<T> Min(Tuple3<C, T> t0, Tuple3<C, T> t1)
    {
        using std::min;
        return {min(t0.x, t1.x), min(t0.y, t1.y), min(t0.z, t1.z)};
    }

    template <typename T>
    class Vector2 : public Tuple2<Vector2, T>
    {
    public:
        using Tuple2<Vector2, T>::x;
        using Tuple2<Vector2, T>::y;

        Vector2() = default;
        Vector2(T x, T y) : Tuple2<tfrt::Vector2, T>(x, y) {}
        template <typename U>
        explicit Vector2(Point2<U> p) : Tuple2<tfrt::Vector2, T>(T(p.x), T(p.y)) {}
        template <typename U>
        explicit Vector2(Vector2<U> v) : Tuple2<tfrt::Vector2, T>(T(v.x), T(v.u)) {}
    };

    template <typename T>
    class Vector3 : public Tuple3<Vector3, T>
    {
    public:
        using Tuple3<Vector3, T>::x;
        using Tuple3<Vector3, T>::y;
        using Tuple3<Vector3, T>::z;

        Vector3() = default;
        Vector3(T x, T y, T z) : Tuple3<tfrt::Vector3, T>(x, y, z) {}

        template <typename U>
        explicit Vector3(Vector3<U> v) : Tuple3<tfrt::Vector3, T>(T(v.x), T(v.y), T(v.z)) {}

        template <typename U>
        explicit Vector3(Point3<U> p) : Tuple3<tfrt::Vector3, T>(T(p.x), T(p.y), T(p.z)) {}
    };

    using Vector2f = Vector2<Float>;
    using Vector2i = Vector2<int>;
    using Vector3f = Vector3<Float>;
    using Vector3i = Vector3<int>;

    template <typename T>
    class Point2 : public Tuple2<Point2, T>
    {
    public:
        using Tuple2<Point2, T>::x;
        using Tuple2<Point2, T>::y;
        using Tuple2<Point2, T>::HasNaN;
        using Tuple2<Point2, T>::operator+;
        using Tuple2<Point2, T>::operator+=;
        using Tuple2<Point2, T>::operator*;
        using Tuple2<Point2, T>::operator*=;

        // constructor
        Point2() = default;
        Point2(T x, T y) : Tuple2<tfrt::Point2, T>(T(x), T(y)) {}
        template <typename U>
        explicit Point2(Point2<U> p) : Tuple2<tfrt::Point2, T>(T(p.x), T(p.y)) {}
        template <typename U>
        explicit Point2(Vector2<U> v) : Tuple2<tfrt::Point2, T>(T(v.x), T(v.y)) {}

        // addition
        template <typename U>
        auto operator+(Vector2<U> v) const -> Point2<decltype(T{} + U{})>
        {
            return {x + v.x, y + v.y};
        }

        template <typename U>
        Point2<T> &operator+=(Vector2<U> v)
        {
            x += v.x;
            y += v.y;
            return (*this);
        }

        // minus
        template <typename U>
        auto operator-(Vector2<U> v) const -> Point2<decltype(T{} - U{})>
        {
            return {x - v.x, y - v.y};
        }

        template <typename U>
        Point2<T> &operator-=(Vector2<U> v) 
        {
            x -= v.x;
            y -= v.y;
            return (*this);
        }
        template <typename U>
        auto operator-(Point2<U> p) const -> Vector2<decltype(T{} - U{})>
        {
            return {x - p.x, y - p.y, z - p.z};
        }

        // negate
        Point2<T> &operator-() const
        {
            return {-x, -y, -z};
        }
    };

    template <typename T>
    class Point3 : public Tuple3<Point3, T>
    {
    public:
        using Tuple3<Point3, T>::x;
        using Tuple3<Point3, T>::y;
        using Tuple3<Point3, T>::z;
        using Tuple3<Point3, T>::HasNaN;
        using Tuple3<Point3, T>::operator+;
        using Tuple3<Point3, T>::operator+=;
        using Tuple3<Point3, T>::operator*;
        using Tuple3<Point3, T>::operator*=;

        // constructors
        Point3() = default;
        Point3(T x, T y, T z) : Tuple3<tfrt::Point3, T>(x, y, z) {}

        template <typename U>
        explicit Point3(Point3<U> p) : Tuple3<tfrt::Point3, T>(T(p.x), T(p.y), T(p.z)) {}
        template <typename U>
        explicit Point3(Vector3<U> v) : Tuple3<tfrt::Point3, T>(T(v.x), T(v.y), T(v.z)) {}

        // negate
        Point3<T> operator-() const { return {-x, -y, -z}; }

        // addition
        template <typename U>
        auto operator+(Vector3<U> v) const -> Point3<decltype(T{} + U{})>
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        template <typename U>
        Point3<T> &operator+=(Vector3<U> v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        template <typename U>
        auto operator-(Vector3<U> v) const -> Point3<decltype(T{} - U{})>
        {
            return {x - v.x, y - v.y, z - v.z};
        }

        template <typename U>
        Point3<t> &operator-=(Vector3<U> v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        template <typename U>
        auto operator-(Point3<U> p) const -> Vector3<decltype(T{} - U{})>
        {
            return {x - p.x, y - p.y, z - p.z};
        }
    };

    using Point2f = Point2<Float>;
    using Point2i = Point2<int>;
    using Point3f = Point3<Float>;
    using Point3i = Point3<int>;
}