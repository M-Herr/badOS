#pragma once

#include <Types.hpp>
#include "Core/IDTEntry.hpp"
#include "Core/ISR.hpp"

class InterruptDescriptorTable 
{
    public:
    constexpr static size_t number_of_entries = 256;
    
    public:
    InterruptDescriptorTable();

    ~InterruptDescriptorTable();

    void set_entry(uint8_t index, ISRBase* isr, uint8_t flags);

    void load();

    void initialize();

    private:
    IDTEntry idt_entries[number_of_entries];
    ISRBase* isr[number_of_entries];

};