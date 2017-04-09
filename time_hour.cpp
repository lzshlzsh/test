/*
 * =====================================================================================
 *
 *       Filename:  time_hour.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/2015 09:01:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <time.h>
#include <stdint.h>

#include <iostream>

using namespace std;

int main()
{
    time_t tm = time(NULL);
    struct tm st_tm;

    localtime_r(&tm, &st_tm);

    cout << st_tm.tm_hour << endl;

    cout << sizeof(uint32_t) << "," << sizeof(time_t) << endl;

    return 0;
}
