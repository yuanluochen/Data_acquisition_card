#ifndef __FRAM_H_
#define __FRAM_H_

#include "main.h"

void FramWriteByte(uint16_t addr, u8 data);
u8 FramReadByte(uint16_t addr);

void FramWrite(u8* data, u16 addr, u16 len);
void FramRead(u8* rdData, u16 addr, u16 len);

void FRAM_CS(u8 __X);

#endif
