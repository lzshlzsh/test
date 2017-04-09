#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static const size_t MMAP_SIZE = 2U * 1024 * 1024 * 1024;

int main(int argc, char **argv)
{
	void *addr;
	int fd;

	if ((fd = open("testaaa", O_RDWR)) < 0){
		perror("open");
		exit(errno);
	}

    if ((void *)-1 == (addr = mmap(0, MMAP_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
                MAP_SHARED | MAP_ANONYMOUS, fd, 0))){
		perror("mmap");
		exit(errno);
	}

	close(fd);


    memset(addr, 0, MMAP_SIZE);

    sleep(100);

	munmap(addr, MMAP_SIZE);
	return 0;
}
