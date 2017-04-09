#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>


int main()
{

	if (open ("sf", O_RDONLY) < 0){
		perror("open");
		printf("errno: %d\n", errno);
		exit(errno);
	}

	return 0;
}
