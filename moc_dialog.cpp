/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dialog_t {
    QByteArrayData data[8];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dialog_t qt_meta_stringdata_dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "dialog"
QT_MOC_LITERAL(1, 7, 9), // "appendLog"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3), // "log"
QT_MOC_LITERAL(4, 22, 20), // "updateBlockChainList"
QT_MOC_LITERAL(5, 43, 15), // "handleAppendLog"
QT_MOC_LITERAL(6, 59, 26), // "handleUpdateBlockChainList"
QT_MOC_LITERAL(7, 86, 8) // "addBlock"

    },
    "dialog\0appendLog\0\0log\0updateBlockChainList\0"
    "handleAppendLog\0handleUpdateBlockChainList\0"
    "addBlock"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dialog[] = {

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
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   43,    2, 0x0a /* Public */,
       6,    0,   46,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dialog *_t = static_cast<dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->appendLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateBlockChainList(); break;
        case 2: _t->handleAppendLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->handleUpdateBlockChainList(); break;
        case 4: _t->addBlock(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (dialog::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dialog::appendLog)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (dialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dialog::updateBlockChainList)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dialog.data,
      qt_meta_data_dialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void dialog::appendLog(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void dialog::updateBlockChainList()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_dialog_controller_t {
    QByteArrayData data[7];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dialog_controller_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dialog_controller_t qt_meta_stringdata_dialog_controller = {
    {
QT_MOC_LITERAL(0, 0, 17), // "dialog_controller"
QT_MOC_LITERAL(1, 18, 20), // "resultReadyAppendLog"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 3), // "log"
QT_MOC_LITERAL(4, 44, 31), // "resultReadyUpdateBlockChainList"
QT_MOC_LITERAL(5, 76, 16), // "operateAppendLog"
QT_MOC_LITERAL(6, 93, 27) // "operateUpdateBlockChainList"

    },
    "dialog_controller\0resultReadyAppendLog\0"
    "\0log\0resultReadyUpdateBlockChainList\0"
    "operateAppendLog\0operateUpdateBlockChainList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dialog_controller[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   38,    2, 0x0a /* Public */,
       6,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void dialog_controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dialog_controller *_t = static_cast<dialog_controller *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReadyAppendLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->resultReadyUpdateBlockChainList(); break;
        case 2: _t->operateAppendLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->operateUpdateBlockChainList(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (dialog_controller::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dialog_controller::resultReadyAppendLog)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (dialog_controller::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dialog_controller::resultReadyUpdateBlockChainList)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject dialog_controller::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dialog_controller.data,
      qt_meta_data_dialog_controller,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *dialog_controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dialog_controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dialog_controller.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int dialog_controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void dialog_controller::resultReadyAppendLog(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void dialog_controller::resultReadyUpdateBlockChainList()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE