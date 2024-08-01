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

        if(options.segment_type == SegmentType::Code)
        {
            segment_type = blib::bit_cast<uint8_t>(options.code_segment);
        }
        else 
        {
            segment_type =  blib::bit_cast<uint8_t>(options.data_segment);
        }

        descriptor_type = blib::bit_cast<uint8_t>(options.descriptor_type);

        privilege_level = blib::bit_cast<uint8_t>(options.privilege_level);

        present = blib::bit_cast<uint8_t>(options.present);

        system_availability = blib::bit_cast<uint8_t>(options.system_availability);

        long_mode = blib::bit_cast<uint8_t>(options.long_mode);
        
        default_operation_size = blib::bit_cast<uint8_t>(options.operation_size);

        granularity = blib::bit_cast<uint8_t>(options.granularity);

    }

}