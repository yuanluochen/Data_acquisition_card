#ifndef ADCWAVE_H
#define ADCWAVE_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class adcWave;
}

class adcWave : public QWidget
{
    Q_OBJECT

public:
    explicit adcWave(QWidget *parent = nullptr);
    ~adcWave();

private:
    Ui::adcWave *ui;



    private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_adcCheck1_clicked();

    void on_adcCheck2_clicked();

    void on_adcCheck3_clicked();

    void on_adcCheck4_clicked();

    void on_adcCheck5_clicked();

    void on_adcCheck6_clicked();

    void on_adcCheck7_clicked();

    void on_adcCheck8_clicked();

    void on_adcTrig1_clicked();

    void on_adcTrig2_clicked();

    void on_adcTrig3_clicked();

    void on_adcTrig4_clicked();

    void on_adcTrig5_clicked();

    void on_adcTrig6_clicked();

    void on_adcTrig7_clicked();

    void on_adcTrig8_clicked();

public:
    void adcWave_rxMsgProcess(quint8 *rxData);
    void adcWaveSendCmdNoParam(quint8 cmd);
    void adcWaveSendCmdUWordParam(quint8 cmd,quint16 data);
    void adcWaveSendCmdUByteParam(quint8 cmd,quint8 data);

    void waveAutoReadProcess();
    void fun_setAdcState();

    void fun_clearAdcTrig();
    QTimer waveAutoReadTimer;

signals:    //向外传递信号
    void sig_adcWaveNetSend(quint8 *txData,quint32 len);
    void sig_adcWaveUsbSend(quint8 *txData,quint32 len);





};

#endif // ADCWAVE_H
