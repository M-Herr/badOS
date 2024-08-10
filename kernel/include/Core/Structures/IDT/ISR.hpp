#pragma once
#include <Types.hpp>
#include "Interrupts.hpp"

typedef void(*ISRFunctionNoError)(void);
typedef void(*ISRFunctionWithError)(uint32_t errorCode);


namespace ISR 
{   
    // Define the stack frame structure for x86_64
    struct stack_frame {
        uint64_t rip;
        uint64_t cs;
        uint64_t rflags;
        uint64_t rsp;
        uint64_t ss;
    };

    // Define the extended stack frame structure for exceptions with an error code
    struct stack_frame_with_error_code {
        uint64_t error_code;
        uint64_t rip;
        uint64_t cs;
        uint64_t rflags;
        uint64_t rsp;
        uint64_t ss;
    };

    enum class ISRType
    {
        NoError,
        WithError
    };

    extern "C"{
        __attribute__((interrupt))
        void general_interrupt_handler(struct stack_frame* frame);
    }


    void HandleFault(struct stack_frame* frame);
};