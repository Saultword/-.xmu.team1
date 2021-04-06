#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<vector>
#include<strstream>
#include<fstream>
using namespace std;
using namespace cv;

namespace picvideo {

    //��Ԫ���ڸ���ͼƬת��Ϊ��Ƶ
    void pic2video(vector<Mat>& src_ims);

    //����Ƶ��֡��ȡ����Ԫ���ΪMat�����
    void video2pic(string path, vector<Mat>& src_ims);

    //���ڲ�����Ƶ���ݣ�����Ϊ��Ŀ¼���ļ�����
    void videoshow(string path);
}
