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

#include "DataProcessing/AdjustCosys.h"
#include <QDebug>
#include <iostream>

AdjustCosys::AdjustCosys(Matrix3d Aacc,
                         Matrix3d Agyro,
                         Matrix3d Amag,
                         QObject* parent) : QObject(parent)
{
    m_Aacc  = Aacc;
    m_Agyro = Agyro;
    m_Amag  = Amag;
}

AdjustCosys::~AdjustCosys()
{

}

void AdjustCosys::newImuData(ImuData d)
{
    const Vector3d x    = Map<const Vector3d>(d.acc());
    const Vector3d y    = Map<const Vector3d>(d.gyro());
    const Vector3d z    = Map<const Vector3d>(d.mag());

    Vector3d acc,gyro,mag;

    acc     = m_Aacc    * x;
    gyro    = m_Agyro   * y;
    mag     = m_Amag    * z;

    Q_EMIT newAdjImuData(ImuData(d.ts(),acc.data(),gyro.data(),mag.data()));

}
