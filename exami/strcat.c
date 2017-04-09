#include <stdio.h>


static char * my_strcat(char *d, const char *s)
{
	
	char *t = d;

	while (*t){
		t++;
	}

	while((*t++ = *s++));

	return d;
}
int main()
{
	char a[100] = "abc";

	my_strcat(a, "edf");

	printf("%s\n", a);

	return 0;
}
