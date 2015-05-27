/****************************************************************************
** Meta object code from reading C++ file 'configdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../configdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConfigDialog_t {
    QByteArrayData data[10];
    char stringdata[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigDialog_t qt_meta_stringdata_ConfigDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ConfigDialog"
QT_MOC_LITERAL(1, 13, 15), // "sendItemDeleted"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "sendItemUpdated"
QT_MOC_LITERAL(4, 46, 10), // "changePage"
QT_MOC_LITERAL(5, 57, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 74, 7), // "current"
QT_MOC_LITERAL(7, 82, 8), // "previous"
QT_MOC_LITERAL(8, 91, 19), // "receiveItemDeletion"
QT_MOC_LITERAL(9, 111, 17) // "receiveItemUpdate"

    },
    "ConfigDialog\0sendItemDeleted\0\0"
    "sendItemUpdated\0changePage\0QListWidgetItem*\0"
    "current\0previous\0receiveItemDeletion\0"
    "receiveItemUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   43,    2, 0x0a /* Public */,
       8,    0,   48,    2, 0x0a /* Public */,
       9,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QBrush,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QBrush,    2,

       0        // eod
};

void ConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConfigDialog *_t = static_cast<ConfigDialog *>(_o);
        switch (_id) {
        case 0: _t->sendItemDeleted(); break;
        case 1: _t->sendItemUpdated((*reinterpret_cast< QBrush(*)>(_a[1]))); break;
        case 2: _t->changePage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 3: _t->receiveItemDeletion(); break;
        case 4: _t->receiveItemUpdate((*reinterpret_cast< QBrush(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ConfigDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigDialog::sendItemDeleted)) {
                *result = 0;
            }
        }
        {
            typedef void (ConfigDialog::*_t)(QBrush );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigDialog::sendItemUpdated)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConfigDialog.data,
      qt_meta_data_ConfigDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigDialog.stringdata))
        return static_cast<void*>(const_cast< ConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ConfigDialog::sendItemDeleted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ConfigDialog::sendItemUpdated(QBrush _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
