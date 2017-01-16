#pragma once
#include "includes.h"
//staticsInfo
void drawRectangle(cv::Mat img, cv::Point point_central);
void drawCircle(cv::Mat img, cv::Point center);
void drawCountNumber(cv::Mat img, cv::Point point_SE, int countNum);
int returnEndCount(const cv::Mat &src, cv::Mat &dst);
int returnTripleCount(const cv::Mat &src, cv::Mat &dst);


void test_info(const cv::Mat &src, cv::Mat &dst);