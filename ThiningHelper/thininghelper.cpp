#include "thininghelper.h"
#include "includes.h"
#include <staticsInfo.h> 
#include "subwindow_statics.h"
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

ThiningHelper::ThiningHelper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//img.resize(2);
	ThiningHelper::iniUI();
//	tst();
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
//	gridLayout = new QGridLayout();
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
}

void tst()
{
	cv::Mat mat = cv::imread("E:\\Code_tst\\opencv_thining\\tstImg\\src.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat mat1 = cv::imread("E:\\Code_tst\\ThiningHelper\\ThiningHelper\\src_real.png", cv::IMREAD_GRAYSCALE);
	//QImage img =ThiningHelper::CvMat2QImage(mat);
	QImage img = CvMat2QImage(mat);
	QImage img1 = CvMat2QImage(mat1);
	QLabel *label = new QLabel();
	label->move(380, 50);
	label->setPixmap(QPixmap::fromImage(img));
	label->setPixmap(QPixmap::fromImage(img1));//测试可得，一个label可以显示多个QImage，并且是覆盖的
	label->resize(label->pixmap()->size());
	label->show();
}


void ThiningHelper::on_pushButton_loadImage_clicked()
{
	filename = QFileDialog::getOpenFileName(this, tr("Open File"), 0, "Image files (*.png *.bmp *.jpg);;PNG (*.png);;BMP (*.bmp);;JPG (*.jpg)");
	showImg(filename);
	std::string filename_cv = filename.toStdString();
	cv::Mat src = cv::imread(filename_cv, cv::IMREAD_GRAYSCALE);
	cv::imshow(WINDOW_NAME, src);
}

void ThiningHelper::on_pushButton_saveImage_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Files"),
		"",
		tr("Jpeg Files (*.jpg)"));
	std::string save_filename = fileName.toStdString();
	if (!fileName.isNull())
	{
		//fileName是文件名
		cv::imwrite(save_filename, src_thinned_mapped);
		qDebug("[thininghelper.cpp] ln108, save Image clicked");
	}
	else
	{
		//点的是取消
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
	//EndPointNum = returnEndCount(src_thinned, src_thinned);//此处的值未传到subwindow_statics.cpp中
	qDebug("[thininghelper.cpp ln145] EndPointNum = %d", EndPointNum);
	qDebug("[thininghelper.cpp ln145] TriplePointNum = %d", TriplePointNum);
	w5.show();
	w2.hide();
	w3.hide();
	w4.hide();
}
//cv::Mat --> QImage convert
//QImage ThiningHelper::CvMat2QImage(cv::Mat mat)
//{   //show the resultImage in result area;  
//	cv::Mat rgb;
//	QImage img;
//	if (mat.channels() == 3)    // RGB image  
//	{
//		cvtColor(mat, rgb, CV_BGR2RGB);
//		img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)  
//			rgb.cols, rgb.rows,
//			rgb.cols*rgb.channels(),   //new add  
//			QImage::Format_RGB888);
//	}
//	else                     // gray image  
//	{
//		img = QImage((const uchar*)(mat.data),
//			mat.cols, mat.rows,
//			mat.cols*mat.channels(),    //new add  
//			QImage::Format_Indexed8);
//	}
//	return img;
//}





