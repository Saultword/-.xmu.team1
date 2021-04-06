#include"encoding.h"

namespace encoding {

    //���ļ�+����string
    string getFile() {

        //���ļ�
        string path = "e1.bin";
        string rt;
        cout << "�������ļ�����" << endl;
        cin >> path;

        fstream file(path, ios::binary | ios::in);
        if (!file) {
            cout << "Open file failed!" << endl;
            return rt;
        }

        unsigned char ch;

        while (file.read((char*)&ch, sizeof(ch)) && rt.size() < (FRAME_MAX * MAX_SIZE) / 8)rt += ch;

        return rt;
    }

    //�ļ�ת���ɶ�����
    string file2Binary(string s) {
        string rt;
        int len = s.length();
        for (int i = 0; i < len; i++) {
            unsigned char ch = s[i];
            for (int j = 0; j < 8; j++) {
                if (ch % 2)rt += '1';
                else rt += '0';
                ch /= 2;
            }
        }
        return rt;
    }

    //��д���ļ��ֿ�
    vector<string> split(string s) {
        vector<string> rt;
        int len = s.size();
        int head = 0, end = min(head + MAX_SIZE, len);
        while (head != len) {
            string tmp;
            for (int i = head; i < end; i++) {
                tmp.push_back(s[i]);
            }
            rt.push_back(tmp);
            head = end;
            end = min(head + MAX_SIZE, len);
        }
        return rt;
    }

    //��string�ڴ�Ķ�������Ϣ����Mat
    Mat string2Mat(string s, int num) {
        Mat img(DATA_LENGTH, DATA_LENGTH, CV_8UC1);

        //����������Ϣ
        for (int i = 7; i >= 0; i--) {
            img.ptr<uchar>(0)[i] = (num % 2 ? 255 : 0);
            num /= 2;
        }

        //��������
        int cnt = 0, len = s.size();
        for (int i = 0; i < DATA_LENGTH; i++) {
            for (int j = 0; j < DATA_LENGTH; j++) {
                if (i == 0 && j < 8)continue;
                if (cnt >= len)img.ptr<uchar>(i)[j] = 0;
                else img.ptr<uchar>(i)[j] = (s[cnt++] == '1' ? 255 : 0);
            }
        }

        //�Ŵ�ͼƬ
        Mat bigger_img(800, 800, CV_8UC1);


        for (int i = 0; i < 800; i++) {
            for (int j = 0; j < 800; j++) {
                int x = i / PIX_SIZE;
                int y = j / PIX_SIZE;
                bigger_img.ptr<uchar>(i)[j] = img.ptr<uchar>(x)[y];
            }
        }


        //�������
        Mat rt(1000, 1000, CV_8UC1);

        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                rt.ptr<uchar>(i)[j] = 255;
                if (i <= 916 && i >= 84 && j <= 916 && j >= 84) {
                    rt.ptr<uchar>(i)[j] = 0;
                }
                /*���ںڿ�ֻ��4pixel*/
                if (i <= 912 && i >= 88 && j <= 912 && j >= 88) {
                    rt.ptr<uchar>(i)[j] = 255;
                }
            }
        }

        //�������������Ϣ
        for (int i = 100; i < 900; i++) {
            for (int j = 100; j < 900; j++) {
                rt.ptr<uchar>(i)[j] = bigger_img.ptr<uchar>(i - 100)[j - 100];
            }
        }

        return rt;
    }

    //��������
    vector<Mat> string2Mat_vector(vector<string> s) {
        int len = s.size();

        //����
        len = min(len, FRAME_MAX);
        vector<Mat> rt;
        for (int i = 0; i < len; i++) {
            Mat tmp = string2Mat(s[i], i + 1);
            rt.push_back(tmp);
        }
        return rt;
    }
}