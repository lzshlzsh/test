/**
* @file page_size.cpp
* @brief
* @version 1.0
* @date 04/18/2017 08:36:25 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
    printf("page size: 0x%lx\n", sysconf(_SC_PAGE_SIZE));
    return 0;
}

