#ifndef ZLOS_NETPORT_H
#define ZLOS_NETPORT_H

#include <QDebug>
#include <QThread>
#include <QTcpSocket>


//这个类放在线程中创建
class zlosNetPort : public QTcpSocket
{
    //槽会自动被调用,只有加入了Q_OBJECT，你才能使用QT中的signal和slot机制。
    Q_OBJECT

public:
    zlosNetPort();

    struct netPortSettings{
        QString     _ip;          //串口名
        quint16     _port;

    };

    void netConnect(netPortSettings netPortSet);
    void netSend(quint8* txData,quint32 len);



public slots:    //将在线程中执行的函数写成槽函数


signals:    //向外传递信号
    void sigConnectFlag(bool state); //串口收到了数据
    void sigNetReceived(QByteArray data); //串口收到了数据


};



#endif // ZLOS_NETPORT_H
