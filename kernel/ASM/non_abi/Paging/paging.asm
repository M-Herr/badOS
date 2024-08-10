section .text
global LoadPageMapLevel4
global EnablePaging


LoadPageMapLevel4:
    cli ; disable interupts
    mov cr3, rdi ; Move rdi(first argument)-> cr3
    ret

EnablePaging:
    mov rax, cr0 ; cr0 -> rax
    or rax, 0x80000000 ; Set PG bit ( bit 31) in rax
    mov cr0, rax ; rax -> cr0
    sti
    ret
