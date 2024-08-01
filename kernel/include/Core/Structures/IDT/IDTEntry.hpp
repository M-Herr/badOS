#pragma once

#include "Types.hpp"
#include "C++/byte.hpp"
#include "Core/ISR.hpp"

namespace IDT {
    class Entry
    {   
        public:
        uint16_t offset_low : 16;
        uint16_t segment_select: 16;
        uint8_t ist : 2;
        uint8_t reserved_low : 6;
        uint8_t segment_type : 4;
        uint8_t reserved_mid : 1;
        uint8_t privilege_level : 2;
        uint8_t present : 1;
        uint16_t offset_mid : 16;
        uint32_t offset_high: 32;
        uint32_t reserved: 32;

        public:
        Entry();
        ~Entry();

        void set_entry(ISRBase* isr, uint8_t flags);
        void set_offset(uint64_t handler_address);


    }__attribute__((packed));;

}