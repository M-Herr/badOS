[bits 64]
extern vga_start, vga_extent, style_wb
print_long:
    push rax
    push rdx
    push rdi
    push rsi

    mov rdx, vga_start
    shl rdi, 8

    print_long_loop:
        cmp byte[rsi], 0
        je print_long_done
        
        mov rax, [vga_start]
        add rax, [vga_extent]

        cmp rdx,rax
        je print_long_done

        mov rax, rdi
        mov al, byte[rsi]

        mov word[rdx], ax

        add rsi, 1
        add rdx, 2

        jmp print_long_loop

print_long_done:
    pop rsi
    pop rdi
    pop rdx
    pop rax

    ret