#ifndef __DDSDAC_H_
#define __DDSDAC_H_

#include "main.h"


#define DA_CS(__X) 		HAL_GPIO_WritePin(DA_CS_GPIO_Port,DA_CS_Pin,__X);
void ddsDac_tim_task();

enum _ddsDacWorkMode
{
//Ê¾²¨Æ÷Ö¸Áî
	_ddsDacWorkMode_Stop = 0x00,
	_ddsDacWorkMode_Dc = 0x01,
	_ddsDacWorkMode_Sin = 0x02,
	_ddsDacWorkMode_Triangle = 0x03,
	_ddsDacWorkMode_Square = 0x04,
	_ddsDacWorkMode_Dds = 0x05,	
	_ddsDacWorkMode_Calib = 0xff,	
};


#pragma pack(1)
typedef struct{
  u32 dacIndex[4];   
  u32 dacMaxIndex[4];   
	
  u8 ddsDacWorkMode[4];

  u32 dacCCR[4];   
	
	u16 ddsDatas[10000];
	u16 ddsDatasLen;
	u32 crc;
	u8 ddsAllCloseFlag;
}ddsDac;
#pragma pack()
extern ddsDac _ddsDac;

#endif


