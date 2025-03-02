#ifndef _GDT_H_
#define _GDT_H_

#include "./stdint.h"

__attribute__((packed))
struct Descriptor{ // Лимит 20 бит;  Базовый Адрес 32 бита;
    u16 Limit;      // Лимит 
    u16 Base_l;     // Младшая часть Базового Адреса
    u8 Base_m;      // Средняя часть Базового Адреса
    u8 priv;        // Привилегии и тип сегмента
    u8 flags;       // 4 бита Флагов и 4 бита Лимита
    u8 Base_h;      // Старшая часть Базового Адреса
} Descriptor;

/// @brief Создать Сегмент Кода
/// @param Base Базовый адрес сегмента. Адрес начала сегмента
/// @param Limit Лимит сегмента
/// @param Granularity 1 если в страницах по 4 Кб, 0 если в байтах
/// @param Ring Уровень доступа к сегменту: 0 - Kernel Space, 3 - User Space
/// @param mod RE - Чтение и Исполнение. E - Только исполнение. A - Можно обратится из уровней доступа выше : N - Нельзя обратится и уровня доступа выше 
/// @param bytest 32 - 32 битный сегмент. 64 - 64 битный сегмент 
static struct Descriptor CreateCode(u32 Base, u32 Limit, u8 Granularity, u8 Ring, const char *mod, u8 bytest){

}
/// @brief Создать Сегмент Данных
/// @param Base Базовый адрес сегмента. Адрес начала сегмента
/// @param Limit Лимит сегмента
/// @param Granularity 1 если в страницах по 4 Кб, 0 если в байтах
/// @param Ring Уровень доступа к сегменту: 0 - Kernel Space, 3 - User Space
/// @param mod RW - Чтение и Запись. R - Только Чтение. A - Можно обратится из уровней доступа выше : N - Нельзя обратится и уровня доступа выше
/// @param bytest 32 - 32 битный сегмент. 64 - 64 битный сегмент 
static struct Descriptor CreateData(u32 Base, u32 Limit, u8 Granularity, u8 Ring, const char *mod, u8 bytest){

}
/// @brief Создать сегмент для TSS (Task Statement Segment)
static struct Descriptor CreateTSS(){

}
/// @brief Создать сегмент для LDT (Local Descriptor Table)
static struct Descriptor CreateLDT(){

}

#endif