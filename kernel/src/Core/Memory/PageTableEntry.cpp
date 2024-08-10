#include "Core/Memory/PageTableEntry.hpp"
#include "C++/byte.hpp"
#include "C++/type_traits.hpp"

namespace Memory {
    namespace Paging {
    PageTableEntry::PageTableEntry() : 
        present(0), read_write(0), user(0), write_through(0),
        cache_disable(0), accessed(0), dirty(0), huge_page(0),
        global(0), address(0), no_execute(0), reserved(0) 
        {}

    PageTableEntry::~PageTableEntry()
    {

    }

    // Initialize the entry with specific options and a physical address
    void PageTableEntry::initialize(PageTableEntryOptions options, uint64_t address)
    {
            memset(this, 0, sizeof(PageTableEntry));
            present       = blib::bit_cast<uint8_t>(options.present);
            read_write    = blib::bit_cast<uint8_t>(options.read_write);
            user          = blib::bit_cast<uint8_t>(options.user);
            write_through = blib::bit_cast<uint8_t>(options.write_through);
            cache_disable = blib::bit_cast<uint8_t>(options.cache_disable);
            accessed      = blib::bit_cast<uint8_t>(options.accessed);
            dirty         = blib::bit_cast<uint8_t>(options.dirty);
            huge_page     = blib::bit_cast<uint8_t>(options.huge_page);
            global        = blib::bit_cast<uint8_t>(options.global);
            address       = blib::extractBits<uint64_t, uint64_t, 40, 12>(address);  // Store the address with a shift to fit in the bitfield
            no_execute    = blib::bit_cast<uint8_t>(NoExecute::No);
    }



    }
}