#ifndef __MSGSTRUCT_H_
#define __MSGSTRUCT_H_

#include "main.h"


void fun_msgProcess_task(u8* data);
extern u8 MSG_TX_BUF[30000];
void fun_dinTrig_StartSramRecord();

enum __cmdId
{
  // 示波器ADC
  _cmdId_setAdc_chEnable = 0x01,       //设置通道使能位图
  _cmdId_getDeviceParam = 0x02,        //请求上报ADC全部参数
  // _cmdId_getAdc_waveData = 0x03,       //获取ADC波形数据
  // _cmdId_setAdc_waveEnable_flag = 0x04,//启动ADC波形采样标志
  // _cmdId_setAdc_trigCh = 0x05,         //设置触发通道
  _cmdId_setAdc_samplingRate = 0x06,   //设置采样率
  // _cmdId_setAdc_trigValue = 0x07,      //设置触发阈值
  _cmdId_getAdcValue = 0x08,           //读取8ADC通道实时数值

  // FLAS记录仪
  // _cmdId_stopFlashRecord = 0x0c,           //停止Flash记录
  // _cmdId_readFlashRecordDatas = 0x0d,      //读取flash记录数据
  // _cmdId_flashRecordAutoUploadDatas = 0x0e,//Flash 数据自动上传（上行
  // _cmdId_setCommunicatiaonPort = 0x0f,     // 切换通信口（USB/串口/网口）

  // 记录仪
  _cmdId_startSramRecord = 0x10,              //启动SRAM记录
  _cmdId_stopSramRecord = 0x11,               //停止SRAM记录
  _cmdId_getSramRecordDatas = 0x12,           //请求上传SRAM记录
  _cmdId_sramRecordAutoUploadDatas = 0x13,    //SRAM 数据自动上传（上行）
  _cmdId_recordUploadStart = 0x14,            //上传开始握手
  _cmdId_recordUploadEnd = 0x15,              //删除结束握手
  _cmdId_startOnlineRecord = 0x16,            //启动在线记录
  _cmdId_stopOnlineRecord = 0x17,             //停止在线记录
  _cmdId_readOnlineRecordDatas = 0x18,        //读取在线记录数据
  _cmdId_readRecentConsecutiveDatas = 0x19,   //读最近 1000 点×8 通道
  _cmdId_setAdc_diffEnable = 0x1a,            //设置差分使能
  _cmdId_readRecentConsecutiveDatasInit = 0x1b, // 连续缓存初始化//复位

  // DDS信号源(Direct Digital Synthesis，直接数字频率合成)
  _cmdId_ddsDacGetParamTotal = 0x20,        //一次拿全 4 通道参数 + 标定
  _cmdId_ddsDacGetParam = 0x21,             //单通道参数上报
  _cmdId_setDdsDacParam = 0x22,             //设频率/幅值/占空比/偏置/相位
  _cmdId_setDdsDacWorkMode = 0x23,          //设通道工作模式（关/输出/校准）
  _cmdId_setDdsDacDatas = 0x24,             //下发任意波形数据（≤10000 点）
  _cmdId_ddsDacCalibPoint1 = 0x25,          //记录标定点
  _cmdId_ddsDacCalibPoint2 = 0x26,          //记录标定点
  _cmdId_ddsDacClearCalib = 0x27,           //清该通道标定
  _cmdId_ddsDacGetCalibParam = 0x28,        //上报标定数据

  // 数字 IO
  _cmdId_getIoAll = 0x30,
  _cmdId_getInputIO = 0x31,
  _cmdId_setOutputIO = 0x32,
  // PWM
  _cmdId_setPwmEnable = 0x33,
  _cmdId_setPwmParam = 0x34,

  // ADC 补充设置
  _cmdId_setAdcRange = 0x40,             //量程
  _cmdId_setAdcSignalType = 0x41,        //设置信号类型
  _cmdId_sramAdutoTrigEnable = 0x42,     //SARM记录是否允许外部触发退出

  // 设置页 / 标定 / 网络
  _cmdId_getSettingParam = 0x50,                 //上报全部标定与设置
  _cmdId_settingAdcCalibPoint1 = 0x51,           //ADC 标定点 A
  _cmdId_settingAdcCalibPoint2 = 0x52,           //ADC 标定点 B
  _cmdId_settingClearAdcCalibDatas = 0x53,       //清 ADC 标定
  _cmdId_settingSetAdcCalibMode = 0x54,          //进/出校准模式
  // _cmdId_getAdcCalibParam = 0x55,
  // _cmdId_setIpAndPort = 0x56,
  // _cmdId_getIpAndPort = 0x57,
  // _cmdId_setDeviceAddr = 0x58,               //设置设备地址
  // _cmdId_setDeviceBauds = 0x59,              //设置波特率

  _cmdId_setCorrectFactor = 0x5b, //设修正系数
  _cmdId_setCalibZero = 0x5c,     //设置零点
  _cmdId_getCalibVolt = 0x5d,     //读校准模式下的实时电压
  _cmdId_setRecordDelay = 0x5e,   //设置记录延时
  _cmdId_setSensorUnit = 0x5f,    //设置传感器单位

  _cmdId_getSoftVersion = 0xf0,
};
#pragma pack(1)
typedef struct
{
  u16 msgHead;  // 0xffff
  u8 cmdId;     // 命令
  u16 frameLen; // 报文长度
} msgHead;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;
  u16 dataLen;
  u16 dacDatas[10000];
  u16 crc;
} msgSetDacDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;  // 0xffff
  u8 cmdId;     // 命令
  u16 frameLen; // 报文长度

  u8 ch;
  u16 dacOutRate;

  u16 freq;
  u16 volt;
  u16 duty;
  u16 bias;
  u16 phase;

  u16 crc;
} msgDdsDacParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u8 calibEnable;
  int32 calibDigital;
  int32 calibAnalog;
} dacCalibDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;

  dacCalibDatas _dacCalibDatasPointA[4];
  dacCalibDatas _dacCalibDatasPointB[4];
  u16 crc;
} msgGetDacCalibParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;  // 0xffff
  u8 cmdId;     // 命令
  u16 frameLen; // 报文长度

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
} msgAdcWaveState;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;  // 0xffff
  u8 cmdId;     // 命令
  u16 frameLen; // 报文长度

  u16 adc_ch_Enable;
  u8 adc_diff_Enable;

  u8 adcSignalType; // 传感器类型
  u8 adcRange;      // 传感器量程

  u32 adcSamplingRate;     // 采样率
  u32 sramSamplingTimeMax; // 采集时间

  u16 crc;
} msgAdcStartSramRecord;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;
  u8 ch;
  u16 crc;
} msgNoParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;
  u8 ch;
  u8 data;
  u16 crc;
} msgUbyte;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;
  u8 ch;
  u16 data;
  u16 crc;
} msgUWord;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;
  u8 ch;
  u32 data;
  u16 crc;
} msgULong;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;  // 包头 0x55aa
  u8 cmdId;     // 返回指令
  u16 frameLen; // 包长度

  u16 adc_ch_Enable;
  u8 adc_diff_Enable;
  u8 adcSignalType;
  u8 adcRange;
  u8 din;
  s32 data[8]; // 8个通道的数据 每个通道2个字节

  u16 crc; // crc校验值
} msgGetAdcValue;
#pragma pack()

#pragma pack(1)
typedef struct
{
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
} msgAutoUploadDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
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
} msgGetDioAll;
#pragma pack()

#pragma pack(1)
typedef struct
{
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
} msgGetSettingParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
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
} msgGetRecentConsecutiveDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;
  u8 ch;

  u16 pwmFreq;
  u16 pwmDuty;
  u16 pwmPulseNum;
  u16 pwmAccUnit;

  u16 crc;
} msgPwmParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;
  u8 cmdId;
  u16 frameLen;
  u8 ch;

  u8 serverIp[4];
  u16 serverPort;

  u16 crc;
} msgSetIpAndPort;
#pragma pack()

#pragma pack(1)
typedef struct
{
  u16 msgHead;  // 包头 0x55aa
  u8 cmdId;     // 返回指令
  u16 frameLen; // 包长度

  u16 adc_ch_Enable;
  u8 adc_diff_Enable;
  u8 adcRange;
  s32 data[8]; // 8个通道的数据 每个通道2个字节

  u16 crc; // crc校验值
} msgGetCalibVolt;
#pragma pack()
#endif
