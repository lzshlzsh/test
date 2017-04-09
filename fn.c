#include <stdio.h>

static inline int sign(int n)
{
	return ((n > 0) ? 1 : ((0 == n) ? 0 : -1));
}

static inline int f(int n)
{
	return  ( 2 + 1 + sign(n-2) + sign(n - 2) * sign(2 - n) + 1 
			- (1 + sign(n - 6) * sign(6 - n))
			- 3 * (3 + sign(n - 9) * sign(9 - n) + sign(n - 10) * sign(10 - n) 
				+ sign(n - 11) * sign(11 - n)));
}
int main()
{
	
	int i;
	for (i = -20; i < 20; i++)
		printf("f(%d) = %d\n", i, f(i));
	
	return 0;
}
