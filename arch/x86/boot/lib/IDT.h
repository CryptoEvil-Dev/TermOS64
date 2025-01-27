#ifndef __IDT_H_
#define __IDT_H_

#include "./types.h"

struct IDT_entry{
    u16 offset_lowerbits;
    u16 selector;
    u8 zero;
    u8 type_attr;
    u16 offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void);
#endif