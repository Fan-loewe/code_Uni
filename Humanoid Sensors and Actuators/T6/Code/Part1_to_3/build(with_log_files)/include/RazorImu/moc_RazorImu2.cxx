/****************************************************************************
** Meta object code from reading C++ file 'RazorImu2.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/RazorImu/RazorImu2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RazorImu2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RazorImu2[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      23,   10,   10,   10, 0x05,
      38,   10,   10,   10, 0x05,
      54,   10,   10,   10, 0x05,
      75,   73,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   10,   10,   10, 0x0a,
     108,   10,   10,   10, 0x0a,
     121,   10,   10,   10, 0x08,
     139,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RazorImu2[] = {
    "RazorImu2\0\0connected()\0disconnected()\0"
    "connectFailed()\0disconnectFailed()\0d\0"
    "newRawImuData(ImuData)\0connect()\0"
    "disconnect()\0watchDogHandler()\0"
    "sensorDataHandler()\0"
};

void RazorImu2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RazorImu2 *_t = static_cast<RazorImu2 *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->connectFailed(); break;
        case 3: _t->disconnectFailed(); break;
        case 4: _t->newRawImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        case 5: _t->connect(); break;
        case 6: _t->disconnect(); break;
        case 7: _t->watchDogHandler(); break;
        case 8: _t->sensorDataHandler(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RazorImu2::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RazorImu2::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RazorImu2,
      qt_meta_data_RazorImu2, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RazorImu2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RazorImu2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RazorImu2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RazorImu2))
        return static_cast<void*>(const_cast< RazorImu2*>(this));
    return QObject::qt_metacast(_clname);
}

int RazorImu2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void RazorImu2::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RazorImu2::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void RazorImu2::connectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void RazorImu2::disconnectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void RazorImu2::newRawImuData(ImuData _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
