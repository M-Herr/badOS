#pragma once
#include "Core/Structures/GDT/GlobalDescriptorTable.hpp"

#include "Core/FrameBuffer.hpp"

class Kernel
{
    public:
    Kernel();

    ~Kernel();

    void run();

    void initialize_idt();

    void get_framebuffer_properties(limine_framebuffer* in_frame_buffer);

    void intialize_gdt();

    GDT::DescriptorTable gdt;

    FrameBuffer frame_buffer;
    
};