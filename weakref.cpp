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

extern "C" {

__attribute__ ((weakref, alias("y"))) static void foo();

__attribute__((weakref)) int i = 20;

}

int main()
{
    printf("%d\n", i);
    foo();
}
