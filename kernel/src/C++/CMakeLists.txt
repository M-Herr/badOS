set(INIT_SOURCE
${CMAKE_SOURCE_DIR}/kernel/src/C++/init.cpp
${CMAKE_SOURCE_DIR}/kernel/src/C++/ABI/icxxabi.cpp
)

add_library(bados_abi OBJECT ${GDT_SOURCES} ${IDT_SOURCES})

target_include_directories(bados_abi PUBLIC ${CMAKE_SOURCE_DIR}/kernel/include)
target_include_directories(bados_abi PUBLIC ${CMAKE_SOURCE_DIR}/bootloader)

# Set target-specific compile options
target_compile_options(bados_abi PRIVATE
    ${FLAGS_COMMON_${CMAKE_BUILD_TYPE}}  # Use appropriate flags based on build type
)

# Set target-specific link options
target_link_options(bados_abi PRIVATE
    "${CMAKE_EXE_LINKER_FLAGS}"
)
