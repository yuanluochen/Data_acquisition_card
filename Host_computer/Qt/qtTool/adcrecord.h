#ifndef ADCRECORD_H
#define ADCRECORD_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class adcRecord;
}

class adcRecord : public QWidget
{
    Q_OBJECT

public:
    explicit adcRecord(QWidget *parent = nullptr);
    ~adcRecord();



private slots:
    void on_pushButton_4_clicked();

    void on_adcCheck1_clicked();

    void on_adcCheck2_clicked();

    void on_adcCheck3_clicked();

    void on_adcCheck4_clicked();

    void on_adcCheck5_clicked();

    void on_adcCheck6_clicked();

    void on_adcCheck7_clicked();

    void on_adcCheck8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::adcRecord *ui;

public:
    void adcRecord_rxMsgProcess(quint8 *rxData);
    void adcRecordSendCmdNoParam(quint8 cmd);
    void adcRecordSendCmdUWordParam(quint8 cmd,quint16 data);
    void adcRecordSendCmdUByteParam(quint8 cmd,quint8 data);
    void fun_setAdcState();
    void clearAllWaves();
    quint8 fun_getAdcChStateEnable();
    void refreshWaveDataList();
    void recordAutoReadProcess();

    QTimer recordAutoReadTimer;


signals:    //向外传递信号
    void sig_adcRecordNetSend(quint8 *txData,quint32 len);
    void sig_adcRecordUsbSend(quint8 *txData,quint32 len);

};

#endif // ADCRECORD_H
