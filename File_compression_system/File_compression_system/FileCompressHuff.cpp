#include "FileCompressHuff.h"



//初始化
FileCompressHuff::FileCompressHuff()
{
	_char.resize(256);
	for (int i = 0; i < 256; ++i) {
		_char[i]._ch = i;
		_char[i]._count = 0;
	}
}

//统计字符
void FileCompressHuff::CompressFile(const string& filepath)
{
	//1.统计字符
	FILE* file = fopen(filepath.c_str(), "rb");
	if (file == nullptr) {
		assert(false);
		return;
	}

	unsigned char* readbuff = new unsigned char[1024];
	int read_size = 0;
	while (true) {
		read_size = fread(readbuff, 1, 1024, file);
		if (read_size == 0) {
			break;
		}
		for (int i = 0; i < read_size; ++i) {
			++_char[readbuff[i]]._count;
		}
	}


	//2.创建哈夫曼树
	Huffman_Tree<Charinfo> tree(_char);

	//3.获取编码
	Huffman_code(tree.get());

	//4.用获取到的字符编码重新改写文件
	fseek(file, 0, SEEK_SET);      //重新定位文件指针
	FILE* fOut = fopen("2.txt", "w");
	if (fOut == nullptr) {
		assert(false);
		return;
	}

	//写入头部信息
	WriteHead(fOut, filepath);
	char ch = 0;
	int bitCount = 0; //bit位计数器
	while (true) {
		read_size = fread(readbuff, 1, 1024, file);
		if (read_size == 0) {
			break;
		}
		//根据字节的编码对读取到的内容进行重写
		for (int i = 0; i < read_size; ++i) {
			string strCode = _char[readbuff[i]]._code;
			for (size_t j = 0; j < strCode.size(); ++j) { //将编码按照bit位写入
				ch <<= 1;
				if (strCode[j] == '1') {
					ch |= 1;
				}
				bitCount++;
				if (bitCount == 8) { //当ch已经被写入一个字节时，写入压缩文件
					fputc(ch, fOut);
					bitCount = 0;
					ch = 0;
				}
			}
		}
	}
	
	//最后一次ch可能不够8个bit位但不包括0个比特位
	if (bitCount != 0 && bitCount < 8) {
		ch <<= (8 - bitCount);
		fputc(ch, fOut);
	}

	fclose(file);
	fclose(fOut);
	delete[] readbuff;
}

//写压缩文件头部信息
void FileCompressHuff::WriteHead(FILE* fOut, const std::string& fileName)
{
	assert(fOut);
	string strHead;
	//写文件后缀
	strHead += GetFilePost(fileName);
	strHead += '\n';
	//fwrite(filePost.c_str(), 1, filePost.size(), fOut);

	//写行数
	size_t lineCount = 0;
	string strCount;
	char szValue[32] = { 0 };
	for (int i = 0; i < 256; ++i) {
		if (_char[i]._count) {
			lineCount++;
			strCount += _char[i]._ch;
			strCount += ':';
			_itoa(_char[i]._count, szValue, 10);
			strCount += szValue;
			strCount += '\n';
		}
	}

	//行数
	_itoa(lineCount, szValue, 10);
	strHead += szValue;
	strHead += '\n';
	
	//字符信息
	strHead += strCount;

	fwrite(strHead.c_str(), 1, strHead.size(), fOut);
}

//获取文件名
string FileCompressHuff::GetFilePost(const string& fileName)
{
	auto it = fileName.rfind('.');
	return fileName.substr(it);
}


//获取huffman编码
void FileCompressHuff::Huffman_code(Huffman_node<Charinfo>* root)
{
	if (root == nullptr) {
		return;
	}
	Huffman_code(root->_Lchild);
	Huffman_code(root->_Rchild);

	if (root->_Lchild == nullptr && root->_Rchild == nullptr) {
		string code;
		Huffman_node<Charinfo>* temp = root;
		Huffman_node<Charinfo>* parent = temp->_Parent;
		while (parent) {
			if (temp == parent->_Lchild) {
				code += '0';
			}
			else {
				code += '1';
			}
			temp = parent;
			parent = temp->_Parent;
		}
		reverse(code.begin(), code.end());
		_char[root->_value._ch]._code = code;
	}
}

//解压缩 
//1.获取头部信息 2.还原huffman树  3.解压缩
void FileCompressHuff::UncompressFile(const string& filepath)
{
	FILE* fIn = fopen(filepath.c_str(), "rb");
	if (fIn == nullptr) {
		assert(false);
		return;
	}

	//文件后缀
	string filePost;
	ReadLine(fIn, filePost);

	//字符信息的总行数
	string strCount;
	ReadLine(fIn, strCount);
	int lineCount = atoi(strCount.c_str());

	//字符信息
	for (int i = 0; i < lineCount; ++i) {
		string strchCount;
		ReadLine(fIn, strchCount);
		
		//如果读到换行 \n 则多读一行
		if (strchCount.empty()) {
			strchCount += '\n';
			ReadLine(fIn, strchCount);
		}
		_char[(unsigned char)strchCount[0]]._count = atoi(strchCount.c_str() + 2);
	}

	//还原huffman树
	Huffman_Tree<Charinfo> t;
	t.HuffmanBuilt(_char);

	//解压缩
	char* readBuff = new char[1024];
	char ch = 0;
	Huffman_node<Charinfo>* pCur = t.get(); 
	size_t unCount = 0;
	size_t fileSize = pCur->_value._count;  //文件总大小
	FILE* fOut = fopen("3.txt", "wb");
	while (true) {
		size_t rdsize = fread(readBuff, 1, 1024, fIn);
		if (0 == rdsize) {
			break;
		}

		for (size_t i = 0; i < rdsize; ++i) {
			//只需将一个字节中8个比特位单独处理
			ch = readBuff[i];
			for (int pos = 0; pos < 8; ++pos) {
				if (ch & 0x80) {
					pCur = pCur->_Rchild;
				}
				else {
					pCur = pCur->_Lchild;
				}
				ch <<= 1;
				if (pCur->_Lchild == nullptr && pCur->_Rchild == nullptr) {
					fputc(pCur->_value._ch, fOut);
					unCount++;
					pCur = t.get();
					if (unCount == fileSize) {
						break;
					}
				}
			}
		}
	}
	delete[] readBuff;
	fclose(fIn);
	fclose(fOut);
}



void FileCompressHuff::ReadLine(FILE* fIn, string& strInfo)
{
	assert(fIn);
	
	while (!feof(fIn)) {
		char ch = fgetc(fIn);
		if (ch == '\n') {
			break;
		}
		strInfo += ch;
	}
	
}