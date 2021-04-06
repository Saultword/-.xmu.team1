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

namespace decoding {

    //���ص��С
    const int PIX_SIZE = 8;

    //��ȡÿһ����Ϣ���ںڰױ���
    double whiteGrayscale_percent(Mat img, int x, int y);

    //��ͼƬ�����ؿ���б���������/����������һ����ֵ�����ж�Ϊ��/�ף�����Ϊ����
    string print_01(Mat img, int x, int y);

    //����ͼƬ����
    string decode(const Mat& img);

    //�ӿ�
    void decoding(const vector<Mat>& rec);
}