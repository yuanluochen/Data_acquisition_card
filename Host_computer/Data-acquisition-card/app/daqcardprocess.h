#ifndef DAQCARDPROCESS_H
#define DAQCARDPROCESS_H

#include "msgStruct.h"
#include <QObject>
#include <array>



class daqCardProcess : public QObject
{
  Q_OBJECT
public:
  daqCardProcess(){};
  // 数据解码
  void dataDecode(const uint8_t *);
  // 记录仪开关控制
  QVector<uint8_t> adcRecordControlEncode(bool state, const std::array<bool, 8> &adcCh = {}, uint32_t sampleRate = 0);

private:
  void decodeOnlineRecordDatas(const uint8_t *);

private:
  // cur Id
  uint8_t _cmdId;
  //采样率
  const uint32_t max_sampRate = 1000000;
  const uint32_t min_sampRate = 10;
signals:
  void dacRTVal(std::array<int32_t, 8> rtVal);
};


#endif // DAQCARDPROCESS_H
