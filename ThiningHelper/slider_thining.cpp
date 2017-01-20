#include "slider_thining.h"
#include "includes.h"
#include <qlabel.h>
#include "staticsInfo.h"

extern cv::Mat src_filtered;//滤值之后的图像，应该还需再次二值化。此处如何改进？目前办法：先写文件，再读文件
 cv::Mat src_thinned;
 cv::Mat src_thinned_mapped;
 cv::Mat src_thinned_with_endpoint;
 cv::Mat src_thinned_with_triplepoint;
 cv::Mat thinImage(const cv::Mat & src, const int maxIterations = -1);
  int EndPointNum;//返回的端点数目
 int TriplePointNum;
slider_thining::slider_thining(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	Value_Slider_Thining = new QLineEdit("128");
	Slider_Thining = new QSlider(Qt::Horizontal);
	Slider_Thining->setMinimum(0);
	Slider_Thining->setMaximum(255);
	Slider_Thining->setValue(128);

	connect(Slider_Thining, SIGNAL(valueChanged(int)), this, SLOT(setThiningLineEditValue(int)));

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(Value_Slider_Thining);
	layout->addWidget(Slider_Thining);

	this->setLayout(layout);
	this->resize(255, 20);
	this->setWindowTitle(QStringLiteral("处理图像"));
	this->setWindowIcon(QIcon(":/ThiningHelper/Resources/myico.ico"));


}

slider_thining::~slider_thining()
{

}
//在此处返回节点统计信息
void slider_thining::setThiningLineEditValue(int value)
{
	int pos = Slider_Thining->value();
	QString str = QString("%1").arg(pos);
	Value_Slider_Thining->setText(str);
	//一种讨巧的办法，因为需要以grayscale形式读入，所以在上一步输出文件，这一步读取该文件
	cv::Mat src_filtered1 = cv::imread("src_filtered.jpg", cv::IMREAD_GRAYSCALE);
	cv::threshold(src_filtered1, src_filtered1,pos,1,cv::THRESH_BINARY_INV);
	src_thinned =thinImage(src_filtered1);

	src_thinned.copyTo(src_thinned_with_endpoint);

	EndPointNum = returnEndCount(src_thinned, src_thinned_with_endpoint);//此处的值未传到subwindow_statics.cpp中
	qDebug("[slider_thining.cpp] ln60,EndPointNum: %d", EndPointNum);
	//因为标记是直接写上去的，所以在写端点标记时会影响三叉点的判断。所以将细化后的图像src_thinned复制一份为src_thinned_with_endpoint,
	//然后将端点和三叉点的标记都放在src_thinned_with_endpoint中。
	TriplePointNum = returnTripleCount(src_thinned, src_thinned_with_endpoint);
	qDebug("[slider_thining.cpp] ln60,TriplePointNum: %d", TriplePointNum);

	src_thinned_mapped = src_thinned_with_endpoint * 255;
	cv::bitwise_not(src_thinned_mapped, src_thinned_mapped);
	cv::imshow(WINDOW_NAME, src_thinned_mapped);
	cv::imwrite("final.jpg", src_thinned_mapped);
}