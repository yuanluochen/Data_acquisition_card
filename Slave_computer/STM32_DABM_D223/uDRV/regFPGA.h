#ifndef __REG_FPGA_H
#define __REG_FPGA_H

#include "main.h"
#pragma pack(1)

void irq_spi_read();
void irq_spi_write();
void rtos_spi_read();
void rtos_spi_write();

typedef struct{
u8 	RESERVE;//	0
u8 	REG_A2F_SRAM_WORK_MODE;//	1
//bit0 reg_sram_workEnable
u8 	REG_A2F_SRAM_EXIT_TRIG;//	2
u8 	REG_A2F_SRAM_RECORD_MAX_LEN1;//	3
u8 	REG_A2F_SRAM_RECORD_MAX_LEN2;//	4
u8 	REG_A2F_SRAM_RECORD_MAX_LEN3;//	5

u8 	REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX1;//	6
u8 	REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX2;//	7
u8 	REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX3;//	8

u8 	REG_A2F_FPGA_ADC_CH_ENABLE;//	9
u8 	REG_A2F_FPGA_ADC_CH_ENABLE_TOTAL;//	10
u8 	REG_A2F_FPGA_ADC_DIFF_ENABLE;//	11
}regA2FMap;

typedef struct{

u8 	RESERVE;//	0
u8 	REG_F2A_SRAM_WORK_MODE;//	1
u8 	REG_F2A_FIFO_IN_ADDR;//	2
u8 	REG_F2A_DIN;//	3
u8 	REG_A2F_SRAM_BUF_CNT;//	4

}regF2AMap;

enum _fpgaWorkMode
{
    _fpgaWorkMode_stop = 0,
    _fpgaWorkMode_writeSram = 1,
    _fpgaWorkMode_readSram = 2,
    _fpgaWorkMode_readFito = 3,
    _fpgaWorkMode_initSram = 0xff,

};

extern regA2FMap _regA2FMap;
extern regF2AMap _regF2AMap;
#pragma pack()
#endif



