/**
 * @file foo.cpp
 * @brief
 * @version 1.0
 * @date 04/09/2017 03:41:19 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */

#include "foo.h"

__attribute__((weak)) int a;
int b = 10;
int c;
//__attribute__((weak)) double f;
double f;

int goo() {
    Foo foo;
    too(10);
    f = 1.2e-19;
    printf("addr(f) = %p\n", &f);
    printf("f = %f\n", f);
}

