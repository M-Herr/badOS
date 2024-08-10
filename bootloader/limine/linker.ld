OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(kernel_main)


PHDRS
{
    headers PT_PHDR PHDRS;
    text PT_LOAD FILEHDR PHDRS;
    rodata PT_LOAD;
    data PT_LOAD;
    dynamic PT_DYNAMIC;
}


SECTIONS 
{
    . = 0xffffffff80000000 + SIZEOF_HEADERS;
    
    _kernel_begin = .;
    
    .text : {
        *(.text .text.*)
    } :text

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .data : {
        *(.data .data.*)

        KEEP(*(.requests_start_marker))
        KEEP(*(.requests))
        KEEP(*(.requests_end_marker))
    } :data

    .dynamic : {
        *(.dynamic)
    } :data :dynamic
    

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data

    /* Define _kernel_end as the end of the .bss section */
    _kernel_end = .;

    .heap : {
        _heap_start = .;
    }

    /* Group all debug sections together at the end */
    .debug_info : {
        *(.debug_info .debug_info.*) 
    } 


    /DISCARD/ : {
        *(.eh_frame)
        *(.note .note.*)
        *(.interp)

    }
}