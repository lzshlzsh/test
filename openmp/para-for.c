#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	int i;

#pragma omp parallel for
	for (i = 0; i < 10; i++ ){
		printf("[%d]i = %d\n", omp_get_thread_num(), i);
	}
	return 0;
}
