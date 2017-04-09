#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *s = "hello world\n";

char *GetMemory(void){
	char p[] = "hello worldslafjsldkjjsdladjflasjdfalsdfjalsdfjaljasldfjasljfalsdjfal\n";
//	char *p = s;
//	printf("GetMemory %p\n", p);
//	printf(p);
	return p;
}
void Test(void){
	char *str = NULL;
	str = GetMemory();
	printf("Test %p\n", str);
	printf(str);
}
int main()
{
	Test();

	return 0;
}
