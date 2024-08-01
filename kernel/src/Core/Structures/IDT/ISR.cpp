#include "Core/ISR.hpp"


extern "C"
{
    void default_isr_handler()
    {
        __asm__ volatile ("cli; hlt");
    }
}