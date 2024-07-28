#pragma once
#include "Types.hpp"
#include "C++/type_traits.hpp"

enum class VGAColors : uint8_t
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Purple,
    Brown,
    Gray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightPurple,
    Yellow,
    White
};

template<typename E>
struct FEnableBitMaskOperators {
    static constexpr bool enable = false;
};

template<>
struct FEnableBitMaskOperators<VGAColors> {
    static constexpr bool enable = true;
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
operator~(E lhs) 
{
    return static_cast<E>(
        ~static_cast<blib::underlying_type_t<E>>(lhs)
    );
}


struct VGAProperties
{
    static constexpr uint64_t start_address = 0xb8000; 
    static constexpr uint64_t width = 80;
    static constexpr uint64_t height = 25;
};