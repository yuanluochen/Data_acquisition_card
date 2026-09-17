#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "comPort.h"
#include <array>
QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private:
  // 按键状态
  struct state{
    bool PB_signal;
    bool PB_serialport;
    bool PB_adc;
  } state;
  // 串口
  comPort *_comport;
  //adc显示精度
  int adcAccuracy = 3; 
private slots : 
  void on_PB_signal_clicked();

  void on_PB_serialport_search_clicked();

  void on_PB_serialport_clicked();

  void DACReadRTdata(std::array<int32_t, 8> rtdata);

  void on_PB_adc_clicked();

  private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
