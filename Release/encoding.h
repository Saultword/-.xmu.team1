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

namespace encoding {

    //��Ϣ�飨�����Σ��߳�
    const int PIX_SIZE = 8;

    //ÿ��/�е���Ϣ������
    const int DATA_LENGTH = 800 / PIX_SIZE;

    //ÿ��ͼƬ�������Ϣ������
    const int MAX_SIZE = DATA_LENGTH * DATA_LENGTH - 8;

    //���֡��
    const int FRAME_MAX = 15;


    //���ļ�+����string
    string getFile();

    //�ļ�ת���ɶ�����
    string file2Binary(string s);

    //��д���ļ��ֿ�
    vector<string> split(string s);

    //��string�ڴ�Ķ�������Ϣ����Mat
    Mat string2Mat(string s, int num);

    //��������
    vector<Mat> string2Mat_vector(vector<string> s);
}