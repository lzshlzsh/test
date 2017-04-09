#include <iostream>

using namespace std;


class Base {
	int x;
public:
	Base(int i){}
};

class Derived : public Base {
public:
	Derived() : Base(0) {}
};


int main()
{

	return 0;
}
