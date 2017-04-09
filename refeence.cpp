/*
 * =====================================================================================
 *
 *       Filename:  refeence.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/14/2015 12:09:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

int main()
{
    int i = 12;
    const int &j = i;

    cout << &i << ", " << &j << endl;

    return 0;
}
