#pragma once
#include <Types.hpp>
#include "Core/GDTEntry.hpp"
#include "Core/GlobalDescriptorUtils.hpp"

class GlobalDescriptorTable 
{
    public:
    static constexpr size_t gdt_entries = 3;
    struct GDTPtr {
        uint16_t limit;
        uint64_t base;
    } __attribute__((packed));
    
    public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();
    inline SegmentDescriptor& get_entry(size_t index) { return entry[index];}
    void init_ptr();
    void initialize();

    void set_entry(int index, uint32_t base, uint32_t limit);

    inline GDTPtr* GetPtr() { return &gdt_ptr;}

    private:
    SegmentDescriptor entry[gdt_entries];
    GDTPtr gdt_ptr;

    private:

};