/*
 * =====================================================================================
 *
 *       Filename:  gettimeofday.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2015 06:53:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <sys/time.h>

#include <iostream>

using namespace std;

int main()
{
    time_t tmp;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    tmp = tv.tv_sec;

    cout << tmp << endl;

    return 0;
}
