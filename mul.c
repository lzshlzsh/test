#include <stdio.h>

int main()
{
    unsigned int a, b;
    unsigned long long c;

    a = 0xffffffff;
    b = 2;

    c = (unsigned long long)a * (unsigned long long)b;
    printf("a = %#x, b = %#x, c = %#llx\n", a, b, c);

    return 0;
}

