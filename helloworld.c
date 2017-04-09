#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

static void foo()
{
	printf("helloworld\n");
}


int main()
{
	foo();
	foo();
	foo();
	foo();

    while (1) {
        usleep(10000);
    }
	return 0;
}
