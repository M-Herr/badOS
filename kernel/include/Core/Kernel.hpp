#pragma once
#include "Core/Structures/GDT/GlobalDescriptorTable.hpp"
#include "Core/Structures/IDT/IDT.hpp"
#include "Core/Fonts/FontParser.hpp"

#include "Core/Interfaces/ScreenManager.hpp"
#include "Core/Memory/PhysicalMemoryManager.hpp"
#include "Core/Memory/VirtualMemoryManager.hpp"

struct memmap;
extern ScreenManager screenManager;

class Kernel
{
    public:
    Kernel();

    ~Kernel();

    void run();

    void initialize_framebuffer();

    void initialize_screenmanager();

    void initialize_idt();

    void intialize_gdt();

    void initialize_memory(struct limine_memmap_response* memmap);

    void initialize_paging();

    GDT::DescriptorTable gdt;
    IDT::InterruptDescriptorTable idt;

    Core::Fonts::FontParser font_parser;
    
    Memory::PhysicalMemoryManager physicalMemoryManager;
    Memory::VirtualMemoryManager virtualMemoryManager;
    
};