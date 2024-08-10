#pragma once

#include <Types.hpp>
#include "C++/enum_bitmask.hpp"

namespace Interrupts
{

    enum class InterruptType : uint8_t
    {
        Fault = 0,
        Trap = 1,
        Abort = 2,
        Interrupt = 3
    };

   
    enum class Vector : uint8_t {
        DivideError                = 0,
        Debug                      = 1,
        NonMaskableInterrupt       = 2,
        Breakpoint                 = 3,
        Overflow                   = 4,
        BoundRangeExceeded         = 5,
        InvalidOpcode              = 6,
        DeviceNotAvailable         = 7,
        DoubleFault                = 8,
        CoprocessorSegmentOverrun  = 9,
        InvalidTSS                 = 10,
        SegmentNotPresent          = 11,
        StackSegmentFault          = 12,
        GeneralProtectionFault     = 13,
        Reserved15                 = 15,
        PageFault                  = 14,
        x87FloatingPointException  = 16,
        AlignmentCheck             = 17,
        MachineCheck               = 18,
        SIMDException              = 19,
        VirtualizationException    = 20,
        ControlProtectionException = 21,
        // Reserved vectors
        Reserved22                 = 22,
        Reserved23                 = 23,
        Reserved24                 = 24,
        Reserved25                 = 25,
        Reserved26                 = 26,
        Reserved27                 = 27,
        Reserved28                 = 28,
        Reserved29                 = 29,
        Reserved30                 = 30,
        Reserved31                 = 31
        // User-defined interrupts start from 32
    };
    
    struct Interrupt
    {
        Vector vector;
        InterruptType interrupt_type;
        bool error_code;
    };
    
    using Interrupt_t = Interrupt;

    
}


ENABLE_BM(Interrupts::InterruptType);


constexpr Interrupts::Interrupt_t interrupt_list[] = {
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::DivideError,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Debug,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::NonMaskableInterrupt,
        .interrupt_type = Interrupts::InterruptType::Interrupt,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Breakpoint,
        .interrupt_type = Interrupts::InterruptType::Trap,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Overflow,
        .interrupt_type = Interrupts::InterruptType::Trap,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::BoundRangeExceeded,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::InvalidOpcode,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::DeviceNotAvailable,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::DoubleFault,
        .interrupt_type = Interrupts::InterruptType::Abort,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::CoprocessorSegmentOverrun,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::InvalidTSS,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::SegmentNotPresent,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::StackSegmentFault,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::GeneralProtectionFault,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::PageFault,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved15,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::x87FloatingPointException,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::AlignmentCheck,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::MachineCheck,
        .interrupt_type = Interrupts::InterruptType::Abort,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::SIMDException,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::VirtualizationException,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::ControlProtectionException,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = true,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved22,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved23,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved24,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved25,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved26,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved27,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved28,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved29,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved30,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    },
    Interrupts::Interrupt{
        .vector = Interrupts::Vector::Reserved31,
        .interrupt_type = Interrupts::InterruptType::Fault,
        .error_code = false,
    }
};
