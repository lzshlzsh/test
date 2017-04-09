#include <stdio.h>

int main()
{
	int i;
	int A[100];

	for (i = 0; i < 100; i++){
		A[i] = i;
	}

	printf("A[0] = %d\n", A[0]);

	return 0;
}
