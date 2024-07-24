
; ax (Accumulator)
; bx (Base)
; cx (Counter)
; dx (Data)

; Program Origin
[org 0x7c00]

[bits 16]

; Initialize base pointer and stack pointer
mov bp, 0x0500
mov sp, bp

; Save ID of the boot drive
mov byte[boot_drive], dl

mov bx, msg_hello_world
call print_bios

; Load next sector
mov bx, 0x0002

 ; load another sector
mov cx, 0x0006

mov dx, 0x7E00

; Load new secotrs
call load_bios

call elevate_bios

bootsector_hold:
jmp $       ; infinite loop


; INCLUDES
%include "real_mode/print.asm"
%include "real_mode/print_hex.asm"
%include "real_mode/load.asm"
%include "real_mode/gdt.asm"
%include "real_mode/elevate.asm"

; DATA STORAGE AREA
msg_hello_world: db `\r\nHello World, from the BIOS!\r\n`, 0

boot_drive:      db 0x00

;pad boot sector
times 510 - ($ - $$) db 0x00

; Magic number
dw 0xAA55

; SECOND SECTOR: 32 Bit Code Only
bootsector_extended:
begin_protected:

[bits 32]

; Clear VGA memory
call clear_protected

call detect_lm_protected

mov esi, protected_alert_two
call print_protected

call intialize_page_tables_protected

call elevate_protected

jmp $

; PROTECTED MODE INCLUDES

%include "protected_mode/clear.asm"
%include "protected_mode/print.asm"
%include "protected_mode/detect_long_mode.asm"
%include "protected_mode/page_tables.asm"
%include "protected_mode/gdt.asm"
%include "protected_mode/elevate.asm"

global vga_start, vga_extent, style_wb
vga_start:          equ 0x000B8000
vga_extent:         equ 80 * 25 * 2 ; width*height*bytes per cell
style_wb:           equ 0x0F  ; white on black

; messages
protected_alert_two:    db `64-bit long mode supported`, 0

times 512 - ($ - bootsector_extended) db 0x00
begin_long_mode:

[bits 64]

mov rdi, style_blue
call clear_long

mov rdi, style_blue
mov rsi, long_mode_note
call print_long

call kernel_start

jmp $

%include "long_mode/clear.asm"
%include "long_mode/print.asm"


kernel_start:           equ 0x8200
long_mode_note:         db `Now running in fully-enabled, 64-bit long mode!`, 0
style_blue:             equ 0x1F

times 512 - ($ - begin_long_mode) db 0x00
