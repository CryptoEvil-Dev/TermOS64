#include "./lib/asm.h"

struct iregs getregs(){
    struct iregs reg;
    asm volatile(
        "movq %%rax, %0\n"
        "movq %%rbx, %1\n"
        "movq %%rcx, %2\n"
        "movq %%rdx, %3\n"
        "movq %%rbp, %4\n"
        "movq %%rsi, %5\n"
        "movq %%rdi, %6\n"
        "movq %%rsp, %7\n"
        "movq %%r8,  %8\n"
        "movq %%r9,  %9\n"
        "movq %%r10, %10\n"
        "movq %%r11, %11\n"
        "movq %%r12, %12\n"
        "movq %%r13, %13\n"
        "movq %%r14, %14\n"
        "movq %%r15, %15\n"
        
        "pushf\n"
        "pop %16\n"
        : "=r"(reg.rax), "=r"(reg.rbx), "=r"(reg.rcx), "=r"(reg.rdx), "=r"(reg.rbp), "=r"(reg.rsi), "=r"(reg.rdi), "=r"(reg.rsp),
          "=r"(reg.r8), "=r"(reg.r9), "=r"(reg.r10), "=r"(reg.r11), "=r"(reg.r12), "=r"(reg.r13), "=r"(reg.r14), "=r"(reg.r15), "=r"(reg.flags)
        :
        : "memory"
        );
    
    return reg;
}