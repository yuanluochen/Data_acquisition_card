#ifndef __ADCFUNCTION_H_
#define __ADCFUNCTION_H_

#include "main.h"

/* 采集线程: 周期性把 FPGA 的 8 路 ADC 原始值发给上位机 */
void adcFunction_thread(void);

/* 系统时基任务 (TIM12), 简易版本保留为空实现 */
void adcFunction_tim_task(void);

#endif
