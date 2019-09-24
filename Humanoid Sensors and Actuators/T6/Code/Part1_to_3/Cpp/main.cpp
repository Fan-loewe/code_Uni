/*********************************************************************
* Compiler:         QT Creator V2.4.1
*                   QT V 4.8.0 (64 bit)
*
* Company:          Institute for Cognitive Systems
*                   Technical University of Munich
*
* Author:           Florian Bergner
*
* Compatibility:
*
* Software Version: V1.0
*
* Created:          05.05.2014
* Changed:          05.05.2014
*
* Comment:
*
*
********************************************************************/
#include <QDebug>

#include <QObject>
#include <QApplication>
#include <QList>
#include <QMetaType>

#include <stdio.h>

#include <RazorImu/RazorImu.h>
#include <RazorImu/RazorImu2.h>
#include <RazorImu/ImuDataLogger.h>
#include <DataProcessing/AdjustCosys.h>

#include <DataProcessing/ApplyAccCalib.h>
#include <DataProcessing/ApplyGyroCalib.h>
#include <DataProcessing/ApplyMagCalib.h>

#include <DataProcessing/CalcAccCalib.h>
#include <DataProcessing/CalcGyroCalib.h>
#include <DataProcessing/CalcMagCalib.h>



#include <Eigen/Eigen>
using namespace Eigen;

#include "mainwindow.h"


Q_DECLARE_METATYPE(Eigen::Matrix3d)
Q_DECLARE_METATYPE(Eigen::Vector3d)


QString matrixToString(const Eigen::MatrixXd& m)
{
    std::ostringstream out;

    out.str("");
    out.clear();
    out << m;

    return QString(out.str().c_str());
}


#define NUM_OF_THREADS  2

int main(int argc, char* argv[])
{
    int ret;

    fprintf(stdout,"ImuGuiTest\n");
    fflush(stdout);

    QApplication a(argc, argv);

    qRegisterMetaType<ImuData>("ImuData");

    qRegisterMetaType<Matrix3d>("Matrix3d");
    qRegisterMetaType<Vector3d>("Vector3d");

    QThread thread[NUM_OF_THREADS];


    MainWindow mw;

    //    RazorImu imu;
    RazorImu2 imu;

    ImuDataLogger log(".","test");
    ImuDataLogger logAccCalib(".","accCalib");
    ImuDataLogger logGyroCalib(".","gyroCalib");
    ImuDataLogger logMagCalib(".","magCalib");

//    RawToPhysical rp;

    ApplyAccCalib   aac;
    ApplyGyroCalib  agc;
    ApplyMagCalib   amc;

    CalcAccCalib    cac;
    CalcGyroCalib   cgc;
    CalcMagCalib    cmc;


    Matrix3d Aacc   = Matrix3d::Identity();
    Matrix3d Agyro  = Matrix3d::Identity();
    Matrix3d Amag   = Matrix3d::Identity();

    // ??????????????????????????????????????????????????????????? //
    //      find the transform matrices Aacc,Agyro,Amag
    //          to transform the calibrated data to the
    //          coordinate systems
    //
    //  NOTE: Each transformation matrix transforms the new
    //      coordinates to the old coordinates
    //
    //  Aacc = Tacc_new_old; tranformation of NEW with respect to OLD
    //
    // ??????????????????????????????????????????????????????????? //

    Matrix3d Rya;
    Rya<<0,0,1,0,1,0,-1,0,0;

    Matrix3d Rxa;
    Rxa<<1,0,0,0,0,1,0,-1,0;

    Aacc = Rya*Rxa;

    Matrix3d Rzg;
    Rzg<<0,-1,0,1,0,0,0,0,1;

    Matrix3d Rxg;
    Rxg<<1,0,0,0,-1,0,0,0,-1;

    Agyro = Rzg*Rxg;

    Matrix3d Invz;
    Invz<<1,0,0,0,1,0,0,0,-1;

    Matrix3d Rxm;
    Rxm<<1,0,0,0,0,1,0,-1,0;

    Amag = Invz*Rxm;

    // ??????????????????????????????????????????????????????????? //

    qDebug("============================================================");
    qDebug("    Transformations to adjust cosys after calibration       ");
    qDebug("============================================================");
    qDebug("Aacc =\n%s",matrixToString(Aacc).toAscii().data());
    qDebug("Agyro =\n%s",matrixToString(Agyro).toAscii().data());
    qDebug("Amag =\n%s",matrixToString(Amag).toAscii().data());
    qDebug("============================================================\n");

    // orthogonal => inverse <=> transpose
    AdjustCosys     adj(Aacc.transpose(),Agyro.transpose(),Amag.transpose());


    aac.loadCalib();
    agc.loadCalib();
    amc.loadCalib();


    imu.moveToThread(&thread[0]);
    log.moveToThread(&thread[1]);

//    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
//                     &rp, SLOT(newRawImuData(ImuData)));



    // imu
    QObject::connect(&mw, SIGNAL(connect()),
                     &imu, SLOT(connect()));

    QObject::connect(&mw, SIGNAL(disconnect()),
                     &imu, SLOT(disconnect()));


    QObject::connect(&imu, SIGNAL(connected()),
                     &mw, SLOT(connected()));


    QObject::connect(&imu, SIGNAL(connectFailed()),
                     &mw, SLOT(connectFailed()));

    QObject::connect(&imu, SIGNAL(disconnected()),
                     &mw, SLOT(disconnected()));

    QObject::connect(&imu, SIGNAL(disconnectFailed()),
                     &mw, SLOT(disconnectFailed()));


    // calc acc calib
    QObject::connect(&mw, SIGNAL(startAccCalib()),
                     &cac, SLOT(start()));

    QObject::connect(&mw, SIGNAL(stopAccCalib()),
                     &cac, SLOT(stop()));

    QObject::connect(&cac, SIGNAL(started()),
                     &mw, SLOT(accCalibStarted()));

    QObject::connect(&cac, SIGNAL(stopped()),
                     &mw, SLOT(accCalibStopped()));

    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
                     &cac, SLOT(newRawImuData(ImuData)));


    // calc gyro calib
    QObject::connect(&mw, SIGNAL(startGyroCalib()),
                     &cgc, SLOT(start()));

    QObject::connect(&mw, SIGNAL(stopGyroCalib()),
                     &cgc, SLOT(stop()));

    QObject::connect(&cgc, SIGNAL(started()),
                     &mw, SLOT(gyroCalibStarted()));

    QObject::connect(&cgc, SIGNAL(stopped()),
                     &mw, SLOT(gyroCalibStopped()));

    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
                     &cgc, SLOT(newRawImuData(ImuData)));


    // calc mag calib
    QObject::connect(&mw, SIGNAL(startMagCalib()),
                     &cmc, SLOT(start()));

    QObject::connect(&mw, SIGNAL(stopMagCalib()),
                     &cmc, SLOT(stop()));

    QObject::connect(&cmc, SIGNAL(started()),
                     &mw, SLOT(magCalibStarted()));

    QObject::connect(&cmc, SIGNAL(stopped()),
                     &mw, SLOT(magCalibStopped()));

    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
                     &cmc, SLOT(newRawImuData(ImuData)));




    // apply acc calib
    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
                     &aac, SLOT(newRawImuData(ImuData)));

    QObject::connect(&cac, SIGNAL(newCalib(Matrix3d,Vector3d)),
                     &aac, SLOT(newCalib(Matrix3d,Vector3d)));


    // apply gyro calib
    QObject::connect(&aac, SIGNAL(newImuData(ImuData)),
                     &agc, SLOT(newRawImuData(ImuData)));

    QObject::connect(&cgc, SIGNAL(newCalib(Matrix3d,Vector3d)),
                     &agc, SLOT(newCalib(Matrix3d,Vector3d)));


    // apply mag calib
    QObject::connect(&agc, SIGNAL(newImuData(ImuData)),
                     &amc, SLOT(newRawImuData(ImuData)));

    QObject::connect(&cmc, SIGNAL(newCalib(Matrix3d,Vector3d)),
                     &amc, SLOT(newCalib(Matrix3d,Vector3d)));


    // adjust cosys
    QObject::connect(&amc, SIGNAL(newImuData(ImuData)),
                     &adj, SLOT(newImuData(ImuData)));





    // acc calib log
    QObject::connect(&mw, SIGNAL(startAccCalib()),
                     &logAccCalib, SLOT(start()));

    QObject::connect(&mw, SIGNAL(stopAccCalib()),
                     &logAccCalib, SLOT(stop()));

    QObject::connect(&mw, SIGNAL(saveAccCalibLog(QString)),
                     &logAccCalib, SLOT(save(QString)));

    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
                     &logAccCalib, SLOT(newImuData(ImuData)));


    // gyro calib log
    QObject::connect(&mw, SIGNAL(startGyroCalib()),
                     &logGyroCalib, SLOT(start()));

    QObject::connect(&mw, SIGNAL(stopGyroCalib()),
                     &logGyroCalib, SLOT(stop()));

    QObject::connect(&mw, SIGNAL(saveGyroCalibLog(QString)),
                     &logGyroCalib, SLOT(save(QString)));

    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
                     &logGyroCalib, SLOT(newImuData(ImuData)));



    // mag calib log
    QObject::connect(&mw, SIGNAL(startMagCalib()),
                     &logMagCalib, SLOT(start()));

    QObject::connect(&mw, SIGNAL(stopMagCalib()),
                     &logMagCalib, SLOT(stop()));

    QObject::connect(&mw, SIGNAL(saveMagCalibLog(QString)),
                     &logMagCalib, SLOT(save(QString)));

    QObject::connect(&imu, SIGNAL(newRawImuData(ImuData)),
                     &logMagCalib, SLOT(newImuData(ImuData)));


    // log
    QObject::connect(&mw, SIGNAL(startLog()),
                     &log, SLOT(start()));

    QObject::connect(&mw, SIGNAL(stopLog()),
                     &log, SLOT(stop()));

    QObject::connect(&mw, SIGNAL(saveLog(QString)),
                     &log, SLOT(save(QString)));


    QObject::connect(&log, SIGNAL(started()),
                     &mw, SLOT(logStarted()));

    QObject::connect(&log, SIGNAL(stopped()),
                     &mw, SLOT(logStopped()));

    QObject::connect(&adj, SIGNAL(newAdjImuData(ImuData)),
                     &log, SLOT(newImuData(ImuData)));



    // main window
    QObject::connect(&mw,SIGNAL(finished()),&a,SLOT(quit()));

    QObject::connect(&adj, SIGNAL(newAdjImuData(ImuData)),
                     &mw, SLOT(newRawImuData(ImuData)));


//    QObject::connect(&rp, SIGNAL(newPhyImuData(ImuData)),
//                     &log, SLOT(newImuData(ImuData)));

    mw.show();


    for(int i=0; i<NUM_OF_THREADS; i++)
    {
        thread[i].start();
    }

    ret = a.exec();

    qDebug() << "exit event loop";

    for(int i=0; i<NUM_OF_THREADS; i++)
    {
        thread[i].exit();
    }

    for(int i=0; i<NUM_OF_THREADS; i++)
    {
        thread[i].wait(100);
    }


    qDebug() << "exit program";

    return ret;
}
