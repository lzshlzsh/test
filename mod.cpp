/*
 * =====================================================================================
 *
 *       Filename:  mod.cpp
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  01/27/2015 09:55:10 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdint.h>

#include <iostream>

using namespace std;

int main()
{
	int lat = -11, lng = -12;
	uint32_t offset = (lat % 10) * 10 + (lng % 10);
	int y = static_cast<int>(offset) % 10;
	int x = (static_cast<int>(offset) - y) / 10;

	cout << offset << endl;
	cout << x << endl;
	cout << y << endl;

	return 0;
}
