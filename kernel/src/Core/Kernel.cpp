#include "Core/Kernel.hpp"
#include "Core/TextDrawable.hpp"
#include "../bootloader/limine/limine.h"

Kernel::Kernel()
{

}

Kernel::~Kernel()
{

}

void Kernel::run()
{
  
}

extern "C" {
    extern void* isr_stub_table[];
     //Apparently it is incredibly important that we pass these by reference
    extern void idt_load(IDT::EntryPtr& idt_ptr);

    void call_set_idt(IDT::EntryPtr& idt_ptr)
    {
        asm("lidt %0" : : "m"(idt_ptr));
        asm("sti"); 
    }
}

void Kernel::initialize_idt()
{   
    uint64_t base = reinterpret_cast<uint64_t>(ISR::general_interrupt_handler);
    for(size_t i = 0; i < 32; ++i)
    {
        IDT::GateOptions error_options;
        error_options.base = base;
        error_options.gate_type = IDT::GateType::InterruptGate32;
        error_options.present = IDT::Present::Yes;
        error_options.privilege_level = IDT::PrivilegeLevel::Ring0;
        error_options.selector = LIMINE_GDT_64_CODE_SEGMENT_OFFSET;
        idt.set_entry(i, error_options);
    }

    idt.init_ptr();

    call_set_idt(*idt.get_idt_ptr());

}

void Kernel::initialize_screenmanager()
{
    screenManager.SetMode(ScreenManager::Mode::Framebuffer);
    screenManager.Initialize();

}

void Kernel::initialize_framebuffer()
{
    //screenManager.SetMode(ScreenManager::Mode::Framebuffer);
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
    16-bit code descriptor. Base = 0, limit = 0xffff. Readable. 0x08
    16-bit data descriptor. Base = 0, limit = 0xffff. Writable. 0x10
    32-bit code descriptor. Base = 0, limit = 0xffffffff. Readable. 0x18
    32-bit data descriptor. Base = 0, limit = 0xffffffff. Writable. 0x20
    64-bit code descriptor. Base and limit irrelevant. Readable.    0x28
    64-bit data descriptor. Base and limit irrelevant. Writable.    0x30
*/
void Kernel::intialize_gdt()
{   
    GDT::SegmentOptions null_segment_options;
    gdt.configure(GDT::DescriptorTable::SegmentLabel::Null, null_segment_options);
    
    GDT::SegmentOptions kernel_code_16_segment_options = GDT::SegmentOptions {
    .base                = 0,
    .limit               = 0xffff, 
    .privilege_level     = GDT::PrivilegeLevel::Ring0,
    .present             = GDT::Present::Yes,
    .descriptor_type     = GDT::DescriptorType::CodeOrData,
    .system_availability = GDT::SystemAvailability::NotAvailable,
    .long_mode           = GDT::LongMode::Disable,
    .operation_size      = GDT::OperationSize::Bits16,
    .granularity         = GDT::Granularity::FourKilobytes,
    .segment_type        = GDT::SegmentType::Code,
    .code_segment        = GDT::CodeSegmentType::ExecuteRead
    };

    gdt.configure(GDT::DescriptorTable::SegmentLabel::KernelCode16, kernel_code_16_segment_options);

    GDT::SegmentOptions kernel_data_16_segment_options = GDT::SegmentOptions {
    .base                = 0,
    .limit               = 0xffff, 
    .privilege_level     = GDT::PrivilegeLevel::Ring0,
    .present             = GDT::Present::Yes,
    .descriptor_type     = GDT::DescriptorType::CodeOrData,
    .system_availability = GDT::SystemAvailability::NotAvailable,
    .long_mode           = GDT::LongMode::Disable,
    .operation_size      = GDT::OperationSize::Bits16,
    .granularity         = GDT::Granularity::FourKilobytes,
    .segment_type        = GDT::SegmentType::Data,
    .data_segment        = GDT::DataSegmentType::ReadWrite
    };

    gdt.configure(GDT::DescriptorTable::SegmentLabel::KernelData16, kernel_data_16_segment_options);
    
    GDT::SegmentOptions kernel_code_32_segment_options = GDT::SegmentOptions {
    .base                = 0,
    .limit               = 0xffffffff, 
    .privilege_level     = GDT::PrivilegeLevel::Ring0,
    .present             = GDT::Present::Yes,
    .descriptor_type     = GDT::DescriptorType::CodeOrData,
    .system_availability = GDT::SystemAvailability::NotAvailable,
    .long_mode           = GDT::LongMode::Disable,
    .operation_size      = GDT::OperationSize::Bits32,
    .granularity         = GDT::Granularity::FourKilobytes,
    .segment_type        = GDT::SegmentType::Code,
    .code_segment        = GDT::CodeSegmentType::ExecuteRead
    };

    gdt.configure(GDT::DescriptorTable::SegmentLabel::KernelCode32, kernel_code_32_segment_options);

    GDT::SegmentOptions kernel_data_32_segment_options = GDT::SegmentOptions {
    .base                = 0,
    .limit               = 0xffffffff, 
    .privilege_level     = GDT::PrivilegeLevel::Ring0,
    .present             = GDT::Present::Yes,
    .descriptor_type     = GDT::DescriptorType::CodeOrData,
    .system_availability = GDT::SystemAvailability::NotAvailable,
    .long_mode           = GDT::LongMode::Disable,
    .operation_size      = GDT::OperationSize::Bits32,
    .granularity         = GDT::Granularity::FourKilobytes,
    .segment_type        = GDT::SegmentType::Data,
    .data_segment        = GDT::DataSegmentType::ReadWrite
    };

    gdt.configure(GDT::DescriptorTable::SegmentLabel::KernelData32, kernel_data_32_segment_options);

    GDT::SegmentOptions kernel_code_64_segment_options = GDT::SegmentOptions {
    .base                = 0,
    .limit               = 0xFFFF, 
    .privilege_level     = GDT::PrivilegeLevel::Ring0,
    .present             = GDT::Present::Yes,
    .descriptor_type     = GDT::DescriptorType::CodeOrData,
    .system_availability = GDT::SystemAvailability::NotAvailable,
    .long_mode           = GDT::LongMode::Enabled,
    .operation_size      = GDT::OperationSize::Bits16,
    .granularity         = GDT::Granularity::FourKilobytes,
    .segment_type        = GDT::SegmentType::Code,
    .code_segment        = GDT::CodeSegmentType::ExecuteRead
    };

    gdt.configure(GDT::DescriptorTable::SegmentLabel::KernelCode64, kernel_code_64_segment_options);
   
    GDT::SegmentOptions kernel_data_64_segment_options = GDT::SegmentOptions {
    .base                = 0,
    .limit               = 0xFFFF, 
    .privilege_level     = GDT::PrivilegeLevel::Ring0,
    .present             = GDT::Present::Yes,
    .descriptor_type     = GDT::DescriptorType::CodeOrData,
    .system_availability = GDT::SystemAvailability::NotAvailable,
    .long_mode           = GDT::LongMode::Enabled,
    .operation_size      = GDT::OperationSize::Bits16,
    .granularity         = GDT::Granularity::FourKilobytes,
    .segment_type        = GDT::SegmentType::Data,
    .data_segment        = GDT::DataSegmentType::ReadWrite
    };

    gdt.configure(GDT::DescriptorTable::SegmentLabel::KernelData64, kernel_data_64_segment_options);

    gdt.init_ptr();

    call_set_gdt(*gdt.GetPtr());
}

void Kernel::initialize_memory(struct limine_memmap_response* memmap)
{
    physicalMemoryManager.Initialize(memmap);

    void* page = physicalMemoryManager.AllocatePage();
    if(page != nullptr)
    {
        //It worked!
    }

    physicalMemoryManager.FreePage(page);
}

void Kernel::initialize_paging()
{
    virtualMemoryManager.Initialize(&physicalMemoryManager);
    virtualMemoryManager.CreateKernelHeap(15000);
    
}