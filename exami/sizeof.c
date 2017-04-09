#include <stdio.h>
#include <stdlib.h>

static void foo(char str[100])
{
	printf("%d\n", sizeof(str));
}
int main()
{
	char str[] = "www.ibegroup.com";
	char *p = str;
	int n = 10;

	printf("%d %d %d\n", sizeof(str), sizeof(p), sizeof(n));

	printf("%d %d %d\n", str[16], '\0', 'm');
	printf("%d %d %d\n", str[15], '\0', 'm');

	void *q = malloc( 100 );
	foo(str);
	printf("%d\n", sizeof ( q ));

	free(q);
	return 0;
}
