#include "main.h"

extern QSPI_HandleTypeDef hqspi;

HAL_StatusTypeDef QSPI_WriteDatas_DMA(u8 cmd,u8 dummyCycle,u8* pData, uint32_t WriteAddr, uint32_t Size)
{
  QSPI_CommandTypeDef s_command;
  HAL_StatusTypeDef status;

  s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES; 
  s_command.Instruction = cmd;               
  
  s_command.AddressMode = QSPI_ADDRESS_4_LINES;        
  s_command.AddressSize = QSPI_ADDRESS_24_BITS;       
  s_command.Address = WriteAddr;                    

  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_4_LINES;             // ！！！关键：数据在四线模式下传输！！！
  s_command.NbData = Size;                            // 要发送的数据长度
  s_command.DummyCycles = dummyCycle;                       

	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;

	
  // 发送指令和数据的组合命令
  status = HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
  if (status != HAL_OK) {
    return status;
  }

  // 非阻塞DMA传输
    status = HAL_QSPI_Transmit_DMA(&hqspi, pData);
    if (status != HAL_OK) return status;
    
   // 等待DMA传输完成
   //while(HAL_QSPI_GetState(&hqspi) != HAL_QSPI_STATE_READY);
   // return QSPI_AutoPollingMemReady(&hqspi, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);

  return HAL_OK;
}

HAL_StatusTypeDef QSPI_ReadDatas_DMA(u8 cmd,u8 dummyCycle,u8* pData, uint32_t ReadAddr, uint32_t Size)
{
	// 等待DMA传输完成
//  while(HAL_QSPI_GetState(&hqspi) != HAL_QSPI_STATE_READY){};

	if(HAL_QSPI_GetState(&hqspi) != HAL_QSPI_STATE_READY != HAL_OK)
	{
			HAL_QSPI_Abort(&hqspi);
			HAL_QSPI_DeInit(&hqspi);
			HAL_QSPI_Init(&hqspi);
	}

  QSPI_CommandTypeDef s_command;
  HAL_StatusTypeDef status;

  s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES; 
  s_command.Instruction = cmd;               
  
  s_command.AddressMode = QSPI_ADDRESS_4_LINES;        
  s_command.AddressSize = QSPI_ADDRESS_24_BITS;       
  s_command.Address = ReadAddr;                    

  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_4_LINES;             // ！！！关键：数据在四线模式下传输！！！
  s_command.NbData = Size;                            // 要发送的数据长度
  s_command.DummyCycles = dummyCycle;                     

	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;

  // 发送指令和数据的组合命令
  status = HAL_QSPI_Command(&hqspi,&s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
  if (status != HAL_OK) {
    return status;
  }

  // 非阻塞DMA传输
    status = HAL_QSPI_Receive_DMA(&hqspi, pData);
    if (status != HAL_OK) return status;
    
   // 等待DMA传输完成
//  while(HAL_QSPI_GetState(&hqspi) != HAL_QSPI_STATE_READY){};
//   // return QSPI_AutoPollingMemReady(&hqspi, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
//  // 非阻塞DMA传输
//    status = HAL_QSPI_Receive(&hqspi, pData,10);
//    if (status != HAL_OK) return status;
    

  return HAL_OK;
}


HAL_StatusTypeDef QSPI_ReadDatas(u8 cmd,u8 dummyCycle,u8* pData, uint32_t ReadAddr, uint32_t Size)
{
	// 等待DMA传输完成
//  while(HAL_QSPI_GetState(&hqspi) != HAL_QSPI_STATE_READY){};

  QSPI_CommandTypeDef s_command;
  HAL_StatusTypeDef status;

  s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES; 
  s_command.Instruction = cmd;               
  
  s_command.AddressMode = QSPI_ADDRESS_4_LINES;        
  s_command.AddressSize = QSPI_ADDRESS_24_BITS;       
  s_command.Address = ReadAddr;                    

  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_4_LINES;             // ！！！关键：数据在四线模式下传输！！！
  s_command.NbData = Size;                            // 要发送的数据长度
  s_command.DummyCycles = dummyCycle;                     

	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;

  // 发送指令和数据的组合命令
  status = HAL_QSPI_Command(&hqspi,&s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
  if (status != HAL_OK) {
    return status;
  }

  // 非阻塞DMA传输
    status = HAL_QSPI_Receive(&hqspi, pData,1);
    if (status != HAL_OK) return status;
    
   // 等待DMA传输完成
//  while(HAL_QSPI_GetState(&hqspi) != HAL_QSPI_STATE_READY){};
//   // return QSPI_AutoPollingMemReady(&hqspi, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
//  // 非阻塞DMA传输
//    status = HAL_QSPI_Receive(&hqspi, pData,10);
//    if (status != HAL_OK) return status;
    

  return HAL_OK;
}