#pragma once

#include "LZHashTable.h"
#include <string>
using namespace std;


class LZ77
{
public:
	LZ77();
	~LZ77();

	void CompressFile(const string& strFilePash); //ѹ���㷨
	void UncompressFile(const string& strFilePath); //��ѹ��
private:
	UCH LongestMatch(USH matchHead, USH& curMatchDist); //��ȡ�ƥ��
private:
	UCH* _pWin; //���������ѹ�����ݵĻ�����
	LZHashTable _pH;
};

