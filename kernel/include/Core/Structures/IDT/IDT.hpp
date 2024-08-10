#pragma once

#include <Types.hpp>
#include "Core/Memory/Constants.hpp"
#include "Core/Structures/IDT/IDTEntry.hpp"
#include "Core/Structures/IDT/ISR.hpp"

namespace IDT {
struct EntryPtr 
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

    void set_entry(size_t index, GateOptions options);

    void load();

    void initialize();
    
    void init_ptr();

    void configure(GateOptions options);

    EntryPtr* get_idt_ptr() { return &entry_ptr;}

    private:
    Entry entries[number_of_entries];
    EntryPtr entry_ptr;
    

};

}