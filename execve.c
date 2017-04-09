#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char **argv)
{
#if 1	
	if (!fork()){
		printf("[%d]child\n", getpid());
		if (execve(argv[1], argv, environ) < 0){
			perror("execve");
			exit(errno);
		}
		exit(0);
	}

	if (wait(NULL) < 0){
		perror("wait");
		exit(errno);
	}
#else
	if (execve(argv[1], NULL, environ) < 0){
		perror("execve");
		exit(errno);
	}
#endif
	return 0;
}
