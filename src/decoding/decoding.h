#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdio.h>
#define charNumber 5000												//�ַ����������5000��
using namespace std;
using namespace cv;

namespace enAndde_code {
	bitset<8> toBinary(char i) {									//���ַ�ת��Ϊ������
		bitset<8> bit;
		bit = i;
		return bit;
	}

	char toDecimal(bitset<8> a) {									//��������ת��Ϊ�ַ���AscII��
		char c = 0;
		for (int i = 0; i < 8; i++) {
			c += a[i] * pow(2, i);
		}
		return c;
	}

	void form(ofstream& ofile) {									//������ɺ���charNumber��AscII��Ϊ
		srand(time(NULL));											//48-122֮�䣨���̿����룩���ַ����ļ�
		for (int i = 0; i < charNumber; i++) {
			char c = 48 + rand() % 74;
			ofile << c;
		}
	}

	void encode(ifstream& ifile) {									//���벿�֣���ifile�е���Ϣ���б���
		bitset<8> toBinary(char i);
		Mat	img = Mat::zeros(810, 810, CV_8UC1);
		char c;
		int colume = 0;
		int row = 0;
		while (ifile.peek() != EOF) {
			ifile >> c;
			bitset<8> ch = toBinary(c);
			for (int i = 0; i < 8; i++) {
				if (colume >= 200) {								//ÿһ�д洢200λ��Ϣ��һ�д�����Ϣ����һ�д���
					colume = 0;
					row++;
				}
				if (ch[i] == 0) {
					Rect rec1 = Rect(5 + 4 * colume, 5 + 4 * row, 4, 4);
					rectangle(img, rec1, Scalar(255), -1, 8, 0);
				}
				colume++;
			}
		}
		imshow("img", img);
		waitKey();
		imwrite("..\\��ά��.jpg", img);
	}

	void decode(ofstream& ofile) {									//���벿��,����������Ϣ�����ofile��
		Mat img = imread("..\\��ά��.jpg", CV_8UC1);					//��ȡ��ͨ��ͼ
		int Grayscale;												//Grayscale�Ҷȡ�
		bitset<8> bitt;
		int count = 0;												//������ÿ��ȡ8λ�����һ���ַ�
		for (int i = 6; i <= img.rows - 5; i += 4)					//��Ϊÿ4��4�����ش�һλ��Ϣ��
			for (int j = 6; j <= img.cols - 5; j += 4)				//���ÿ4�У�ÿ4�ж�ȡһλ��
			{
				Grayscale = img.at<uchar>(i, j);					//��at������ȡ���صĻҶ�ֵ
				if (count < 8) {
					if (Grayscale > 128) {
						bitt[count] = 0;
						count++;
					}
					else {
						bitt[count] = 1;
						count++;
					}
				}
				else {
					ofile << toDecimal(bitt);						//ÿ��ȡ8λ�����һ���ַ�
					count = 0;
					if (Grayscale > 128) {
						bitt[count] = 0;
						count++;
					}
					else {
						bitt[count] = 1;
						count++;
					}

				}
			}
		ofile << toDecimal(bitt);
	}
}
