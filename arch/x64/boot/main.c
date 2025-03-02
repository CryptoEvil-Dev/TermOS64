void main(void){
    char* __vidmem = (char*)0xb8000;
    __vidmem[0] = 'x';
    __vidmem[1] = 0x07;
    __vidmem[2] = '6';
    __vidmem[3] = 0x07;
    __vidmem[4] = '4'; 
    __vidmem[5] = 0x07;
    __vidmem[6] = ' '; 
    __vidmem[7] = 0x07;
    __vidmem[8] = 'C'; 
    __vidmem[9] = 0x07;

    return;   
}
