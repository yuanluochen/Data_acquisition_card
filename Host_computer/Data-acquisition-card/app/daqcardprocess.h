#ifndef DAQCARDPROCESS_H
#define DAQCARDPROCESS_H

#include <msgStruct.h>
#include <QVector>
#include <QObject>

class daqCardProcess : public QObject
{
  Q_OBJECT
public:
  daqCardProcess(){};
  // 数据解码
  void dataDecode(const uint8_t *buf);

private:
  void decodeOnlineRecordDatas(const uint8_t *buf);

private:
  // cur Id
  uint8_t _cmdId;
signals:
  void dacRTVal(QVector<int32_t> rtVal);
};


#endif // DAQCARDPROCESS_H
