#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <vector>
#define charNumber 5000												//�ַ����������5000��
using namespace std;
using namespace cv;

namespace enAndde_code {
	vector<string> pool;
	double whiteGrayscale_percent(Mat img, int x, int y) {
		int white = 0;
		for (int i = x; i < x + 4; i++) {
			for (int j = y; j < y + 4; j++) {
				if (img.at<uchar>(i, j) > 128) white++;
			}
		}
		return white / 16.0;
	}
	void print_01(Mat img, int x, int y) {
		String s = "";
		for (int i = x; i < x + 400; i += 4) {
			for (int j = y; j < y + 400; j += 4) {
				if (whiteGrayscale_percent(img, i, j) > 0.5) s += '0';
				else s += '1';
			}
		}
		pool.push_back(s);
	}
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
		Mat	img = Mat::zeros(820, 820, CV_8UC1);
		char c;
		int colume = 0;
		int row = 0;
		Rect rec_up = Rect(5, 5, 810, 5);
		Rect rec_down = Rect(5, 810, 810, 5);
		Rect rec_left = Rect(5, 10, 5, 800);
		Rect rec_right = Rect(810, 10, 5, 800);
		rectangle(img, rec_up, Scalar(255), -1, 8, 0);
		rectangle(img, rec_down, Scalar(255), -1, 8, 0);
		rectangle(img, rec_left, Scalar(255), -1, 8, 0);
		rectangle(img, rec_right, Scalar(255), -1, 8, 0);
		while (ifile.peek() != EOF) {
			ifile >> c;
			bitset<8> ch = toBinary(c);
			for (int i = 0; i < 8; i++) {
				if (colume >= 200) {								//ÿһ�д洢200λ��Ϣ��һ�д�����Ϣ����һ�д���
					colume = 0;
					row++;
				}
				if (ch[i] == 0) {
					Rect rec1 = Rect(10 + 4 * colume, 10 + 4 * row, 4, 4);
					rectangle(img, rec1, Scalar(255), -1, 8, 0);
				}
				colume++;
			}
		}
		imshow("img", img);
		waitKey();
		imwrite("..\\��ά��.jpg", img);
	}

	void decode() {									//���벿��,����������Ϣ�����ofile��  decode(ofstream& ofile_01)
		Mat img = imread("..\\��ά��.jpg", CV_8UC1);					//��ȡ��ͨ��ͼ
		int Grayscale;												//Grayscale�Ҷȡ�
		bitset<8> bitt;
		print_01(img, 11, 11);										
		print_01(img, 411, 11);
		print_01(img, 11, 411);
		print_01(img, 411, 411);
//		infile >> bitt;
//		cout << toDecimal(bitt);

		/*
		int count = 0;												//������ÿ��ȡ8λ�����һ���ַ�
		for (int i = 12; i <= img.rows - 10; i += 4)					//��Ϊÿ4��4�����ش�һλ��Ϣ��
			for (int j = 12; j <= img.cols - 10; j += 4)				//���ÿ4�У�ÿ4�ж�ȡһλ��
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
		*/
	}
}
