 


[bits 16]
;Define load_sectors
; 
load_bios:
    push ax
    push bx  ; Sector start
    push cx  ; Number of sectors
    push dx  ; Destination address

    push cx ; Safe number of sectors to read

    mov ah, 0x02 ; Set ah to high for ATA Read Bios Utility

    mov al, cl ; Number of sectors to read move to a1 for input

    mov cl, bl ; Sector to read must be in c1

    mov bx, dx ; Destination address must be in bx

    ; Need actualy values for real hardwar, but for qemu - 0 is fine
    mov ch, 0x00 ; Cylinder goes in ch
    mov dh, 0x00 ; Cylinder head in dh

    mov dl, byte[boot_drive]
    
    ; Interrupt to read
    int 0x13

    ; Bios will set cary bit in 8086 special register. Jump to error
    ; function if the carry bit is set
    jc bios_disk_error

    ;Make sure the correct amount was read
    pop bx
    cmp al, bl
    jne bios_disk_error

    mov bx, success_msg
    call print_bios

    pop dx
    pop cx
    pop bx
    pop ax

    ret

bios_disk_error:
    ; print out the error code
    mov bx, error_msg
    call print_bios

    ; Error code is in ah
    shr ax, 8
    mov bx, ax

    jmp $

error_msg:              db `\r\nERROR Loading Sectors. Code: `, 0
success_msg:            db `\r\nAdditional Sectors Loaded Successfully!\r\n`, 0

