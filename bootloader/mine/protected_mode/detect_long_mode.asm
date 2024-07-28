[bits 32]


detect_lm_protected:
    pushad

    ; General sequence:
    ; Check for CPUID
    ; Check for CPUID extensions
    ; Check for long mode

    pushfd
    pop eax

    ; save for later
    mov ecx, eax

    ; FLip the ID bit (21st bit of eax)
    xor eax, 1 << 21

    ; Save to flags
    push eax
    popfd

    ; read from flags
    ; Bit will be lfipped if CPUID is supported
    pushfd
    pop eax

    ;Restore

    push ecx
    popfd

    ; Perform comparison
    ; if equal cpuid is not supported
    cmp eax, ecx
    je cpuid_not_found_protected


    ; Check for extended functions

    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001             ; If result is larger thatn 0x80000001 cpuid is supported
    jb cpuid_not_found_protected

    ; Check for long mode
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz lm_not_found_protected

    popad
    ret

cpuid_not_found_protected:
    call clear_protected
    mov esi, cpuid_not_found_str
    call print_protected
    jmp $


lm_not_found_protected:
    call clear_protected
    mov esi, lm_not_found_str
    call print_protected
    jmp $

lm_not_found_str:            db `ERROR: Long mode not supported. Exiting...`, 0
cpuid_not_found_str:         db `ERROR: CPUID mode not supported. Exiting...`, 0

    