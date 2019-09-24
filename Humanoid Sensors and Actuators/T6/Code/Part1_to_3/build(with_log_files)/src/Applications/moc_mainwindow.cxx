/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Applications/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      23,   11,   11,   11, 0x05,
      34,   11,   11,   11, 0x05,
      53,   44,   11,   11, 0x05,
      70,   11,   11,   11, 0x05,
      86,   11,   11,   11, 0x05,
     101,   44,   11,   11, 0x05,
     126,   11,   11,   11, 0x05,
     143,   11,   11,   11, 0x05,
     159,   44,   11,   11, 0x05,
     185,   11,   11,   11, 0x05,
     201,   11,   11,   11, 0x05,
     216,   44,   11,   11, 0x05,
     241,   11,   11,   11, 0x05,
     251,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     264,   11,   11,   11, 0x08,
     281,   11,   11,   11, 0x08,
     301,   11,   11,   11, 0x08,
     316,   11,   11,   11, 0x08,
     334,   11,   11,   11, 0x08,
     351,   11,   11,   11, 0x08,
     368,   11,   11,   11, 0x08,
     391,   11,   11,   11, 0x08,
     413,   11,   11,   11, 0x08,
     438,   11,   11,   11, 0x08,
     462,   11,   11,   11, 0x08,
     485,   11,   11,   11, 0x08,
     511,   11,   11,   11, 0x08,
     534,   11,   11,   11, 0x08,
     556,   11,   11,   11, 0x08,
     581,   11,   11,   11, 0x0a,
     588,   11,   11,   11, 0x0a,
     600,   11,   11,   11, 0x0a,
     616,   11,   11,   11, 0x0a,
     631,   11,   11,   11, 0x0a,
     650,   11,   11,   11, 0x0a,
     663,   11,   11,   11, 0x0a,
     676,   11,   11,   11, 0x0a,
     694,   11,   11,   11, 0x0a,
     712,   11,   11,   11, 0x0a,
     731,   11,   11,   11, 0x0a,
     750,   11,   11,   11, 0x0a,
     768,   11,   11,   11, 0x0a,
     791,  786,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0finished()\0startLog()\0"
    "stopLog()\0filename\0saveLog(QString)\0"
    "startAccCalib()\0stopAccCalib()\0"
    "saveAccCalibLog(QString)\0startGyroCalib()\0"
    "stopGyroCalib()\0saveGyroCalibLog(QString)\0"
    "startMagCalib()\0stopMagCalib()\0"
    "saveMagCalibLog(QString)\0connect()\0"
    "disconnect()\0connectClicked()\0"
    "disconnectClicked()\0clearClicked()\0"
    "startLogClicked()\0stopLogClicked()\0"
    "saveLogClicked()\0startAccCalibClicked()\0"
    "stopAccCalibClicked()\0saveAccCalibLogClicked()\0"
    "startGyroCalibClicked()\0stopGyroCalibClicked()\0"
    "saveGyroCalibLogClicked()\0"
    "startMagCalibClicked()\0stopMagCalibClicked()\0"
    "saveMagCalibLogClicked()\0quit()\0"
    "connected()\0connectFailed()\0disconnected()\0"
    "disconnectFailed()\0logStarted()\0"
    "logStopped()\0accCalibStarted()\0"
    "accCalibStopped()\0gyroCalibStarted()\0"
    "gyroCalibStopped()\0magCalibStarted()\0"
    "magCalibStopped()\0data\0newRawImuData(ImuData)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->startLog(); break;
        case 2: _t->stopLog(); break;
        case 3: _t->saveLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->startAccCalib(); break;
        case 5: _t->stopAccCalib(); break;
        case 6: _t->saveAccCalibLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->startGyroCalib(); break;
        case 8: _t->stopGyroCalib(); break;
        case 9: _t->saveGyroCalibLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->startMagCalib(); break;
        case 11: _t->stopMagCalib(); break;
        case 12: _t->saveMagCalibLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->connect(); break;
        case 14: _t->disconnect(); break;
        case 15: _t->connectClicked(); break;
        case 16: _t->disconnectClicked(); break;
        case 17: _t->clearClicked(); break;
        case 18: _t->startLogClicked(); break;
        case 19: _t->stopLogClicked(); break;
        case 20: _t->saveLogClicked(); break;
        case 21: _t->startAccCalibClicked(); break;
        case 22: _t->stopAccCalibClicked(); break;
        case 23: _t->saveAccCalibLogClicked(); break;
        case 24: _t->startGyroCalibClicked(); break;
        case 25: _t->stopGyroCalibClicked(); break;
        case 26: _t->saveGyroCalibLogClicked(); break;
        case 27: _t->startMagCalibClicked(); break;
        case 28: _t->stopMagCalibClicked(); break;
        case 29: _t->saveMagCalibLogClicked(); break;
        case 30: _t->quit(); break;
        case 31: _t->connected(); break;
        case 32: _t->connectFailed(); break;
        case 33: _t->disconnected(); break;
        case 34: _t->disconnectFailed(); break;
        case 35: _t->logStarted(); break;
        case 36: _t->logStopped(); break;
        case 37: _t->accCalibStarted(); break;
        case 38: _t->accCalibStopped(); break;
        case 39: _t->gyroCalibStarted(); break;
        case 40: _t->gyroCalibStopped(); break;
        case 41: _t->magCalibStarted(); break;
        case 42: _t->magCalibStopped(); break;
        case 43: _t->newRawImuData((*reinterpret_cast< ImuData(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::startLog()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::stopLog()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::saveLog(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::startAccCalib()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MainWindow::stopAccCalib()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void MainWindow::saveAccCalibLog(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::startGyroCalib()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void MainWindow::stopGyroCalib()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void MainWindow::saveGyroCalibLog(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::startMagCalib()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void MainWindow::stopMagCalib()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void MainWindow::saveMagCalibLog(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::connect()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}

// SIGNAL 14
void MainWindow::disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}
QT_END_MOC_NAMESPACE
