/*
 * =====================================================================================
 *
 *       Filename:  weakref.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  10/09/2014 07:55:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>

#include "foo.h"

extern "C" {

__attribute__ ((weakref, alias("y"))) static void foo();

__attribute__((weak)) int f;

}

int main()
{
    printf("addrof(foo) = %p\n", foo);
    printf("sizeof(f) = %ld\n", sizeof(f));
    f = 14999999;
    printf("f = %f\n", f);
    goo();

    return 0;
}
