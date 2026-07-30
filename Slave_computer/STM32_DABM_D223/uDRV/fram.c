
#include "main.h"
extern SPI_HandleTypeDef hspi3;

void fram_tick_delay(uint32_t t)
{	
    while(t--);
}

#define WREN 0x06           //D¡ä¨º1?¨¹
#define WRDI 0x04           //???1D¡ä
#define RDSR 0x05           //?¨¢¡Á¡ä¨¬???¡ä??¡Â
#define WRSR 0x01           //D¡ä¡Á¡ä¨¬???¡ä??¡Â
#define READD 0x03          //?¨¢¡ä?¡ä¡é?¡Â¨ºy?Y
#define WRITEE 0x02         //D¡ä¡ä?¡ä¡é?¡Â¨ºy?Y

//#define FRAM_CS(__X)   HAL_GPIO_WritePin( FRAM_CS_GPIO_Port, FRAM_CS_Pin, __X )

void FRAM_CS(u8 __X)
{
	HAL_GPIO_WritePin( FRAM_CS_GPIO_Port, FRAM_CS_Pin, __X );
}

u8 framTxBuf[10],framRxBuf[10];
void FramWrite(u8* data, u16 addr,  u16 len)
{
  uint8_t temM,temL;
  temM=(uint8_t)((addr&0xff00)>>8);
  temL=(uint8_t)(addr&0x00ff);	
	
 	FRAM_CS(0);  
	framTxBuf[0] = 	WREN;
	HAL_SPI_Transmit(&hspi3,framTxBuf,1,100);	
  FRAM_CS(1);
	fram_tick_delay(80);
	
  FRAM_CS(0);
	framTxBuf[0] = 	WRITEE;
	framTxBuf[1] = 	temM;
	framTxBuf[2] = 	temL;
	HAL_SPI_Transmit(&hspi3,framTxBuf,3,100);
	HAL_SPI_Transmit(&hspi3,data,len,100);

  FRAM_CS(1);
  fram_tick_delay(80);
	
  FRAM_CS(0);
	framTxBuf[0] = 	WRDI;
	HAL_SPI_Transmit(&hspi3,framTxBuf,1,100);	
  FRAM_CS(1);
	
}

void FramRead(u8* rdData, u16 addr, u16 len)
{
  uint8_t  temM,temL;
	u8 temp;
  temM=(uint8_t)((addr&0xff00)>>8);
  temL=(uint8_t)(addr&0x00ff);
	
  FRAM_CS(0);           
	framTxBuf[0] = 	READD;
	framTxBuf[1] = 	temM;
	framTxBuf[2] = 	temL;
	HAL_SPI_Transmit(&hspi3,framTxBuf,3,100);
	HAL_SPI_Receive(&hspi3,rdData,len,100);
  FRAM_CS(1);  
	
}








