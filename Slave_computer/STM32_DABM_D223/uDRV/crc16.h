
#ifndef __CRC16_H_
#define __CRC16_H_
#include "main.h"



//u16 setCrc16(unsigned char *puchMsg, unsigned short usDataLen);
u16 getCrc16WithTail(unsigned char *puchMsg, unsigned short usDataLen);
u16 getCrc16ExcludeTail(unsigned char *puchMsg, unsigned short usDataLen);
//u8 checkCrc16ExcludeTail(unsigned char *puchMsg, unsigned short usDataLen);
u8 checkCrc16WithTail(unsigned char *puchMsg, unsigned short usDataLen);




#endif


