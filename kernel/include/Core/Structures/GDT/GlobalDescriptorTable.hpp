#pragma once
#include <Types.hpp>
#include "Core/Structures/GDT/GDTEntry.hpp"
#include "Core/Structures/GDT/GlobalDescriptorUtils.hpp"


namespace GDT {
    class DescriptorTable 
    {
        public:
        static constexpr size_t gdt_entries = 3;
        struct EntryPtr {
            uint16_t limit;
            uint64_t base;
        } __attribute__((packed));
        
        public:
        DescriptorTable();
        ~DescriptorTable();

        inline Entry& get_entry(size_t index) { return entries[index];}

        void init_ptr();

        
        void initialize(const auto ...options);

        void set_entry(int index, uint32_t base, uint32_t limit);

        inline EntryPtr* GetPtr() { return &entry_ptr;}

        private:
        Entry entries[gdt_entries];
        EntryPtr entry_ptr;

        private:

    };

}