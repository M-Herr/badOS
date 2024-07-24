; Enter protected mode


[bits 16]

elevate_bios:
    ;Start by clearing interrupts
    cli

    ;Need to load the gdt for 32 bit mode
    lgdt[gdt_32_descriptor]

    ; Enable 32 bit mode by setting bit 0 of the original
    ; control reigster.  Can't be done directly.  Need to 
    ; copy the contents into eax and back again
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax

    ; clear pipeline of all 16 bit instructions
    ; do this with a far jump
    jmp code_seg:init_pm

    [bits 32]
    init_pm:

    ; Now in 32 bit mode.  Tell segment register to point to flat-mode data semgnet

    mov ax, data_seg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Reset stack pointers
    mov ebp, 0x90000
    mov esp, ebp

    jmp begin_protected


