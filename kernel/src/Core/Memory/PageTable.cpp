#include "Core/Memory/PageTable.hpp"
#include "C++/type_traits.hpp"
#include "C++/byte.hpp"

namespace Memory
{
    namespace Paging {
    PageTable::PageTable()
    : memoryAllocated(0)
    {

    }


    PageTable::~PageTable()
    {

    }


    void PageTable::Initialize()
    {
        for(size_t i = 0; i < numberOfPageTables; ++i)
        {
            entries[i].initialize({}, 0);
        }
    }

    void PageTable::Initialize(void* entriesAddress)
    {

    }

    void PageTable::MapPage(uint64_t virtual_address, uint64_t physical_address, PageTableEntryOptions options)
    {
        PageTableEntry* entry = GetEntry(virtual_address);
        if(entry)
        {
            entry->initialize(options, physical_address);
            memoryAllocated += Paging::numberOfBytesInPage;
        }
    }

    void PageTable::UnMapPage(uint64_t virtual_address)
    {
        PageTableEntry* entry = GetEntry(virtual_address);
        if(entry)
        {
            entry->initialize({}, 0);
            memoryAllocated -= Paging::numberOfBytesInPage;
        }
    }

    PageTableEntry* PageTable::GetEntry(uint64_t virtual_address)
    {
        uint64_t index = blib::extractBits<uint64_t, uint64_t, 9, 12>(virtual_address);
        return &entries[index];
    }

    }

  
}