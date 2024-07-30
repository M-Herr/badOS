#pragma once
#include <Types.hpp>
#include "C++/byte.hpp"
#include "GlobalDescriptorUtils.hpp"

class GDTEntry
{
    public:
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
    uint32_t base_upper;
    uint32_t reserved;
    
    public:
    GDTEntry();
    ~GDTEntry();
    //void set(uint32_t base, uint32_t limit, DescriptorFlags accessFlags, DescriptorFlags granularityFlags);

    private:

    private:
    
}__attribute__((packed));