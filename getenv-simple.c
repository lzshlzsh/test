#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


extern char **environ;

int main(int argc, char **argv)
{
	char **pp = NULL;
	pid_t pid = getpid();

	printf("[%d]HOME: %s\n", pid, getenv("HOME"));
	printf("[%d]in %s\n", pid, argv[0]);
	for (pp = environ; *pp; pp++)
	  printf ("[%d]%s\n", pid, *pp);

	return 0;
}
