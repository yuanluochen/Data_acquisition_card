#include "ddsdac.h"
#include "ui_ddsdac.h"
#include "mainwindow.h"

ddsDac::ddsDac(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ddsDac)
{
    ui->setupUi(this);
}

ddsDac::~ddsDac()
{
    delete ui;
}



void ddsDac::ddsDac_rxMsgProcess(quint8 *rxData)
{
    msgHead *_pRxHead = (msgHead *)rxData;

    if (_pRxHead->cmdId == (byte)_cmdId_ddsDacGetParam)
    {
        msgDdsDacParam *_prxData = (msgDdsDacParam *)rxData;
        if (_prxData->ch == 1)
        {
            double dacVolt = (double)(SWAP16(_prxData->volt) / 1000.0);
            double dacBias = (double)(SWAP16(_prxData->bias)  / 1000.0);
            ui->setAdcSamplingRate->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));
            ui->dacFreq1->setText(QString::number(SWAP16(_prxData->freq)));
            ui->dacVolt1->setText(QString::number(dacVolt,'f', 3));
            ui->dacDuty1->setText(QString::number(SWAP16(_prxData->duty)));
            ui->dacBias1->setText(QString::number(dacBias,'f', 3));
            ui->ddsGain1->setText(QString::number(SWAP16(_prxData->gain)));
        }
        else if (_prxData->ch == 2)
        {
            double dacVolt = (double)(SWAP16(_prxData->volt) / 1000.0);
            double dacBias = (double)(SWAP16(_prxData->bias)  / 1000.0);
            ui->setAdcSamplingRate->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));
            ui->dacFreq2->setText(QString::number(SWAP16(_prxData->freq)));
            ui->dacVolt2->setText(QString::number(dacVolt,'f', 3));
            ui->dacDuty2->setText(QString::number(SWAP16(_prxData->duty)));
            ui->dacBias2->setText(QString::number(dacBias,'f', 3));
            ui->ddsGain2->setText(QString::number(SWAP16(_prxData->gain)));
        }
        else if (_prxData->ch == 3)
        {
            double dacVolt = (double)(SWAP16(_prxData->volt) / 1000.0);
            double dacBias = (double)(SWAP16(_prxData->bias)  / 1000.0);
            ui->setAdcSamplingRate->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));
            ui->dacFreq3->setText(QString::number(SWAP16(_prxData->freq)));
            ui->dacVolt3->setText(QString::number(dacVolt,'f', 3));
            ui->dacDuty3->setText(QString::number(SWAP16(_prxData->duty)));
            ui->dacBias3->setText(QString::number(dacBias,'f', 3));
            ui->ddsGain3->setText(QString::number(SWAP16(_prxData->gain)));
        }
        else if (_prxData->ch == 4)
        {
            double dacVolt = (double)(SWAP16(_prxData->volt) / 1000.0);
            double dacBias = (double)(SWAP16(_prxData->bias)  / 1000.0);
            ui->setAdcSamplingRate->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));
            ui->dacFreq4->setText(QString::number(SWAP16(_prxData->freq)));
            ui->dacVolt4->setText(QString::number(dacVolt,'f', 3));
            ui->dacDuty4->setText(QString::number(SWAP16(_prxData->duty)));
            ui->dacBias4->setText(QString::number(dacBias,'f', 3));
            ui->ddsGain4->setText(QString::number(SWAP16(_prxData->gain)));
        }
    }
    else if (_pRxHead->cmdId == (byte)_cmdId_ddsDacGetCalibParam)
    {
        msgGetDacCalibParam *_prxData = (msgGetDacCalibParam *)rxData;

        ui->ckb_enA1->setChecked(_prxData->_dacCalibDatasPointA[0].calibEnable == 1);
        ui->ckb_enA2->setChecked(_prxData->_dacCalibDatasPointA[1].calibEnable == 1);
        ui->ckb_enA3->setChecked(_prxData->_dacCalibDatasPointA[2].calibEnable == 1);
        ui->ckb_enA4->setChecked(_prxData->_dacCalibDatasPointA[3].calibEnable == 1);

        ui->ckb_enB1->setChecked(_prxData->_dacCalibDatasPointB[0].calibEnable == 1);
        ui->ckb_enB2->setChecked(_prxData->_dacCalibDatasPointB[1].calibEnable == 1);
        ui->ckb_enB3->setChecked(_prxData->_dacCalibDatasPointB[2].calibEnable == 1);
        ui->ckb_enB4->setChecked(_prxData->_dacCalibDatasPointB[3].calibEnable == 1);

        ui->calibDigitalA1->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[0].calibDigital)));
        ui->calibDigitalA2->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[1].calibDigital)));
        ui->calibDigitalA3->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[2].calibDigital)));
        ui->calibDigitalA4->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[3].calibDigital)));
        ui->calibDigitalB1->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[0].calibDigital)));
        ui->calibDigitalB2->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[1].calibDigital)));
        ui->calibDigitalB3->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[2].calibDigital)));
        ui->calibDigitalB4->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[3].calibDigital)));

        ui->calibAnaloigA1->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[0].calibAnalog)* 0.001,'f',3));
        ui->calibAnaloigA2->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[1].calibAnalog)* 0.001,'f',3));
        ui->calibAnaloigA3->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[2].calibAnalog)* 0.001,'f',3));
        ui->calibAnaloigA4->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointA[3].calibAnalog)* 0.001,'f',3));

        ui->calibAnaloigB1->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[0].calibAnalog)* 0.001,'f',3));
        ui->calibAnaloigB2->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[0].calibAnalog)* 0.001,'f',3));
        ui->calibAnaloigB3->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[0].calibAnalog)* 0.001,'f',3));
        ui->calibAnaloigB4->setText(QString::number(SWAP16(_prxData->_dacCalibDatasPointB[0].calibAnalog)* 0.001,'f',3));
    }
}

static quint8 MSG_TX_BUF[2000];

void ddsDac::func_setDdsDacParams(quint8 cmd, quint8 ch, quint16 freq, quint16 volt, quint16 duty, quint16 bias, quint16 gain)
{
    msgDdsDacParam* _pTx = (msgDdsDacParam*)MSG_TX_BUF;

    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->cmdId = cmd;
    _pTx->frameLen = SWAP16(sizeof(msgDdsDacParam));
    _pTx->ch = ch;
    _pTx->adcSamplingRate = SWAP16(ui->setAdcSamplingRate->text().toUInt());
    _pTx->freq = SWAP16(freq);
    _pTx->volt = SWAP16(volt);
    _pTx->duty = SWAP16(duty);
    _pTx->bias = SWAP16(bias);
    _pTx->gain = SWAP16(gain);

    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_ddsDacNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_ddsDacUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));

}

void ddsDac::usbSendCmdUByteParam(quint8 cmd, quint8 ch, quint8 data)
{
    msgUbyte* _pTx = (msgUbyte*)MSG_TX_BUF;

    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->cmdId = cmd;
    _pTx->frameLen = SWAP16(sizeof(msgUbyte));

    _pTx->ch = ch;
    _pTx->data = data;

    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_ddsDacNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_ddsDacUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}

void ddsDac::usbSendCmdUWordParam(quint8 cmd, quint8 ch, quint8 data)
{
    msgUWord* _pTx = (msgUWord*)MSG_TX_BUF;

    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->cmdId = cmd;
    _pTx->frameLen = SWAP16(sizeof(msgUWord));

    _pTx->ch = ch;
    _pTx->data = data;

    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_ddsDacNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_ddsDacUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}

void ddsDac:: clearSelectMode(quint8 ch)
{
    if (ch == 1)
    {
        ui->ckb_stop1->setChecked(false);
        ui->ckb_dc1->setChecked(false);
        ui->ckb_sin1->setChecked(false);
        ui->ckb_triangle1->setChecked(false);
        ui->ckb_square1->setChecked(false);
        ui->ckb_dds1->setChecked(false);
    }
    else if (ch == 2)
    {
        ui->ckb_stop2->setChecked(false);
        ui->ckb_dc2->setChecked(false);
        ui->ckb_sin2->setChecked(false);
        ui->ckb_triangle2->setChecked(false);
        ui->ckb_square2->setChecked(false);
        ui->ckb_dds2->setChecked(false);
    }
    else if (ch == 3)
    {
        ui->ckb_stop3->setChecked(false);
        ui->ckb_dc3->setChecked(false);
        ui->ckb_sin3->setChecked(false);
        ui->ckb_triangle3->setChecked(false);
        ui->ckb_square3->setChecked(false);
        ui->ckb_dds3->setChecked(false);
    }
    else if (ch == 4)
    {
        ui->ckb_stop4->setChecked(false);
        ui->ckb_dc4->setChecked(false);
        ui->ckb_sin4->setChecked(false);
        ui->ckb_triangle4->setChecked(false);
        ui->ckb_square4->setChecked(false);
        ui->ckb_dds4->setChecked(false);
    }
}


void ddsDac::on_ckb_dc1_clicked()
{
    clearSelectMode(1);

    ui->ckb_dc1->setChecked(true);

    ui->dacVolt1->setEnabled(true);
    ui->dacFreq1->setEnabled(false);
    ui->dacBias1->setEnabled(false);
    ui->dacDuty1->setEnabled(false);
    ui->ddsGain1->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 1,
        _ddsDacWorkMode_Dc);
}
void ddsDac::on_ckb_dc2_clicked()
{
    clearSelectMode(2);

    ui->ckb_dc2->setChecked(true);

    ui->dacVolt2->setEnabled(true);
    ui->dacFreq2->setEnabled(false);
    ui->dacBias2->setEnabled(false);
    ui->dacDuty2->setEnabled(false);
    ui->ddsGain2->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 2,
        _ddsDacWorkMode_Dc);}

void ddsDac::on_ckb_dc3_clicked()
{
    clearSelectMode(3);

    ui->ckb_dc3->setChecked(true);

    ui->dacVolt3->setEnabled(true);
    ui->dacFreq3->setEnabled(false);
    ui->dacBias3->setEnabled(false);
    ui->dacDuty3->setEnabled(false);
    ui->ddsGain3->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 3,
        _ddsDacWorkMode_Dc);}

void ddsDac::on_ckb_dc4_clicked()
{
    clearSelectMode(4);

    ui->ckb_dc4->setChecked(true);

    ui->dacVolt4->setEnabled(true);
    ui->dacFreq4->setEnabled(false);
    ui->dacBias4->setEnabled(false);
    ui->dacDuty4->setEnabled(false);
    ui->ddsGain4->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 4,
        _ddsDacWorkMode_Dc);
}

void ddsDac::on_ckb_sin1_clicked()
{
    clearSelectMode(1);

    ui->ckb_sin1->setChecked(true);

    ui->dacVolt1->setEnabled(true);
    ui->dacFreq1->setEnabled(true);
    ui->dacBias1->setEnabled(true);
    ui->dacDuty1->setEnabled(false);
    ui->ddsGain1->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 1,
        _ddsDacWorkMode_Sin);
}



void ddsDac::on_ckb_sin2_clicked()
{
    clearSelectMode(2);

    ui->ckb_sin2->setChecked(true);

    ui->dacVolt2->setEnabled(true);
    ui->dacFreq2->setEnabled(true);
    ui->dacBias2->setEnabled(true);
    ui->dacDuty2->setEnabled(false);
    ui->ddsGain2->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 2,
        _ddsDacWorkMode_Sin);
}

void ddsDac::on_ckb_sin3_clicked()
{
    clearSelectMode(3);

    ui->ckb_sin3->setChecked(true);

    ui->dacVolt3->setEnabled(true);
    ui->dacFreq3->setEnabled(true);
    ui->dacBias3->setEnabled(true);
    ui->dacDuty3->setEnabled(false);
    ui->ddsGain3->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 3,
        _ddsDacWorkMode_Sin);
}

void ddsDac::on_ckb_sin4_clicked()
{
    clearSelectMode(4);

    ui->ckb_sin4->setChecked(true);

    ui->dacVolt4->setEnabled(true);
    ui->dacFreq4->setEnabled(true);
    ui->dacBias4->setEnabled(true);
    ui->dacDuty4->setEnabled(false);
    ui->ddsGain4->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 4,
        _ddsDacWorkMode_Sin);
}

void ddsDac::on_ckb_triangle1_clicked()
{
    clearSelectMode(1);

    ui->ckb_triangle1->setChecked(true);

    ui->dacVolt1->setEnabled(true);
    ui->dacFreq1->setEnabled(true);
    ui->dacBias1->setEnabled(true);
    ui->dacDuty1->setEnabled(false);
    ui->ddsGain1->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 1,
        _ddsDacWorkMode_Triangle);
}

void ddsDac::on_ckb_triangle2_clicked()
{
    clearSelectMode(2);

    ui->ckb_triangle2->setChecked(true);

    ui->dacVolt2->setEnabled(true);
    ui->dacFreq2->setEnabled(true);
    ui->dacBias2->setEnabled(true);
    ui->dacDuty2->setEnabled(false);
    ui->ddsGain2->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 2,
        _ddsDacWorkMode_Triangle);
}

void ddsDac::on_ckb_triangle3_clicked()
{
    clearSelectMode(3);

    ui->ckb_triangle3->setChecked(true);

    ui->dacVolt3->setEnabled(true);
    ui->dacFreq3->setEnabled(true);
    ui->dacBias3->setEnabled(true);
    ui->dacDuty3->setEnabled(false);
    ui->ddsGain3->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 3,
        _ddsDacWorkMode_Triangle);
}

void ddsDac::on_ckb_triangle4_clicked()
{
    clearSelectMode(4);

    ui->ckb_triangle4->setChecked(true);

    ui->dacVolt4->setEnabled(true);
    ui->dacFreq4->setEnabled(true);
    ui->dacBias4->setEnabled(true);
    ui->dacDuty4->setEnabled(false);
    ui->ddsGain4->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 4,
        _ddsDacWorkMode_Triangle);
}

void ddsDac::on_ckb_square1_clicked()
{
    clearSelectMode(1);

    ui->ckb_square1->setChecked(true);
    ui->dacVolt1->setEnabled(true);
    ui->dacFreq1->setEnabled(true);
    ui->dacBias1->setEnabled(true);
    ui->dacDuty1->setEnabled(true);
    ui->ddsGain1->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 1,
        _ddsDacWorkMode_Square);
}

void ddsDac::on_ckb_square2_clicked()
{
    clearSelectMode(2);

    ui->ckb_square2->setChecked(true);
    ui->dacVolt2->setEnabled(true);
    ui->dacFreq2->setEnabled(true);
    ui->dacBias2->setEnabled(true);
    ui->dacDuty2->setEnabled(true);
    ui->ddsGain2->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 2,
        _ddsDacWorkMode_Square);
}

void ddsDac::on_ckb_square3_clicked()
{
    clearSelectMode(3);

    ui->ckb_square3->setChecked(true);
    ui->dacVolt3->setEnabled(true);
    ui->dacFreq3->setEnabled(true);
    ui->dacBias3->setEnabled(true);
    ui->dacDuty3->setEnabled(true);
    ui->ddsGain3->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 3,
        _ddsDacWorkMode_Square);
}

void ddsDac::on_ckb_square4_clicked()
{
    clearSelectMode(4);

    ui->ckb_square4->setChecked(true);
    ui->dacVolt4->setEnabled(true);
    ui->dacFreq4->setEnabled(true);
    ui->dacBias4->setEnabled(true);
    ui->dacDuty4->setEnabled(true);
    ui->ddsGain4->setEnabled(false);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 4,
        _ddsDacWorkMode_Square);
}

void ddsDac::on_ckb_dds1_clicked()
{
    clearSelectMode(1);

    ui->ckb_dds1->setChecked(true);
    ui->dacVolt1->setEnabled(false);
    ui->dacFreq1->setEnabled(false);
    ui->dacBias1->setEnabled(true);
    ui->dacDuty1->setEnabled(false);
    ui->ddsGain1->setEnabled(true);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 1,
        _ddsDacWorkMode_Dds);
}

void ddsDac::on_ckb_dds2_clicked()
{
    clearSelectMode(2);

    ui->ckb_dds2->setChecked(true);
    ui->dacVolt2->setEnabled(false);
    ui->dacFreq2->setEnabled(false);
    ui->dacBias2->setEnabled(true);
    ui->dacDuty2->setEnabled(false);
    ui->ddsGain2->setEnabled(true);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 2,
        _ddsDacWorkMode_Dds);
}

void ddsDac::on_ckb_dds3_clicked()
{
    clearSelectMode(3);

    ui->ckb_dds3->setChecked(true);
    ui->dacVolt3->setEnabled(false);
    ui->dacFreq3->setEnabled(false);
    ui->dacBias3->setEnabled(true);
    ui->dacDuty3->setEnabled(false);
    ui->ddsGain3->setEnabled(true);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 3,
        _ddsDacWorkMode_Dds);
}

void ddsDac::on_ckb_dds4_clicked()
{
    clearSelectMode(4);

    ui->ckb_dds4->setChecked(true);
    ui->dacVolt4->setEnabled(false);
    ui->dacFreq4->setEnabled(false);
    ui->dacBias4->setEnabled(true);
    ui->dacDuty4->setEnabled(false);
    ui->ddsGain4->setEnabled(true);

    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 4,
        _ddsDacWorkMode_Dds);
}

void ddsDac::on_ckb_stop1_clicked()
{
    clearSelectMode(1);
    ui->ckb_stop1->setChecked(true);
    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 1,
        _ddsDacWorkMode_Stop);
}

void ddsDac::on_ckb_stop2_clicked()
{
    clearSelectMode(2);
    ui->ckb_stop2->setChecked(true);
    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 2,
        _ddsDacWorkMode_Stop);
}

void ddsDac::on_ckb_stop3_clicked()
{
    clearSelectMode(3);
    ui->ckb_stop3->setChecked(true);
    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 3,
        _ddsDacWorkMode_Stop);
}

void ddsDac::on_ckb_stop4_clicked()
{
    clearSelectMode(4);
    ui->ckb_stop4->setChecked(true);
    usbSendCmdUByteParam(_cmdId_setDdsDacWorkMode, 4,
        _ddsDacWorkMode_Stop);
}

void ddsDac::on_pushButton_13_clicked()
{
    if (ui->calibAnaloigA1->text().isEmpty()) { return; }
    double voltF = ui->calibAnaloigA1->text().toDouble();
    if (voltF > 65.535) { voltF = 65.535; }
    quint16 volt = (quint16)(voltF * 1000);
    usbSendCmdUWordParam((quint8)(_cmdId_ddsDacCalibPoint1), 1, volt);
}


void ddsDac::on_pushButton_11_clicked()
{
    if (ui->calibAnaloigA2->text().isEmpty()) { return; }
    double voltF = ui->calibAnaloigA2->text().toDouble();
    if (voltF > 65.535) { voltF = 65.535; }
    quint16 volt = (quint16)(voltF * 1000);
    usbSendCmdUWordParam((quint8)(_cmdId_ddsDacCalibPoint1), 2, volt);
}


void ddsDac::on_pushButton_12_clicked()
{
    if (ui->calibAnaloigA3->text().isEmpty()) { return; }
    double voltF = ui->calibAnaloigA3->text().toDouble();
    if (voltF > 65.535) { voltF = 65.535; }
    quint16 volt = (quint16)(voltF * 1000);
    usbSendCmdUWordParam((quint8)(_cmdId_ddsDacCalibPoint1), 3, volt);
}


void ddsDac::on_pushButton_10_clicked()
{
    if (ui->calibAnaloigA4->text().isEmpty()) { return; }
    double voltF = ui->calibAnaloigA4->text().toDouble();
    if (voltF > 65.535) { voltF = 65.535; }
    quint16 volt = (quint16)(voltF * 1000);
    usbSendCmdUWordParam((quint8)(_cmdId_ddsDacCalibPoint1), 4, volt);
}

void ddsDac::on_pushButton_2_clicked()
{
    if (ui->dacFreq1->text().isEmpty()) { return; }
    if (ui->dacVolt1->text().isEmpty()) { return; }
    if (ui->dacDuty1->text().isEmpty()) { return; }
    if (ui->dacBias1->text().isEmpty()) { return; }
    if (ui->ddsGain1->text().isEmpty()) { return; }

    quint16 dacFreq = ui->dacFreq1->text().toUInt();
    double t1 = ui->dacVolt1->text().toDouble();
    quint16 dacDuty = ui->dacDuty1->text().toUInt();
    double t2 = ui->dacBias1->text().toDouble();
    quint16 dacGain = ui->ddsGain1->text().toUInt();

    quint16 dacVolt = (quint16)(t1 * 1000 );
    quint16 dacBias = (quint16)(t2 * 1000 );

    func_setDdsDacParams(_cmdId_setDdsDacParam, 1, dacFreq, dacVolt, dacDuty, dacBias, dacGain);
}

void ddsDac::on_pushButton_3_clicked()
{
    if (ui->dacFreq2->text().isEmpty()) { return; }
    if (ui->dacVolt2->text().isEmpty()) { return; }
    if (ui->dacDuty2->text().isEmpty()) { return; }
    if (ui->dacBias2->text().isEmpty()) { return; }
    if (ui->ddsGain2->text().isEmpty()) { return; }

    quint16 dacFreq = ui->dacFreq2->text().toUInt();
    double t1 = ui->dacVolt2->text().toDouble();
    quint16 dacDuty = ui->dacDuty2->text().toUInt();
    double t2 = ui->dacBias2->text().toDouble();
    quint16 dacGain = ui->ddsGain2->text().toUInt();

    quint16 dacVolt = (quint16)(t1 * 1000 );
    quint16 dacBias = (quint16)(t2 * 1000 );

    func_setDdsDacParams(_cmdId_setDdsDacParam, 2, dacFreq, dacVolt, dacDuty, dacBias, dacGain);
}


void ddsDac::on_pushButton_4_clicked()
{
    if (ui->dacFreq3->text().isEmpty()) { return; }
    if (ui->dacVolt3->text().isEmpty()) { return; }
    if (ui->dacDuty3->text().isEmpty()) { return; }
    if (ui->dacBias3->text().isEmpty()) { return; }
    if (ui->ddsGain3->text().isEmpty()) { return; }

    quint16 dacFreq = ui->dacFreq3->text().toUInt();
    double t1 = ui->dacVolt3->text().toDouble();
    quint16 dacDuty = ui->dacDuty3->text().toUInt();
    double t2 = ui->dacBias3->text().toDouble();
    quint16 dacGain = ui->ddsGain3->text().toUInt();

    quint16 dacVolt = (quint16)(t1 * 1000 );
    quint16 dacBias = (quint16)(t2 * 1000 );

    func_setDdsDacParams(_cmdId_setDdsDacParam, 3, dacFreq, dacVolt, dacDuty, dacBias, dacGain);
}


void ddsDac::on_pushButton_5_clicked()
{
    if (ui->dacFreq4->text().isEmpty()) { return; }
    if (ui->dacVolt4->text().isEmpty()) { return; }
    if (ui->dacDuty4->text().isEmpty()) { return; }
    if (ui->dacBias4->text().isEmpty()) { return; }
    if (ui->ddsGain4->text().isEmpty()) { return; }

    quint16 dacFreq = ui->dacFreq4->text().toUInt();
    double t1 = ui->dacVolt4->text().toDouble();
    quint16 dacDuty = ui->dacDuty4->text().toUInt();
    double t2 = ui->dacBias4->text().toDouble();
    quint16 dacGain = ui->ddsGain4->text().toUInt();

    quint16 dacVolt = (quint16)(t1 * 1000 );
    quint16 dacBias = (quint16)(t2 * 1000 );

    func_setDdsDacParams(_cmdId_setDdsDacParam, 4, dacFreq, dacVolt, dacDuty, dacBias, dacGain);
}

