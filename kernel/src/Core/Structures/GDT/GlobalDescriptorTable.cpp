
#include "Core/Structures/GDT/GlobalDescriptorTable.hpp"


namespace GDT {

    DescriptorTable::DescriptorTable() {
    
    }


    DescriptorTable::~DescriptorTable()
    {
        
    }

    void DescriptorTable::initialize(const auto ...options)
    {

    }    

    void DescriptorTable::init_ptr()
    {
        entry_ptr.limit = (sizeof(Entry) * gdt_entries) - 1;
        entry_ptr.base = reinterpret_cast<uint64_t>(&entries);
    }

    void DescriptorTable::configure(SegmentLabel label, SegmentOptions options)
    {   
        size_t index = blib::underlying_type_t<SegmentLabel>(label);
        entries[index].initialize(options);

    }

}