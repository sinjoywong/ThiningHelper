#pragma once
#ifndef SLIDER_THRESHOLD_H
#define SLIDER_THRESHOLD_H

#include <QWidget>
#include "ui_slider_threshold.h"
#include <qslider.h>
#include <qlineedit.h>
#include <QHBoxLayout>
#include <qlabel.h>
class slider_threshold : public QWidget
{
	Q_OBJECT

public:
	slider_threshold(QWidget *parent = 0);
	~slider_threshold();

private:
	Ui::slider_threshold ui;

private:

	QLineEdit *Value_Slider_Threshold;//滤波函数（medianBlur)中的参数
	QSlider *Slider_Threshold;
	QLabel *label2;

	private slots:
	void setThresholdLineEditValue(int);
};

#endif // SLIDER_THRESHOLD_H
