#include "zlos_netPort.h"

zlosNetPort::zlosNetPort()
{
   // tcpClient = new QTcpSocket(this);
    connect( this, &QTcpSocket::readyRead, [this]
    {
        //qDebug() <<"zlosNetPortThread: "<< QThread::currentThreadId();
            QByteArray buffer = QTcpSocket::readAll();
            emit sigNetReceived(buffer);
    });
}

void zlosNetPort::netConnect(netPortSettings netPortSet)
{
    qDebug() << "netConnect\r\n";
    //未连接状态  去链接
    if(QTcpSocket::state() != QAbstractSocket::ConnectedState)
    {
        //连接服务器
        QTcpSocket::connectToHost(netPortSet._ip,netPortSet._port);
        //等待连接成功
        if(!QTcpSocket::waitForConnected(5000)) {
            qDebug() << "Connection failed!";
            return;
        }
    }
    //已连接状态 去断开
    else
    {
        //断开服务器
        QTcpSocket::disconnectFromHost();
    }

    if(QTcpSocket::state() == QAbstractSocket::ConnectedState)
    {
        emit sigConnectFlag(true);
    }
    else
    {
        emit sigConnectFlag(false);
    }
}

void zlosNetPort::netSend(quint8* txData,quint32 len)
{
    //qDebug()<<"send: "<<QThread::currentThread();

    if(QTcpSocket::state() == QAbstractSocket::ConnectedState)
    {
        QTcpSocket::write((char*)txData,len);
    }
}
