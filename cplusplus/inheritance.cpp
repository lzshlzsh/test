#include <iostream>

using namespace std;


class Base 
{
private:
	int i;
	void foo(){};
protected:
	int j;
	void goo(){};
public:
};

class Inheritance : public Base
{
private:
	int i, j;
public:
	void foo(){}
	void goo()
	{
		//Base::i = 0;  //Oops 
		Base::j = 0;
		//Base::foo(); //Oops
		Base::goo();
	}
};

int main()
{
	cout << "sizeof(Base): " << sizeof(Base) << endl;
	cout << "sizeof(Inheritance): " << sizeof(Inheritance) << endl;
	return 0;
}
