#pragma once
#include <Types.hpp>
#include "Pixel.hpp"

struct FrameBufferProperties
{   

    
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

    private:
    Drawable* drawable_items;
};