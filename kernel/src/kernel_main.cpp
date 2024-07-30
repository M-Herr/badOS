#include "C++/ABI/icxxabi.hpp"
#include "Hardware/VGA/VGA.hpp"
#include "bootloader/limine/limine.h"
#include "C/cmemory.hpp"

#include "Core/Kernel.hpp"


VGATextWriter writer;
Kernel kernel;

extern "C" {

    // Set the base revision to 2, this is recommended as this is the latest
    // base revision described by the Limine boot protocol specification.
    // See specification for further info.

    __attribute__((used, section(".requests")))
    static volatile LIMINE_BASE_REVISION(2);

    // The Limine requests can be placed anywhere, but it is important that
    // the compiler does not optimise them away, so, usually, they should
    // be made volatile or equivalent, _and_ they should be accessed at least
    // once or marked as used with the "used" attribute as done here.

    __attribute__((used, section(".requests")))
    static volatile struct limine_framebuffer_request framebuffer_request = {
        .id = LIMINE_FRAMEBUFFER_REQUEST,
        .revision = 0
    };

    __attribute__((used, section(".requests")))
    static volatile struct limine_memmap_request memorymap_request = {
        .id = LIMINE_MEMMAP_REQUEST,
        .revision = 0
    };

    // Finally, define the start and end markers for the Limine requests.
    // These can also be moved anywhere, to any .c file, as seen fit.

    __attribute__((used, section(".requests_start_marker")))
    static volatile LIMINE_REQUESTS_START_MARKER;

    __attribute__((used, section(".requests_end_marker")))
    static volatile LIMINE_REQUESTS_END_MARKER;
    
    // Halt and catch fire function.
    static void hcf(void) {
        asm ("cli");
        for (;;) {
            asm ("hlt");
        }
    }
    
    void kernel_main()
    {
        
        

            // Ensure the bootloader actually understands our base revision (see spec).
        if (LIMINE_BASE_REVISION_SUPPORTED == false) {
            hcf();
        }

        // Ensure we got a framebuffer.
        if (framebuffer_request.response == nullptr
        || framebuffer_request.response->framebuffer_count < 1) {
            hcf();
        }

        // Fetch the first framebuffer.
        struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
        
        kernel.get_framebuffer_properties(framebuffer);
        
        if(memorymap_request.response == nullptr
        || memorymap_request.response->entry_count < 1)
        {
            hcf();
        }
        
        kernel.intialize_gdt();

        kernel.initialize_idt();

        kernel.run();

        // We're done, just hang...
        hcf();
    }
}