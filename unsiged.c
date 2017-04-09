#include <stdio.h>


void foo()
{
	unsigned short i;
	int sum = 0;
	int flag = 1;
	int t;

	for (i = 65535; i>= 0; i--){
		if (flag){
			flag = 0;
			t = 65536;
			sum += t % 3;
		}else{
			sum += --t % 3;
			if (t <= 0){
				printf("%d, %d\n", sum, i);
				break;
			}
		}
	}
}

int main()
{
	foo();
	return 0;
}



