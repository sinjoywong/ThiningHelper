#include "thininghelper.h"
#include "includes.h"
#include <staticsInfo.h> 
#include "subwindow_statics.h"
#include <fstream>
#include <qmessagebox.h>
#include <QTextCodec.h>
void tst();

//global variables
extern cv::Mat src_thinned;
extern cv::Mat src_thinned_mapped;
cv::Mat src_gotInfo;
cv::Mat dst;
QString filename;
QLabel *label_img;
extern int EndPointNum;//返回的端点数目
extern int TriplePointNum;

QString qstring_EndPointNum;

ThiningHelper::ThiningHelper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//img.resize(2);
	ThiningHelper::iniUI();
	QLabel *label2 = new QLabel();//new
}

ThiningHelper::~ThiningHelper()
{

}
void ThiningHelper::iniUI()
{
	label_img = new QLabel(this);

	btn_open_img = new QPushButton(QStringLiteral("打开图像"));
	connect(btn_open_img, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_loadImage_clicked()));

	btn_slider_threshold = new QPushButton(QStringLiteral("[1]二值化图像"));
	connect(btn_slider_threshold, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_slider_threshold_clicked()));

	btn_filter_img = new QPushButton(QStringLiteral("[2]去除杂色"));
	connect(btn_filter_img, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_slider_filter_clicked()));

	btn_thining_img = new QPushButton(QStringLiteral("[3]处理图像"));
	connect(btn_thining_img, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_slider_thining_clicked()));

	btn_statics = new QPushButton(QStringLiteral("统计信息"));
	connect(btn_statics, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_staticsinfo_clicked()));

	btn_save_img = new QPushButton(QStringLiteral("保存图像"));
	connect(btn_save_img, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_saveImage_clicked()));

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(btn_open_img);
	buttonLayout->addWidget(btn_slider_threshold);
	buttonLayout->addWidget(btn_filter_img);
	buttonLayout->addWidget(btn_thining_img);
	buttonLayout->addWidget(btn_statics);
	buttonLayout->addWidget(btn_save_img);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(label_img);
	mainLayout->addLayout(buttonLayout);

	//show layout
	widget = new QWidget();
	widget->setLayout(mainLayout);
	this->setCentralWidget(widget);
	this->setWindowTitle(QStringLiteral("单晶筏化-解筏SEM图像连通数处理软件v1.0"));//Title
	this->setWindowIcon(QIcon(":/ThiningHelper/Resources/myico.ico"));

	QString backgroundpic = (":/ThiningHelper/Resources/backgroundpic1.jpg");
	showImg(backgroundpic);
	qDebug("[thininghelper] ln80, backgoundpic = %s ", backgroundpic);
	std::ofstream Save_statics;
	Save_statics.open("ConnectivityStatics.txt", std::ios::out | std::ios::app | std::ios::binary);
	Save_statics << "EndPointNum" << "\t" << "TriplePointNum" << "\t" << "Minus" << std::endl;
	Save_statics.close();
}

void ThiningHelper::on_pushButton_loadImage_clicked()
{
	filename = QFileDialog::getOpenFileName(this, tr("Open File"), 0, "Image files (*.png *.bmp *.jpg);;PNG (*.png);;BMP (*.bmp);;JPG (*.jpg)");
	showImg(filename);
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string filename_cv = code->fromUnicode(filename).data();
	//std::string filename_cv = filename.toStdString();
	cv::Mat src = cv::imread(filename_cv, cv::IMREAD_GRAYSCALE);
	cv::namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
	cv::imshow(WINDOW_NAME, src);
}

void ThiningHelper::on_pushButton_saveImage_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Image"),
		"",
		tr("JPEG Files (*.jpg)"));
	std::string save_filename = fileName.toStdString();
	if (!fileName.isNull())
	{
		cv::imwrite(save_filename, src_thinned_mapped);
		qDebug("[thininghelper.cpp] ln108, save Image clicked");
	}
	else
	{
		qDebug("[thininghelper.cpp] ln108, save Image Failed");
	}
}

void ThiningHelper::showImg(QString filename)
{
	if (filename.isEmpty())
		return;//TODO:QMessageBox提示出错
	show_img = new QImage;
	show_img->load(filename);
	label_img->setPixmap(QPixmap::fromImage(*show_img));
}
void ThiningHelper::on_pushButton_slider_threshold_clicked()
{
	w2.show();
	w3.hide();
	w4.hide();
	w5.hide();
}
void ThiningHelper::on_pushButton_slider_filter_clicked()
{
	w3.show();
	w2.hide();
	w4.hide();
	w5.hide();
}
void ThiningHelper::on_pushButton_slider_thining_clicked()
{
	w4.show();
	w3.hide();
	w5.hide();
	w2.hide();
}
void ThiningHelper::on_pushButton_staticsinfo_clicked()
{
	qDebug("[thininghelper.cpp ln145] EndPointNum = %d", EndPointNum);
	qDebug("[thininghelper.cpp ln145] TriplePointNum = %d", TriplePointNum);
	qstring_EndPointNum = QString::number(EndPointNum);//, 10);
	std::ofstream Save_statics;
	Save_statics.open("ConnectivityStatics.txt", std::ios::out | std::ios::app | std::ios::binary);

	if (Save_statics.is_open())
	{
	//	Save_statics << "EndPointNum" << "\t" << "TriplePointNum" << "\t" << "Minus" << std::endl;
		Save_statics << EndPointNum << "\t" << TriplePointNum << "\t" << (EndPointNum - TriplePointNum) << std::endl;
		Save_statics.close();
	}
	else
	{
		qDebug("[thininghelper.cpp] ln167, save statics failed.");
	}
	qDebug("qstring_EndPointNum = %s", qstring_EndPointNum);
	QMessageBox::about(NULL, QStringLiteral("保存数据"), QStringLiteral("数据已保存至软件根目录“ConnectivityStatics.txt”，请勿重复点击"));
	//w5.show();
	w2.hide();
	w3.hide();
	w4.hide();
}




