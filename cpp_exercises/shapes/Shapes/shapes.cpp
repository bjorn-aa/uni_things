#include <iostream>
using namespace std;

const double PI = 22 / 7;

class Shape
{
public:
	Shape(double ax, double ay) : anchor_x(ax), anchor_y(ay) {}
	void move(double dx, double dy) { anchor_x += dx; anchor_y += dy; }
	virtual void print(void) { cout << "Anchor point: (" << this->anchor_x << "," << this->anchor_y << ") - "; }
	virtual double get_area(void) = 0; // pure virtual function
private:
	double anchor_x, anchor_y;

};


class Rectangle : public Shape
{
public:
	Rectangle(double ax, double ay, double l, double w) :Shape(ax, ay), length(l), width(w) {}
	virtual void print(void) { Shape::print(); cout << " Length: " << length << " Width: " << width << endl;  }
	virtual double get_area(void) { return length * width; }

private:
	double length, width;

};

class Circle : public Shape
{
public:
	Circle(double ax, double ay, double r) :Shape(ax, ay), radius(r) {}
	virtual void print(void) { Shape::print(); cout << "Radius: " << radius << endl; }
	virtual double get_area(void) { return PI*radius*radius; }

private:
	double radius;

};

class Square : public Shape
{
public:
	Square(double ax, double ay, double s) :Shape(ax, ay), side(s) {}
	virtual void print(void) { Shape::print(); cout << "Side: " << side << endl; }
	virtual double get_area(void) { return side*side; }

private:
	double side;

};

int main(void)
{
	int k;

	Rectangle r(1, 2, 3, 4);
	Circle c(5, 6, 4);
	Square s(7, 8, 3);

	c.print();
	s.print();
	r.print();

	r.move(3, 2);
	cout << "Moved by a bit." << endl;
	r.print();
	cout << endl << "Area: " << r.get_area() << endl << endl;

	//Shape shapes[] = { c, s, r }; //BAD IDEA

	Shape* shapes[] = { &c, &s, &r }; //GOOD IDEA

	for (unsigned int i = 0; i < 3; i++)
	{
		shapes[i]->print();
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		cout << "Area: " << shapes[i]->get_area() << endl;
	}

	system("pause");

	/*cin >> k;*/

	return 0;

}
