#pragma once
#include <Types.hpp>
#include "C++/enum_bitmask.hpp"


namespace Memory
{
    namespace Paging {
    // Page table entry options represented as enum classes.
    // Each option corresponds to a specific bit in the 64-bit page table entry.

    // Present flag (bit 0)
    // Indicates whether the page is present in memory.
    // - No (0): The page is not present in memory.
    // - Yes (1): The page is present in memory.
    enum class Present : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };
   
   
    // Read/Write flag (bit 1)
    // Controls the write permissions to the page.
    // - ReadOnly (0): The page is read-only.
    // - ReadWrite (1): The page can be read and written to.
    enum class ReadWrite : uint8_t {
        ReadOnly  = 0b0,
        ReadWrite = 0b1
    };

    // User/Supervisor flag (bit 2)
    // Controls access to the page based on privilege level.
    // - Supervisor (0): The page can only be accessed by the kernel (Ring 0).
    // - User (1): The page can be accessed by both the kernel and user-space applications.
    enum class User : uint8_t {
        Supervisor = 0b0,
        User       = 0b1
    };

    // Write-Through flag (bit 3)
    // Controls caching behavior of the page.
    // - No (0): Write-back caching is used.
    // - Yes (1): Write-through caching is used, meaning writes are immediately written to memory.
    enum class WriteThrough : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };

    // Cache Disable flag (bit 4)
    // Controls whether caching is enabled for the page.
    // - No (0): Caching is enabled for the page.
    // - Yes (1): Caching is disabled for the page.
    enum class CacheDisable : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };

    // Accessed flag (bit 5)
    // Indicates whether the page has been accessed (read or written to).
    // This bit is set by the CPU.
    // - No (0): The page has not been accessed.
    // - Yes (1): The page has been accessed.
    enum class Accessed : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };

    // Dirty flag (bit 6)
    // Indicates whether the page has been written to.
    // This bit is set by the CPU when a write occurs.
    // - No (0): The page has not been written to.
    // - Yes (1): The page has been written to (dirty).
    enum class Dirty : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };

    // Huge Page flag (bit 7)
    // Controls the page size.
    // - No (0): The page is 4 KB in size.
    // - Yes (1): The page is 2 MB (if in a page directory) or 1 GB (if in a page directory pointer table).
    enum class HugePage : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };

    // Global flag (bit 8)
    // Controls whether the page is global across all processes.
    // - No (0): The page is not global.
    // - Yes (1): The page is global and is not flushed from the TLB on a context switch.
    enum class Global : uint8_t {
        No  = 0b0,
        Yes = 0b1
    };

    // No Execute flag (bit 63)
    // Controls whether the page can be executed as code.
    // - Yes (0): The page can be executed.
    // - No (1): The page cannot be executed (NX bit).
    enum class NoExecute : uint8_t {
        Yes = 0b0,
        No  = 0b1
    };

    // Structure to group all options together for easy initialization
    struct PageTableEntryOptions {
        Present present;               // Present flag
        ReadWrite read_write;          // Read/Write flag
        User user;                     // User/Supervisor flag
        WriteThrough write_through;    // Write-Through flag
        CacheDisable cache_disable;    // Cache Disable flag
        Accessed accessed;             // Accessed flag
        Dirty dirty;                   // Dirty flag
        HugePage huge_page;            // Huge Page flag
        Global global;                 // Global flag
        NoExecute no_execute;          // No Execute flag
    };

    // Represents a single entry in a page table
    class PageTableEntry {
    public:
        uint8_t present         : 1;  // Present flag
        uint8_t read_write      : 1;  // Read/Write flag
        uint8_t user            : 1;  // User/Supervisor flag
        uint8_t write_through   : 1;  // Write-Through flag
        uint8_t cache_disable   : 1;  // Cache Disable flag
        uint8_t accessed        : 1;  // Accessed flag
        uint8_t dirty           : 1;  // Dirty flag
        uint8_t huge_page       : 1;  // Huge Page flag
        uint8_t global          : 1;  // Global flag
        uint8_t ignored         : 3;  // Ignored by the CPU
        uint8_t reserved_11     : 1;  //
        uint64_t address        : 40; // Physical address (shifted right by 12 bits)
        uint8_t no_execute      : 1;  // No Execute flag
        uint32_t reserved       : 11; // Reserved bits

    public:
        PageTableEntry();
        ~PageTableEntry();

        inline bool IsPresent() { return present;}

        // Initialize the entry with specific options and a physical address
        void initialize(PageTableEntryOptions options, uint64_t address);
    } __attribute__((packed));
    }
}

ENABLE_BM( Memory::Paging::Present);
ENABLE_BM( Memory::Paging::ReadWrite);
ENABLE_BM( Memory::Paging::User);
ENABLE_BM( Memory::Paging::WriteThrough);
ENABLE_BM( Memory::Paging::CacheDisable);
ENABLE_BM( Memory::Paging::Dirty);
ENABLE_BM( Memory::Paging::HugePage);
ENABLE_BM( Memory::Paging::Global);
ENABLE_BM( Memory::Paging::NoExecute);
