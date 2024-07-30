#pragma once

#include "Types.hpp"
#include "Core/ISR.hpp"

struct IDTGateDescriptor
{
    uint16_t offset_low : 16;
    uint16_t segment_select: 16;
    uint8_t ist : 2;
    uint8_t reserved_low : 6;
    uint8_t segment_type : 4;
    uint8_t reserved_mid : 1;
    uint8_t privilege_level : 2;
    uint8_t present : 1;
    uint8_t offset_mid : 16;
    uint8_t offset_high: 32;
    uint8_t reserved: 32;
}__attribute__((packed));

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
