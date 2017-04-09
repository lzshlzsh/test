#include <iostream>

using namespace std;

class Base 
{
public:
	int a;
	Base(): a(0){}
	virtual int foo(){return a--;}
};

class Derived: public Base
{
public:
	virtual int foo(){return ++a;}
};

int main()
{
	Derived *pd = new Derived();
	Base *pb = pd;
	Base &b = *pb;

	pd->foo();
	pb->foo();
	b.foo();
	cout << pd->foo() << endl;
	cout << pb->foo() << endl;
	cout << b.foo() << endl;


	delete pd;

	return 0;
}
