/**
 *	Created Time: 2009-11-29 16:03:04
 *	Last Modified: 2009-11-29 16:03:04
 *	File Name: typeof.c
 *	Description: 
 */

#include <stdio.h>

int main()
{
	__typeof__ (char *) x;
	char y;
	x = &y;

	__typeof__(__typeof__(char *)[5]) xx;
	xx[0] = x;
	return 0;
}
