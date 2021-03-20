#include "module3.h"

using namespace module3;

int main()
{
	char window_name[15] = "Module3_2Dcode";

	//������ʾ����
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	//����һ��ͼƬ�����롢����ӿ�
	vector<Mat> src_images;

	//���Խӿ�
	Mat src_image = imread("./test.jpg");

	src_images.push_back(src_image);

	src_images = get_QRcode(src_images);
	

	//��ʾ���
	imshow(window_name, src_images[0]);
	imwrite("C:/Users/df/Desktop/duibi.jpg", src_images[0]);
	// �ȴ��û���Ӧ
	waitKey(0);

	return 0;
}