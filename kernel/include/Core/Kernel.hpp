#pragma once
#include "Core/GlobalDescriptorTable.hpp"
#include "Core/IDT.hpp"
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

    GlobalDescriptorTable gdt;

    InterruptDescriptorTable idt;

    FrameBuffer frame_buffer;
    
};