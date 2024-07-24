; GDT


;Set up GDT in Flat mode


gdt_32_start:
    ; Define required null entry
    gdt_32_null:
    dd 0x00000000
    dd 0x00000000
gdt_32_code: 
    ; Base:     0x00000
    ; Limit:    0xFFFFF
    ; 1st Flags:        0b1001
    ;   Present:        1
    ;   Privelege:      00
    ;   Descriptor:     1
    ; Type Flags:       0b1010
    ;   Code:           1
    ;   Conforming:     0
    ;   Readable:       1
    ;   Accessed:       0
    ; 2nd Flags:        0b1100
    ;   Granularity:    1
    ;   32-bit Default: 1
    ;   64-bit Segment: 0
    ;   AVL:            0
    dw 0xFFFF     ; Limit
    dw 0x0000     ; Base
    db 0x00
    db 0b10011010 ;1st Flags, Type flags
    db 0b11001111 ; 2nd flags, limit
    db 0x00       ; Base
gdt_32_data:
    dw 0xFFFF     ; Limit
    dw 0x0000     ; Base
    db 0x00
    db 0b10010010 ;1st Flags, Type flags
    db 0b11001111 ; 2nd flags, limit
    db 0x00       ; Base
gdt_32_end:
    
gdt_32_descriptor:
    dw gdt_32_end - gdt_32_start -1     ; size of gdt
    dd gdt_32_start                     ;start of gdt

code_seg: equ gdt_32_code - gdt_32_start
data_seg: equ gdt_32_data - gdt_32_start