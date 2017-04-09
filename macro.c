/**
 *	Created Time: 2009-11-24 17:05:03
 *	Last Modified: 2009-11-24 17:05:03
 *	File Name: macro.c
 *	Description: 
 */
#include <stdio.h>

#define STRUCT(zero, list...) printf("%s\n", #list)
#define VERBOSE(a, b, c) a ## b ## c

#define CONF_ROOT "/apps"
#define LOG_MOD "log"
#define LOG_PATH CONF_ROOT"/"LOG_MOD"/log_path"

int main()
{
	char *ABC = "ABC";
//	STRUCT(0, 1, 2);
//	printf("%s\n", VERBOSE(A, B, C));
    printf("%s\n", LOG_PATH);
	return 0;
}
