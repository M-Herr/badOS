#include "Core/Structures/IDT/ISR.hpp"

#include "Core/TextDrawable.hpp"


namespace ISR 
{
    extern "C"{
        __attribute__((interrupt))
        void general_interrupt_handler(struct stack_frame* frame)
        {
            HandleFault(frame);
        }
    }

    

    void HandleFault(struct stack_frame* frame)
    {
        while(true)
        {
            
        }

    }

}