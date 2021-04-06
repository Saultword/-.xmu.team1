#include"picvideo.h"

namespace picvideo {

    //��Ԫ���ڸ���ͼƬת��Ϊ��Ƶ
    void pic2video(vector<Mat>& src_ims)
    {
        string name2 = "test.avi";
        cout << "�������������Ƶ�ļ��������硰test.avi��:" << endl;
        cin >> name2;

        int frame_rate = 15;
        //cout << "��������Ƶ֡��:" << endl;
        //cin >> frame_rate;

        VideoWriter video(name2, VideoWriter::fourcc('M', 'P', '4', 'V'), frame_rate, Size(1000, 1000), false);
        for (size_t i = 0; i < src_ims.size(); i++)
        {
            Mat image = src_ims[i].clone();
            // ������������ͼƬ������Ƶ
            video << image;
        }

    }

    //����Ƶ��֡��ȡ����Ԫ���ΪMat�����
    void video2pic(string path, vector<Mat>& src_ims)
    {
        VideoCapture capture(path);
        Mat frame;
        while (true) {
            //һ֡һ֡��
            capture >> frame;
            if (frame.empty()) {
                break;
            }
            else src_ims.push_back(frame.clone());
        }
    }

    //���ڲ�����Ƶ���ݣ�����Ϊ��Ŀ¼���ļ�����
    void videoshow(string path)
    {
        VideoCapture capture(path);
        while (1)
        {
            //frame�洢ÿһ֡ͼ��
            Mat frame;
            //��ȡ��ǰ֡
            capture >> frame;
            //�������˳�
            if (frame.empty()) {
                printf("�������\n");
                break;
            }
            //��ʾ��ǰ��Ƶ
            imshow("��ȡ��Ƶ", frame);
            //��ʱ300ms
            waitKey(300);
        }
    }
}
