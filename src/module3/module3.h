#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/highgui/highgui.hpp"
#include <vector>

using namespace std;
using namespace cv;

namespace module3
{
    // �����ռ��Ա���� -- ����


    //Canny�㷨��Canny��ֵ�������1:3
    Mat CannyThreshold(Mat& src);

    //��ͼ����ж�ֵ������
    Mat enhancement(Mat src);

    //��ͼ������޸�
    Mat repair(Mat src);
    //��ͼƬ�����򻯺͸�ʴ����ȥ������Ҫ�ı�Ե�ͱպϼ�϶
    void dilate_erode(Mat& src, Mat& dst);

    //�޸ľ��ε����꣬
    //void reSizeRect(Rect& rect);


    //ȷ��Ŀ��ͼƬ�е�Ŀ���ά����������
    vector<Point> getRect(Mat& src, Mat& dst);

    Mat get_Mappedim(Mat src, vector<Point> point);

    vector<Mat> get_QRcode(vector<Mat>& src_ims);

}