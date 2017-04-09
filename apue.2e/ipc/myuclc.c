#include "apue.h"
#include <ctype.h>

int
main(void)
{
	int		c;
	char str[5] = {'\0', '\0', '\0', '\0', '\0'};
	str[4] = '\0';
	int i = 0, j;
	char tmp;

	while ((c = getchar()) != EOF) {
		if (islower(c))
			c = toupper(c);
		if (i >= 4){
			tmp = str[0];	
			for (j = 0; j < 4; j++){
				str[j] = str[j + 1];
			}
			i = 3;
		}
		if ('\n' != c){
			str[i++] = (char)c;
		}else{
			i = 0;
			str[0] = '\0';
		}
		if (putchar(c) == EOF)
			err_sys("output error");
		if (c == '\n')
			fflush(stdout);
/*		puts(str);
		fflush(stdout);*/
		if (!strcmp(str, "QUIT") || !strcmp(str, "EXIT")){
			putchar('\n');
			exit(0);
		}
	}
	exit(0);
}
