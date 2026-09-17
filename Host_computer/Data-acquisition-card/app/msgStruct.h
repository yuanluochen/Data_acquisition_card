#ifndef __MSGSTRUCT_H_
#define __MSGSTRUCT_H_

#include "struct_typedef.h"


enum __cmdId
{
  /*       TO stm      */
  // 示波器ADC
  _cmdId_setAdc_chEnable = 0x01,            // 设置通道使能位图
  _cmdId_getDeviceParam = 0x02,             // 请求上报ADC全部参数
  _cmdId_setAdc_samplingRate = 0x06,        // 设置采样率
  _cmdId_getAdcValue = 0x08,                // 读取8ADC通道实时数值
  _cmdId_startOnlineRecord = 0x16,          // 启动在线记录
  _cmdId_stopOnlineRecord = 0x17,           // 停止在线记录
  _cmdId_readRecentConsecutiveDatas = 0x19, // 读最近 1000 点×8 通道

  _cmdId_setAdc_diffEnable = 0x1a, // 设置差分使能
  // ADC 补充设置
  _cmdId_setAdcRange = 0x40,      // 量程
  _cmdId_setAdcSignalType = 0x41, // 设置信号类型
  // DDS信号源(Direct Digital Synthesis，直接数字频率合成)
  _cmdId_ddsDacGetParamTotal = 0x20, // 一次拿全 4 通道参数 + 标定

  _cmdId_setDdsDacParam = 0x22,    // 设频率/幅值/占空比/偏置/相位
  _cmdId_setDdsDacWorkMode = 0x23, // 设通道工作模式（关/输出/校准）
  _cmdId_setDdsDacDatas = 0x24,    // 下发任意波形数据（≤10000 点）

  /*       TO this      */
  _cmdId_sramRecordAutoUploadDatas = 0x13, // SRAM 数据自动上传（上行）
  _cmdId_recordUploadStart = 0x14,         // 上传开始握手
  _cmdId_recordUploadEnd = 0x15,           // 删除结束握手

  _cmdId_readOnlineRecordDatas = 0x18, // 读取在线记录数据

  _cmdId_ddsDacGetParam = 0x21, // 单通道参数上报

  _cmdId_ddsDacGetCalibParam = 0x28, // 上报标定数据
};
#pragma pack(1)
typedef struct
{
  uint16_t msgHead;  // 0xffff
  uint8_t cmdId;     // 命令
  uint16_t frameLen; // 报文长度
} msgHead;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint16_t dataLen;
  uint16_t dacDatas[10000];
  uint16_t crc;
} msgSetDacDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;  // 0xffff
  uint8_t cmdId;     // 命令
  uint16_t frameLen; // 报文长度

  uint8_t ch;
  uint16_t dacOutRate;

  uint16_t freq;
  uint16_t volt;
  uint16_t duty;
  uint16_t bias;
  uint16_t phase;

  uint16_t crc;
} msgDdsDacParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint8_t calibEnable;
  int32_t calibDigital;
  int32_t calibAnalog;
} dacCalibDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;

  dacCalibDatas _dacCalibDatasPointA[4];
  dacCalibDatas _dacCalibDatasPointB[4];
  uint16_t crc;
} msgGetDacCalibParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;  // 0xffff
  uint8_t cmdId;     // 命令
  uint16_t frameLen; // 报文长度

  uint16_t adc_ch_Enable;
  uint8_t adc_diff_Enable;

  uint8_t adcSignalType;
  uint8_t adcRange;
  uint8_t trigCh;
  uint32_t adcSamplingRate;
  uint16_t adcTrigValue;

  uint32_t adcSramRecordMaxTime;

  uint8_t sramAdutoTrigEnable;

  uint16_t crc;
} msgAdcWaveState;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;  // 0xffff
  uint8_t cmdId;     // 命令
  uint16_t frameLen; // 报文长度

  uint16_t adc_ch_Enable;
  uint8_t adc_diff_Enable;

  uint8_t adcSignalType; // 传感器类型
  uint8_t adcRange;      // 传感器量程

  uint32_t adcSamplingRate;     // 采样率
  uint32_t sramSamplingTimeMax; // 采集时间

  uint16_t crc;
} msgAdcStartSramRecord;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;  // 0xffff
  uint8_t cmdId;     // 命令
  uint16_t frameLen; // 报文长度

  uint16_t adc_ch_Enable;
  uint8_t adc_diff_Enable;

  uint8_t adcSignalType; // 传感器类型
  uint8_t adcRange;      // 传感器量程

  uint32_t adcSamplingRate;     // 采样率

  uint16_t crc;
} msgAdcStartOnlineRecord;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint8_t ch;
  uint16_t crc;
} msgNoParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint8_t ch;
  uint8_t data;
  uint16_t crc;
} msgUbyte;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint8_t ch;
  uint16_t data;
  uint16_t crc;
} msgUWord;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint8_t ch;
  uint32_t data;
  uint16_t crc;
} msgULong;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;  // 包头 0x55aa
  uint8_t cmdId;     // 返回指令
  uint16_t frameLen; // 包长度

  uint16_t adc_ch_Enable;
  uint8_t adc_diff_Enable;
  uint8_t adcSignalType;
  uint8_t adcRange;
  uint8_t din;
  int32_t data[8]; // 8个通道的数据 每个通道2个字节

  uint16_t crc; // crc校验值
} msgGetAdcValue;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;

  uint16_t adc_ch_Enable;
  uint8_t adc_diff_Enable;
  uint8_t adcSignalType;
  uint8_t adcRange;

  uint8_t hour;
  uint8_t minute;
  uint8_t second;

  uint16_t crc;
} msgAutoUploadDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;

  uint8_t din;
  uint8_t dout;
  uint8_t pwmEnable;

  uint16_t pwmFreq[6];
  uint16_t pwmDuty[6];
  uint16_t pwmPulseNum[6];
  uint16_t pwmAccUnit[6];
  uint16_t crc;
} msgGetDioAll;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint8_t calibEnable;
  int32_t calibDigital;
  int32_t calibAnalog;
} calibDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;

  uint8_t deviceWorkMode;

  calibDatas _adcCalibDatasPointA[8];
  calibDatas _adcCalibDatasPointB[8];

  int32_t correctFactor[8];
  int32_t calibZero[8];
  uint8_t sensorUnit[8];

  uint8_t RecordDelay;
  uint32_t softVersion;

  uint16_t crc;
} msgGetSettingParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint32_t globalTick;
  uint32_t adcSamplingRate;
  uint16_t adc_ch_Enable;
  uint8_t adc_diff_Enable;
  uint8_t adcSignalType;
  uint8_t adcRange;
  uint8_t din;
  int16_t data1[1000];
  int16_t data2[1000];
  int16_t data3[1000];
  int16_t data4[1000];
  int16_t data5[1000];
  int16_t data6[1000];
  int16_t data7[1000];
  int16_t data8[1000];
  uint16_t crc;
} msgGetRecentConsecutiveDatas;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint8_t ch;

  uint16_t pwmFreq;
  uint16_t pwmDuty;
  uint16_t pwmPulseNum;
  uint16_t pwmAccUnit;

  uint16_t crc;
} msgPwmParam;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;
  uint8_t cmdId;
  uint16_t frameLen;
  uint8_t ch;

  uint8_t serverIp[4];
  uint16_t serverPort;

  uint16_t crc;
} msgSetIpAndPort;
#pragma pack()

#pragma pack(1)
typedef struct
{
  uint16_t msgHead;  // 包头 0x55aa
  uint8_t cmdId;     // 返回指令
  uint16_t frameLen; // 包长度

  uint16_t adc_ch_Enable;
  uint8_t adc_diff_Enable;
  uint8_t adcRange;
  int32_t data[8]; // 8个通道的数据 每个通道2个字节

  uint16_t crc; // crc校验值
} msgGetCalibVolt;
#pragma pack()

#define SWAP16(c) ((((c) & 0xff00) >> 8) + (((c) & 0x00ff) << 8))

#define SWAP32(c) ( (( (c) & 0xff000000UL ) >> 24)\
    +( ( (c) & 0x00ff0000UL ) >> 8 )\
    +( ( (c) & 0x0000ff00UL ) << 8 )\
    +( ( (c) & 0x000000ffUL ) << 24 ))

#endif
