#include "LZ77.h"

#include <assert.h>
#include <iostream>
using namespace std;

LZ77::LZ77()
: _pWin(new UCH[WSIZE * 2])
, _pH(WSIZE)
{}

LZ77::~LZ77()
{
	delete[] _pWin;
	_pWin = nullptr;
}

//压缩算法
void LZ77::CompressFile(const string& strFilePath)
{
    //1.如果源文件的大小小于 MIN_MATCH，则不进行处理
	//
	//获取文件大小
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	if (fIn == nullptr) {
		cout << "文件大小为空 ！" << endl;
		return;
	}

	//获取文件大小
	fseek(fIn, 0, SEEK_END);
	ULL FileSize= ftell(fIn);

	//1.文件大小小于MIN_MATCH，则不进行处理
	if (FileSize < MIN_MATCH) {
		cout << "文件太小" << endl;
		return;
	}

	//从压缩文件中读取一个缓冲区的数据到窗口中
	fseek(fIn, 0, SEEK_SET);
	USH lookAhead = fread(_pWin, 1, 2 * WSIZE, fIn);
	USH start = 0;
	USH hashAddr = 0;
	USH matchHead = 0;
	UCH curMatchLength = 0;  //匹配链长度
	USH curMatchDist = 0;    //距离

	//计算起始位置前2个字符的hashaddr值
	for (USH i = 0; i < MIN_MATCH - 1; ++i) {
		_pH.HashFunc(hashAddr, _pWin[i]);
	}

	//打开输出文件
	FILE* fOut = fopen("2.txt", "wb");
	assert(fOut);

	//lookAhead表示先行缓冲区中剩余字节的个数
	while (lookAhead) {
		//1.获取匹配头
	    _pH.Insert(matchHead, _pWin[start + 2], start, hashAddr);

		//2.验证在查找缓冲区中是否找到匹配，有匹配，找最长
		if (matchHead) {
			//顺着匹配链找最长,最终得到 <长度， 距离> 对
			curMatchLength = LongestMatch(matchHead, curMatchDist);
		}

		//3.验证是否找到匹配
		if (curMatchLength < MIN_MATCH) {
			//在查找缓冲区中没有找到匹配
			//将start位置的字符写入到压缩文件中
			start++;
		}
		else {
			//找到匹配，将<长度， 距离> 对插入

			//写长度
			fputc(curMatchLength, fOut);
            //写距离
			fwrite(&curMatchDist, sizeof(curMatchDist), 1, fOut);

			//更新先行缓冲区中剩余的字节数
			lookAhead -= curMatchLength;

			//将已经匹配的字符串按照三个一组插入到hash表中
			curMatchLength -= 1;
			while (curMatchLength) {
				start++;
				_pH.Insert(matchHead, _pWin[start], start, hashAddr);
				curMatchDist--;				
			}
		}

	}



}




UCH LZ77::LongestMatch(USH matchHead, USH& curMatchDist)
{
	return 0;
}