#pragma once
#include "Types.hpp"
#include "C++/type_traits.hpp"
#include "C++/enum_bitmask.hpp"

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

template<>
struct FEnableBitMaskOperators<VGAColors> {
    static constexpr bool enable = true;
};

struct VGAProperties
{
    static constexpr uint64_t start_address = 0xb8000; 
    static constexpr uint64_t width = 80;
    static constexpr uint64_t height = 25;
};