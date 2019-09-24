/****************************************************************************
** Meta object code from reading C++ file 'RazorImu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/RazorImu/RazorImu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RazorImu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RazorImu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      22,    9,    9,    9, 0x05,
      37,    9,    9,    9, 0x05,
      53,    9,    9,    9, 0x05,
      74,   72,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,    9,    9,    9, 0x0a,
     107,    9,    9,    9, 0x0a,
     120,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RazorImu[] = {
    "RazorImu\0\0connected()\0disconnected()\0"
    "connectFailed()\0disconnectFailed()\0d\0"
    "newRawImuData(ImuData)\0connect()\0"
    "disconnect()\0sensorDataHandler()\0"
};

void RazorImu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RazorImu *_t = static_cast<RazorImu *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->connectFailed(); break;
        case 3: _t->disconnectFailed(); break;
        case 4: _t->newRawImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        case 5: _t->connect(); break;
        case 6: _t->disconnect(); break;
        case 7: _t->sensorDataHandler(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RazorImu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RazorImu::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RazorImu,
      qt_meta_data_RazorImu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RazorImu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RazorImu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RazorImu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RazorImu))
        return static_cast<void*>(const_cast< RazorImu*>(this));
    return QObject::qt_metacast(_clname);
}

int RazorImu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void RazorImu::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RazorImu::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void RazorImu::connectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void RazorImu::disconnectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void RazorImu::newRawImuData(ImuData _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
