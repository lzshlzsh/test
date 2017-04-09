/*
 * =====================================================================================
 *
 *       Filename:  test_ucontext.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/23/2015 08:00:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <ucontext.h>

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    cout << __builtin_offsetof(ucontext, uc_mcontext) << endl;
    return 0;
}
