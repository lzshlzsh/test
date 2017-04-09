#include <stdio.h>

int main()
{
#define PAGE_SHIFT 12	
	int incr = 9;
	int align = 0x3fff;//0x1000;

	incr = align >> PAGE_SHIFT ? : 1;

	printf("incr: %d\n", incr);
	return 0;
}

