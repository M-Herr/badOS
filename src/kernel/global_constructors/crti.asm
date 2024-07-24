section .init
global _init
_init:
    push rbp
    mov rsp, rbp
    ; gcc will put crtbegin.o's .init here

section .fini
global _fini
_fini:
    push rbp
    mov rsp, rbp
        