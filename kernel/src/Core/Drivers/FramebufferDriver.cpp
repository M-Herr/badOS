#include "Core/Drivers/FramebufferDriver.hpp"


FramebufferDriver::FramebufferDriver()
{

}

FramebufferDriver::~FramebufferDriver()
{


}

void FramebufferDriver::Initialize(struct limine_framebuffer *in_framebuffer)
{

    // Validation
    if (in_framebuffer == nullptr)
    {
        // didn't work, give up and go home
    }
    else
    {
        frameBuffer = reinterpret_cast<uint8_t*>(in_framebuffer->address);
        pitch = in_framebuffer->pitch;
        bytesPerPixel = in_framebuffer->bpp;
    }
}

void FramebufferDriver::WritePixel()
{

}    

void FramebufferDriver::Clear()
{

}