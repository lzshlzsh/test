/**
* @file test_pu_closure.cpp
* @brief
* @version 1.0
* @date 05/19/2017 09:12:45 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include "pu_closure.h"

using namespace r2::pu;

int foo0() {return 0;}
int foo1(int i1) {return 0;}
int foo2(int i1, int i2) {return 0;}
int foo3(int i1, int i2, int i3) {return 0;}
int foo4(int i1, int i2, int i3, int i4) {return 0;}
int foo5(int i1, int i2, int i3, int i4, int i5) {return 0;}
int foo6(int i1, int i2, int i3, int i4, int i5, int i6) {return 0;}
int foo7(int i1, int i2, int i3, int i4, int i5, int i6, int i7) {return 0;}
int foo8(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8) {return 0;}

int main(int argc, char **argv) {
    SubCoroutine closure;

    closure.bind(foo0);
    closure.bind(foo1, 1);
    closure.bind(foo2, 1, 2);

    return 0;
}

