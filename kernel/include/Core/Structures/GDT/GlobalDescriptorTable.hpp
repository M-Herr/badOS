#pragma once
#include <Types.hpp>
#include "Core/Structures/GDT/GDTEntry.hpp"
#include "Core/Structures/GDT/GlobalDescriptorUtils.hpp"


namespace GDT {
    class DescriptorTable 
    {
        public:
        static constexpr size_t gdt_entries = 7;
        struct EntryPtr {
            uint16_t limit;
            uint64_t base;
        } __attribute__((packed));

        enum class SegmentLabel : size_t
        {
            Null        = 0,
            KernelCode16 = 1,
            KernelData16 = 2,
            KernelCode32 = 3,
            KernelData32 = 4,
            KernelCode64 = 5, 
            KernelData64 = 6
        };

        public:
        DescriptorTable();
        ~DescriptorTable();

        inline Entry& get_entry(size_t index) { return entries[index];}

        void init_ptr();

        void configure(SegmentLabel label, SegmentOptions options);

        Entry& get_segment(SegmentLabel label) { 
             size_t index = blib::underlying_type_t<SegmentLabel>(label);
             return entries[index];
             }
        inline EntryPtr* GetPtr() { return &entry_ptr;}

        private:
        Entry entries[gdt_entries];
        EntryPtr entry_ptr;

        private:

    };

}