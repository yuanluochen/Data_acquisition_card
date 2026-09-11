#include "main.h"
__UADC _uadc;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;

f2a_qspiAdcBufSturct _qspiAdcBuf;
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{    
		

		if(_adcFunctionParam.deviceWorkMode == _deviceWorkMode_onlineRecord)
		{
			//__disable_irq();
			//全部全局变量一次性缓存到局部，减少RAM访问
			const uint16_t gapCnt = _uadc.adc_BufIndexGap;
			const uint8_t chMask = _framDatas._adcParam.adc_ch_Enable;
			const uint16_t maxPoint = _adcFunctionParam.recordOnce_MaxDataLen;
			uint16_t idx = _uadc.adc_collectIndex;
			uint8_t bufFlag = _uadc.recordAB_flag;

			uint16_t *pDst;
			uint8_t nextFlag, fullFlag;
			if(bufFlag == 0)
			{
					pDst = _adcBuf.data;
					nextFlag = 1;
					fullFlag = 2;
			}
			else
			{
					pDst = _adcBufB.data;
					nextFlag = 0;
					fullFlag = 3;
			}

			for(uint16_t j = 0; j < gapCnt; j++)
			{
					for(uint8_t i = 0; i < 8; i++)
					{
							if( !(chMask & (1U << i)) )
									continue;

							uint16_t rawVal = SWAP16(_qspiAdcBuf.fifo[j].data[i]);
							if(rawVal > 100)
							{
								int i123 = 0;
							}
							if(idx < maxPoint - 1)
							{
									pDst[idx++] = rawVal;
							}
							else if(idx == maxPoint - 1)
							{
									// 填满整块缓存
									pDst[idx] = rawVal;
									idx = 0;
									_uadc.recordAB_flag = nextFlag;
									_adcFunctionParam.adc_collectFullFlag = fullFlag;
									// 一次性跳出双层循环，不再解析剩余FIFO
									goto parse_end_all;
							}
					}
			}
parse_end_all:
    // 仅最后写回更新后的索引，减少全局写入次数
    _uadc.adc_collectIndex = idx;
			//__enable_irq();
		}
		else if((_adcFunctionParam.deviceWorkMode != _deviceWorkMode_sramRecord) 
			&&(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_getSramRecord) )
		{
			_uadc.adc_collectIndex = 0;
			_uadc.recordAB_flag = 0;

				for(u16 i=0;i<8;i++)
				{
					_uadc.getAdc_Buf1000[i][_uadc.getAdc_BufIndex1000] = _uadc.getAdc[i];
					_uadc.getAdc_Buf256[i][_uadc.getAdc_BufIndex256]=_uadc.getAdc[i];
				}
				_uadc.getAdc_BufIndex256++;
				_uadc.getAdc_BufIndex1000++;
				_uadc.getAdc_BufIndex1000 %= 1000;
				_dioParam.dinAll = _uadc.getAdc[8]&0xff;
				_adcFunctionParam.global_tick_ms++;
		}
    
}


void qspiAdcTimTask(void)
{

		//如果是在线记录仪模式
		_uadc.adc_BufIndexHis = _uadc.adc_BufIndex;
		irq_spi_read();
		if(_adcFunctionParam.deviceWorkMode == _deviceWorkMode_onlineRecord)
		{
			_uadc.adc_BufIndex = _regF2AMap.REG_F2A_FIFO_IN_ADDR;
			_uadc.adc_BufIndexGap = ( _uadc.adc_BufIndex - _uadc.adc_BufIndexHis);
			if(_uadc.adc_BufIndexGap == 0)return;
			QSPI_ReadDatas_DMA(0x81,2,(u8*)&_qspiAdcBuf,_uadc.adc_BufIndexHis,_uadc.adc_BufIndexGap*17);		
		}
		else if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_getSramRecord)
		{
			QSPI_ReadDatas_DMA(0x80,2,(u8*)&_uadc.getAdc,0,17);
		}
}




void adc_dac_paramCalcThread(void)
{
	//adc的定时器
	//计算arr(pcs预设为0)
	u32 adcFreq = _framDatas._adcParam.samplingRate;
//	if(_adcFunctionParam.deviceWorkMode == _deviceWorkMode_onlineRecord)
//	{
//		adcFreq /= 3;
//		adcFreq += 1000;
//	}
	
	adcFreq = 1000;
	u32 adcArr = 240000000 / adcFreq;
	//根据arr计算psc, 将arr取余
	u32 adcPsc  = adcArr / 0x10000;
	adcArr = adcArr / (adcPsc + 1);
	
	htim13.Instance->ARR = adcArr-1;			
	htim13.Instance->PSC = adcPsc;	
	
	//dac的定时器
	u32 dacFreq = _framDatas.dacOutRate;
	htim14.Instance->ARR = 1000000/dacFreq - 1;		
}


