#include "./include/stdint.h"
#include "./include/disk.h"


void _start(void){
    char* _vidptr = (char*)0xb8000;
    char buffer[512];
    LBAInit();
    
    LBARead(0, buffer);

    int pos = 0;
    for(int c = 0; c < 512; c++){
        _vidptr[pos] = buffer[c];
        pos++;
        _vidptr[pos] = 0x07;
        pos++;
    }

    
    
    return;
}