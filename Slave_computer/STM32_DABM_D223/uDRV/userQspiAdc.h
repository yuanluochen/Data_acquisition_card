#ifndef _AD7606_H
#define _AD7606_H

#include "main.h"

/* TIM13 中断里调用: 读取 FPGA 当前 8 通道 ADC 原始值 */
void qspiAdcTimTask(void);

/* 主循环里调用: 计算 ADC / DAC 定时器时基 */
void adc_dac_paramCalcThread(void);

#pragma pack(1)
typedef struct
{
  s16 adc[8]; /* 8 路 ADC 原始值 */
  u8 din;     /* FPGA 数字输入 */
  u8 newFlag; /* 新数据标志 */
} __UADC;
#pragma pack()

extern __UADC _uadc;

#endif
