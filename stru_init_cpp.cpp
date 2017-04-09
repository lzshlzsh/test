/*
 *Created Time: 2009-07-31 20:32:52
 *Last Modified: 2009-07-31 20:35:08
 *File Name: stru_init.cpp
 *Description: 
 */
#include <stdio.h>
int main()
{
	struct emtpy_struct{
	};
	printf("sizeof(struct emtpy_struct) = %d\n", sizeof(struct emtpy_struct));
	return 0;
}
