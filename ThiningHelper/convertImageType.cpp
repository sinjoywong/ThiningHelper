#include "includes.h"
#include <qimage.h>
QImage CvMat2QImage(cv::Mat mat)
{   //show the resultImage in result area;  
	cv::Mat rgb;
	QImage img;
	if (mat.channels() == 3)    // RGB image  
	{
		cvtColor(mat, rgb, CV_BGR2RGB);
		img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)  
			rgb.cols, rgb.rows,
			rgb.cols*rgb.channels(),   //new add  
			QImage::Format_RGB888);
	}
	else                     // gray image  
	{
		img = QImage((const uchar*)(mat.data),
			mat.cols, mat.rows,
			mat.cols*mat.channels(),    //new add  
			QImage::Format_Indexed8);
	}
	return img;
}
