/********************************************************************************
** Form generated from reading UI file 'RunCapooRun.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNCAPOORUN_H
#define UI_RUNCAPOORUN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RunCapooRunClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RunCapooRunClass)
    {
        if (RunCapooRunClass->objectName().isEmpty())
            RunCapooRunClass->setObjectName(QString::fromUtf8("RunCapooRunClass"));
        RunCapooRunClass->resize(600, 400);
        menuBar = new QMenuBar(RunCapooRunClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        RunCapooRunClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RunCapooRunClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RunCapooRunClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(RunCapooRunClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        RunCapooRunClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(RunCapooRunClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RunCapooRunClass->setStatusBar(statusBar);

        retranslateUi(RunCapooRunClass);

        QMetaObject::connectSlotsByName(RunCapooRunClass);
    } // setupUi

    void retranslateUi(QMainWindow *RunCapooRunClass)
    {
        RunCapooRunClass->setWindowTitle(QCoreApplication::translate("RunCapooRunClass", "RunCapooRun", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RunCapooRunClass: public Ui_RunCapooRunClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNCAPOORUN_H
