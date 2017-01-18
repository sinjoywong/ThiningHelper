#include "includes.h"
#include "staticsInfo.h"
#include <fstream>

int EndPointNum = 0;
int TriplePointNum = 0;

void drawCircle(cv::Mat img, cv::Point center)
{
	cv::circle(img, center, 6, cv::Scalar(34, 139, 34), 0.12, 8);
}
//Let the central of rectangle lying in the node
void drawRectangle(cv::Mat img, cv::Point point_central)
{
	cv::Point point_SE;
	cv::Point point_NW;
	double len = 3;
	point_NW.x = point_central.x - len;
	point_NW.y = point_central.y - 2 * len;
	point_SE.x = point_central.x + len;
	point_SE.y = point_central.y + 2 * len;
	//0.2 is line width,point_NW stands for node in North-west，point_SE stands for node in South-east，8 stands for line type
	cv::rectangle(img, point_NW, point_SE, cv::Scalar(3, 97, 255), 0.2, 8);
}
//Type convertion. string-->int, so that we can print count number directly
void drawCountNumber(cv::Mat img, cv::Point point_SE, int countNum)
{
	//void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, \
		int thickness=1, int lineType=8, bool bottomLeftOrigin=false )
	std::string countNumStr;
	//	int countNum;
	std::stringstream stream;
	stream << countNum;
	countNumStr = stream.str();

	cv::putText(img, countNumStr, point_SE, CV_FONT_HERSHEY_SIMPLEX, 0.45, cv::Scalar(255, 0, 0), 1, 8);
}
//return end point number and add rectangle in the node 
int returnEndCount(const cv::Mat &src, cv::Mat &dst)
{
	assert(src.type() == CV_8UC1);
	int width = src.cols;
	int height = src.rows;
	cv::Mat src_copy1;
	src.copyTo(src_copy1);
	int endPointCount = 0;
	std::vector<uchar *> endPointPosition;
	for (int i = 0; i < height; ++i)//行循环
	{
		uchar * p = src_copy1.ptr<uchar>(i);//获取第i行的首地址
		for (int j = 0; j < width; ++j)//列循环
		{
			//如果满足四个条件，进行标记
			//  p9 p2 p3
			//  p8 p1 p4
			//  p7 p6 p5
			uchar p1 = p[j];
			if (p1 != 1) continue;
			uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
			uchar p8 = (j == 0) ? 0 : *(p + j - 1);
			uchar p2 = (i == 0) ? 0 : *(p - src_copy1.step + j);
			uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - src_copy1.step + j + 1);
			uchar p9 = (i == 0 || j == 0) ? 0 : *(p - src_copy1.step + j - 1);
			uchar p6 = (i == height - 1) ? 0 : *(p + src_copy1.step + j);
			uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + src_copy1.step + j + 1);
			uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + src_copy1.step + j - 1);

			if (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 == 1)
			{
				endPointCount = endPointCount + 1;//calculating the number of end points
				drawRectangle(dst, cv::Point(j, i));//marking the end points
				drawCountNumber(dst, cv::Point(j, i), endPointCount);//marking the number of end points
			}
		}
	}
	return endPointCount;
}
int returnTripleCount(const cv::Mat &src, cv::Mat &dst)
{
	std::vector<int> xvec;
	std::vector<int> yvec;

	std::cout << "In staticsInfo: return TripleCount actived! " << std::endl;
	/*      sum_01
	sum_10  sum_11  sum_12
			sum_21
	*/
	int sum_01, sum_10,sum_11,sum_12,sum_21;

	//索引表
	int Triple_mark[256] = {
		0,0,0,0,0,0,0,1,/*7*/   0,0,0,0,0,0,0,0,//15  !!!实际上是第15个，数组从零开始数,以下同理减一
		0,0,0,0,0,1,0,1,   0,0,0,0,0,1,0,0,//31

		0,0,0,0,0,1,0,0,   0,1,1,1,0,1,0,1,//47
		0,0,0,0,0,1,0,1,   0,0,0,0,0,0,0,0,//63

		0,0,0,0,0,1,0,0,   0,1,1,0,0,1,0,0,//79
		0,1,1,1,1,1,1,1,   0,1,1,1,1,1,1,1,//95

		0,0,0,0,0,1,0,1,   0,1,1,1,0,1,0,0,//111
		0,1,0,1,1,1,1,1,   0,0,0,0,0,1,0,0,//127

		0,0,0,0,0,0,0,0,   0,0,1,0,0,0,0,0,//143
		0,0,1,0,1,1,1,1,   0,0,1,0,0,1,1,0,//159

		0,0,1,0,1,1,1,1,   1,1,1,1,1,1,1,1,//175
		0,0,1,0,1,1,1,0,   0,0,1,0,0,0,0,0,//191

		0,1,0,0,0,0,0,0,   0,0,1,1,0,1,0,0,//207
		0,1,1,0,1,1,1,1,   0,1,1,0,1,1,0,0,//223

		0,0,0,0,0,0,0,0,   0,1,1,1,0,0,0,0,//239
		0,0,0,0,1,1,0,0,   0,0,0,0,0,0,0,0//255
	};
	cv::Mat src_copy;//src备份
	assert(src.type() == CV_8UC1);
	int width = src.cols;
	int height = src.rows;
	src.copyTo(src_copy);
	int triplePointCount = 0;

	qDebug("width = %d ", width);
	qDebug("height = %d ", height);


	std::ofstream output;
	output.open("PointStatics.txt");
	std::ofstream vec_out;
	vec_out.open("vec_out.txt");
	std::ofstream vec_out_after_erase;
	vec_out_after_erase.open("vec_out_after_erase.txt");

	for (int i = 0; i < height; ++i)//行循环
	{
		//new in 2017.1.11, 4-邻域的8-邻域的表示：1.先表示4-邻域
		uchar * p_ln0 = (i < 1) ? src_copy.ptr<uchar>(i) : src_copy.ptr<uchar>(i - 1);//获取第i-1行的首地址
		uchar * p_ln1 = src_copy.ptr<uchar>(i);//第i行
		uchar * p_ln2 = (i < height - 2) ? src_copy.ptr<uchar>(i + 1) : src_copy.ptr<uchar>(i);//第i+1行
		for (int j = 0; j < width; ++j)//列循环
		{
			//如果满足条件，进行标记
			//  p9 p2 p3
			//  p8 p1 p4
			//  p7 p6 p5
							/*      
									sum_01
							sum_10  sum_11  sum_12
									sum_21
							*/
//-------------p11-------------
			uchar p11 = p_ln1[j];
			if (p11 != 1)  continue; 
			uchar p11_4 = (j == width - 1) ? 0 : *(p_ln1 + j + 1);
			uchar p11_8 = (j == 0) ? 0 : *(p_ln1 + j - 1);
			uchar p11_2 = (i == 0) ? 0 : *(p_ln1 - src_copy.step + j);
			uchar p11_3 = (i == 0 || j == width - 1) ? 0 : *(p_ln1 - src_copy.step + j + 1);
			uchar p11_9 = (i == 0 || j == 0) ? 0 : *(p_ln1 - src_copy.step + j - 1);
			uchar p11_6 = (i == height - 1) ? 0 : *(p_ln1 + src_copy.step + j);
			uchar p11_5 = (i == height - 1 || j == width - 1) ? 0 : *(p_ln1 + src_copy.step + j + 1);
			uchar p11_7 = (i == height - 1 || j == 0) ? 0 : *(p_ln1 + src_copy.step + j - 1);
			p11_9 *= 1;
			p11_2 *= 2;
			p11_3 *= 4;
			p11_4 *= 8;
			p11_5 *= 16;
			p11_6 *= 32;
			p11_7 *= 64;
			p11_8 *= 128;
			sum_11 = p11_9 + p11_2 + p11_3 + p11_4 + p11_5 + p11_6 + p11_7 + p11_8;

/*
//------------p01------------
		//	uchar p01 = (j < width - 1) ? p_ln0[j + 1] : p_ln0[j];
			uchar p01 = p_ln0[j];
		//	if (p01 != 1)  continue; 
			uchar p01_4 = (j == width - 1) ? 0 : *(p_ln0 + j + 1);
			uchar p01_8 = (j == 0) ? 0 : *(p_ln0 + j - 1);
			uchar p01_2 = (i == 0) ? 0 : *(p_ln0 - src_copy.step + j);
			uchar p01_3 = (i == 0 || j == width - 1) ? 0 : *(p_ln0 - src_copy.step + j + 1);
			uchar p01_9 = (i == 0 || j == 0) ? 0 : *(p_ln0 - src_copy.step + j - 1);
			uchar p01_6 = (i == height - 1) ? 0 : *(p_ln0 + src_copy.step + j);
			uchar p01_5 = (i == height - 1 || j == width - 1) ? 0 : *(p_ln0 + src_copy.step + j + 1);
			uchar p01_7 = (i == height - 1 || j == 0) ? 0 : *(p_ln0 + src_copy.step + j - 1);
			p01_9 *= 1;
			p01_2 *= 2;
			p01_3 *= 4;
			p01_4 *= 8;
			p01_5 *= 16;
			p01_6 *= 32;
			p01_7 *= 64;
			p01_8 *= 128;
			sum_01 = p01_9 + p01_2 + p01_3 + p01_4 + p01_5 + p01_6 + p01_7 + p01_8;

 //-------------p10-------------
			uchar p10 = p_ln1[j-1];
			//if (p10 != 1) { continue; }
			uchar p10_4 = (j == width - 1) ? 0 : *(p_ln1 + j + 1);
			uchar p10_8 = (j == 0) ? 0 : *(p_ln1 + j - 1);
			uchar p10_2 = (i == 0) ? 0 : *(p_ln1 - src_copy.step + j);
			uchar p10_3 = (i == 0 || j == width - 1) ? 0 : *(p_ln1 - src_copy.step + j + 1);
			uchar p10_9 = (i == 0 || j == 0) ? 0 : *(p_ln1 - src_copy.step + j - 1);
			uchar p10_6 = (i == height - 1) ? 0 : *(p_ln1 + src_copy.step + j);
			uchar p10_5 = (i == height - 1 || j == width - 1) ? 0 : *(p_ln1 + src_copy.step + j + 1);
			uchar p10_7 = (i == height - 1 || j == 0) ? 0 : *(p_ln1 + src_copy.step + j - 1);
			p10_9 *= 1;
			p10_2 *= 2;
			p10_3 *= 4;
			p10_4 *= 8;
			p10_5 *= 16;
			p10_6 *= 32;
			p10_7 *= 64;
			p10_8 *= 128;
			sum_10 = p10_9 + p10_2 + p10_3 + p10_4 + p10_5 + p10_6 + p10_7 + p10_8;

//-------------p12-------------
			uchar p12 = p_ln1[j + 1];
			//if (p12 != 1) { continue; }
			uchar p12_4 = (j == width - 1) ? 0 : *(p_ln1 + j + 1);
			uchar p12_8 = (j == 0) ? 0 : *(p_ln1 + j - 1);
			uchar p12_2 = (i == 0) ? 0 : *(p_ln1 - src_copy.step + j);
			uchar p12_3 = (i == 0 || j == width - 1) ? 0 : *(p_ln1 - src_copy.step + j + 1);
			uchar p12_9 = (i == 0 || j == 0) ? 0 : *(p_ln1 - src_copy.step + j - 1);
			uchar p12_6 = (i == height - 1) ? 0 : *(p_ln1 + src_copy.step + j);
			uchar p12_5 = (i == height - 1 || j == width - 1) ? 0 : *(p_ln1 + src_copy.step + j + 1);
			uchar p12_7 = (i == height - 1 || j == 0) ? 0 : *(p_ln1 + src_copy.step + j - 1);
			p12_9 *= 1;
			p12_2 *= 2;
			p12_3 *= 4;
			p12_4 *= 8;
			p12_5 *= 16;
			p12_6 *= 32;
			p12_7 *= 64;
			p12_8 *= 128;
			sum_12 = p12_9 + p12_2 + p12_3 + p12_4 + p12_5 + p12_6 + p12_7 + p12_8;

//-------------p21-------------
			uchar p21 = p_ln2[j];
			//if (p21 != 1) { continue; }
			uchar p21_4 = (j == width - 1) ? 0 : *(p_ln1 + j + 1);
			uchar p21_8 = (j == 0) ? 0 : *(p_ln1 + j - 1);
			uchar p21_2 = (i == 0) ? 0 : *(p_ln1 - src_copy.step + j);
			uchar p21_3 = (i == 0 || j == width - 1) ? 0 : *(p_ln1 - src_copy.step + j + 1);
			uchar p21_9 = (i == 0 || j == 0) ? 0 : *(p_ln1 - src_copy.step + j - 1);
			uchar p21_6 = (i == height - 1) ? 0 : *(p_ln1 + src_copy.step + j);
			uchar p21_5 = (i == height - 1 || j == width - 1) ? 0 : *(p_ln1 + src_copy.step + j + 1);
			uchar p21_7 = (i == height - 1 || j == 0) ? 0 : *(p_ln1 + src_copy.step + j - 1);
			p21_9 *= 1;
			p21_2 *= 2;
			p21_3 *= 4;
			p21_4 *= 8;
			p21_5 *= 16;
			p21_6 *= 32;
			p21_7 *= 64;
			p21_8 *= 128;
			sum_21 = p21_9 + p21_2 + p21_3 + p21_4 + p21_5 + p21_6 + p21_7 + p21_8;
	*/		
			//============== 4-neighbor judgement ===============
				if (Triple_mark[sum_11] == 1 )
				{
					triplePointCount += 1;
					//将三叉点的位置坐标(i,j)放入xvec 和 yvec中
					xvec.push_back(i);
					yvec.push_back(j);
					//qDebug("xvec = %d", xvec.size());

					//显示三叉点p01,p19,p11,p12,p21的位置，其中p11为中心点
					qDebug("\t \t %d,%d, \n %d,%d  %d,%d  %d,%d \n \t \t %d,%d \n ------------------------------", i-1,j, i,j-1, i,j, i,j+1, j+1,j);
//print point statics
					output << triplePointCount << std::endl;
					output << i - 1 << "," << j << std::endl \
						<< i << "," << j - 1 << "   " << i << "," << j << "  " << i << "," << j + 1 << std::endl \
						<< j + 1 << "," << j << std::endl;
					output << "___________" << std::endl;

/*
					if (Triple_mark[sum_01] == 1)
					{
					//	qDebug("[staticsInfo] 11, 01 Num %d, Point ( %d, %d )", triplePointCount , j, i+1);
						triplePointCount += 1;
					//	drawCircle(dst, cv::Point(j, i));
					}
					else if (Triple_mark[sum_10] == 1 && Triple_mark[sum_11] == 1)
					{
					//	qDebug("[staticsInfo] 11, 10 Num %d, Point ( %d, %d )", triplePointCount , j, i+1);
						triplePointCount += 1;
						drawCircle(dst, cv::Point(j, i));
					}
					else if (Triple_mark[sum_12] == 1)
					{
					//	qDebug("[staticsInfo] 11, 12 Num %d, Point ( %d, %d )", triplePointCount , j, i+1);
						triplePointCount += 1;
						//drawCircle(dst, cv::Point(j, i));
					}
					else if (Triple_mark[sum_21] == 1)
					{
					//	qDebug("[staticsInfo] 11, 21 Num %d, Point ( %d, %d )", triplePointCount , j, i+1);
						triplePointCount += 1;
						//drawCircle(dst, cv::Point(j, i));
					}
					else
					{
					//	qDebug("[staticsInfo] rec");
						//triplePointCount -= 1;
						//drawRectangle(dst, cv::Point(j, i));
						continue;
					}
					*/
		//	drawCountNumber(dst, cv::Point(j, i), triplePointCount);
			}
		}
	}
	
	qDebug("triplePoint Num = %d", triplePointCount);
	output.close();
//输出所有三叉点的坐标，包含重复的点
	qDebug("xvec.size() = %d ", xvec.size());
	for (std::vector<int>::size_type ii = 0; ii != xvec.size(); ++ii)
	{
		vec_out << xvec[ii] << ", " << yvec[ii] << std::endl;
	}
	vec_out.close();
	
//判断如果相邻两个三叉点被标记，则删去一个
	for (std::vector<int>::size_type ii = 0; ii != xvec.size() - 1; ++ii)
	{
			qDebug("ii = %d ", ii);
		if (abs(xvec[ii] - xvec[ii + 1]) == 0 && abs(yvec[ii] - yvec[ii + 1]) == 1)
		{
			xvec.erase(xvec.begin() + ii);
			yvec.erase(yvec.begin() + ii);
		}
		if (abs(xvec[ii] - xvec[ii + 1]) == 1 && abs(yvec[ii] - yvec[ii + 1]) == 0)
		{
			xvec.erase(xvec.begin() + ii);
			yvec.erase(yvec.begin() + ii);
		}
	}
	//输出已经去除掉重复标记的三叉点的坐标,此时剩余的xvec的size就是去除重复后的三叉点数目
	qDebug("After erase: xvec.size() = %d ", xvec.size());
	for (std::vector<int>::size_type ii = 0; ii != xvec.size(); ++ii)
	{
		vec_out_after_erase << xvec[ii] << ", " << yvec[ii] << std::endl;
		drawCircle(dst, cv::Point(yvec[ii], xvec[ii]));
	}
	vec_out_after_erase.close();
	//return triplePointCount - 1;
	return xvec.size();
}


void fprint(int num, int i, int j)
{
	std::ofstream output;
	output.open("PointStatics.txt");
	output<< ("%d: \n \t \t %d,%d, \n %d,%d  %d,%d  %d,%d \n \t \t %d,%d \n ------------------------------",num, i - 1, j, i, j - 1, i, j, i, j + 1, j + 1, j);

	output.close();
}








