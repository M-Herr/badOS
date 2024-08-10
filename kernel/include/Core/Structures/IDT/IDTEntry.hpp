#pragma once

#include "Types.hpp"
#include "C++/byte.hpp"
#include "Core/Structures/IDT/ISR.hpp"
#include "C++/enum_bitmask.hpp"



namespace IDT {

    // Interrupt Gate Types
    enum class GateType : uint8_t {
        TaskGate        = 0b0101, // 5
        InterruptGate16 = 0b0110, // 6
        TrapGate16      = 0b0111, // 7
        InterruptGate32 = 0b1110, // 14
        TrapGate32      = 0b1111  // 15
    };

    enum class PrivilegeLevel : uint8_t {
        Ring0 = 0b00,
        Ring1 = 0b01,
        Ring2 = 0b10,
        Ring3 = 0b11
    };

    enum class Present : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };

    struct GateOptions {
        uint64_t base;
        uint16_t selector;
        PrivilegeLevel privilege_level;
        Present present;
        GateType gate_type;
    };

    class Entry {
    public:
        uint16_t base_low : 16;         // Lower 16 bits of the base address
        uint16_t selector : 16;         // Code segment selector in GDT
        uint8_t ist : 3;                // Interrupt Stack Table (IST) index
        uint8_t reserved0 : 5;          // Reserved, set to zero
        uint8_t gate_type : 4;          // Gate type (e.g., interrupt, trap)
        uint8_t storage_segment : 1;    // Storage Segment (set to 0 for interrupt and trap gates)
        uint8_t privilege_level : 2;    // Descriptor privilege level (0 = kernel, 3 = user)
        uint8_t present : 1;            // Segment present flag
        uint16_t base_middle : 16;      // Middle 16 bits of the base address
        uint32_t base_high : 32;        // Upper 32 bits of the base address
        uint32_t reserved1 : 32;        // Reserved, set to zero

    public:
        Entry();
        ~Entry();

        void initialize(GateOptions options);

    } __attribute__((packed));
}

// Enable bit mask operations for all of this enum classes
ENABLE_BM(IDT::PrivilegeLevel);
ENABLE_BM(IDT::Present);
ENABLE_BM(IDT::GateType);