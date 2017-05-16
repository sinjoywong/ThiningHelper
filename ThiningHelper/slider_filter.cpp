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
	this->setWindowTitle(QStringLiteral("�����˲�ǿ��"));
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

	cv::medianBlur(src_thresholded, src_filtered, pos);//��ֵ�˲�
	 //TODO:���⼸���˲���ѡ��

	//���ַ�����ȡ�ɡ���Ϊ����ϸ����Ҫ��ֵͼ��������Ҫ�ٴ�threshold,ֱ�Ӷ�ȡ����ֲ��������Ĵ����������һ�����ڴ˴�����ļ���\
	����void slider_thining::setThiningLineEditValue(int value)�ж�ȡ.\
	ע��Ҫ��ӳ�䵽0-255������ſ��ԡ��˴���żȻ��ĳ����ע���п����ģ��ɼ����ۺʹ����Ķ�������Ҫ��	
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