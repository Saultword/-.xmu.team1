#include "decoding.h"

using namespace enAndde_code;

int main() {
//	ofstream infile("..\\in.txt", ios::out);								//�����������������txt�ļ�
//	form(infile);															//�õ�ʱ��������ע�͵��������У�
	ifstream infile("..\\in.txt", ios::in);
	ofstream outfile("..\\out.txt", ios::out && ios::binary);
	encode(infile);															//��infile�е����ݱ��룬���ɶ�ά��
	decode(outfile);														//����ά����룬��д�뵽outfile��
	outfile.close();		
	infile.close();
	return 0;
}

