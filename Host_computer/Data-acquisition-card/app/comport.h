#ifndef COMPORT_H
#define COMPORT_H
#include <QMainWindow>
#include <QSerialPort>
#include <QObject>
#include <QThread>
#include "daqCardProcess.h"
#include "struct_typedef.h"
QT_BEGIN_NAMESPACE
class comPort : public QObject
{
  Q_OBJECT
public:
  comPort(){
    // 实例化串口对象
    this->_serialport = new QSerialPort();
  };     
  // 析构函数
  ~comPort(){
    // 关闭串口
    if (this->isopen())
    {
      // 已经打开，关闭
      this->_serialport->close();
    }
    // 释放内存
    delete this->_serialport;
    qDebug() << "comPort  has been released";
  }
  // 判断串口是否开启
  bool isopen(){
    return this->_serialport->isOpen();
  }
  //设置串口名
  void setName(QString name){
    this->_name = name;
  }
  // 开启串口
  bool open();
  //关闭串口
  void close(){
    this->_serialport->close();
    qDebug() << "close serial port successful";
  }
  void startRecord(std::array<bool, 8> &adcCh, uint32_t sampleRate){
    QVector<uint8_t> data = this->_daqCardProcess.adcRecordControlEncode(true, adcCh, sampleRate);
    QByteArray txdata;
    for (const auto e : data){
      txdata.append(static_cast<char>(e));
    }
    int i = 0;
    // for (auto e : data){
    //   qDebug() << "data " << i++ << " :" << Qt::hex << Qt::showbase << e;
    // }
    for (auto e : txdata)
    {
      qDebug() << "data " << i++ << " :" << Qt::hex << Qt::showbase << static_cast<uint8_t>(e);
    }

    this->_serialport->write(txdata);
  }
  void stopRecord(){
    QVector<uint8_t> data = this->_daqCardProcess.adcRecordControlEncode(false);
    QByteArray txdata;
    for (const auto e : data)
    {
      txdata.append(static_cast<char>(e));
    }
  }

public:
  // 串口对象
  QSerialPort *_serialport;
  // 数据解码对象
  daqCardProcess _daqCardProcess;

private:
  // 串口名
  QString _name;

private slots:
  // 串口数据接收
  void serial_receive();
};

#endif // COMPORT_H
