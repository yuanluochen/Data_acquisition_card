#ifndef DDSDAC_H
#define DDSDAC_H

#include <QWidget>
using byte = uint8_t;
namespace Ui {
class ddsDac;
}

class ddsDac : public QWidget
{
    Q_OBJECT

public:
    explicit ddsDac(QWidget *parent = nullptr);
    ~ddsDac();

private:
    Ui::ddsDac *ui;

public:
    void ddsDac_rxMsgProcess(quint8 *rxData);
    void func_setDdsDacParams(quint8 cmd, quint8 ch, quint16 freq, quint16 volt, quint16 duty, quint16 bias, quint16 gain);
    void  clearSelectMode(quint8 ch);
    void usbSendCmdUByteParam(quint8 cmd, quint8 ch, quint8 data);
    void usbSendCmdUWordParam(quint8 cmd, quint8 ch, quint8 data);


signals:    //向外传递信号
    void sig_ddsDacNetSend(quint8 *txData,quint32 len);
    void sig_ddsDacUsbSend(quint8 *txData,quint32 len);

private slots:
    void on_pushButton_2_clicked();
    void on_ckb_dc1_clicked();
    void on_ckb_sin1_clicked();
    void on_ckb_dc2_clicked();
    void on_ckb_dc3_clicked();
    void on_ckb_dc4_clicked();
    void on_ckb_sin2_clicked();
    void on_ckb_sin3_clicked();
    void on_ckb_sin4_clicked();
    void on_ckb_triangle1_clicked();
    void on_ckb_triangle2_clicked();
    void on_ckb_triangle3_clicked();
    void on_ckb_triangle4_clicked();
    void on_ckb_square1_clicked();
    void on_ckb_square2_clicked();
    void on_ckb_square3_clicked();
    void on_ckb_square4_clicked();
    void on_ckb_dds1_clicked();
    void on_ckb_dds2_clicked();
    void on_ckb_dds3_clicked();
    void on_ckb_dds4_clicked();
    void on_ckb_stop1_clicked();
    void on_ckb_stop2_clicked();
    void on_ckb_stop3_clicked();
    void on_ckb_stop4_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // DDSDAC_H
