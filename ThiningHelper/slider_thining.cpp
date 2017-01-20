#include "slider_thining.h"
#include "includes.h"
#include <qlabel.h>
#include "staticsInfo.h"

extern cv::Mat src_filtered;//��ֵ֮���ͼ��Ӧ�û����ٴζ�ֵ�����˴���θĽ���Ŀǰ�취����д�ļ����ٶ��ļ�
 cv::Mat src_thinned;
 cv::Mat src_thinned_mapped;
 cv::Mat src_thinned_with_endpoint;
 cv::Mat src_thinned_with_triplepoint;
 cv::Mat thinImage(const cv::Mat & src, const int maxIterations = -1);
  int EndPointNum;//���صĶ˵���Ŀ
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
	this->setWindowTitle(QStringLiteral("����ͼ��"));
	this->setWindowIcon(QIcon(":/ThiningHelper/Resources/myico.ico"));


}

slider_thining::~slider_thining()
{

}
//�ڴ˴����ؽڵ�ͳ����Ϣ
void slider_thining::setThiningLineEditValue(int value)
{
	int pos = Slider_Thining->value();
	QString str = QString("%1").arg(pos);
	Value_Slider_Thining->setText(str);
	//һ�����ɵİ취����Ϊ��Ҫ��grayscale��ʽ���룬��������һ������ļ�����һ����ȡ���ļ�
	cv::Mat src_filtered1 = cv::imread("src_filtered.jpg", cv::IMREAD_GRAYSCALE);
	cv::threshold(src_filtered1, src_filtered1,pos,1,cv::THRESH_BINARY_INV);
	src_thinned =thinImage(src_filtered1);

	src_thinned.copyTo(src_thinned_with_endpoint);

	EndPointNum = returnEndCount(src_thinned, src_thinned_with_endpoint);//�˴���ֵδ����subwindow_statics.cpp��
	qDebug("[slider_thining.cpp] ln60,EndPointNum: %d", EndPointNum);
	//��Ϊ�����ֱ��д��ȥ�ģ�������д�˵���ʱ��Ӱ���������жϡ����Խ�ϸ�����ͼ��src_thinned����һ��Ϊsrc_thinned_with_endpoint,
	//Ȼ�󽫶˵�������ı�Ƕ�����src_thinned_with_endpoint�С�
	TriplePointNum = returnTripleCount(src_thinned, src_thinned_with_endpoint);
	qDebug("[slider_thining.cpp] ln60,TriplePointNum: %d", TriplePointNum);

	src_thinned_mapped = src_thinned_with_endpoint * 255;
	cv::bitwise_not(src_thinned_mapped, src_thinned_mapped);
	cv::imshow(WINDOW_NAME, src_thinned_mapped);
	cv::imwrite("final.jpg", src_thinned_mapped);
}