//============================================================================
// Name        : virtual_cout_function.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Base
{
public:
	Base()
	{
	}
	virtual ~Base()
	{
	}

	friend ostream& operator << (ostream& o, const Base& b);

	virtual void test()
	{
		cout << "test Base" << endl;;
	}

protected:
	virtual void print(ostream& o) const
	{
		cout << "Base";
	}
};

inline std::ostream& operator<< (std::ostream& o, const Base& b)
{
	b.print(o); // delegate the work to a polymorphic member function.
	return o;
}

class Derived : public Base
{
public:
	Derived()
	{
	}

	virtual ~Derived()
	{
	}

	virtual void test()
	{
		cout << "test Derived" << endl;
	}

protected:
	virtual void print(ostream& o) const
	{
		cout << "derived";
	}
};

int main()
{
	Base b;
	Derived d;
	Base bd = d;
	Base *p = &d;
	Base & br = d;

	cout << b << endl;
	cout << d << endl;
	cout << bd << endl;
	cout << *p << endl;
	cout << br << endl;

	cout << "!!!Hello World!!!" << endl;

	b.test();
	d.test();
	bd.test();
	p->test();


	return 0;
}
