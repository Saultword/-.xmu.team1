#include "module3.h"
#include <iostream>

using namespace std;

namespace module3
{
    // �����ռ��Ա����

    Mat src_gray;                               //ԴͼƬ��Դ�Ҷ�ͼƬ 
    Mat dst, detected_edges;                    //Ŀ��ͼƬ���Ѽ���ԵͼƬ
    int lowThreshold = 80;                      //����ֵ   ����Ϊ0�ǵľ�Ϊǿ��Ե�㣬�Ӷ���ø������ı�ԵͼƬ
    int ratio1 = 3;                             //�ߵ���ֵ֮��
    int kernel_size = 3;                        //�ں˴�С


    // �����ռ��Ա���� -- ����


    //Canny�㷨��Canny��ֵ�������1:3
    Mat CannyThreshold(Mat &src)
    {
        // ʹ�� 3x3 �ں˽��룬ƽ��ͼƬ
        blur(src_gray, detected_edges, Size(3, 3));

        // ����Canny���ӣ�ģ��ͼ��Ѱ�ұ�Ե��Ȼ��ֵ������detected_edges��
        Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio1, kernel_size);

        // ʹ�� Canny���������Ե��Ϊ������ʾԭͼ�����dstͼ��ȫ�ڣ�
        dst = Scalar::all(0);

        //ʹ�ú��� copyTo ��ʶ����⵽�ı�Ե����
        src.copyTo(dst, detected_edges);
        return dst;
    }

    //��ͼƬ�����򻯺͸�ʴ����ȥ������Ҫ�ı�Ե�ͱպϼ�϶
    void dilate_erode(Mat& src, Mat& dst)
    {
        //����ָ����״�ͳߴ���ں˾���ѡ����ε� 3*3 �ںˣ�ê��Ĭ��Ϊ���ĵ�(-1,-1)
        Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
        
        //�򻯴���
        dilate(src, dst, element);

        //��ʴ����
        erode(dst, dst, element);
        
        for (int i = 0; i < 10; i++)
        {
            //�򻯴���
            dilate(dst, dst, element);

            //��ʴ����
            erode(dst, dst, element);
        }
    }

    //ȷ��Ŀ��ͼƬ�е�Ŀ���ά����������
    vector<Point> getRect(Mat& src, Mat& dst)
    {
        double maxarea = 0;             //����������
        int maxAreaIdx = 0;             //�������������±�
        vector<vector<Point>>contours;  //��������
        vector<Vec4i>hierarchy;         //ͼ������˽ṹ

        //Ѱ��������������contours��
        findContours(src, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        //Ѱ���������
        for (int i = 0; i < contours.size(); i++)
        {
            double tmparea = fabs(contourArea(contours[i]));
            if (tmparea > maxarea)
            {
                maxarea = tmparea;
                maxAreaIdx = i;
                continue;
            }
        }

        Mat res_dst = Mat::zeros(src.size(), CV_8UC3);

        //������������ɫ
        RNG rng(0);
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

        //��������
        drawContours(res_dst, contours, maxAreaIdx, color, 2, 8, hierarchy, 0, Point(0, 0));

        //���ڴ洢��϶���εĶ�����Ϣ
        vector<Point>vertex_point;
        //������������ϣ���ϳɶ����
        approxPolyDP(contours[maxAreaIdx], vertex_point, 250, 1);

        //�����ϳɵĶ���εĶ�����Ϣ
        cout << vertex_point << endl;

        return vertex_point;
    }

    //͸��ӳ�䣬����ӳ����ͼƬ
    Mat get_Mappedim(Mat src, vector<Point> point)
    {
        Point2f src_corners[4];          //Դ������Ϣ
        Point2f dst_corners[4];          //Ŀ�궥����Ϣ
        
        //��ʽ��ת��
        for (int i = 0; i < 4; i++)         
        {
            src_corners[i].x = point[i].x;       
            src_corners[i].y = point[i].y;
        }

        //����Ŀ������
        dst_corners[0] = Point(400, 0);          
        dst_corners[1] = Point(0, 0);
        dst_corners[2] = Point(0, 400);
        dst_corners[3] = Point(400, 400);

        //��ȡ͸�Ӿ���
        Mat warpmatrix = getPerspectiveTransform(src_corners, dst_corners);
        
        Mat res;

        //����͸��
        warpPerspective(src, res, warpmatrix, res.size(), CV_INTER_LINEAR);
        
        //��ȡĿ���������Ϣ
        Rect res_rect(0, 0, 400, 400);
        res = res(res_rect);

        return res;
    }

    //module3�Ľӿ�
    vector<Mat> get_QRcode(vector<Mat>& src_ims)
    {
        vector<Mat> src;
        for (auto src_im : src_ims)
        {
            if (!src_im.data)
                exit(-1);

            //��ͼƬ��С���е���
            resize(src_im, src_im, Size(805, 805), 0, 0, INTER_LINEAR);

            //������src_imͬ���͵Ĵ�С�ľ���dst��
            dst.create(src_im.size(), src_im.type());

            //ԭͼ��ת��Ϊ�Ҷ�ͼ��
            cvtColor(src_im, src_gray, CV_BGR2GRAY);

            //��ȡ��Ե
            dst = CannyThreshold(src_im);

            //ת��Ϊ�Ҷ�ͼ
            cvtColor(dst, dst, CV_BGR2GRAY);
            
            //���븯ʴ
            dilate_erode(dst, dst);

            //�õ���ά�����򶥵�
            vector<Point>point = getRect(dst, dst);

            //��ȡ��ά��
            src_im = get_Mappedim(src_im, point);

            //�Զ�ά���С���е���
            resize(src_im, src_im, Size(805, 805), 0, 0, INTER_LINEAR);

            //����ȡ���Ķ�ά����ӵ�����src��
            src.push_back(src_im);
        }

        return src;
    }
}