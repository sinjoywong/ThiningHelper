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
	//cv::cvtColor(src_filtered_mapped, src_filtered1, 6);
	cv::threshold(src_filtered1, src_filtered1, pos, 1, cv::THRESH_BINARY_INV);
	//	cv::threshold(src_filtered1, src_filtered1,128,1,cv::THRESH_BINARY_INV);
	src_thinned = thinImage(src_filtered1);

	/*
	//src_thinned.copyTo(src_thinned_with_endpoint);
	//*
	//去除边界像素测试，2017.1.21
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
	EndPointNum = returnEndCount(src_thinned_cutted, src_thinned_with_endpoint);//此处的值未传到subwindow_statics.cpp中
	qDebug("[slider_thining.cpp] ln60,EndPointNum: %d", EndPointNum);
	//因为标记是直接写上去的，所以在写端点标记时会影响三叉点的判断。所以将细化后的图像src_thinned复制一份为src_thinned_with_endpoint,
	//然后将端点和三叉点的标记都放在src_thinned_with_endpoint中。
	TriplePointNum = returnTripleCount(src_thinned_cutted, src_thinned_with_endpoint);
	qDebug("[slider_thining.cpp] ln60,TriplePointNum: %d", TriplePointNum);

	src_thinned_mapped = src_thinned_with_endpoint * 255;
	cv::bitwise_not(src_thinned_mapped, src_thinned_mapped);
	cv::namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
	cv::imshow(WINDOW_NAME, src_thinned_mapped);
	//cv::imwrite("final.jpg", src_thinned_mapped);
	
}
using namespace cv;
//void slider_thining::on_mouse(int event, int x, int y, int flags, void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号  
void slider_thining::on_mouse(int event, int x, int y, int flags, void* param)
{
	;
	static Point pre_pt = (-1, -1);//初始坐标  
	static Point cur_pt = (-1, -1);//实时坐标  
	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
	{
		src_thinned.copyTo(img);//将原始图片复制到img中  
		sprintf(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255), 1, 8);//在窗口上显示坐标  
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//划圆  
		img = img * 255;
		cv::bitwise_not(img, img);
		namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
		imshow(WINDOW_NAME, img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数  
	{
		return;
		/*
		img.copyTo(tmp);//将img复制到临时图像tmp上，用于显示实时坐标
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));//只是实时显示鼠标移动的坐标
		namedWindow("mouseLeft not pushed");
		imshow("mouseLeft not pushed", tmp);
		*/
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//左键按下时，鼠标移动，则在图像上划矩形  
	{
		img.copyTo(tmp);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		rectangle(tmp, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//在临时图像上实时显示鼠标拖动时形成的矩形  
		tmp = tmp * 255;
		cv::bitwise_not(tmp, tmp);
		namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
		imshow(WINDOW_NAME, tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)//左键松开，将在图像上划矩形  
	{
		src_thinned.copyTo(img);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(img, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//根据初始点和结束点，将矩形画到img上  
		imshow(WINDOW_NAME, img);
		img.copyTo(tmp);
		//截取矩形包围的图像，并保存到src_thinned_cutted中  
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