#pragma once
#include <Types.hpp>
#include "C++/byte.hpp"
#include "GlobalDescriptorUtils.hpp"

#define ENABLE_BM(name) \
    template<> \
    struct FEnableBitMaskOperators<name> { \
        static constexpr bool enable = true; \
    }; 

namespace GDT {

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

    enum class PrivilegeLevel : uint8_t
    {
        Ring0 = 0b00,
        Ring1 = 0b01,
        Ring2 = 0b10,
        Ring3 = 0b11
    };

    enum class Present : uint8_t
    {
        Yes = 0b1,
        No = 0b0
    };

    enum class DescriptorType : uint8_t
    {
        Sytem = 0b0,
        CodeOrData = 0b1
    };

    enum class SystemAvailability : uint8_t
    {
        NotAvailable = 0b0,
        Available = 0b1
    };

    enum class LongMode : uint8_t
    {
        Enabled = 0b1,
        Disable = 0b0
    };

    enum class OperationSize : uint8_t
    {
        Bits16 = 0b0,
        Bits32 = 0b1
    };

    enum class Granularity : uint8_t
    {
        OneByte = 0b0,
        FourKilobytes = 0b1,
    };

    //This is used like a normal enum, not bit masking
    enum class SegmentType
    {
        Code,
        Data
    };

    struct SegmentOptions {
        uint32_t base;
        uint32_t limit;
        PrivilegeLevel privilege_level;
        Present present;
        DescriptorType descriptor_type;
        SystemAvailability system_availability;
        LongMode long_mode;
        OperationSize operation_size;
        Granularity granularity;
        SegmentType segment_type;
        // Only one of these will be used, based on segment_type
        CodeSegmentType code_segment;
        DataSegmentType data_segment;
    };

    class Entry
    {
        public:
        uint16_t limit_lower : 16;           // Lower 16 bits of the segment limit
        uint16_t base_low : 16;              // Lower 16 bits of the base address
        uint8_t base_middle : 8;             // Next 8 bits of the base address
        uint8_t segment_type : 4;            // Segment type (e.g., code, data)
        uint8_t descriptor_type : 1;         // Descriptor type (0 = system, 1 = code or data)
        uint8_t privilege_level : 2;         // Descriptor privilege level (0 = kernel, 3 = user)
        uint8_t present : 1;                 // Segment present flag
        uint8_t limit_upper : 4;             // Upper 4 bits of the segment limit
        uint8_t system_availability : 1;     // System availability (usually 0)
        uint8_t long_mode : 1;               // Long mode flag (1 = 64-bit code segment)
        uint8_t default_operation_size : 1;  // Default operation size (0 = 16-bit segment, 1 = 32-bit segment)
        uint8_t granularity : 1;             // Granularity (0 = byte, 1 = 4KB)
        uint8_t base_high : 8;               // Last 8 bits of the base address
        
        public:
        Entry();
        ~Entry();

        void initialize(SegmentOptions options);
        private:

        private:
        
    }__attribute__((packed));
}


//Enable bit mask operations for all of this enum classes
ENABLE_BM(GDT::PrivilegeLevel);
ENABLE_BM(GDT::Present);
ENABLE_BM(GDT::DescriptorType);
ENABLE_BM(GDT::SystemAvailability);
ENABLE_BM(GDT::LongMode);
ENABLE_BM(GDT::OperationSize);
ENABLE_BM(GDT::Granularity);
ENABLE_BM(GDT::DataSegmentType);
ENABLE_BM(GDT::CodeSegmentType);