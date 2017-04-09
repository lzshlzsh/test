#include <stdio.h>

int f1(int val)
{
	int *ptr;
	if (0 == val){
		int val;
		val = 5;
		ptr = &val;
	}
	return (*ptr + 1);
}

int main()
{
	printf("f1(0) = %d\n", f1(0));
	printf("f1(1) = %d\n", f1(1));
	return 0;
}
