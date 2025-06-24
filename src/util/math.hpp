#pragma once

#include <cmath>

namespace tfrt {

    template<class T>
    inline T FMA(T a, T b, T c) {
        return std::fma(a, b, c);
    }

    template <typename T>
    inline constexpr T Sqr(T v) {
        return v * v;
    }
    
    template <typename Ta, typename Tb, typename Tc, typename Td>
    inline auto SumOfProducts(Ta a, Tb b, Tc c, Td d) {
        auto cd = c * d;
        auto sumOfProducts = FMA(a, b, cd);
        auto error = FMA(c, d, -cd);
        return sumOfProducts + error;
    }
}