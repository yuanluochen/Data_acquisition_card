#include "adcrecord.h"
#include "ui_adcrecord.h"
#include "mainwindow.h"

adcRecord::adcRecord(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::adcRecord)
{
    ui->setupUi(this);

    //系统初始化
    connect(&recordAutoReadTimer, &QTimer::timeout, this, &adcRecord::recordAutoReadProcess);
    recordAutoReadTimer.start(200);

}

adcRecord::~adcRecord()
{
    delete ui;
}

void adcRecord::recordAutoReadProcess()
{
    if(ui->autoReadCheck->isChecked())
    {
        adcRecordSendCmdNoParam(_cmdId_getAdcValue);
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

QVector<double> xAxisIndex;

QVector<double> adcRecord1;
QVector<double> adcRecord2;
QVector<double> adcRecord3;
QVector<double> adcRecord4;
QVector<double> adcRecord5;
QVector<double> adcRecord6;
QVector<double> adcRecord7;
QVector<double> adcRecord8;
quint32 listAxisIndex;

quint8 adc_ch_Enable;
quint16 flashRecordIntervalTime;
quint64 flash_DateTimeOffset_H;
quint64 flash_DateTimeOffset_L;
quint32 recordMaxDataLen = 0;
quint32 recordDatasNowLen = 0;
quint32 recordTick = 0;
bool sramRecordFlag = false;
bool flashRecordFlag = false;


quint16 adcEnableChState[8];
quint16 adcEnableChNum = 0;

bool bar_toggle;
void adcRecord::adcRecord_rxMsgProcess(quint8 *rxData)
{

    msgHead *_pRxHead = (msgHead *)rxData;

    if (_pRxHead->cmdId == _cmdId_getDeviceParam)
    {
      msgAdcWaveState *_prxData = (msgAdcWaveState *)rxData;

      ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
      ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
      ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
      ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
      ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
      ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
      ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
      ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);

      ui->setAdcSamplingRate->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));
      ui->setSramSamplingTime->setText(QString::number(SWAP32(_prxData->adcSramRecordMaxTime)));
      ui->intervalTime->setText(QString::number(SWAP16(_prxData->adcFlashRecordIntervalTime)));
    }
    else if (_pRxHead->cmdId == _cmdId_recordUploadStart)
    {
        msgULong *_prxData = (msgULong *)rxData;

        ui->progressBar->setValue(0);
        recordDatasNowLen = 0;
        recordMaxDataLen = SWAP32(_prxData->data);
        sramRecordFlag = false;
    }
    else if (_pRxHead->cmdId == _cmdId_recordUploadEnd)
    {
      if (sramRecordFlag == true)
      {
          //全部接收完成后再刷新波形

          ui->waveform->clearGraphs();

          //将曲线分别加入到相应的list

          for (quint16 i = 0; i < adcEnableChNum; i++)
          {
              ui->waveform->addGraph();

              if ((adcEnableChState[i % adcEnableChNum]) == 0) {ui->waveform->graph(i)->setPen(colorCh1); ui->waveform->graph(i)->setData(xAxisIndex, adcRecord1); }
              else if ((adcEnableChState[i % adcEnableChNum]) == 1) {ui->waveform->graph(i)->setPen(colorCh2);  ui->waveform->graph(i)->setData(xAxisIndex, adcRecord2); }
              else if ((adcEnableChState[i % adcEnableChNum]) == 2) {ui->waveform->graph(i)->setPen(colorCh3);  ui->waveform->graph(i)->setData(xAxisIndex, adcRecord3); }
              else if ((adcEnableChState[i % adcEnableChNum]) == 3) {ui->waveform->graph(i)->setPen(colorCh4);  ui->waveform->graph(i)->setData(xAxisIndex, adcRecord4); }
              else if ((adcEnableChState[i % adcEnableChNum]) == 4) {ui->waveform->graph(i)->setPen(colorCh5);  ui->waveform->graph(i)->setData(xAxisIndex, adcRecord5); }
              else if ((adcEnableChState[i % adcEnableChNum]) == 5) {ui->waveform->graph(i)->setPen(colorCh6);  ui->waveform->graph(i)->setData(xAxisIndex, adcRecord6); }
              else if ((adcEnableChState[i % adcEnableChNum]) == 6) {ui->waveform->graph(i)->setPen(colorCh7);  ui->waveform->graph(i)->setData(xAxisIndex, adcRecord7); }
              else if ((adcEnableChState[i % adcEnableChNum]) == 7) {ui->waveform->graph(i)->setPen(colorCh8);  ui->waveform->graph(i)->setData(xAxisIndex, adcRecord8); }
          }
          ui->waveform->xAxis->setLabel("x");
          ui->waveform->yAxis->setLabel("y");
          ui->waveform->xAxis->setRange(0, xAxisIndex.length());//adcDataWholeChLen/adcEnableChNum);
          ui->waveform->yAxis->setRange(-5.5, 5.5);
          ui->waveform->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);
          ui->waveform->replot();
          sramRecordFlag = false;
      }

      if(flashRecordFlag == true)
      {
          ui->waveform->clearGraphs();
          ui->waveform->replot();

          refreshWaveDataList();
          flashRecordFlag = false;
      }

      ui->progressBar->setValue(0);
      recordDatasNowLen = 0;
    }
    else if (_pRxHead->cmdId == _cmdId_flashRecordInfo)
    {
      msgAdcStartFlashRecordInfo *_prxData = (msgAdcStartFlashRecordInfo *)rxData;

      flash_DateTimeOffset_H = SWAP32(_prxData->DateTimeOffset_H);
      flash_DateTimeOffset_L = SWAP32(_prxData->DateTimeOffset_L);

      flashRecordIntervalTime = SWAP16(_prxData->recordIntervalTime);
      adc_ch_Enable = _prxData->adc_ch_Enable;
    }
    else if (_pRxHead->cmdId == _cmdId_flashRecordDatas)
    {
        msgRecordFlashDatas *_prxData = (msgRecordFlashDatas *)rxData;

        // 处理数据并添加到显示缓冲区和完整数据存储
        ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
        ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
        ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
        ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
        ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
        ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
        ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
        ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);

        quint16 dataIndex = 0;
        while (dataIndex < _prxData->dataLen)
        {
            if (((_prxData->adc_ch_Enable >> 0) & 0x01) == 1) { adcRecord1.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            if (((_prxData->adc_ch_Enable >> 1) & 0x01) == 1) { adcRecord2.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            if (((_prxData->adc_ch_Enable >> 2) & 0x01) == 1) { adcRecord3.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            if (((_prxData->adc_ch_Enable >> 3) & 0x01) == 1) { adcRecord4.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            if (((_prxData->adc_ch_Enable >> 4) & 0x01) == 1) { adcRecord5.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            if (((_prxData->adc_ch_Enable >> 5) & 0x01) == 1) { adcRecord6.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            if (((_prxData->adc_ch_Enable >> 6) & 0x01) == 1) { adcRecord7.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            if (((_prxData->adc_ch_Enable >> 7) & 0x01) == 1) { adcRecord8.append(SWAP16(_prxData->adcData[dataIndex++]) * 5.0 / 32768.0 - 5.0); }
            xAxisIndex.append(listAxisIndex++);
        }

        recordDatasNowLen += _prxData->dataLen;
        flashRecordFlag = true;
        double barPercent = recordDatasNowLen * 100.0 / recordMaxDataLen;
        ui->progressBar->setValue(barPercent);
    }
    else if (_pRxHead->cmdId == _cmdId_readSramRecordDatas)
    {
        msgGetAdcDatas *_prxData = (msgGetAdcDatas *)rxData;

        // 处理数据并添加到显示缓冲区和完整数据存储
        ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
        ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
        ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
        ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
        ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
        ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
        ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
        ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);
        ui->setAdcSamplingRate->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));

        quint16 adcStartChBias = 0;
        adcEnableChNum = 0;
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

        for (quint16 i = 0; i < SWAP16(_prxData->dataLen); i++)
        {
            if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 0) { adcRecord1.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 1) { adcRecord2.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 2) { adcRecord3.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 3) { adcRecord4.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 4) { adcRecord5.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 5) { adcRecord6.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 6) { adcRecord7.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 7) { adcRecord8.append(SWAP16((_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
        }

        //生成X轴数组
        for (quint16 i = 0; i < SWAP16(_prxData->dataLen) / adcEnableChNum; i++)
        {
            xAxisIndex.append(xAxisIndex.length());
        }

        recordDatasNowLen += SWAP16(_prxData->dataLen);
        sramRecordFlag = true;
        double barPercent = recordDatasNowLen * 100.0 / recordMaxDataLen;
        ui->progressBar->setValue(barPercent);

    }
    else if (_pRxHead->cmdId == _cmdId_sramRecordAutoUploadDatas)
    {
        msgAutoUploadDatas *_prxData = (msgAutoUploadDatas *)rxData;

        ui->sramSecond->setText(QString::number(_prxData->second));
        ui->sramMinute->setText(QString::number(_prxData->minute));
        ui->sramHour->setText(QString::number(_prxData->hour));
        ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
        ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
        ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
        ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
        ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
        ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
        ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
        ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);

    }
    else if (_pRxHead->cmdId == _cmdId_flashRecordAutoUploadDatas)
    {
        msgAutoUploadDatas *_prxData = (msgAutoUploadDatas *)rxData;

        ui->flashSecond->setText(QString::number(_prxData->second));
        ui->flashMinute->setText(QString::number(_prxData->minute));
        ui->flashHour->setText(QString::number(_prxData->hour));

        // 处理数据并添加到显示缓冲区和完整数据存储
        ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
        ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
        ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
        ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
        ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
        ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
        ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
        ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);
    }
    else if (_pRxHead->cmdId == _cmdId_getAdcValue)
    {
        msgGetAdcValue *_prxData = (msgGetAdcValue *)rxData;

        // 处理数据并添加到显示缓冲区和完整数据存储
        ui->adcCheck1->setChecked(((_prxData->adc_ch_Enable >> 0) & 0x01) == 1);
        ui->adcCheck2->setChecked(((_prxData->adc_ch_Enable >> 1) & 0x01) == 1);
        ui->adcCheck3->setChecked(((_prxData->adc_ch_Enable >> 2) & 0x01) == 1);
        ui->adcCheck4->setChecked(((_prxData->adc_ch_Enable >> 3) & 0x01) == 1);
        ui->adcCheck5->setChecked(((_prxData->adc_ch_Enable >> 4) & 0x01) == 1);
        ui->adcCheck6->setChecked(((_prxData->adc_ch_Enable >> 5) & 0x01) == 1);
        ui->adcCheck7->setChecked(((_prxData->adc_ch_Enable >> 6) & 0x01) == 1);
        ui->adcCheck8->setChecked(((_prxData->adc_ch_Enable >> 7) & 0x01) == 1);

        double value1 = SWAP16(_prxData->data[0]) * 5.0 / 32768.0 - 5.0;
        double value2 = SWAP16(_prxData->data[1]) * 5.0 / 32768.0 - 5.0;
        double value3 = SWAP16(_prxData->data[2]) * 5.0 / 32768.0 - 5.0;
        double value4 = SWAP16(_prxData->data[3]) * 5.0 / 32768.0 - 5.0;
        double value5 = SWAP16(_prxData->data[4]) * 5.0 / 32768.0 - 5.0;
        double value6 = SWAP16(_prxData->data[5]) * 5.0 / 32768.0 - 5.0;
        double value7 = SWAP16(_prxData->data[6]) * 5.0 / 32768.0 - 5.0;
        double value8 = SWAP16(_prxData->data[7]) * 5.0 / 32768.0 - 5.0;

        ui->adcValue1->setText(QString::number(value1,'f', 3) + " V");
        ui->adcValue2->setText(QString::number(value2,'f', 3) + " V");
        ui->adcValue3->setText(QString::number(value3,'f', 3) + " V");
        ui->adcValue4->setText(QString::number(value4,'f', 3) + " V");
        ui->adcValue5->setText(QString::number(value5,'f', 3) + " V");
        ui->adcValue6->setText(QString::number(value6,'f', 3) + " V");
        ui->adcValue7->setText(QString::number(value7,'f', 3) + " V");
        ui->adcValue8->setText(QString::number(value8,'f', 3) + " V");

        adcRecord1.append(SWAP16(_prxData->data[0]) * 5.0 / 32768.0 - 5.0);
        adcRecord2.append(SWAP16(_prxData->data[1]) * 5.0 / 32768.0 - 5.0);
        adcRecord3.append(SWAP16(_prxData->data[2]) * 5.0 / 32768.0 - 5.0);
        adcRecord4.append(SWAP16(_prxData->data[3]) * 5.0 / 32768.0 - 5.0);
        adcRecord5.append(SWAP16(_prxData->data[4]) * 5.0 / 32768.0 - 5.0);
        adcRecord6.append(SWAP16(_prxData->data[5]) * 5.0 / 32768.0 - 5.0);
        adcRecord7.append(SWAP16(_prxData->data[6]) * 5.0 / 32768.0 - 5.0);
        adcRecord8.append(SWAP16(_prxData->data[7]) * 5.0 / 32768.0 - 5.0);

        xAxisIndex.append(xAxisIndex.length());

        ui->waveform->clearGraphs();

        quint8 recordChNum = 0;

        if (ui->adcCheck1->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh1);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord1);
            recordChNum++;
        }

        if (ui->adcCheck2->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh2);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord2);
            recordChNum++;
        }

        if (ui->adcCheck3->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh3);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord3);
            recordChNum++;
        }

        if (ui->adcCheck4->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh4);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord4);
            recordChNum++;
        }

        if (ui->adcCheck5->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh5);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord5);
            recordChNum++;
        }

        if (ui->adcCheck6->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh6);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord6);
            recordChNum++;
        }

        if (ui->adcCheck7->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh7);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord7);
            recordChNum++;
        }

        if (ui->adcCheck8->isChecked()) {
            ui->waveform->addGraph();
            ui->waveform->graph(recordChNum)->setPen(colorCh8);
            ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord8);
            recordChNum++;
        }

        ui->waveform->xAxis->setLabel("x");
        ui->waveform->yAxis->setLabel("y");
        ui->waveform->xAxis->setRange(0, xAxisIndex.length());//adcDataWholeChLen/adcEnableChNum);
        ui->waveform->yAxis->setRange(-5.5, 5.5);
        ui->waveform->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
        ui->waveform->replot();
    }
    else if (_pRxHead->cmdId == _cmdId_readOnlineRecordDatas)
    {
        msgGetAdcDatas *_prxData = (msgGetAdcDatas*)rxData;

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

        ui->setAdcSamplingRate->setText(QString::number(SWAP16(_prxData->adcSamplingRate)));

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
        clearAllWaves();
        const quint16 ADC_ONCE_LEN = 4000;
        //开始采集点不一定是通道1, 寻找初始通道, 最后采集不一定是通道数整数倍, 所以删除最后非完整采集部分
        quint16 adcDataWholeChLen = (ADC_ONCE_LEN / adcEnableChNum) * adcEnableChNum;

        for (quint16 i = 0; i < adcDataWholeChLen; i++)
        {
            //最后叠加的数字为偏置
            if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 0) { adcRecord1.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 1) { adcRecord2.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 2) { adcRecord3.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 3) { adcRecord4.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 4) { adcRecord5.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 5) { adcRecord6.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 6) { adcRecord7.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
            else if (adcEnableChState[(i + adcStartChBias) % adcEnableChNum] == 7) { adcRecord8.append((SWAP16(_prxData->adcData[i])) * 5.0 / 32768.0 - 5.0); }
        }

        //生成X轴数组
        quint16 axisMaxLen = (quint16)(adcDataWholeChLen / adcEnableChNum);
        for (quint16 i = 0; i < axisMaxLen; i++) { xAxisIndex.append(i); }

        if (ui->ckb_RefreshWave->isChecked())
        {
            refreshWaveDataList();
        }

        if(ui->progressBar->value() == 100)
        {
            ui->progressBar->setValue(0);
        }
        else
        {
            ui->progressBar->setValue(100);
        }

        if (ui->autoSave->isChecked() && ui->filePath->text() != "N/A" && !ui->filePath->text().isEmpty())
        {
            QFile file(ui->filePath->text());
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                qDebug() << "文件打开失败，无法以追加模式写入";
                return;
            }

            QTextStream out(&file);
            //out.setEncoding(QStringConverter::Utf8);  // Qt 6

            for (int i = 0; i < axisMaxLen; i++)
            {
                QString line;

                // 同上，构建每一行
                if (adcRecord1.size() > i) line += QString::number(adcRecord1[i], 'f', 3) + ",";
                else line += ",";

                if (adcRecord2.size() > i) line += QString::number(adcRecord2[i], 'f', 3) + ",";
                else line += ",";

                if (adcRecord3.size() > i) line += QString::number(adcRecord3[i], 'f', 3) + ",";
                else line += ",";

                if (adcRecord4.size() > i) line += QString::number(adcRecord4[i], 'f', 3) + ",";
                else line += ",";

                if (adcRecord5.size() > i) line += QString::number(adcRecord5[i], 'f', 3) + ",";
                else line += ",";

                if (adcRecord6.size() > i) line += QString::number(adcRecord6[i], 'f', 3) + ",";
                else line += ",";

                if (adcRecord7.size() > i) line += QString::number(adcRecord7[i], 'f', 3) + ",";
                else line += ",";

                if (adcRecord8.size() > i) line += QString::number(adcRecord8[i], 'f', 3) + ",";
                else line += ",";

                line += "\n";

                // 直接写入文件，不保存到 QStringList
                out << line;
            }

            file.close();

        }

    }

}

void adcRecord::refreshWaveDataList()
{
    quint8 recordChNum = 0;

    if (ui->adcCheck1->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh1);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord1);
        recordChNum++;
    }

    if (ui->adcCheck2->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh2);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord2);
        recordChNum++;
    }

    if (ui->adcCheck3->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh3);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord3);
        recordChNum++;
    }

    if (ui->adcCheck4->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh4);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord4);
        recordChNum++;
    }

    if (ui->adcCheck5->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh5);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord5);
        recordChNum++;
    }

    if (ui->adcCheck6->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh6);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord6);
        recordChNum++;
    }

    if (ui->adcCheck7->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh7);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord7);
        recordChNum++;
    }

    if (ui->adcCheck8->isChecked()) {
        ui->waveform->addGraph();
        ui->waveform->graph(recordChNum)->setPen(colorCh8);
        ui->waveform->graph(recordChNum)->setData(xAxisIndex, adcRecord8);
        recordChNum++;
    }

        ui->waveform->xAxis->setLabel("x");
        ui->waveform->yAxis->setLabel("y");
        ui->waveform->xAxis->setRange(0, xAxisIndex.length());//adcDataWholeChLen/adcEnableChNum);
        ui->waveform->yAxis->setRange(-5.5, 5.5);
        ui->waveform->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
        ui->waveform->replot();
        sramRecordFlag = false;

}

void adcRecord::adcRecordSendCmdNoParam(quint8 cmd)
{
    /************消息数组转结构体************/
    msgNoParam* _pTx = (msgNoParam*)MSG_TX_BUF;
    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->frameLen = SWAP16(sizeof(msgNoParam));
    _pTx->cmdId = cmd;
    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_adcRecordNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_adcRecordUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));

}

void adcRecord::adcRecordSendCmdUByteParam(quint8 cmd,quint8 data)
{
    /************消息数组转结构体************/
    msgUbyte* _pTx = (msgUbyte*)MSG_TX_BUF;
    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->frameLen = sizeof(msgUbyte);
    _pTx->cmdId = cmd;
    _pTx->data = data;
    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,_pTx->frameLen));
    emit sig_adcRecordNetSend(MSG_TX_BUF,_pTx->frameLen);
    emit sig_adcRecordUsbSend(MSG_TX_BUF,_pTx->frameLen);

}

void adcRecord::adcRecordSendCmdUWordParam(quint8 cmd,quint16 data)
{
    /************消息数组转结构体************/
    msgUWord* _pTx = (msgUWord*)MSG_TX_BUF;
    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->frameLen = sizeof(msgUWord);
    _pTx->cmdId = cmd;
    _pTx->data = data;
    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,_pTx->frameLen));
    emit sig_adcRecordNetSend(MSG_TX_BUF,_pTx->frameLen);
    emit sig_adcRecordUsbSend(MSG_TX_BUF,_pTx->frameLen);

}
quint8 adcRecord::fun_getAdcChStateEnable()
{
    quint8 adc1ChState = ui->adcCheck1->isChecked() << 0;
    quint8 adc2ChState = ui->adcCheck2->isChecked() << 1;
    quint8 adc3ChState = ui->adcCheck3->isChecked() << 2;
    quint8 adc4ChState = ui->adcCheck4->isChecked() << 3;
    quint8 adc5ChState = ui->adcCheck5->isChecked() << 4;
    quint8 adc6ChState = ui->adcCheck6->isChecked() << 5;
    quint8 adc7ChState = ui->adcCheck7->isChecked() << 6;
    quint8 adc8ChState = ui->adcCheck8->isChecked() << 7;

    quint8 adcChState = adc1ChState + adc2ChState + adc3ChState + adc4ChState + adc5ChState + adc6ChState + adc7ChState + adc8ChState;

    return adcChState;
}

void adcRecord::fun_setAdcState()
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
    adcRecordSendCmdUByteParam(_cmdId_setAdc_chEnable, adcChState);
}

void adcRecord::on_pushButton_4_clicked()
{
    adcRecordSendCmdNoParam(_cmdId_getAdcValue);
}


void adcRecord::on_adcCheck1_clicked()
{
    fun_setAdcState();
}


void adcRecord::on_adcCheck2_clicked()
{
    fun_setAdcState();
}


void adcRecord::on_adcCheck3_clicked()
{
    fun_setAdcState();
}


void adcRecord::on_adcCheck4_clicked()
{
    fun_setAdcState();
}


void adcRecord::on_adcCheck5_clicked()
{
    fun_setAdcState();
}


void adcRecord::on_adcCheck6_clicked()
{
    fun_setAdcState();
}


void adcRecord::on_adcCheck7_clicked()
{
    fun_setAdcState();
}


void adcRecord::on_adcCheck8_clicked()
{
    fun_setAdcState();
}

void adcRecord::clearAllWaves()
{
    xAxisIndex.clear();
    listAxisIndex = 0;
    adcRecord1.clear();
    adcRecord2.clear();
    adcRecord3.clear();
    adcRecord4.clear();
    adcRecord5.clear();
    adcRecord6.clear();
    adcRecord7.clear();
    adcRecord8.clear();

    ui->waveform->clearGraphs();
    ui->waveform->replot();
}

void adcRecord::on_pushButton_2_clicked()
{
    clearAllWaves();
    /************消息数组转结构体************/
    if (ui->setAdcSamplingRate->text().isEmpty()) { return; }
    if (ui->setSramSamplingTime->text().isEmpty()) { return; }

    msgAdcStartSramRecord* _pTx = (msgAdcStartSramRecord*)MSG_TX_BUF;

    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->frameLen = SWAP16(sizeof(msgAdcStartSramRecord));
    _pTx->cmdId = _cmdId_startSramRecord;
    _pTx->adc_ch_Enable = fun_getAdcChStateEnable();
    _pTx->adcSamplingRate = SWAP16(ui->setAdcSamplingRate->text().toUInt());
    _pTx->sramSamplingTimeMax = SWAP32(ui->setSramSamplingTime->text().toUInt());

    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_adcRecordNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_adcRecordUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}


void adcRecord::on_pushButton_3_clicked()
{
    adcRecordSendCmdNoParam(_cmdId_stopSramRecord);

}

void adcRecord::on_pushButton_6_clicked()
{
    ui->autoReadCheck->setChecked(false);

    clearAllWaves();

    adcRecordSendCmdNoParam(_cmdId_readSramRecordDatas);
}

void adcRecord::on_pushButton_8_clicked()
{
    adcRecordSendCmdNoParam(_cmdId_stopFlashRecord);
}

void adcRecord::on_pushButton_12_clicked()
{
    ui->autoReadCheck->setChecked(false);
    xAxisIndex.clear();
    listAxisIndex = 0;
    adcRecord1.clear();
    adcRecord2.clear();
    adcRecord3.clear();
    adcRecord4.clear();
    adcRecord5.clear();
    adcRecord6.clear();
    adcRecord7.clear();
    adcRecord8.clear();

    ui->waveform->clearGraphs();
    ui->waveform->replot();
    adcRecordSendCmdNoParam(_cmdId_readFlashRecordDatas);
}

void adcRecord::on_pushButton_5_clicked()
{

}

void adcRecord::on_pushButton_7_clicked()
{
    QString path = QFileDialog::getExistingDirectory(
        this,
        tr("选择保存文件的目录"),
        QDir::homePath(), // 默认打开用户主目录
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (path.isEmpty()) {
        // 用户取消了选择
        return;
    }

    // 以当前时间生成文件名，格式如：2024-06-01_14-30-45.txt
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    QString fileName = timestamp + ".txt";
    QString fullPath = path + "/" + fileName; // 或者使用 QDir::toNativeSeparators

    // 打开文件以写入
    QFile file(fullPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       qDebug()<<"文件打开失败";
        return;
    }

    // //对文件进行写操作
    // if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    // {
    //     qDebug()<<"文件打开失败";
    // }
    QString str = "";

    str+=("SRAM RECORD, TOTAL LINE: " + QString::number(xAxisIndex.count()) + "\n");
    str+="\n";
    for (int i = 0; i < xAxisIndex.count(); i++)
    {
        if (adcRecord1.count() > i) { str+=(QString::number(adcRecord1[i],'f',3) + ","); } else { str+=(","); }
        if (adcRecord2.count() > i) { str+=(QString::number(adcRecord2[i],'f',3) + ","); } else { str+=(","); }
        if (adcRecord3.count() > i) { str+=(QString::number(adcRecord3[i],'f',3) + ","); } else { str+=(","); }
        if (adcRecord4.count() > i) { str+=(QString::number(adcRecord4[i],'f',3) + ","); } else { str+=(","); }
        if (adcRecord5.count() > i) { str+=(QString::number(adcRecord5[i],'f',3) + ","); } else { str+=(","); }
        if (adcRecord6.count() > i) { str+=(QString::number(adcRecord6[i],'f',3) + ","); } else { str+=(","); }
        if (adcRecord7.count() > i) { str+=(QString::number(adcRecord7[i],'f',3) + ","); } else { str+=(","); }
        if (adcRecord8.count() > i) { str+=(QString::number(adcRecord8[i],'f',3) + ","); } else { str+=(","); }
        str+=("\n");
    }

    QTextStream out(&file);
    out << str;
    //向文件中写入两行字符串
    //file.write(str);
    //关闭文件
    file.close();
}

void adcRecord::on_pushButton_11_clicked()
{

}

void adcRecord::on_pushButton_9_clicked()
{

}

void adcRecord::on_pushButton_10_clicked()
{
    /************消息数组转结构体************/
    msgAdcStartFlashRecordInfo* _pTx = (msgAdcStartFlashRecordInfo*)MSG_TX_BUF;
    if (ui->intervalTime->text().isEmpty()) { return; }


    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->cmdId = _cmdId_startFlashRecord;
    _pTx->frameLen = SWAP16(sizeof(msgAdcStartFlashRecordInfo));

    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    _pTx->DateTimeOffset_H = (currentTime >> 32) & 0xffffffff;
    _pTx->DateTimeOffset_L = (currentTime >> 0) & 0xffffffff;

    _pTx->adc_ch_Enable = fun_getAdcChStateEnable();
    _pTx->recordIntervalTime = ui->intervalTime->text().toUInt();

    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_adcRecordNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_adcRecordUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));

    clearAllWaves();
}

void adcRecord::on_pushButton_13_clicked()
{
    clearAllWaves();
}

void adcRecord::on_pushButton_14_clicked()
{
    /************消息数组转结构体************/
    if (ui->setAdcSamplingRate->text().isEmpty()) { return; }

    msgAdcStartOnlineRecord* _pTx = (msgAdcStartOnlineRecord*)MSG_TX_BUF;

    _pTx->msgHead = SWAP16(0x55aa);
    _pTx->cmdId = _cmdId_startOnlineRecord;
    _pTx->frameLen = SWAP16(sizeof(msgAdcStartOnlineRecord));

    _pTx->adc_ch_Enable = fun_getAdcChStateEnable();
    _pTx->adcSamplingRate = SWAP16(ui->setAdcSamplingRate->text().toUInt());
    _pTx->crc = SWAP16(getCrc16WithTail((quint8*)MSG_TX_BUF,SWAP16(_pTx->frameLen)));
    emit sig_adcRecordNetSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
    emit sig_adcRecordUsbSend(MSG_TX_BUF,SWAP16(_pTx->frameLen));
}

void adcRecord::on_pushButton_15_clicked()
{
    adcRecordSendCmdNoParam(_cmdId_stopOnlineRecord);
}

void adcRecord::on_pushButton_16_clicked()
{
    QString path = QFileDialog::getExistingDirectory(
        this,
        tr("选择保存文件的目录"),
        QDir::homePath(), // 默认打开用户主目录
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (path.isEmpty()) {
        // 用户取消了选择
        return;
    }

    // 以当前时间生成文件名，格式如：2024-06-01_14-30-45.txt
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    QString fileName = timestamp + ".txt";
    QString fullPath = path + "/" + fileName; // 或者使用 QDir::toNativeSeparators
    ui->filePath->setText( path + "/" + fileName); // 或者使用 QDir::toNativeSeparators

    // 打开文件以写入
    QFile file(ui->filePath->text());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<"文件打开失败";
        return;
    }


    QString str = "";

    QTextStream out(&file);
    out << str;
    //向文件中写入两行字符串
    //file.write(str);
    //关闭文件
    file.close();

}

