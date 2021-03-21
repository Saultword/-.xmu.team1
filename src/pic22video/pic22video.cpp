#include<iostream>
#include "pic22video.h"
using namespace std;
using namespace cv;


using namespace picvideo;

	void pic2video(vector<Mat>& src_ims)
	{
		char name2[20];
		cout << "�������������Ƶ�ļ��������硰test.mp4��:" << endl;
		cin >> name2;
		
		cout << "��������Ƶ֡��:" << endl;
		cin >> frame_rate;
		VideoWriter video(name2, CAP_ANY, frame_rate, Size(720, 720));
		for (size_t i = 0; i < src_ims.size(); i++)
		{
			Mat image = src_ims[i].clone();
			// ������������ͼƬ������Ƶ
			video << image;
		}
	}
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





