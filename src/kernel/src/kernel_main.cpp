#include "C++/ABI/icxxabi.hpp"
#include "Hardware/VGA/VGA.hpp"

VGATextWriter writer;

extern "C" {
    void kernel_main()
    {
        writer.clear_screen();
        writer.Write("Welcome to badOS!\n");
    }
}