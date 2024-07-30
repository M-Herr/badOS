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

    extern void gdt_load(GlobalDescriptorTable::GDTPtr& gdt_ptr);

    void call_set_gdt(GlobalDescriptorTable::GDTPtr& gdt_ptr)
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
    gdt.initialize();
    
    call_set_gdt(*gdt.GetPtr());
}