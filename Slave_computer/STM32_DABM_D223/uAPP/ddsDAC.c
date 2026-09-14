#include "main.h"

// 查找表深度200, 100KHz索引速率  每次加2
ddsDac _ddsDac;

const u16 sinTable[500] = {
#include "sin_table.txt"
};

s32 calc_ddsDacCalibData(s32 data, s32 d1, s32 a1, s32 d2, s32 a2)
{
  s32 result = ((data - a1) * (d2 - d1) / (a2 - a1)) + d1;
  return result;
}

// DDS计算，主要生成有规律的波形
void ddsDacCalc()
{
  for (u8 i = 0; i < 4; i++)
  {
    if (_ddsDac.ddsDacWorkMode[i] == _ddsDacWorkMode_Stop)
    {
      _ddsDac.dacCCR[i] = 0;
      continue;
    }

    s32 interruptFreq = _framDatas.dacOutRate;     // DDS 的时基（= TIM14 中断频率）
    s32 freq = _framDatas._ddsDacParam[i].freq;    // 目标输出频率
    // s32 duty = _framDatas._ddsDacParam[i].duty; // 方波占空比
    s32 phase = _framDatas._ddsDacParam[i].phase;  // 多通道相位
    s32 calib_d1 = _framDatas._dacCalibDatasPointA[i].calibDigital;
    s32 calib_a1 = _framDatas._dacCalibDatasPointA[i].calibAnalog;
    s32 calib_d2 = _framDatas._dacCalibDatasPointB[i].calibDigital;
    s32 calib_a2 = _framDatas._dacCalibDatasPointB[i].calibAnalog;
    u8 calib_en1 = _framDatas._dacCalibDatasPointA[i].calibEnable;
    u8 calib_en2 = _framDatas._dacCalibDatasPointB[i].calibEnable;
    u32 dacIndexInt;

    s32 amp, bias;
    if ((calib_en1 == 1) && (calib_en2 == 1))
    {
      amp = (uint16)calc_ddsDacCalibData(_framDatas._ddsDacParam[i].volt, calib_d1, calib_a1, calib_d2, calib_a2);
      bias = (uint16)calc_ddsDacCalibData(_framDatas._ddsDacParam[i].bias, calib_d1, calib_a1, calib_d2, calib_a2);
    }
    else
    {
      amp = ((s32)_framDatas._ddsDacParam[i].volt) * 65536 / 5000;
      bias = ((s32)_framDatas._ddsDacParam[i].bias) * 65536 / 5000;
    }

    if (_ddsDac.ddsDacWorkMode[i] == _ddsDacWorkMode_Dc || _ddsDac.ddsDacWorkMode[i] == _ddsDacWorkMode_Calib)
    {

      _ddsDac.dacCCR[i] = amp;
    }
    else if (_ddsDac.ddsDacWorkMode[i] == _ddsDacWorkMode_Sin)
    {
      // 虚拟浮点数 保留3位精度
      if (i == 0)
      {
        _ddsDac.dacIndex[i] += freq * 500000 / interruptFreq; // 500是查表深度, 除以中断频率为1Hz时每次需要的累加值
        _ddsDac.dacIndex[i] %= 500000;
        dacIndexInt = _ddsDac.dacIndex[i] / 1000;
      }
      else if (_framDatas._ddsDacParam[i].freq == _framDatas._ddsDacParam[0].freq && _ddsDac.ddsDacWorkMode[0] == _ddsDacWorkMode_Sin)
      {
        _ddsDac.dacIndex[i] = _ddsDac.dacIndex[0] + phase * 500000 / 360; // 500是查表深度, 除以中断频率为1Hz时每次需要的累加值
        _ddsDac.dacIndex[i] %= 500000;
        dacIndexInt = _ddsDac.dacIndex[i] / 1000;
      }
      else
      {
        _ddsDac.dacIndex[i] += freq * 500000 / interruptFreq; // 500是查表深度, 除以中断频率为1Hz时每次需要的累加值
        _ddsDac.dacIndex[i] %= 500000;
        dacIndexInt = _ddsDac.dacIndex[i] / 1000;
      }

      _ddsDac.dacCCR[i] = ((s32)sinTable[dacIndexInt] * amp / 65536) + bias;
    }
    else if (_ddsDac.ddsDacWorkMode[i] == _ddsDacWorkMode_Triangle)
    {
      // 虚拟浮点数 保留3位精度
      if (i == 0)
      {
        _ddsDac.dacMaxIndex[i] = interruptFreq / freq; // 中断频率除以期望频率为每周期的台阶数
        _ddsDac.dacIndex[i]++;
        _ddsDac.dacIndex[i] %= _ddsDac.dacMaxIndex[i];

        if (_ddsDac.dacIndex[i] < (_ddsDac.dacMaxIndex[i] / 2))
        {
          dacIndexInt = _ddsDac.dacIndex[i] * 2000 / _ddsDac.dacMaxIndex[i];
        }
        else if (_ddsDac.dacIndex[i] < _ddsDac.dacMaxIndex[i])
        {
          dacIndexInt = (_ddsDac.dacMaxIndex[i] - _ddsDac.dacIndex[i]) * 2000 / _ddsDac.dacMaxIndex[i];
        }
      }
      else if (_framDatas._ddsDacParam[i].freq == _framDatas._ddsDacParam[0].freq && _ddsDac.ddsDacWorkMode[0] == _ddsDacWorkMode_Triangle)
      {
        _ddsDac.dacIndex[i] = _ddsDac.dacIndex[0] + (phase * _ddsDac.dacMaxIndex[0] / 360);
        _ddsDac.dacIndex[i] %= _ddsDac.dacMaxIndex[0];

        if (_ddsDac.dacIndex[i] < (_ddsDac.dacMaxIndex[0] / 2))
        {
          dacIndexInt = _ddsDac.dacIndex[i] * 2000 / _ddsDac.dacMaxIndex[0];
        }
        else if (_ddsDac.dacIndex[i] < _ddsDac.dacMaxIndex[0])
        {
          dacIndexInt = (_ddsDac.dacMaxIndex[0] - _ddsDac.dacIndex[i]) * 2000 / _ddsDac.dacMaxIndex[0];
        }
      }
      else
      {
        _ddsDac.dacMaxIndex[i] = interruptFreq / freq; // 中断频率除以期望频率为每周期的台阶数
        _ddsDac.dacIndex[i]++;
        _ddsDac.dacIndex[i] %= _ddsDac.dacMaxIndex[i];

        if (_ddsDac.dacIndex[i] < (_ddsDac.dacMaxIndex[i] / 2))
        {
          dacIndexInt = _ddsDac.dacIndex[i] * 2000 / _ddsDac.dacMaxIndex[i];
        }
        else if (_ddsDac.dacIndex[i] < _ddsDac.dacMaxIndex[i])
        {
          dacIndexInt = (_ddsDac.dacMaxIndex[i] - _ddsDac.dacIndex[i]) * 2000 / _ddsDac.dacMaxIndex[i];
        }
      }

      _ddsDac.dacCCR[i] = (dacIndexInt * amp / 1000) + bias;
    }
    else if (_ddsDac.ddsDacWorkMode[i] == _ddsDacWorkMode_Square)
    {
      // 虚拟浮点数 保留3位精度
      if (i == 0)
      {
        _ddsDac.dacMaxIndex[i] = interruptFreq / freq; // 中断频率除以期望频率为每周期的台阶数
        _ddsDac.dacIndex[i]++;
        _ddsDac.dacIndex[i] %= _ddsDac.dacMaxIndex[i];

        if (_ddsDac.dacIndex[i] < (_framDatas._ddsDacParam[i].duty * _ddsDac.dacMaxIndex[i] / 10000))
        {
          dacIndexInt = 1000;
        }
        else
        {
          dacIndexInt = 0;
        }
      }
      else if (_framDatas._ddsDacParam[i].freq == _framDatas._ddsDacParam[0].freq && _ddsDac.ddsDacWorkMode[0] == _ddsDacWorkMode_Square)
      {
        _ddsDac.dacIndex[i] = _ddsDac.dacIndex[0] + (phase * _ddsDac.dacMaxIndex[0] / 360);
        _ddsDac.dacIndex[i] %= _ddsDac.dacMaxIndex[0];

        if (_ddsDac.dacIndex[i] < (_framDatas._ddsDacParam[i].duty * _ddsDac.dacMaxIndex[0] / 10000))
        {
          dacIndexInt = 1000;
        }
        else
        {
          dacIndexInt = 0;
        }
      }
      else
      {
        _ddsDac.dacMaxIndex[i] = interruptFreq / freq; // 中断频率除以期望频率为每周期的台阶数
        _ddsDac.dacIndex[i]++;
        _ddsDac.dacIndex[i] %= _ddsDac.dacMaxIndex[i];

        if (_ddsDac.dacIndex[i] < (_framDatas._ddsDacParam[i].duty * _ddsDac.dacMaxIndex[i] / 10000))
        {
          dacIndexInt = 1000;
        }
        else
        {
          dacIndexInt = 0;
        }
      }
      _ddsDac.dacCCR[i] = (dacIndexInt * amp / 1000) + bias;
    }
    else if (_ddsDac.ddsDacWorkMode[i] == _ddsDacWorkMode_Dds)
    {
      // 虚拟浮点数 保留2位精度
      _ddsDac.dacIndex[i]++;
      _ddsDac.dacIndex[i] %= 10000;
      _ddsDac.dacIndex[i] %= _ddsDac.ddsDatasLen;
      _ddsDac.dacCCR[i] = _ddsDac.ddsDatas[_ddsDac.dacIndex[i]] + bias;
    }
  }
}

u8 dac_txBuf[20];
extern SPI_HandleTypeDef hspi2;

void ddsDac_tim_task()
{
  //dac设置输出
  if (_ddsDac.ddsDacWorkMode[0] || _ddsDac.ddsDacWorkMode[1] || _ddsDac.ddsDacWorkMode[2] || _ddsDac.ddsDacWorkMode[3])
  {
    ddsDacCalc();

    DA_CS(0);
    dac_txBuf[0] = 0X08;
    dac_txBuf[1] = _ddsDac.dacCCR[0] >> 8;
    dac_txBuf[2] = _ddsDac.dacCCR[0] & 0XFF;
    HAL_SPI_Transmit(&hspi2, dac_txBuf, 3, 1);
    DA_CS(1);

    DA_CS(0);
    dac_txBuf[0] = 0X0a;
    dac_txBuf[1] = _ddsDac.dacCCR[1] >> 8;
    dac_txBuf[2] = _ddsDac.dacCCR[1] & 0XFF;
    HAL_SPI_Transmit(&hspi2, dac_txBuf, 3, 1);
    DA_CS(1);

    DA_CS(0);
    dac_txBuf[0] = 0X0c;
    dac_txBuf[1] = _ddsDac.dacCCR[2] >> 8;
    dac_txBuf[2] = _ddsDac.dacCCR[2] & 0XFF;
    HAL_SPI_Transmit(&hspi2, dac_txBuf, 3, 1);
    DA_CS(1);

    DA_CS(0);
    dac_txBuf[0] = 0X0e;
    dac_txBuf[1] = _ddsDac.dacCCR[3] >> 8;
    dac_txBuf[2] = _ddsDac.dacCCR[3] & 0XFF;
    HAL_SPI_Transmit(&hspi2, dac_txBuf, 3, 1);
    DA_CS(1);
  }
}
