
#ifndef __CRC16_H_
#define __CRC16_H_
#include "app/struct_typedef.h"

// uint16_t setCrc16(unsigned char *puchMsg, unsigned short usDataLen);
uint16_t getCrc16WithTail(unsigned char *puchMsg, unsigned short usDataLen);
uint16_t getCrc16ExcludeTail(unsigned char *puchMsg, unsigned short usDataLen);
// uint8_t checkCrc16ExcludeTail(unsigned char *puchMsg, unsigned short usDataLen);
uint8_t checkCrc16WithTail(unsigned char *puchMsg, unsigned short usDataLen);

#endif
