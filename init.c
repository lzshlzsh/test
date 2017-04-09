/*
 *Created Time: 2009-07-31 20:20:24
 *Last Modified: 2009-07-31 20:20:24
 *File Name: init.c
 *Description: 
 */
#include <stdio.h>

int main()
{
	int A[10] = {[0 ... 9] = 1};
	int B[10];
	int i;
	for (i = 0; i < 10; i++)
	  printf("A[%d] = %d, B[%d] = %d\n", i, A[i], i, B[i]);
	
	return 0;
}
