#include "Core/Structures/IDT/IDT.hpp"

namespace IDT {
InterruptDescriptorTable::InterruptDescriptorTable()
{
    for(size_t i = 0; i < number_of_entries; ++i)
    {
        //isr[i] = nullptr;

    }
}

InterruptDescriptorTable::~InterruptDescriptorTable()
{

}

void InterruptDescriptorTable::init_ptr()
{
    entry_ptr.limit = (sizeof(Entry) * number_of_entries) - 1;
    entry_ptr.base = reinterpret_cast<uint64_t>(&entries);
}

void InterruptDescriptorTable::configure(GateOptions options)
{   

}

void InterruptDescriptorTable::set_entry(size_t index, GateOptions options)
{
    entries[index].initialize(options);
}

void InterruptDescriptorTable::initialize()
{

}

}