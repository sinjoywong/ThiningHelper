/********************************************************************************
** Form generated from reading UI file 'thininghelper.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THININGHELPER_H
#define UI_THININGHELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThiningHelperClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ThiningHelperClass)
    {
        if (ThiningHelperClass->objectName().isEmpty())
            ThiningHelperClass->setObjectName(QStringLiteral("ThiningHelperClass"));
        ThiningHelperClass->resize(600, 400);
        menuBar = new QMenuBar(ThiningHelperClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ThiningHelperClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ThiningHelperClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ThiningHelperClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ThiningHelperClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ThiningHelperClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ThiningHelperClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ThiningHelperClass->setStatusBar(statusBar);

        retranslateUi(ThiningHelperClass);

        QMetaObject::connectSlotsByName(ThiningHelperClass);
    } // setupUi

    void retranslateUi(QMainWindow *ThiningHelperClass)
    {
        ThiningHelperClass->setWindowTitle(QApplication::translate("ThiningHelperClass", "ThiningHelper", 0));
    } // retranslateUi

};

namespace Ui {
    class ThiningHelperClass: public Ui_ThiningHelperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THININGHELPER_H
