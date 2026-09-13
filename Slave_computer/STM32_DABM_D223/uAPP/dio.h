#ifndef __DIO_H_
#define __DIO_H_

#include "main.h"


void dio_tim_task();
void pwm_task_thread();

#pragma pack(1)
typedef struct{
	u8 dinAll;
	u8 doutAll;
  u8 din[8]; 
	u8 dout[2];    
	u8 pwmEnable[6];  

	u32 pwmPhaseSyncFlag;
	u32 arr[6];
	u32 psc[6];
	u32 duty[6];
	u32 phase[6];
  u32 presentFreq[6];
	u32 pwmPulseNum[6];
	u32 pwmPulseTick[6];
	u32 findDecPulseFlag[6];
	u32 pwmCalcDecPulse[6];
	
	u8 uploadFinshFlag;
}dioWorkParam;
#pragma pack()

extern dioWorkParam _dioParam;

void TIM1_task(void);
void TIM2_task(void);
void TIM3_task(void);
void TIM4_task(void);
void TIM5_task(void);
void TIM8_task(void);



#endif


