#include "main.h"

//FRAM数据
framDatas _framDatas;

void nvm_data_init(void)
{
  rt_thread_delay(10);
  fram_read_datas();
  rt_thread_delay(10);
}

////////////////////////////////////////////
#define ADC_MAX_FREQ (510000)
//			#define ADC_MAX_FREQ	(250000)

void fram_write_datas(void)
{
  FramWrite((u8 *)&_framDatas, FRAM_BASE_ADDR, FRAM_DATA_LENGTH);
}

void fram_read_datas(void)
{
  // 读取fram中数据到RAM
  FramRead((u8 *)&_framDatas, FRAM_BASE_ADDR, FRAM_DATA_LENGTH);
  //FRAM数据校验
  if (_framDatas.softVersion != 0x00300002)
  {
    _framDatas.softVersion = 0x00300002;

    _framDatas._adcParam.adc_ch_Enable = 0xff;
    _framDatas._adcParam.samplingRate = 500000;
    _framDatas._adcParam.sramRecordMaxTime = 300;
    _framDatas._adcParam.sramAdutoTrigEnable = 0;

    for (u8 i = 0; i < 8; i++)
    {
      _framDatas._adcCalibDatasPointA[i].calibEnable = 0;
      _framDatas._adcCalibDatasPointA[i].calibDigital = 0;
      _framDatas._adcCalibDatasPointA[i].calibAnalog = 0;

      _framDatas._adcCalibDatasPointB[i].calibEnable = 0;
      _framDatas._adcCalibDatasPointB[i].calibDigital = 0;
      _framDatas._adcCalibDatasPointB[i].calibAnalog = 0;

      _framDatas.correctFactor[i] = 100000;
      _framDatas.calibZero[i] = 0;
    }

    for (u8 i = 0; i < 4; i++)
    {
      _framDatas._ddsDacParam[i].freq = 10;
      _framDatas._ddsDacParam[i].volt = 3000;
      _framDatas._ddsDacParam[i].duty = 5000;
      _framDatas._ddsDacParam[i].bias = 1000;
      _framDatas._ddsDacParam[i].phase = 90 * i;

      _framDatas._dacCalibDatasPointA[i].calibEnable = 0;
      _framDatas._dacCalibDatasPointA[i].calibDigital = 0;
      _framDatas._dacCalibDatasPointA[i].calibAnalog = 0;

      _framDatas._dacCalibDatasPointB[i].calibEnable = 0;
      _framDatas._dacCalibDatasPointB[i].calibDigital = 0;
      _framDatas._dacCalibDatasPointB[i].calibAnalog = 0;
    }

    _framDatas._ddsDacParam[0].freq = 50;
    _framDatas.dacOutRate = 10000;

    for (u8 i = 0; i < 6; i++)
    {
      _framDatas._pwmDatas[i].pwmFreq = 1000;
      _framDatas._pwmDatas[i].pwmDuty = 1000;
      _framDatas._pwmDatas[i].pwmAccUnit = 1;
    }
    _framDatas.RecordDelay = 5;

    rt_thread_delay(100);

    fram_write_datas();
    fram_read_datas();
  }
  

  _framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate > ADC_MAX_FREQ ? ADC_MAX_FREQ : _framDatas._adcParam.samplingRate;
  _framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate < 1 ? 1 : _framDatas._adcParam.samplingRate;
  _framDatas.dacOutRate = _framDatas.dacOutRate > 20000 ? 20000 : _framDatas.dacOutRate;
  _framDatas.dacOutRate = _framDatas.dacOutRate < 1000 ? 1000 : _framDatas.dacOutRate;

  for (u8 i = 0; i < 4; i++)
  {
    _framDatas._ddsDacParam[i].freq = _framDatas._ddsDacParam[i].freq > 1000 ? 1000 : _framDatas._ddsDacParam[i].freq;
  }

  for (u8 i = 0; i < 6; i++)
  {
    _framDatas._pwmDatas[i].pwmAccUnit = _framDatas._pwmDatas[i].pwmAccUnit == 0 ? 1 : _framDatas._pwmDatas[i].pwmAccUnit;
    _framDatas._pwmDatas[i].pwmFreq = _framDatas._pwmDatas[i].pwmFreq == 0 ? 1 : _framDatas._pwmDatas[i].pwmFreq;
    _framDatas._pwmDatas[i].pwmFreq = _framDatas._pwmDatas[i].pwmFreq > 10000 ? 10000 : _framDatas._pwmDatas[i].pwmFreq;
    _framDatas._pwmDatas[i].pwmDuty = _framDatas._pwmDatas[i].pwmDuty > 1000 ? 1000 : _framDatas._pwmDatas[i].pwmDuty;
  }
}
