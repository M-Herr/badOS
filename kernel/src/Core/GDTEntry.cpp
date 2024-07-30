#include "Core/GDTEntry.hpp"


GDTEntry::GDTEntry()
: 
limit_low(0),
base_low(0),
base_middle(0),
base_high(0),
base_upper(0),
access(0),
granularity(0)
{
}

GDTEntry::~GDTEntry()
{

}

/*
void GDTEntry::set(uint32_t base, uint32_t limit, DescriptorFlags accessFlags, DescriptorFlags granularityFlags)
{
    limit_low = limit & 0xFFFF;
    base_low = base & 0xFFFF;
    base_middle = (base >> 16) & 0xFF;
    base_high = (base >> 24) & 0xFF;
    base_upper = (base >> 32) & 0xFFFFFFFF;

    access = static_cast<uint8_t>(accessFlags);
    granularity = (limit >> 16) & 0x0F;
    granularity |= static_cast<uint8_t>(granularityFlags);
}
*/