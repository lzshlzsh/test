#include <iostream>
#include <cstdio>

using namespace std;

class A{
	int a;
public:
	int get(int)const {return a;}
};


static void foo(A &a)
{
	cout << a.get(1) << endl;
}

int main()
{
	A a;
	char *p1 = NULL;
	char * &p2 = p1;

	int i = 0;
	int &j = i;
	int k = 1;

	foo(a);

	printf("%p\n", p2);

	cout << "&i = " << hex << &i << ", &k = " << &k
		<< ", &j = " << &j << endl; 
}
