#pragma once
#include "type_traits.hpp"

template<typename E>
struct FEnableBitMaskOperators {
    static constexpr bool enable = false;
};

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator|(E lhs,E rhs) 
{
    return static_cast<E>(
        static_cast<blib::underlying_type_t<E>>(lhs) |
        static_cast<blib::underlying_type_t<E>>(rhs)
    );
}

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator|(int lhs,E rhs) 
{
    return static_cast<E>(
        static_cast<blib::underlying_type_t<E>>(lhs) |
        static_cast<blib::underlying_type_t<E>>(rhs)
    );
}

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator|(E lhs,int rhs) 
{
    return static_cast<E>(
        static_cast<blib::underlying_type_t<E>>(lhs) |
        static_cast<blib::underlying_type_t<E>>(rhs)
    );
}

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator&(E lhs,E rhs) 
{
    return static_cast<E>(
        static_cast<blib::underlying_type_t<E>>(lhs) |
        static_cast<blib::underlying_type_t<E>>(rhs)
    );
}

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator<<(E lhs,E rhs) 
{
    return static_cast<E>(
        static_cast<blib::underlying_type_t<E>>(lhs) |
        static_cast<blib::underlying_type_t<E>>(rhs)
    );
}

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator<<(E lhs, int rhs) 
{
    return static_cast<E>(
        static_cast<blib::underlying_type_t<E>>(lhs) |
        static_cast<blib::underlying_type_t<E>>(rhs)
    );
}

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator<<(int lhs, E rhs) 
{
    return static_cast<E>(
        static_cast<blib::underlying_type_t<E>>(lhs) |
        static_cast<blib::underlying_type_t<E>>(rhs)
    );
}

template<typename E>
typename blib::enable_if_t<FEnableBitMaskOperators<E>::enable, E> 
operator~(E lhs) 
{
    return static_cast<E>(
        ~static_cast<blib::underlying_type_t<E>>(lhs)
    );
}


#define ENABLE_BM(name) \
template<> \
struct FEnableBitMaskOperators<name> { \
    static constexpr bool enable = true; \
};