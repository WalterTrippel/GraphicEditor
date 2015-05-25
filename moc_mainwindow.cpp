/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "newImage"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "buttonLineAction"
QT_MOC_LITERAL(4, 38, 16), // "buttonRectAction"
QT_MOC_LITERAL(5, 55, 19), // "buttonEllipseAction"
QT_MOC_LITERAL(6, 75, 20), // "buttonTriangleAction"
QT_MOC_LITERAL(7, 96, 20), // "buttonPenColorAction"
QT_MOC_LITERAL(8, 117, 20), // "buttonPenWidthAction"
QT_MOC_LITERAL(9, 138, 10), // "buttonFill"
QT_MOC_LITERAL(10, 149, 9), // "showNames"
QT_MOC_LITERAL(11, 159, 9), // "hideNames"
QT_MOC_LITERAL(12, 169, 17), // "itemDoubleClicked"
QT_MOC_LITERAL(13, 187, 5), // "index"
QT_MOC_LITERAL(14, 193, 9), // "addedItem"
QT_MOC_LITERAL(15, 203, 4), // "name"
QT_MOC_LITERAL(16, 208, 10), // "deleteItem"
QT_MOC_LITERAL(17, 219, 8), // "closeTab"
QT_MOC_LITERAL(18, 228, 8), // "tabIndex"
QT_MOC_LITERAL(19, 237, 11) // "itemClicked"

    },
    "MainWindow\0newImage\0\0buttonLineAction\0"
    "buttonRectAction\0buttonEllipseAction\0"
    "buttonTriangleAction\0buttonPenColorAction\0"
    "buttonPenWidthAction\0buttonFill\0"
    "showNames\0hideNames\0itemDoubleClicked\0"
    "index\0addedItem\0name\0deleteItem\0"
    "closeTab\0tabIndex\0itemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    1,  104,    2, 0x08 /* Private */,
      14,    1,  107,    2, 0x08 /* Private */,
      16,    1,  110,    2, 0x08 /* Private */,
      17,    0,  113,    2, 0x08 /* Private */,
      17,    1,  114,    2, 0x08 /* Private */,
      19,    1,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QModelIndex,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::QModelIndex,   13,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->newImage(); break;
        case 1: _t->buttonLineAction(); break;
        case 2: _t->buttonRectAction(); break;
        case 3: _t->buttonEllipseAction(); break;
        case 4: _t->buttonTriangleAction(); break;
        case 5: _t->buttonPenColorAction(); break;
        case 6: _t->buttonPenWidthAction(); break;
        case 7: _t->buttonFill(); break;
        case 8: _t->showNames(); break;
        case 9: _t->hideNames(); break;
        case 10: _t->itemDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 11: _t->addedItem((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->deleteItem((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 13: _t->closeTab(); break;
        case 14: _t->closeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->itemClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "CanvasObserver"))
        return static_cast< CanvasObserver*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
