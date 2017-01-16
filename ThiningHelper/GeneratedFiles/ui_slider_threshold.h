/********************************************************************************
** Form generated from reading UI file 'slider_threshold.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDER_THRESHOLD_H
#define UI_SLIDER_THRESHOLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_slider_threshold
{
public:

    void setupUi(QWidget *slider_threshold)
    {
        if (slider_threshold->objectName().isEmpty())
            slider_threshold->setObjectName(QStringLiteral("slider_threshold"));
        slider_threshold->resize(400, 300);

        retranslateUi(slider_threshold);

        QMetaObject::connectSlotsByName(slider_threshold);
    } // setupUi

    void retranslateUi(QWidget *slider_threshold)
    {
        slider_threshold->setWindowTitle(QApplication::translate("slider_threshold", "slider_threshold", 0));
    } // retranslateUi

};

namespace Ui {
    class slider_threshold: public Ui_slider_threshold {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDER_THRESHOLD_H
