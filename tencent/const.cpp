#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	const int i = 1;
	int *pi;
	cout << i << endl;
//	*const_cast<int *>(&i) = 3;
//	pi = (int *)&i;
//	*pi = 3;
	*(int *)&i = 3;
	printf("%d\n", i);
	cout << i << endl;
	return 0;
}
