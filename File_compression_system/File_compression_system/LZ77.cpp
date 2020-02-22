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

//ѹ���㷨
void LZ77::CompressFile(const string& strFilePath)
{
    //1.���Դ�ļ��Ĵ�СС�� MIN_MATCH���򲻽��д���
	//
	//��ȡ�ļ���С
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	if (fIn == nullptr) {
		cout << "�ļ���СΪ�� ��" << endl;
		return;
	}

	//��ȡ�ļ���С
	fseek(fIn, 0, SEEK_END);
	ULL FileSize= ftell(fIn);

	//1.�ļ���СС��MIN_MATCH���򲻽��д���
	if (FileSize < MIN_MATCH) {
		cout << "�ļ�̫С" << endl;
		return;
	}

	//��ѹ���ļ��ж�ȡһ�������������ݵ�������
	fseek(fIn, 0, SEEK_SET);
	USH lookAhead = fread(_pWin, 1, 2 * WSIZE, fIn);
	USH start = 0;
	USH hashAddr = 0;
	USH matchHead = 0;
	UCH curMatchLength = 0;  //ƥ��������
	USH curMatchDist = 0;    //����

	//������ʼλ��ǰ2���ַ���hashaddrֵ
	for (USH i = 0; i < MIN_MATCH - 1; ++i) {
		_pH.HashFunc(hashAddr, _pWin[i]);
	}

	//������ļ�
	FILE* fOut = fopen("2.txt", "wb");
	assert(fOut);

	//lookAhead��ʾ���л�������ʣ���ֽڵĸ���
	while (lookAhead) {
		//1.��ȡƥ��ͷ
	    _pH.Insert(matchHead, _pWin[start + 2], start, hashAddr);

		//2.��֤�ڲ��һ��������Ƿ��ҵ�ƥ�䣬��ƥ�䣬���
		if (matchHead) {
			//˳��ƥ�������,���յõ� <���ȣ� ����> ��
			curMatchLength = LongestMatch(matchHead, curMatchDist);
		}

		//3.��֤�Ƿ��ҵ�ƥ��
		if (curMatchLength < MIN_MATCH) {
			//�ڲ��һ�������û���ҵ�ƥ��
			//��startλ�õ��ַ�д�뵽ѹ���ļ���
			start++;
		}
		else {
			//�ҵ�ƥ�䣬��<���ȣ� ����> �Բ���

			//д����
			fputc(curMatchLength, fOut);
            //д����
			fwrite(&curMatchDist, sizeof(curMatchDist), 1, fOut);

			//�������л�������ʣ����ֽ���
			lookAhead -= curMatchLength;

			//���Ѿ�ƥ����ַ�����������һ����뵽hash����
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