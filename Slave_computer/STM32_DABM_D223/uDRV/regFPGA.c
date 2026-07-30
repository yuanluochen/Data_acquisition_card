#include "main.h"
extern SPI_HandleTypeDef hspi1;
regA2FMap _regA2FMap;
regF2AMap _regF2AMap;
static uint8_t pTxCmd[2];

// 全局互斥标志
static u8 fpga_spi_lock = 0;

static u8 fpga_write_register(void)
{
    // 总线被读/写占用，直接退出
    if(fpga_spi_lock)
        return 0;

    __disable_irq();
    fpga_spi_lock = 1; // 上锁，禁止其他读写
    __enable_irq();

    // SPI发送逻辑不变
    HAL_GPIO_WritePin(FPGA_SPI_CS_GPIO_Port,FPGA_SPI_CS_Pin,0);
    pTxCmd[0] = 0X80;
    pTxCmd[1] = 0X0;
    HAL_SPI_Transmit(&hspi1,pTxCmd,2,1);	
    HAL_SPI_Transmit(&hspi1,(u8*)&_regA2FMap,sizeof(_regA2FMap),1);	
    HAL_GPIO_WritePin(FPGA_SPI_CS_GPIO_Port,FPGA_SPI_CS_Pin,1);

    __disable_irq();
    fpga_spi_lock = 0; // 解锁
    __enable_irq();
    return 1;
}

static u8 fpga_read_register(void)
{
    // 总线被读/写占用，直接退出
    if(fpga_spi_lock)
        return 0;

    __disable_irq();
    fpga_spi_lock = 1; // 上锁
    __enable_irq();

    // SPI读取逻辑不变
    HAL_GPIO_WritePin(FPGA_SPI_CS_GPIO_Port,FPGA_SPI_CS_Pin,0);
    pTxCmd[0] = 0X0;
    pTxCmd[1] = 0X0;
    HAL_SPI_Transmit(&hspi1,pTxCmd,2,1);	
    HAL_SPI_Receive(&hspi1,(u8*)&_regF2AMap,sizeof(_regF2AMap),1);	
    HAL_GPIO_WritePin(FPGA_SPI_CS_GPIO_Port,FPGA_SPI_CS_Pin,1);
    _adcFunctionParam.sramBufCnt = _regF2AMap.REG_A2F_SRAM_BUF_CNT;

    __disable_irq();
    fpga_spi_lock = 0; // 解锁
    __enable_irq();
    return 1;
}


void rtos_spi_read()
{
		// 写寄存器示例
	#define SPI_MAX_RETRY 1000
	u16 retry = 0;
	while(retry < SPI_MAX_RETRY)
	{
			if(fpga_read_register() == 1)
					break;
			retry++;
			HAL_Delay(1);
	}
		
}

void rtos_spi_write()
{
		// 写寄存器示例
	#define SPI_MAX_RETRY 1000
	u16 retry = 0;
	while(retry < SPI_MAX_RETRY)
	{
			if(fpga_write_register() == 1)
					break;
			retry++;
			HAL_Delay(1);
	}
	if(retry >= SPI_MAX_RETRY)
	{
			// SPI读写超时异常处理
	}
}

void irq_spi_read()
{
	fpga_read_register();
}

void irq_spi_write()
{
	fpga_write_register();
}
