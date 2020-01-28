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