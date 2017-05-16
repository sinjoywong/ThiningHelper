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
cv::Mat src_thinned_cutted;
cv::Mat img;
cv::Mat tmp;
extern cv::Mat src_filtered_mapped;
extern cv::Mat src_filtered;
cv::Mat src_thinned_cutted_marked;
slider_thining::slider_thining(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Value_Slider_Thining = new QLineEdit("12");
	Slider_Thining = new QSlider(Qt::Horizontal);
	Slider_Thining->setMinimum(2);
	Slider_Thining->setMaximum(255);
	Slider_Thining->setValue(12);

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
	//cv::cvtColor(src_filtered_mapped, src_filtered1, 6);
	cv::threshold(src_filtered1, src_filtered1, pos, 1, cv::THRESH_BINARY_INV);
	//	cv::threshold(src_filtered1, src_filtered1,128,1,cv::THRESH_BINARY_INV);
	src_thinned = thinImage(src_filtered1);

	/*
	//src_thinned.copyTo(src_thinned_with_endpoint);
	//*
	//ȥ���߽����ز��ԣ�2017.1.21
	int width = src_thinned.cols;
	int height = src_thinned.rows;
	int cut_width = 17;
	int width_now = width - cut_width;
	int height_now = height - cut_width;// -0.2*cut_width;
	qDebug("[slider_thining.cpp] ln63, width = %d,width_now = %d",width, width_now);
	cv::Mat src_thinned_cutted;
	src_thinned.copyTo(src_thinned_cutted);
	src_thinned_cutted = src_thinned_cutted(cv::Rect(cut_width/2, 0, width_now, height_now));
	//
	src_thinned_cutted.copyTo(src_thinned_with_endpoint);
	*/
	src_thinned.copyTo(src_thinned_cutted);
	cv::Mat src_thinned_before_cut;

	src_thinned.copyTo(src_thinned_before_cut);

	cv::setMouseCallback(WINDOW_NAME, on_mouse, 0);
	
	src_thinned_cutted.copyTo(src_thinned_with_endpoint);
	EndPointNum = returnEndCount(src_thinned_cutted, src_thinned_with_endpoint);//�˴���ֵδ����subwindow_statics.cpp��
	qDebug("[slider_thining.cpp] ln60,EndPointNum: %d", EndPointNum);
	//��Ϊ�����ֱ��д��ȥ�ģ�������д�˵���ʱ��Ӱ���������жϡ����Խ�ϸ�����ͼ��src_thinned����һ��Ϊsrc_thinned_with_endpoint,
	//Ȼ�󽫶˵�������ı�Ƕ�����src_thinned_with_endpoint�С�
	TriplePointNum = returnTripleCount(src_thinned_cutted, src_thinned_with_endpoint);
	qDebug("[slider_thining.cpp] ln60,TriplePointNum: %d", TriplePointNum);

	src_thinned_mapped = src_thinned_with_endpoint * 255;
	cv::bitwise_not(src_thinned_mapped, src_thinned_mapped);
	cv::namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
	cv::imshow(WINDOW_NAME, src_thinned_mapped);
	//cv::imwrite("final.jpg", src_thinned_mapped);
	
}
using namespace cv;
//void slider_thining::on_mouse(int event, int x, int y, int flags, void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���  
void slider_thining::on_mouse(int event, int x, int y, int flags, void* param)
{
	;
	static Point pre_pt = (-1, -1);//��ʼ����  
	static Point cur_pt = (-1, -1);//ʵʱ����  
	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//������£���ȡ��ʼ���꣬����ͼ���ϸõ㴦��Բ  
	{
		src_thinned.copyTo(img);//��ԭʼͼƬ���Ƶ�img��  
		sprintf(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255), 1, 8);//�ڴ�������ʾ����  
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//��Բ  
		img = img * 255;
		cv::bitwise_not(img, img);
		namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
		imshow(WINDOW_NAME, img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//���û�а��µ����������ƶ��Ĵ�����  
	{
		return;
		/*
		img.copyTo(tmp);//��img���Ƶ���ʱͼ��tmp�ϣ�������ʾʵʱ����
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));//ֻ��ʵʱ��ʾ����ƶ�������
		namedWindow("mouseLeft not pushed");
		imshow("mouseLeft not pushed", tmp);
		*/
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//�������ʱ������ƶ�������ͼ���ϻ�����  
	{
		img.copyTo(tmp);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		rectangle(tmp, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//����ʱͼ����ʵʱ��ʾ����϶�ʱ�γɵľ���  
		tmp = tmp * 255;
		cv::bitwise_not(tmp, tmp);
		namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
		imshow(WINDOW_NAME, tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)//����ɿ�������ͼ���ϻ�����  
	{
		src_thinned.copyTo(img);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(img, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//���ݳ�ʼ��ͽ����㣬�����λ���img��  
		imshow(WINDOW_NAME, img);
		img.copyTo(tmp);
		//��ȡ���ΰ�Χ��ͼ�񣬲����浽src_thinned_cutted��  
		int width = abs(pre_pt.x - cur_pt.x);
		int height = abs(pre_pt.y - cur_pt.y);
		if (width == 0 || height == 0)
		{
			printf("width == 0 || height == 0");
			return;
		}
		src_thinned_cutted = src_thinned(Rect(min(cur_pt.x, pre_pt.x), min(cur_pt.y, pre_pt.y), width, height));
		
		src_thinned_cutted.copyTo(src_thinned_cutted_marked);
		EndPointNum = returnEndCount(src_thinned_cutted, src_thinned_cutted_marked);
		TriplePointNum = returnTripleCount(src_thinned_cutted, src_thinned_cutted_marked);
		src_thinned_cutted_marked = src_thinned_cutted_marked * 255;
		cv::bitwise_not(src_thinned_cutted_marked, src_thinned_cutted_marked);
		namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
		imshow(WINDOW_NAME, src_thinned_cutted_marked);
		cv::imwrite("final.jpg", src_thinned_cutted_marked);
		waitKey(0);
	}
}