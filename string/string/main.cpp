#include "string.h"
#include <string>

void test()
{
	std::string str = "qwertyuiop";
	str += "assdfdfggh";
	str += 'e';
}

int main()
{
	//test();
	My_string::string str("qwer");
	str += 'c';
	str += 'b';
	str += 'n';
	str += 'm';
	str += "poiqreesdfsfd";
	const My_string::string str1("wewwe");
	char j = str1[3];
	char k = str[2];
	str.reserve(10);
	str.resize(10, '8');
	str.resize(5, '7');
	str.resize(20, '9');
	return 0;
}