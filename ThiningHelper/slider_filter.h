#pragma once
#ifndef SLIDER_FILTER_H
#define SLIDER_FILTER_H

#include <QDialog>
#include "ui_slider_filter.h"
#include <qslider.h>
#include <qlineedit.h>
#include <QHBoxLayout>


class QLineEdit;
class QSlider;
class slider_filter : public QDialog
{
	Q_OBJECT

public:
	slider_filter(QWidget *parent = 0);
	~slider_filter();

private:
	Ui::slider_filter ui;

private:
	QLineEdit *Value_Slider_Filter;//滤波函数（medianBlur)中的参数
	QSlider *Slider_Filter;

	private slots:
	void setLineEditValue(int);
};

#endif // SLIDER_FILTER_H
