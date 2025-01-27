#include "./lib/IDT.h"

void idt_init(void){
    u64 keyboard_address;
    u64 idt_address;
    u64 idt_ptr[2];

    keyboard_address = (u64)keyboard_handler; 
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    write_port(0x20 , 0x11);
    write_port(0xA0 , 0x11);

    write_port(0x21 , 0x20);
    write_port(0xA1 , 0x28);

    write_port(0x21 , 0x00);  
    write_port(0xA1 , 0x00);  

    write_port(0x21 , 0x01);
    write_port(0xA1 , 0x01);

    write_port(0x21 , 0xff);
    write_port(0xA1 , 0xff);

    idt_address = (u64)IDT ;
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16 ;

    load_idt(idt_ptr);
}