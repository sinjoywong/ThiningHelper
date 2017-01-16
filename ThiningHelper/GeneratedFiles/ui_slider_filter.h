/********************************************************************************
** Form generated from reading UI file 'slider_filter.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDER_FILTER_H
#define UI_SLIDER_FILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_slider_filter
{
public:

    void setupUi(QDialog *slider_filter)
    {
        if (slider_filter->objectName().isEmpty())
            slider_filter->setObjectName(QStringLiteral("slider_filter"));
        slider_filter->resize(400, 300);

        retranslateUi(slider_filter);

        QMetaObject::connectSlotsByName(slider_filter);
    } // setupUi

    void retranslateUi(QDialog *slider_filter)
    {
        slider_filter->setWindowTitle(QApplication::translate("slider_filter", "slider_filter", 0));
    } // retranslateUi

};

namespace Ui {
    class slider_filter: public Ui_slider_filter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDER_FILTER_H
