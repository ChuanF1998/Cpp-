#define _CRT_SECURE_NO_WARNINGS
#include "string.h"

My_string::string::string()
: _str(new char[1])
, _size(0)
, _capacity(0)
{
	_str[_size] = '\0';
}
My_string::string::string(const char* str)
    : _str(new char[strlen(str) + 1])
    , _size(strlen(str))
    , _capacity(_size)
{
	strcpy(_str, str);
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

//拷贝构造函数
My_string::string::string(const string& str)
: _str(new char[str._size + 1])
, _size(str._size)
, _capacity(_size)
{
	strcpy(_str, str._str);
}

My_string::string::string(const string& str, size_t n)
{	
	//n小于等于源字符串长度
	if (n <= str._size) {
		_str = new char[n + 1];
		_size = n + 1;
		_capacity = _size;
		for (size_t i = 0; i < n; ++i) {
			_str[i] = str._str[i];
		}	
	}
	//n大于源字符串长度时就只复制str的size大小即可
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

My_string::string& My_string::string::operator+= (const string& str)
{
	*this += str._str;
	return *this;
}

My_string::string& My_string::string::operator+= (const char* str)
{
	size_t addSize = strlen(str);
	if (_capacity < _size + addSize) {
		size_t newCapacity = _capacity;
		while (newCapacity < _capacity + addSize) {
			newCapacity = 2 * newCapacity + 1; //为什么要加一，可能存在起始空间为0的情况
		}
		reserve(newCapacity);
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

My_string::string& My_string::string::operator= (const char* str)
{
	char* temp = new char[strlen(str) + 1];
	strcpy(temp, _str);
	delete[] _str;
	_str = temp;
	_size = strlen(str);
	_capacity = _size;
	return *this;
}

bool My_string::string::operator== (const string& str)
{
	return (strcmp(_str, str._str) == 0);
}

bool My_string::string::operator!= (const string& str)
{
	return !(*this == str);
}

My_string::string& My_string::string::operator= (const My_string::string& str)
{
	if (this != &str) {
		char* temp = new char[strlen(str._str) + 1];
		strcpy(_str, temp);
		delete[] _str;
		_str = temp;
		_size = str._size;
		_capacity = str._capacity;
	}
	return *this;
}

My_string::string My_string::string::operator+ (const string& str)
{
	My_string::string temp;
	temp += *this;
	temp += str;
	return temp;
}

My_string::string My_string::string::operator+ (const char* str)
{
	My_string::string temp(str);
	temp += *this;
	return temp;
}

My_string::string My_string::string::operator+ (const char c)
{
	string temp;
	temp += *this;
	temp += c;
	return temp;
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
	//如果有效个数小于待删除下标,什么都不做
	if (_size - 1 < pos) {}
	else {
		if (pos + n >= _size) {
			_size = pos;
			_str[_size] = '\0';
		}
		else {
			for (size_t i = pos; i < _size - n; ++i) {
				_str[i] = _str[i + n];
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
	//新有效个数大于原有效个数
	if (n > _size) {
		//新有效个数大于容量时，扩容
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
	//新空间大于旧空间，扩容
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

void My_string::string::pop_back()
{
	_size -= 1;
	_str[_size] = '\0';
}

const char* My_string::string::c_str()const
{
	return _str;
}

std::ostream& My_string::operator<< (std::ostream& out, const string& str)
{
	out << str._str;
	return out;
}

std::istream& My_string::operator>> (std::istream& in, string& str)
{
	in >> str._str;
	str._size = strlen(str._str);
	str._capacity = str._size;
	return in;
}

My_string::iterator My_string::string::begin()
{
	return _str;
}
My_string::iterator My_string::string::end()
{
	return _str + _size;
}