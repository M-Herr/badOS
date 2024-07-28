#pragma once

#include "Types.hpp"
#include "Core/ISR.hpp"

#pragma pack(push, 1)
class IDTEntry
{   
    public:
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t ist;
    uint8_t attributes;
    uint16_t isr_mid;
    uint32_t isr_high;
    uint32_t reserved;

    public:
    IDTEntry();
    ~IDTEntry();

    void set_entry(ISRBase* isr, uint8_t flags);

};
#pragma pack(pop)