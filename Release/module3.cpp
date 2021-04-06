#include"module3.h"

namespace module3
{
    // �����ռ��Ա����

    Mat src_gray;                               //ԴͼƬ��Դ�Ҷ�ͼƬ 
    Mat dst, detected_edges;                    //Ŀ��ͼƬ���Ѽ���ԵͼƬ
    int lowThreshold = 80;                      //����ֵ   ����Ϊ0�ǵľ�Ϊǿ��Ե�㣬�Ӷ���ø������ı�ԵͼƬ
    int ratio1 = 3;                             //�ߵ���ֵ֮��
    int kernel_size = 3;                        //�ں˴�С
    int highThreshold = lowThreshold * ratio1;
    int idx = 0;

    //��ǿͼ�� //���ж�ֵ������
    Mat enhancement(Mat src) {
        for (int i = 0; i < src.rows; i++) {
            for (int j = 0; j < src.cols; j++) {
                src.ptr<uchar>(i)[j] = (src.ptr<uchar>(i)[j] > 128 ? 255 : 0);
            }
        }
        return src;
    }

    //Canny�㷨��Canny��ֵ�������1:3
    Mat CannyThreshold(Mat& src)
    {
        //��˹�˲�
        GaussianBlur(src_gray, detected_edges, Size(9, 9), 0, 0);
        //˫���˲�
        //bilateralFilter(src_gray, detected_edges, 5, 200, 200, BORDER_REFLECT_101);
        // ����Canny���ӣ�ģ��ͼ��Ѱ�ұ�Ե��Ȼ��ֵ������detected_edges��
        Canny(detected_edges, detected_edges, lowThreshold, highThreshold, kernel_size);

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

        //imshow("res", res_dst);

        //���ڴ洢��϶���εĶ�����Ϣ
        vector<Point>vertex_point;
        //������������ϣ���ϳɶ����
        approxPolyDP(contours[maxAreaIdx], vertex_point, 50, 1);

        //�����ϳɵĶ���εĶ�����Ϣ
        //cout << vertex_point << endl;

        return vertex_point;
    }

    //͸��ӳ�䣬����ӳ����ͼƬ
    Mat get_Mappedim(Mat src, vector<Point> point)
    {
        Point2f src_corners[4];          //Դ������Ϣ
        Point2f dst_corners[4];          //Ŀ�궥����Ϣ

        bool x[4] = { false,false,false,false };
        bool y[4] = { false,false,false,false };

        //ΪpointԪ��x��С����
        float x_tmp1;
        float x_tmp2;
        int idx11;
        int idx12;
        if (point[0].x < point[1].x)
        {
            x_tmp1 = point[0].x;
            idx11 = 0;
            x_tmp2 = point[1].x;
            idx12 = 1;
        }
        else
        {
            x_tmp1 = point[1].x;
            idx11 = 1;
            x_tmp2 = point[0].x;
            idx12 = 0;
        }

        for (int i = 2; i < 4; i++)
        {
            if (point[i].x < x_tmp2)
            {
                if (point[i].x < x_tmp1)
                {
                    x_tmp2 = x_tmp1;
                    idx12 = idx11;
                    x_tmp1 = point[i].x;
                    idx11 = i;
                }
                else
                {
                    x_tmp2 = point[i].x;
                    idx12 = i;
                }
            }
        }
        x[idx11] = true;
        x[idx12] = true;
        //ΪpointԪ��y��С����
        float y_tmp1;
        float y_tmp2;
        int idx21;
        int idx22;
        if (point[0].y < point[1].y)
        {
            y_tmp1 = point[0].y;
            idx21 = 0;
            y_tmp2 = point[1].y;
            idx22 = 1;
        }
        else
        {
            y_tmp1 = point[1].y;
            idx21 = 1;
            y_tmp2 = point[0].y;
            idx22 = 0;
        }

        for (int i = 2; i < 4; i++)
        {
            if (point[i].y < y_tmp2)
            {
                if (point[i].y < y_tmp1)
                {
                    y_tmp2 = y_tmp1;
                    idx22 = idx21;
                    y_tmp1 = point[i].y;
                    idx21 = i;
                }
                else
                {
                    y_tmp2 = point[i].y;
                    idx22 = i;
                }
            }
        }
        y[idx21] = true;
        y[idx22] = true;
        //��ʽ��ת��
        for (int i = 0; i < 4; i++)
        {
            if (x[i] && y[i])
            {
                src_corners[0].x = point[i].x;
                src_corners[0].y = point[i].y;
            }
            else if (x[i] && !y[i])
            {
                src_corners[1].x = point[i].x;
                src_corners[1].y = point[i].y;
            }
            else if (!x[i] && !y[i])
            {
                src_corners[2].x = point[i].x;
                src_corners[2].y = point[i].y;
            }
            else
            {
                src_corners[3].x = point[i].x;
                src_corners[3].y = point[i].y;
            }
        }
        //����Ŀ������
        dst_corners[0] = Point(0, 0);
        dst_corners[1] = Point(0, 832);
        dst_corners[2] = Point(832, 832);
        dst_corners[3] = Point(832, 0);

        //��ȡ͸�Ӿ���
        Mat warpmatrix = getPerspectiveTransform(src_corners, dst_corners);

        Mat res;

        //����͸��
        warpPerspective(src, res, warpmatrix, res.size(), INTER_LANCZOS4);

        //��ȡĿ���������Ϣ
        Rect res_rect(0, 0, 832, 832);
        res = res(res_rect);

        return res;
    }

    //module3�Ľӿ�
    vector<Mat> get_QRcode(vector<Mat>& src_ims)
    {
        //int i = 1;
        vector<Mat> src;
        for (auto src_im : src_ims)
        {
            //cout << i++ << endl;
            if (!src_im.data)
                exit(-1);

            //��ͼƬ��С���е���
            resize(src_im, src_im, Size(832, 832), 0, 0, INTER_LANCZOS4);

            //imshow("src", src_im);
            //������src_imͬ���͵Ĵ�С�ľ���dst��
            dst.create(src_im.size(), src_im.type());

            //ԭͼ��ת��Ϊ�Ҷ�ͼ��
            cvtColor(src_im, src_gray, CV_BGR2GRAY);

            //��ȡ��Ե
            dst = CannyThreshold(src_im);

            //ת��Ϊ�Ҷ�ͼ
            cvtColor(dst, dst, CV_BGR2GRAY);

            //���븯ʴ
            //dilate_erode(dst, dst);

            //�õ���ά�����򶥵�
            vector<Point>point = getRect(dst, dst);

            //��ȡ͸�Ӻ�Ķ�ά��
            src_im = get_Mappedim(src_im, point);


            //�Զ�ά���С���е���
            //resize(src_im, src_im, Size(820, 820), 0, 0, INTER_CUBIC);
            cvtColor(src_im, src_im, CV_BGR2GRAY);
            src_im = enhancement(src_im);

            //����ȡ���Ķ�ά����ӵ�����src��
            src.push_back(src_im);
        }

        return src;
    }
}