// daymonth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

#define C_PI 22/7

const double PI = 22 / 7;

class Date
{
	public:
		Date(int d, int m) : day(d), month(m)
		{}
		Date(void) :day(1), month(1) {}

		void print(void) const //the function cannot change any member variable
		{ cout << day << "/" << month; }
		void set_date(int d, int m) { day = d; month = m; };
		int get_day(void) const { return day; }
		int get_month(void) const { return month; }

	private:
		int day, month;
};

class Period
{
	public:
		Period(Date s, Date e) : start(s), end(e) {}
		void print(void) { start.print(); cout << " - "; end.print(); }
		int length(void)
		{
			if (start.get_month() == end.get_month())
			{
				return end.get_day() - start.get_day();
			}
			else
			{
				//homework
				return 0;
			}
		}
	private:
		Date start, end;



};

Date minimum(Date a, Date b)
{

}

template<class T>
T minimum(T a, T b)
{
	return a < b ? a : b; // question operator ? if true_value
}



int main()
{
	Date christmas(24, 12), new_year(1, 1), d;
	cout << " Christmas "; christmas.print();
	cout << endl;
	cout << " New year "; new_year.print();
	cout << endl;
	d.set_date(14, 2);
	d.print();
	cout << " day: " << d.get_day();

	Period easter_holiday(Date(15, 4), Date(22, 4));
	cout << endl;
	easter_holiday.print();
	cout << endl << " length: " << easter_holiday.length() << endl;

	//cout << myCPI;

	cout << minimum(2, 3) << endl;
	cout << minimum(2.3, 3.4) << endl;
	//cout << minimum(2, 3.4) << endl; //doesn't work because int and float are different types.
	cout << minimum('f', 'g') << endl;
	cout << minimum("f", "g") << endl; //does not work because addresses are compared
	cout << minimum(string("f"), string("g")) << endl;
	minimum(christmas, new_year).print();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
