#include "Core/Structures/IDT/IDTEntry.hpp"
#include "C++/byte.hpp"

namespace IDT {

    Entry::Entry() : base_low(0), selector(0), ist(0), reserved0(0), gate_type(0), storage_segment(0), privilege_level(0), present(0), base_middle(0), base_high(0), reserved1(0) {}

    Entry::~Entry() {}

    void Entry::initialize(GateOptions options) 
    {
        base_low = blib::extractBits<uint64_t, uint16_t, 16, 0>(options.base);
        base_middle = blib::extractBits<uint64_t, uint16_t, 16, 16>(options.base);
        base_high = blib::extractBits<uint64_t, uint32_t, 32, 32>(options.base);
        selector = options.selector;
        gate_type = static_cast<uint8_t>(options.gate_type);
        storage_segment = 0; 
        privilege_level = static_cast<uint8_t>(options.privilege_level);
        present = static_cast<uint8_t>(options.present);
        ist = 0; 
        reserved0 = 0;
        reserved1 = 0;
    }


}
