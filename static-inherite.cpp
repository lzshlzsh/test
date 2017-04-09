#include <iostream>

using namespace std;

class A {
public:
	static void func(){cout << "A::func" << endl;}
};

class B : public A {
public:
	static void func(){cout << "B::func" << endl;}
};

int main()
{
	A a;
	B b;

	a.func();
	b.func();
	return 0;
}
