/****************************************************************************
** Meta object code from reading C++ file 'FtdiPort.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/RazorImu/FtdiPort.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FtdiPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FtdiPort[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      28,   22,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FtdiPort[] = {
    "FtdiPort\0\0readyRead()\0error\0"
    "error(FtdiPort::FtdiPortError)\0"
};

void FtdiPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FtdiPort *_t = static_cast<FtdiPort *>(_o);
        switch (_id) {
        case 0: _t->readyRead(); break;
        case 1: _t->error((*reinterpret_cast< FtdiPort::FtdiPortError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FtdiPort::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FtdiPort::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FtdiPort,
      qt_meta_data_FtdiPort, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FtdiPort::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FtdiPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FtdiPort::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FtdiPort))
        return static_cast<void*>(const_cast< FtdiPort*>(this));
    return QThread::qt_metacast(_clname);
}

int FtdiPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FtdiPort::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FtdiPort::error(FtdiPort::FtdiPortError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
