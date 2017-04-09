#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>


int main()
{
	int fd;  
	void *addr;
	int err;
	
	fd = open("/dev/urandom", O_RDONLY);	
	if (-1 == fd){
		perror("open: ");
		exit(-1);
	}
	
	addr = mmap(0, 16 << 10, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);	
	if (MAP_FAILED == addr){
		perror("mmap: ");
		exit(-1);
	}
	printf("mmap: %p\n", addr);	
	err = pread(fd, addr, 32 << 10, 0);
	if (-1 == err){
		perror("pread: ");
		exit(-1);
	}

	printf("pread: %d\n", err);

	munmap(addr, 100);

	return 0;
}
