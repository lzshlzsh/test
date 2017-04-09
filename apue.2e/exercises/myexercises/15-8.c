#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <errno.h>

#define MAXLINE  4096

int main()
{
	FILE *file;
	char line[MAXLINE];
	
	file = popen("/bin/ls -l | grep pipe", "r");
	if (NULL == file){
		perror("open error");
		exit(errno);
	}

#if 0
	while (NULL != fgets(line, MAXLINE, file)){
		puts(line);
	}

	if (ferror(file)){
		perror("fgets");
		exit(errno);
	}
#endif
	if (-1 == pclose(file)){
		perror("pclose error");
		exit(errno);
	}
	return 0;
}


