#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void foo(int a, int b);
extern int xxx;

#ifdef __cplusplus
}
#endif


static void foo1()
{
	foo(1, 2);
}

int main()
{
	foo(1, 2);
	foo1();

	printf("xxx = %d\n", xxx);

#ifdef __cplusplus
	printf("__cplusplus defined\n");
#endif
	return 0;
}
