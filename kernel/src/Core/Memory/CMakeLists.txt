set(MEMORY_SOURCES 
${CMAKE_SOURCE_DIR}/kernel/src/Core/Memory/PageTable.cpp
${CMAKE_SOURCE_DIR}/kernel/src/Core/Memory/PageTableEntry.cpp
${CMAKE_SOURCE_DIR}/kernel/src/Core/Memory/PhysicalMemoryManager.cpp
${CMAKE_SOURCE_DIR}/kernel/src/Core/Memory/VirtualMemoryManager.cpp
)


add_library(bados_mem ${MEMORY_SOURCES})
target_include_directories(bados_mem PUBLIC ${CMAKE_SOURCE_DIR}/kernel/include)
target_include_directories(bados_mem PUBLIC ${CMAKE_SOURCE_DIR}/bootloader)