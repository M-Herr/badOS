set(GDT_SOURCES
${CMAKE_SOURCE_DIR}/kernel/src/Core/Structures/GDT/GDTEntry.cpp
${CMAKE_SOURCE_DIR}/kernel/src/Core/Structures/GDT/GlobalDescriptorTable.cpp
)

set(IDT_SOURCES
${CMAKE_SOURCE_DIR}/kernel/src/Core/Structures/IDT/IDTEntry.cpp
${CMAKE_SOURCE_DIR}/kernel/src/Core/Structures/IDT/IDT.cpp
${CMAKE_SOURCE_DIR}/kernel/src/Core/Structures/IDT/ISR.cpp
)


add_library(bados_structures OBJECT ${GDT_SOURCES} ${IDT_SOURCES})

target_include_directories(bados_structures PUBLIC ${CMAKE_SOURCE_DIR}/kernel/include)
target_include_directories(bados_structures PUBLIC ${CMAKE_SOURCE_DIR}/bootloader)


# Set target-specific compile options
target_compile_options(bados_structures PRIVATE
    ${FLAGS_COMMON_${CMAKE_BUILD_TYPE}}  # Use appropriate flags based on build type
)

# Set target-specific link options
target_link_options(bados_structures PRIVATE
    ${CMAKE_EXE_LINKER_FLAGS}
)

