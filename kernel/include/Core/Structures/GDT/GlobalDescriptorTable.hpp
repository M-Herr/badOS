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

        enum class SegmentLabel : size_t
        {
            Null        = 0,
            KernelCode  = 1, 
            KernelData  = 2,
            UserCode    = 3,
            UserData    = 4,
        };

        public:
        DescriptorTable();
        ~DescriptorTable();

        inline Entry& get_entry(size_t index) { return entries[index];}

        void init_ptr();

        void configure(SegmentLabel label, SegmentOptions options);

        void initialize(const auto ...options);

        inline EntryPtr* GetPtr() { return &entry_ptr;}

        private:
        Entry entries[gdt_entries];
        EntryPtr entry_ptr;

        private:

    };

}