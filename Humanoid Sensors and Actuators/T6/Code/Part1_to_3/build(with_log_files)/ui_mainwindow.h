/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbConnect;
    QPushButton *pbDisconnect;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbClear;
    QPushButton *pbClose;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pbStartLog;
    QPushButton *pbStartAccCalib;
    QPushButton *pbStartGyroCalib;
    QPushButton *pbStartMagCalib;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pbStopLog;
    QPushButton *pbStopAccCalib;
    QPushButton *pbStopGyroCalib;
    QPushButton *pbStopMagCalib;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pbSaveLog;
    QPushButton *pbSaveAccCalibLog;
    QPushButton *pbSaveGyroCalibLog;
    QPushButton *pbSaveMagCalibLog;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QCustomPlot *wAccPlot;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QCustomPlot *wGyroPlot;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QCustomPlot *wMagPlot;
    QSpacerItem *verticalSpacer_2;
    QPlainTextEdit *pteStatus;
    QSpacerItem *verticalSpacer_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pbConnect = new QPushButton(centralwidget);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));

        horizontalLayout->addWidget(pbConnect);

        pbDisconnect = new QPushButton(centralwidget);
        pbDisconnect->setObjectName(QString::fromUtf8("pbDisconnect"));

        horizontalLayout->addWidget(pbDisconnect);

        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbClear = new QPushButton(centralwidget);
        pbClear->setObjectName(QString::fromUtf8("pbClear"));

        horizontalLayout->addWidget(pbClear);

        pbClose = new QPushButton(centralwidget);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));

        horizontalLayout->addWidget(pbClose);


        verticalLayout_7->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pbStartLog = new QPushButton(centralwidget);
        pbStartLog->setObjectName(QString::fromUtf8("pbStartLog"));

        verticalLayout->addWidget(pbStartLog);

        pbStartAccCalib = new QPushButton(centralwidget);
        pbStartAccCalib->setObjectName(QString::fromUtf8("pbStartAccCalib"));

        verticalLayout->addWidget(pbStartAccCalib);

        pbStartGyroCalib = new QPushButton(centralwidget);
        pbStartGyroCalib->setObjectName(QString::fromUtf8("pbStartGyroCalib"));

        verticalLayout->addWidget(pbStartGyroCalib);

        pbStartMagCalib = new QPushButton(centralwidget);
        pbStartMagCalib->setObjectName(QString::fromUtf8("pbStartMagCalib"));

        verticalLayout->addWidget(pbStartMagCalib);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        pbStopLog = new QPushButton(centralwidget);
        pbStopLog->setObjectName(QString::fromUtf8("pbStopLog"));

        verticalLayout_5->addWidget(pbStopLog);

        pbStopAccCalib = new QPushButton(centralwidget);
        pbStopAccCalib->setObjectName(QString::fromUtf8("pbStopAccCalib"));

        verticalLayout_5->addWidget(pbStopAccCalib);

        pbStopGyroCalib = new QPushButton(centralwidget);
        pbStopGyroCalib->setObjectName(QString::fromUtf8("pbStopGyroCalib"));

        verticalLayout_5->addWidget(pbStopGyroCalib);

        pbStopMagCalib = new QPushButton(centralwidget);
        pbStopMagCalib->setObjectName(QString::fromUtf8("pbStopMagCalib"));

        verticalLayout_5->addWidget(pbStopMagCalib);


        horizontalLayout_2->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pbSaveLog = new QPushButton(centralwidget);
        pbSaveLog->setObjectName(QString::fromUtf8("pbSaveLog"));

        verticalLayout_6->addWidget(pbSaveLog);

        pbSaveAccCalibLog = new QPushButton(centralwidget);
        pbSaveAccCalibLog->setObjectName(QString::fromUtf8("pbSaveAccCalibLog"));

        verticalLayout_6->addWidget(pbSaveAccCalibLog);

        pbSaveGyroCalibLog = new QPushButton(centralwidget);
        pbSaveGyroCalibLog->setObjectName(QString::fromUtf8("pbSaveGyroCalibLog"));

        verticalLayout_6->addWidget(pbSaveGyroCalibLog);

        pbSaveMagCalibLog = new QPushButton(centralwidget);
        pbSaveMagCalibLog->setObjectName(QString::fromUtf8("pbSaveMagCalibLog"));

        verticalLayout_6->addWidget(pbSaveMagCalibLog);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        wAccPlot = new QCustomPlot(centralwidget);
        wAccPlot->setObjectName(QString::fromUtf8("wAccPlot"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wAccPlot->sizePolicy().hasHeightForWidth());
        wAccPlot->setSizePolicy(sizePolicy);
        wAccPlot->setMinimumSize(QSize(250, 200));
        wAccPlot->setBaseSize(QSize(0, 0));

        verticalLayout_2->addWidget(wAccPlot);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        wGyroPlot = new QCustomPlot(centralwidget);
        wGyroPlot->setObjectName(QString::fromUtf8("wGyroPlot"));
        sizePolicy.setHeightForWidth(wGyroPlot->sizePolicy().hasHeightForWidth());
        wGyroPlot->setSizePolicy(sizePolicy);
        wGyroPlot->setMinimumSize(QSize(250, 200));
        wGyroPlot->setBaseSize(QSize(0, 0));

        verticalLayout_3->addWidget(wGyroPlot);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_4->addWidget(label_3);

        wMagPlot = new QCustomPlot(centralwidget);
        wMagPlot->setObjectName(QString::fromUtf8("wMagPlot"));
        sizePolicy.setHeightForWidth(wMagPlot->sizePolicy().hasHeightForWidth());
        wMagPlot->setSizePolicy(sizePolicy);
        wMagPlot->setMinimumSize(QSize(250, 200));
        wMagPlot->setBaseSize(QSize(0, 0));

        verticalLayout_4->addWidget(wMagPlot);


        horizontalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_7->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer_2);

        pteStatus = new QPlainTextEdit(centralwidget);
        pteStatus->setObjectName(QString::fromUtf8("pteStatus"));
        pteStatus->setMinimumSize(QSize(0, 100));
        pteStatus->setMaximumSize(QSize(16777215, 150));
        pteStatus->setBaseSize(QSize(0, 0));
        pteStatus->setReadOnly(true);

        verticalLayout_7->addWidget(pteStatus);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer_5);

        MainWindow->setCentralWidget(centralwidget);
        pteStatus->raise();
        pbSaveMagCalibLog->raise();
        pbStartAccCalib->raise();
        pbStartGyroCalib->raise();
        pbStopGyroCalib->raise();
        pbStopAccCalib->raise();
        pbSaveGyroCalibLog->raise();
        pbSaveAccCalibLog->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pbConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        pbDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        pbClear->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        pbClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        pbStartLog->setText(QApplication::translate("MainWindow", "Start Log", 0, QApplication::UnicodeUTF8));
        pbStartAccCalib->setText(QApplication::translate("MainWindow", "Start Acc Calib", 0, QApplication::UnicodeUTF8));
        pbStartGyroCalib->setText(QApplication::translate("MainWindow", "Start Gyro Calib", 0, QApplication::UnicodeUTF8));
        pbStartMagCalib->setText(QApplication::translate("MainWindow", "Start Mag Calib", 0, QApplication::UnicodeUTF8));
        pbStopLog->setText(QApplication::translate("MainWindow", "Stop Log", 0, QApplication::UnicodeUTF8));
        pbStopAccCalib->setText(QApplication::translate("MainWindow", "Stop Acc Calib", 0, QApplication::UnicodeUTF8));
        pbStopGyroCalib->setText(QApplication::translate("MainWindow", "Stop Gyro Calib", 0, QApplication::UnicodeUTF8));
        pbStopMagCalib->setText(QApplication::translate("MainWindow", "Stop Mag Calib", 0, QApplication::UnicodeUTF8));
        pbSaveLog->setText(QApplication::translate("MainWindow", "Save Log", 0, QApplication::UnicodeUTF8));
        pbSaveAccCalibLog->setText(QApplication::translate("MainWindow", "Save Acc Calib Log", 0, QApplication::UnicodeUTF8));
        pbSaveGyroCalibLog->setText(QApplication::translate("MainWindow", "Save Gyro Calib Log", 0, QApplication::UnicodeUTF8));
        pbSaveMagCalibLog->setText(QApplication::translate("MainWindow", "Save Mag Calib Log", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Acc plot: [</span><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">ax</span><span style=\" font-size:12pt; font-weight:600;\">, </span><span style=\" font-size:12pt; font-weight:600; color:#00ff00;\">ay</span><span style=\" font-size:12pt; font-weight:600;\">, </span><span style=\" font-size:12pt; font-weight:600; color:#0000ff;\">az</span><span style=\" font-size:12pt; font-weight:600;\">]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Gyro plot: [</span><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">gx</span><span style=\" font-size:12pt; font-weight:600;\">, </span><span style=\" font-size:12pt; font-weight:600; color:#00ff00;\">gy</span><span style=\" font-size:12pt; font-weight:600;\">, </span><span style=\" font-size:12pt; font-weight:600; color:#0000ff;\">gz</span><span style=\" font-size:12pt; font-weight:600;\">]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Mag plot: [</span><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">mx</span><span style=\" font-size:12pt; font-weight:600;\">, </span><span style=\" font-size:12pt; font-weight:600; color:#00ff00;\">my</span><span style=\" font-size:12pt; font-weight:600;\">, </span><span style=\" font-size:12pt; font-weight:600; color:#0000ff;\">mz</span><span style=\" font-size:12pt; font-weight:600;\">]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
