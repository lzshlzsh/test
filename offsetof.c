#include <stdio.h>
#include <stdlib.h>


#define offsetof(type, member) ((size_t)&((type *)0)->member)

int main()
{
	struct A{
		long long ll;
		int a[2];
	};

	printf("%d %d\n", offsetof(struct A, a[0]), offsetof(struct A, a[1]));
	return 0;
}
