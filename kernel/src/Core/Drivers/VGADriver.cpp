#include "Core/Drivers/VGADriver.hpp"
#include "C++/utility.hpp"
#include "../bootloader/limine/limine.h"

VGADriver::VGADriver()
 : 
 vgaBuffer(reinterpret_cast<VGAChar*>(VGA_START_ADDRESS)),
 foregroundColor(VGAColors::Green),
 backgroundColor(VGAColors::Black),
 cursor(TextModeCursor{.x = 0, .y = 0})
{

    clearChar.SetBackgroundColor(VGAColors::Gray);
    clearChar.SetForegroundColor(VGAColors::Gray);
    clearChar.SetBlink(false);

   
}

VGADriver::~VGADriver()
{

}

void VGADriver::Initialize(struct limine_framebuffer* framebuffer)
{
    


    //Validation
    if(framebuffer == nullptr)
    {
        //didn't work, give up and go home
    } else 
    {
        if (framebuffer->bpp == 16 && framebuffer->pitch == 0xA0 && framebuffer->width == 80 && framebuffer->height == 25) 
        {
            //Yay!
        }
    }

    if(vgaBuffer == nullptr)
    {
        vgaBuffer = reinterpret_cast<VGAChar*>(VGA_START_ADDRESS);
    }

    //Clear();
}

void VGADriver::SetForegroundColor(VGAColors color)
{
    foregroundColor = color;
}

void VGADriver::SetBackgroundColor(VGAColors color)
{
    backgroundColor = color;
}

void VGADriver::WriteChar(char c)
{
    cursor.y = blib::clamp(cursor.y, static_cast<uint32_t>(0), VGA_HEIGHT);
    cursor.x = blib::clamp(cursor.x, static_cast<uint32_t>(0), VGA_WIDTH);

    //vgaBuffer[cursor.y*VGA_WIDTH + cursor.x] = clearChar;
}

void VGADriver::Clear()
{   

    for (uint32_t y = 0; y < VGA_HEIGHT; ++y) {
        for (uint32_t x = 0; x < VGA_WIDTH; ++x) {
            vgaBuffer[y * VGA_WIDTH + x] = clearChar; // Use x and y directly
        }
    }

    cursor.x = 0;
    cursor.y = 0;
}

void VGADriver::SetCursor(uint8_t x, uint8_t y)
{   
    static_assert(blib::is_same<blib::common_type_t<unsigned int, unsigned int>, unsigned int>::value, "common_type_t<unsigned int, unsigned int> should be unsigned int");
    static_assert(blib::is_same<blib::common_type_t<unsigned int, blib::common_type_t<unsigned int, unsigned int>>, unsigned int>::value, "Nested common_type_t<unsigned int, common_type_t<unsigned int, unsigned int>> should be unsigned int");

    cursor.x = blib::clamp(x, static_cast<uint8_t>(0), static_cast<uint8_t>(VGA_WIDTH) - static_cast<uint8_t>(1));
    cursor.y = blib::clamp(y, static_cast<uint8_t>(0), static_cast<uint8_t>(VGA_HEIGHT) - static_cast<uint8_t>(1));
}