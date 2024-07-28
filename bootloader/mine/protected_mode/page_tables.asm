; Set up page tables

;  PML4T -> 0x1000 (Page Map Level 4 Table)
;  PDPT  -> 0x2000 (Page Directory Pointer Table)
;  PDT   -> 0x3000 (Page Directory Table)
;  PT    -> 0x4000 (Page table)

[bits 32]

intialize_page_tables_protected:
    
    ;mov esi, initialize_message

    pushad
    
    mov edi, 0x1000 ; Set base address for rep stosd page table goes from 0x1000 to 0x4FFF 

    mov cr3, edi    ; save PML4T start address in cr3

    xor eax, eax    ; set eax to 0

    mov ecx, 4096   ; Repeat 4096 times.  This zeros out all 4 page tables

    rep stosd

    mov edi, cr3    ; set edi back to PML4T[0]

    ; Page tables must be aligned.  The lower 12 bits of the physic address must be 0. Then the lwoer 12 bits can
    ; be used as flags for that entry

    mov dword[edi], 0x2003 ; set PMl4T[0] to address 0x2000 with flags 0x0003
    add edi, 0x1000
    mov dword[edi], 0x3003 ; Same
    add edi, 0x1000
    mov dword[edi], 0x4003 ; Same

    ; Edit is at 0x3000

    add edi, 0x1000
    mov ebx, 0x00000003
    mov ecx, 512

    add_page_entry_protected:
        mov dword[edi], ebx
        add ebx, 0x1000
        add edi, 8

        loop add_page_entry_protected

    ; Set up PAE paging

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    popad
    ret


; Data
;initialize_message: db `INFO: Initializing page tables.`, 0