#ifndef SLIDER_THINING_H
#define SLIDER_THINING_H

#include <QDialog>
#include "ui_slider_thining.h"
#include <qslider.h>
#include <qlineedit.h>
#include <QHBoxLayout>
#include <qlabel.h>
class slider_thining : public QDialog
{
	Q_OBJECT

public:
	slider_thining(QWidget *parent = 0);
	~slider_thining();
	//void on_mouse(int event, int x, int y, int flags, void *ustc);
	static void on_mouse(int event, int x, int y, int flags, void* param);
private:
	Ui::slider_thining ui;

private:
	QLineEdit *Value_Slider_Thining;
	QSlider *Slider_Thining;
	QLabel *label3;
	private slots:
	void setThiningLineEditValue(int);
	
};

#endif // SLIDER_THINING_H
