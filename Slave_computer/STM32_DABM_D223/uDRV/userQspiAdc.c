#include "main.h"

extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;

__UADC _uadc;

/* QSPI DMA 接收缓冲: 8 通道 x 2 字节 + 1 字节 DIN = 17 字节 */
static u8 _adcRxBuf[17];

/* FPGA 返回的 ADC 数据 (QSPI cmd 0x80) 排列为:
 *   [0..1] 通道0 (小端) ... [14..15] 通道7
 *   [16]   数字输入
 */
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  memcpy(_uadc.adc, _adcRxBuf, 16);
  _uadc.din = _adcRxBuf[16];
  _dioParam.dinAll = _uadc.din;
  _uadc.newFlag = 1;
}

void qspiAdcTimTask(void)
{
  /* 读取 FPGA 当前 8 通道 ADC 原始值 */
  QSPI_ReadDatas_DMA(0x80, 2, _adcRxBuf, 0, 17);
}

void adc_dac_paramCalcThread(void)
{
  /* ADC 读取时基固定 1kHz */
  u32 adcFreq = 1000;
  u32 adcArr = 240000000 / adcFreq;
  u32 adcPsc = adcArr / 0x10000;
  adcArr = adcArr / (adcPsc + 1);

  htim13.Instance->ARR = adcArr - 1;
  htim13.Instance->PSC = adcPsc;

  /* DAC 输出时基 */
  htim14.Instance->ARR = 1000000 / _framDatas.dacOutRate - 1;
}
