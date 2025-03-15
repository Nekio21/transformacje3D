/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ekran.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    Ekran *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_8;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider_6;
    QSlider *horizontalSlider_7;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSlider *horizontalSlider_4;
    QSlider *horizontalSlider_5;
    QSlider *horizontalSlider_9;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButton;
    QSlider *horizontalSlider_10;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(983, 627);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new Ekran(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 602, 526));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(650, 60, 261, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(verticalLayoutWidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMinimum(-1500);
        horizontalSlider->setMaximum(1500);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        horizontalSlider_2 = new QSlider(verticalLayoutWidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setMinimum(-1500);
        horizontalSlider_2->setMaximum(1500);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_2);

        horizontalSlider_8 = new QSlider(verticalLayoutWidget);
        horizontalSlider_8->setObjectName("horizontalSlider_8");
        horizontalSlider_8->setMinimum(100);
        horizontalSlider_8->setMaximum(1500);
        horizontalSlider_8->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_8);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(650, 170, 261, 91));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_3 = new QSlider(verticalLayoutWidget_2);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setMinimum(-360);
        horizontalSlider_3->setMaximum(360);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_3);

        horizontalSlider_6 = new QSlider(verticalLayoutWidget_2);
        horizontalSlider_6->setObjectName("horizontalSlider_6");
        horizontalSlider_6->setMinimum(-360);
        horizontalSlider_6->setMaximum(360);
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_6);

        horizontalSlider_7 = new QSlider(verticalLayoutWidget_2);
        horizontalSlider_7->setObjectName("horizontalSlider_7");
        horizontalSlider_7->setMinimum(-360);
        horizontalSlider_7->setMaximum(360);
        horizontalSlider_7->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_7);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(650, 300, 261, 101));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_4 = new QSlider(verticalLayoutWidget_3);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setMinimum(1);
        horizontalSlider_4->setMaximum(30);
        horizontalSlider_4->setValue(10);
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_4);

        horizontalSlider_5 = new QSlider(verticalLayoutWidget_3);
        horizontalSlider_5->setObjectName("horizontalSlider_5");
        horizontalSlider_5->setMinimum(1);
        horizontalSlider_5->setMaximum(30);
        horizontalSlider_5->setValue(10);
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_5);

        horizontalSlider_9 = new QSlider(verticalLayoutWidget_3);
        horizontalSlider_9->setObjectName("horizontalSlider_9");
        horizontalSlider_9->setMinimum(1);
        horizontalSlider_9->setMaximum(30);
        horizontalSlider_9->setValue(10);
        horizontalSlider_9->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_9);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(830, 520, 83, 29));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(650, 30, 101, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(650, 150, 101, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(650, 280, 101, 20));
        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(650, 450, 261, 61));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(verticalLayoutWidget_4);
        radioButton->setObjectName("radioButton");

        verticalLayout_4->addWidget(radioButton);

        horizontalSlider_10 = new QSlider(verticalLayoutWidget_4);
        horizontalSlider_10->setObjectName("horizontalSlider_10");
        horizontalSlider_10->setMinimum(-30);
        horizontalSlider_10->setMaximum(300);
        horizontalSlider_10->setValue(100);
        horizontalSlider_10->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(horizontalSlider_10);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(650, 410, 91, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 983, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "reset", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Translacja", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Rotacja", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Skala", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "perpektywa", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "perpektywa", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
