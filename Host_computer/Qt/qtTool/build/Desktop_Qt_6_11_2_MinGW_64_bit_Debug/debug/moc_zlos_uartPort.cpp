/****************************************************************************
** Meta object code from reading C++ file 'zlos_uartPort.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../zlos_uartPort.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zlos_uartPort.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12zlosUartPortE_t {};
} // unnamed namespace

template <> constexpr inline auto zlosUartPort::qt_create_metaobjectdata<qt_meta_tag_ZN12zlosUartPortE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "zlosUartPort",
        "sigUartStarted",
        "",
        "sigUartStopped",
        "status",
        "sigUartReceived",
        "data",
        "uartStart",
        "uartSettings",
        "set",
        "uartStop",
        "uartSend",
        "quint8*",
        "len"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sigUartStarted'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sigUartStopped'
        QtMocHelpers::SignalData<void(int)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 },
        }}),
        // Signal 'sigUartReceived'
        QtMocHelpers::SignalData<void(QByteArray)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 6 },
        }}),
        // Slot 'uartStart'
        QtMocHelpers::SlotData<void(uartSettings)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'uartStop'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'uartSend'
        QtMocHelpers::SlotData<void(quint8 *, quint32)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 6 }, { QMetaType::UInt, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<zlosUartPort, qt_meta_tag_ZN12zlosUartPortE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject zlosUartPort::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPort::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12zlosUartPortE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12zlosUartPortE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12zlosUartPortE_t>.metaTypes,
    nullptr
} };

void zlosUartPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<zlosUartPort *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sigUartStarted(); break;
        case 1: _t->sigUartStopped((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->sigUartReceived((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 3: _t->uartStart((*reinterpret_cast<std::add_pointer_t<uartSettings>>(_a[1]))); break;
        case 4: _t->uartStop(); break;
        case 5: _t->uartSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (zlosUartPort::*)()>(_a, &zlosUartPort::sigUartStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (zlosUartPort::*)(int )>(_a, &zlosUartPort::sigUartStopped, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (zlosUartPort::*)(QByteArray )>(_a, &zlosUartPort::sigUartReceived, 2))
            return;
    }
}

const QMetaObject *zlosUartPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *zlosUartPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12zlosUartPortE_t>.strings))
        return static_cast<void*>(this);
    return QSerialPort::qt_metacast(_clname);
}

int zlosUartPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void zlosUartPort::sigUartStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void zlosUartPort::sigUartStopped(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void zlosUartPort::sigUartReceived(QByteArray _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
