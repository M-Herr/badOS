#pragma once
#include <Types.hpp>


#ifdef USE_LIMINE
constexpr static uint32_t LIMINE_GDT_64_CODE_SEGMENT_OFFSET = 0x28;
constexpr static uint32_t LIMINE_GDT_64_DATA_SEGMENT_OFFSET = 0x30;
#endif


//Defined in the linker script
extern uint8_t _kernel_begin;
extern uint8_t _kernel_end;
extern uint8_t _heap_start;
