#include "C++/ABI/icxxabi.hpp"
#include "C++/init.hpp"
#include "Core/Interfaces/ScreenManager.hpp"
#include "bootloader/limine/limine.h"
#include "C/cmemory.hpp"

#include "Core/Kernel.hpp"

constexpr int32_t BITMAP_SIZE =  1 << 20;

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
    static volatile struct limine_memmap_request memorymap_request = {
        .id = LIMINE_MEMMAP_REQUEST,
        .revision = 0
    };

    // Finally, define the start and end markers for the Limine requests.
    // These can also be moved anywhere, to any .c file, as seen fit.
    __attribute__((used, section(".requests")))
    static volatile struct limine_hhdm_request hhdm_request = {
        .id = LIMINE_HHDM_REQUEST,
        .revision = 0

    };
    
    __attribute__((used, section(".requests")))
    static volatile struct limine_paging_mode_request paging_mode_request = {
        .id = LIMINE_PAGING_MODE_REQUEST,
        .revision = 0,
        .mode = LIMINE_PAGING_MODE_DEFAULT,
        .max_mode = LIMINE_PAGING_MODE_MAX,
        .min_mode = LIMINE_PAGING_MODE_MIN
    };
    
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
        _init();

            // Ensure the bootloader actually understands our base revision (see spec).
        if (LIMINE_BASE_REVISION_SUPPORTED == false) {
            hcf();
        }

       
        if(hhdm_request.response == nullptr || hhdm_request.response->offset == 0)
        {
            //DO a thing
        }
  
        if(paging_mode_request.response != nullptr)
        {
            //Do a thing!
        }
      
  
        kernel.initialize_screenmanager();

        kernel.initialize_framebuffer();

         kernel.intialize_gdt();
     
        kernel.initialize_idt();

        kernel.initialize_memory(memorymap_request.response);

        kernel.initialize_paging();

        kernel.run();

        // We're done, just hang...
        hcf();
    }
}