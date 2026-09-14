/********************************************************************************
** Form generated from reading UI file 'adcwave.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADCWAVE_H
#define UI_ADCWAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_adcWave
{
public:
    QPushButton *pushButton;
    QCustomPlot *waveform;
    QWidget *layoutWidget;
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
    QCheckBox *adcTrig1;
    QCheckBox *adcTrig2;
    QCheckBox *adcTrig3;
    QCheckBox *adcTrig4;
    QCheckBox *adcTrig5;
    QCheckBox *adcTrig6;
    QCheckBox *adcTrig7;
    QCheckBox *adcTrig8;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *Ybias1;
    QLineEdit *Ybias2;
    QLineEdit *Ybias4;
    QLineEdit *Ybias3;
    QLineEdit *Ybias6;
    QLineEdit *Ybias5;
    QLineEdit *Ybias7;
    QLineEdit *Ybias8;
    QLineEdit *setAdcSamplingRate;
    QLineEdit *trigValue;
    QLabel *rdAdcFreq;
    QLabel *rdTrigValue;
    QLineEdit *xAxisLen;
    QLabel *rdTrigValue_2;
    QLabel *rdAdcFreq_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *rdAdcFreq_3;
    QCheckBox *autoReadCheck;
    QLabel *rdAdcFreq_4;

    void setupUi(QWidget *adcWave)
    {
        if (adcWave->objectName().isEmpty())
            adcWave->setObjectName("adcWave");
        adcWave->resize(1400, 800);
        pushButton = new QPushButton(adcWave);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 70, 75, 23));
        waveform = new QCustomPlot(adcWave);
        waveform->setObjectName("waveform");
        waveform->setGeometry(QRect(260, 50, 1111, 721));
        layoutWidget = new QWidget(adcWave);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 150, 201, 214));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
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
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font.setPointSize(12);
        adcCheck1->setFont(font);

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

        verticalLayout->addWidget(adcCheck8);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        adcTrig1 = new QCheckBox(layoutWidget);
        adcTrig1->setObjectName("adcTrig1");
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        adcTrig1->setPalette(palette8);
        adcTrig1->setFont(font);

        verticalLayout_2->addWidget(adcTrig1);

        adcTrig2 = new QCheckBox(layoutWidget);
        adcTrig2->setObjectName("adcTrig2");
        adcTrig2->setFont(font);

        verticalLayout_2->addWidget(adcTrig2);

        adcTrig3 = new QCheckBox(layoutWidget);
        adcTrig3->setObjectName("adcTrig3");
        adcTrig3->setFont(font);

        verticalLayout_2->addWidget(adcTrig3);

        adcTrig4 = new QCheckBox(layoutWidget);
        adcTrig4->setObjectName("adcTrig4");
        adcTrig4->setFont(font);

        verticalLayout_2->addWidget(adcTrig4);

        adcTrig5 = new QCheckBox(layoutWidget);
        adcTrig5->setObjectName("adcTrig5");
        adcTrig5->setFont(font);

        verticalLayout_2->addWidget(adcTrig5);

        adcTrig6 = new QCheckBox(layoutWidget);
        adcTrig6->setObjectName("adcTrig6");
        adcTrig6->setFont(font);

        verticalLayout_2->addWidget(adcTrig6);

        adcTrig7 = new QCheckBox(layoutWidget);
        adcTrig7->setObjectName("adcTrig7");
        adcTrig7->setFont(font);

        verticalLayout_2->addWidget(adcTrig7);

        adcTrig8 = new QCheckBox(layoutWidget);
        adcTrig8->setObjectName("adcTrig8");
        adcTrig8->setFont(font);

        verticalLayout_2->addWidget(adcTrig8);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        Ybias1 = new QLineEdit(layoutWidget);
        Ybias1->setObjectName("Ybias1");

        verticalLayout_3->addWidget(Ybias1);

        Ybias2 = new QLineEdit(layoutWidget);
        Ybias2->setObjectName("Ybias2");

        verticalLayout_3->addWidget(Ybias2);

        Ybias4 = new QLineEdit(layoutWidget);
        Ybias4->setObjectName("Ybias4");

        verticalLayout_3->addWidget(Ybias4);

        Ybias3 = new QLineEdit(layoutWidget);
        Ybias3->setObjectName("Ybias3");

        verticalLayout_3->addWidget(Ybias3);

        Ybias6 = new QLineEdit(layoutWidget);
        Ybias6->setObjectName("Ybias6");

        verticalLayout_3->addWidget(Ybias6);

        Ybias5 = new QLineEdit(layoutWidget);
        Ybias5->setObjectName("Ybias5");

        verticalLayout_3->addWidget(Ybias5);

        Ybias7 = new QLineEdit(layoutWidget);
        Ybias7->setObjectName("Ybias7");

        verticalLayout_3->addWidget(Ybias7);

        Ybias8 = new QLineEdit(layoutWidget);
        Ybias8->setObjectName("Ybias8");

        verticalLayout_3->addWidget(Ybias8);


        horizontalLayout->addLayout(verticalLayout_3);

        setAdcSamplingRate = new QLineEdit(adcWave);
        setAdcSamplingRate->setObjectName("setAdcSamplingRate");
        setAdcSamplingRate->setGeometry(QRect(100, 420, 71, 21));
        trigValue = new QLineEdit(adcWave);
        trigValue->setObjectName("trigValue");
        trigValue->setGeometry(QRect(100, 470, 71, 21));
        rdAdcFreq = new QLabel(adcWave);
        rdAdcFreq->setObjectName("rdAdcFreq");
        rdAdcFreq->setGeometry(QRect(30, 430, 53, 15));
        rdAdcFreq->setFont(font);
        rdTrigValue = new QLabel(adcWave);
        rdTrigValue->setObjectName("rdTrigValue");
        rdTrigValue->setGeometry(QRect(30, 470, 53, 15));
        rdTrigValue->setFont(font);
        xAxisLen = new QLineEdit(adcWave);
        xAxisLen->setObjectName("xAxisLen");
        xAxisLen->setGeometry(QRect(310, 20, 113, 21));
        rdTrigValue_2 = new QLabel(adcWave);
        rdTrigValue_2->setObjectName("rdTrigValue_2");
        rdTrigValue_2->setGeometry(QRect(30, 450, 71, 16));
        rdTrigValue_2->setFont(font);
        rdAdcFreq_2 = new QLabel(adcWave);
        rdAdcFreq_2->setObjectName("rdAdcFreq_2");
        rdAdcFreq_2->setGeometry(QRect(30, 410, 53, 15));
        rdAdcFreq_2->setFont(font);
        pushButton_2 = new QPushButton(adcWave);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(180, 420, 41, 23));
        pushButton_3 = new QPushButton(adcWave);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(180, 470, 41, 23));
        rdAdcFreq_3 = new QLabel(adcWave);
        rdAdcFreq_3->setObjectName("rdAdcFreq_3");
        rdAdcFreq_3->setGeometry(QRect(170, 130, 53, 15));
        autoReadCheck = new QCheckBox(adcWave);
        autoReadCheck->setObjectName("autoReadCheck");
        autoReadCheck->setGeometry(QRect(20, 100, 101, 20));
        autoReadCheck->setFont(font);
        rdAdcFreq_4 = new QLabel(adcWave);
        rdAdcFreq_4->setObjectName("rdAdcFreq_4");
        rdAdcFreq_4->setGeometry(QRect(250, 20, 53, 15));

        retranslateUi(adcWave);

        QMetaObject::connectSlotsByName(adcWave);
    } // setupUi

    void retranslateUi(QWidget *adcWave)
    {
        adcWave->setWindowTitle(QCoreApplication::translate("adcWave", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("adcWave", "\350\257\273\345\217\226\346\263\242\345\275\242", nullptr));
        adcCheck1->setText(QCoreApplication::translate("adcWave", "ADC_1", nullptr));
        adcCheck2->setText(QCoreApplication::translate("adcWave", "ADC_2", nullptr));
        adcCheck3->setText(QCoreApplication::translate("adcWave", "ADC_3", nullptr));
        adcCheck4->setText(QCoreApplication::translate("adcWave", "ADC_4", nullptr));
        adcCheck5->setText(QCoreApplication::translate("adcWave", "ADC_5", nullptr));
        adcCheck6->setText(QCoreApplication::translate("adcWave", "ADC_6", nullptr));
        adcCheck7->setText(QCoreApplication::translate("adcWave", "ADC_7", nullptr));
        adcCheck8->setText(QCoreApplication::translate("adcWave", "ADC_8", nullptr));
        adcTrig1->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        adcTrig2->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        adcTrig3->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        adcTrig4->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        adcTrig5->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        adcTrig6->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        adcTrig7->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        adcTrig8->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221", nullptr));
        rdAdcFreq->setText(QCoreApplication::translate("adcWave", "N/A", nullptr));
        rdTrigValue->setText(QCoreApplication::translate("adcWave", "N/A", nullptr));
        rdTrigValue_2->setText(QCoreApplication::translate("adcWave", "\350\247\246\345\217\221\351\230\210\345\200\274", nullptr));
        rdAdcFreq_2->setText(QCoreApplication::translate("adcWave", "\351\207\207\346\240\267\347\216\207", nullptr));
        pushButton_2->setText(QCoreApplication::translate("adcWave", "\345\206\231", nullptr));
        pushButton_3->setText(QCoreApplication::translate("adcWave", "\345\206\231", nullptr));
        rdAdcFreq_3->setText(QCoreApplication::translate("adcWave", "Y\345\201\217\347\275\256", nullptr));
        autoReadCheck->setText(QCoreApplication::translate("adcWave", "\350\207\252\345\212\250\350\257\273\345\217\226", nullptr));
        rdAdcFreq_4->setText(QCoreApplication::translate("adcWave", "X\350\275\264\351\225\277\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adcWave: public Ui_adcWave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADCWAVE_H
