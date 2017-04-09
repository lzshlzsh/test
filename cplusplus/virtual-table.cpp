#include <iostream>

using namespace std;


class Base
{
private:
	int i;
public:
	virtual void foo(){cout << "Base::foo" << endl;}
	virtual void goo(){cout << "Base::goo" << endl;}
};

class Class1 : public Base 
{
public:
	virtual void foo(){cout << "Class1::foo" << endl;}
//	virtual void goo(){cout << "Base::goo" << endl;}
};


int main()
{
	Base *A[] = {new Base(), new Class1()};

	cout << "sizeof(Base) = " << sizeof(Base) << endl;
	cout << "sizeof(Class1) = " << sizeof(Class1) << endl;
	
	A[0]->foo();
	A[0]->goo();
	A[1]->foo();
	A[1]->goo();


	delete A[0];
	delete A[1];
	return 0;
}
