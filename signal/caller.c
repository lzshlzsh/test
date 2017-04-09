#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
	struct sigaltstack x;
	int buf[16384];
	int pid;

	x.ss_sp = buf;
	x.ss_size = sizeof buf;
	x.ss_flags = 0;
	if (sigaltstack(&x,NULL) < 0) {
		perror("caller sigaltstack");
		return 1;
	} else {
		printf("caller sigaltstack ok\n");
	}
	pid = fork();
	if (pid < 0) {
		perror("caller fork");
		return 1;
	} else if (pid == 0) {
		execlp("./callee","callee",NULL);
		perror("exec");
		return -1;
	} else {
		sleep(1);
		return 0;
	}
} 
