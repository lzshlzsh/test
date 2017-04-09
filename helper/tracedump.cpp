#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


int main(int argc, char **argv)
{
	int fd;
	int *buf = NULL;
	struct stat stat;
	
	assert(2 == argc);

	fd = open(argv[1], O_RDONLY);
	assert(fd > 0);

	assert(0 == fstat(fd, &stat));
	
	buf = (int *)mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	assert(-1 != (int)buf);

	for (unsigned int i = 0; i < stat.st_size / sizeof(int); i++){
		printf("%#x\n", buf[i]);
	}

	close(fd);

	return 0;
}
