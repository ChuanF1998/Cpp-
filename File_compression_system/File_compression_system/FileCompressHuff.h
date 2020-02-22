#pragma once
#include "HuffmanTree.hpp"

#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Charinfo
{
	unsigned char _ch;       //字符ascll码
	size_t _count; //字符数量
	string _code;   //字符编码
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
	void CompressFile(const string& filepath); //压缩
	void UncompressFile(const string& filepath); //解压缩

private:
	//哈夫曼编码
	void Huffman_code(Huffman_node<Charinfo>* root);
	void WriteHead(FILE* fOut, const std::string& fileName); //写头部信息
	string GetFilePost(const string& fileName); //文件名获取
	void ReadLine(FILE* fIn, string& strInfo);
private:
	vector<Charinfo> _char;
};