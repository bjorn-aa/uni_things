/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *btnOn;
    QPushButton *btnOff;
    QLabel *label_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_15;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *label_4;
    QLabel *lblStatus;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_3;
    QProgressBar *progressBar;
    QPushButton *btnMode;
    QPushButton *btnReboot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        MainWindow->setCursor(QCursor(Qt::PointingHandCursor));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 0, 991, 121));
        QFont font;
        font.setFamily(QString::fromUtf8("Aniron"));
        font.setPointSize(48);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        btnOn = new QPushButton(centralwidget);
        btnOn->setObjectName(QString::fromUtf8("btnOn"));
        btnOn->setGeometry(QRect(680, 130, 331, 71));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        btnOn->setFont(font1);
        btnOff = new QPushButton(centralwidget);
        btnOff->setObjectName(QString::fromUtf8("btnOff"));
        btnOff->setGeometry(QRect(680, 210, 331, 71));
        btnOff->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1110, 30, 61, 71));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../marvin.gif")));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(110, 130, 531, 521));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(gridLayoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font1);

        gridLayout->addWidget(label_15, 8, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        gridLayout->addWidget(label_6, 7, 1, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font1);

        gridLayout->addWidget(label_11, 1, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        lblStatus = new QLabel(gridLayoutWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setFont(font1);

        gridLayout->addWidget(lblStatus, 1, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);

        gridLayout->addWidget(label_8, 4, 1, 1, 1);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font1);

        gridLayout->addWidget(label_13, 6, 1, 1, 1);

        label_14 = new QLabel(gridLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font1);

        gridLayout->addWidget(label_14, 8, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);

        gridLayout->addWidget(label_10, 5, 1, 1, 1);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        gridLayout->addWidget(label_12, 6, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 9, 0, 1, 1);

        progressBar = new QProgressBar(gridLayoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(240, 50));
        progressBar->setValue(64);

        gridLayout->addWidget(progressBar, 9, 1, 1, 1);

        btnMode = new QPushButton(centralwidget);
        btnMode->setObjectName(QString::fromUtf8("btnMode"));
        btnMode->setGeometry(QRect(680, 290, 331, 71));
        btnMode->setFont(font1);
        btnReboot = new QPushButton(centralwidget);
        btnReboot->setObjectName(QString::fromUtf8("btnReboot"));
        btnReboot->setGeometry(QRect(680, 370, 331, 71));
        btnReboot->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "M.A.R.V.I.N. Console", nullptr));
        btnOn->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        btnOff->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        label_2->setText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "5.0 V", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "24.6 V", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "STATUS", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "BATTERY VOLTAGE", nullptr));
        lblStatus->setText(QCoreApplication::translate("MainWindow", "STOPPED", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "SELF-TEST", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "CONNECTED", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "12.1 V", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "5 V RAIL", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "CONTROLLER", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "PASSED", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "12 V RAIL", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "BATTERY LEVEL", nullptr));
        btnMode->setText(QCoreApplication::translate("MainWindow", "MANUAL", nullptr));
        btnReboot->setText(QCoreApplication::translate("MainWindow", "REBOOT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
