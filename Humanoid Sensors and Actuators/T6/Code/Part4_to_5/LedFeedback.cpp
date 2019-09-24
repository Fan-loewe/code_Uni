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

#include "Tasks/LedFeedback.h"
#include <QDebug>


LedFeedback::LedFeedback()
{
    m_started = false;

    moveToThread(&m_thread);

    m_thread.start();
    m_timer.start(20);     // 50 Hz
}

LedFeedback::~LedFeedback()
{
    m_thread.exit();
    m_thread.wait(100);
}

void LedFeedback::start(int num)
{
    m_data.reserve(num);
    m_cellIdMap.clear();

    connect(&m_timer,SIGNAL(timeout()),this,SLOT(update()));

    m_started = true;
}

void LedFeedback::stop()
{
    disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(update()));
    m_started = false;
}

void LedFeedback::update()
{
    for(int i=0; i<m_data.size(); i++)
    {
        int id = m_data.at(i).cellId;
        const double prox = m_data.at(i).prox.at(0);
        const double* force = m_data.at(i).force.data();

        // ??????????????????????????????????????????????????????????? //
        //      change the led color according to touch event
        //          green   = no contact
        //          red     = proximity event
        //          blue    = force event (overrides proximity event)
        //
        //      if you want you can implement also visual feedback for
        //          vibrational or acceleration events
        // ??????????????????????????????????????????????????????????? //


            Skin::Cell::LedColor c = Skin::Cell::LedColor::Green;

            Skin::Cell::LedColor d = Skin::Cell::LedColor::Red;

            Skin::Cell::LedColor e = Skin::Cell::LedColor::Blue;


        // ??????????????????????????????????????????????????????????? //

        const double th1=0.02;
        const double th2=0.2;
        if (*force>= th1){
            emit changeLedColor(e,id);
        }
        else if (prox >= th2){
            emit changeLedColor(d,id);
        }
        else{
            emit changeLedColor(c,id);
        }
    }
}

void LedFeedback::newDataBunch(QVector<Skin::Cell::Data> d)
{
    if(!m_started)
    {
        return;
    }

    for(int i=0; i<d.size(); i++)
    {
        int id  = d.at(i).cellId;
        int ind = m_cellIdMap.value(id,-1);

        if(ind == -1)
        {
            m_cellIdMap.insert(id,m_data.size());
            m_data.append(d.at(i));
            continue;
        }

        m_data[ind] = d.at(i);
    }
}

