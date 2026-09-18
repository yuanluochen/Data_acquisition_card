#include "main.h"
#pragma pack(1)

void waitHostCrcCheckReturn();

adcFunctionParam _adcFunctionParam;
_adcSendBuf _adcBuf;
_adcSendBuf _adcBufB;

u8 RECORD_MSG_TXBUF[500];
static u32 adc_tim_arr, adc_tim_psc;
static u32 adc_tim_sys_clk = 84000000;

void adcFunction_tim_task()
{

  // sram记录仪时间
  if (_adcFunctionParam.deviceWorkMode == _deviceWorkMode_sramRecord)
  {
    _adcFunctionParam.RecodeUpdateTick++;
    _adcFunctionParam.recordTimeTick++;
    // 用来记录时钟 处理当前时间
    if (_adcFunctionParam.recordTimeTick >= 1000)
    {
      _adcFunctionParam.recordTimeTick = 0;
      _adcFunctionParam.second++;
      if (_adcFunctionParam.second >= 60)
      {
        _adcFunctionParam.second = 0;
        _adcFunctionParam.minute++;
      }

      if (_adcFunctionParam.minute >= 60)
      {
        _adcFunctionParam.minute = 0;
        _adcFunctionParam.hour++;
      }
    } // 截止 记录时钟
  }
  else
  {
    _adcFunctionParam.RecodeUpdateTick = 0;
  }
}

u8 trig_his = 0;
u16 sram_fifo_read_tick = 0;

void adcFunction_thread()
{
  //usb虚拟串口运行检测
  if (_usbMsg.usbWorkFlag == 0 && _adcFunctionParam.deviceWorkMode == _deviceWorkMode_onlineRecord)
  {
    _adcFunctionParam.deviceWorkMode = _deviceWorkMode_Stop;
  }
  // 在线记录模式
  if (_adcFunctionParam.deviceWorkMode == _deviceWorkMode_onlineRecord)
  {
    //设置采样率，在没有PWM或者DAC运行的情况下，采样率最大100k，要是有的话最大30k
    _framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate > 100000 ? 100000 : _framDatas._adcParam.samplingRate;
    if (_dioParam.pwmEnable[0] || _dioParam.pwmEnable[1] || _dioParam.pwmEnable[2] || _dioParam.pwmEnable[3] || _dioParam.pwmEnable[4] || _dioParam.pwmEnable[5] || _ddsDac.ddsDacWorkMode[0] || _ddsDac.ddsDacWorkMode[1] || _ddsDac.ddsDacWorkMode[2] || _ddsDac.ddsDacWorkMode[3])
    {
      _framDatas._adcParam.samplingRate = _framDatas._adcParam.samplingRate > 30000 ? 30000 : _framDatas._adcParam.samplingRate;
    }
  }
  // SRAM模式
  if (_adcFunctionParam.deviceWorkMode == _deviceWorkMode_sramRecord)
  {
    //如果计数值变了 -> 切入读取并上传
    if (_adcFunctionParam.sramBufCnt != _adcFunctionParam.sramBufCnt_his)
    {
      _adcFunctionParam.deviceWorkMode = _deviceWorkMode_getSramRecord;
    }
    //保存当前数据
    _adcFunctionParam.sramBufCnt_his = _adcFunctionParam.sramBufCnt;
  }

  // 如果启用外部触发,且为sram模式
  // FPGA 收到外部触发信号才开始录一段，录满后 MCU 自动把这段读出来上传，然后等下一次触发。
  if (_framDatas._adcParam.sramAdutoTrigEnable & (_regA2FMap.REG_A2F_SRAM_WORK_MODE == _fpgaWorkMode_writeSram))
  {
    // 如果计数值变了 -> 切入读取并上传
    if (_adcFunctionParam.sramBufCnt != _adcFunctionParam.sramBufCnt_his)
    {
      _adcFunctionParam.deviceWorkMode = _deviceWorkMode_getSramRecord;
    }
    // 保存当前数据
    _adcFunctionParam.sramBufCnt_his = _adcFunctionParam.sramBufCnt;
  }

  // 波形采集完成, 上传数据至上位机，根据adc_collectFullFlag判断用那个缓冲区
  if (_adcFunctionParam.adc_collectFullFlag == 2)
  {
    _adcBuf.msgHead = SWAP16(0x55aa);
    _adcBuf.cmdId = _cmdId_readOnlineRecordDatas;
    _adcBuf.frameLen = SWAP16(sizeof(_adcBuf));
    _adcBuf.adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
    _adcBuf.adc_diff_Enable = _framDatas._adcParam.adc_diff_Enable;
    _adcBuf.samplingRate = SWAP32(_framDatas._adcParam.samplingRate);
    _adcBuf.adcRange = _framDatas._adcParam.adcRange;
    _adcBuf.adcSignalType = _framDatas._adcParam.adcSignalType;
    _adcBuf.dataLen = SWAP16(_adcFunctionParam.recordOnce_MaxDataLen);
    // 计算crc
    _adcBuf.crc = SWAP16(getCrc16WithTail((u8 *)&_adcBuf, sizeof(_adcBuf)));

    usb_sendMsg((u8 *)&_adcBuf, SWAP16(_adcBuf.frameLen));
    _adcFunctionParam.adc_collectFullFlag = 0;
    // memset((u8*)&_adcBuf,0,sizeof(_adcSendBuf));
  }
  else if (_adcFunctionParam.adc_collectFullFlag == 3)
  {
    _adcBufB.msgHead = SWAP16(0x55aa);
    _adcBufB.cmdId = _cmdId_readOnlineRecordDatas;
    _adcBufB.frameLen = SWAP16(sizeof(_adcBufB));
    _adcBufB.adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
    _adcBufB.adc_diff_Enable = _framDatas._adcParam.adc_diff_Enable;
    _adcBufB.samplingRate = SWAP32(_framDatas._adcParam.samplingRate);
    _adcBufB.adcRange = _framDatas._adcParam.adcRange;
    _adcBufB.adcSignalType = _framDatas._adcParam.adcSignalType;
    _adcBufB.dataLen = SWAP16(_adcFunctionParam.recordOnce_MaxDataLen);
    // 计算crc
    _adcBufB.crc = SWAP16(getCrc16WithTail((u8 *)&_adcBufB, sizeof(_adcBufB)));

    usb_sendMsg((u8 *)&_adcBufB, SWAP16(_adcBufB.frameLen));
    _adcFunctionParam.adc_collectFullFlag = 0;
    // memset((u8*)&_adcBufB,0,sizeof(_adcSendBuf));
  }

  // 上位机读取sram记录仪信息
  if (_adcFunctionParam.deviceWorkMode == _deviceWorkMode_getSramRecord)
  {
    //FPGA设置为读取模式
    _regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_readSram;
    rtos_spi_write();

    // 除以2再乘以2 是防止出现奇数地址

    // 上传记录仪开始,给进度条使用
    msgULong *_pRecordUploadTx = (msgULong *)RECORD_MSG_TXBUF;
    _pRecordUploadTx->msgHead = SWAP16(0x55aa);
    _pRecordUploadTx->frameLen = SWAP16(sizeof(msgULong));
    _pRecordUploadTx->data = SWAP32(_adcFunctionParam.adc_fpga_sampleLen); // 上传SRAM最大数据长度
    _pRecordUploadTx->cmdId = _cmdId_recordUploadStart;
    _pRecordUploadTx->crc = SWAP16(getCrc16WithTail((u8 *)RECORD_MSG_TXBUF, SWAP16(_pRecordUploadTx->frameLen)));
    usb_sendMsg(RECORD_MSG_TXBUF, SWAP16(_pRecordUploadTx->frameLen));
    rt_thread_delay(10 + _framDatas.RecordDelay);

    // 计算起始通道, 和通道使能信息
    _adcFunctionParam.adcChEnableMaxNum = 0;
    _adcFunctionParam.sramReadStartIndex = 0;
    for (u8 i = 0; i < 16; i++)
    {
      if (_framDatas._adcParam.adc_ch_Enable & (1 << i))
      {
        _adcFunctionParam.adcChEnableIndexBuf[_adcFunctionParam.adcChEnableMaxNum] = i;
        _adcFunctionParam.adcChEnableMaxNum++;
      }
    }
    _adcBuf.msgHead = SWAP16(0x55aa);
    _adcBuf.cmdId = _cmdId_getSramRecordDatas;
    _adcBuf.frameLen = SWAP16(sizeof(_adcSendBuf));
    _adcBuf.adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
    _adcBuf.adc_diff_Enable = _framDatas._adcParam.adc_diff_Enable;
    _adcBuf.samplingRate = SWAP32(_framDatas._adcParam.samplingRate);

    _adcBuf.adcRange = _framDatas._adcParam.adcRange;
    _adcBuf.adcSignalType = _framDatas._adcParam.adcSignalType;

    // 循环上传扇区信息
    u16 sramOnceDataLen = (ADC_WAVE_ONCE_LEN) / _adcFunctionParam.adcChEnableMaxNum * _adcFunctionParam.adcChEnableMaxNum;

    _adcFunctionParam.sram_update_addr = _adcFunctionParam.adcChEnableMaxNum * 2;
    sram_fifo_read_tick = 0;
    while (_adcFunctionParam.sram_update_addr < _adcFunctionParam.adc_fpga_sampleLen)
    {
      // 每次传输长度为通道数的整数倍
      if (sram_fifo_read_tick != 0)
      {
        memcpy((u8 *)&_adcBufB, (u8 *)&_adcBuf, sizeof(_adcBuf));
      }
      rt_thread_delay(1);
      if ((_adcFunctionParam.adc_fpga_sampleLen - _adcFunctionParam.sram_update_addr) > (sramOnceDataLen * 2))
      {

        QSPI_ReadDatas_DMA(0xeb, 6, (u8 *)&_adcBuf.data, _adcFunctionParam.sram_update_addr, sramOnceDataLen * 2);
        _adcFunctionParam.sram_update_addr += sramOnceDataLen * 2;
        _adcBuf.dataLen = SWAP16(sramOnceDataLen);
      }
      else
      {
        QSPI_ReadDatas_DMA(0xeb, 6, (u8 *)&_adcBuf.data, _adcFunctionParam.sram_update_addr,
                           (_adcFunctionParam.adc_fpga_sampleLen - _adcFunctionParam.sram_update_addr));

        _adcBuf.dataLen = SWAP16(
            ((_adcFunctionParam.adc_fpga_sampleLen - _adcFunctionParam.sram_update_addr) / 2) / _adcFunctionParam.adcChEnableMaxNum * _adcFunctionParam.adcChEnableMaxNum);
        _adcFunctionParam.sram_update_addr = _adcFunctionParam.adc_fpga_sampleLen;
      }

      if (sram_fifo_read_tick != 0)
      {
        _adcBufB.crc = SWAP16(getCrc16WithTail((u8 *)&_adcBufB, SWAP16(_adcBufB.frameLen)));
        usb_sendMsg((u8 *)&_adcBufB, SWAP16(_adcBufB.frameLen));
      }

      rt_thread_delay(3 + _framDatas.RecordDelay);
      sram_fifo_read_tick = 1;
    }

    // 循环结束，上传最后一次DMA读到的_adcBuf数据
    if (sram_fifo_read_tick == 1)
    {
      memcpy((u8 *)&_adcBufB, (u8 *)&_adcBuf, sizeof(_adcBuf));
      _adcBufB.crc = SWAP16(getCrc16WithTail((u8 *)&_adcBufB, SWAP16(_adcBufB.frameLen)));
      usb_sendMsg((u8 *)&_adcBufB, SWAP16(_adcBufB.frameLen));
      rt_thread_delay(5 + _framDatas.RecordDelay);
    }

    rt_thread_delay(5 + _framDatas.RecordDelay);
    // 计算下次上传的起始通道
    //_adcFunctionParam.sramReadStartIndex += _adcBufB.dataLen;

    rt_thread_delay(10 + _framDatas.RecordDelay);
    // 上传记录仪开始,给进度条使用
    _pRecordUploadTx->msgHead = SWAP16(0x55aa);
    _pRecordUploadTx->frameLen = SWAP16(sizeof(msgULong));
    _pRecordUploadTx->cmdId = _cmdId_recordUploadEnd;
    _pRecordUploadTx->ch = 0;
    _pRecordUploadTx->crc = SWAP16(getCrc16WithTail((u8 *)RECORD_MSG_TXBUF, SWAP16(_pRecordUploadTx->frameLen)));
    usb_sendMsg(RECORD_MSG_TXBUF, _pRecordUploadTx->frameLen);
    rt_thread_delay(1 + _framDatas.RecordDelay);

    _adcFunctionParam.deviceWorkMode = _deviceWorkMode_Stop;
    _regA2FMap.REG_A2F_SRAM_WORK_MODE = _fpgaWorkMode_writeSram;
    rtos_spi_write();
  }

  // 记录仪自动上传低速采集信息,
  if (_adcFunctionParam.deviceWorkMode == _deviceWorkMode_sramRecord) // nn: no nvm data start, 掉电不保存, 每次点击才测试
  {
    if (_adcFunctionParam.RecodeUpdateTick > 500)
    {
      _adcFunctionParam.RecodeUpdateTick = 0;

      msgAutoUploadDatas *_pTx = (msgAutoUploadDatas *)RECORD_MSG_TXBUF;
      _pTx->msgHead = SWAP16(0x55aa);
      _pTx->cmdId = _cmdId_sramRecordAutoUploadDatas;
      _pTx->frameLen = SWAP16(sizeof(msgAutoUploadDatas));

      _pTx->adc_ch_Enable = SWAP16(_framDatas._adcParam.adc_ch_Enable);
      _pTx->adc_diff_Enable = _framDatas._adcParam.adc_diff_Enable;

      _pTx->adcSignalType = _framDatas._adcParam.adcSignalType;
      _pTx->adcRange = _framDatas._adcParam.adcRange;

      _pTx->hour = _adcFunctionParam.hour;
      _pTx->minute = _adcFunctionParam.minute;
      _pTx->second = _adcFunctionParam.second;
      _pTx->crc = SWAP16(getCrc16WithTail((u8 *)RECORD_MSG_TXBUF, SWAP16(_pTx->frameLen)));

      usb_sendMsg((u8 *)&RECORD_MSG_TXBUF, SWAP16(_pTx->frameLen));
    }
  }
}
