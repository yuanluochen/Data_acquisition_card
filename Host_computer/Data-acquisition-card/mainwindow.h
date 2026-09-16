#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "comPort.h"
#include <QVector>
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
  struct state
  {
    bool PB_signal;
    bool PB_serialport;
  } state;
  // 串口
  comPort *_comport;
private slots:
  void on_PB_signal_clicked();

  void on_PB_serialport_search_clicked();

  void on_PB_serialport_clicked();

  void DACReadRTdata(QVector<int32_t> rtdata){};

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
