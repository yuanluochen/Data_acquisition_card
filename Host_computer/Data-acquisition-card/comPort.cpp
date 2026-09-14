#include "comPort.h"
#include "mainwindow.h"

bool comPort::open(){
    //判断当前串口是否打开
    if (this->isopen()){
        //已经打开关闭
        this->_serialport->clear();
        this->_serialport->close();
    }
    //设置基本参数

    //串口名
    this->_serialport->setPortName(this->_name);
    //波特率
    this->_serialport->setBaudRate(QSerialPort::Baud115200);
    //数据位
    this->_serialport->setDataBits(QSerialPort::Data8);
    //流控制
    this->_serialport->setFlowControl(QSerialPort::NoFlowControl);
    //校验位
    this->_serialport->setParity(QSerialPort::NoParity);
    //停止位
    this->_serialport->setStopBits(QSerialPort::OneStop);

    //开启串口
    if (!this->_serialport->open(QSerialPort::ReadWrite)){
        qDebug() << "open serial port " << this->_name << " is false";
        return false;
    }
    qDebug() << "open serial port " << this->_name << " is successful";
    return true;
}