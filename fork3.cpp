/**
 * @file fork3.cpp
 * @brief
 * @version 1.0
 * @date 02/06/2017 12:30:00 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
int main(void)
{
    int i;
    const int N = 1;

    for(i=0; i<N; i++){
        fork();
        printf("-");
    }

    for (i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}
