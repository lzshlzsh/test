#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;

int main(int argc, char **argv)
{
	char **pp = NULL;
	pid_t pid = fork();
	pid_t my_pid = getpid();

	if (0 == pid){
		if (execve("./getenv-simple", NULL, NULL) < 0){
			perror("execve");
			exit(errno);
		}
		exit(1);
	}

	if (wait(NULL) < 0){
		perror("wait");
		exit(errno);
	}
	printf("[%d]in %s\n", my_pid, argv[0]);
	for (pp = environ; *pp; pp++)
	  printf ("[%d]%s\n", my_pid, *pp);

	return 0;
}
