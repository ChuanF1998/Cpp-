

#if 0
#include <iostream>
using namespace std;

class student
{
private:
	int age = 0;
	static int a;
};

//友元函数举例：重写 << 运算符
class Date
{
public:
	Date(int year, int month, int day)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	//ostream& operator<<(ostream& _cout)
	//{
	//	_cout << _year << "-" << _month << "-" << _day;
	//	return _cout;
	//}
	friend ostream& operator<<(ostream& _cout,const Date& d)
	{
		_cout << d._year << "-" <<d. _month << "-" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d(2017, 12, 24);
	cout << d;
	return 0;
}
#endif

#if 0
//友元成员函数举例
#include <iostream>
using namespace std;

class Date; //对Date类的提前引用声明
class Time
{
public:
	Time(int hour, int minute, int second)
		:hour(hour)
		, minute(minute)
		, second(second)
	{}
	void display(Date& d);  //引用Date类的对象
private:
	int hour;
	int minute;
	int second;
};

class Date   //Date类的声明
{
public:
	Date(int year, int month, int day)
		:year(year)
		, month(month)
		, day(day)
	{}
	friend void Time::display(Date& d); //声明Time类中display函数为本类的友元函数
private:
	int year;
	int month;
	int day;
};

void Time::display(Date& d) //定义display函数，只能在Date类后面定义
{
	cout << d.year << "-" << d.month << "-" << d.day << " " << hour << ":" << minute << ":" << second << endl;
}


int main()
{
	Time t(12, 30, 8);
	Date d(2019, 12, 23);
	t.display(d);
	return 0;
}
#endif

#if 0
//友元类
#include <iostream>
using namespace std;

class Date; // 前置声明
class Time
{
	friend class Date; // 声明日期类为时间类的友元类，则在日期类中就直接访问Time类中的私有成员变量
public:
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{}
private:
	int _hour;
	int _minute;
	int _second;
};
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	void SetTimeOfDate(Time& _t)
	{
		// 直接访问时间类私有的成员变量
		cout << _t._hour << " " << _t._minute << " " << _t._second << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d;
	Time t(12, 34, 23);
	d.SetTimeOfDate(t);
	return 0;
}
#endif

class B;
class A
{
	friend void fun(const A& a, const B& b);
private:
	int a;
};

class B
{
	friend void fun(const A& a, const B& b);
private:
	int b;
};

void fun(const A& a, const B& b)
{
	int x = a.a;
	int y = b.b;
}

int main()
{
	return  0;
}

