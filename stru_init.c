/*
 *Created Time: 2009-07-31 20:32:52
 *Last Modified: 2009-07-31 20:35:08
 *File Name: stru_init.cpp
 *Description: 
 */
#include <stdio.h>
int main()
{
	struct Stru
	{
		int a, b;
	};
	struct Stru s = {
		.a = 0,
		.b = 1
	};
	struct emtpy_struct{
	};
	printf("s = {%d, %d}\n", s.a, s.b);
	printf("sizeof(struct emtpy_struct) = %d\n", sizeof(struct emtpy_struct));
	return 0;
}
