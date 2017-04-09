/*
 * =====================================================================================
 *
 *       Filename:  mktime.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  01/24/2015 07:42:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <time.h>

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	struct tm tm;
	time_t now, t;

	now = time(NULL);

	localtime_r(&now, &tm);

	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;

	t = mktime(&tm);

	cout << ctime(&t) << endl;

	return 0;
}
