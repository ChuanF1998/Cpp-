#pragma once
#include "HuffmanTree.hpp"

#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Charinfo
{
	unsigned char _ch;       //�ַ�ascll��
	size_t _count; //�ַ�����
	string _code;   //�ַ�����
	Charinfo(size_t count = 0)
		: _count(count)
	{}
	bool operator>(const Charinfo& a)const
	{
		return _count > a._count;
	}
	Charinfo operator+(const Charinfo& a)const
	{
		return Charinfo(_count + a._count);
	}
	bool operator==(const Charinfo& a)
	{
		return _count == a._count;
	}
};

class FileCompressHuff
{
public:
	FileCompressHuff();
	void CompressFile(const string& filepath); //ѹ��
	void UncompressFile(const string& filepath); //��ѹ��

private:
	//����������
	void Huffman_code(Huffman_node<Charinfo>* root);
	void WriteHead(FILE* fOut, const std::string& fileName); //дͷ����Ϣ
	string GetFilePost(const string& fileName); //�ļ�����ȡ
	void ReadLine(FILE* fIn, string& strInfo);
private:
	vector<Charinfo> _char;
};