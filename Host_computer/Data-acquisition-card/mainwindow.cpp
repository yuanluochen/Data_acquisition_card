#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化状态
    //串口下拉框清空
    ui->CB_serialport->clear();
    ui->CB_serialport->clearEditText();
    // 按键关闭
    this->state.PB_signal = false;
    this->state.PB_serialport = false;
    //初始化信号输入和输出按键
    ui->PB_signal->setText(QString("open"));
    //初始化串口按键
    ui->PB_serialport->setText(QString("open serial port"));

    //初始化指针
    this->_comport = nullptr;

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 信号输入输出按键按下->信号输出或者关闭
void MainWindow::on_PB_signal_clicked()
{
    if (this->state.PB_signal == false){
        //设置状态为打开
        this->state.PB_signal = true;
        ui->PB_signal->setText(QString("close"));
    }
    else{
        //设置状态为关闭
        this->state.PB_signal = false;
        ui->PB_signal->setText(QString("open"));
    }
}


//搜索串口
void MainWindow::on_PB_serialport_search_clicked()
{
    //串口列表
    QStringList serialportList;
    //遍历输出可用串口
    qDebug() << "search available serial ports:";
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()){
        serialportList << info.portName();
        qDebug() << info.portName();
    }
    //清空下拉框
    ui->CB_serialport->clear();
    ui->CB_serialport->clearEditText();
    //输出可用串口到下拉框
    ui->CB_serialport->addItems(serialportList);
}

//串口开关
void MainWindow::on_PB_serialport_clicked()
{
    if (this->state.PB_serialport == false){
        //获取当前预开启串口名
        QString serialPortName = ui->CB_serialport->currentText();
        //实例化串口对象
        if (this->_comport != nullptr){
            //释放对象
            delete this->_comport;
        }
        this->_comport = new comPort(serialPortName);
        //开启串口
        if (this->_comport->open()){
            //开启成功
            qDebug() << "serial port " << ui->CB_serialport->currentText() << " open";
            this->state.PB_serialport = true;
            ui->PB_serialport->setText(QString("close serial port"));
            return;
        }
    }
    else{
        //关闭串口
        //释放串口对象，析构函数内部自带关闭串口
        delete this->_comport;
        this->_comport = nullptr;
        qDebug() << "serial port " << ui->CB_serialport->currentText() << " close";
        this->state.PB_serialport = false;
        ui->PB_serialport->setText(QString("open serial port"));
    }
}

