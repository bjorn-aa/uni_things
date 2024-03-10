#include<iostream>
#include<string>
#include<vector>

class Date
{
	/*friend class Period;
	friend bool before(Date d1, Date d2);*/
public:
	Date(int d, int m) :day(d), month{ m } {}
	Date(const Date& d) :day(d.day), month(d.month) { }
	void print(void) const { std::cout << "(" << day << ',' << month << ")"; }
	void set_day(int d) { day = d; }
	void set_month(int m) { month = m; }
	int get_day(void) const { return day; }
	int get_month(void)const { return month; }
private:
	int day, month;
};

class Person
{
public:
	Person(std::string n, Date d) : name(n), birth_date(d), mother_ptr(0), father_ptr(0) {}
	void print(void) 
	{
		std::cout << "Name: " << name << std::endl << "Birth date: " << birth_date.get_day() << "-" << birth_date.get_month() << std::endl;
	}
	void add_parents(Person& mother, Person& father)
	{
		mother_ptr = &mother;
		father_ptr = &father;
	}
	void print_parents()
	{
		if (mother_ptr != 0)
			mother_ptr->print();
		if (father_ptr != 0)
			father_ptr->print();
	}
	void add_child(Person& child)
	{
		children.push_back(&child);
	}
	void print_children()
	{
		for (auto& child : children)
		{
			child->print();
		}
	}
	void print_grandparents()
	{
		mother_ptr->print_parents();
		father_ptr->print_parents();
	}
	void print_grandchildren()
	{
		for (auto& child : children)
		{
			child->print_children();
		}
	}
	
private:
	std::string name; 
	Date birth_date;
	Person* mother_ptr;
	Person* father_ptr;
	std::vector<Person*> children;
};

int main(void)
{
	Person bob("Bob", { 1, 6 });
	Person joe("Joe", { 3, 9 });
	Person jill("Jill", { 8, 2 });
	Person jeb("Jeb", { 7, 8 });
	Person jane("Jane", { 1, 3 });
	Person jack("Jack", { 8, 8 });
	Person bell("Bell", { 9, 7 });
	Person john("John", { 1, 7 });
	Person bea("Bea", { 1, 4 });
	Person bubba("Bubba", { 6, 6 });
	Person jean("Jean", { 4, 3 });
	
	bob.print();
	bob.add_parents(joe, jill);
	bob.print_parents();
	bob.add_child(jeb);
	bob.add_child(jane);
	bob.print_children();
	joe.add_parents(jack, bell);
	jill.add_parents(john, bea);
	bob.print_grandparents();
	jeb.add_child(bubba);
	jane.add_child(jean);
	bob.print_grandchildren();


	return(0);
}