#include"decoding.h"


namespace decoding {

    //��ȡÿһ����Ϣ���ںڰױ���
    double whiteGrayscale_percent(Mat img, int x, int y) {
        int white = 0;
        for (int i = x; i < x + PIX_SIZE; i++) {
            for (int j = y; j < y + PIX_SIZE; j++) {
                if (img.at<uchar>(i, j) > 128) white++;
            }
        }
        return white / ((double)PIX_SIZE * PIX_SIZE);
    }

    //��ͼƬ�����ؿ���б���������/����������һ����ֵ�����ж�Ϊ��/�ף�����Ϊ����
    string print_01(Mat img, int x, int y) {
        string s = "";
        for (int i = x; i < x + 800; i += PIX_SIZE) {
            for (int j = y; j < y + 800; j += PIX_SIZE) {
                double rate = whiteGrayscale_percent(img, i, j);
                if (rate > 0.6) s += '1';
                else if (rate < 0.4)s += '0';
                else s += '-';
            }
        }
        return s;
    }

    //����ͼƬ����
    string decode(const Mat& img) {
        string rt = print_01(img, 16, 16);
        return rt;
    }

    //�ӿ�
    void decoding(const vector<Mat>& rec) {

        string path2 = "1.bin", path3 = "v1.bin";

        cout << "��������Ϣ�ļ�����" << endl;
        cin >> path2;
        cout << "������У���ļ�����" << endl;
        cin >> path3;

        fstream file(path2, ios::binary | ios::out);
        fstream vfile(path3, ios::binary | ios::out);

        //��¼ÿ����ŵ�ͼƬ�Ƿ񱻶�ȡ��
        int used[5000] = { 0 };

        //�ӵ�һ��ͼƬ��ʼ��ȡ
        int pic_tag = 1;

        for (int i = 0; i < rec.size(); i++) {

            //��ȡͼƬ�е�0-1��
            string s = decoding::decode(rec[i]);
            int num = 0;

            //���ͼƬ�����Ϣ
            for (int j = 0; j < s.size() && j < 8; j++) {
                num *= 2;
                num += (s[j] == '1' ? 1 : 0);
                if (s[j] == '-') { num = 10000; break; }
            }

            //�����ȡͼƬ��Ų���ȷ
            if (num != pic_tag)continue;

            //ѡȡÿ����ŵĵڶ���ͼƬ
            if (!used[num]) { used[num]++; continue; }

            //��ȡ��һ��ͼƬ
            pic_tag++;

            //�����Ϣ��������Ϊ'-'�͵������봦��
            for (int j = 8; j < s.size(); j += 8) {
                unsigned char ch = 0, lg = 0;
                bool flag = 1;
                for (int k = j + 7; k >= j; k--) {
                    ch *= 2;
                    ch += s[k] == '1' ? 1 : 0;
                    lg *= 2;
                    lg += s[k] == '-' ? 0 : 1;
                }
                file.write((char*)&ch, sizeof(ch));
                vfile.write((char*)&lg, sizeof(ch));
            }
        }
    }

}