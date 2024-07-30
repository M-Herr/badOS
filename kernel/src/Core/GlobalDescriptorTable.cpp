
#include "Core/GlobalDescriptorTable.hpp"

GlobalDescriptorTable::GlobalDescriptorTable() {
   
}


GlobalDescriptorTable::~GlobalDescriptorTable()
{
    
}

void GlobalDescriptorTable::set_entry(int index, uint32_t base, uint32_t limit) {
    //entry[index].set(base, limit);
}

void GlobalDescriptorTable::initialize()
{

    init_ptr(); // Initialize GDT pointer

    // Null Segment
   
    entry[0] = blib::bit_cast<SegmentDescriptor>(static_cast<uint64_t>(0));

    
    entry[1].set_base(0);
    entry[1].set_limit(0xFFFFF); // 20 bits all set to 1
    entry[1].set_code_segment_type(CodeSegmentType::ExecuteOnlyConforming);
    entry[1].set_default_op(true);
    entry[1].set_present(true);
    entry[1].set_granularity(true);
    entry[1].set_long_mode(true);
    entry[1].set_privelage_level();
    entry[1].set_descriptor_type(true);

    entry[2].set_base(0);
    entry[2].set_limit(0xFFFFF); // 20 bits all set to 1
    entry[2].set_data_segment_type(DataSegmentType::ReadWrite);
    entry[2].set_default_op(true);
    entry[2].set_present(true);
    entry[2].set_granularity(true);
    entry[2].set_long_mode(true);
    entry[2].set_privelage_level();
    entry[2].set_descriptor_type(true);

}

void GlobalDescriptorTable::init_ptr()
{
    gdt_ptr.limit = (sizeof(SegmentDescriptor) * gdt_entries) - 1;
    gdt_ptr.base = reinterpret_cast<uint64_t>(&entry);
}
