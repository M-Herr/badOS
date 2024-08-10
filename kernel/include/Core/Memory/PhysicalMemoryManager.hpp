#pragma once
#include "Types.hpp"
#include "../bootloader/limine/limine.h"
#include "C++/bitset.hpp"


namespace Memory {
    class PhysicalMemoryManager {
    public:
        static constexpr size_t PAGE_SIZE = 4096;

        // Calculate max frames based on max memory size (avoid potential overflows)
        static constexpr size_t MAX_MEMORY_SIZE = 128 * 1024 * 1024;  // 128 MB
        static constexpr size_t MAX_FRAMES = MAX_MEMORY_SIZE / PAGE_SIZE;
        static constexpr size_t BITMAP_SIZE = (MAX_FRAMES + 63) / 64;  // Use 64-bit words in the bitmap

    public:
        PhysicalMemoryManager();
        ~PhysicalMemoryManager();

        void Initialize(struct limine_memmap_response* memmap);
        void* AllocatePage();
        void FreePage(void* address);

    private:
        blib::Bitset<MAX_FRAMES, uint64_t> bitmap;  // Use uint64_t for efficiency
        size_t totalFrames = 0;
        size_t usedFrames = 0;
        size_t freeFrames = 0;

        size_t FirstFree() const;
    };
}
