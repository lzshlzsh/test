/*
 * =====================================================================================
 *
 *       Filename:  lambda.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/05/2015 10:29:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

int main()
{
    int a[10];
    int total = 0;

    iota(a, a + sizeof(a) / sizeof(a[0]), 1);

    for_each(a, a + sizeof(a) / sizeof(a[0]), [&total](const int i)->int {
        total += i;
        cout << i << "->" << total << endl;
        return i;
    });

    return 0;
}
