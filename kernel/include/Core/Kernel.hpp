#pragma once
#include "Core/IDT.hpp"
#include "Core/FrameBuffer.hpp"

class Kernel
{

    public:
    Kernel();
    ~Kernel();


    void run();

    void initialize_idt();


    InterruptDescriptorTable idt;
    
};