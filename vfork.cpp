/**
 * @file vfork.cpp
 * @brief
 * @version 1.0
 * @date 02/05/2017 07:59:55 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>


int main(void)
{
    int count = 1;
    int child;

    // child = vfork( );

    printf("Before create son, the father's count is:%d\n", count);

    if((child = vfork())< 0)
    {
        perror("fork error : ");
    }
    else if(child == 0)     //  fork return 0 in the child process because child can get hid PID by getpid( )
    {
        ++count;
        printf("This is son, his count is: %d (%p). and his pid is: %d\n", count, &count, getpid());
        exit(0);
    }
    else                    //  the PID of the child process is returned in the parent’s thread of execution
    {
        ++count;
        printf("After son, This is father, his count is: %d (%p), his pid is: %d\n", count, &count, getpid());
    }

    return EXIT_SUCCESS;
}

