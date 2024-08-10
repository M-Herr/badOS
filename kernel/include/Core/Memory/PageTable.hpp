#pragma once
#include <Types.hpp>

#include "Core/Memory/PageTableEntry.hpp"


namespace Memory
{

    namespace Paging {


    static constexpr size_t numberOfPageTables = 512;
    static constexpr size_t numberOfBytesInPage = 4096;

    class PageTable
    {   
        public:
        PageTable();
        ~PageTable();
        
        void Initialize();
        void Initialize(void* entriesAddress);

        void MapPage(uint64_t virtual_address, uint64_t physical_address, PageTableEntryOptions options);
        void UnMapPage(uint64_t virtual_address);
        
        inline PageTableEntry* GetEntryByIndex(uint64_t index) { return &entries[index];}
        
        bool CreateEntry(uint64_t index, uint64_t virtualAddress);
        PageTableEntry* GetEntry(uint64_t virtual_address);
        
        inline uint64_t& GetPageTableAddress() { pageTableAddress = reinterpret_cast<uint64_t>(&entries[0]); return pageTableAddress; }

        public:
        

        private:
        alignas(4096) PageTableEntry entries[numberOfPageTables];
        bool    entryUsed[numberOfPageTables];

        uint64_t pageTableAddress;
        size_t memoryAllocated;

    };

    extern "C" 
    {
        void LoadPageMapLevel4(uint64_t PageMapLevel4Address);
        void EnablePaging();
    }

    }
}  