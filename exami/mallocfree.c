#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Test(void){
	char *str = (char *) malloc(100);
	strcpy(str, "hello\n");
	free(str);
	if(str != NULL){
//		strcpy(str, "world\n");
		printf(str);
	}
}

int main()
{
	Test();

	return 0;
}
