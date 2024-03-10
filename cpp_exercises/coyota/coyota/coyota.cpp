#include<iostream>
#include<string>
#include<vector>
using namespace std;




class Person
{
public:
	Person(string n, string adr, int a) : name(n), address(adr), age(a) {};
	void print() const { cout << endl << "Name: " << name << endl << "Address: " << address << endl << "Age: " << age << endl; }
	string get_name(void) const { return name; }
private:
	string name, address;
	int age;
};


class Coyota_dealer_affiliated
{
public:
	virtual string write_letter_to(string) = 0;
private:
};


class Customer
{
public:
	Customer(const Person &p, int n, double ac) : person_ptr(&p), c_num(n), account(ac) {};

	void print() const
	{ 
		person_ptr->print();
		cout << "Customer Number: " << c_num << endl << endl;
	}
	virtual string write_letter_to(string n)
	{
		return "Dear " + person_ptr->get_name() + ",\n" + n + "\n\n";
	}

private:
	const Person *person_ptr;
	int c_num;
	double account;
};

class Employee
{
public:
	Employee(Person *p_ptr, int n) : person_ptr(p_ptr), e_num(n) {};
	void  print()
	{
		person_ptr->print();
		cout << "Employee Number: " << e_num << endl;

	}
	string get_name(void) { return person_ptr->get_name(); }
	virtual double calculate_salary(void) = 0;
	virtual string write_letter_to(string) = 0;
private:
	Person *person_ptr;
	int e_num;
};
class Mechanic : public Employee
{
public:
	Mechanic(Person *p_ptr, int n) : Employee(p_ptr, n) {};
	void set_hourly_salary(double s) { hourly_salary = s; }
	void set_hours(int h) { hours = h; }

	void print()
	{
		cout << endl << "Hours: " << hours << endl << "Hourly Salary: " << hourly_salary << endl << endl;
	}
	virtual double calculate_salary(void) { return hours * hourly_salary; }
	virtual string write_letter_to(string n) 
	{
		return "Dear mechanic " + get_name() + ",\n" + n + "\n\n";
	}

private:
	int hours;
	double hourly_salary;
};

class Secretary : public Employee
{
public:
	Secretary(Person *p_ptr, int n) : Employee(p_ptr, n) {};
	void set_monthly_salary(double s) { monthly_salary = s; }

	void print()
	{
		cout << endl << "Monthly Salary: " << monthly_salary << endl << endl;
	}
	virtual double calculate_salary(void) { return monthly_salary; }
	virtual string write_letter_to(string n)
	{
		return "Dear secretary " + get_name() + ",\n" + n + "\n\n";
	}
private:
	double monthly_salary;
};

class Salesman : public Employee
{
public:
	Salesman(Person *p_ptr, int n) : Employee(p_ptr, n) {};
	void set_provision(double p) { provision = p; }
	void set_sale(double s) { sale = s; }

	void  print()
	{
		cout << "Provision: " << provision << endl << "Sale: " << sale << endl << endl;
	}
	virtual double calculate_salary(void) { return sale*provision; }
	virtual string write_letter_to(string n)
	{
		return "Dear salesman " + get_name() + ",\n" + n + "\n\n";
	}
private:
	double sale, provision;
};

class Director : public Employee
{
public:
	Director(Person *p_ptr, int n) : Employee(p_ptr, n) {};
	void set_monthly_salary(double s) { monthly_salary = s; }
	void assign_free_car(string m) { free_car = m; }
	void  print()
	{
		cout << "Monthly Salary: " << monthly_salary << endl << "Free Car: " << free_car << endl << endl;
	}
	virtual double calculate_salary(void) { return monthly_salary; }
	virtual string write_letter_to(string n)
	{
		return "Dear director " + get_name() + ",\n" + n + "\n\n";
	}
private:
	double monthly_salary;
	string free_car;
};




class Coyota_dealer
{
public:
	Coyota_dealer(Person *o_ptr, string adr) : owner_ptr(o_ptr), address(adr) {};
	void hire(Employee &e) { employees.push_back(&e); }
	void fire(Employee &e) 
	{ 
		
		for (auto it = employees.begin(); it < employees.end(); it++)
		{
			if (*it == &e)
			{
				employees.erase(it);
				break;
			}
		}
		//employees.erase(&e); 
	}
	void register_customer(Customer *c_ptr) { customers.push_back(c_ptr); }
	void print()
	{
		cout << "Owner: " << endl;
		owner_ptr->print();
		cout << "Address: " << address << endl;
		for (auto e_ptr : employees)
		{
			e_ptr->print();
		}
		cout << endl;
		for (auto c_ptr : customers)
		{
			c_ptr->print();
		}
		cout << endl;
	}
	void calculate_total_salary(void) 
	{ 
		double total = 0;
		for (auto e_ptr : employees)
		{
			double salary = 0;
			salary = e_ptr->calculate_salary();
			cout << "Salaries: " << salary << endl;

			total += salary;
			
		}
		cout << "Total: " << total << endl;
	}
	void write_letter_to_employees(void)
	{
		for (auto e_ptr : employees) { cout << e_ptr->write_letter_to("Lorem ipsum dolor sit amet."); }
	}
	void write_letter_to_customers(void)
	{
		for (auto c_ptr : customers) { cout << c_ptr->write_letter_to("Check out the new Lorem Ipsum!"); }
	}
	void write_letter_to_affiliates(void)
	{
		for (auto e_ptr : employees) { cout << e_ptr->write_letter_to("Check out our amazing prizes this Easter!"); }
		for (auto c_ptr : customers) { cout << c_ptr->write_letter_to("Check out our amazing prizes this Easter!"); }
	}

private:
	Person *owner_ptr;
	string address;
	vector<Employee*> employees;
	vector<Customer*> customers;
};


int main(void)
{
	
	Person p1("Jens","Odense",20);
	Mechanic m1(&p1,1);
	m1.set_hourly_salary(100.5);
	m1.set_hours(10);
	m1.print();

	cout << endl;

	Person p2("Ole","Fynshav",22);
	Secretary s1(&p2,2);
	s1.set_monthly_salary(20000.7);
	s1.print();

	cout << endl;

	Person p3("Ib","Skovby",42);
	Salesman sm1(&p3,3);
	sm1.set_provision(0.1);
	sm1.set_sale(1000);
	sm1.print();

	cout << endl;

	Person p4("Ole","Fynshav",22);
	Director d1(&p4,4);
	d1.set_monthly_salary(200000.8);
	d1.assign_free_car("Tesla-X");
	d1.print();

	cout << endl;

	Person p5("Rudolf","Augustenborg",25);
	Customer c1(p5,1,0);
	c1.print();

	cout << endl;


	Customer c2(p5,2,0);
	c2.print();

	cout << endl;

	Person p6("Wolf","Broager",35);
	Coyota_dealer Broager_coyota(&p6," Broager");

	Broager_coyota.hire(d1);
	Broager_coyota.hire(sm1);
	Broager_coyota.hire(s1);
	Broager_coyota.hire(m1);


	Broager_coyota.register_customer(&c1);
	Broager_coyota.register_customer(&c1);

	cout << endl;
	Broager_coyota.print();

	Broager_coyota.fire(s1);
	cout << endl;
	Broager_coyota.print();

	Broager_coyota.calculate_total_salary();

	Broager_coyota.write_letter_to_employees();
	Broager_coyota.write_letter_to_customers();
	Broager_coyota.write_letter_to_affiliates();


	
	system("pause");

	/*int kk; cin >> kk;*/
	return 0;
}

