/****************************************************************************
** Meta object code from reading C++ file 'CalcMagCalib.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/DataProcessing/CalcMagCalib.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CalcMagCalib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CalcMagCalib[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   14,   13,   13, 0x05,
      46,   13,   13,   13, 0x05,
      56,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   13,   13,   13, 0x0a,
      74,   13,   13,   13, 0x0a,
      83,   81,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CalcMagCalib[] = {
    "CalcMagCalib\0\0A,w\0newCalib(Matrix3d,Vector3d)\0"
    "started()\0stopped()\0start()\0stop()\0d\0"
    "newRawImuData(ImuData)\0"
};

void CalcMagCalib::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CalcMagCalib *_t = static_cast<CalcMagCalib *>(_o);
        switch (_id) {
        case 0: _t->newCalib((*reinterpret_cast< Matrix3d(*)>(_a[1])),(*reinterpret_cast< Vector3d(*)>(_a[2]))); break;
        case 1: _t->started(); break;
        case 2: _t->stopped(); break;
        case 3: _t->start(); break;
        case 4: _t->stop(); break;
        case 5: _t->newRawImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CalcMagCalib::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CalcMagCalib::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CalcMagCalib,
      qt_meta_data_CalcMagCalib, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CalcMagCalib::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CalcMagCalib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CalcMagCalib::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalcMagCalib))
        return static_cast<void*>(const_cast< CalcMagCalib*>(this));
    return QObject::qt_metacast(_clname);
}

int CalcMagCalib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CalcMagCalib::newCalib(Matrix3d _t1, Vector3d _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalcMagCalib::started()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CalcMagCalib::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
