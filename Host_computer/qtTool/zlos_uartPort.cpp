#include "zlos_uartPort.h"

zlosUartPort::zlosUartPort()
{

    connect( this, &QSerialPort::readyRead, [this]
    {
        //qDebug() <<"zlosUartPortThread: "<< QThread::currentThreadId();
        QByteArray data = QSerialPort::readAll();
        emit sigUartReceived(data);
    });
}

//开启一个串口
void zlosUartPort::uartStart(uartSettings serialSet)
{
    QSerialPort::setPortName(serialSet._name);
    QSerialPort::setParity(serialSet._parity);
    QSerialPort::setBaudRate(serialSet._baudRate);
    QSerialPort::setDataBits(serialSet._dataBits);
    QSerialPort::setStopBits(serialSet._stopBits);
    QSerialPort::setFlowControl(serialSet._flowControl);

    //qDebug()<<"start: "<<QThread::currentThreadId();

    if(QSerialPort::open(QIODevice::ReadWrite))
    {
        emit sigUartStarted();
    }
    else
    {
        emit sigUartStopped(1);
    }
}

//停止一个串口
void zlosUartPort::uartStop()
{
    if(QSerialPort::isOpen())
    {
        QSerialPort::close();
    }

    //qDebug()<< "stop: "<<QThread::currentThreadId();

    //正常关闭传递0
    emit  sigUartStopped(0);
}

//向串口写数据
void zlosUartPort::uartSend(quint8* data,quint32 len)
{
    //qDebug()<<"send: "<<QThread::currentThread();

    if(QSerialPort::isOpen())
    {
        QSerialPort::write((char*)data,len);
    }
}






