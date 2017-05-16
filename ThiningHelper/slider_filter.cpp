#include "slider_filter.h"
#include "includes.h"


 cv::Mat src_filtered;
 cv::Mat src_filtered_mapped;
extern cv::Mat src_thresholded;

slider_filter::slider_filter(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Value_Slider_Filter = new QLineEdit("5");
	Slider_Filter = new QSlider(Qt::Horizontal);
	Slider_Filter->setMinimum(0);
	Slider_Filter->setMaximum(20);
	Slider_Filter->setValue(5);

	connect(Slider_Filter, SIGNAL(valueChanged(int)), this, SLOT(setLineEditValue(int)));

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(Value_Slider_Filter);
	layout->addWidget(Slider_Filter);

	this->setLayout(layout);
	this->resize(200, 50);
	this->setWindowTitle(QStringLiteral("调整滤波强度"));
	this->setWindowIcon(QIcon(":/ThiningHelper/Resources/myico.ico"));

}

slider_filter::~slider_filter()
{

}

void slider_filter::setLineEditValue(int value) {
	int pos = Slider_Filter->value();
	pos = getMeanNum(pos);
	QString str = QString("%1").arg(pos);
	Value_Slider_Filter->setText(str);

	cv::medianBlur(src_thresholded, src_filtered, pos);//均值滤波
	 //TODO:另外几种滤波的选择

	//这种方法很取巧。因为后期细化需要二值图像，所以需要再次threshold,直接读取会出现不可描述的错误，所以灵光一闪先在此处输出文件，\
	再在void slider_thining::setThiningLineEditValue(int value)中读取.\
	注意要先映射到0-255再输出才可以。此处是偶然在某代码注释中看到的，可见理论和代码阅读量的重要性	
	src_filtered_mapped = src_filtered * 255;
	//cv::bitwise_not(src_filtered_mapped, src_filtered_mapped);
	cv::namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
	cv::imshow(WINDOW_NAME, src_filtered_mapped);
	cv::imwrite("src_filtered.jpg", src_filtered_mapped);
}
int getMeanNum(int pos)
{
	if (pos % 2 != 0)
		return pos;
	else
		return pos + 1;
}