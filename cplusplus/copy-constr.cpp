#include <iostream>

using namespace std;

class Base {
public:
	Base(){cout << "Base constructor" << endl;}
	Base(const Base &){cout << "Base copy constructor" << endl;}
};

class Base2 {
public:
	Base2(){cout << "Base2 constructor" << endl;}
	Base2(const Base2 &){cout << "Base2 copy constructor" << endl;}
};


class Derived : public Base{
	Base2 b2;
public:
	Derived(){cout << "Derived constructor" << endl;}
	Derived(const Derived &){cout << "Derived copy constructor" << endl; }
};


int main()
{
	Derived d1;
	Derived d2 = d1;
	return 0;
}
