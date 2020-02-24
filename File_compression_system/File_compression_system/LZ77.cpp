#include "LZ77.h"

//curMatchlength������

#include <assert.h>
#include <iostream>
using namespace std;


const USH MIN_LOOKAHEAD = MAX_MATCH + MIN_MATCH + 1;
const USH MAX_DIST = WSIZE - MIN_LOOKAHEAD;

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

	//��д�����صı���
	UCH chFlag = 0;  
	USH bitCount = 0;
	bool isLen = false;
	FILE* fOutFlag = fopen("3.txt", "wb");  //д��ǵ��ļ�

	USH start = 0;
	USH hashAddr = 0;
	USH matchHead = 0;
	USH curMatchLength = 0;  //ƥ��������
	USH curMatchDist = 0;    //����

	//������ʼλ��ǰ2���ַ���hashaddrֵ
	for (USH i = 0; i < MIN_MATCH - 1; ++i) {
		_pH.HashFunc(hashAddr, _pWin[i]);
	}

	//������ļ�
	FILE* fOut = fopen("2.txt", "wb");
	assert(fOut);

	ULL fileSize = 0; //�ļ���С

	//lookAhead��ʾ���л�������ʣ���ֽڵĸ���
	while (lookAhead) {
		//ƥ��֮ǰ�������Ⱥ;�������
		curMatchDist = 0;
		curMatchLength = 0;

		//1.��ȡƥ��ͷ
	    _pH.Insert(matchHead, _pWin[start + 2], start, hashAddr);

		//2.��֤�ڲ��һ��������Ƿ��ҵ�ƥ�䣬��ƥ�䣬���
		if (matchHead) {
			//˳��ƥ�������,���յõ� <���ȣ� ����> ��
			curMatchLength = LongestMatch(matchHead, curMatchDist, start);
		}

		//3.��֤�Ƿ��ҵ�ƥ��
		if (curMatchLength < MIN_MATCH) {
			//�ڲ��һ�������û���ҵ�ƥ��
			//��startλ�õ��ַ�д�뵽ѹ���ļ���
			fputc(_pWin[start], fOut);

			//дԭ�ַ���Ӧ�ı��
			WriteFlag(fOutFlag, chFlag, bitCount, false);
			start++;
			lookAhead--;
			fileSize++;
		}
		else {
			//�ҵ�ƥ�䣬��<���ȣ� ����> �Բ���

			//д����
			UCH ch = (UCH)(curMatchLength - 3);
			fputc(ch, fOut);
            //д����
			fwrite(&curMatchDist, sizeof(curMatchDist), 1, fOut);

			//дԭ�ַ���Ӧ�ı��
			WriteFlag(fOutFlag, chFlag, bitCount, true);

			//�������л�������ʣ����ֽ���
			lookAhead -= curMatchLength;

			fileSize += curMatchLength;

			//���Ѿ�ƥ����ַ�����������һ����뵽hash����
			curMatchLength -= 1;
			while (curMatchLength) {
				start++;
				_pH.Insert(matchHead, _pWin[start + 2], start, hashAddr);
				curMatchLength--;				
			}
			start++;
		}

	}

	//���λ����8������λ
	if (bitCount != 0 && bitCount < 8) {
		chFlag <<= (8 - bitCount);
		fputc(chFlag, fOutFlag);
	}

	fclose(fIn);
	fclose(fOutFlag);

	//�ϲ�ѹ���ļ�
	//1.��ȡ�����Ϣ�ļ������ݣ�Ȼ�󽫽��д�뵽ѹ���ļ���
	FILE* fInF = fopen("3.txt", "rb");

	ULL flagSize = 0;
	UCH* pReadBuff = new UCH[1024];
	while (true) {
		size_t rdSize = fread(pReadBuff, 1, 1024, fInF);
		if (rdSize == 0) {
			break;
		}

		fwrite(pReadBuff, 1, rdSize, fOut);
		flagSize += rdSize;
	}

	fwrite(&flagSize, sizeof(flagSize), 1, fOut);

	//�ر��ļ�
	
	fclose(fOut);
	

}

//chFlag:���ֽڵ�ÿ������λ�������ֵ�ǰ�ַ���ԭ�ַ����ǳ��� 0--ԭ�ַ�  1--����
//islen:������ֽ���ԭ�ַ����ǳ���
void LZ77::WriteFlag(FILE* fOut, UCH& chFlag, USH& bitCount, bool isLen)
{
	chFlag <<= 1;
	if (isLen) {
		chFlag |= 1;
	}
	bitCount++;
	if (bitCount == 8 && bitCount != 0) {
		//���ñ��д�뵽ѹ���ļ���
		fputc(chFlag, fOut);
		chFlag = 0;
		bitCount = 0;
	}
}


//ƥ�䣺���ڲ��һ������н��еģ����һ������п��ܻ��ҵ����ƥ��
//������ƥ��
//ע��������ܻ�������״�������������ƥ�����
//ƥ����MAX_DIST��Χ��ƥ�䣬̫Զ������ƥ��
USH LZ77::LongestMatch(USH matchHead, USH& curMatchDist, USH start)
{
	UCH curMatchLen = 0;   //һ��ƥ�䳤��
	UCH maxMatchLen = 0;   //���ƥ�䳤��
	UCH maxMatchCount = 255; //���ƥ�����
	USH curMatchStart = 0; //��ǰƥ���ڲ��һ������е�λ��
	
	//�����л������в���ƥ��ʱ������̫Զ�����ܳ���MAX_DIST
	USH limit = start > MAX_DIST ? start - MAX_DIST : 0;

	do {
		//ƥ�䷶Χ
		UCH* pStart = _pWin + start;
		UCH* pEnd = pStart + MAX_MATCH;

		//���һ�����ƥ�䴮����ʼ
		UCH* pMatchStart = _pWin + matchHead;
		curMatchLen = 0;

		//����ƥ��
		while (pStart < pEnd && *pStart == *pMatchStart) {
			curMatchLen++;
			pStart++;
			pMatchStart++;
		}

		//һ��ƥ�����
		if (curMatchLen > maxMatchLen) {
			maxMatchLen = curMatchLen;
			curMatchStart = matchHead;
		}

	} while ((matchHead = _pH.GetNext(matchHead)) > limit &&  maxMatchCount--);

	//����
	curMatchDist = start - curMatchStart;

	return maxMatchLen;
}



//��ѹ��
void LZ77::UncompressFile(const string& strFilePath)
{
	//��ѹ���ļ��ͱ���ļ�
	FILE* fIn = fopen("2.txt", "rb");
	if (fIn == nullptr) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	FILE* fIn_Flag = fopen("3.txt", "rb");
	if (fIn_Flag == nullptr) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}

	FILE* fOut = fopen("4.txt", "wb");
	if (fOut == nullptr) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}

	FILE* fOut_r = fopen("4.txt", "rb");

	UCH bitCount = 0;
	UCH chFlag = 0;
	while (!feof(fIn)) {
		if (bitCount == 0) {
			chFlag = fgetc(fIn_Flag);
			bitCount = 8;
		}


		//���Ϊ1
		if (chFlag & 0x80) {
			//<����,����>��
			USH matchLen = fgetc(fIn) + 3;
			USH matchDist = 0;
			fread(&matchDist, sizeof(matchDist), 1, fIn);

			UCH ch;
			//��ջ�����
			fflush(fOut);
			//fOut_r:��ȡǰ��ƥ�������
			fseek(fOut_r, 0 - matchDist, SEEK_END);
			while (matchLen != 0) {
				 ch = fgetc(fOut_r);
				 fputc(ch, fOut);
				 matchLen--;
			}

		}
		else {
			//ԭ�ַ�
			UCH ch = fgetc(fIn);
			fputc(ch, fOut);
		}

		chFlag <<= 1;
		bitCount--;
	}

	fclose(fIn);
	fclose(fIn_Flag);
	fclose(fOut);
	fclose(fOut_r);

}



