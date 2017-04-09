#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	if (-1 == wait(NULL)){
		perror("wait");
		exit(errno);
	}
	return 0;
}
