
#include <alloca.h>
#include <stdio.h>


void foo(int i, void *p, int j)
{
	printf("%p\n", p);
}
int main()
{
	int i = 0;
	char *addr = (char *)alloca(18);

	printf("%p, %p\n", &i, addr);
	foo (1, alloca(13), 3);
	return 0;
}
