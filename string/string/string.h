#pragma once

#include <string.h>

namespace My_string
{
	class string
	{
	public:
		string();
		string(const char* str);
		string(const string& str); //��������
		size_t size()const;  //�ַ�������
		size_t capacity()const; //���ؿռ��С
	private:
		char* _str;
	};
}