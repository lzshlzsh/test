#include <math.h>
#include <stdio.h>

int main()
{
	int i = 0;
	long long j = 0;
	double x = M_PI / 4;
	double rst;

#if 1
	while (i++ < (1 << 26)){
		x = (j * M_PI / 180);
//		rst = sin(x);
		rst = cos(x);
		j += 4;
	}
#else
	while (i++ < (1 << 26)){
//		rst = sin(x);
		rst = cos(x);
	}
#endif
	printf("%f\n", rst);
	return 0;
}
