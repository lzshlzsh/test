/**
 *	Created Time: 2009-11-28 11:00:13
 *	Last Modified: 2009-11-28 11:00:13
 *	File Name: define.c
 *	Description: 
 */
#include <stdio.h>

#define DEFINE(sym, val) \
	asm volatile("\n->" #sym " %0 " #val : : "i" (val))

struct Path
{
	int vfsmount, dentry;
};
struct Stru
{
	struct Path f_path;
#define vfsmount f_path.vfsmount
#define dentry f_path.dentry
};
int main(void)
{
	struct Stru inst;
	printf("%d, %d\n", inst.vfsmount, inst.dentry);

	struct Path f_path;

#define AAA 10


	printf("AAA = %d\n", AAA);

	printf("%d, %d\n", vfsmount, dentry);
	return 0;
}
