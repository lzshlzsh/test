#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    omp_set_num_threads(1);
#pragma omp parallel
#pragma omp master
    {
        printf("Hello, World!, ThreadId=%d\n", omp_get_num_threads());
    }

    return 0;
}
