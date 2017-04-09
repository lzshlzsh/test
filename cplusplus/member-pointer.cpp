#include <iostream>

using namespace std;

class A {
public:
	static void func(){cout << "func" << endl;} /*not belong to A*/
	void func2(){cout << "func2" << endl;}
};


int main()
{
	A a;
//!	void (A::*f)() = &A::func; //Oops
	void (*f)() = &A::func;
	void (A::*f2)() = &A::func2;
	f();
	(a.*f2)();
	return 0;
}
