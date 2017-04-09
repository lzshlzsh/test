#include <stdio.h>

int main()
{
	int i = 1; 
	for (i = 0; i < 5; i++){
		switch (i){
		case 0:
			printf("%d\n", i);
			break;
		case 1:
			printf("%d\n", i);
			continue;
		default:
			printf("%d\n", i);
			break;
		}
		printf("after switch\n");
	}
	return 0;
}
