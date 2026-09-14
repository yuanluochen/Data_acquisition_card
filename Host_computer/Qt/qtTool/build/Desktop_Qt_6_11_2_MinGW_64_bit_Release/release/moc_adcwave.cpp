/****************************************************************************
** Meta object code from reading C++ file 'adcwave.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../adcwave.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adcwave.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7adcWaveE_t {};
} // unnamed namespace

template <> constexpr inline auto adcWave::qt_create_metaobjectdata<qt_meta_tag_ZN7adcWaveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "adcWave",
        "sig_adcWaveNetSend",
        "",
        "quint8*",
        "txData",
        "len",
        "sig_adcWaveUsbSend",
        "on_pushButton_clicked",
        "on_pushButton_2_clicked",
        "on_pushButton_3_clicked",
        "on_adcCheck1_clicked",
        "on_adcCheck2_clicked",
        "on_adcCheck3_clicked",
        "on_adcCheck4_clicked",
        "on_adcCheck5_clicked",
        "on_adcCheck6_clicked",
        "on_adcCheck7_clicked",
        "on_adcCheck8_clicked",
        "on_adcTrig1_clicked",
        "on_adcTrig2_clicked",
        "on_adcTrig3_clicked",
        "on_adcTrig4_clicked",
        "on_adcTrig5_clicked",
        "on_adcTrig6_clicked",
        "on_adcTrig7_clicked",
        "on_adcTrig8_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_adcWaveNetSend'
        QtMocHelpers::SignalData<void(quint8 *, quint32)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::UInt, 5 },
        }}),
        // Signal 'sig_adcWaveUsbSend'
        QtMocHelpers::SignalData<void(quint8 *, quint32)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::UInt, 5 },
        }}),
        // Slot 'on_pushButton_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_2_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_3_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck1_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck2_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck3_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck4_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck5_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck6_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck7_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcCheck8_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig1_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig2_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig3_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig4_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig5_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig6_clicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig7_clicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_adcTrig8_clicked'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<adcWave, qt_meta_tag_ZN7adcWaveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject adcWave::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7adcWaveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7adcWaveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7adcWaveE_t>.metaTypes,
    nullptr
} };

void adcWave::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<adcWave *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_adcWaveNetSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        case 1: _t->sig_adcWaveUsbSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        case 4: _t->on_pushButton_3_clicked(); break;
        case 5: _t->on_adcCheck1_clicked(); break;
        case 6: _t->on_adcCheck2_clicked(); break;
        case 7: _t->on_adcCheck3_clicked(); break;
        case 8: _t->on_adcCheck4_clicked(); break;
        case 9: _t->on_adcCheck5_clicked(); break;
        case 10: _t->on_adcCheck6_clicked(); break;
        case 11: _t->on_adcCheck7_clicked(); break;
        case 12: _t->on_adcCheck8_clicked(); break;
        case 13: _t->on_adcTrig1_clicked(); break;
        case 14: _t->on_adcTrig2_clicked(); break;
        case 15: _t->on_adcTrig3_clicked(); break;
        case 16: _t->on_adcTrig4_clicked(); break;
        case 17: _t->on_adcTrig5_clicked(); break;
        case 18: _t->on_adcTrig6_clicked(); break;
        case 19: _t->on_adcTrig7_clicked(); break;
        case 20: _t->on_adcTrig8_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (adcWave::*)(quint8 * , quint32 )>(_a, &adcWave::sig_adcWaveNetSend, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (adcWave::*)(quint8 * , quint32 )>(_a, &adcWave::sig_adcWaveUsbSend, 1))
            return;
    }
}

const QMetaObject *adcWave::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *adcWave::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7adcWaveE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int adcWave::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void adcWave::sig_adcWaveNetSend(quint8 * _t1, quint32 _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void adcWave::sig_adcWaveUsbSend(quint8 * _t1, quint32 _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}
QT_WARNING_POP
