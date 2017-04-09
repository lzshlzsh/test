#include <stdio.h>
#include <stdlib.h>


int main()
{
	char *p1, *p2;

	p1 = (char *)malloc(100);
	p2 = (char *)malloc(100);

	printf("%p %p\n", p1, p2);

	free(p1);
	free(p2);

	return 0;
}
