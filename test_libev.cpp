/*
 * =====================================================================================
 *
 *       Filename:  test_libev.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/04/2015 07:56:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <ev.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
#if EV_MULTIPLICITY
    cout << "EV_MULTIPLICITY defined" << endl;
#else
    cout << "EV_MULTIPLICITY NOT defined" << endl;
#endif    
    return 0;
}
