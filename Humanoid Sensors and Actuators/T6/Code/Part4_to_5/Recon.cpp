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
* Created:          26.05.2014
* Changed:
*
* Comment:
*
*
********************************************************************/

#include "Tasks/Recon.h"
#include <QDebug>

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
const QVector<Eigen::Vector3d> Recon::defaultPos(
        QVector<Eigen::Vector3d>()
        << Eigen::Vector3d( 12,     7,     0)*1e-3
        << Eigen::Vector3d( 12,    -7,     0)*1e-3
        << Eigen::Vector3d(-12,     7,     0)*1e-3
        << Eigen::Vector3d(-12,    -7,     0)*1e-3);

const QVector<Eigen::Vector3d> Recon::defaultRollAxis(
        QVector<Eigen::Vector3d>()
        << Eigen::Vector3d(-0.500,     0.866,     0)
        << Eigen::Vector3d( 0.500,     0.866,     0)
        << Eigen::Vector3d(-0.500,    -0.866,     0)
        << Eigen::Vector3d(-0.500,    -0.866,     0));

const QVector<Eigen::Vector3d> Recon::defaultPitchAxis(
        QVector<Eigen::Vector3d>()
        << Eigen::Vector3d( 0.866,    0.5,       0)
        << Eigen::Vector3d( 0.866,   -0.5,       0)
        << Eigen::Vector3d(-0.866,    0.5,       0)
        << Eigen::Vector3d(-0.866,   -0.5,       0));

const QVector<Eigen::Vector3d> Recon::defaultYawAxis(
        QVector<Eigen::Vector3d>()
        << Eigen::Vector3d(0,0,1)
        << Eigen::Vector3d(0,0,1)
        << Eigen::Vector3d(0,0,1)
        << Eigen::Vector3d(0,0,1));



Eigen::Vector3d Recon::getRPY(const Eigen::Matrix3d& r)
{
    Eigen::Vector3d rpy;

    rpy(0) = atan2(r(2,1),r(2,2));
    rpy(1) = atan2(-r(2,1), sqrt(r(2,1)*r(2,1) + r(2,2)*r(2,2)));
    rpy(2) = atan2(r(1,0),r(0,0));

    return rpy;
}

Eigen::Matrix3d Recon::rotRPY(const Eigen::Vector3d& rpy)
{
    Eigen::Matrix3d R;

    R  =        Eigen::AngleAxisd(rpy(2)/180.0*M_PI,    Eigen::Vector3d::UnitZ())
            *   Eigen::AngleAxisd(rpy(1)/180.0*M_PI,    Eigen::Vector3d::UnitY())
            *   Eigen::AngleAxisd(rpy(0)/180.0*M_PI,    Eigen::Vector3d::UnitX());

    return R;
}

QString Recon::matrixToString(const Eigen::MatrixXd& m)
{
    std::ostringstream out;

    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");

    out.str("");
    out.clear();
    out << m.format(CleanFmt);

    return QString(out.str().c_str());
}


Recon::Recon()
{
    moveToThread(&m_thread);
    m_thread.start();
}

Recon::~Recon()
{
    m_thread.exit();
    m_thread.wait(100);
}


void Recon::sampledData(SamplerData d)
{
    const int srcPort = 2;
    const int destPort = 3;

//    const int srcPort = 1;
//    const int destPort = 4;


    QVector<Skin::Cell::Organization> o;

    Eigen::Matrix3d Rd = Eigen::Matrix3d::Identity();

    Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
    Eigen::Vector3d p1 = Eigen::Vector3d::Zero();

    Eigen::Matrix3d R2 = Eigen::Matrix3d::Identity();
    Eigen::Vector3d p2 = Eigen::Vector3d::Zero();

    Eigen::MatrixXd A,B;
    Eigen::Matrix3d M;
    Eigen::Matrix3d U,V;
    Eigen::Matrix3d Sr = Eigen::Matrix3d::Identity();
    Eigen::Vector3d Sig;
    Eigen::Vector3d Sighat;
    Eigen::Matrix3d Srhat;
    Eigen::MatrixXd CC;
    Eigen::Vector3d rpy;
    Eigen::Vector3d r1;
    Eigen::Vector3d r2;
    //Eigen::JacobiSVD<Eigen::MatrixXd> svd;

    const QVector<int>& ids = d.cellIdList();

    int n = d.numberOfSamples()/d.numberOfCells();
    double sr33 = 0;

    A.resize(3,n);
    B.resize(3,n);

    int ind = 0;

    for(int p=1; p<=d.numberOfPoses(); p++)
    {
        const QVector<Eigen::Vector3d>& s1 = d.samples(ids.at(0),p);
        const QVector<Eigen::Vector3d>& s2 = d.samples(ids.at(1),p);

        if(s1.size() != s2.size())
        {
            qDebug("Invalid sampled data!");
            return;
        }

        // ??????????????????????????????????????????????????????????? //
        //      add normalized samples to Matrix A and B
        // ??????????????????????????????????????????????????????????? //

        for(int i=0; i<s1.size(); i++){
            Eigen::Vector3d Vs1= s1.at(i);
            Vs1.normalize();
            A.col(i)= Vs1;
        }

        for(int i=0; i<s2.size(); i++){
            Eigen::Vector3d Vs2= s2.at(i);
            Vs2.normalize();
            B.col(i)= Vs2;
        }


        ind=p*s1.size();

      // ??????????????????????????????????????????????????????????? //
    }

    if(ind != n)
    {
        qDebug("Invalid sampled data: ind = %d, n = %d",ind,n);
        return;
    }

    // ??????????????????????????????????????????????????????????? //
    //      use the procrustes algorithm and calculate
    //          the rotation matrix between cell 1 and cell 2
    // ??????????????????????????????????????????????????????????? //


    Rd = Eigen::Matrix3d::Identity();

    M=A*(B.transpose());

    Eigen::JacobiSVD<Eigen::Matrix3d> svd(M, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Sig = svd.singularValues();
    Sr = Sig.asDiagonal();
    U = svd.matrixU();
    V = svd.matrixV();
    CC=U*(V.transpose());
    double cc = CC.determinant();
    if (cc<0){cc=-1;}
    else if (cc>0){cc=1;}
    Sighat << 1,1,cc;
    Srhat = Sighat.asDiagonal();
    Rd = U*Srhat*(V.transpose());


    // ??????????????????????????????????????????????????????????? //

    qDebug("Rd =\n%s",matrixToString(Rd).toAscii().data());
    qDebug("rpy =\n%s",matrixToString(getRPY(Rd)/M_PI*180).toAscii().data());


    // ??????????????????????????????????????????????????????????? //
    //      calculate the absolute orientation R2 and
    //          position p2 of cell 2 using the determined
    //          rotation Rd, the given port vectors
    //
    //                  defaultPos.at(srcPort-1)
    //                  defaultPos.at(destPort-1)
    //
    //          which point from the cell center to the repective
    //          port and the absolute postion p1 and orientation R1 of cell 1
    // ??????????????????????????????????????????????????????????? //


    R2 = R1*Rd;
    //p2 = p1 + Eigen::Vector3d(0.40,0,0);
    r1=defaultPos.at(srcPort-1);
    r2=defaultPos.at(destPort-1);
    //p2 = p1+Rd*r1-Rd.inverse()*r2;
    p2 = p1+R1*r1-R2*r2;
    //p2 = p1+Rd*r1-Rd.inverse()*r2;


    // qDebug("i =%d",i);
    std::cout<<"R2:"<< R2<< "\np2:"<< p2 <<std::endl;

    // ??????????????????????????????????????????????????????????? //


    o.append(Skin::Cell::Organization(1,p1,R1));
    o.append(Skin::Cell::Organization(2,p2,R2));

    qDebug("new skin organization");

    emit newSkinOrganization(o);
}



