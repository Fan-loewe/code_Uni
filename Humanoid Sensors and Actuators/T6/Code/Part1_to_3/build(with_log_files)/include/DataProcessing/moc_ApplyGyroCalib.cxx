/****************************************************************************
** Meta object code from reading C++ file 'ApplyGyroCalib.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/DataProcessing/ApplyGyroCalib.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ApplyGyroCalib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ApplyGyroCalib[] = {

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
      18,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   38,   15,   15, 0x0a,
      70,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ApplyGyroCalib[] = {
    "ApplyGyroCalib\0\0d\0newImuData(ImuData)\0"
    "A,w\0newCalib(Matrix3d,Vector3d)\0"
    "newRawImuData(ImuData)\0"
};

void ApplyGyroCalib::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApplyGyroCalib *_t = static_cast<ApplyGyroCalib *>(_o);
        switch (_id) {
        case 0: _t->newImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        case 1: _t->newCalib((*reinterpret_cast< Matrix3d(*)>(_a[1])),(*reinterpret_cast< Vector3d(*)>(_a[2]))); break;
        case 2: _t->newRawImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApplyGyroCalib::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApplyGyroCalib::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ApplyGyroCalib,
      qt_meta_data_ApplyGyroCalib, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplyGyroCalib::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplyGyroCalib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplyGyroCalib::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplyGyroCalib))
        return static_cast<void*>(const_cast< ApplyGyroCalib*>(this));
    return QObject::qt_metacast(_clname);
}

int ApplyGyroCalib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ApplyGyroCalib::newImuData(ImuData _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
