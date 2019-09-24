/****************************************************************************
** Meta object code from reading C++ file 'ApplyMagCalib.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/DataProcessing/ApplyMagCalib.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ApplyMagCalib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ApplyMagCalib[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   37,   14,   14, 0x0a,
      69,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ApplyMagCalib[] = {
    "ApplyMagCalib\0\0d\0newImuData(ImuData)\0"
    "A,w\0newCalib(Matrix3d,Vector3d)\0"
    "newRawImuData(ImuData)\0"
};

void ApplyMagCalib::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApplyMagCalib *_t = static_cast<ApplyMagCalib *>(_o);
        switch (_id) {
        case 0: _t->newImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        case 1: _t->newCalib((*reinterpret_cast< Matrix3d(*)>(_a[1])),(*reinterpret_cast< Vector3d(*)>(_a[2]))); break;
        case 2: _t->newRawImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApplyMagCalib::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApplyMagCalib::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ApplyMagCalib,
      qt_meta_data_ApplyMagCalib, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplyMagCalib::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplyMagCalib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplyMagCalib::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplyMagCalib))
        return static_cast<void*>(const_cast< ApplyMagCalib*>(this));
    return QObject::qt_metacast(_clname);
}

int ApplyMagCalib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ApplyMagCalib::newImuData(ImuData _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
