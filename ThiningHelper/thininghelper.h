#pragma once
#ifndef THININGHELPER_H
#define THININGHELPER_H

#include <string>

#include <QtWidgets/QMainWindow>
#include "ui_thininghelper.h"
#include "sstream"
#include "opencv.hpp"
#include "core.hpp"
#include "imgproc.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <highgui\highgui.hpp>

#include <qpushbutton.h>
#include <qwidget.h>
#include <qimage.h>
#include <qlabel.h>
#include <qfiledialog.h>
#include <qstring.h>
#include <qpainter.h>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <slider_filter.h>
#include <slider_threshold.h>
#include <slider_thining.h>
#include <subwindow_statics.h>
#include "convertImageType.h"
class ThiningHelper : public QMainWindow
{
	Q_OBJECT

public:
	ThiningHelper(QWidget *parent = 0);
	~ThiningHelper();

private:
	Ui::ThiningHelperClass ui;
private:
	QImage *show_img;

	QPushButton *btn_open_img;
	QPushButton *btn_save_img;

	QPushButton *btn_slider_threshold;//open sub-window slider_bio
	QPushButton *btn_threshold_img;//threshold img

	QPushButton *btn_slider_filter;
	QPushButton *btn_filter_img;
	
	QPushButton *btn_slider_thining;
	QPushButton *btn_thining_img;

	QPushButton *btn_statics;

	QWidget *widget;

private:
	void iniUI();
	void showImg(QString filename);
	
public:

private:
	slider_threshold w2;
	slider_filter w3;
	slider_thining w4;
	subwindow_statics w5;
private slots:
	void on_pushButton_loadImage_clicked();
	void on_pushButton_saveImage_clicked();

	void on_pushButton_slider_threshold_clicked();
	void on_pushButton_slider_filter_clicked();
	void on_pushButton_slider_thining_clicked();
	void on_pushButton_staticsinfo_clicked();
};
#endif // THININGHELPER_H
