#include<iostream>
#include<iomanip>
using namespace std;

class Date
{
public:
	Date(int year = 1901, int month = 1, int day = 1,int week=2)
		:_year(year)                            //��ʼ���б�Ч�ʸ�
		, _month(month)
		, _day(day)
		, _week(week)

	{
		if (NotLegal())               //������Ϸ��������ó�Ĭ��ֵ
		{
			_year = 1901;
			_month = 1;
			_day = 1;
		}
	}

	bool NotLegal()
	{
		if ((_year < 1)||(_month <1 || _month>12) || (_day<1|| _day> BigMonthDay()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int BigMonthDay()                           //����һ���µ�����
	{
		static int Month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
		if (LeapYear() && (_month == 2))
		{
			return Month[_month] + 1;
		}
		else
		{
			return Month[_month];
		}
	}

	int LeapYear()                            //�ж��ǲ�������
	{
		if ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0))
			return 1;
		else
			return 0;
	}

	void DateOperator()
	{
		if (_day<=0)
		{
			while (_day<=0)
			{
				_month--;
				if (_month<1)
				{
					_year--;
					_month = 12;
				}
				_day += BigMonthDay();
			}
		}
		else
		{
			while (_day>BigMonthDay())
			{
				_day -= BigMonthDay();
				_month++;
				if (_month > 12)
				{
					_year++;
					_month = 1;
				}
			}
		}
	}
public:
	Date operator+(int day)
	{
		Date tmp(*this);
		tmp._day += day;
		tmp.DateOperator();
		return tmp;
	}

	Date operator-(int day)
	{
		Date tmp(*this);
		tmp._day -= day;
		tmp.DateOperator();
		return tmp;
	}

	int operator-(Date& d)
	{
		int count = 0;
		Date Max;
		Date Min;
		if (*this > d)
		{
			Max = *this;
			Min = d;
		}
		else
		{
			Max = d;
			Min = *this;
		}
		while (Max>Min)
		{
			Min=Min+1;
			count++;
		}
		return count;
	}

	bool operator>(Date& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year==d._year)
		{
			if (_month > d._month)
			{
				return true;
			}
			else if (_month == d._month)
			{
				if (_day > d._day)
					return true;
			}
		}
		return false;
	}

	void display()
	{
		Date d;
		int day = *this - d;                  //��ǰ������Ĭ������֮�������
		_week =(day%7+1)%7+1;                 //������һ������Ӧ������
		cout << _year << "��" << _month << "��" << _day << "��" << "  ����" << _week << endl << endl;
		cout << "  �� " << " һ " << " �� " << " �� " << " �� " << " �� " << " �� " << endl;
		//������һ���µ�һ������Ӧ������
		int week = _week;
		Date d1(*this);
		d1._day = 1;
		day = d1 - d;                  //��ǰ������Ĭ������֮�������
		week = (day % 7 + 1) % 7 + 1;

		for (int i = 0; i < (week % 7); i++)
		{
			cout << setw(4) << " ";
		}
		for (int i = 1; i <=BigMonthDay(); i++)
		{
			week++;
			cout << setw(4) << setiosflags(ios::right) <<i;
			if (week % 7 == 0)
			{
				cout << endl;
			}
		}
		cout << endl;
	}

	friend istream& operator>>(istream& is, Date& d);
private:
	int _year;
	int _month;
	int _day;
	int _week;
};



istream& operator>>(istream& is, Date& d)
{
	is >> d._year >> d._month >> d._day;
	return is;
}

void test1()
{
	Date d1;
	Date d2;
	int day = 0;
	cout << "����������:  " ;
	cin >> d1;
	cout << "������������ ";
	cin >> day;
	d2 = d1 + day;
	d2.display();
}


void test2()
{
	Date d1;
	Date d2;
	int day = 0;
	cout << "����������:  ";
	cin >> d1;
	cout << "������������ ";
	cin >> day;
	d2 = d1 -day;
	d2.display();
}

void test3()
{
	Date d1;
	Date d2;
	cout << "����������:  ";
	cin >> d1;
	cout << "����������:  ";
	cin >> d2;
	int day = d1 - d2;
	cout << "���" << day << "��" << endl;
}

void menu()
{
	int n;
	while (1)
	{
		cout << endl<< " 0.exit" << " 1.���ڼ�����" << " 2.���ڼ�����" << " 3.���ڼ�����" << endl << endl;;
		cout << "��ѡ��";
		cin >> n;
		switch (n)
		{
		case 0:
			exit(1);
			break;
		case 1:
			test1();
			break;
		case 2:
			test2();
			break;
		case 3:
			test3();
			break;
		default:
			cout << "���벻�Ϸ�" << endl;
		}
	}
}


int main()
{
	menu();
	system("pause");
	return 0;
}