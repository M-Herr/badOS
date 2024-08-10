#include "Core/Memory/VirtualMemoryManager.hpp"
#include "C++/byte.hpp"

namespace Memory
{


VirtualMemoryManager::VirtualMemoryManager()
: KernelHeapAddressBegin(0), CurrentKernelHeapPosition(0), physicalMemoryManager(nullptr), heapSizeSetting(0), heapSizeUsed(0)
{

    //Set these both to the beginning of the heap address space
    KernelHeapAddressBegin = _heap_start;
    CurrentKernelHeapPosition = _heap_start;
}   

VirtualMemoryManager::~VirtualMemoryManager()
{

}

void VirtualMemoryManager::MapPage(uint64_t virtualAddress, uint64_t physicalAddress,  Paging::PageTableEntryOptions options)
{
    auto entry = TraversePageHeirarchy(virtualAddress, options);

    if(entry != nullptr)
    {
        entry->initialize(options, physicalAddress);
    }
}

Paging::PageTableEntry* VirtualMemoryManager::TraversePageHeirarchy(uint64_t virtualAddress,  Paging::PageTableEntryOptions options)
{
    //Break down indexes
    uint64_t PageMapLevel4Index             = blib::extractBits<uint64_t, uint64_t, 8, 39>(virtualAddress);
    uint64_t pageDirectoryPointerTableIndex = blib::extractBits<uint64_t, uint64_t, 8, 30>(virtualAddress);
    uint64_t PageDirectoryIndex             = blib::extractBits<uint64_t, uint64_t, 8, 21>(virtualAddress);
    uint64_t PageTableIndex                 = blib::extractBits<uint64_t, uint64_t, 8, 12>(virtualAddress);


    auto pageMapLevel4Entry = pageMapLevel4.GetEntryByIndex(PageMapLevel4Index);
    if(pageMapLevel4Entry!= nullptr) 
    {
        if(!pageMapLevel4Entry->IsPresent())
        {
            pageMapLevel4Entry->initialize(defaultOptions, reinterpret_cast<uint64_t>(physicalMemoryManager->AllocatePage()));
        }
    }

    auto pageDPTEntry = pageDirectoryPointerTable.GetEntryByIndex(pageDirectoryPointerTableIndex);
    if(!pageDPTEntry->IsPresent())
    {
        pageDPTEntry->initialize(defaultOptions, reinterpret_cast<uint64_t>(physicalMemoryManager->AllocatePage()));
    }

    auto pageDirectoryEntry = pageDirectory.GetEntryByIndex(PageDirectoryIndex);
    if(!pageDirectoryEntry->IsPresent())
    {
        pageDirectoryEntry->initialize(defaultOptions, reinterpret_cast<uint64_t>(physicalMemoryManager->AllocatePage()));
    }

    auto pageTableEntry = pageTable.GetEntryByIndex(PageTableIndex);

    return pageTableEntry;
}

void VirtualMemoryManager::AllocatePage()
{
    void* newPage = physicalMemoryManager->AllocatePage();
    if(newPage == nullptr)
    {
        //Out of Memory
    }
    else 
    {
       // MapPage(, reinterpret_cast<uint64_t>(newPage), defaultOptions);
    }


}


void VirtualMemoryManager::Initialize(PhysicalMemoryManager* physicalMemoryManager_in)
{
    physicalMemoryManager = physicalMemoryManager_in;

    using namespace Memory::Paging;

   PageTableEntryOptions options = {
            .present       =  Present::Yes,
            .read_write    =  ReadWrite::ReadWrite,
            .user          =  User::Supervisor,
            .write_through =  WriteThrough::No,
            .cache_disable =  CacheDisable::No,
            .accessed      =  Accessed::No,
            .dirty         =  Dirty::No,
            .huge_page     =  HugePage::No,
            .global        =  Global::No,
            .no_execute    =  NoExecute::No
    };

    defaultOptions = options;

    

    //Identity map lower memory
    for( size_t i = 0; i < numberOfPageTables; ++i)
    {
        pageTable.MapPage(i*numberOfBytesInPage, i*numberOfBytesInPage, options);
    }

    pageDirectory.MapPage(0, pageTable.GetPageTableAddress(), options);
    pageDirectoryPointerTable.MapPage(0, pageDirectory.GetPageTableAddress(), options);
    pageMapLevel4.MapPage(0, pageDirectoryPointerTable.GetPageTableAddress(), options);

    MapKernelSegmentsToHigherHalf();
    
    //Some ASM function calls to get paging going
    LoadPageMapLevel4(pageMapLevel4.GetPageTableAddress());

    EnablePaging();
}

void VirtualMemoryManager::MapKernelSegmentsToHigherHalf()
{
    uint64_t kernelStartPhysical = reinterpret_cast<uint64_t>(&_kernel_begin);
    kernelSize = reinterpret_cast<uint64_t>(&_kernel_end) - kernelStartPhysical;
    uint64_t kernelStartVirtual = 0xffffffff80000000;

    for(uint64_t offset = 0; offset < kernelSize; offset += Paging::numberOfBytesInPage)
    {
        MapPage(kernelStartVirtual + offset, kernelStartPhysical + offset, defaultOptions);
    }

}

//Create heap of size heapSize_in
void VirtualMemoryManager::CreateKernelHeap(size_t heapSize_in)
{
    heapSizeSetting = heapSize_in;

    size_t numPages = (heapSizeSetting + Paging::numberOfBytesInPage - 1) / Paging::numberOfBytesInPage;
    Paging::PageTableEntryOptions options = defaultOptions;
    
    options.user = Paging::User::Supervisor;
    options.huge_page = Paging::HugePage::Yes;

    for(size_t i = 0; i < numPages; ++i)
    {   
        void* physicalPage = physicalMemoryManager->AllocatePage();
        if(physicalPage == nullptr)
        {
            //Handle error
        }
        
        uint64_t physicalAddress = reinterpret_cast<uint64_t>(physicalPage);

        uint64_t virtualAddress = KernelHeapAddressBegin + (i * Paging::numberOfBytesInPage);

        MapPage(virtualAddress, physicalAddress, options);
    }

}

}

