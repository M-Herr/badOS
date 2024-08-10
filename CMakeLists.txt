cmake_minimum_required(VERSION 3.20)
project(badOS)

enable_language(ASM)


#find_package(GTest REQUIRED)


set(FLAGS_COMMON_DEBUG "-g -O0 -Wall -Wextra -std=gnu++20 -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -fPIE -m64 -march=x86-64 -mno-80387 -nostdinc -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Ikernel/include -fPIC -I. -fno-rtti -fno-exceptions")

set(FLAGS_COMMON_RELEASE 
    -O2 
    -Wall
    -Wextra 
    -std=gnu++20 
    -ffreestanding 
    -fno-stack-protector 
    -fno-stack-check 
    -fPIE 
    -m64 
    -march=x86-64 
    -mno-80387 
    -nostdinc 
    -mno-mmx 
    -mno-sse  
    -mno-sse2 
    -mno-red-zone 
    -Ikernel/include 
    -fPIC 
    -I. 
    -fno-rtti
    -fno-exceptions 
    -mcmodel=kernel
)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " -nostdlib -mcmodel=kernel -m elf_x86_64 -z text -z max-page-size=0x1000 -T ${CMAKE_SOURCE_DIR}/bootloader/limine/linker.ld -M")

set(NASM_FLAGS_DEBUG " -g -O0 -Wall -f elf64")

set(NASM_FLAGS_RELEASE " -Wall -f elf64")

if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON_RELEASE}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON_DEBUG}")
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/kernel/src/Core/Memory)
add_subdirectory(${CMAKE_SOURCE_DIR}/kernel/src/Core/Structures)

set(KERNEL_MAIN_SOURCE 
${CMAKE_SOURCE_DIR}/kernel/src/kernel_main.cpp)

add_executable(bados_kernel ${KERNEL_MAIN_SOURCE})


# Set target-specific compile options
target_compile_options(bados_kernel PRIVATE
    ${FLAGS_COMMON_${CMAKE_BUILD_TYPE}}  # Use appropriate flags based on build type
)

# Set target-specific link options
target_link_options(bados_kernel PRIVATE
    "${CMAKE_EXE_LINKER_FLAGS}"
)

target_link_libraries(bados_kernel PRIVATE bados_structures bados_mem bados_cpp)
