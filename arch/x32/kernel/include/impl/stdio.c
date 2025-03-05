#include "./../stdio.h"


int _pos = 0;
char* _vidptr = (char*)VIDMEM;
char _color = 0x07;

void put(char _sym) {
    *_vidptr = _sym;
    _vidptr++;
    *_vidptr = _color;
    _vidptr++;

}

void puts(char* _str){
    int pos = 0;
    while(_str[pos] != '\0'){
        put(_str[pos]);
        pos++;
    }
}

void putstr(const char* _str, int size){
    for(int i = 0; i < size; i++){
        put(_str[i]);
    }
}

void __print_digits(int n) {
        if (n / 10 != 0) {
            __print_digits(n / 10);  // Рекурсивно вызываем для старших разрядов
        }
        put((n % 10) + '0');  // Выводим текущую цифру
    }


void putint(int num){
    if(num < 0){
        put('-');
        num = -num;
    }

    

    if (num == 0) {
        put('0');  // Если число равно 0, просто выводим '0'
    } else {
        __print_digits(num);  // Иначе выводим все цифры числа
    }

}