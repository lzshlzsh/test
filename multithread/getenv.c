#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char **argv)
{
	char **pp = NULL;
#if 0
	pid_t pid = fork();

	if (0 == pid){
		execve("./getenv-simple", NULL, NULL);
		return 0;
	}
	printf("in %s\n", argv[0]);
#endif	
	for (pp = environ; *pp; pp++)
	  printf ("%s\n", *pp);

	return 0;
}
