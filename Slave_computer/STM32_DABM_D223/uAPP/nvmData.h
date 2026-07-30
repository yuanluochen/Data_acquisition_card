#ifndef _NVMDATA_H_
#define _NVMDATA_H_

#include "main.h"
#pragma pack(1)

void nvm_data_init(void);

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

typedef struct{
	u16 adc_ch_Enable;   
	u8 adc_diff_Enable;   	
	u32 samplingRate;
	u16 sramRecordMaxTime;
	u8 adcRange;
	u8 adcSignalType;
	u8 sramAdutoTrigEnable;	
	u16 trigValue;
	u8 trig_Ch;
	u8 back;
}adcParam;

typedef struct{
	u16 freq;
	u16 volt;
	u16 duty;
	u16 bias;
	u16 phase;
}ddsDacParam;

typedef struct{
	u16 pwmFreq;
	u16 pwmDuty;
	u16 pwmAccUnit;
}pwmDatas;

typedef struct{
	u8 calibEnable;
	int32 calibDigital;
	int32 calibAnalog;
}calibDatas;

typedef struct{
adcParam _adcParam;
ddsDacParam _ddsDacParam[4];

pwmDatas _pwmDatas[6];
	
//校准参数预留
calibDatas _adcCalibDatasPointA[8];
calibDatas _adcCalibDatasPointB[8];
calibDatas _dacCalibDatasPointA[4];
calibDatas _dacCalibDatasPointB[4];
int32 correctFactor[8];
int32 calibZero[8];
u8 sensorUnit[8];
u8 RecordDelay;
u16 dacOutRate;
u32 softVersion;
}framDatas;


extern framDatas _framDatas;

#define FRAM_DATA_LENGTH  (sizeof(framDatas) + (sizeof(framDatas) % 2 == 1))
#define FRAM_BASE_ADDR  0

void fram_write_datas(void);
void fram_read_datas(void);

#define FRAM_MODBUS_HOLD_REG_ADDR  FRAM_DATA_LENGTH

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////



#endif
