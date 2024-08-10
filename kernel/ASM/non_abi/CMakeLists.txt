SET(NON_ABI_SOURCE
${CMAKE_SOURCE_DIR}/GDT/gdt.asm
${CMAKE_SOURCE_DIR}/IDT/idt.asm
${CMAKE_SOURCE_DIR}/Paging/paging.asm
)

add_custom_target(assemble_non_abi ALL  # 'ALL' ensures it's built by default
    DEPENDS ${NON_ABI_SOURCE}  # Depend on the source files
)

# Add custom commands to assemble each non-ABI assembly file
foreach(source_file ${NON_ABI_SOURCE})
    get_filename_component(obj_file ${source_file} NAME_WE)  # Extract filename without extension
    set(obj_file ${NON_ABI_OBJ_DIR}/${obj_file}.o)  # Construct the object file path

    add_custom_command(
        OUTPUT ${obj_file}
        COMMAND nasm 
            ${NASM_FLAGS_${CMAKE_BUILD_TYPE}}  # Use flags based on build type
            ${source_file} -o ${obj_file}
        DEPENDS ${source_file}  # Make the command depend on the source file
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}  # Set the working directory
    )

    # Add the generated object file to the 'bados_kernel' target
    target_sources(bados_kernel PRIVATE ${obj_file})
endforeach()