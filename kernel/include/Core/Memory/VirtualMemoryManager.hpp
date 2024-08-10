#pragma once
#include <Types.hpp>
#include "Core/Memory/Constants.hpp"
#include "Core/Memory/PageTable.hpp"
#include "Core/Memory/PageTableEntry.hpp"
#include "Core/Memory/PhysicalMemoryManager.hpp"

namespace Memory
{
    class VirtualMemoryManager
    {
        public:
        VirtualMemoryManager();
        ~VirtualMemoryManager();

        void Initialize(PhysicalMemoryManager* physicalMemoryManager_in);
        void MapPage(uint64_t virtualAddress, uint64_t physicalAddress,  Paging::PageTableEntryOptions options);
        void AllocatePage();
        void CreateKernelHeap(size_t heapSize_in);
        
        void MapKernelSegmentsToHigherHalf();

        inline uint64_t GetKernelSize() { return kernelSize;}
        
        public:
        
        private:
        //Page table instances
        Paging::PageTable pageMapLevel4;
        Paging::PageTable pageDirectoryPointerTable;
        Paging::PageTable pageDirectory;
        Paging::PageTable pageTable;
        
        Paging::PageTableEntryOptions defaultOptions;

        uint64_t KernelHeapAddressBegin;
        uint64_t CurrentKernelHeapPosition;

        PhysicalMemoryManager* physicalMemoryManager;

        size_t heapSizeSetting;
        size_t heapSizeUsed;
        
        uint64_t kernelSize;

        private:
        Paging::PageTableEntry* TraversePageHeirarchy(uint64_t virtualAddress,  Paging::PageTableEntryOptions options);


    };
}