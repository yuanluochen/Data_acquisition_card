#ifndef _AD7606_H
#define _AD7606_H

#include "main.h"

void qspiAdcTimTask(void);
void adc_dac_paramCalcThread(void);
#pragma pack(1)
typedef struct{

	s16 getAdc[9];
	
	u8 getAdc_BufIndex256;
	s16 getAdc_Buf256[8][256];
	
	u16 getAdc_BufIndex1000;
	s16 getAdc_Buf1000[8][1000];
	
	u16 adc_collectIndex;
	
	u16 trig_cnt;
	u16 trig_flag;
	u16 trig_Data_t;
	u8 recordAB_flag;
	//u16 dmaFifoFlag;
	
	u8 adc_BufIndex;
	u8 adc_BufIndexHis;
	u8 adc_BufIndexGap;

}__UADC;
#pragma pack()

extern __UADC _uadc;

#pragma pack(1)
typedef struct {
	u16 data[8]; 
	u8 din;
}f2a_qspiAdc_FIFO_BufSturct;
#pragma pack()

#pragma pack(1)
typedef struct {
	f2a_qspiAdc_FIFO_BufSturct fifo[500]; 
}f2a_qspiAdcBufSturct;
#pragma pack()

#endif


