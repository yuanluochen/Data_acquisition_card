#include "adcwave.h"
#include "ui_adcwave.h"
#include "mainwindow.h"

adcWave::adcWave(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::adcWave)
{
    ui->setupUi(this);


    //系统初始化
    connect(&waveAutoReadTimer, &QTimer::timeout, this, &adcWave::waveAutoReadProcess);
    waveAutoReadTimer.start(200);

}

adcWave::~adcWave()
{
    delete ui;

}

void adcWave::waveAutoReadProcess()
{
    if(ui->autoReadCheck->isChecked())
    {
        adcWaveSendCmdNoParam(_cmdId_setAdc_waveEnable_flag);
    }
}


static QColor colorCh1 = QColor("#aa0000");
static QColor colorCh2 = QColor("#ff0000");
static QColor colorCh3 = QColor("#ff00ff");
static QColor colorCh4 = QColor("#dc9300");
static QColor colorCh5 = QColor("#00a100");
static QColor colorCh6 = QColor("#00e1e1");
static QColor colorCh7 = QColor("#0000ff");
static QColor colorCh8 = QColor("#aa00ff");

static quint8 MSG_TX_BUF[2000];

void adcWave::adcWaveSendCmdNoParam(quint8 cmd)
{
    /************消息数组转结构体************/
    msgNoParam* _pTx = (msgNoParam*)MSG_TX_BUF;
    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->frameLen = SWAP16(sizeof(msgNoParam));
    _pTx->cmdId = cmd;
    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_adcWaveNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_adcWaveUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));

}

void adcWave::adcWaveSendCmdUByteParam(quint8 cmd,quint8 data)
{
    /************消息数组转结构体************/
    msgUbyte* _pTx = (msgUbyte*)MSG_TX_BUF;
    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->frameLen = SWAP16(sizeof(msgUbyte));
    _pTx->cmdId = cmd;
    _pTx->data = data;
    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_adcWaveNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_adcWaveUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));

}

void adcWave::adcWaveSendCmdUWordParam(quint8 cmd,quint16 data)
{
    /************消息数组转结构体************/
    msgUWord* _pTx = (msgUWord*)MSG_TX_BUF;
    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->frameLen = SWAP16(sizeof(msgUWord));
    _pTx->cmdId = cmd;
    _pTx->data = SWAP16(data);
    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_adcWaveNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_adcWaveUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));

}

void adcWave::fun_clearAdcTrig()
{
    ui->adcTrig1->setChecked(false);
    ui->adcTrig2->setChecked(false);
    ui->adcTrig3->setChecked(false);
    ui->adcTrig4->setChecked(false);
    ui->adcTrig5->setChecked(false);
    ui->adcTrig6->setChecked(false);
    ui->adcTrig7->setChecked(false);
    ui->adcTrig8->setChecked(false);
}


static QVector<double> xAxisIndex;

static QVector<double> adcWave1;
static QVector<double> adcWave2;
static QVector<double> adcWave3;
static QVector<double> adcWave4;
static QVector<double> adcWave5;
static QVector<double> adcWave6;
static QVector<double> adcWave7;
static QVector<double> adcWave8;
static quint32 listAxisIndex;
static const quint32 ADC_ONCE_LEN = 4000;

void adcWave::adcWave_rxMsgProcess(quint8 *rxData)
{
    qDebug()<<"zldac_adcWave_process";

    msgHead* _pRxHead = (msgHead*)rxData;

    if (_pRxHead->cmdId == _cmdId_getDeviceParam)
    {
        msgAdcWaveState *_prxData = ( msgAdcWaveState *)rxData;

        ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
        ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
        ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
        ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
        ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
        ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
        ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
        ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);

        fun_clearAdcTrig();

        if (_prxData->trigCh == 0) { ui->adcTrig1->setChecked(true); }
        else if (_prxData->trigCh == 1) { ui->adcTrig2->setChecked(true); }
        else if (_prxData->trigCh == 2) { ui->adcTrig3->setChecked(true);  }
        else if (_prxData->trigCh == 3) { ui->adcTrig4->setChecked(true);  }
        else if (_prxData->trigCh == 4) { ui->adcTrig5->setChecked(true);  }
        else if (_prxData->trigCh == 5) { ui->adcTrig6->setChecked(true);  }
        else if (_prxData->trigCh == 6) { ui->adcTrig7->setChecked(true);  }
        else if (_prxData->trigCh == 7) { ui->adcTrig8->setChecked(true);  }

        ui->rdAdcFreq->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));
        ui->rdTrigValue->setText(QString::number(SWAP16(_prxData->adcTrigValue) * 5.0 / 32768.0 - 5.0,'f', 3));
    }
    else if (_pRxHead->cmdId == _cmdId_getAdc_waveData)
    {
        msgGetAdcDatas *_prxData = ( msgGetAdcDatas *)rxData;

        // 添加数据到图表
        //waveform.AddScatter(data);
        //根据回读信息更新adc通道选项, 并建立bool数组用来处理循环依据
        ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
        ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
        ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
        ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
        ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
        ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
        ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
        ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);

        fun_clearAdcTrig();
        if (_prxData->trigCh == 0) { ui->adcTrig1->setChecked(true); }
        else if (_prxData->trigCh == 1) { ui->adcTrig2->setChecked(true); }
        else if (_prxData->trigCh == 2) { ui->adcTrig3->setChecked(true);  }
        else if (_prxData->trigCh == 3) { ui->adcTrig4->setChecked(true);  }
        else if (_prxData->trigCh == 4) { ui->adcTrig5->setChecked(true);  }
        else if (_prxData->trigCh == 5) { ui->adcTrig6->setChecked(true);  }
        else if (_prxData->trigCh == 6) { ui->adcTrig7->setChecked(true);  }
        else if (_prxData->trigCh == 7) { ui->adcTrig8->setChecked(true);  }

        ui->rdAdcFreq->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));
        ui->rdTrigValue->setText(QString::number(SWAP16(_prxData->adcTrigValue) * 5.0 / 32768.0 - 5.0,'f', 3));

        quint16 adcEnableChNum = 0;
        quint16 adcStartChBias = 0;
        quint16 adcEnableChState[8];
        for (quint16 i = 0; i < 8; i++)
        {
            if (((_prxData->adc_ch_Enable >> i) & 0x01) == 1)
            {
                adcEnableChState[adcEnableChNum] = i;
                if (_prxData->adcStartCh == i)
                {
                    adcStartChBias = adcEnableChNum;
                }
                adcEnableChNum++;
            }
        }

        adcWave1.clear(); adcWave2.clear(); adcWave3.clear(); adcWave4.clear(); adcWave5.clear(); adcWave6.clear(); adcWave7.clear(); adcWave8.clear(); xAxisIndex.clear();

        //开始采集点不一定是通道1, 寻找初始通道, 最后采集不一定是通道数整数倍, 所以删除最后非完整采集部分
        quint16 adcDataWholeChLen = (ADC_ONCE_LEN / adcEnableChNum) * adcEnableChNum;

        double ADC_Ybias1 = 0, ADC_Ybias2 = 0, ADC_Ybias3 = 0, ADC_Ybias4 = 0, ADC_Ybias5 = 0, ADC_Ybias6 = 0, ADC_Ybias7 = 0, ADC_Ybias8 = 0;

        if (!ui->Ybias1->text().isEmpty()) { ADC_Ybias1 = ui->Ybias1->text().toDouble(); }
        if (!ui->Ybias2->text().isEmpty()) { ADC_Ybias2 = ui->Ybias2->text().toDouble(); }
        if (!ui->Ybias3->text().isEmpty()) { ADC_Ybias3 = ui->Ybias3->text().toDouble(); }
        if (!ui->Ybias4->text().isEmpty()) { ADC_Ybias4 = ui->Ybias4->text().toDouble(); }
        if (!ui->Ybias5->text().isEmpty()) { ADC_Ybias5 = ui->Ybias5->text().toDouble(); }
        if (!ui->Ybias6->text().isEmpty()) { ADC_Ybias6 = ui->Ybias6->text().toDouble(); }
        if (!ui->Ybias7->text().isEmpty()) { ADC_Ybias7 = ui->Ybias7->text().toDouble(); }
        if (!ui->Ybias8->text().isEmpty()) { ADC_Ybias8 = ui->Ybias8->text().toDouble(); }


        for (quint16 i = 0; i < adcDataWholeChLen; i++)
        {
            //最后叠加的数字为偏置
            if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 0) { adcWave1.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias1); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 1) { adcWave2.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias2); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 2) { adcWave3.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias3); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 3) { adcWave4.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias4); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 4) { adcWave5.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias5); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 5) { adcWave6.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias6); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 6) { adcWave7.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias7); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 7) { adcWave8.append(SWAP16(_prxData->adcData[i]) * 5.0 / 32768.0 - 5.0 + ADC_Ybias8); }
        }

        //生成X轴数组
        for (quint16 i = 0; i < adcDataWholeChLen/adcEnableChNum; i++) { xAxisIndex.append(i); }


        quint16 axisMaxLen = adcDataWholeChLen/adcEnableChNum;
        if (!ui->xAxisLen->text().isEmpty())
        {
            axisMaxLen = ui->xAxisLen->text().toUInt();
        }

        if (axisMaxLen > ADC_ONCE_LEN / adcEnableChNum)
        {
            axisMaxLen = ADC_ONCE_LEN / adcEnableChNum;
        }

        // create graph and assign data to it:
        ui->waveform->clearGraphs();
        //ui->customPlot->graph(0)->setData(xAxis, adc1);
        //将曲线分别加入到相应的list

        for (quint16 i = 0; i < adcEnableChNum; i++)
        {
            ui->waveform->addGraph();

            if ((adcEnableChState[i % adcEnableChNum]) == 0) {ui->waveform->graph(i)->setPen(colorCh1); ui->waveform->graph(i)->setData(xAxisIndex, adcWave1); }
            else if ((adcEnableChState[i % adcEnableChNum]) == 1) {ui->waveform->graph(i)->setPen(colorCh2);  ui->waveform->graph(i)->setData(xAxisIndex, adcWave2); }
            else if ((adcEnableChState[i % adcEnableChNum]) == 2) {ui->waveform->graph(i)->setPen(colorCh3);  ui->waveform->graph(i)->setData(xAxisIndex, adcWave3); }
            else if ((adcEnableChState[i % adcEnableChNum]) == 3) {ui->waveform->graph(i)->setPen(colorCh4);  ui->waveform->graph(i)->setData(xAxisIndex, adcWave4); }
            else if ((adcEnableChState[i % adcEnableChNum]) == 4) {ui->waveform->graph(i)->setPen(colorCh5);  ui->waveform->graph(i)->setData(xAxisIndex, adcWave5); }
            else if ((adcEnableChState[i % adcEnableChNum]) == 5) {ui->waveform->graph(i)->setPen(colorCh6);  ui->waveform->graph(i)->setData(xAxisIndex, adcWave6); }
            else if ((adcEnableChState[i % adcEnableChNum]) == 6) {ui->waveform->graph(i)->setPen(colorCh7);  ui->waveform->graph(i)->setData(xAxisIndex, adcWave7); }
            else if ((adcEnableChState[i % adcEnableChNum]) == 7) {ui->waveform->graph(i)->setPen(colorCh8);  ui->waveform->graph(i)->setData(xAxisIndex, adcWave8); }
        }

        // give the axes some labels:
        ui->waveform->xAxis->setLabel("x");
        ui->waveform->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        ui->waveform->xAxis->setRange(0, axisMaxLen);//adcDataWholeChLen/adcEnableChNum);
        ui->waveform->yAxis->setRange(-5.5, 5.5);

        ui->waveform->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
        //ui->waveform->axisRect()->setRangeZoomFactor(1.2,1);
        //setGeometry(400, 250, 542, 390);
        //ui->customPlot->axisRect()->setupFullAxesBox();
        // ui->customPlot->rescaleAxes();
        ui->waveform->replot();
    }
}

void adcWave::on_pushButton_clicked()
{
    adcWaveSendCmdNoParam(_cmdId_setAdc_waveEnable_flag);

}


void adcWave::on_pushButton_2_clicked()
{
    if (ui->setAdcSamplingRate->text().isEmpty()){return;}
    quint32 freq = ui->setAdcSamplingRate->text().toUInt();
    adcWaveSendCmdUWordParam(_cmdId_setAdc_samplingRate, freq);

}

void adcWave::on_pushButton_3_clicked()
{
    if (ui->trigValue->text().isEmpty()){return;}
    double value = ui->trigValue->text().toDouble();
    quint16 trigD = (quint16)((value + 5.0) / 5.0 * 32768.0);
    adcWaveSendCmdUWordParam(_cmdId_setAdc_trigValue,trigD);

}

void adcWave::fun_setAdcState()
{
    ui->autoReadCheck->setChecked(false);
    quint8 adc1ChState = ui->adcCheck1->isChecked() << 0;
    quint8 adc2ChState = ui->adcCheck2->isChecked() << 1;
    quint8 adc3ChState = ui->adcCheck3->isChecked() << 2;
    quint8 adc4ChState = ui->adcCheck4->isChecked() << 3;
    quint8 adc5ChState = ui->adcCheck5->isChecked() << 4;
    quint8 adc6ChState = ui->adcCheck6->isChecked() << 5;
    quint8 adc7ChState = ui->adcCheck7->isChecked() << 6;
    quint8 adc8ChState = ui->adcCheck8->isChecked() << 7;

    quint8 adcChState = adc1ChState + adc2ChState + adc3ChState + adc4ChState + adc5ChState + adc6ChState + adc7ChState + adc8ChState;
    adcWaveSendCmdUByteParam(_cmdId_setAdc_chEnable, adcChState);
}

void adcWave::on_adcCheck1_clicked()
{
     fun_setAdcState();
}


void adcWave::on_adcCheck2_clicked()
{
    fun_setAdcState();
}


void adcWave::on_adcCheck3_clicked()
{
    fun_setAdcState();
}


void adcWave::on_adcCheck4_clicked()
{
    fun_setAdcState();
}


void adcWave::on_adcCheck5_clicked()
{
    fun_setAdcState();
}


void adcWave::on_adcCheck6_clicked()
{
    fun_setAdcState();
}


void adcWave::on_adcCheck7_clicked()
{
    fun_setAdcState();
}


void adcWave::on_adcCheck8_clicked()
{
    fun_setAdcState();
}


void adcWave::on_adcTrig1_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig1->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 0);
}


void adcWave::on_adcTrig2_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig2->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 1);
}


void adcWave::on_adcTrig3_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig3->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 2);
}


void adcWave::on_adcTrig4_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig4->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 3);
}


void adcWave::on_adcTrig5_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig5->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 4);
}


void adcWave::on_adcTrig6_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig6->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 5);
}


void adcWave::on_adcTrig7_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig7->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 6);
}


void adcWave::on_adcTrig8_clicked()
{
    fun_clearAdcTrig();
    ui->adcTrig8->setChecked(true);
    adcWaveSendCmdUByteParam(_cmdId_setAdc_trigCh, 7);
}

