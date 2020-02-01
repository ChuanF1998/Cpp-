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

//��λnew���ʽ

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

#if 0
//���һ���࣬����ֻ���ڶ��ϴ�������
//����һ�������캯��˽�л�
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

//����������������˽�л�
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
//ֻ����ջ�ϴ�������
//����һ������operator new �� operator delete 
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

//�����������캯��˽�л�
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

#if 0
#include <iostream>
//����ģʽ
class singleton
{
public:
	static singleton* get()
	{
		return &m_instance;
	}
	void print()
	{
		std::cout << _n << std::endl;
	}
private:
	singleton(){}
	singleton(int n)
		: _n(n)
	{}

	singleton(const singleton& s) = delete;
	singleton& operator = (const singleton& s) = delete;
private:
	int _n;
	static singleton m_instance;
	static int k;
};

singleton singleton::m_instance(9);

int main()
{
	singleton::get()->print();
	return 0;
}
#endif


#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
class Singleton
{
public:
	static Singleton* GetInstance() {
		// ע������һ��Ҫʹ��Double-Check�ķ�ʽ���������ܱ�֤Ч�ʺ��̰߳�ȫ
		if (nullptr == m_pInstance) {
			m_mtx.lock();
			if (nullptr == m_pInstance) {
					m_pInstance = new Singleton();
			}
			m_mtx.unlock();
		}
		return m_pInstance;
	}
	// ʵ��һ����Ƕ����������
	class CGarbo {
	public:
		~CGarbo(){
			if (Singleton::m_pInstance)
				delete Singleton::m_pInstance;
		}
	};
	// ����һ����̬��Ա�������������ʱ��ϵͳ���Զ������������������Ӷ��ͷŵ�������
	static CGarbo Garbo;
private:
	// ���캯��˽��
	Singleton(){};
	// ������
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
	static Singleton* m_pInstance; // ��������ָ��
	static mutex m_mtx; //������
};
Singleton* Singleton::m_pInstance = nullptr;
Singleton::CGarbo Garbo;
mutex Singleton::m_mtx;
void func(int n)
{
	cout << Singleton::GetInstance() << endl;
}
// ���̻߳�������ʾ����GetInstance()�����Ͳ�����������
int main()
{
	thread t1(func, 10);
	thread t2(func, 10);
	t1.join();
	t2.join();
	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;
	return 0;
}