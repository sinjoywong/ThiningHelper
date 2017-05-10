#include "includes.h"
#include "slider_thining.h"
using namespace std;
using namespace cv;
//int g_nCurrRowsSize = 0, g_nCurrColsSize = 0;
void resize_picture(Mat &src,Mat &dst) {

	int g_nCurrRowsSize = 0, g_nCurrColsSize = 0;

	Mat midImage;
	src.copyTo(midImage);

	g_nCurrRowsSize = src.rows;
	g_nCurrColsSize = src.cols;

	createTrackbar("rows", WINDOW_NAME, &g_nCurrRowsSize, src.rows * 2, 0);
	createTrackbar("cols", WINDOW_NAME, &g_nCurrColsSize, src.cols * 2, 0);

	char key;
	while (1) {//һֱ��ʾ
		resize(src, dst, Size(g_nCurrColsSize, g_nCurrRowsSize), 0, 0, 3);
	
		dst = dst * 255;
		cv::bitwise_not(dst, dst);
		imshow(WINDOW_NAME, dst);
		
		key = waitKey(10);

		switch (key) {
		case    27:
			break;
		case    'x'://�����⵽����ֵΪ 'x' ��ָ�ԭͼ  
			midImage.copyTo(dst);
			qDebug("iflag = 0");
			g_nCurrColsSize = src.cols;
			g_nCurrRowsSize = src.rows;
			break;
		default:
			break;
		}
	}
}