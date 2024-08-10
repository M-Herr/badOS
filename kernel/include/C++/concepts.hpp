#pragma once
#include "type_traits.hpp"

namespace blib {

    template<typename T>
    concept integral = 
        is_same_v<T, bool> ||
        is_same_v<T, char> ||
        is_same_v<T, signed char> ||
        is_same_v<T, unsigned char> ||
        is_same_v<T, short> ||
        is_same_v<T, unsigned short> ||
        is_same_v<T, int> ||
        is_same_v<T, unsigned int> ||
        is_same_v<T, long> ||
        is_same_v<T, unsigned long> ||
        is_same_v<T, long long> ||
        is_same_v<T, unsigned long long>;


    template<typename T, typename... Args>
    concept is_trivially_copyable = is_trivially_copyable_v<T, Args...>;


    template<typename T>
    concept PositiveInteger = requires(T a) 
    {
        (a > 0) && integral<T>;
    };
}

    