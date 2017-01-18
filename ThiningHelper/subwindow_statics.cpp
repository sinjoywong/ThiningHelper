#include "subwindow_statics.h"
#include "includes.h"
#include <staticsInfo.h> 
#include <qfile.h>
#include <qfiledialog.h>

extern int EndPointNum;//返回的端点数目
extern int TriplePointNum;
extern cv::Mat src_thinned;
cv::Mat src_thinned_End_count;
cv::Mat src_thinned_Triple_count;

extern QString qstring_EndPointNum;
subwindow_statics::subwindow_statics(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	labelName_endPoint = new QLabel("End Point Num:", this);
	//labelName_endPoint->setStyleSheet("font-size:15px;color:light-red;font-weight:bold;font-syle:");
	
	//EndPointNum = returnEndCount(src_thinned, src_thinned_End_count); //此处有更改 2016.12.5
	//QString qstring_EndPointNum = QString::number(EndPointNum, 10);
	label_endPointNum = new QLabel(qstring_EndPointNum, this);
	qDebug("[subwindow_statics.cpp] ln24, end point num %d", EndPointNum);

	labelName_triplePointNum = new QLabel("Triple Point Num:", this);
	labelName_triplePointNum->setStyleSheet("font-size:15px;color:light-red;font-weight:bold;font-syle:");
	//QString qstring_EndPointNum = QString::number(EndPointNum, 10);

	//TriplePointNum = returnTripleCount(src_thinned, src_thinned_Triple_count);//此处src_thining不应该从上一步开始，因为上一步已经加入了标记！！！
	QString qstring_TriplePointNum = QString::number(TriplePointNum, 10);
	label_triplePointNum = new QLabel(qstring_TriplePointNum, this);
	qDebug("[subwindow_statics.cpp] ln24, end point num %d", TriplePointNum);

	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(labelName_endPoint);
	layout1->addWidget(label_endPointNum);

	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(labelName_triplePointNum);
	layout2->addWidget(label_triplePointNum);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(layout1);
	mainLayout->addLayout(layout2);

	//show layout 
	widget = new QWidget();
//	widget->setLayout(mainLayout);

	setLayout(mainLayout);
//	this->resize(255, 20);
	this->setWindowTitle("Statics Info");
	this->setMaximumSize(250, 100);
	this->setMinimumSize(250, 100);
}

subwindow_statics::~subwindow_statics()
{

}
