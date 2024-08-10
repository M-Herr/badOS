#pragma once
#include <Types.hpp>
#include "Core/Drivers/VGABuffer.hpp"
#include "Core/Drivers/TextModeUtils.hpp"

class VGADriver 
{
    public:
    VGADriver();
    ~VGADriver(); 

    void Initialize(struct limine_framebuffer* framebuffer);

    static constexpr uint32_t VGA_WIDTH = 80;
    static constexpr uint32_t VGA_HEIGHT = 25;
    static constexpr uint64_t VGA_START_ADDRESS = 0xb8000;
    
    void WriteChar(char c);
    void Clear();
   


    void SetForegroundColor(VGAColors color);
    void SetBackgroundColor(VGAColors color);

    void SetCursor(uint8_t x, uint8_t y);
    inline TextModeCursor* GetTextModeCursor() { return &cursor;}
    
    private:
    VGAChar* vgaBuffer{nullptr};
    VGAChar clearChar;

    VGAColors foregroundColor;
    VGAColors backgroundColor;

    TextModeCursor cursor;
};