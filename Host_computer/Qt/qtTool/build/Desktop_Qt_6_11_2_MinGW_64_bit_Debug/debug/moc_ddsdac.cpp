/****************************************************************************
** Meta object code from reading C++ file 'ddsdac.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ddsdac.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ddsdac.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6ddsDacE_t {};
} // unnamed namespace

template <> constexpr inline auto ddsDac::qt_create_metaobjectdata<qt_meta_tag_ZN6ddsDacE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ddsDac",
        "sig_ddsDacNetSend",
        "",
        "quint8*",
        "txData",
        "len",
        "sig_ddsDacUsbSend",
        "on_pushButton_2_clicked",
        "on_ckb_dc1_clicked",
        "on_ckb_sin1_clicked",
        "on_ckb_dc2_clicked",
        "on_ckb_dc3_clicked",
        "on_ckb_dc4_clicked",
        "on_ckb_sin2_clicked",
        "on_ckb_sin3_clicked",
        "on_ckb_sin4_clicked",
        "on_ckb_triangle1_clicked",
        "on_ckb_triangle2_clicked",
        "on_ckb_triangle3_clicked",
        "on_ckb_triangle4_clicked",
        "on_ckb_square1_clicked",
        "on_ckb_square2_clicked",
        "on_ckb_square3_clicked",
        "on_ckb_square4_clicked",
        "on_ckb_dds1_clicked",
        "on_ckb_dds2_clicked",
        "on_ckb_dds3_clicked",
        "on_ckb_dds4_clicked",
        "on_ckb_stop1_clicked",
        "on_ckb_stop2_clicked",
        "on_ckb_stop3_clicked",
        "on_ckb_stop4_clicked",
        "on_pushButton_13_clicked",
        "on_pushButton_11_clicked",
        "on_pushButton_12_clicked",
        "on_pushButton_10_clicked",
        "on_pushButton_3_clicked",
        "on_pushButton_4_clicked",
        "on_pushButton_5_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_ddsDacNetSend'
        QtMocHelpers::SignalData<void(quint8 *, quint32)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::UInt, 5 },
        }}),
        // Signal 'sig_ddsDacUsbSend'
        QtMocHelpers::SignalData<void(quint8 *, quint32)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::UInt, 5 },
        }}),
        // Slot 'on_pushButton_2_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dc1_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_sin1_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dc2_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dc3_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dc4_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_sin2_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_sin3_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_sin4_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_triangle1_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_triangle2_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_triangle3_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_triangle4_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_square1_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_square2_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_square3_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_square4_clicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dds1_clicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dds2_clicked'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dds3_clicked'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_dds4_clicked'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_stop1_clicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_stop2_clicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_stop3_clicked'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ckb_stop4_clicked'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_13_clicked'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_11_clicked'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_12_clicked'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_10_clicked'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_3_clicked'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_4_clicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_5_clicked'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ddsDac, qt_meta_tag_ZN6ddsDacE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ddsDac::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ddsDacE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ddsDacE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6ddsDacE_t>.metaTypes,
    nullptr
} };

void ddsDac::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ddsDac *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_ddsDacNetSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        case 1: _t->sig_ddsDacUsbSend((*reinterpret_cast<std::add_pointer_t<quint8*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2]))); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_ckb_dc1_clicked(); break;
        case 4: _t->on_ckb_sin1_clicked(); break;
        case 5: _t->on_ckb_dc2_clicked(); break;
        case 6: _t->on_ckb_dc3_clicked(); break;
        case 7: _t->on_ckb_dc4_clicked(); break;
        case 8: _t->on_ckb_sin2_clicked(); break;
        case 9: _t->on_ckb_sin3_clicked(); break;
        case 10: _t->on_ckb_sin4_clicked(); break;
        case 11: _t->on_ckb_triangle1_clicked(); break;
        case 12: _t->on_ckb_triangle2_clicked(); break;
        case 13: _t->on_ckb_triangle3_clicked(); break;
        case 14: _t->on_ckb_triangle4_clicked(); break;
        case 15: _t->on_ckb_square1_clicked(); break;
        case 16: _t->on_ckb_square2_clicked(); break;
        case 17: _t->on_ckb_square3_clicked(); break;
        case 18: _t->on_ckb_square4_clicked(); break;
        case 19: _t->on_ckb_dds1_clicked(); break;
        case 20: _t->on_ckb_dds2_clicked(); break;
        case 21: _t->on_ckb_dds3_clicked(); break;
        case 22: _t->on_ckb_dds4_clicked(); break;
        case 23: _t->on_ckb_stop1_clicked(); break;
        case 24: _t->on_ckb_stop2_clicked(); break;
        case 25: _t->on_ckb_stop3_clicked(); break;
        case 26: _t->on_ckb_stop4_clicked(); break;
        case 27: _t->on_pushButton_13_clicked(); break;
        case 28: _t->on_pushButton_11_clicked(); break;
        case 29: _t->on_pushButton_12_clicked(); break;
        case 30: _t->on_pushButton_10_clicked(); break;
        case 31: _t->on_pushButton_3_clicked(); break;
        case 32: _t->on_pushButton_4_clicked(); break;
        case 33: _t->on_pushButton_5_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ddsDac::*)(quint8 * , quint32 )>(_a, &ddsDac::sig_ddsDacNetSend, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ddsDac::*)(quint8 * , quint32 )>(_a, &ddsDac::sig_ddsDacUsbSend, 1))
            return;
    }
}

const QMetaObject *ddsDac::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ddsDac::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ddsDacE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ddsDac::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void ddsDac::sig_ddsDacNetSend(quint8 * _t1, quint32 _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void ddsDac::sig_ddsDacUsbSend(quint8 * _t1, quint32 _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}
QT_WARNING_POP
