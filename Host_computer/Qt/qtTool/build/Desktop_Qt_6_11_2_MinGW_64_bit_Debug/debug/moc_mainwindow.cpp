/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "sigUartStart",
        "",
        "zlosUartPort::uartSettings",
        "uartSet",
        "sigUartStop",
        "sigUartSend",
        "quint8*",
        "txData",
        "len",
        "sigUartReceive",
        "str",
        "sigNetConnect",
        "zlosNetPort::netPortSettings",
        "netPortSet",
        "sigNetDisconnect",
        "sigNetSend",
        "sigNetRxData",
        "_rxValidMsg",
        "rxData",
        "on_openButton_clicked",
        "on_scanPort_clicked",
        "on_listWidget_itemSelectionChanged",
        "widgetCommucationInit",
        "on_netConnectBtn_clicked",
        "on_ckb_usb_clicked",
        "on_ckb_net_clicked",
        "started",
        "stoped",
        "status",
        "uartReceived",
        "data",
        "netConnectState",
        "flag",
        "netReceive",
        "usbSend",
        "netSend"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sigUartStart'
        QtMocHelpers::SignalData<void(zlosUartPort::uartSettings)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'sigUartStop'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sigUartSend'
        QtMocHelpers::SignalData<void(quint8 *, quint32)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::UInt, 9 },
        }}),
        // Signal 'sigUartReceive'
        QtMocHelpers::SignalData<void(QByteArray)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 11 },
        }}),
        // Signal 'sigNetConnect'
        QtMocHelpers::SignalData<void(zlosNetPort::netPortSettings)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Signal 'sigNetDisconnect'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sigNetSend'
        QtMocHelpers::SignalData<void(quint8 *, quint32)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::UInt, 9 },
        }}),
        // Signal 'sigNetRxData'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal '_rxValidMsg'
        QtMocHelpers::SignalData<void(quint8 *)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 19 },
        }}),
        // Slot 'on_openButton_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_scanPort_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_listWidget_itemSelectionChanged'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'widgetCommucationInit'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_netConnectBtn_clicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_usb_clicked'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_net_clicked'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'started'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stoped'
        QtMocHelpers::SlotData<void(int)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 29 },
        }}),
        // Slot 'uartReceived'
        QtMocHelpers::SlotData<void(QByteArray)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 31 },
        }}),
        // Slot 'netConnectState'
        QtMocHelpers::SlotData<void(bool)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 33 },
        }}),
        // Slot 'netReceive'
        QtMocHelpers::SlotData<void(QByteArray)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 31 },
        }}),
        // Slot 'usbSend'
        QtMocHelpers::SlotData<void(quint8 *, quint32)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::UInt, 9 },
        }}),
        // Slot 'netSend'
        QtMocHelpers::SlotData<void(quint8 *, quint32)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::UInt, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sigUartStart((*reinterpret_cast<std::add_pointer_t<zlosUartPort::uartSettings>>(_a[1]))); break;
        case 1: _t->sigUartStop(); break;
        case 2: _t->sigUartSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        case 3: _t->sigUartReceive((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 4: _t->sigNetConnect((*reinterpret_cast<std::add_pointer_t<zlosNetPort::netPortSettings>>(_a[1]))); break;
        case 5: _t->sigNetDisconnect(); break;
        case 6: _t->sigNetSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        case 7: _t->sigNetRxData(); break;
        case 8: _t->_rxValidMsg((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1]))); break;
        case 9: _t->on_openButton_clicked(); break;
        case 10: _t->on_scanPort_clicked(); break;
        case 11: _t->on_listWidget_itemSelectionChanged(); break;
        case 12: _t->widgetCommucationInit(); break;
        case 13: _t->on_netConnectBtn_clicked(); break;
        case 14: _t->on_ckb_usb_clicked(); break;
        case 15: _t->on_ckb_net_clicked(); break;
        case 16: _t->started(); break;
        case 17: _t->stoped((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->uartReceived((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 19: _t->netConnectState((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 20: _t->netReceive((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 21: _t->usbSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        case 22: _t->netSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(zlosUartPort::uartSettings )>(_a, &MainWindow::sigUartStart, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::sigUartStop, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(quint8 * , quint32 )>(_a, &MainWindow::sigUartSend, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(QByteArray )>(_a, &MainWindow::sigUartReceive, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(zlosNetPort::netPortSettings )>(_a, &MainWindow::sigNetConnect, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::sigNetDisconnect, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(quint8 * , quint32 )>(_a, &MainWindow::sigNetSend, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::sigNetRxData, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(quint8 * )>(_a, &MainWindow::_rxValidMsg, 8))
            return;
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sigUartStart(zlosUartPort::uartSettings _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MainWindow::sigUartStop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::sigUartSend(quint8 * _t1, quint32 _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void MainWindow::sigUartReceive(QByteArray _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void MainWindow::sigNetConnect(zlosNetPort::netPortSettings _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void MainWindow::sigNetDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::sigNetSend(quint8 * _t1, quint32 _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void MainWindow::sigNetRxData()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MainWindow::_rxValidMsg(quint8 * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}
QT_WARNING_POP
