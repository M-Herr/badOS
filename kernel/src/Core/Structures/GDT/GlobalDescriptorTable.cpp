
#include "Core/Structures/GDT/GlobalDescriptorTable.hpp"


namespace GDT {

    DescriptorTable::DescriptorTable() {
    
    }


    DescriptorTable::~DescriptorTable()
    {
        
    }

    void DescriptorTable::set_entry(int index, uint32_t base, uint32_t limit) 
    {
        //entry[index].set(base, limit);
    }

    void DescriptorTable::initialize(const auto ...options)
    {

    }    

    void DescriptorTable::init_ptr()
    {
        entry_ptr.limit = (sizeof(Entry) * gdt_entries) - 1;
        entry_ptr.base = reinterpret_cast<uint64_t>(&entries);
    }

}