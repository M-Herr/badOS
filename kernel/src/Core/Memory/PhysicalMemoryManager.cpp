#include "Core/Memory/PhysicalMemoryManager.hpp"


namespace Memory {

    PhysicalMemoryManager::PhysicalMemoryManager()
    {
        
    }

    PhysicalMemoryManager::~PhysicalMemoryManager()
    {

    }

    void PhysicalMemoryManager::Initialize(struct limine_memmap_response* memmap) 
    {
        for (size_t i = 0; i < memmap->entry_count; ++i) 
        {
            struct limine_memmap_entry* entry = memmap->entries[i];
            if (entry != nullptr) 
            {
                if (entry->type == LIMINE_MEMMAP_USABLE) 
                {
                    totalFrames += entry->length / PAGE_SIZE;
                } else {
                    for (uint64_t j = entry->base / PAGE_SIZE; 
                    j < (static_cast<uint64_t>(entry->base) + entry->length) / PAGE_SIZE && j < MAX_FRAMES; 
                    ++j) 
                    {
                    
                        {
                            bitmap.Set(j); // Mark non-usable frames
                        }

                    }
                }
            }
        }

        freeFrames = totalFrames - usedFrames; // Initialize freeFrames
    }

    void* PhysicalMemoryManager::AllocatePage() {
        size_t freeFrame = FirstFree();
        if (freeFrame == 0xFFFFFFFFF) {
            return nullptr; // Out of memory
        }

        bitmap.Set(freeFrame);
        --freeFrames;
        ++usedFrames;

        return reinterpret_cast<void*>(freeFrame * PAGE_SIZE);
    }

    void PhysicalMemoryManager::FreePage(void* address) {
        size_t frame = reinterpret_cast<size_t>(address) / PAGE_SIZE;
        bitmap.Reset(frame);
        ++freeFrames;
        --usedFrames;
    }

    size_t PhysicalMemoryManager::FirstFree() const 
    {
        for (size_t i = 0; i < totalFrames; ++i) {
            if (!bitmap.Test(i)) {
                return i;
            }
        }
        return 0xFFFFFFFFF;  // No free frame found
    }
}