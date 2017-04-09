/*
 * =====================================================================================
 *
 *       Filename:  daemon.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/18/2015 04:38:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    char strCurPath[PATH_MAX];

    if(daemon(1, 1) < 0)
    {
        perror("error daemon.../n");
        exit(1);
    }
    sleep(10);

    if(getcwd(strCurPath, PATH_MAX) == NULL)
    {
        perror("error getcwd");
        exit(1);
    }
    printf("%s/n", strCurPath);

    sleep(10);
    return 0;
}

