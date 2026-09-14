#include "main.h"
#include "msgStruct.h"
u8 MSG_TX_BUF[30000];

void fun_getAdcParam()
{
	msgAdcWaveState* _pTx = (msgAdcWaveState*)MSG_TX_BUF;
	_pTx->msgHead = SWAP16(0x55aa);
	_pTx->cmdId = _cmdId_getDeviceParam;
	_pTx->frameLen = SWAP16(sizeof(msgAdcWaveState));
	
	_pTx->adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
	_pTx->adc_diff_Enable = _framDatas._adcParam.adc_diff_Enable;
	
	_pTx->adcSignalType = _framDatas._adcParam.adcSignalType;
	_pTx->adcRange = _framDatas._adcParam.adcRange;
	_pTx->trigCh = _framDatas._adcParam.trig_Ch;
	_pTx->adcSamplingRate = SWAP32(_framDatas._adcParam.samplingRate);
	_pTx->adcTrigValue = SWAP16(_framDatas._adcParam.trigValue);
	
	_pTx->adcSramRecordMaxTime = SWAP32(_framDatas._adcParam.sramRecordMaxTime);
	
	_pTx->sramAdutoTrigEnable = _framDatas._adcParam.sramAdutoTrigEnable;

	_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
	usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}

void fun_msgSetAdcChState(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		
		msgUWord * _pRx = (msgUWord*)rxData;
		_framDatas._adcParam.adc_ch_Enable = SWAP16(_pRx->data) ;
		fram_write_datas();
		fram_read_datas();
}

void fun_msgSetAdcDiffState(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		
		msgUbyte * _pRx = (msgUbyte*)rxData;
		_framDatas._adcParam.adc_diff_Enable = _pRx->data ;
		fram_write_datas();
		fram_read_datas();
}

void fun_msgSetAdcSamplingRate(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		
		msgULong * _pRx = (msgULong*)rxData;
		_framDatas._adcParam.samplingRate = SWAP32(_pRx->data) ;
		fram_write_datas();
		fram_read_datas();	

}

void fun_msgSetWaveEnable()
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		 fun_getAdcParam();
		_adcFunctionParam.adcChEnableMaxNum = 0;
	for(u8 i=0;i<8;i++)
	{
		if(_framDatas._adcParam.adc_ch_Enable & (1<<i))
		{
			_adcFunctionParam.adcChEnableIndexBuf[_adcFunctionParam.adcChEnableMaxNum] = i;
			_adcFunctionParam.adcChEnableMaxNum++;
		}
	}
		//除以2再乘以2 是防止出现奇数地址
	_adcFunctionParam.recordOnce_MaxDataLen = (ADC_WAVE_ONCE_LEN / _adcFunctionParam.adcChEnableMaxNum) * _adcFunctionParam.adcChEnableMaxNum;
			_adcFunctionParam.deviceWorkMode = _deviceWorkMode_getWave;
}


void fun_msgSetTrigCh(u8* rxData)
{
		msgUbyte * _pRx = (msgUbyte*)rxData;
		_framDatas._adcParam.trig_Ch = _pRx->data;
		fram_write_datas();
		fram_read_datas();	
}


void fun_msgSetAdcTrigValue(u8* rxData)
{
		msgUWord * _pRx = (msgUWord*)rxData;
		_framDatas._adcParam.trigValue = SWAP16(_pRx->data) ;
		fram_write_datas();
		fram_read_datas();	
}

void fun_msgGetAdcValue()
{
	//停止模式和flash记录仪允许读取
	if((_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop)
		&&(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_adcCalib)){
			return;
		}

	_framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate < 1000? 1000: _framDatas._adcParam.samplingRate;
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN3 = _adcFunctionParam.adc_fpga_sampleLen>>16;
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN2 = _adcFunctionParam.adc_fpga_sampleLen>>8;
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN1 = _adcFunctionParam.adc_fpga_sampleLen>>0;
		
	
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX3 = _adcFunctionParam.adc_fpga_cycleMax>>16;
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX2 = _adcFunctionParam.adc_fpga_cycleMax>>8;
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX1 = _adcFunctionParam.adc_fpga_cycleMax>>0;
		_regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_readFito;

	_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE = _framDatas._adcParam.adc_ch_Enable;
	_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE_TOTAL = _adcFunctionParam.adcChEnableMaxNum*2;
	_regA2FMap.REG_A2F_FPGA_ADC_DIFF_ENABLE = _framDatas._adcParam.adc_diff_Enable;

	rtos_spi_write();
		
	msgGetAdcValue* _pTx = (msgGetAdcValue*)MSG_TX_BUF;
	_pTx->msgHead = SWAP16(0x55aa);
	_pTx->cmdId = _cmdId_getAdcValue;
	_pTx->frameLen = SWAP16(sizeof(msgGetAdcValue));
	
	_pTx->adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
	_pTx->adc_diff_Enable = _framDatas._adcParam.adc_diff_Enable;
	_pTx->adcSignalType = _framDatas._adcParam.adcSignalType;
	_pTx->adcRange = _framDatas._adcParam.adcRange;
	
		_pTx->din = _dioParam.dinAll;
		
		//计算adc值, 读取一次计算一次, 节省资源,提高实时性
		for(u8 i=0;i<8;i++)
		{
			int32 sumTotal = 0;
			for(u16 j=0;j<256;j++)
			{
				sumTotal+=_uadc.getAdc_Buf256[i][j];
			}
			_pTx->data[i] = SWAP32(sumTotal);
		}
	
	_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
	
	usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}





void fun_readRecentConsecutiveDatas()
{
		//停止模式和flash记录仪允许读取
	if((_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop)){
			return;
		}
	
		if(_framDatas._adcParam.samplingRate > 5000)
		{
			_framDatas._adcParam.samplingRate = 5000;
			fram_write_datas();
			fram_read_datas();
		}
		
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN3 = _adcFunctionParam.adc_fpga_sampleLen>>16;
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN2 = _adcFunctionParam.adc_fpga_sampleLen>>8;
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN1 = _adcFunctionParam.adc_fpga_sampleLen>>0;
		
	_regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_readFito;
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX3 = _adcFunctionParam.adc_fpga_cycleMax>>16;
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX2 = _adcFunctionParam.adc_fpga_cycleMax>>8;
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX1 = _adcFunctionParam.adc_fpga_cycleMax>>0;
	
	_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE = _framDatas._adcParam.adc_ch_Enable;
	_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE_TOTAL = _adcFunctionParam.adcChEnableMaxNum*2;
	_regA2FMap.REG_A2F_FPGA_ADC_DIFF_ENABLE = _framDatas._adcParam.adc_diff_Enable;

	rtos_spi_write();

	msgGetRecentConsecutiveDatas* _pTx = (msgGetRecentConsecutiveDatas*)MSG_TX_BUF;
	_pTx->msgHead = SWAP16(0x55aa);
	_pTx->cmdId = _cmdId_readRecentConsecutiveDatas;
	_pTx->frameLen = SWAP16(sizeof(msgGetRecentConsecutiveDatas));
	
	_pTx->adcSamplingRate = SWAP32(_framDatas._adcParam.samplingRate);
	_pTx->adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
	_pTx->adc_diff_Enable = _framDatas._adcParam.adc_diff_Enable;
	_pTx->adcSignalType = _framDatas._adcParam.adcSignalType;
	_pTx->adcRange = _framDatas._adcParam.adcRange;
	_pTx->globalTick = 	SWAP32(_adcFunctionParam.global_tick_ms);//预留缓存数据的时间
	
	_pTx->din = _dioParam.dinAll;
		
		u32 localTick = _uadc.getAdc_BufIndex1000;
		for(u16 i=0;i<1000;i++)
		{
			_pTx->data1[i] = SWAP16(_uadc.getAdc_Buf1000[0][(i + localTick) % 1000]);
			_pTx->data2[i] = SWAP16(_uadc.getAdc_Buf1000[1][(i + localTick) % 1000]);
			_pTx->data3[i] = SWAP16(_uadc.getAdc_Buf1000[2][(i + localTick) % 1000]);
			_pTx->data4[i] = SWAP16(_uadc.getAdc_Buf1000[3][(i + localTick) % 1000]);
			_pTx->data5[i] = SWAP16(_uadc.getAdc_Buf1000[4][(i + localTick) % 1000]);
			_pTx->data6[i] = SWAP16(_uadc.getAdc_Buf1000[5][(i + localTick) % 1000]);
			_pTx->data7[i] = SWAP16(_uadc.getAdc_Buf1000[6][(i + localTick) % 1000]);
			_pTx->data8[i] = SWAP16(_uadc.getAdc_Buf1000[7][(i + localTick) % 1000]);
		}
		
	_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
	
	usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
	
}


void fun_msgStartSramRecord(u8* rxData)
{
		//工作过程中禁止打扰
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
					

		
	msgAdcStartSramRecord *_pRx = (msgAdcStartSramRecord*)rxData;

	_framDatas._adcParam.adc_ch_Enable = SWAP16(_pRx->adc_ch_Enable);
	_framDatas._adcParam.adc_diff_Enable = _pRx->adc_diff_Enable;
	_framDatas._adcParam.adcSignalType = _pRx->adcSignalType;
	_framDatas._adcParam.adcRange = _pRx->adcRange;
	_framDatas._adcParam.samplingRate = SWAP32(_pRx->adcSamplingRate);
	_framDatas._adcParam.sramRecordMaxTime = SWAP32(_pRx->sramSamplingTimeMax);
		
	fram_write_datas();
	fram_read_datas();	

			
		//建立数组,查找需要采集的通道
	_adcFunctionParam.adcChEnableMaxNum = 0;
	for(u8 i=0;i<16;i++)
	{
		if(_framDatas._adcParam.adc_ch_Enable & (1<<i))
		{
			_adcFunctionParam.adcChEnableIndexBuf[_adcFunctionParam.adcChEnableMaxNum] = i;
			_adcFunctionParam.adcChEnableMaxNum++;
		}
	}
		//除以2再乘以2 是防止出现奇数地址
	_adcFunctionParam.recordOnce_MaxDataLen = (ADC_WAVE_ONCE_LEN / _adcFunctionParam.adcChEnableMaxNum) * _adcFunctionParam.adcChEnableMaxNum;
	
		//计算采集时间

	_adcFunctionParam.adc_fpga_sampleLen = _framDatas._adcParam.sramRecordMaxTime 
																					* (_framDatas._adcParam.samplingRate * _adcFunctionParam.adcChEnableMaxNum * 2 / 1000) ;
		
	if(_adcFunctionParam.adc_fpga_sampleLen  > 8300000)
	{
		_adcFunctionParam.adc_fpga_sampleLen  = 8300000;
		_framDatas._adcParam.sramRecordMaxTime = _adcFunctionParam.adc_fpga_sampleLen  
																						/  (_framDatas._adcParam.samplingRate * _adcFunctionParam.adcChEnableMaxNum * 2 / 1000) ;
	}
	
	//根据采样率计算max, fpga主频75M
	_adcFunctionParam.adc_fpga_cycleMax = 75000000/ _framDatas._adcParam.samplingRate - 1;
	
	_adcFunctionParam.sramInitInfo = 1;
		
	//选择上传的接口
	_adcFunctionParam.hour = 0;
	_adcFunctionParam.minute = 0;
	_adcFunctionParam.second = 0;
	

	_regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_stop;
	_regA2FMap.REG_A2F_SRAM_EXIT_TRIG = _framDatas._adcParam.sramAdutoTrigEnable;

	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN3 = _adcFunctionParam.adc_fpga_sampleLen>>16;
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN2 = _adcFunctionParam.adc_fpga_sampleLen>>8;
	_regA2FMap.REG_A2F_SRAM_RECORD_MAX_LEN1 = _adcFunctionParam.adc_fpga_sampleLen>>0;
		
	
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX3 = _adcFunctionParam.adc_fpga_cycleMax>>16;
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX2 = _adcFunctionParam.adc_fpga_cycleMax>>8;
	_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX1 = _adcFunctionParam.adc_fpga_cycleMax>>0;
	
	_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE = _framDatas._adcParam.adc_ch_Enable;
	_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE_TOTAL = _adcFunctionParam.adcChEnableMaxNum*2;
	_regA2FMap.REG_A2F_FPGA_ADC_DIFF_ENABLE = _framDatas._adcParam.adc_diff_Enable;

	rtos_spi_write();
	
	rt_thread_delay(10);
	_regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_writeSram;
	rtos_spi_write();
	rt_thread_delay(10);
	
	//保存采集的起始地址
	_adcFunctionParam.sramIndex = 0;	//sram索引地址归零
	_adcFunctionParam.deviceWorkMode = _deviceWorkMode_sramRecord;
	 _adcFunctionParam.RecodeUpdateTick = 500;
}

void fun_msgReadSramRecordDatas()
{
	if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		rt_thread_delay(10);
	_adcFunctionParam.deviceWorkMode = _deviceWorkMode_getSramRecord;
}


void fun_msgStartOnlineRecord(u8* rxData)
{
	//工作过程中禁止打扰
	if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
		return;
	}

		msgAdcStartSramRecord *_pRx = (msgAdcStartSramRecord*)rxData;

		_framDatas._adcParam.adc_ch_Enable = SWAP16(_pRx->adc_ch_Enable) ;
		_framDatas._adcParam.adcSignalType = _pRx->adcSignalType;
		_framDatas._adcParam.adcRange = _pRx->adcRange;

		_framDatas._adcParam.samplingRate = SWAP32(_pRx->adcSamplingRate);
	
		if(_dioParam.pwmEnable[0]||_dioParam.pwmEnable[1]||_dioParam.pwmEnable[2]||_dioParam.pwmEnable[3]||_dioParam.pwmEnable[4]||_dioParam.pwmEnable[5]
			||_ddsDac.ddsDacWorkMode[0]||_ddsDac.ddsDacWorkMode[1]||_ddsDac.ddsDacWorkMode[2]||_ddsDac.ddsDacWorkMode[3])
		{
			_framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate > 30000 ? 30000 : _framDatas._adcParam.samplingRate; 
		}
		else
		{
			_framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate > 100000? 100000: _framDatas._adcParam.samplingRate;
		}
		
		fram_write_datas();
		fram_read_datas();	
				
		//计算起始通道, 和通道使能信息
		_adcFunctionParam.adcChEnableMaxNum = 0;
		for(u8 i=0;i<16;i++)
		{
			if(_framDatas._adcParam.adc_ch_Enable & (1<<i))
			{
				_adcFunctionParam.adcChEnableMaxNum++;
			}
		}
		_regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_readFito;
			//根据采样率计算max, fpga主频75M
		_adcFunctionParam.adc_fpga_cycleMax = 75000000 / _framDatas._adcParam.samplingRate - 1;
		_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX3 = _adcFunctionParam.adc_fpga_cycleMax>>16;
		_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX2 = _adcFunctionParam.adc_fpga_cycleMax>>8;
		_regA2FMap.REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX1 = _adcFunctionParam.adc_fpga_cycleMax>>0;
		
		_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE = _framDatas._adcParam.adc_ch_Enable;
		_regA2FMap.REG_A2F_FPGA_ADC_CH_ENABLE_TOTAL = _adcFunctionParam.adcChEnableMaxNum*2;
		_regA2FMap.REG_A2F_FPGA_ADC_DIFF_ENABLE = _framDatas._adcParam.adc_diff_Enable;

			rtos_spi_write();
		//除以2再乘以2 是防止出现奇数地址
		_adcFunctionParam.recordOnce_MaxDataLen = (ADC_WAVE_ONCE_LEN / _adcFunctionParam.adcChEnableMaxNum) * _adcFunctionParam.adcChEnableMaxNum;
		_adcFunctionParam.findFirstCh = 1;	//通知adc记录采集到的第一个数据通道号
		_adcFunctionParam.deviceWorkMode = _deviceWorkMode_onlineRecord;
		
		
}

void fun_msgStopOnlineRecord(void)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_onlineRecord){
			return;
		}
		
	_adcFunctionParam.deviceWorkMode = _deviceWorkMode_Stop;
}



void fun_msgStopSramRecord()
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_sramRecord){
			return;
		}
		
		_adcFunctionParam.deviceWorkMode = _deviceWorkMode_Stop;
}



void fun_msgSetDdsDacParam( u8* rxData)
{
		msgDdsDacParam * _pRx = (msgDdsDacParam*)rxData;
	
		_framDatas.dacOutRate = SWAP16(_pRx->dacOutRate);
		if(_pRx->ch > 4)return;

		_framDatas._ddsDacParam[_pRx->ch-1].freq = SWAP16(_pRx->freq);
		_framDatas._ddsDacParam[_pRx->ch-1].volt = SWAP16(_pRx->volt);
		_framDatas._ddsDacParam[_pRx->ch-1].duty = SWAP16(_pRx->duty);
		_framDatas._ddsDacParam[_pRx->ch-1].bias = SWAP16(_pRx->bias);
		_framDatas._ddsDacParam[_pRx->ch-1].phase = SWAP16(_pRx->phase);
	
		fram_write_datas();
		fram_read_datas();	
}

void fun_msgSetDdsDacWorkMode(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode == _deviceWorkMode_onlineRecord){
		_framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate > 30000 ? 30000 : _framDatas._adcParam.samplingRate; 
			_adcFunctionParam.deviceWorkMode = _deviceWorkMode_Stop;
		}
		
		msgUbyte * _pRx = (msgUbyte*)rxData;
		if(_pRx->ch > 4)return;


		_ddsDac.ddsDacWorkMode[_pRx->ch-1] = _pRx->data;
}

void fun_msgSetDdsDatas(u8* rxData)
{
	msgSetDacDatas * _pRx = (msgSetDacDatas*)rxData;
	u16 dataLen = SWAP16(_pRx->dataLen);
	_ddsDac.ddsDatasLen = dataLen >= 10000 ? 10000 : dataLen;
	
	for(u16 i=0;i<_ddsDac.ddsDatasLen;i++)
	{
		_ddsDac.ddsDatas[i] = SWAP16(_pRx->dacDatas[i]);
	}
}

void fun_msgGetDdsDacParam()
{
		msgDdsDacParam* _pTx = (msgDdsDacParam*)MSG_TX_BUF;
		_pTx->msgHead = SWAP16(0x55aa);
		_pTx->frameLen = SWAP16(sizeof(msgDdsDacParam));
		_pTx->dacOutRate = SWAP16(_framDatas.dacOutRate);
	for(u8 i=0;i<4;i++)
	{
		_pTx->cmdId = _cmdId_ddsDacGetParam;
		_pTx->ch = i+1;
		
		_pTx->freq = SWAP16(_framDatas._ddsDacParam[i].freq);
		_pTx->volt = SWAP16(_framDatas._ddsDacParam[i].volt);
		_pTx->duty = SWAP16(_framDatas._ddsDacParam[i].duty);
		_pTx->bias = SWAP16(_framDatas._ddsDacParam[i].bias);
		_pTx->phase = SWAP16(_framDatas._ddsDacParam[i].phase);
			
		_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));

		usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
	}
}

void fun_ddsDacGetCalibParam()
{
		msgGetDacCalibParam* _pTx = (msgGetDacCalibParam*)MSG_TX_BUF;
		_pTx->msgHead = SWAP16(0x55aa);
		_pTx->frameLen = SWAP16(sizeof(msgGetDacCalibParam));
		_pTx->cmdId = _cmdId_ddsDacGetCalibParam;

	for(u8 i=0;i<4;i++)
	{		
		_pTx->_dacCalibDatasPointA[i].calibEnable = _framDatas._dacCalibDatasPointA[i].calibEnable;
		_pTx->_dacCalibDatasPointA[i].calibAnalog = SWAP32(_framDatas._dacCalibDatasPointA[i].calibAnalog);
		_pTx->_dacCalibDatasPointA[i].calibDigital = SWAP32(_framDatas._dacCalibDatasPointA[i].calibDigital);
		_pTx->_dacCalibDatasPointB[i].calibEnable = _framDatas._dacCalibDatasPointB[i].calibEnable;
		_pTx->_dacCalibDatasPointB[i].calibAnalog = SWAP32(_framDatas._dacCalibDatasPointB[i].calibAnalog);
		_pTx->_dacCalibDatasPointB[i].calibDigital = SWAP32(_framDatas._dacCalibDatasPointB[i].calibDigital);
	}
			
		_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));

		usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}

void fun_setDdsDacCalibPoint1(u8* rxData)
{
		msgUWord * _pRx = (msgUWord*)rxData;
		if(_pRx->ch > 4)return;
		if(_pRx->ch == 0)return;
		if(_ddsDac.ddsDacWorkMode[_pRx->ch-1] != _ddsDacWorkMode_Calib)return;
	
		_framDatas._dacCalibDatasPointA[_pRx->ch-1].calibAnalog = SWAP16(_pRx->data);
		_framDatas._dacCalibDatasPointA[_pRx->ch-1].calibDigital = _ddsDac.dacCCR[_pRx->ch-1];
		_framDatas._dacCalibDatasPointA[_pRx->ch-1].calibEnable = 1;
	
		fram_write_datas();
		fram_read_datas();	
	
}


void fun_setDdsDacCalibPoint2(u8* rxData)
{
		msgUWord * _pRx = (msgUWord*)rxData;
		if(_pRx->ch > 4)return;
		if(_pRx->ch == 0)return;
		if(_ddsDac.ddsDacWorkMode[_pRx->ch-1] != _ddsDacWorkMode_Calib)return;
	
		_framDatas._dacCalibDatasPointB[_pRx->ch-1].calibAnalog = SWAP16(_pRx->data) ;
		_framDatas._dacCalibDatasPointB[_pRx->ch-1].calibDigital = _ddsDac.dacCCR[_pRx->ch-1] ;
		_framDatas._dacCalibDatasPointB[_pRx->ch-1].calibEnable = 1;
		fram_write_datas();
		fram_read_datas();	
	
}


void fun_clearDdsDacCalib(u8* rxData)
{
		msgUWord * _pRx = (msgUWord*)rxData;
		if(_pRx->ch > 4)return;
		if(_pRx->ch == 0)return;
		if(_ddsDac.ddsDacWorkMode[_pRx->ch-1] != _ddsDacWorkMode_Calib)return;

		_framDatas._dacCalibDatasPointA[_pRx->ch-1].calibEnable = 0;
		_framDatas._dacCalibDatasPointB[_pRx->ch-1].calibEnable = 0;
		_framDatas._dacCalibDatasPointA[_pRx->ch-1].calibDigital = 0;
		_framDatas._dacCalibDatasPointB[_pRx->ch-1].calibDigital = 0;
		_framDatas._dacCalibDatasPointA[_pRx->ch-1].calibAnalog = 0;
		_framDatas._dacCalibDatasPointB[_pRx->ch-1].calibAnalog = 0;
		fram_write_datas();
		fram_read_datas();	
	
}


void fun_msgSetOutputIO(u8* rxData)
{
	msgUbyte * _pRx = (msgUbyte*)rxData;
	if(_pRx->ch > 8)return;
	else if(_pRx->ch < 3)
	{
		_dioParam.dout[_pRx->ch-1] = !(_pRx->data == 0);
	}
	else
	{
		_dioParam.pwmEnable[_pRx->ch-3] = !(_pRx->data == 0);
	}

}

void fun_msgSetPwmParam(u8* rxData)
{
	msgPwmParam * _pRx = (msgPwmParam*)rxData;
	if(_pRx->ch > 6)return;

	_framDatas._pwmDatas[_pRx->ch-1].pwmFreq = SWAP16(_pRx->pwmFreq);
	_framDatas._pwmDatas[_pRx->ch-1].pwmDuty = SWAP16(_pRx->pwmDuty);
	_dioParam.pwmPulseNum[_pRx->ch-1] = SWAP16(_pRx->pwmPulseNum);
	_framDatas._pwmDatas[_pRx->ch-1].pwmAccUnit = SWAP16(_pRx->pwmAccUnit);
			
	fram_write_datas();
	fram_read_datas();	
}

void fun_msgGetIoAll()
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		_regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_readFito;
		rtos_spi_write();
		
		msgGetDioAll* _pTx = (msgGetDioAll*)MSG_TX_BUF;
		_pTx->msgHead = SWAP16(0x55aa);
		_pTx->frameLen = SWAP16(sizeof(msgGetDioAll));
		_pTx->cmdId = _cmdId_getIoAll;
		

		_pTx->din = _dioParam.dinAll;
		
		_pTx->dout = _dioParam.dout[0] + (_dioParam.dout[1]<<1);

		_pTx->pwmEnable = (_dioParam.pwmEnable[0]<<0)
											+(_dioParam.pwmEnable[1]<<1)
											+(_dioParam.pwmEnable[2]<<2)
											+(_dioParam.pwmEnable[3]<<3)
											+(_dioParam.pwmEnable[4]<<4)
											+(_dioParam.pwmEnable[5]<<5);
		
		
		for(u8 i=0;i<6;i++)
		{
			_pTx->pwmFreq[i] = SWAP16(_framDatas._pwmDatas[i].pwmFreq);
			_pTx->pwmDuty[i] = SWAP16(_framDatas._pwmDatas[i].pwmDuty);
			_pTx->pwmPulseNum[i] = SWAP16(_dioParam.pwmPulseNum[i]);
			_pTx->pwmAccUnit[i] = SWAP16(_framDatas._pwmDatas[i].pwmAccUnit);
		}
		
		_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
		usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
	
}

void fun_setAdcRange(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		msgUbyte * _pRx = (msgUbyte*)rxData;
    //解析数据
		_framDatas._adcParam.adcRange = _pRx->data;

		fram_write_datas();
		fram_read_datas();	
}

void fun_setAdcSignalType(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
		return;
		}
		msgUbyte * _pRx = (msgUbyte*)rxData;
    //解析数据
		_framDatas._adcParam.adcSignalType = _pRx->data;

		fram_write_datas();
		fram_read_datas();	
}

void fun_sramAdutoTrigEnable(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		
		msgUbyte * _pRx = (msgUbyte*)rxData;
		_framDatas._adcParam.sramAdutoTrigEnable = _pRx->data ;
		fram_write_datas();
		fram_read_datas();
}

//void fun_getSoftVersion()
//{
//		msgULong* _pTx = (msgULong*)MSG_TX_BUF;
//		_pTx->msgHead = SWAP16(0x55aa);
//		_pTx->frameLen = SWAP16(sizeof(msgULong));
//		_pTx->cmdId = _cmdId_getSoftVersion;
//		
//		_pTx->data = SWAP32(_framDatas.softVersion);

//		_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
//		usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
////		HAL_GPIO_WritePin(BOOT_HIGH_GPIO_Port,BOOT_HIGH_Pin,1);
////		rt_thread_delay(10);
////		NVIC_SystemReset();
//	
//}

//设置页面adc标定
void fun_setAdcCalibPoint1(u8* rxData)
{
		msgULong * _pRx = (msgULong*)rxData;
		if(_pRx->ch > 8)return;
		if(_pRx->ch == 0)return;
		if(_adcFunctionParam.deviceWorkMode  != _deviceWorkMode_adcCalib)return;
	
			int32 sumTotal = 0;
			for(u16 j=0;j<256;j++)
			{
				sumTotal+=_uadc.getAdc_Buf256[_pRx->ch-1][j];
			}
		
		_framDatas._adcCalibDatasPointA[_pRx->ch-1].calibAnalog = SWAP32(_pRx->data);
		_framDatas._adcCalibDatasPointA[_pRx->ch-1].calibDigital = sumTotal;
		_framDatas._adcCalibDatasPointA[_pRx->ch-1].calibEnable = 1;
	
		fram_write_datas();
		fram_read_datas();	
	
}


void fun_setAdcCalibPoint2(u8* rxData)
{
		msgULong * _pRx = (msgULong*)rxData;
		if(_pRx->ch > 8)return;
		if(_pRx->ch == 0)return;
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_adcCalib)return;
	
			u32 sumTotal = 0;
			for(u16 j=0;j<256;j++)
			{
				sumTotal+=_uadc.getAdc_Buf256[_pRx->ch-1][j];
			}

		_framDatas._adcCalibDatasPointB[_pRx->ch-1].calibAnalog = SWAP32(_pRx->data);
		_framDatas._adcCalibDatasPointB[_pRx->ch-1].calibDigital = sumTotal;
		_framDatas._adcCalibDatasPointB[_pRx->ch-1].calibEnable = 1;
		fram_write_datas();
		fram_read_datas();	
	
}


void fun_clearAdcCalib(u8* rxData)
{
		msgUWord * _pRx = (msgUWord*)rxData;
		if(_pRx->ch > 8)return;
		if(_pRx->ch == 0)return;
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_adcCalib)return;

		_framDatas._adcCalibDatasPointA[_pRx->ch-1].calibEnable = 0;
		_framDatas._adcCalibDatasPointA[_pRx->ch-1].calibAnalog = 0;
		_framDatas._adcCalibDatasPointA[_pRx->ch-1].calibDigital = 0;
	
		_framDatas._adcCalibDatasPointB[_pRx->ch-1].calibEnable = 0;
		_framDatas._adcCalibDatasPointB[_pRx->ch-1].calibAnalog = 0;
		_framDatas._adcCalibDatasPointB[_pRx->ch-1].calibDigital = 0;		
	
		_framDatas.correctFactor[_pRx->ch-1] = 100000;
		_framDatas.calibZero[_pRx->ch-1] = 0;
		fram_write_datas();
		fram_read_datas();	
	
}

void fun_enterAdcCalibMode(u8* rxData)
{
		msgUbyte * _pRx = (msgUbyte*)rxData;

		if(_adcFunctionParam.deviceWorkMode == _deviceWorkMode_Stop)
		{
			if(_pRx->data == 1)
			{
				_adcFunctionParam.deviceWorkMode = _deviceWorkMode_adcCalib;
			}
		}
		else if(_adcFunctionParam.deviceWorkMode == _deviceWorkMode_adcCalib)
		{
			if(_pRx->data == 0)
			{
				_adcFunctionParam.deviceWorkMode = _deviceWorkMode_Stop;
			}
		}
}


void fun_setCorrectFactor(u8* rxData)
{
		msgULong * _pRx = (msgULong*)rxData;
		if(_pRx->ch > 8)return;
		if(_pRx->ch == 0)return;
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_adcCalib)return;
	
		_framDatas.correctFactor[_pRx->ch-1] = SWAP32(_pRx->data);

		fram_write_datas();
		fram_read_datas();	
}

void fun_setCalibZero(u8* rxData)
{
		msgULong * _pRx = (msgULong*)rxData;
		if(_pRx->ch > 8)return;
		if(_pRx->ch == 0)return;
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_adcCalib)return;
	
		_framDatas.calibZero[_pRx->ch-1] = SWAP32(_pRx->data);

		fram_write_datas();
		fram_read_datas();	
}


void fun_msgGetCalibVolt()
{
	//非校准模式无法读取
	if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_adcCalib){
			return;
		}

	msgGetCalibVolt* _pTx = (msgGetCalibVolt*)MSG_TX_BUF;
	_pTx->msgHead = SWAP16(0x55aa);
	_pTx->cmdId = _cmdId_getCalibVolt;
	_pTx->frameLen = SWAP16(sizeof(msgGetCalibVolt));
	
	_pTx->adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
	_pTx->adcRange = _framDatas._adcParam.adcRange;
	
		//计算adc值, 读取一次计算一次, 节省资源,提高实时性
		for(u8 i=0;i<8;i++)
		{
			int32 sumTotal = 0;
			for(u16 j=0;j<256;j++)
			{
				sumTotal+=_uadc.getAdc_Buf256[i][j];
			}
			_pTx->data[i] = SWAP32(sumTotal);
		}
	
	_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
	
	usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}


void fun_setRecordDelay(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_Stop){
			return;
		}
		
		msgUbyte * _pRx = (msgUbyte*)rxData;
		_framDatas.RecordDelay = _pRx->data ;
		fram_write_datas();
		fram_read_datas();
}

void fun_setSensorUnit(u8* rxData)
{
		if(_adcFunctionParam.deviceWorkMode != _deviceWorkMode_adcCalib){
			return;
		}
		
		msgUbyte * _pRx = (msgUbyte*)rxData;
		if(_pRx->ch > 8)return;
		if(_pRx->ch == 0)return;

		_framDatas.sensorUnit[_pRx->ch - 1] = _pRx->data ;
		fram_write_datas();
		fram_read_datas();
}

void fun_getSettingParam()
{
		msgGetSettingParam* _pTx = (msgGetSettingParam*)MSG_TX_BUF;
		_pTx->msgHead = SWAP16(0x55aa);
		_pTx->frameLen = SWAP16(sizeof(msgGetSettingParam));
		_pTx->cmdId = _cmdId_getSettingParam;

		_pTx->deviceWorkMode = (_adcFunctionParam.deviceWorkMode == _deviceWorkMode_adcCalib);
	
		for(u8 i=0;i<8;i++)
		{
			_pTx->_adcCalibDatasPointA[i].calibEnable = _framDatas._adcCalibDatasPointA[i].calibEnable;
			_pTx->_adcCalibDatasPointA[i].calibDigital = SWAP32(_framDatas._adcCalibDatasPointA[i].calibDigital);
			_pTx->_adcCalibDatasPointA[i].calibAnalog = SWAP32(_framDatas._adcCalibDatasPointA[i].calibAnalog);
			 
			_pTx->_adcCalibDatasPointB[i].calibEnable = _framDatas._adcCalibDatasPointB[i].calibEnable;
			_pTx->_adcCalibDatasPointB[i].calibDigital = SWAP32(_framDatas._adcCalibDatasPointB[i].calibDigital);
			_pTx->_adcCalibDatasPointB[i].calibAnalog = SWAP32(_framDatas._adcCalibDatasPointB[i].calibAnalog);
			
			_pTx->correctFactor[i] = SWAP32(_framDatas.correctFactor[i]);
			_pTx->calibZero[i] = SWAP32(_framDatas.calibZero[i]);
			_pTx->sensorUnit[i] = _framDatas.sensorUnit[i];
		}

		_pTx->softVersion = SWAP32(_framDatas.softVersion);
		_pTx->RecordDelay = _framDatas.RecordDelay;
		
		_pTx->crc = SWAP16(getCrc16WithTail((u8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
		usb_sendMsg(MSG_TX_BUF,SWAP16(_pTx->frameLen));
	
}

//开始处理USB数据
void fun_msgProcess_task(u8 *rxData)
{
  msgHead *_pRx = (msgHead *)rxData;

  //CRC校验
  if (!checkCrc16WithTail((u8 *)rxData, SWAP16(_pRx->frameLen)))
  {
    return;
  }
  //翻转电平
  HAL_GPIO_TogglePin(LED_USB_GPIO_Port, LED_USB_Pin);
  //判断数据包头
  if (_pRx->msgHead != SWAP16(0x55aa))
  {
    // 如果起始帧不为0x55aa, 则说明报文受污染, 丢弃
  }
  else
  {
    //判断数据包指令类型
    switch (_pRx->cmdId)
    {
    // 设置adc采样范围
    case _cmdId_setAdcRange:
      fun_setAdcRange(rxData);
      break;

    case _cmdId_setAdcSignalType:
      fun_setAdcSignalType(rxData);
      break;

    case _cmdId_setAdc_chEnable:
      fun_msgSetAdcChState(rxData);
      fun_getAdcParam();
      break;

    case _cmdId_setAdc_diffEnable:
      fun_msgSetAdcDiffState(rxData);
      fun_getAdcParam();
      break;

    case _cmdId_getDeviceParam:
      fun_getAdcParam();
      break;

    case _cmdId_setAdc_samplingRate:
      fun_msgSetAdcSamplingRate(rxData);
      fun_getAdcParam();
      break;

    case _cmdId_getAdcValue:
      fun_msgGetAdcValue();
      break;

    // SRAM记录仪
    case _cmdId_startSramRecord:
      fun_msgStartSramRecord(rxData);
      fun_getAdcParam();
      break;

    case _cmdId_stopSramRecord:
      fun_msgStopSramRecord();
      break;

    case _cmdId_getSramRecordDatas:
      fun_getAdcParam();
      fun_msgReadSramRecordDatas();
      break;

    // 在线记录仪
    case _cmdId_startOnlineRecord:
      fun_msgStartOnlineRecord(rxData);
      break;

    case _cmdId_stopOnlineRecord:
      fun_msgStopOnlineRecord();
      break;

      // 连续续记录仪
    case _cmdId_readRecentConsecutiveDatas:
      fun_readRecentConsecutiveDatas();
      break;

      // DDS信号发生器
    case _cmdId_setDdsDacParam:
      fun_msgSetDdsDacParam(rxData);
      fun_msgGetDdsDacParam();
      break;

    case _cmdId_setDdsDacWorkMode:
      fun_msgSetDdsDacWorkMode(rxData);
      fun_msgGetDdsDacParam();
      break;

    case _cmdId_setDdsDacDatas:
      fun_msgSetDdsDatas(rxData);
      fun_msgGetDdsDacParam();
      break;

    case _cmdId_ddsDacGetParamTotal:
      fun_msgGetDdsDacParam();
      fun_ddsDacGetCalibParam();
      break;

    case _cmdId_ddsDacCalibPoint1:
      fun_setDdsDacCalibPoint1(rxData);
      fun_ddsDacGetCalibParam();
      break;

    case _cmdId_ddsDacCalibPoint2:
      fun_setDdsDacCalibPoint2(rxData);
      fun_ddsDacGetCalibParam();
      break;

    case _cmdId_ddsDacClearCalib:
      fun_clearDdsDacCalib(rxData);
      fun_ddsDacGetCalibParam();
      break;

    case _cmdId_ddsDacGetCalibParam:
      fun_ddsDacGetCalibParam();
      break;

      // 数字输出
    case _cmdId_setOutputIO:
      fun_msgSetOutputIO(rxData);
      fun_msgGetIoAll();
      break;

    case _cmdId_setPwmParam:
      fun_msgSetPwmParam(rxData);
      fun_msgGetIoAll();
      break;

    case _cmdId_getIoAll:
      fun_msgGetIoAll();
      break;

    // 设置页面
    case _cmdId_getSettingParam:
      fun_getSettingParam();
      break;

    case _cmdId_settingAdcCalibPoint1:
      fun_setAdcCalibPoint1(rxData);
      fun_getSettingParam();
      break;

    case _cmdId_settingAdcCalibPoint2:
      fun_setAdcCalibPoint2(rxData);
      fun_getSettingParam();
      break;

    case _cmdId_settingClearAdcCalibDatas:
      fun_clearAdcCalib(rxData);
      fun_getSettingParam();
      break;

    case _cmdId_settingSetAdcCalibMode:
      fun_enterAdcCalibMode(rxData);
      fun_getSettingParam();
      break;

    // 修正系数 修正值
    case _cmdId_setCorrectFactor:
      fun_setCorrectFactor(rxData);
      fun_getSettingParam();
      break;

    case _cmdId_setCalibZero:
      fun_setCalibZero(rxData);
      fun_getSettingParam();
      break;

    case _cmdId_sramAdutoTrigEnable:
      fun_sramAdutoTrigEnable(rxData);
      break;

    case _cmdId_getCalibVolt:
      fun_msgGetCalibVolt();
      break;

    case _cmdId_setRecordDelay:
      fun_setRecordDelay(rxData);
      fun_getSettingParam();
      break;

    case _cmdId_setSensorUnit:
      fun_setSensorUnit(rxData);
      fun_getSettingParam();
      break;

    case _cmdId_getSoftVersion:
      fun_getSettingParam();
      break;

    default:
      break;
    }
  }
}

void usbAutoUpload_thread_task()
{
		if(_dioParam.uploadFinshFlag == 1)
		{
			fun_msgGetIoAll();
			_dioParam.uploadFinshFlag = 0;
		}
}