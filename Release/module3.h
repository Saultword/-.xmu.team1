#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<math.h>
#include<vector>
#include<strstream>
#include<fstream>
using namespace std;
using namespace cv;

namespace module3{

    //��ǿͼ�� //���ж�ֵ������
    Mat enhancement(Mat src);

    //Canny�㷨��Canny��ֵ�������1:3
    Mat CannyThreshold(Mat& src);

    //��ͼƬ�����򻯺͸�ʴ����ȥ������Ҫ�ı�Ե�ͱպϼ�϶
    void dilate_erode(Mat& src, Mat& dst);


    //ȷ��Ŀ��ͼƬ�е�Ŀ���ά����������
    vector<Point> getRect(Mat& src, Mat& dst);

    //͸��ӳ�䣬����ӳ����ͼƬ
    Mat get_Mappedim(Mat src, vector<Point> point);

    //module3�Ľӿ�
    vector<Mat> get_QRcode(vector<Mat>& src_ims);
}