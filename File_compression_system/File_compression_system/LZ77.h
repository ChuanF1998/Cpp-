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
	USH LongestMatch(USH matchHead, USH& curMatchDist, USH start); //��ȡ�ƥ��
	void WriteFlag(FILE* fOut, UCH& chFlag, USH& bitCount, bool isLen);
private:
	UCH* _pWin; //���������ѹ�����ݵĻ�����
	LZHashTable _pH;
};

