#pragma once

#include <string.h>

const size_t npos = 0;
namespace My_string
{
	typedef char* iterator;
	class string
	{
	public:
		string();
		string(const char* str);
		string(size_t n, char c);
		string(const string& str); //��������
		string(const string& str, size_t n); //����str��ǰn���ַ�
		size_t size()const;  //�ַ�������
		size_t capacity()const; //���ؿռ��С
		bool empty()const; //�ַ����Ƿ�Ϊ��
		void clear(); //���
		string& erase(size_t pos = 0, size_t n = 1); //��posλ�����ɾ��n���ַ�
		void resize(size_t n, char c);
		void resize(size_t n);
		void reserve(size_t res_arg = 0); //Ϊ�ַ���Ԥ���ռ�
		char& operator[] (size_t pos);
		const char& operator[] (size_t pos)const;
		string& operator+= (const char* str);
		string& operator+= (const char c);
		void push_back(char c); //����
		void pop_back();  //ɾ��
		size_t find(char c, size_t pos = 0)const; //��posλ�������ң������ҵ��ĵ�һ����ͬ�ַ����±�
		string substr(size_t pos = 0, size_t n = npos)const;
		const char* c_str()const; //����char���ַ���
		~string();
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}