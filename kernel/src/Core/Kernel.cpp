#include "Core/Kernel.hpp"

Kernel::Kernel()
{

}

Kernel::~Kernel()
{

}

void Kernel::run()
{

}

void Kernel::initialize_idt()
{

}

void Kernel::get_framebuffer_properties(limine_framebuffer* in_frame_buffer)
{
    frame_buffer.get_properties()->address = reinterpret_cast<uint64_t*>(in_frame_buffer->address);
}

extern "C" 
{
    
    //Apparently it is incredibly important that we pass these by reference

    extern void gdt_load(GDT::DescriptorTable::EntryPtr& gdt_ptr);

    void call_set_gdt(GDT::DescriptorTable::EntryPtr& gdt_ptr)
    {
        gdt_load(gdt_ptr);
    }
}

/*
At entry all segment registers are loaded as 64 bit code/data segments, limits and bases are ignored since this is 64-bit mode.

The GDT register is loaded to point to a GDT, in bootloader-reclaimable memory, with at least the following entries, starting at offset 0:

    Null descriptor
    16-bit code descriptor. Base = 0, limit = 0xffff. Readable.
    16-bit data descriptor. Base = 0, limit = 0xffff. Writable.
    32-bit code descriptor. Base = 0, limit = 0xffffffff. Readable.
    32-bit data descriptor. Base = 0, limit = 0xffffffff. Writable.
    64-bit code descriptor. Base and limit irrelevant. Readable.
    64-bit data descriptor. Base and limit irrelevant. Writable.
*/
void Kernel::intialize_gdt()
{   
    GDT::SegmentOptions null_segment_options;

    GDT::SegmentOptions kernel_code_segment_options;
    kernel_code_segment_options.base = 0;
    kernel_code_segment_options.limit = 0xFFFF; // Big number
    kernel_code_segment_options.descriptor_type = GDT::DescriptorType::CodeOrData;
    kernel_code_segment_options.granularity = GDT::Granularity::FourKilobytes;
    kernel_code_segment_options.long_mode = GDT::LongMode::Enabled;
    kernel_code_segment_options.operation_size = GDT::OperationSize::Bits16;
    kernel_code_segment_options.present = GDT::Present::Yes;
    kernel_code_segment_options.privilege_level = GDT::PrivilegeLevel::Ring0;
    kernel_code_segment_options.system_availability = GDT::SystemAvailability::NotAvailable;
    kernel_code_segment_options.segment_type = GDT::SegmentType::Code;
    kernel_code_segment_options.code_segment = GDT::CodeSegmentType::ExecuteRead;

    GDT::SegmentOptions kernel_data_segment_options;
    kernel_data_segment_options.base = 0;
    kernel_data_segment_options.limit = 0xFFFF; // Big number
    kernel_data_segment_options.descriptor_type = GDT::DescriptorType::CodeOrData;
    kernel_data_segment_options.granularity = GDT::Granularity::FourKilobytes;
    kernel_data_segment_options.long_mode = GDT::LongMode::Enabled;
    kernel_data_segment_options.operation_size = GDT::OperationSize::Bits16;
    kernel_data_segment_options.present = GDT::Present::Yes;
    kernel_data_segment_options.privilege_level = GDT::PrivilegeLevel::Ring0;
    kernel_data_segment_options.system_availability = GDT::SystemAvailability::NotAvailable;
    kernel_data_segment_options.segment_type = GDT::SegmentType::Code;
    kernel_data_segment_options.code_segment = GDT::CodeSegmentType::ExecuteRead;

    gdt.initialize(null_segment_options, kernel_code_segment_options, kernel_data_segment_options);

    call_set_gdt(*gdt.GetPtr());
}