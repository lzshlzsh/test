#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

char *strsignal(int sig);

int* getPower(int i)
{
	static int result;
	result = pow(2, i);
	getchar();
	return &result;
}

void getPower_r(int i, int* result)
{
	*result = pow(2, i);
}

void handler (int signal_number)          /*处理SIGALRM信号*/
{
	printf("sig %s(%d) received\n", strsignal(signal_number), signal_number);
	getPower(3);
}

int main ()
{
	int *result;
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handler;
	sigaction(SIGALRM, &sa, NULL);
	result = getPower(5);
	printf("2^5 = %d\n", *result);
	return 0;
}
