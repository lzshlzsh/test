#include <stdio.h>

struct A{
	int a, b;
};

int main()
{
	struct A a, *pa = &a;
	struct A b, *pb = &b;

	
	printf("%d\n", pa - pb);

	return 0;
}


