#define _CRT_SECURE_NO_WARNINGS
#include "string.h"

My_string::string::string(){}
My_string::string::string(const char* str = "")
    : _str(new char[strlen(str) + 1])
    , _size(strlen(str))
    , _capacity(_size)
{
	strcpy(_str, str);
	//_str[_size] = '\0';
}

My_string::string::string(size_t n, char c)
    : _str(new char[n + 1])
    , _size(n)
    , _capacity(n)
{
	for (size_t i = 0; i < n; ++i) {
		_str[i] = c;
	}
}

My_string::string::~string()
{
	delete[] _str;
	_size = 0;
	_capacity = 0;
}

//�������캯��
My_string::string::string(const string& str)
: _str(new char[str._size + 1])
, _size(str._size)
, _capacity(_size)
{
	strcpy(_str, str._str);
}

My_string::string::string(const string& str, size_t n)
{	
	//nС�ڵ���Դ�ַ�������
	if (n <= str._size) {
		_str = new char[n + 1];
		_size = n + 1;
		_capacity = _size;
		for (size_t i = 0; i < n; ++i) {
			_str[i] = str._str[i];
		}	
	}
	//n����Դ�ַ�������ʱ��ֻ����str��size��С����
	else {
		_str = new char[str._size + 1];
		strcpy(_str, str._str);
		_size = str._size;
		_capacity = _size;
	}
}

char& My_string::string::operator[] (size_t pos)
{
	return _str[pos];
}

const char& My_string::string::operator[] (size_t pos)const
{
	return _str[pos];
}

My_string::string& My_string::string::operator+= (const char* str)
{
	size_t addSize = strlen(str);
	if (_capacity < _size + addSize) {
		reserve(_size + addSize);
	}
	strncpy(_str + _size, str, strlen(str));
	_size = _size + addSize;
	_str[_size] = '\0';
	return *this;
}

My_string::string& My_string::string::operator+= (const char c)
{
	push_back(c);
	return *this;
}


size_t My_string::string::size()const
{
	return _size;
}

size_t My_string::string::capacity()const
{
	return _capacity;
}

bool My_string::string::empty()const
{
	return (_size == 0);
}

My_string::string& My_string::string::erase(size_t pos, size_t n)
{
	//�����Ч����С�ڴ�ɾ���±�,ʲô������
	if (_size - 1 < pos) {}
	else {
		if (pos + n >= _size) {
			_size = pos;
			_str[_size] = '\0';
		}
		else {
			for (size_t i = pos; i < _size - pos - n; ++i) {
				_str[i] = _str[i + pos + n];
			}
			_size = _size - n;
			_str[_size] = '\0';
		}
		return *this;
	}
	return *this;
}

void My_string::string::clear()
{
	_size = 0;
	memset(0, '\0', _size);
}

void My_string::string::resize(size_t n, char c)
{
	//����Ч��������ԭ��Ч����
	if (n > _size) {
		//����Ч������������ʱ������
		if (n > _capacity) {
			reserve(n);
			
		}
		memset(_str + _size, c, n - _size);
		//for (size_t i = _size; i < n; ++i) {
		//	_str[i] = c;
		//}
	}
	_size = n;
	_str[_size] = '\0';
}

void My_string::string::reserve(size_t res_arg)
{
	//�¿ռ���ھɿռ䣬����
	if (res_arg > _capacity) {
		char* temp = new char[res_arg + 1];
		strcpy(temp, _str);
		delete[] _str;
		_str = temp;
		_capacity = res_arg;
	}
}

void My_string::string::push_back(char c)
{
	if (_size == _capacity) {
		reserve(_size * 2);
	}
	_str[_size] = c;
	_size += 1;
	_str[_size] = '\0';
}