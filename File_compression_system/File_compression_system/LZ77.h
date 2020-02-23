#pragma once

#include "LZHashTable.h"
#include <string>
using namespace std;


class LZ77
{
public:
	LZ77();
	~LZ77();

	void CompressFile(const string& strFilePash); //压缩算法
	void UncompressFile(const string& strFilePath); //解压缩
	
private:
	USH LongestMatch(USH matchHead, USH& curMatchDist, USH start); //获取最长匹配
	void WriteFlag(FILE* fOut, UCH& chFlag, USH& bitCount, bool isLen);
private:
	UCH* _pWin; //用来保存待压缩数据的缓冲区
	LZHashTable _pH;
};

