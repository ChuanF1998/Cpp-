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
		string(const string& str); //拷贝构造
		string(const string& str, size_t n); //拷贝str的前n个字符
		size_t size()const;  //字符串长度
		size_t capacity()const; //返回空间大小
		bool empty()const; //字符串是否为空
		void clear(); //清空
		string& erase(size_t pos = 0, size_t n = 1); //从pos位置向后删除n个字符
		void resize(size_t n, char c);
		void resize(size_t n);
		void reserve(size_t res_arg = 0); //为字符串预留空间
		char& operator[] (size_t pos);
		const char& operator[] (size_t pos)const;
		string& operator+= (const char* str);
		string& operator+= (const char c);
		void push_back(char c); //插入
		void pop_back();  //删除
		size_t find(char c, size_t pos = 0)const; //从pos位置向后查找，返回找到的第一个相同字符的下标
		string substr(size_t pos = 0, size_t n = npos)const;
		const char* c_str()const; //返回char型字符串
		~string();
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}