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

#include "DataProcessing/ApplyMagCalib.h"
#include <QDebug>
#include <iostream>
#include <fstream>

ApplyMagCalib::ApplyMagCalib(Eigen::Matrix3d A,
                             Eigen::Vector3d w,
                             QObject* parent) : QObject(parent)
{
    m_A = A;
    m_w = w;

    applyCalib();

//    saveMatrix("./magCalib_A.dat",A);
//    saveMatrix("./magCalib_w.dat",w);
}

ApplyMagCalib::~ApplyMagCalib()
{

}

void ApplyMagCalib::loadCalib()
{
    MatrixXd A = Matrix3d::Identity();
    VectorXd w = Vector3d::Zero();

    if(!loadMatrix("./magCalib_A.dat",A))
    {
        A = Matrix3d::Identity();
    }

    if(!loadMatrix("./magCalib_w.dat",w))
    {
        w = Vector3d::Zero();
    }

    m_A = A;
    m_w = w;

    applyCalib();

//    qDebug("A =\n%s",matrixToString(A).toAscii().data());
//    qDebug("w =\n%s",matrixToString(w).toAscii().data());

}

void ApplyMagCalib::saveCalib()
{
    saveMatrix("./magCalib_A.dat",m_A);
    saveMatrix("./magCalib_w.dat",m_w);
}

void ApplyMagCalib::applyCalib()
{
    // ??????????????????????????????????????????????????????????? //
    //      calculate the model matrix M using the ellipsoid
    //           matrix A
    // ??????????????????????????????????????????????????????????? //

    m_M = Matrix3d::Identity();

    JacobiSVD<Matrix3d> svd(m_A,ComputeFullV);
    Vector3d Sig = svd.singularValues();
    Matrix3d V = svd.matrixV();

    m_M = ((Sig.cwiseSqrt()).asDiagonal())*(V.transpose());

    qDebug("============================================================");
    qDebug("    Magnetometer calibration                                ");
    qDebug("============================================================");
    qDebug("A =\n%s",matrixToString(m_A).toAscii().data());
    qDebug("M =\n%s",matrixToString(m_M).toAscii().data());
    qDebug("w =\n%s",matrixToString(m_w).toAscii().data());
    qDebug("============================================================\n");
}

QString ApplyMagCalib::matrixToString(const Eigen::MatrixXd& m) const
{
    std::ostringstream out;

    out.str("");
    out.clear();
    out << m;

    return QString(out.str().c_str());
}

template<class Matrix> bool ApplyMagCalib::saveMatrix(const QString& filename, const Matrix& m) const
{
    std::ofstream out(filename.toAscii().data(), std::ios::out | std::ios::binary | std::ios::trunc);

    typename Matrix::Index rows = m.rows();
    typename Matrix::Index cols = m.cols();

    out.write((char*) (&rows), sizeof(typename Matrix::Index));
    out.write((char*) (&cols), sizeof(typename Matrix::Index));
    out.write((char*) m.data(), rows*cols*sizeof(typename Matrix::Scalar));
    out.close();

    return !out.bad();
}

template<class Matrix> bool ApplyMagCalib::loadMatrix(const QString& filename, Matrix& m) const
{
    std::ifstream in(filename.toAscii().data(), std::ios::in | std::ios::binary);
    typename Matrix::Index rows = 0;
    typename Matrix::Index cols = 0;

    if(in.fail())
    {
        return false;
    }

    in.read((char*) (&rows),sizeof(typename Matrix::Index));
    in.read((char*) (&cols),sizeof(typename Matrix::Index));

    m.resize(rows, cols);

    in.read( (char *) m.data() , rows*cols*sizeof(typename Matrix::Scalar));
    in.close();

    return !in.bad();
}


void ApplyMagCalib::newCalib(Eigen::Matrix3d A, Eigen::Vector3d w)
{
    m_A = A;
    m_w = w;

    applyCalib();
    saveCalib();
}

void ApplyMagCalib::newRawImuData(ImuData d)
{
    const double* acc = d.acc();
    const double* gyro = d.gyro();
    const double* mag = d.mag();

    // mag calib;
    const Vector3d x = Map<const Vector3d>(mag);
    Vector3d y;

    // ??????????????????????????????????????????????????????????? //
    //      calculate the new mag measurements using
    //          the model matrix M and the offset w
    // ??????????????????????????????????????????????????????????? //

    y = m_M*(x - m_w);

    // ??????????????????????????????????????????????????????????? //

    Q_EMIT newImuData(ImuData(d.ts(),acc,gyro,y.data()));

}
