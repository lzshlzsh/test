#include <iostream>

using namespace std;


static int foo(const void *)
{
	cout << "const void" << endl;
	return 0;
}
static int foo(void *)
{
	cout << "void" << endl;
	return 0;
}
static int foo(const char *)
{
	cout << "const char" << endl;
	return 0;
}
static int foo(char *)
{
	cout << "char" << endl;
	return 0;
}


int main()
{
	const void *pcvoid = NULL;
	void *pvoid = NULL;
	char *pstr = NULL;
	const char *str = "fffffff";
	char A[] = "ffffff";

	foo(pcvoid);
	foo(pvoid);

	foo(pstr);
	foo(str);


//	pstr = pvoid;

	cout << sizeof(str) << endl;;
	cout << sizeof(A) << endl;
	return 0;
}
