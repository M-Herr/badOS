#include "Core/Structures/IDT/IDT.hpp"

namespace IDT {
InterruptDescriptorTable::InterruptDescriptorTable()
{
    for(size_t i = 0; i < number_of_entries; ++i)
    {
        isr[i] = nullptr;

    }
}

InterruptDescriptorTable::~InterruptDescriptorTable()
{

}

void InterruptDescriptorTable::set_entry(uint8_t index, ISRBase* isr, uint8_t flags)
{
    
}

void InterruptDescriptorTable::load()
{
        
}

}