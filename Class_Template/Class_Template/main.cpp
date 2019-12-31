#if 0

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
	����䲻��ͨ�����룬��Ϊ�ڱ����ڼ䣬��������������ʵ����ʱ����Ҫ������ʵ������
		ͨ��ʵ��a1��T����Ϊint��ͨ��ʵ��d1��T����Ϊdouble���ͣ���ģ������б���ֻ��һ��T��
		�������޷�ȷ���˴����׸ý�Tȷ��Ϊint ���� double���Ͷ�����
		ע�⣺��ģ���У�������һ�㲻���������ת����������Ϊһ��ת�������⣬����������Ҫ���ڹ�
	*/
}

int main()
{
	Test_01();
	return 0;
}
#endif


#if 0
// ����һ��ģ�����͵ľ�̬����
template<class T, size_t N = 10>
class Array
{
public:
	T& operator[](size_t index)
	{
		return _array[index];
	}
	const T& operator[](size_t index)const
	{
		return _array[index];
	}
	size_t Size()const
	{
		return _size;
	}
	bool Empty()const
	{
		return 0 == _size;
	}
private:
	T _array[N];
	size_t _size;
};


template<class T, int m = 5>
class A
{


private:
	int k ;
	int n = m;
};

int main()
{
	//Array<int> arr;
	A<int> a;

	return 0;
}
#endif

#if 0
#include <iostream>
using namespace std;

template<class T>
bool IsEqual(T& left, T& right)
{
	return left == right;
}

//����ģ���ػ���template<>,�������<>�����ػ�������
template<>
bool IsEqual<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) > 0)
		return true;
	return false;
}

bool IsEqual(char* left, char* right)
{
	if (strcmp(left, right) > 0)
		return true;
	return false;
}

void Test()
{
	char* p1 = "hello";
	char* p2 = "aorld";
	if (IsEqual(p1, p2))
		cout << p1 << endl;
	else
		cout << p2 << endl;
};

int main()
{
	Test();
	return 0;
}
#endif

#if 0

#include <iostream>
using namespace std;


template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

//ȫ�ػ�
template<>
class Data<int, char>
{
public:
	Data() { cout << "Data<int, char>" << endl; }
private:
	int _d1;
	char _d2;
};

// ���ڶ��������ػ�Ϊint
template <class T1>
class Data<T1, int>
{
public:
	Data() { cout << "Data<T1, int>" << endl; }
private:
	T1 _d1;
	int _d2;
};

//��������ƫ�ػ�Ϊָ������
template <typename T1, typename T2>
class Data <T1*, T2*>
{
public:
	Data() { cout << "Data<T1*, T2*>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

//��������ƫ�ػ�Ϊ��������
template <typename T1, typename T2>
class Data <T1&, T2&>
{
public:
	Data(const T1& d1, const T2& d2)
		: _d1(d1)
		, _d2(d2)
	{
		cout << "Data<T1&, T2&>" << endl;
	}
private:
	const T1 & _d1;
	const T2 & _d2;
};

void TestVector()
{
	Data<int, int> d1; //����ģ��
	Data<int, char> d2;//ȫ�ػ�
	Data<char, int> d3; //ƫ�ػ��������ػ���int�Ͱ汾
	Data<int&, int&> d4(1,3); //�����ػ������ð汾
	Data<int*, int*> d5;//�����ػ���ָ��汾

}

int main()
{
	TestVector();
	return 0;
}
#endif

#if 0

#include <string>
#include <iostream>


template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	memcpy(dst, src, sizeof(T)*size);
}

template<class T>
void copy(T* dst, const T* src, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		dst[i] = src[i];
	}
}

class A
{
public:
	A(int k, char* str)
		:_k(k)
		, _str(new char[strlen(str)+1])
	{
		for (int i = 0; i < strlen(str); ++i) {
			_str[i] = str[i];
		}
		_str[strlen(str)] = '\0';
	}

	A(const A& a)
	{
		char* temp = new char[strlen(a._str) + 1];
		for (int i = 0; i < strlen(a._str); ++i) {
			temp[i] = a._str[i];
		}
		delete _str;
		_str = temp;
	}
	const A& operator = (const A& a)
	{
		char* temp = new char[strlen(a._str) + 1];
		for (int i = 0; i < strlen(a._str); ++i) {
			temp[i] = a._str[i];
		}
		temp[strlen(a._str)] = '\0';
		delete _str;
		_str = temp;
		return *this;
	}
private:
	int _k;
	char* _str;
};
int main()
{
	char* s = new char('j');
	std::cout << s << std::endl;
	delete s;
	// ��������Ĵ���
	std::string strarr1[3] = { "11", "22", "33" };
	std::string strarr2[3];
	Copy(strarr2, strarr1, 3);
	A a1(2, "ASD");
	A a2(3,"a");
	copy(&a2, &a1, 1);
	return 0;
}
#endif

