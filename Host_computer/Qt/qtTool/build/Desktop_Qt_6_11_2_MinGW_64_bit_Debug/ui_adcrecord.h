/********************************************************************************
** Form generated from reading UI file 'adcrecord.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADCRECORD_H
#define UI_ADCRECORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_adcRecord
{
public:
    QPushButton *pushButton_2;
    QLabel *rdAdcFreq_2;
    QCustomPlot *waveform;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QCheckBox *adcCheck1;
    QCheckBox *adcCheck2;
    QCheckBox *adcCheck3;
    QCheckBox *adcCheck4;
    QCheckBox *adcCheck5;
    QCheckBox *adcCheck6;
    QCheckBox *adcCheck7;
    QCheckBox *adcCheck8;
    QVBoxLayout *verticalLayout_2;
    QLabel *adcValue1;
    QLabel *adcValue2;
    QLabel *adcValue3;
    QLabel *adcValue4;
    QLabel *adcValue5;
    QLabel *adcValue6;
    QLabel *adcValue7;
    QLabel *adcValue8;
    QCheckBox *autoReadCheck;
    QPushButton *pushButton_4;
    QCheckBox *refreshCheckBox;
    QLabel *rdAdcFreq_3;
    QLabel *rdAdcFreq_4;
    QLineEdit *setSramSamplingTime;
    QLineEdit *setAdcSamplingRate;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLineEdit *intervalTime;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *rdAdcFreq_15;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLabel *rdAdcFreq_21;
    QPushButton *pushButton_13;
    QProgressBar *progressBar;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *rdAdcFreq_5;
    QLabel *sramHour;
    QLabel *rdAdcFreq_6;
    QLabel *sramMinute;
    QLabel *rdAdcFreq_8;
    QLabel *sramSecond;
    QLabel *rdAdcFreq_7;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *rdAdcFreq_16;
    QLabel *flashHour;
    QLabel *rdAdcFreq_19;
    QLabel *flashMinute;
    QLabel *rdAdcFreq_12;
    QLabel *flashSecond;
    QLabel *rdAdcFreq_14;
    QLabel *rdAdcFreq_9;
    QLabel *rdAdcFreq_10;
    QLabel *rdAdcFreq_11;
    QCheckBox *ckb_RefreshWave;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QLabel *filePath;
    QPushButton *pushButton_16;
    QCheckBox *autoSave;

    void setupUi(QWidget *adcRecord)
    {
        if (adcRecord->objectName().isEmpty())
            adcRecord->setObjectName("adcRecord");
        adcRecord->resize(1400, 800);
        pushButton_2 = new QPushButton(adcRecord);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(840, 50, 91, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font.setPointSize(12);
        pushButton_2->setFont(font);
        rdAdcFreq_2 = new QLabel(adcRecord);
        rdAdcFreq_2->setObjectName("rdAdcFreq_2");
        rdAdcFreq_2->setGeometry(QRect(660, 20, 191, 16));
        rdAdcFreq_2->setFont(font);
        waveform = new QCustomPlot(adcRecord);
        waveform->setObjectName("waveform");
        waveform->setGeometry(QRect(260, 270, 1111, 511));
        layoutWidget = new QWidget(adcRecord);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 310, 191, 208));
        layoutWidget->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        adcCheck1 = new QCheckBox(layoutWidget);
        adcCheck1->setObjectName("adcCheck1");
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(170, 85, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        QBrush brush2(QColor(255, 128, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush2);
        QBrush brush3(QColor(212, 106, 0, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush3);
        QBrush brush4(QColor(85, 42, 0, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush4);
        QBrush brush5(QColor(113, 56, 0, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush5);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush6);
        QBrush brush7(QColor(255, 255, 255, 255));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush7);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush7);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush6);
        QBrush brush8(QColor(212, 170, 127, 255));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush8);
        QBrush brush9(QColor(255, 255, 220, 255));
        brush9.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush9);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush6);
        QBrush brush10(QColor(0, 0, 0, 128));
        brush10.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush7);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush7);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush8);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush9);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush9);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        adcCheck1->setPalette(palette);
        adcCheck1->setFont(font);
        adcCheck1->setChecked(true);

        verticalLayout->addWidget(adcCheck1);

        adcCheck2 = new QCheckBox(layoutWidget);
        adcCheck2->setObjectName("adcCheck2");
        QPalette palette1;
        QBrush brush11(QColor(255, 0, 0, 255));
        brush11.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush11);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush11);
        QBrush brush12(QColor(120, 120, 120, 255));
        brush12.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcCheck2->setPalette(palette1);
        adcCheck2->setFont(font);
        adcCheck2->setChecked(true);

        verticalLayout->addWidget(adcCheck2);

        adcCheck3 = new QCheckBox(layoutWidget);
        adcCheck3->setObjectName("adcCheck3");
        QPalette palette2;
        QBrush brush13(QColor(255, 0, 255, 255));
        brush13.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush13);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush13);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcCheck3->setPalette(palette2);
        adcCheck3->setFont(font);
        adcCheck3->setChecked(true);

        verticalLayout->addWidget(adcCheck3);

        adcCheck4 = new QCheckBox(layoutWidget);
        adcCheck4->setObjectName("adcCheck4");
        QPalette palette3;
        QBrush brush14(QColor(220, 147, 0, 255));
        brush14.setStyle(Qt::BrushStyle::SolidPattern);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush14);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush14);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcCheck4->setPalette(palette3);
        adcCheck4->setFont(font);
        adcCheck4->setChecked(true);

        verticalLayout->addWidget(adcCheck4);

        adcCheck5 = new QCheckBox(layoutWidget);
        adcCheck5->setObjectName("adcCheck5");
        QPalette palette4;
        QBrush brush15(QColor(0, 161, 0, 255));
        brush15.setStyle(Qt::BrushStyle::SolidPattern);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush15);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush15);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcCheck5->setPalette(palette4);
        adcCheck5->setFont(font);
        adcCheck5->setChecked(true);

        verticalLayout->addWidget(adcCheck5);

        adcCheck6 = new QCheckBox(layoutWidget);
        adcCheck6->setObjectName("adcCheck6");
        QPalette palette5;
        QBrush brush16(QColor(0, 225, 225, 255));
        brush16.setStyle(Qt::BrushStyle::SolidPattern);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush16);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush16);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcCheck6->setPalette(palette5);
        adcCheck6->setFont(font);
        adcCheck6->setChecked(true);

        verticalLayout->addWidget(adcCheck6);

        adcCheck7 = new QCheckBox(layoutWidget);
        adcCheck7->setObjectName("adcCheck7");
        QPalette palette6;
        QBrush brush17(QColor(0, 0, 255, 255));
        brush17.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush17);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush17);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcCheck7->setPalette(palette6);
        adcCheck7->setFont(font);
        adcCheck7->setChecked(true);

        verticalLayout->addWidget(adcCheck7);

        adcCheck8 = new QCheckBox(layoutWidget);
        adcCheck8->setObjectName("adcCheck8");
        QPalette palette7;
        QBrush brush18(QColor(170, 0, 255, 255));
        brush18.setStyle(Qt::BrushStyle::SolidPattern);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush18);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush18);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcCheck8->setPalette(palette7);
        adcCheck8->setFont(font);
        adcCheck8->setChecked(true);

        verticalLayout->addWidget(adcCheck8);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        adcValue1 = new QLabel(layoutWidget);
        adcValue1->setObjectName("adcValue1");
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush1);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush1);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue1->setPalette(palette8);
        adcValue1->setFont(font);

        verticalLayout_2->addWidget(adcValue1);

        adcValue2 = new QLabel(layoutWidget);
        adcValue2->setObjectName("adcValue2");
        QPalette palette9;
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush11);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush11);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue2->setPalette(palette9);
        adcValue2->setFont(font);

        verticalLayout_2->addWidget(adcValue2);

        adcValue3 = new QLabel(layoutWidget);
        adcValue3->setObjectName("adcValue3");
        QPalette palette10;
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush13);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush13);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue3->setPalette(palette10);
        adcValue3->setFont(font);

        verticalLayout_2->addWidget(adcValue3);

        adcValue4 = new QLabel(layoutWidget);
        adcValue4->setObjectName("adcValue4");
        QPalette palette11;
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush14);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush14);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue4->setPalette(palette11);
        adcValue4->setFont(font);

        verticalLayout_2->addWidget(adcValue4);

        adcValue5 = new QLabel(layoutWidget);
        adcValue5->setObjectName("adcValue5");
        QPalette palette12;
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush15);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush15);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue5->setPalette(palette12);
        adcValue5->setFont(font);

        verticalLayout_2->addWidget(adcValue5);

        adcValue6 = new QLabel(layoutWidget);
        adcValue6->setObjectName("adcValue6");
        QPalette palette13;
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush16);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush16);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue6->setPalette(palette13);
        adcValue6->setFont(font);

        verticalLayout_2->addWidget(adcValue6);

        adcValue7 = new QLabel(layoutWidget);
        adcValue7->setObjectName("adcValue7");
        QPalette palette14;
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush17);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush17);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue7->setPalette(palette14);
        adcValue7->setFont(font);

        verticalLayout_2->addWidget(adcValue7);

        adcValue8 = new QLabel(layoutWidget);
        adcValue8->setObjectName("adcValue8");
        QPalette palette15;
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush18);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush18);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush12);
        adcValue8->setPalette(palette15);
        adcValue8->setFont(font);

        verticalLayout_2->addWidget(adcValue8);


        horizontalLayout_2->addLayout(verticalLayout_2);

        autoReadCheck = new QCheckBox(adcRecord);
        autoReadCheck->setObjectName("autoReadCheck");
        autoReadCheck->setGeometry(QRect(10, 220, 181, 20));
        autoReadCheck->setFont(font);
        pushButton_4 = new QPushButton(adcRecord);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 250, 181, 23));
        pushButton_4->setFont(font);
        refreshCheckBox = new QCheckBox(adcRecord);
        refreshCheckBox->setObjectName("refreshCheckBox");
        refreshCheckBox->setGeometry(QRect(10, 280, 181, 20));
        refreshCheckBox->setFont(font);
        refreshCheckBox->setChecked(true);
        rdAdcFreq_3 = new QLabel(adcRecord);
        rdAdcFreq_3->setObjectName("rdAdcFreq_3");
        rdAdcFreq_3->setGeometry(QRect(680, 50, 71, 16));
        rdAdcFreq_3->setFont(font);
        rdAdcFreq_4 = new QLabel(adcRecord);
        rdAdcFreq_4->setObjectName("rdAdcFreq_4");
        rdAdcFreq_4->setGeometry(QRect(640, 80, 111, 16));
        rdAdcFreq_4->setFont(font);
        setSramSamplingTime = new QLineEdit(adcRecord);
        setSramSamplingTime->setObjectName("setSramSamplingTime");
        setSramSamplingTime->setGeometry(QRect(760, 80, 71, 21));
        setSramSamplingTime->setFont(font);
        setAdcSamplingRate = new QLineEdit(adcRecord);
        setAdcSamplingRate->setObjectName("setAdcSamplingRate");
        setAdcSamplingRate->setGeometry(QRect(760, 50, 71, 21));
        setAdcSamplingRate->setFont(font);
        pushButton_3 = new QPushButton(adcRecord);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(690, 150, 91, 31));
        pushButton_3->setFont(font);
        pushButton_5 = new QPushButton(adcRecord);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(800, 150, 91, 31));
        pushButton_5->setFont(font);
        pushButton_6 = new QPushButton(adcRecord);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(690, 190, 91, 31));
        pushButton_6->setFont(font);
        pushButton_7 = new QPushButton(adcRecord);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(800, 190, 91, 31));
        pushButton_7->setFont(font);
        intervalTime = new QLineEdit(adcRecord);
        intervalTime->setObjectName("intervalTime");
        intervalTime->setGeometry(QRect(1070, 60, 71, 31));
        intervalTime->setFont(font);
        pushButton_8 = new QPushButton(adcRecord);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(1000, 160, 91, 31));
        pushButton_8->setFont(font);
        pushButton_9 = new QPushButton(adcRecord);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(1110, 200, 91, 31));
        pushButton_9->setFont(font);
        rdAdcFreq_15 = new QLabel(adcRecord);
        rdAdcFreq_15->setObjectName("rdAdcFreq_15");
        rdAdcFreq_15->setGeometry(QRect(970, 30, 251, 16));
        rdAdcFreq_15->setFont(font);
        pushButton_10 = new QPushButton(adcRecord);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(1150, 50, 91, 51));
        pushButton_10->setFont(font);
        pushButton_11 = new QPushButton(adcRecord);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(1110, 160, 91, 31));
        pushButton_11->setFont(font);
        pushButton_12 = new QPushButton(adcRecord);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(1000, 200, 91, 31));
        pushButton_12->setFont(font);
        rdAdcFreq_21 = new QLabel(adcRecord);
        rdAdcFreq_21->setObjectName("rdAdcFreq_21");
        rdAdcFreq_21->setGeometry(QRect(960, 70, 111, 16));
        rdAdcFreq_21->setFont(font);
        pushButton_13 = new QPushButton(adcRecord);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(160, 750, 91, 31));
        pushButton_13->setFont(font);
        progressBar = new QProgressBar(adcRecord);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(1240, 240, 161, 23));
        progressBar->setValue(0);
        layoutWidget1 = new QWidget(adcRecord);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(640, 120, 301, 18));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        rdAdcFreq_5 = new QLabel(layoutWidget1);
        rdAdcFreq_5->setObjectName("rdAdcFreq_5");
        rdAdcFreq_5->setFont(font);

        horizontalLayout_3->addWidget(rdAdcFreq_5);

        sramHour = new QLabel(layoutWidget1);
        sramHour->setObjectName("sramHour");
        sramHour->setFont(font);

        horizontalLayout_3->addWidget(sramHour);

        rdAdcFreq_6 = new QLabel(layoutWidget1);
        rdAdcFreq_6->setObjectName("rdAdcFreq_6");
        rdAdcFreq_6->setFont(font);

        horizontalLayout_3->addWidget(rdAdcFreq_6);

        sramMinute = new QLabel(layoutWidget1);
        sramMinute->setObjectName("sramMinute");
        sramMinute->setFont(font);

        horizontalLayout_3->addWidget(sramMinute);

        rdAdcFreq_8 = new QLabel(layoutWidget1);
        rdAdcFreq_8->setObjectName("rdAdcFreq_8");
        rdAdcFreq_8->setFont(font);

        horizontalLayout_3->addWidget(rdAdcFreq_8);

        sramSecond = new QLabel(layoutWidget1);
        sramSecond->setObjectName("sramSecond");
        sramSecond->setFont(font);

        horizontalLayout_3->addWidget(sramSecond);

        rdAdcFreq_7 = new QLabel(layoutWidget1);
        rdAdcFreq_7->setObjectName("rdAdcFreq_7");
        rdAdcFreq_7->setFont(font);

        horizontalLayout_3->addWidget(rdAdcFreq_7);

        layoutWidget2 = new QWidget(adcRecord);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(950, 120, 291, 18));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        rdAdcFreq_16 = new QLabel(layoutWidget2);
        rdAdcFreq_16->setObjectName("rdAdcFreq_16");
        rdAdcFreq_16->setFont(font);

        horizontalLayout_4->addWidget(rdAdcFreq_16);

        flashHour = new QLabel(layoutWidget2);
        flashHour->setObjectName("flashHour");
        flashHour->setFont(font);

        horizontalLayout_4->addWidget(flashHour);

        rdAdcFreq_19 = new QLabel(layoutWidget2);
        rdAdcFreq_19->setObjectName("rdAdcFreq_19");
        rdAdcFreq_19->setFont(font);

        horizontalLayout_4->addWidget(rdAdcFreq_19);

        flashMinute = new QLabel(layoutWidget2);
        flashMinute->setObjectName("flashMinute");
        flashMinute->setFont(font);

        horizontalLayout_4->addWidget(flashMinute);

        rdAdcFreq_12 = new QLabel(layoutWidget2);
        rdAdcFreq_12->setObjectName("rdAdcFreq_12");
        rdAdcFreq_12->setFont(font);

        horizontalLayout_4->addWidget(rdAdcFreq_12);

        flashSecond = new QLabel(layoutWidget2);
        flashSecond->setObjectName("flashSecond");
        flashSecond->setFont(font);

        horizontalLayout_4->addWidget(flashSecond);

        rdAdcFreq_14 = new QLabel(layoutWidget2);
        rdAdcFreq_14->setObjectName("rdAdcFreq_14");
        rdAdcFreq_14->setFont(font);

        horizontalLayout_4->addWidget(rdAdcFreq_14);

        rdAdcFreq_9 = new QLabel(adcRecord);
        rdAdcFreq_9->setObjectName("rdAdcFreq_9");
        rdAdcFreq_9->setGeometry(QRect(310, 60, 191, 16));
        rdAdcFreq_9->setFont(font);
        rdAdcFreq_10 = new QLabel(adcRecord);
        rdAdcFreq_10->setObjectName("rdAdcFreq_10");
        rdAdcFreq_10->setGeometry(QRect(290, 80, 221, 20));
        rdAdcFreq_10->setFont(font);
        rdAdcFreq_11 = new QLabel(adcRecord);
        rdAdcFreq_11->setObjectName("rdAdcFreq_11");
        rdAdcFreq_11->setGeometry(QRect(300, 100, 191, 16));
        rdAdcFreq_11->setFont(font);
        ckb_RefreshWave = new QCheckBox(adcRecord);
        ckb_RefreshWave->setObjectName("ckb_RefreshWave");
        ckb_RefreshWave->setGeometry(QRect(340, 120, 88, 20));
        QPalette palette16;
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush2);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush3);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush4);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush5);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush6);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush7);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush6);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush7);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush6);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush8);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush9);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush2);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush3);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush4);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush5);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush6);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush7);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush6);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush7);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush6);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush8);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush9);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush4);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush2);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush3);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush4);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush5);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush4);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush7);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush4);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush6);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush1);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush9);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        ckb_RefreshWave->setPalette(palette16);
        ckb_RefreshWave->setFont(font);
        pushButton_14 = new QPushButton(adcRecord);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(340, 150, 91, 31));
        pushButton_14->setFont(font);
        pushButton_15 = new QPushButton(adcRecord);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(340, 180, 91, 31));
        pushButton_15->setFont(font);
        filePath = new QLabel(adcRecord);
        filePath->setObjectName("filePath");
        filePath->setGeometry(QRect(10, 10, 1121, 16));
        filePath->setFont(font);
        pushButton_16 = new QPushButton(adcRecord);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(0, 40, 121, 31));
        pushButton_16->setFont(font);
        autoSave = new QCheckBox(adcRecord);
        autoSave->setObjectName("autoSave");
        autoSave->setGeometry(QRect(0, 70, 131, 20));
        QPalette palette17;
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush2);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush3);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush4);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush5);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush6);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush7);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush6);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush7);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush6);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush8);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush9);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush2);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush3);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush4);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush5);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush6);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush7);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush6);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush7);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush6);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush8);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush9);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush4);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush2);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush3);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush4);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush5);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush4);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush7);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush4);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush6);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush1);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush9);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        autoSave->setPalette(palette17);
        autoSave->setFont(font);

        retranslateUi(adcRecord);

        QMetaObject::connectSlotsByName(adcRecord);
    } // setupUi

    void retranslateUi(QWidget *adcRecord)
    {
        adcRecord->setWindowTitle(QCoreApplication::translate("adcRecord", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("adcRecord", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        rdAdcFreq_2->setText(QCoreApplication::translate("adcRecord", "SRAM\350\256\260\345\275\225\344\273\252(\351\200\237\347\216\207\347\255\211\345\220\214ADC)", nullptr));
        adcCheck1->setText(QCoreApplication::translate("adcRecord", "ADC_1", nullptr));
        adcCheck2->setText(QCoreApplication::translate("adcRecord", "ADC_2", nullptr));
        adcCheck3->setText(QCoreApplication::translate("adcRecord", "ADC_3", nullptr));
        adcCheck4->setText(QCoreApplication::translate("adcRecord", "ADC_4", nullptr));
        adcCheck5->setText(QCoreApplication::translate("adcRecord", "ADC_5", nullptr));
        adcCheck6->setText(QCoreApplication::translate("adcRecord", "ADC_6", nullptr));
        adcCheck7->setText(QCoreApplication::translate("adcRecord", "ADC_7", nullptr));
        adcCheck8->setText(QCoreApplication::translate("adcRecord", "ADC_8", nullptr));
        adcValue1->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        adcValue2->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        adcValue3->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        adcValue4->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        adcValue5->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        adcValue6->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        adcValue7->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        adcValue8->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        autoReadCheck->setText(QCoreApplication::translate("adcRecord", "\350\207\252\345\212\250\350\257\273\345\217\226(100\346\254\241\345\271\263\345\235\207)", nullptr));
        pushButton_4->setText(QCoreApplication::translate("adcRecord", "\350\257\273\345\217\226ADC(100\346\254\241\345\271\263\345\235\207)", nullptr));
        refreshCheckBox->setText(QCoreApplication::translate("adcRecord", "\345\210\267\346\226\260\346\263\242\345\275\242", nullptr));
        rdAdcFreq_3->setText(QCoreApplication::translate("adcRecord", "\351\207\207\346\240\267\347\216\207Hz", nullptr));
        rdAdcFreq_4->setText(QCoreApplication::translate("adcRecord", "\351\207\207\351\233\206\346\227\266\351\227\264(\346\257\253\347\247\222)", nullptr));
        setSramSamplingTime->setText(QCoreApplication::translate("adcRecord", "1000", nullptr));
        setAdcSamplingRate->setText(QCoreApplication::translate("adcRecord", "10000", nullptr));
        pushButton_3->setText(QCoreApplication::translate("adcRecord", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        pushButton_5->setText(QCoreApplication::translate("adcRecord", "\346\211\223\345\274\200\346\263\242\345\275\242", nullptr));
        pushButton_6->setText(QCoreApplication::translate("adcRecord", "\350\257\273\345\217\226\346\263\242\345\275\242", nullptr));
        pushButton_7->setText(QCoreApplication::translate("adcRecord", "\344\277\235\345\255\230\346\263\242\345\275\242", nullptr));
        intervalTime->setText(QCoreApplication::translate("adcRecord", "10", nullptr));
        pushButton_8->setText(QCoreApplication::translate("adcRecord", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        pushButton_9->setText(QCoreApplication::translate("adcRecord", "\344\277\235\345\255\230\346\263\242\345\275\242", nullptr));
        rdAdcFreq_15->setText(QCoreApplication::translate("adcRecord", "flash\350\256\260\345\275\225\344\273\252(\346\216\211\347\224\265\347\274\223\345\255\230, \346\234\200\345\244\2471KHz)", nullptr));
        pushButton_10->setText(QCoreApplication::translate("adcRecord", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        pushButton_11->setText(QCoreApplication::translate("adcRecord", "\346\211\223\345\274\200\346\263\242\345\275\242", nullptr));
        pushButton_12->setText(QCoreApplication::translate("adcRecord", "\350\257\273\345\217\226\346\263\242\345\275\242", nullptr));
        rdAdcFreq_21->setText(QCoreApplication::translate("adcRecord", "\351\207\207\346\240\267\351\227\264\351\232\224(\346\257\253\347\247\222)", nullptr));
        pushButton_13->setText(QCoreApplication::translate("adcRecord", "\346\270\205\351\231\244\346\263\242\345\275\242", nullptr));
        rdAdcFreq_5->setText(QCoreApplication::translate("adcRecord", "\345\267\262\351\207\207\351\233\206\346\227\266\351\227\264:", nullptr));
        sramHour->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        rdAdcFreq_6->setText(QCoreApplication::translate("adcRecord", "\346\227\266", nullptr));
        sramMinute->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        rdAdcFreq_8->setText(QCoreApplication::translate("adcRecord", "\345\210\206", nullptr));
        sramSecond->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        rdAdcFreq_7->setText(QCoreApplication::translate("adcRecord", "\347\247\222", nullptr));
        rdAdcFreq_16->setText(QCoreApplication::translate("adcRecord", "\345\267\262\351\207\207\351\233\206\346\227\266\351\227\264:", nullptr));
        flashHour->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        rdAdcFreq_19->setText(QCoreApplication::translate("adcRecord", "\346\227\266", nullptr));
        flashMinute->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        rdAdcFreq_12->setText(QCoreApplication::translate("adcRecord", "\345\210\206", nullptr));
        flashSecond->setText(QCoreApplication::translate("adcRecord", "N/A", nullptr));
        rdAdcFreq_14->setText(QCoreApplication::translate("adcRecord", "\347\247\222", nullptr));
        rdAdcFreq_9->setText(QCoreApplication::translate("adcRecord", "\345\234\250\347\272\277\350\277\236\347\273\255\350\256\260\345\275\225\344\273\252\346\214\201", nullptr));
        rdAdcFreq_10->setText(QCoreApplication::translate("adcRecord", "\344\270\216CPU\347\241\254\347\233\230\351\200\237\347\216\207\346\234\211\345\205\263,\351\205\214\346\203\205\350\260\203\346\205\242", nullptr));
        rdAdcFreq_11->setText(QCoreApplication::translate("adcRecord", "\351\205\214\346\203\205\351\231\215\344\275\216\351\207\207\346\240\267\347\216\207,\351\200\232\351\201\223\346\225\260", nullptr));
        ckb_RefreshWave->setText(QCoreApplication::translate("adcRecord", "\345\210\267\346\226\260\346\263\242\345\275\242", nullptr));
        pushButton_14->setText(QCoreApplication::translate("adcRecord", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        pushButton_15->setText(QCoreApplication::translate("adcRecord", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        filePath->setText(QCoreApplication::translate("adcRecord", "\350\257\267\351\200\211\346\213\251\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        pushButton_16->setText(QCoreApplication::translate("adcRecord", "\351\200\211\346\213\251\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        autoSave->setText(QCoreApplication::translate("adcRecord", "\350\207\252\345\212\250\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adcRecord: public Ui_adcRecord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADCRECORD_H
