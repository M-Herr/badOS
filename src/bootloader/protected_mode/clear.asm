

[bits 32]

;Clear VGA memory
clear_protected:
    pushad

    mov ebx, vga_extent
    mov ecx, vga_start
    mov edx, 0

    ; Main loop
    clear_protected_loop:
    ; while edx < ebx
        cmp edx, ebx
        jge clear_protected_done

        push edx

        mov al, space_char
        mov ah, style_wb

        ; print character to VGA memory
        add edx, ecx
        mov word[edx], ax

        pop edx

        ; increment counter
        add edx, 2

        jmp clear_protected_loop

clear_protected_done:
    popad
    ret


space_char: equ ` `
