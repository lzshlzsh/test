/*
 * =====================================================================================
 *
 *       Filename:  test_string.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2015 08:57:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;

    str.resize(1024);

    cout << str.size() << endl;

    str.clear();
    cout << str.size() << endl;

    return 0;
}
