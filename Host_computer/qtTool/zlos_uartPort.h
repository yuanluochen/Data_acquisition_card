#ifndef ZLOS_UARTPORT_H
#define ZLOS_UARTPORT_H

#include <QSerialPort>
#include <QDebug>
#include <QThread>

//这个类放在线程中创建
class zlosUartPort : public QSerialPort
{
    //槽会自动被调用,只有加入了Q_OBJECT，你才能使用QT中的signal和slot机制。
    Q_OBJECT

public:
    zlosUartPort();

    struct uartSettings{
        QString     _name;          //串口名
        BaudRate    _baudRate;      //波特率
        DataBits    _dataBits;      //数据位
        Parity      _parity;        //奇偶校验位
        StopBits    _stopBits;      //停止位
        FlowControl _flowControl;   //流控制
        };

public slots:    //将在线程中执行的函数写成槽函数
        void uartStart(uartSettings set);
        void uartStop();
        void uartSend(quint8* data,quint32 len);


signals:    //向外传递信号
        void sigUartStarted();                  //串口打开了
        void sigUartStopped(int status);       //串口停止了
        void sigUartReceived(QByteArray data); //串口收到了数据

};

#endif // ZLOS_UARTPORT_H
