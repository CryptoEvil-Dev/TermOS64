#ifndef _DISK_H_
#define _DISK_H_
#include "./stdint.h"

void LBAInit();
void LBARead(int LBA_Sector, char *buffer);

#endif