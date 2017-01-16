/********************************************************************************
** Form generated from reading UI file 'subwindow_statics.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWINDOW_STATICS_H
#define UI_SUBWINDOW_STATICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_subwindow_statics
{
public:

    void setupUi(QDialog *subwindow_statics)
    {
        if (subwindow_statics->objectName().isEmpty())
            subwindow_statics->setObjectName(QStringLiteral("subwindow_statics"));
        subwindow_statics->resize(400, 300);

        retranslateUi(subwindow_statics);

        QMetaObject::connectSlotsByName(subwindow_statics);
    } // setupUi

    void retranslateUi(QDialog *subwindow_statics)
    {
        subwindow_statics->setWindowTitle(QApplication::translate("subwindow_statics", "subwindow_statics", 0));
    } // retranslateUi

};

namespace Ui {
    class subwindow_statics: public Ui_subwindow_statics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW_STATICS_H
