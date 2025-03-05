/* IO Lib x32 kernel mode!
Author: Daniil K. 
*/

#ifndef _STDIO_H_
#define _STDIO_H_

#include "./stdarg.h"
#include "./stdint.h"

#define VIDMEM 0xb8000
#define VIDMEM_MAX 0xb8000 * (80*25*2)

extern int _pos;
extern char* _vidptr;
extern char _color;

void put(char _sym);
void puts(char* _str);
void putstr(const char* _str, int size);

void putint(int _digit);
void __print_digits(int n);
//void printk(const char* _str, va_list fmt, int RING, ...);
//void printf(const char* _str, va_list fmt, ...);

#endif