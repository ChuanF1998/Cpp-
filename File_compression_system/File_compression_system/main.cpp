/*
�ļ�ѹ����
1.ʲô���ļ�ѹ����
2.ΪʲôҪ���ļ�����ѹ����
   �ļ�̫�󣬽�ʡ�ռ�
   ��������������ϴ����Ч��
   �����ݱ���������--����
3.�ļ�ѹ�����ࣿ
    ����ѹ����
	����ѹ������ѹ��֮���ܽ��仹ԭ����Դ�ļ���ȫ��ͬ�ĸ�ʽ
4.��ν���ѹ����
*/

/*
ѹ���ļ����������֣�ѹ����Ϣ��Դ�ļ���׺����������, �ַ�������Ϣ
                    ѹ�����ݣ�
*/

#if 0
#include "FileCompressHuff.h"



int main()
{
	FileCompressHuff fc;
	fc.CompressFile("1.txt");
	fc.UncompressFile("2.txt");
	return 0;
}

#endif

#include "FileCompressHuff.h"
#include "LZ77.h"
#include <time.h>
#include <string>
#include <iostream>

int main()
{
	LZ77 lz;
	FileCompressHuff hu;
	//clock_t start_time, finish_time;
	//clock_t time;
	//double cord_time = 0.0;
	std::string postFix;
	
	std::string fileName;
	while (std::cin >> fileName) {
		size_t pos = fileName.find('.');
		string comFile = fileName.substr(0, pos) + ".lzp";
		string hf_comFile = fileName.substr(0, pos) + "_hf.lzp";
		string uhf_comFile = fileName.substr(0, pos) + "_hf_u.lzp";
		//hu.CompressFile(fileName);
		//hu.UncompressFile(hf_comFile);
		//for (int i = 0; i < 10; ++i) {
			//start_time = clock();
			lz.CompressFile(fileName, postFix);	
			hu.CompressFile(comFile);
			hu.UncompressFile(hf_comFile);
			lz.UncompressFile(uhf_comFile, postFix);
			//finish_time = clock();
			//time = (double)(finish_time - start_time);
			//cord_time += time;
			//std::cout << time << std::endl;
		//}
		//std::cout << cord_time / 10 << std::endl;
	}
	return 0;
}

/*
����1��������char�Σ�Ҫ��unsiged char
����2����д����һ���ո�ѹ���ļ�
*/

/*
1.ѹ�����ݸ�ʽ
2.����-->��λ���⣿��ν����
3.�ļ�ѹ�����߽�ѹ��һ����
4.��α�֤ѹ������ȷ�ԣ���---beyond compare
5.ѹ������
6.�ǲ���ÿ��ѹ��֮�󶼻��С��������
7.�ı��ļ�����Ƶ�ļ�����Ƶ��ͼƬ
8.�Ľ��ķ�ʽ
*/

/*
LZ77:
1.������������
*/