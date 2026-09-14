#ifndef MSGSTRUCT_H
#define MSGSTRUCT_H

#include <QMainWindow>
#pragma pack(1)

enum _cmdId{
    //示波器指令
    _cmdId_setAdc_chEnable = 0x01,
    _cmdId_getDeviceParam = 0x02,
    _cmdId_getAdc_waveData = 0x03,
    _cmdId_setAdc_waveEnable_flag = 0x04,
    _cmdId_setAdc_trigCh = 0x05,
    _cmdId_setAdc_samplingRate = 0x06,
    _cmdId_setAdc_trigValue = 0x07,
    _cmdId_getAdcValue = 0x08,

    _cmdId_startFlashRecord = 0x09,
    _cmdId_flashRecordInfo = 0x0a,
    _cmdId_flashRecordDatas = 0x0b,
    _cmdId_stopFlashRecord = 0x0c,
    _cmdId_readFlashRecordDatas = 0x0d,
    _cmdId_flashRecordAutoUploadDatas = 0x0e,
    _cmdId_setCommunicatiaonPort = 0x0f,

    _cmdId_startSramRecord = 0x10,
    _cmdId_stopSramRecord = 0x11,
    _cmdId_readSramRecordDatas = 0x12,
    _cmdId_sramRecordAutoUploadDatas = 0x13,
    _cmdId_recordUploadStart = 0x14,
    _cmdId_recordUploadEnd = 0x15,
    _cmdId_startOnlineRecord = 0x16,
    _cmdId_stopOnlineRecord = 0x17,
    _cmdId_readOnlineRecordDatas = 0x18,
    _cmdId_readRecentConsecutiveDatas = 0x19,
    _cmdId_setRecentRecordParam = 0x1a,

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
    _cmdId_getCalibParam = 0x5a,
};

typedef struct{
    quint8 calibEnable;
    quint16 calibDigital;
    quint16 calibAnalog;
}calibDatas;

typedef struct {
        quint16 msgHead;  //0xffff
        quint8 cmdId;      //命令
        quint16 frameLen;   //报文长度
}msgHead;

typedef struct {
     quint16 msgHead;
     quint8  cmdId;
     quint16 frameLen;
     quint16 dataLen;
     quint16 dacDatas[1000];
     quint16 crc;
}msgSetDacDatas;

typedef struct {
    quint16 msgHead;  //0xffff
    quint8 cmdId;      //命令
    quint16 frameLen;   //报文长度

    quint8 ch;
 quint16 adcSamplingRate;

 quint16 freq;
 quint16 volt;
 quint16 duty;
 quint16 bias;
 quint16 gain;

    quint16 crc;
}msgDdsDacParam;

typedef struct {
    quint16 head;
    quint8 cmdId;
    quint16 frameLen;

    calibDatas _dacCalibDatasPointA[4];
    calibDatas _dacCalibDatasPointB[4];
    quint16 crc;
}msgGetDacCalibParam;

typedef struct {
    quint16 msgHead;  //0xffff
    quint8 cmdId;      //命令
    quint16 frameLen;   //报文长度

    quint8 adc_ch_Enable;
    quint8 trigCh;
    quint16 adcSamplingRate;
    quint16 adcTrigValue;

    quint16 adcFlashRecordIntervalTime;
    quint32 adcSramRecordMaxTime;

    quint8 recentRecordSampleNeedTimsMs;
    quint16 crc;
}msgAdcWaveState;


typedef struct {
    quint16 msgHead;  //0xffff
    quint8 cmdId;      //命令
    quint16 frameLen;   //报文长度

    quint32 DateTimeOffset_H;
    quint32 DateTimeOffset_L;

    quint8 adc_ch_Enable;
    quint16 recordIntervalTime;

    quint16 crc;
}msgAdcStartFlashRecordInfo;


typedef struct {
    quint16 msgHead;  //0xffff
    quint8 cmdId;      //命令
    quint16 frameLen;   //报文长度

    quint8 adc_ch_Enable;
    quint16 adcSamplingRate;

    quint16 crc;
}msgAdcStartOnlineRecord;

typedef struct {
    quint16 msgHead;  //0xffff
    quint8 cmdId;      //命令
    quint16 frameLen;   //报文长度

 quint8 adc_ch_Enable;
 quint16 adcSamplingRate;
 quint32 sramSamplingTimeMax;

    quint16 crc;
}msgAdcStartSramRecord;


typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;
        quint8 ch;
        quint16 crc;
}msgNoParam;

typedef struct {
     quint16 msgHead;
     quint8 cmdId;
     quint16 frameLen;
     quint8 ch;
     quint8 data;
     quint16 crc;
}msgUbyte;

typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;
        quint8 ch;
        quint16 data;
        quint16 crc;
}msgUWord;

typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;
        quint8 ch;
        quint32 data;
        quint16 crc;
}msgULong;

typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;

        quint8 adc_ch_Enable;
        quint16 data[8];

        quint16 crc;
}msgGetAdcValue;

typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;

        quint8 adc_ch_Enable;

        quint8 hour;
        quint8 minute;
        quint8 second;

        quint16 crc;
}msgAutoUploadDatas;


typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;

        quint8 din[8];
        quint8 dout[4];
        quint8 pwmEnable[4];

        quint16 pwmFreq[4];
        quint16 pwmDuty[4];
        quint16 pwmPulseNum[4];
        quint16 pwmAccUnit[4];
        quint16 crc;
}msgGetDioAll;

typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;

        quint8 addr;
        quint32 bauds;
        quint8 deviceWorkMode;
        calibDatas _adcCalibDatasPointA[8];
        calibDatas _adcCalibDatasPointB[8];
        quint16 crc;
}msgGetSettingParam;


typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;
        quint32 globalTick;
        quint8 recentRecordSampleNeedTimsMs;
        quint8 adc_ch_Enable;
        quint16 data1[200];
        quint16 data2[200];
        quint16 data3[200];
        quint16 data4[200];
        quint16 data5[200];
        quint16 data6[200];
        quint16 data7[200];
        quint16 data8[200];

        quint16 crc;
}msgGetRecentConsecutiveDatas;


typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;
        quint8 ch;

        quint16 pwmFreq;
        quint16 pwmDuty;
        quint16 pwmPulseNum;
        quint16 pwmAccUnit;

        quint16 crc;
}msgPwmParam;

typedef struct {
        quint16 msgHead;
        quint8 cmdId;
        quint16 frameLen;
        quint8 ch;

        quint8 serverIp[4];
        quint16 serverPort;

        quint16 crc;
}msgSetIpAndPort;

#define FLASH_SECTOR_ADC_MAX_LEN  	(2043)
 typedef struct{
     quint16 msgHead;
     quint8 cmdId;
     quint16 frameLen;
     quint32 DateTimeOffset_H;
     quint32 DateTimeOffset_L;

     quint8 adc_ch_Enable;
     quint16 dataLen;

     quint16 adcData[FLASH_SECTOR_ADC_MAX_LEN];
     quint32 back1;
     quint32 back2;
     quint16 crc;
 }msgRecordFlashDatas;

typedef struct {
     quint16 msgHead;
     quint8 cmdId;
     quint16 frameLen;

     quint16 dataLen;

     quint8 adc_ch_Enable;
     quint8 adcStartCh;
     quint8 trigCh;
     quint16 adcSamplingRate;
     quint16 adcTrigValue;

     quint16 adcData[4000];

     quint16 crc;
}msgGetAdcDatas;


#define SWAP16(c) ((((c)&0xff00)>>8)+(((c)&0x00ff)<<8))

#define SWAP32(c) (( ( (c) & 0xff000000UL ) >> 24)\
    +( ( (c) & 0x00ff0000UL ) >> 8 )\
    +( ( (c) & 0x0000ff00UL ) << 8 )\
    +( ( (c) & 0x000000ffUL ) << 24 ) )

enum _ddsDacWorkMode
{
    //示波器指令
    _ddsDacWorkMode_Stop = 0x00,
    _ddsDacWorkMode_Dc = 0x01,
    _ddsDacWorkMode_Sin = 0x02,
    _ddsDacWorkMode_Triangle = 0x03,
    _ddsDacWorkMode_Square = 0x04,
    _ddsDacWorkMode_Dds = 0x05,
    _ddsDacWorkMode_Calib = 0xff,

};

#endif // MSGSTRUCT_H
