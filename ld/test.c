/**
 *	Created Time: 2009-07-31 23:32:02
 *	Last Modified: 2009-07-31 23:32:02
 *	File Name: test.c
 *	Description: 
 */
#include <stdio.h>
#define host_termios termios
#include <asm/termbits.h>
#include <time.h>

#define Snd Snd_aes
struct Snd
{
	int a, b, c;
};
#undef Snd

extern char __executable_start[];
int main()
{
	int A[10] = {2, 3, 0};
	int *p_int = &A[1];
	int b = 2;
	int a = b + *p_int++;
	printf("%d, %d\n", a, sizeof(struct host_termios));
	printf("%d\n", sizeof(struct termios));


	struct Snd_aes snd;

	printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);

	printf("__executable_start = %p\n", __executable_start);
	return 0;
}
