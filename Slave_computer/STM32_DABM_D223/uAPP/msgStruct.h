#ifndef __MSGSTRUCT_H_
#define __MSGSTRUCT_H_

#include "main.h"
#pragma pack(1)

void fun_msgProcess_task(u8* data);
extern u8 MSG_TX_BUF[30000];
void fun_dinTrig_StartSramRecord();

enum __cmdId
{
 //示波器指令
 _cmdId_setAdc_chEnable = 0x01,
 _cmdId_getDeviceParam = 0x02,
 _cmdId_getAdc_waveData = 0x03,
 _cmdId_setAdc_waveEnable_flag = 0x04,
 _cmdId_setAdc_trigCh = 0x05,
 _cmdId_setAdc_samplingRate = 0x06,
 _cmdId_setAdc_trigValue = 0x07,
 _cmdId_getAdcValue = 0x08,


 _cmdId_stopFlashRecord = 0x0c,
 _cmdId_readFlashRecordDatas = 0x0d,
 _cmdId_flashRecordAutoUploadDatas = 0x0e,
 _cmdId_setCommunicatiaonPort = 0x0f,

 _cmdId_startSramRecord = 0x10,
 _cmdId_stopSramRecord = 0x11,
 _cmdId_getSramRecordDatas = 0x12,
 _cmdId_sramRecordAutoUploadDatas = 0x13,
 _cmdId_recordUploadStart = 0x14,
 _cmdId_recordUploadEnd = 0x15,
 _cmdId_startOnlineRecord = 0x16,
 _cmdId_stopOnlineRecord = 0x17,
 _cmdId_readOnlineRecordDatas = 0x18,
 _cmdId_readRecentConsecutiveDatas = 0x19,
 _cmdId_setAdc_diffEnable = 0x1a,
 _cmdId_readRecentConsecutiveDatasInit = 0x1b,

 _cmdId_ddsDacGetParamTotal = 0x20,
 _cmdId_ddsDacGetParam = 0x21,
 _cmdId_setDdsDacParam = 0x22,
 _cmdId_setDdsDacWorkMode = 0x23,
 _cmdId_setDdsDacDatas = 0x24,
 _cmdId_ddsDacCalibPoint1 = 0x25,
 _cmdId_ddsDacCalibPoint2 = 0x26,
 _cmdId_ddsDacClearCalib = 0x27,
 _cmdId_ddsDacGetCalibParam = 0x28,
						
 _cmdId_getIoAll = 0x30,
 _cmdId_getInputIO = 0x31,
 _cmdId_setOutputIO = 0x32,

 _cmdId_setPwmEnable = 0x33,
 _cmdId_setPwmParam = 0x34,

 _cmdId_setAdcRange = 0x40,
 _cmdId_setAdcSignalType = 0x41,
 _cmdId_sramAdutoTrigEnable = 0x42,

_cmdId_getSettingParam = 0x50,
_cmdId_settingAdcCalibPoint1 = 0x51,
_cmdId_settingAdcCalibPoint2 = 0x52,
_cmdId_settingClearAdcCalibDatas = 0x53,
_cmdId_settingSetAdcCalibMode = 0x54,
_cmdId_getAdcCalibParam = 0x55,
_cmdId_setIpAndPort = 0x56,
_cmdId_getIpAndPort = 0x57,
_cmdId_setDeviceAddr = 0x58,
_cmdId_setDeviceBauds = 0x59,


_cmdId_setCorrectFactor = 0x5b,
_cmdId_setCalibZero = 0x5c,
_cmdId_getCalibVolt = 0x5d,
_cmdId_setRecordDelay = 0x5e,
_cmdId_setSensorUnit = 0x5f,

_cmdId_getSoftVersion = 0xf0,


};

typedef struct {
		u16 msgHead;  //0xffff
		u8 cmdId;      //命令
		u16 frameLen;   //报文长度
}msgHead;

typedef struct {
	 u16 msgHead;
	 u8  cmdId;
	 u16 frameLen;
	 u16 dataLen;
	 u16 dacDatas[10000];
	 u16 crc;
}msgSetDacDatas;

typedef struct {
	u16 msgHead;  //0xffff
	u8 cmdId;      //命令
	u16 frameLen;   //报文长度

	u8 ch;
	 u16 dacOutRate;
		
	 u16 freq;
	 u16 volt;
	 u16 duty;
	 u16 bias;
	 u16 phase;
	
	u16 crc;
}msgDdsDacParam;

typedef struct{
	u8 calibEnable;
	int32 calibDigital;
	int32 calibAnalog;
}dacCalibDatas;

typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;  

		dacCalibDatas _dacCalibDatasPointA[4];
		dacCalibDatas _dacCalibDatasPointB[4];
		u16 crc;   
}msgGetDacCalibParam;

typedef struct {
	u16 msgHead;  //0xffff
	u8 cmdId;      //命令
	u16 frameLen;   //报文长度
	
	u16 adc_ch_Enable;   
	u8 adc_diff_Enable; 

	u8 adcSignalType;   
	u8 adcRange;   
  u8 trigCh;   
	u32 adcSamplingRate;
	u16 adcTrigValue;

	u32 adcSramRecordMaxTime;
	
	u8 sramAdutoTrigEnable;   

	u16 crc;
}msgAdcWaveState;




typedef struct {
	u16 msgHead;  //0xffff
	u8 cmdId;      //命令
	u16 frameLen;   //报文长度

	u16 adc_ch_Enable;   
	u8 adc_diff_Enable;   
	
	u8 adcSignalType;   	//传感器类型
	u8 adcRange;   				//传感器量程
	
	u32 adcSamplingRate;			//采样率
	u32 sramSamplingTimeMax;	//采集时间

	u16 crc;
}msgAdcStartSramRecord;


typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;   
		u8 ch;   
		u16 crc;   
}msgNoParam;

typedef struct {
     u16 msgHead;  
     u8 cmdId;      
     u16 frameLen;   
     u8 ch;   
     u8 data;   
     u16 crc;   
}msgUbyte;

typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;   
		u8 ch;   
		u16 data;   
		u16 crc;   
}msgUWord;

typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;   
		u8 ch;   
		u32 data;   
		u16 crc;   
}msgULong;

typedef struct {
		u16 msgHead;  //包头 0x55aa
		u8 cmdId;     //返回指令
		u16 frameLen; //包长度

		u16 adc_ch_Enable;   
		u8 adc_diff_Enable;   
		u8 adcSignalType;   
		u8 adcRange;   
		u8 din; 
	s32 data[8];  			//8个通道的数据 每个通道2个字节

		u16 crc;   	//crc校验值
}msgGetAdcValue;

typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;  

	u16 adc_ch_Enable;   
	u8 adc_diff_Enable;   
		u8 adcSignalType;   
		u8 adcRange;   

		u8 hour;
		u8 minute;
		u8 second;	
	
		u16 crc;   
}msgAutoUploadDatas;


typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;  

		u8 din;  
		u8 dout;    
		u8 pwmEnable;  
	
		u16 pwmFreq[6];
		u16 pwmDuty[6];
		u16 pwmPulseNum[6];
		u16 pwmAccUnit[6];	
		u16 crc;   
}msgGetDioAll;

typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;  

		u8 deviceWorkMode;
	
		calibDatas _adcCalibDatasPointA[8];
		calibDatas _adcCalibDatasPointB[8];
	
		int32 correctFactor[8];
		int32 calibZero[8];
		u8 sensorUnit[8];
	
		u8 RecordDelay;
		u32 softVersion;
	
		u16 crc;   
}msgGetSettingParam;

typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;  
		u32 globalTick;
		u32 adcSamplingRate;   
	u16 adc_ch_Enable;   
	u8 adc_diff_Enable;   
		u8 adcSignalType;   
		u8 adcRange;   
		u8 din;   
		s16 data1[1000];  
		s16 data2[1000];  
		s16 data3[1000];  
		s16 data4[1000];  
		s16 data5[1000];  
		s16 data6[1000];  
		s16 data7[1000];  
		s16 data8[1000];  
		u16 crc;   
}msgGetRecentConsecutiveDatas;


typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;  
		u8 ch;   

		u16 pwmFreq;
		u16 pwmDuty;
		u16 pwmPulseNum;
		u16 pwmAccUnit;	
	
		u16 crc;   
}msgPwmParam;

typedef struct {
		u16 msgHead;  
		u8 cmdId;      
		u16 frameLen;  
		u8 ch;   

		u8 serverIp[4];
		u16 serverPort;

		u16 crc;   
}msgSetIpAndPort;


typedef struct {
		u16 msgHead;  //包头 0x55aa
		u8 cmdId;     //返回指令
		u16 frameLen; //包长度

	u16 adc_ch_Enable;   
	u8 adc_diff_Enable;   
		u8 adcRange;   
		s32 data[8];  			//8个通道的数据 每个通道2个字节

		u16 crc;   	//crc校验值
}msgGetCalibVolt;

#endif




