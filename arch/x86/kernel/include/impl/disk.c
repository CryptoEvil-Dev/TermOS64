#include "./../disk.h"

void LBAInit(){
    __asm__ volatile(
        // Инициализация портов
        "movw $0x1F6, %%dx\n\t"
        "movb $0xE0, %%al\n\t"
        "outb %%al, %%dx\n\t"
        :
        :
        : "dx", "al"
    );
    return;
}

void LBARead(int LBA_Sector, char *buffer) {
    __asm__ volatile(
        // Установка LBA
        "movw $0x1F3, %%dx\n\t"      // LBA Low
        "movb %b0, %%al\n\t"        // Загружаем младший байт LBA_Sector
        "outb %%al, %%dx\n\t"       // Выводим в порт
        "movw $0x1F4, %%dx\n\t"     // LBA Mid
        "movb %h0, %%al\n\t"        // Загружаем средний байт LBA_Sector
        "outb %%al, %%dx\n\t"       // Выводим в порт
        "movw $0x1F5, %%dx\n\t"     // LBA High
        "shrl $16, %0\n\t"          // Сдвигаем LBA_Sector на 16 бит вправо
        "movb %b0, %%al\n\t"        // Загружаем старший байт LBA_Sector
        "outb %%al, %%dx\n\t"       // Выводим в порт
        "movw $0x1F7, %%dx\n\t"     // Регистр команд
        "movb $0x20, %%al\n\t"      // Команда чтения сектора
        "outb %%al, %%dx\n\t"      // Выводим команду
        "1:\n\t"                    // Локальная метка для ожидания
        "inb %%dx, %%al\n\t"        // Читаем статус
        "test $0x80, %%al\n\t"      // Проверяем бит BSY
        "jnz 1b\n\t"                // Если BSY установлен, ждем
        "test $0x08, %%al\n\t"      // Проверяем бит DRQ
        "jz 1b\n\t"                 // Если DRQ не установлен, ждем
        "movw $256, %%cx\n\t"       // 256 слов (512 байт)
        "movl %1, %%edi\n\t"         // Указатель на буфер (32-битный)
        "movw $0x1F0, %%dx\n\t"      // Регистр данных
        "2:\n\t"                     // Локальная метка для чтения
        "inw %%dx, %%ax\n\t"        // Читаем слово из порта
        "stosw\n\t"                 // Сохраняем слово в буфер
        "loop 2b\n\t"               // Повторяем для всех слов
        :
        : "a"(LBA_Sector), "r"(buffer) // Входные операнды
        : "dx", "cx", "di", "memory"   // Разрушаемые регистры и память
    );
}