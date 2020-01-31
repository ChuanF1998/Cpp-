#if 0

#include <malloc.h>
#include <stdio.h>

int main()
{
	int *ptr = NULL;
	ptr = (int*)realloc(ptr, sizeof(int)*4);
	ptr[0] = 0;
	ptr[1] = 1;
	ptr[2] = 2;
	ptr[3] = 3;;
	int k = sizeof(ptr);
	return 0;
}

#endif

#if 0

#include <iostream>
using namespace std;

int main()
{
	int* k = new int(8);
	cout << *k << endl;
	delete k;
	return 0;
}
#endif


#if 0

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//定位new表达式

class student
{
public:
	student(){}
	student(int num, string name)
		: _num(num)
		, _name(name)
	{}
	friend ostream& operator<<(ostream& out, const student& s)
	{
		out << s._num << "  " << s._name;
		return out;
	}
	void printf()
	{
		cout << _num << endl;
		cout << _name << endl;
	}
private:
	int _num;
	string _name;
};

int main()
{
	student* s1 = new student();
	student* s2 = new student(121, "dis");
	student* s3 = (student*)malloc(sizeof(student));
	new(s3)student(232, "sadja");
	return 0;
}
#endif

#if 1
//设计一个类，该类只能在堆上创建对象
//方法一：将构造函数私有化
class only_heap1
{
public:
	static only_heap1* create(int k)
	{
		return new only_heap1(k);
	}
	static only_heap1* create()
	{
		return new only_heap1;
	}
	~only_heap1(){}
private:
	only_heap1(){}
	only_heap1(int k)
		: _k(k)
	{}
	only_heap1(const only_heap1& a) = delete;
private:
	int _k;
};

//方法二：析构函数私有化
class only_heap2
{
public:
	only_heap2(int n)
		: _n(n)
	{}

	void destroy(only_heap2* p)
	{
		delete p;
	}
private:
	~only_heap2(){}
private:
	int _n;
};

int main()
{
	only_heap1* q = only_heap1::create(3);
	
	only_heap2* o = new only_heap2(7);
	o->destroy(o);
	delete q;
	return 0;
}
#endif


#if 0
//只能在栈上创建对象
//方法一：屏蔽operator new 和 operator delete 
class only_stack
{
public:
	only_stack(){}
	only_stack(int n)
		: _n(n)
	{}
	void* operator new(size_t size) = delete;
	void operator delete(void* v) = delete;
private:
	int _n;
};

//方法二：构造函数私有化
class only_stack1
{
public:
	static only_stack1 create(int n)
	{
		return only_stack1(n);
	}
private:
	only_stack1(){}
	only_stack1(int n)
		: _n(n)
	{}
private:
	int _n;
};

int main()
{
	only_stack o1(2);
	only_stack1 o4 = only_stack1::create(5);
	return 0;
}
#endif