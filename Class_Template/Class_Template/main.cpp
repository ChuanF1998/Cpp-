#include <iostream>
using namespace std;

template<class T>
T add(T x, T y)
{
	return x + y;
}

int add(int x, int y)
{
	return x + y;
}

void Test_01()
{
	int a1 = 2;
	int b1 = 6;
	int c1 = add(a1, b1);
	int d1 = add<int>(a1, b1);
	cout << c1 << endl;
	double a2 = 3.4;
	double b2 = 5.6;
	add(a2, b2);
	double c2 = add<int>(a1, a2);
	
	/*
	add(a1, a2);
	该语句不能通过编译，因为在编译期间，当编译器看到该实例化时，需要推演其实参类型
		通过实参a1将T推演为int，通过实参d1将T推演为double类型，但模板参数列表中只有一个T，
		编译器无法确定此处到底该将T确定为int 或者 double类型而报错
		注意：在模板中，编译器一般不会进行类型转换操作，因为一旦转化出问题，编译器就需要背黑锅
	*/
}

int main()
{
	Test_01();
	return 0;
}