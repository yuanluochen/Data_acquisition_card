#include "daqCardProcess.h"
#include "crc16.h"

void daqCardProcess::dataDecode(const uint8_t *buf)
{
  const msgHead *_pRx = reinterpret_cast<const msgHead *>(buf);

  // CRC校验
  if (!checkCrc16WithTail((uint8_t *)buf, _pRx->frameLen))
  {
    return;
  }
  // 判断数据包头
  if (_pRx->msgHead != 0x55aa)
  {
    return;
  }
  // 根据命令段进行分类
  this->_cmdId = _pRx->cmdId;
  switch (this->_cmdId)
  {
  case _cmdId_readOnlineRecordDatas:
    // 解码
    this->decodeOnlineRecordDatas(buf);
    break;
  case _cmdId_recordUploadStart:
    break;
  case _cmdId_recordUploadEnd:
    break;
  case _cmdId_sramRecordAutoUploadDatas:
    break;
  case _cmdId_ddsDacGetParam:
    break;
  case _cmdId_ddsDacGetCalibParam:
    break;
  }
}

void daqCardProcess::decodeOnlineRecordDatas(const uint8_t *buf)
{
  // 解码
  const msgGetAdcValue *_pD = reinterpret_cast<const msgGetAdcValue *>(buf);
  //输出信息
  std::array<int32_t, 8> rx;
  //遍历幅值
  for (int i = 0 ; i < rx.size(); i++){
    rx[i] = _pD->data[i];
  }
  //输出
  emit this->dacRTVal(rx);
}

QVector<uint8_t> daqCardProcess::adcRecordControlEncode(bool state , const std::array<bool, 8> & adcCh, uint32_t sampleRate)
{
  msgAdcStartOnlineRecord msg;
  //赋值
  msg.msgHead = SWAP16(0x55aa);
  msg.frameLen = SWAP16(sizeof(msgAdcStartOnlineRecord));
  //开启采集
  if (state)
  {
    msg.cmdId = _cmdId_startOnlineRecord;

    // adc 采集口使能
    uint16_t chEna = 0;
    int i = 0;
    for (const auto e : adcCh)
    {
      chEna += (e << i);
      i++;
    }
    msg.adc_ch_Enable = SWAP16(chEna);
    // adc 差分通道使能
    msg.adc_diff_Enable = 0;

    // 信号类型
    msg.adcSignalType = 1;
    // 采样范围
    msg.adcRange = 1;

    // 采样率
    if (sampleRate > max_sampRate)
    {
      sampleRate = max_sampRate;
    }

    if (sampleRate < min_sampRate)
    {
      sampleRate = min_sampRate;
    }
    msg.adcSamplingRate = SWAP32(sampleRate);
  }
  else{
    //关闭采集
    msg.cmdId = _cmdId_stopOnlineRecord;
  }

  //CRC
  msg.crc = SWAP16(getCrc16WithTail((unsigned char *)(&msg), msg.frameLen));

  QVector<uint8_t> data;
  //拆数据
  uint8_t *pM = reinterpret_cast<uint8_t *> (&msg);
  for (int i = 0; i < sizeof(msg); i++){
    data.push_back(pM[i]);
  }
  return data;
}