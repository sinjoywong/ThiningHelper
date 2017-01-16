/********************************************************************************
** Form generated from reading UI file 'slider_thining.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDER_THINING_H
#define UI_SLIDER_THINING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_slider_thining
{
public:

    void setupUi(QDialog *slider_thining)
    {
        if (slider_thining->objectName().isEmpty())
            slider_thining->setObjectName(QStringLiteral("slider_thining"));
        slider_thining->resize(400, 300);

        retranslateUi(slider_thining);

        QMetaObject::connectSlotsByName(slider_thining);
    } // setupUi

    void retranslateUi(QDialog *slider_thining)
    {
        slider_thining->setWindowTitle(QApplication::translate("slider_thining", "slider_thining", 0));
    } // retranslateUi

};

namespace Ui {
    class slider_thining: public Ui_slider_thining {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDER_THINING_H
