#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE *file;

	file = popen("/home/lzs/programming/test/helloworld", "r");
	if (NULL == file){
		fprintf(stderr, "popen error\n");
		exit(1);
	}
	pclose(file);
	return 0;
}
