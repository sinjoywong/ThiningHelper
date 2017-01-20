#include "slider_threshold.h"
#include "includes.h"
#include <qlabel.h>
#include "convertImageType.h"
#include <QTextCodec.h>
 cv::Mat src;
 cv::Mat src_thresholded;
 cv::Mat src_thresholded_mapped;
extern QString filename;
extern QLabel *label_img;

slider_threshold::slider_threshold(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	Value_Slider_Threshold = new QLineEdit("128");
	Slider_Threshold = new QSlider(Qt::Horizontal);
	Slider_Threshold->setMinimum(0);
	Slider_Threshold->setMaximum(255);
	Slider_Threshold->setValue(128);

	connect(Slider_Threshold, SIGNAL(valueChanged(int)), this, SLOT(setThresholdLineEditValue(int)));

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(Value_Slider_Threshold);
	layout->addWidget(Slider_Threshold);

	this->setLayout(layout);
	this->resize(255, 20);
	this->setWindowTitle(QStringLiteral("调整阈值"));
	this->setWindowIcon(QIcon(":/ThiningHelper/Resources/myico.ico"));
}

slider_threshold::~slider_threshold()
{

}

void slider_threshold::setThresholdLineEditValue(int value)
{
	cv::Mat src_thresholded_toQImage;
	int pos = Slider_Threshold->value();
	//Todo:在此处将QSlider的步长从整型转为更为精确的小数
	QString str = QString("%1").arg(pos);
	Value_Slider_Threshold->setText(str);
	//std::string cstr = filename.toStdString();//QString --> std::string
	std::string cstr = filename.toLocal8Bit();//QString --> std::string

	//QTextCodec *code = QTextCodec::codecForName("gb18030");
	//std::string cstr = code->fromUnicode(str).data();

	src = cv::imread(cstr, cv::IMREAD_GRAYSCALE);

	cv::threshold(src, src_thresholded, pos, 1, cv::THRESH_BINARY);
	src_thresholded_mapped = src_thresholded * 255;
	cv::imshow(WINDOW_NAME, src_thresholded_mapped);
//	cv::imwrite("src_thresholded.jpg",src_thresholded);
}