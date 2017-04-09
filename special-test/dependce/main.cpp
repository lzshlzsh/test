/**
 *	Created Time: 2009-09-11 11:19:13
 *	Last Modified: 2009-09-11 11:19:13
 *	File Name: main.cpp
 *	Description: 
 */
#include <stdio.h>

extern int y, x;

int main()
{

	printf("x = %d, y = %d\n", x, y);

	x = 5;
	y = 6;

	return 0;
}
