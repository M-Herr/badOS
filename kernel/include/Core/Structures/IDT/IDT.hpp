#pragma once

#include <Types.hpp>
#include "Core/Structures/IDT/IDTEntry.hpp"
#include "Core/ISR.hpp"

namespace IDT {
struct IDTPointer 
{
    uint16_t limit;
    uint64_t base;
 } __attribute__((packed));


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
    
    IDTPointer* get_idt_ptr() { return &idt_ptr;}

    private:
    IDTPointer idt_ptr;
    //IDTGateDescriptor entries[number_of_entries];
    ISRBase* isr[number_of_entries];

};

}