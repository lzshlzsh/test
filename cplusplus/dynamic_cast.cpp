#include <iostream>
#include <typeinfo>

using namespace std;

class Base
{
	static int a;
public:
	virtual void f(){}
};

int Base::a = 0;

class Derived : public Base
{
public:
	void f() {}
};

int main()
{
//	Base b;
	Base *pb;
	Derived d, *pd;
	const char *name;

//	pd = dynamic_cast<Derived *>(&b);
//	cout << "pd = " << pd << endl;

	name = typeid(d).name();
	cout << name << endl;

	pb = &d;
	pd = dynamic_cast<Derived *>(pb);
	cout << "pd = " << pd << endl;

	cout << "sizeof(Base) = " << sizeof(Base) << endl;

	return 0;
}
