#include <iostream>

using namespace std;

class A
{
	int a;
public:
	virtual int f() 
	{ 
		a = 1;
		cout << "a = " << a << endl;
		return a;
	}
};

class B : public A
{
	int b;
public:
	int f() 
	{ 
		b = 2;
		cout << "b = " << b << endl;
		return b;
	}
};

static void f(A a)
{
	a.f();
}

int main()
{
	B b;

	f(b);

	return 0;
}
