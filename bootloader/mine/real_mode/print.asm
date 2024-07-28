[bits 16] ; Define function

print_bios:
; Save ax and bx 
push ax
push bx

; Use interrupt 0x10 to print something to the screen. Action
; taken depends on valuer of register ax. Set 0x0E in the high
; bits of register ax(ah - a high)

mov ah, 0x0E
; String size is unkown, loop to print it all
print_bios_loop:

; Get value of register by specifying size and using square brackets
; byte[bx]
; Use this to check for null terminator

cmp byte[bx], 0
je print_bios_end

; At this point we want to print a character
; MOve the character to al, then call the interrupt(0x10)

mov al, byte[bx] ; Move character in ax low
int 0x10 ; call the interrupt

inc bx ; increment pointer
jmp print_bios_loop ; start the loop over


print_bios_end:

    ; Restore values of ax and bx
    pop bx
    pop ax

    ret




