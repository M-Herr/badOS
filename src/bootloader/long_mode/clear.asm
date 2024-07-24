[bits 64]

extern vga_start, vga_extent

clear_long:
    push rdi
    push rax
    push rcx

    shl rdi, 8
    mov rax, rdi

    mov al, space_char
    
    mov rax, [vga_extent]
    mov rcx, 2
    div rcx

    mov rcx, rax
    rep stosw

    pop rcx
    pop rax
    pop rdi

    ret

space_char:                 equ ` `