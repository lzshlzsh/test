#include <signal.h>
#include <stdio.h>

int main ()
{
	struct sigaltstack x;
	int buf[1024];
	x.ss_sp = buf;
	x.ss_size = sizeof buf;
	x.ss_flags = 0;
	if (sigaltstack(&x,NULL) < 0) {
		perror("callee sigaltstack");
		return 1;
	} else {
		printf("callee sigaltstack ok\n");
		return 0;
	}
} 
