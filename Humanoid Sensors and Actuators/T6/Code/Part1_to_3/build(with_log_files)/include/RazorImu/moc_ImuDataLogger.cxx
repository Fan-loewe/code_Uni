/****************************************************************************
** Meta object code from reading C++ file 'ImuDataLogger.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/RazorImu/ImuDataLogger.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImuDataLogger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImuDataLogger[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      25,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   14,   14,   14, 0x0a,
      43,   14,   14,   14, 0x0a,
      52,   50,   14,   14, 0x0a,
      81,   72,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImuDataLogger[] = {
    "ImuDataLogger\0\0started()\0stopped()\0"
    "start()\0stop()\0d\0newImuData(ImuData)\0"
    "filename\0save(QString)\0"
};

void ImuDataLogger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImuDataLogger *_t = static_cast<ImuDataLogger *>(_o);
        switch (_id) {
        case 0: _t->started(); break;
        case 1: _t->stopped(); break;
        case 2: _t->start(); break;
        case 3: _t->stop(); break;
        case 4: _t->newImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        case 5: _t->save((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImuDataLogger::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImuDataLogger::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ImuDataLogger,
      qt_meta_data_ImuDataLogger, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImuDataLogger::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImuDataLogger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImuDataLogger::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImuDataLogger))
        return static_cast<void*>(const_cast< ImuDataLogger*>(this));
    return QObject::qt_metacast(_clname);
}

int ImuDataLogger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ImuDataLogger::started()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ImuDataLogger::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
