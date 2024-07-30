#pragma once
#include <Types.hpp>
#include "C++/type_traits.hpp"
#include "C++/byte.hpp"
#include "C++/enum_bitmask.hpp"

//We could assign this integer values, 0, 1, 2 etc
//But I think this is more descriptive.

//Data segment type, bit 11 = 0
// bit 10: Expansion Direction (1 expand down, 0 expand up)
// bit 9: Write(1 Read/Write, 0 read only)
// bit 8: Accessed (1 accessed, 0 ...not accessed?)
enum class DataSegmentType : uint8_t
{
    ReadOnly                    = 0b0000, //0
    ReadOnlyAccessed            = 0b0001,
    ReadWrite                   = 0b0010,
    ReadWriteAccessed           = 0b0011,
    ReadOnlyExpandDown          = 0b0100,
    ReadOnlyExpandDownAccessed  = 0b0101,
    ReadWriteExpandDown         = 0b0110,
    ReadWriteExpandDownAccessed = 0b0111 // 7
};

template<>
struct FEnableBitMaskOperators<DataSegmentType> {
    static constexpr bool enable = true;
};
//Code segment type, 
// bit 11 = 1
// bit 10: Conforming ( 1 conforming, 0 ....not conforming?)
// bit 9: Read (1 Read, 0 no read)
// bit 8: Accessed ( 1 accessed, 0 ..not accessed?)

enum class CodeSegmentType : uint8_t
{
    ExecuteOnly                    = 0b1000,//8 etc
    ExecuteOnlyAccessed            = 0b1001,
    ExecuteRead                    = 0b1010,
    ExecuteReadAccessed            = 0b1011,
    ExecuteOnlyConforming          = 0b1100,
    ExecuteOnlyConformingAccessed  = 0b1101,
    ExecuteReadConfirming          = 0b1110,
    ExecuteReadConformingAccessed  = 0b1111 // 15
};

template<>
struct FEnableBitMaskOperators<CodeSegmentType> {
    static constexpr bool enable = true;
};

template <typename T, typename U, size_t N, size_t Pos>
T extractBits(U value) {
    static_assert(N > 0 && N <= 64, "Number of bits to extract must be between 1 and 64");
    
    // Create a mask with N bits set to 1
    U mask = (1U << N) - 1;
    
    // Shift the mask to the correct position and apply it to the value
    return static_cast<T>((value >> Pos) & mask);
}

// Helper function template to deduce types automatically
template <size_t N, size_t Pos, typename T = uint32_t, typename U = uint32_t>
auto extractBitsHelper(U value) {
    return extractBits<T, U, N, Pos>(value);
}

struct SegmentDescriptor
{
    uint16_t limit_lower: 16;
    uint16_t base_low: 16;
    uint8_t base_middle : 8;
    uint8_t segment_type : 4;
    uint8_t descriptor_type : 1;
    uint8_t privilege_level : 2;
    uint8_t present : 1;
    uint8_t limit_upper : 4;
    uint8_t system_availability: 1;
    uint8_t long_mode : 1;
    uint8_t default_operation_size : 1;
    uint8_t granularity : 1;
    uint8_t base_high : 8;

    void set_base(uint32_t base)
    {
        base_low = extractBitsHelper<16, 0>(base);
        base_middle = extractBitsHelper<8, 16>(base);
        base_high = extractBitsHelper<8, 24>(base);
        system_availability = 0b0;
    }

    void set_limit(uint32_t limit)
    {
        //20 bit number, so just use the lower 20 bits of the 32 bit
        //unsigned integer 
        limit_lower = extractBitsHelper<16, 0>(limit);
        limit_upper = extractBitsHelper<4, 16>(limit);
    }

    void set_data_segment_type(DataSegmentType data_segment_type)
    {
        segment_type = blib::bit_cast<uint8_t>(data_segment_type);
    }

    void set_code_segment_type(CodeSegmentType code_segment_type)
    {
        segment_type = blib::bit_cast<uint8_t>(code_segment_type);
    }

    void set_present(bool yes_no)
    {
        if(yes_no)
        {
            present = 0b1;
        }
        else 
        {
            present = 0b0;
        }
    }

    void set_descriptor_type(bool yes_no)
    {
        if(yes_no)
        {
            descriptor_type = 0b1; //code or data
        }
        else
        {
            descriptor_type = 0b0; // System
        }
        
    }

    void set_granularity(bool yes_no)
    {
        if(yes_no)
        {
            granularity = 0b1; // 4 GB max
        }
        else 
        {
            granularity = 0b0; // 1 Mb max
        }
    }

    void set_long_mode(bool yes_no)
    {
        if(yes_no)
        {
            long_mode = 0b1;
        }
        else 
        {
            long_mode = 0b0;
        }
    }

    void set_default_op(bool yes_no)
    {    
        default_operation_size = 0b0; //16   D bit cleared when in long mode
    }

    void set_privelage_level(uint8_t level = 0)
    {
        privilege_level = level & 0x3;
    }

} __attribute((packed));

