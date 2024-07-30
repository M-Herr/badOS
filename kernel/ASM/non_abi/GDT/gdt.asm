section .text
global gdt_load

gdt_load:
  lgdt [rdi]

  ; Set the segment registers to appropriate values for kernel mode
  mov ax, 0x10 ; Kernel data segment
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  pop rdi

  mov rax, 0x08 ; Kernel code segment
  push rax
  push rdi
  retfq