#include <iostream>

using namespace std;

class A
{
public:
	virtual ~A() = 0;
};

A::~A()
{
	cout << "A::~A()" << endl;
}

class B : public A
{
public:
	~B() 
	{
		cout << "B::~B()" << endl;
	}
};

int main()
{
	B b;
	return 0;
}
