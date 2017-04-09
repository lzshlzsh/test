/*
 * =====================================================================================
 *
 *       Filename:  builtin-gcc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/20/2015 01:16:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int i = 0x2342300;
    int zero = 0;
    int imax = 0xffffffff;

    cout << std::hex << std::showbase;
    cout << "__builtin_ffs(" << i << ") = " <<  __builtin_ffs(i) << endl;
    cout << "__builtin_ffs(" << zero << ") = " << __builtin_ffs(zero) << endl;
    cout << __builtin_ffs(imax) << endl;

    cout << __builtin_ctz(i) << endl;
    cout << __builtin_ctz(zero) << endl;
    cout << __builtin_ctz(imax) << endl;

    return 0;
}
