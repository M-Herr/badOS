#pragma once
#include "C++/type_traits.hpp"

namespace blib
{
    template<typename T>
    const T& max(const T& a, const T& b)
    {
       return (a > b) ? a : b;
    }

    template<typename T>
    const T& min(const T& a, const T& b)
    {
        return (a < b) ? a : b;
    }

     template<typename T, typename U, typename V>
    auto clamp(const T& n, const U& lower, const V& upper)
        -> common_type_variadic_t<T, U, V> {
        using common_t = common_type_variadic_t<T, U, V>;
        return (n < static_cast<common_t>(lower)) ? static_cast<common_t>(lower) :
               (n > static_cast<common_t>(upper)) ? static_cast<common_t>(upper) : static_cast<common_t>(n);
    }
}