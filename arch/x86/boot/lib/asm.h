#ifndef __ASM_H_
#define __ASM_H_
#include "./types.h"

struct iregs
{
    u64 rax;
    u64 rbx;
    u64 rcx;
    u64 rdx;
    u64 rbp;
    u64 rsi;
    u64 rdi;
    u64 rsp;

    u64 r8;
    u64 r9;
    u64 r10;
    u64 r11;
    u64 r12;
    u64 r13;
    u64 r14;
    u64 r15;

    u64 flags;
};

struct iregs getregs();
void setregs();

u8 read_port(u32 _port);
void write_port(u32 _port, u16 _src);

// in al, dx  ; dx - порт al - регистр куда положить данные

#endif