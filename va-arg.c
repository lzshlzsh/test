#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void demo(char *msg, ...)
{
	va_list argp;
	char *arg;

	printf("%s", msg);

	va_start(argp, msg);

	while (1){
		arg = va_arg(argp, char *);
		printf("%s", arg);
		if (!strcmp(arg, "\n")){
			break;
		}
	}

	va_end(argp);
}

int main()
{
	demo("hello, ", "world", "\n");
	return 0;
}
