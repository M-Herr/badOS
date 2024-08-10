#pragma once
#include <Types.hpp>
#include "C++/enum_bitmask.hpp"
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

inline uint8_t MakeColor(VGAColors fg, VGAColors bg)
{
    return (static_cast<uint8_t>(bg) << 4) | static_cast<uint8_t>(fg);
};

template<>
struct FEnableBitMaskOperators<VGAColors> {
    static constexpr bool enable = true;
};



struct TextModeCursor
{
    uint32_t x;
    uint32_t y;
};