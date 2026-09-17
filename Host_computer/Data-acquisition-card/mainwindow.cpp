#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  // 初始化状态
  // 串口下拉框清空
  ui->CB_serialport->clear();
  ui->CB_serialport->clearEditText();
  // 按键关闭
  this->state.PB_signal = false;
  this->state.PB_serialport = false;
  this->state.PB_adc = false;
  // 初始化信号输入和输出按键
  ui->PB_signal->setText(QString("open"));
  // 初始化串口按键
  ui->PB_serialport->setText(QString("open serial port"));
  // 初始化adc采集按键
  ui->PB_adc->setText(QString("open ADC"));
  // 初始化ADC显示

  ui->LB_ADC1_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");
  ui->LB_ADC2_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");
  ui->LB_ADC3_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");
  ui->LB_ADC4_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");
  ui->LB_ADC5_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");
  ui->LB_ADC6_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");
  ui->LB_ADC7_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");
  ui->LB_ADC8_DIS->setText(QString::number(0, 'f', this->adcAccuracy) + " v");


  // 初始化串口指针
  this->_comport = new comPort();
  
  //连接信号和槽
  connect(&this->_comport->_daqCardProcess, SIGNAL(this->_comport->_daqCardProcess.dacRTVal), this, SLOT(this->DACReadRTdata));
}

MainWindow::~MainWindow()
{
  delete ui;
}

// 信号输入输出按键按下->信号输出或者关闭
void MainWindow::on_PB_signal_clicked()
{
  if (this->state.PB_signal == false)
  {
    // 设置状态为打开
    this->state.PB_signal = true;
    ui->PB_signal->setText(QString("close"));
  }
  else
  {
    // 设置状态为关闭
    this->state.PB_signal = false;
    ui->PB_signal->setText(QString("open"));
  }
}

// 搜索串口
void MainWindow::on_PB_serialport_search_clicked()
{
  // 串口列表
  QStringList serialportList;
  // 遍历输出可用串口
  qDebug() << "search available serial ports:";
  for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
  {
    serialportList << info.portName();
    qDebug() << info.portName();
  }
  // 清空下拉框
  ui->CB_serialport->clear();
  ui->CB_serialport->clearEditText();
  // 输出可用串口到下拉框
  ui->CB_serialport->addItems(serialportList);
}

// 串口开关
void MainWindow::on_PB_serialport_clicked()
{
  if (this->state.PB_serialport == false)
  {
    // 获取当前预开启串口名
    QString serialPortName = ui->CB_serialport->currentText();
    //设置串口名
    this->_comport->setName(serialPortName);
    
    // 开启串口
    if (this->_comport->open())
    {
      // 开启成功
      qDebug() << "serial port " << ui->CB_serialport->currentText() << " open";
      this->state.PB_serialport = true;
      ui->PB_serialport->setText(QString("close serial port"));
      return;
    }
  }
  else
  {
    // 关闭串口
    // 释放串口对象，析构函数内部自带关闭串口
    this->_comport->close();
    qDebug() << "serial port " << ui->CB_serialport->currentText() << " close";
    this->state.PB_serialport = false;
    ui->PB_serialport->setText(QString("open serial port"));
  }
}



void MainWindow::DACReadRTdata(std::array<int32_t, 8> rtdata){
  // 遍历读取
  ui->LB_ADC1_DIS->setText(QString::number(rtdata[0], 'f', this->adcAccuracy) + " v");
  ui->LB_ADC2_DIS->setText(QString::number(rtdata[1], 'f', this->adcAccuracy) + " v");
  ui->LB_ADC3_DIS->setText(QString::number(rtdata[2], 'f', this->adcAccuracy) + " v");
  ui->LB_ADC4_DIS->setText(QString::number(rtdata[3], 'f', this->adcAccuracy) + " v");
  ui->LB_ADC5_DIS->setText(QString::number(rtdata[4], 'f', this->adcAccuracy) + " v");
  ui->LB_ADC6_DIS->setText(QString::number(rtdata[5], 'f', this->adcAccuracy) + " v");
  ui->LB_ADC7_DIS->setText(QString::number(rtdata[6], 'f', this->adcAccuracy) + " v");
  ui->LB_ADC8_DIS->setText(QString::number(rtdata[7], 'f', this->adcAccuracy) + " v");
}
//adc 采集按键
void MainWindow::on_PB_adc_clicked(){
  if (this->state.PB_adc == false){
    this->state.PB_adc = true;
    ui->PB_adc->setText(QString("close ADC"));
    
    std::array<bool, 8> chEna;
    //读取ADC使能情况
    chEna[0] = ui->ChB_ADC1->isChecked();
    chEna[1] = ui->ChB_ADC2->isChecked();
    chEna[2] = ui->ChB_ADC3->isChecked();
    chEna[3] = ui->ChB_ADC4->isChecked();
    chEna[4] = ui->ChB_ADC5->isChecked();
    chEna[5] = ui->ChB_ADC6->isChecked();
    chEna[6] = ui->ChB_ADC7->isChecked();
    chEna[7] = ui->ChB_ADC8->isChecked();

    //采样率
    int32_t sampleRate = 1000;
    this->_comport->startRecord(chEna, sampleRate);
  }
  else{
    this->state.PB_adc = false;
    ui->PB_adc->setText(QString("open ADC"));
  }
}

