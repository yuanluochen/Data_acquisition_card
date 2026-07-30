#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QThread>
#include <QMessageBox>
#include <QListWidgetItem>

#include "qcustomplot.h"

#include "crc.h"

#include "zlos_uartPort.h"
#include "zlos_netPort.h"
#include "msgStruct.h"

#include "adcwave.h"
#include "adcrecord.h"
#include "ddsdac.h"
#pragma pack(1)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //初始化界面控件的内容
    void InitUI();
    void InitSerialPort();
    void initTcpClient();

    void sendCmdParamless(quint8 cmd);
    void msgSendCmdNoParam(byte cmd);

    //窗口关闭时调用
    void closeEvent(QCloseEvent *event);
    void processUsbMsg();
    void processNetMsg();


private slots:
    void on_openButton_clicked();

    void on_scanPort_clicked();

    void on_listWidget_itemSelectionChanged();

    void widgetCommucationInit();

    void on_netConnectBtn_clicked();

    void on_ckb_usb_clicked();

    void on_ckb_net_clicked();

signals:
    void sigUartStart(zlosUartPort::uartSettings uartSet );
    void sigUartStop();
    void sigUartSend(quint8* txData,quint32 len);
    void sigUartReceive(QByteArray str);

    void sigNetConnect(zlosNetPort::netPortSettings netPortSet );
    void sigNetDisconnect();
    void sigNetSend(quint8* txData,quint32 len);
    void sigNetRxData();

    void _rxValidMsg(quint8 *rxData);


public slots:
    void started();
    void stoped(int status);
    void uartReceived(QByteArray data);
    void netConnectState(bool flag);
    void netReceive(QByteArray data);
    void usbSend(quint8* txData,quint32 len);
    void netSend(quint8* txData,quint32 len);

private:
    Ui::MainWindow *ui;

    //定义串口类的对象
    zlosUartPort zl_uartPort;   // 不是QSerial Port!!
    zlosNetPort zl_netPort;

    QThread uart_thread;
    QThread net_thread;
    QTimer msgRxTimer;

    adcWave  *_adcWave = nullptr;
    adcRecord  *_adcRecord = nullptr;
    ddsDac  *_ddsDac = nullptr;

};

#pragma pack()
#endif // MAINWINDOW_H
