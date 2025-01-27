[BITS 64]
global Execute ; rcx - Адрес начала ELF-программы

Execute:
    push rax
    push rdx

    mov QWORD [ELF_HEAD_PTR], rcx
    mov rax, rcx
    add rax, 23
    mov rdx, [rax]
    mov QWORD [ELF_ENTRY_OFF], rdx
    sub rax, 23
    add rax, rdx
    call rax

    ret


ELF_HEAD_PTR: dq 0x00
ELF_ENTRY_OFF: dq 0x00