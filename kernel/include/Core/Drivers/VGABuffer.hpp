#pragma once
#include <Types.hpp>
#include "C++/type_traits.hpp"
#include "Core/Drivers/TextModeUtils.hpp"   
#include "Core/Interfaces/Screenbuffer.hpp"


class VGAChar
{
    public:
    uint8_t character : 8;
    uint8_t foregroundColor : 4;
    uint8_t backgroundColor: 3;
    uint8_t blink : 1;

    inline void SetForegroundColor(VGAColors color)
    {
        foregroundColor = blib::bit_cast<uint8_t>(color);
    }

    inline void SetBackgroundColor(VGAColors color)
    {
        backgroundColor = blib::bit_cast<uint8_t>(color);
    }

    inline void SetBlink(bool should_blink)
    {
        if(should_blink)
        {
            blink = 0b1;
        }
        else 
        {
            blink = 0b0;
        }
    }

}__attribute__((packed));