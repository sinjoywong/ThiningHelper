#ifndef SUBWINDOW_STATICS_H
#define SUBWINDOW_STATICS_H

#include <QDialog>
#include "ui_subwindow_statics.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qlabel.h>
#include <qwidget.h>
#include <qstring.h>

class subwindow_statics : public QDialog
{
	Q_OBJECT

public:
	subwindow_statics(QWidget *parent = 0);
	~subwindow_statics();

private:
	Ui::subwindow_statics ui;
private:
	QLabel *labelName_endPoint;
	QLabel *label_endPointNum;
	QLabel *labelName_triplePointNum;
	QLabel *label_triplePointNum;

	QWidget *widget;

	private slots:
	//void setThresholdLineEditValue(int)
};

#endif // SUBWINDOW_STATICS_H
