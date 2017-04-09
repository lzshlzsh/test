#include <stdio.h>
#include <math.h>

extern double native_sin(double x);
extern double native_cos(double x);

int main()
{
	double rst = M_1_PI;
	double f180 = 180;
	double x;
	int i;

//	printf(".dword 0x%llx\n", *(long long *)&rst);
//	printf(".dword 0x%llx\n", *(long long *)&f180);

#if 0
	for (i = 0; i < 360; i++){
		x = -i * M_PI / 180.0;
		printf("%1.20f : %1.20f\n", sin(x), native_sin(x));
//		printf(".dword 0x%llx\n", *(long long *)&rst);
	}
#endif
	
	for (i = 0; i < 360; i++){
//		rst = cos(i * M_PI / 180.0);
//		printf(".dword 0x%llx\n", *(long long *)&rst);
		x = -i * M_PI / 180.0;
		printf("%1.20f : %1.20f\n", sin(x), cos(x));
	}
	return 0;
}
