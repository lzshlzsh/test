/**
* @file foo.h
* @brief
* @version 1.0
* @date 04/09/2017 04:25:30 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#ifndef  __FOO_H__
#define  __FOO_H__

#include <stdio.h>

int goo();

class Foo {
public:
    virtual ~Foo() {}
};

template <typename T>
int too(T a) {
    printf("a = %d\n", a);
    return 0;
}

#endif

