#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	const char *null = NULL;

	if (access(argv[0], R_OK | X_OK) < 0){
		perror("access");
		exit(errno);
	}

	if (access(null, R_OK | X_OK) < 0){
		perror("access");
		exit(errno);
	}

	return 0;
}
