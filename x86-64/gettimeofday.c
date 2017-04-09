#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

int main()
{
	struct timeval tval;

	if (gettimeofday(&tval, NULL) < 0){
		printf("error\n");
	}
	
	printf("tv_sec: %d, tv_usec: %d\n", (int)tval.tv_sec, (int)tval.tv_usec);
	
	return 0;
}
