#include <stdio.h>
#include <stdint.h>

static int foo(const char *format, ...) {
    return 0;
}

static int goo(const char *format, ...) {
    return foo(format);
}

int main()
{
    uint64_t a = 10;
    printf("a = %lu\n", a);

    goo("ads", 10);

	return 0;
}
