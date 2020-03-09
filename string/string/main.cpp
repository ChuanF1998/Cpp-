#include "string.h"
//#include <string>



int main()
{
	//test();
	My_string::string str1("qwer");
	My_string::string str2;
	std::cin >> str2;
	My_string::string str3 = "32434";
	My_string::string str4 = str1 + str3;
	str1.push_back('v');
	str1 += "qwew";
	str1 += str2;
	std::cout << str1 << std::endl;
	str1.pop_back();
	std::cout << str1 << std::endl;
	std::cout << str1[8] << std::endl;
	std::cout << str1.size() << std::endl;
	std::cout << str1.capacity() << std::endl;
	std::cout << str1.erase(2, 4) << std::endl;
	str1.clear();
	str1.resize(10, 'r');
	str1.reserve(30);
	return 0;
}