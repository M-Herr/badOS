#include "Core/Structures/GDT/GDTEntry.hpp"


namespace GDT {
    Entry::Entry()
    {

    }

    Entry::~Entry()
    {

    }

    void Entry::initialize(SegmentOptions options)
    {
        base_low = blib::extractBitsHelper<16, 0>(options.base);
        base_middle = blib::extractBitsHelper<8, 16>(options.base);
        base_high = blib::extractBitsHelper<8, 24>(options.base);
        
        limit_lower = blib::extractBitsHelper<16, 0>(options.limit);
        limit_upper = blib::extractBitsHelper<4, 16>(options.limit);

        

    }

}