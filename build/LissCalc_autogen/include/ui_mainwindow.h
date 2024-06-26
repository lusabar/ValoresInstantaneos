/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_File_Ctrl_N;
    QAction *action1_1;
    QAction *action2_1;
    QAction *action1_3;
    QAction *action2_3;
    QAction *action3_4;
    QAction *action4_5;
    QAction *action5_6;
    QAction *actionSobre;
    QWidget *centralwidget;
    QSlider *phase_slider;
    QLineEdit *phase_txt;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *vamp_txt;
    QLineEdit *iamp_txt;
    QLabel *label_4;
    QCustomPlot *sine;
    QCustomPlot *liss;
    QCustomPlot *vector;
    QComboBox *freqList;
    QLabel *label_5;
    QLabel *logo;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAjuda;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1280, 720);
        MainWindow->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        actionNew_File_Ctrl_N = new QAction(MainWindow);
        actionNew_File_Ctrl_N->setObjectName(QString::fromUtf8("actionNew_File_Ctrl_N"));
        action1_1 = new QAction(MainWindow);
        action1_1->setObjectName(QString::fromUtf8("action1_1"));
        action1_1->setCheckable(true);
        action1_1->setChecked(true);
        action2_1 = new QAction(MainWindow);
        action2_1->setObjectName(QString::fromUtf8("action2_1"));
        action2_1->setCheckable(true);
        action1_3 = new QAction(MainWindow);
        action1_3->setObjectName(QString::fromUtf8("action1_3"));
        action1_3->setCheckable(true);
        action2_3 = new QAction(MainWindow);
        action2_3->setObjectName(QString::fromUtf8("action2_3"));
        action2_3->setCheckable(true);
        action3_4 = new QAction(MainWindow);
        action3_4->setObjectName(QString::fromUtf8("action3_4"));
        action3_4->setCheckable(true);
        action4_5 = new QAction(MainWindow);
        action4_5->setObjectName(QString::fromUtf8("action4_5"));
        action4_5->setCheckable(true);
        action5_6 = new QAction(MainWindow);
        action5_6->setObjectName(QString::fromUtf8("action5_6"));
        action5_6->setCheckable(true);
        actionSobre = new QAction(MainWindow);
        actionSobre->setObjectName(QString::fromUtf8("actionSobre"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        phase_slider = new QSlider(centralwidget);
        phase_slider->setObjectName(QString::fromUtf8("phase_slider"));
        phase_slider->setGeometry(QRect(20, 360, 251, 16));
        phase_slider->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        phase_slider->setMinimum(-90);
        phase_slider->setMaximum(90);
        phase_slider->setOrientation(Qt::Orientation::Horizontal);
        phase_txt = new QLineEdit(centralwidget);
        phase_txt->setObjectName(QString::fromUtf8("phase_txt"));
        phase_txt->setGeometry(QRect(300, 360, 71, 16));
        QFont font;
        font.setPointSize(8);
        phase_txt->setFont(font);
        phase_txt->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 330, 251, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 240, 251, 17));
        vamp_txt = new QLineEdit(centralwidget);
        vamp_txt->setObjectName(QString::fromUtf8("vamp_txt"));
        vamp_txt->setGeometry(QRect(300, 240, 71, 16));
        vamp_txt->setFont(font);
        vamp_txt->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        iamp_txt = new QLineEdit(centralwidget);
        iamp_txt->setObjectName(QString::fromUtf8("iamp_txt"));
        iamp_txt->setGeometry(QRect(300, 270, 71, 16));
        iamp_txt->setFont(font);
        iamp_txt->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 270, 251, 17));
        sine = new QCustomPlot(centralwidget);
        sine->setObjectName(QString::fromUtf8("sine"));
        sine->setGeometry(QRect(20, 390, 371, 281));
        liss = new QCustomPlot(centralwidget);
        liss->setObjectName(QString::fromUtf8("liss"));
        liss->setGeometry(QRect(400, 390, 371, 281));
        vector = new QCustomPlot(centralwidget);
        vector->setObjectName(QString::fromUtf8("vector"));
        vector->setGeometry(QRect(400, 60, 371, 321));
        freqList = new QComboBox(centralwidget);
        freqList->addItem(QString());
        freqList->addItem(QString());
        freqList->addItem(QString());
        freqList->addItem(QString());
        freqList->addItem(QString());
        freqList->addItem(QString());
        freqList->addItem(QString());
        freqList->setObjectName(QString::fromUtf8("freqList"));
        freqList->setGeometry(QRect(300, 300, 72, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 300, 251, 17));
        logo = new QLabel(centralwidget);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(20, 20, 351, 191));
        logo->setPixmap(QPixmap(QString::fromUtf8("../logo.png")));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAjuda = new QMenu(menubar);
        menuAjuda->setObjectName(QString::fromUtf8("menuAjuda"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAjuda->menuAction());
        menuAjuda->addAction(actionSobre);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "LissCalc", nullptr));
        actionNew_File_Ctrl_N->setText(QCoreApplication::translate("MainWindow", "New File (Ctrl+N)", nullptr));
        action1_1->setText(QCoreApplication::translate("MainWindow", "1:1", nullptr));
        action2_1->setText(QCoreApplication::translate("MainWindow", "1:2", nullptr));
        action1_3->setText(QCoreApplication::translate("MainWindow", "1:3", nullptr));
        action2_3->setText(QCoreApplication::translate("MainWindow", "2:3", nullptr));
        action3_4->setText(QCoreApplication::translate("MainWindow", "3:4", nullptr));
        action4_5->setText(QCoreApplication::translate("MainWindow", "4:5", nullptr));
        action5_6->setText(QCoreApplication::translate("MainWindow", "5:6", nullptr));
        actionSobre->setText(QCoreApplication::translate("MainWindow", "Sobre", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Selecionar \303\242ngulo de fase da corrente (\302\260)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Selecionar amplitude da tens\303\243o (V):", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Selecionar amplitude da corrente (A):", nullptr));
        freqList->setItemText(0, QCoreApplication::translate("MainWindow", "1:1", nullptr));
        freqList->setItemText(1, QCoreApplication::translate("MainWindow", "1:2", nullptr));
        freqList->setItemText(2, QCoreApplication::translate("MainWindow", "1:3", nullptr));
        freqList->setItemText(3, QCoreApplication::translate("MainWindow", "2:3", nullptr));
        freqList->setItemText(4, QCoreApplication::translate("MainWindow", "3:4", nullptr));
        freqList->setItemText(5, QCoreApplication::translate("MainWindow", "4:5", nullptr));
        freqList->setItemText(6, QCoreApplication::translate("MainWindow", "5:6", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Selecionar rela\303\247\303\243o entre frequ\303\252ncias (V:A)", nullptr));
        logo->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "Arquivo", nullptr));
        menuAjuda->setTitle(QCoreApplication::translate("MainWindow", "Ajuda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
