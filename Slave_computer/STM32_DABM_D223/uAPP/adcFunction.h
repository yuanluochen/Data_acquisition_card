#ifndef __ADCFUNCTION_H_
#define __ADCFUNCTION_H_

#include "main.h"
#pragma pack(1)
void adcFunction_thread(void);
void adcFunction_tim_task(void);

void fun_msgReadSramRecordDatas();

enum _deviceWorkMode
{
	//示波器指令
		_deviceWorkMode_Stop = 0x00,
		_deviceWorkMode_sendBusy,
		_deviceWorkMode_sramRecord,
		_deviceWorkMode_getSramRecord,
	  _deviceWorkMode_onlineRecord,	
		_deviceWorkMode_getWave,
	
		_deviceWorkMode_adcCalib = 0xff,
};

#define ADC_WAVE_ONCE_LEN (10000)


typedef struct{
	u32 global_tick_ms;
		u8 deviceWorkMode;
//示波器
		u8 adc_collectFullFlag;
	
		u8 hour;
		u8 minute;
		u8 second;

		u16 RecodeUpdateTick;
		u16 recordTimeTick;

		//sram record
		u8 adcChEnableIndexBuf[8];
		u8 adcChEnableMaxNum;
		u32 sramReadStartIndex;

	  u32 sramSamplingTimeTick;
		
		u8 sramInitInfo;

		u32 sramIndex;
				
		u32 sram_update_addr;
		
		//在线记录仪
		u8 onlineRecord_startCh;
		u16 recordOnce_MaxDataLen;
		u8 findFirstCh;
		u32 adc_fpga_cycleMax;
		u32 adc_fpga_sampleLen;
		
		u8 sramBufCnt;
		u8 sramBufCnt_his;
		
}adcFunctionParam;

extern adcFunctionParam _adcFunctionParam;

typedef struct{
  u16 msgHead; 
  u8 cmdId;      
  u16 frameLen;   
  u16 dataLen;   
	
	u16 adc_ch_Enable; 
	u8 adc_diff_Enable; 
	u8 adcSignalType;   
	u8 adcRange;   
  u8 trigCh;   
	u32 samplingRate;
	u16 adcTrigValue;
	
	u16 data[ADC_WAVE_ONCE_LEN];
	
	u16 crc;
}_adcSendBuf;

extern _adcSendBuf _adcBuf;
extern _adcSendBuf _adcBufB;

#endif


