#pragma once
#include <Types.hpp>
#ifdef USE_LIMINE
#include "bootloader/limine/limine.h"
#endif
#include "Pixel.hpp"

struct FrameBufferProperties
{   
    uint64_t* address;
    uint64_t width;
    uint64_t height;
    uint64_t pitch;
    uint16_t bits_per_pixel;
};

class FrameBuffer 
{
    public:


    public:
    FrameBuffer();
    ~FrameBuffer();
    void draw_frame();
    void add_drawable(Drawable* in_drawable);
    FrameBufferProperties* get_properties() { return &properties; }
    
    private:
    Drawable* drawable_items;
    FrameBufferProperties properties;
};