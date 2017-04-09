#include <stdio.h>
#include <stdint.h>

struct node {
	double a;
	int b;
	int c;
	char d;
};

struct empty_struct{
};

int main()
{
	char *lang[] = {"C", "Perl", "C#", "Python"};
    char *str = "MOVED";

	printf("sizeof(lang) = %ld\n", sizeof(lang));
	printf("sizeof(short) = %ld\n", sizeof(short));
	printf("sizeof(int) = %ld\n", sizeof(int));
	printf("sizeof(long int) = %ld\n", sizeof(long int));
	printf("sizeof(long long) = %ld\n", sizeof(long long));
	printf("sizeof(struct node) = %ld\n", sizeof(struct node));
	printf("sizeof(struct empty_struct) = %ld\n", sizeof(struct empty_struct));

    printf("sizeof(uint64_t) = %ld\n", sizeof(uint64_t));

	printf("sizeof(str) = %ld\n", sizeof(str));

    void *p_void = (void *)12;
    printf("%p, %p\n", p_void, p_void + 1);

	return 0;
}
