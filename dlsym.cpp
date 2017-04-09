/**
 * @file dlsym.cpp
 * @brief
 * @version 1.0
 * @date 11/06/2015 04:36:58 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

#include "do_write.h"

using namespace std;

#define COUT std::cout << '[' << __FILE__ << ':' << __FUNCTION__ \
    << ':' << __LINE__ << ']'

int main()
{
    void *p;
    p = dlsym(RTLD_DEFAULT, "printf");
    COUT << "dlsym(RTLD_DEFAULT, \"printf\") = " << p << endl;
    p = dlsym(RTLD_NEXT, "printf");
    COUT << "dlsym(RTLD_NEXT, \"printf\") = " << p << endl;
    p = dlsym(RTLD_NEXT, "printf");
    COUT << "dlsym(RTLD_NEXT, \"printf\") = " << p << endl;

    // call puts
    printf("asd\n");
    printf("asd%d%s\n", 1, "asdf");
    fprintf(stdout, "asd\n");
    fprintf(stdout, "asd%d%s\n", 1, "asdf");

    p = dlsym(RTLD_DEFAULT, "write");
    COUT << "dlsym(RTLD_DEFAULT, \"write\") = " << p << endl;
    p = dlsym(RTLD_NEXT, "write");
    COUT << "dlsym(RTLD_NEXT, \"write\") = " << p << endl;
    p = dlsym(RTLD_NEXT, "write");
    COUT << "dlsym(RTLD_NEXT, \"write\") = " << p << endl;

    COUT << "dlsym(RTLD_DEFAULT, \"strlen\") = "
        << dlsym(RTLD_DEFAULT, "strlen")<< endl;
    COUT << "dlsym(RTLD_NEXT, \"strlen\") = "
        << dlsym(RTLD_NEXT, "strlen")<< endl;

    write(0, NULL, 0);

    const char *str = "asdfs";
    int i = strlen(str);

    COUT << strlen("asdf") << i << endl;

    do_write();

    sleep(100);
    return 0;
}

