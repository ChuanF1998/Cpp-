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


#include "LZ77.h"
#include <string>

int main()
{
	LZ77 lz;

	std::string postFix;
	lz.CompressFile("1.txt", postFix);
	lz.UncompressFile("1.lzp", postFix);
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