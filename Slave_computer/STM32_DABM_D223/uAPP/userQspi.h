
/*  */
#ifndef __USERSPI_H_
#define __USERSPI_H_

#include "main.h"


HAL_StatusTypeDef QSPI_WriteDatas_DMA(u8 cmd,u8 dummyCycle,u8* pData, uint32_t WriteAddr, uint32_t Size);
HAL_StatusTypeDef QSPI_ReadDatas_DMA(u8 cmd,u8 dummyCycle,u8* pData, uint32_t ReadAddr, uint32_t Size);
HAL_StatusTypeDef QSPI_ReadDatas(u8 cmd,u8 dummyCycle,u8* pData, uint32_t ReadAddr, uint32_t Size);



#endif


