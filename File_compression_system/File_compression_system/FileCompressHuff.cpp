#include "FileCompressHuff.h"



//��ʼ��
FileCompressHuff::FileCompressHuff()
{
	_char.resize(256);
	for (int i = 0; i < 256; ++i) {
		_char[i]._ch = i;
		_char[i]._count = 0;
	}
}

//ͳ���ַ�
void FileCompressHuff::CompressFile(const string& filepath)
{
	//1.ͳ���ַ�
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


	//2.������������
	Huffman_Tree<Charinfo> tree(_char);

	//3.��ȡ����
	Huffman_code(tree.get());

	//4.�û�ȡ�����ַ��������¸�д�ļ�
	fseek(file, 0, SEEK_SET);      //���¶�λ�ļ�ָ��
	FILE* fOut = fopen("2.txt", "w");
	if (fOut == nullptr) {
		assert(false);
		return;
	}

	//д��ͷ����Ϣ
	WriteHead(fOut, filepath);
	char ch = 0;
	int bitCount = 0; //bitλ������
	while (true) {
		read_size = fread(readbuff, 1, 1024, file);
		if (read_size == 0) {
			break;
		}
		//�����ֽڵı���Զ�ȡ�������ݽ�����д
		for (int i = 0; i < read_size; ++i) {
			string strCode = _char[readbuff[i]]._code;
			for (size_t j = 0; j < strCode.size(); ++j) { //�����밴��bitλд��
				ch <<= 1;
				if (strCode[j] == '1') {
					ch |= 1;
				}
				bitCount++;
				if (bitCount == 8) { //��ch�Ѿ���д��һ���ֽ�ʱ��д��ѹ���ļ�
					fputc(ch, fOut);
					bitCount = 0;
					ch = 0;
				}
			}
		}
	}
	
	//���һ��ch���ܲ���8��bitλ��������0������λ
	if (bitCount != 0 && bitCount < 8) {
		ch <<= (8 - bitCount);
		fputc(ch, fOut);
	}

	fclose(file);
	fclose(fOut);
	delete[] readbuff;
}

//дѹ���ļ�ͷ����Ϣ
void FileCompressHuff::WriteHead(FILE* fOut, const std::string& fileName)
{
	assert(fOut);
	string strHead;
	//д�ļ���׺
	strHead += GetFilePost(fileName);
	strHead += '\n';
	//fwrite(filePost.c_str(), 1, filePost.size(), fOut);

	//д����
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

	//����
	_itoa(lineCount, szValue, 10);
	strHead += szValue;
	strHead += '\n';
	
	//�ַ���Ϣ
	strHead += strCount;

	fwrite(strHead.c_str(), 1, strHead.size(), fOut);
}

//��ȡ�ļ���
string FileCompressHuff::GetFilePost(const string& fileName)
{
	auto it = fileName.rfind('.');
	return fileName.substr(it);
}


//��ȡhuffman����
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

//��ѹ�� 
//1.��ȡͷ����Ϣ 2.��ԭhuffman��  3.��ѹ��
void FileCompressHuff::UncompressFile(const string& filepath)
{
	FILE* fIn = fopen(filepath.c_str(), "rb");
	if (fIn == nullptr) {
		assert(false);
		return;
	}

	//�ļ���׺
	string filePost;
	ReadLine(fIn, filePost);

	//�ַ���Ϣ��������
	string strCount;
	ReadLine(fIn, strCount);
	int lineCount = atoi(strCount.c_str());

	//�ַ���Ϣ
	for (int i = 0; i < lineCount; ++i) {
		string strchCount;
		ReadLine(fIn, strchCount);
		
		//����������� \n ����һ��
		if (strchCount.empty()) {
			strchCount += '\n';
			ReadLine(fIn, strchCount);
		}
		_char[(unsigned char)strchCount[0]]._count = atoi(strchCount.c_str() + 2);
	}

	//��ԭhuffman��
	Huffman_Tree<Charinfo> t;
	t.HuffmanBuilt(_char);

	//��ѹ��
	char* readBuff = new char[1024];
	char ch = 0;
	Huffman_node<Charinfo>* pCur = t.get(); 
	size_t unCount = 0;
	size_t fileSize = pCur->_value._count;  //�ļ��ܴ�С
	FILE* fOut = fopen("3.txt", "wb");
	while (true) {
		size_t rdsize = fread(readBuff, 1, 1024, fIn);
		if (0 == rdsize) {
			break;
		}

		for (size_t i = 0; i < rdsize; ++i) {
			//ֻ�轫һ���ֽ���8������λ��������
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