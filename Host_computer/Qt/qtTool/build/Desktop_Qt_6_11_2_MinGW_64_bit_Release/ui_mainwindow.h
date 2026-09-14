/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *scanPort;
    QComboBox *portName;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QLabel *label;
    QLabel *label_3;
    QPushButton *openButton;
    QCheckBox *ckb_usb;
    QCheckBox *ckb_net;
    QLabel *label_4;
    QLabel *label_2;
    QLineEdit *lnEt_port;
    QPushButton *netConnectBtn;
    QLineEdit *lnEt_ip;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1522, 852);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 201, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        groupBox->setFont(font);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 179, 30));
        layoutWidget->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        scanPort = new QPushButton(layoutWidget);
        scanPort->setObjectName("scanPort");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font1.setPointSize(12);
        scanPort->setFont(font1);

        horizontalLayout_2->addWidget(scanPort);

        portName = new QComboBox(layoutWidget);
        portName->setObjectName("portName");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font2.setPointSize(12);
        font2.setBold(false);
        portName->setFont(font2);

        horizontalLayout_2->addWidget(portName);

        listWidget = new QListWidget(centralwidget);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setTextAlignment(Qt::AlignCenter);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setTextAlignment(Qt::AlignCenter);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setTextAlignment(Qt::AlignCenter);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setTextAlignment(Qt::AlignCenter);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setTextAlignment(Qt::AlignCenter);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget);
        __qlistwidgetitem5->setTextAlignment(Qt::AlignCenter);
        __qlistwidgetitem5->setFont(font);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 130, 101, 331));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font3.setPointSize(15);
        font3.setBold(false);
        listWidget->setFont(font3);
        listWidget->setLayoutDirection(Qt::RightToLeft);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(110, 40, 1400, 800));
        stackedWidget->setFrameShape(QFrame::Panel);
        stackedWidget->setFrameShadow(QFrame::Raised);
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(1159, 0, 161, 71));
        label->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/LOGO/LABIO.png);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(-30, 660, 181, 101));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/LOGO/5.png);"));
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(210, 10, 91, 32));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font4.setPointSize(14);
        openButton->setFont(font4);
        ckb_usb = new QCheckBox(centralwidget);
        ckb_usb->setObjectName("ckb_usb");
        ckb_usb->setGeometry(QRect(30, 70, 71, 16));
        ckb_usb->setFont(font1);
        ckb_net = new QCheckBox(centralwidget);
        ckb_net->setObjectName("ckb_net");
        ckb_net->setGeometry(QRect(30, 90, 71, 16));
        ckb_net->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(310, 10, 20, 32));
        label_4->setFont(font4);
        label_4->setMidLineWidth(-3);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(530, 10, 40, 32));
        label_2->setFont(font4);
        label_2->setMidLineWidth(-3);
        label_2->setAlignment(Qt::AlignCenter);
        lnEt_port = new QLineEdit(centralwidget);
        lnEt_port->setObjectName("lnEt_port");
        lnEt_port->setGeometry(QRect(580, 10, 61, 26));
        lnEt_port->setFont(font4);
        lnEt_port->setLayoutDirection(Qt::LeftToRight);
        lnEt_port->setAlignment(Qt::AlignCenter);
        netConnectBtn = new QPushButton(centralwidget);
        netConnectBtn->setObjectName("netConnectBtn");
        netConnectBtn->setGeometry(QRect(650, 10, 75, 27));
        netConnectBtn->setFont(font4);
        lnEt_ip = new QLineEdit(centralwidget);
        lnEt_ip->setObjectName("lnEt_ip");
        lnEt_ip->setGeometry(QRect(340, 10, 191, 26));
        lnEt_ip->setFont(font4);
        lnEt_ip->setLayoutDirection(Qt::LeftToRight);
        lnEt_ip->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "zlTool", nullptr));
        groupBox->setTitle(QString());
        scanPort->setText(QCoreApplication::translate("MainWindow", "\346\211\253\346\217\217\344\270\262\345\217\243", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "\347\244\272\346\263\242\345\231\250", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "\350\256\260\345\275\225\344\273\252", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\346\272\220", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "\351\200\232\347\224\250IO", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("MainWindow", "MODBUS", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256 ", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QString());
        label_3->setText(QString());
        openButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        ckb_usb->setText(QCoreApplication::translate("MainWindow", "USB", nullptr));
        ckb_net->setText(QCoreApplication::translate("MainWindow", "\347\275\221\345\217\243", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "PORT", nullptr));
        lnEt_port->setText(QCoreApplication::translate("MainWindow", "10000", nullptr));
        netConnectBtn->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        lnEt_ip->setText(QCoreApplication::translate("MainWindow", "192.168.100.100", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
