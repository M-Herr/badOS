#include "Core/IDT.hpp"


InterruptDescriptorTable::InterruptDescriptorTable()
{
    for(size_t i = 0; i < number_of_entries; ++i)
    {
        isr[i] = nullptr;
        idt_entries[i] = IDTEntry();
    }
}

InterruptDescriptorTable::~InterruptDescriptorTable()
{

}

void InterruptDescriptorTable::set_entry(uint8_t index, ISRBase* isr, uint8_t flags)
{
    idt_entries[index].set_entry(isr, flags);
}

void InterruptDescriptorTable::load()
{
        struct IDTPointer {
            uint16_t limit;
            uint64_t base;
        } __attribute__((packed));

        IDTPointer idt_ptr;

        idt_ptr.limit = sizeof(IDTEntry) * number_of_entries - 1;
        idt_ptr.base = reinterpret_cast<uint64_t>(&idt_entries);

        asm volatile ("lidt (%0)" : : "r" (&idt_ptr));
}
