#include "./include/stdio.h"
#include "./include/stdint.h"
#include "./include/disk.h"


void _start(void){
    char buffer[512];
    LBAInit();
    
    LBARead(0, buffer);
    char msg[] = "Hello World!";
    puts(msg);
    
    
    return;
}