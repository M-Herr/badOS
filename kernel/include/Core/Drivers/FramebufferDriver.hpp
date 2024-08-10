#pragma once
#include <Types.hpp>
#include "../bootloader/limine/limine.h"

class FramebufferDriver 
{
    public:
    FramebufferDriver();
    ~FramebufferDriver();

    void Initialize(struct limine_framebuffer* in_framebuffer);
    void WritePixel();
    void Clear();

    public:
    

    private:    
    const uint32_t width = 1024;
    const uint32_t height = 768;
    uint8_t* frameBuffer;
    uint32_t pitch;
    uint32_t bytesPerPixel;

    private:
    

};