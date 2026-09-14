#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);//去掉最大化选项
    //注册SerialSettings,以便在信号槽中作为参数使用
    qRegisterMetaType<zlosUartPort::uartSettings>("zlosUartPort::uartSettings");
    qRegisterMetaType<zlosNetPort::netPortSettings>("zlosNetPort::netPortSettings");

    InitUI();
    InitSerialPort();
    initTcpClient();
    widgetCommucationInit();

    qDebug() <<"mainThread: "<< QThread::currentThreadId();
}

//串口任务初始化
void MainWindow::InitSerialPort()
{
    zl_uartPort.moveToThread(&uart_thread);   //将任务放在线程中执行
    uart_thread.start();       //启动线程

    //连接响应的信号与槽，Main函数发送给SerialPort，界面主动发送的信号
    connect(this, &MainWindow::sigUartStart, &zl_uartPort, &zlosUartPort::uartStart);
    connect(this, &MainWindow::sigUartStop, &zl_uartPort, &zlosUartPort::uartStop);
    connect(this, &MainWindow::sigUartSend, &zl_uartPort, &zlosUartPort::uartSend);

    connect(&zl_uartPort,&zlosUartPort::sigUartStarted,this,&MainWindow::started);
    connect(&zl_uartPort,&zlosUartPort::sigUartStopped,this,&MainWindow::stoped);
    connect(&zl_uartPort,&zlosUartPort::sigUartReceived,this,&MainWindow::uartReceived);
}

void MainWindow::started()
{

    ui->openButton->setText(QStringLiteral("关闭串口"));
    ui->groupBox->setEnabled(false);

}

void MainWindow::stoped(int status)
{
    if(status)
    {
        //待补充
    }
    ui->openButton->setText(QStringLiteral("打开串口"));
    ui->groupBox->setEnabled(true);
}

void MainWindow::InitUI()
{
    //端口名称预置
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portName->addItem(serial.portName());
            serial.close();
        }
    }
}

void MainWindow::initTcpClient()
{
    zl_netPort.moveToThread(&net_thread);   //将任务放在线程中执行
    net_thread.start();       //启动线程

    //连接响应的信号与槽Main函数发送给netPort
    connect(this, &MainWindow::sigNetConnect, &zl_netPort, &zlosNetPort::netConnect);
    connect(this, &MainWindow::sigNetSend, &zl_netPort, &zlosNetPort::netSend);

    connect(&zl_netPort,&zlosNetPort::sigConnectFlag,this,&MainWindow::netConnectState);
    connect(&zl_netPort,&zlosNetPort::sigNetReceived,this,&MainWindow::netReceive);

    connect(&msgRxTimer, &QTimer::timeout, this, &MainWindow::processUsbMsg);
    connect(&msgRxTimer, &QTimer::timeout, this, &MainWindow::processNetMsg);
    msgRxTimer.start(50);

}

void MainWindow::netSend(quint8* txData,quint32 len)
{

    if(ui->netConnectBtn->text() == "断开")
    {
        if (ui->ckb_net->isChecked())
        {
             emit sigNetSend(txData,len);
        }
    }
}


void MainWindow::widgetCommucationInit()
{
    if(_adcWave == nullptr)
    {
        _adcWave = new adcWave(this);
        ui->stackedWidget->addWidget(_adcWave);
        connect(_adcWave,&adcWave::sig_adcWaveUsbSend, this, &MainWindow::usbSend);
        connect(_adcWave,&adcWave::sig_adcWaveNetSend, this, &MainWindow::netSend);
        connect(this, &MainWindow::_rxValidMsg,_adcWave,&adcWave::adcWave_rxMsgProcess);
    }

    if(_adcRecord == nullptr)
    {
        _adcRecord = new adcRecord(this);
        ui->stackedWidget->addWidget(_adcRecord);
        connect(_adcRecord,&adcRecord::sig_adcRecordUsbSend, this, &MainWindow::usbSend);
        connect(_adcRecord,&adcRecord::sig_adcRecordNetSend, this, &MainWindow::netSend);
        connect(this, &MainWindow::_rxValidMsg,_adcRecord,&adcRecord::adcRecord_rxMsgProcess);
    }

    if(_ddsDac == nullptr)
    {
        _ddsDac = new ddsDac(this);
        ui->stackedWidget->addWidget(_ddsDac);
        connect(_ddsDac,&ddsDac::sig_ddsDacUsbSend, this, &MainWindow::usbSend);
        connect(_ddsDac,&ddsDac::sig_ddsDacNetSend, this, &MainWindow::netSend);
        connect(this, &MainWindow::_rxValidMsg,_ddsDac,&ddsDac::ddsDac_rxMsgProcess);
    }

}



void MainWindow::on_listWidget_itemSelectionChanged()
{
    QString currentItem = ui->listWidget->currentItem()->text();
    qDebug()<<currentItem;

    if(currentItem=="示波器")
    {
        ui->stackedWidget->setCurrentWidget(_adcWave);
        msgSendCmdNoParam(_cmdId_getDeviceParam);
    }
    else if(currentItem=="记录仪")
    {
        ui->stackedWidget->setCurrentWidget(_adcRecord);
        msgSendCmdNoParam(_cmdId_getDeviceParam);
    }
    else if(currentItem=="信号源")
    {
        ui->stackedWidget->setCurrentWidget(_ddsDac);
        msgSendCmdNoParam(_cmdId_ddsDacGetParamTotal);
    }
}


quint8 usbTxBuf[20000];
void MainWindow::msgSendCmdNoParam(byte cmd)
{
    /************消息数组转结构体************/

    //struct_noParam _pTx = new struct_noParam();

   msgNoParam *_pTx = (msgNoParam*)usbTxBuf;

   _pTx->msgHead = SWAP16(0x55aa);
   _pTx->cmdId = cmd;
   _pTx->frameLen = SWAP16(sizeof(msgNoParam));

   quint16 crctx = getCrc16WithTail((quint8*)usbTxBuf, SWAP16(_pTx->frameLen));
   _pTx->crc = SWAP16(crctx);
   netSend((quint8*)usbTxBuf, SWAP16(_pTx->frameLen));
   usbSend((quint8*)usbTxBuf, SWAP16(_pTx->frameLen));

}


void MainWindow::netConnectState(bool flag)
{
    if(flag==true)
    {
        ui->netConnectBtn->setText("断开");
    }
    //已连接状态 去断开
    else
    {
        ui->netConnectBtn->setText("连接");
    }
}


void MainWindow::on_netConnectBtn_clicked()
{
    QString text= ui->netConnectBtn->text();
    zlosNetPort::netPortSettings  netPortSet;
    netPortSet._ip = ui->lnEt_ip->text();
    netPortSet._port= ui->lnEt_port->text().toUShort();

    if(text ==  QStringLiteral("连接"))
    {
        //发信号在线程中打开串口
        emit sigNetConnect(netPortSet);
    }
    else
    {
        //发信号在线程中关闭串口
        emit sigNetConnect(netPortSet);
    }
    ui->ckb_usb->setChecked(false);
    ui->ckb_net->setChecked(true);


}



MainWindow::~MainWindow()
{
    delete ui;
}

//关闭任务 关闭窗口时退出线程
//窗口关闭时调用
void MainWindow::closeEvent(QCloseEvent *event)
{
    emit sigUartStop();
    uart_thread.quit();
    uart_thread.wait();

    net_thread.quit();
    net_thread.wait();

}


void MainWindow::usbSend(quint8* txData,quint32 len)
{

    if(ui->openButton->text() != "关闭串口")
    {
        return;
    }
    if (ui->ckb_usb->isChecked())
    {
       emit sigUartSend(txData,len);//发送数据
    }
}


void MainWindow::on_openButton_clicked()
{
    QString text= ui->openButton->text();
    if(text ==  QStringLiteral("打开串口"))
    {
        zlosUartPort::uartSettings  uartSet;
        uartSet._name = ui->portName->currentText();

        uartSet._baudRate =  QSerialPort::Baud9600;


        uartSet._dataBits = QSerialPort::Data8;
        uartSet._stopBits = QSerialPort::OneStop;
        uartSet._parity = QSerialPort::NoParity;
        uartSet._flowControl = QSerialPort::NoFlowControl;

        //发信号在线程中打开串口
        emit sigUartStart(uartSet);
    }
    else
    {
        //发信号在线程中关闭串口
        emit sigUartStop();
    }

    ui->ckb_usb->setChecked(true);
    ui->ckb_net->setChecked(false);

}//打开串口 open函数结束


void MainWindow::on_scanPort_clicked()
{
    int portLen = ui->portName->count();
    //删除应该从高往低删, 否则删除后长度变化会出bug
    for(int i=portLen;i>=0;i--)
    {
        ui->portName->removeItem(i);
    }

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portName->addItem(serial.portName());
            serial.close();
        }
    }

    qDebug()<<"SCAN PORT";
}


void MainWindow::on_ckb_usb_clicked()
{
    ui->ckb_usb->setChecked(true);
    ui->ckb_net->setChecked(false);
    msgSendCmdNoParam(_cmdId_setCommunicatiaonPort);
}

void MainWindow::on_ckb_net_clicked()
{
    ui->ckb_usb->setChecked(false);
    ui->ckb_net->setChecked(true);
    msgSendCmdNoParam(_cmdId_setCommunicatiaonPort);
}

QByteArray usbRxMsgBuf;
//接收函数
void MainWindow::uartReceived(QByteArray data)
{
    usbRxMsgBuf.append(data);
}

void MainWindow::processUsbMsg()
{
    //检索收到的数据开头是否为0x55aa, 如果不是则继续轮循下一步
    while (usbRxMsgBuf.length() > 5)
    {
          qDebug()<<usbRxMsgBuf.length();
        //找0x55作为包头
        bool findNewHead = false;
        quint8* usbRxBuf = (quint8*)usbRxMsgBuf.data();
        quint16 usbRxBufLength = usbRxMsgBuf.length();
        for (quint16 i = 0; i < usbRxBufLength; i++)
        {
            if (usbRxBuf[i] == 0x55 && i != (usbRxBufLength - 1))
            {
                if (usbRxBuf[i + 1] == 0xaa)
                {
                    if (i > 0 && usbRxMsgBuf.length() >= i)
                    {
                        //清除源文件数据
                        usbRxMsgBuf.remove(0, i);
                    }

                    //检索到报文开头,判断是否完成一帧
                    findNewHead = true;
                    msgHead *_pRxHead = (msgHead *)usbRxBuf;

                    if ((usbRxBufLength - i) >= SWAP16(_pRxHead->frameLen))
                    {
                        bool crcResult = checkCrc16WithTail((quint8 *)usbRxBuf, SWAP16(_pRxHead->frameLen));
                        // updateRxLog("len: " + _pRxHead.cmdId + "," + _pRxHead.frameLen + "\r\n");

                        if (crcResult != true)
                        {
                            //updateRxLog("rx net Msg crc Error: " + crcResult + "\r\n");
                            //校验失败, 说明0x55aa不是包头 或者数据被污染, 重新找包头
                            usbRxMsgBuf.remove(0, 2);
                            break;
                        }
                        //usbRxProcess(usbRxMsgBuf.ToArray());
                        emit _rxValidMsg((quint8*)usbRxMsgBuf.data());
                        if (_pRxHead->cmdId == _cmdId_getDeviceParam)
                        {
                            qDebug()<<"_cmdId_getDeviceParam";
                        }
                        usbRxMsgBuf.remove(0, SWAP16(_pRxHead->frameLen));
                        break;
                    }
                    else
                    {
                        //长度不够, 退出中断继续接收
                        return;
                    }
                }
            }
        }

        //未找到 newHead, 则清空缓存区
        if (!findNewHead)
        {
            usbRxMsgBuf.clear();
        }

    }
}

QByteArray netRxMsgBuf;
void MainWindow::netReceive(QByteArray data)
{
    netRxMsgBuf.append(data);
    qDebug()<<"uartReceived "<<data;
}



void MainWindow::processNetMsg()
{
    //检索收到的数据开头是否为0x55aa, 如果不是则继续轮循下一步
    while (netRxMsgBuf.length() > 5)
    {
        qDebug()<<netRxMsgBuf.length();
        //找0x55作为包头
        bool findNewHead = false;
        quint8* usbRxBuf = (quint8*)netRxMsgBuf.data();
        quint16 usbRxBufLength = netRxMsgBuf.length();
        for (quint16 i = 0; i < usbRxBufLength; i++)
        {
            if (usbRxBuf[i] == 0x55 && i != (usbRxBufLength - 1))
            {
                if (usbRxBuf[i + 1] == 0xaa)
                {
                    if (i > 0 && netRxMsgBuf.length() >= i)
                    {
                        //清除源文件数据
                        netRxMsgBuf.remove(0, i);
                    }

                    //检索到报文开头,判断是否完成一帧
                    findNewHead = true;
                    msgHead *_pRxHead = (msgHead *)usbRxBuf;

                    if ((usbRxBufLength - i) >= SWAP16(_pRxHead->frameLen))
                    {
                        bool crcResult = checkCrc16WithTail((quint8 *)usbRxBuf, SWAP16(_pRxHead->frameLen));
                        // updateRxLog("len: " + _pRxHead.cmdId + "," + _pRxHead.frameLen + "\r\n");

                        if (crcResult != true)
                        {
                            //updateRxLog("rx net Msg crc Error: " + crcResult + "\r\n");
                            //校验失败, 说明0x55aa不是包头 或者数据被污染, 重新找包头
                            netRxMsgBuf.remove(0, 2);
                            break;
                        }
                        //usbRxProcess(netRxMsgBuf.ToArray());
                        emit _rxValidMsg((quint8*)usbRxMsgBuf.data());
                        if (_pRxHead->cmdId == _cmdId_getDeviceParam)
                        {
                            qDebug()<<"_cmdId_getDeviceParam";
                        }
                        netRxMsgBuf.remove(0, SWAP16(_pRxHead->frameLen));
                        break;
                    }
                    else
                    {
                        //长度不够, 退出中断继续接收
                        return;
                    }
                }
            }
        }

        //未找到 newHead, 则清空缓存区
        if (!findNewHead)
        {
            netRxMsgBuf.clear();
        }

    }
}

