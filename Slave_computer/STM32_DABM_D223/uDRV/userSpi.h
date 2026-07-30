
/*  */
#ifndef __USERSPI_H_
#define __USERSPI_H_

#include "main.h"

#pragma pack(1)
u8 spi_transmit_receive8(SPI_TypeDef *spi,u8 tx);
u16 spi_transmit_receive16(SPI_TypeDef *spi,u16 tx);



#endif


