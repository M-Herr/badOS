#include "Core/IDTEntry.hpp"

IDTEntry::IDTEntry() 
: 
isr_low(0),
kernel_cs(0),
ist(0),
attributes(0),
isr_mid(0),
isr_high(0),
reserved(0)
{

}


IDTEntry::~IDTEntry()
{

}


void IDTEntry::set_entry(ISRBase* isr, uint8_t flags)
{
    isr_low = reinterpret_cast<uint64_t>(isr) & 0xFFFF;
    kernel_cs = 0;
    ist = 0;
    attributes = flags;
    isr_mid =  (reinterpret_cast<uint64_t>(isr) >> 16) & 0xFFFF;
    isr_high = (reinterpret_cast<uint64_t>(isr) >> 32) & 0xFFFFFFFF;
    reserved = 0;
}
