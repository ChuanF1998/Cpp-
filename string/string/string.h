#pragma once

#include <string.h>

namespace My_string
{
	class string
	{
	public:
		string();
		string(const char* str);
		string(const string& str); //拷贝构造
		size_t size()const;  //字符串长度
		size_t capacity()const; //返回空间大小
	private:
		char* _str;
	};
}