#include <iostream>

using namespace std;

class Base {
public:	
	Base() {cout << "Base()" << endl;}
	virtual ~Base() {cout << "~Base()" << endl;}
};

class Derived : public Base {
public:	
	Derived() {cout << "Derived()" << endl;}
	~Derived() {cout << "~Derived()" << endl;}
};

class Derived2 : public Derived {
public:
	Derived2() {cout << "Derived2()" << endl;}
	~Derived2() {cout << "~Derived2()" << endl;}
};

int main()
{
	Derived *p_base = new Derived2();
	delete p_base;

	return 0;
}
