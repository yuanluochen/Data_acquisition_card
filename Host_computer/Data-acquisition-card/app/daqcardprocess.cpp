#include "daqCardProcess.h"
#include "crc16.h"

void daqCardProcess::dataDecode(const uint8_t *buf)
{
  msgHead *_pRx = (msgHead *)buf;

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
  msgGetAdcValue *_pData = (msgGetAdcValue *)buf;
  //
}
