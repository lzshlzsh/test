/*
 * =====================================================================================
 *
 *       Filename:  uin_list.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/05/2015 03:53:59 PM
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

int main(int argc, char **argv)
{
	uint32_t range = 2500, scale1 = 2000, scale2 = 3000;
	uint32_t count1 = 30642192, count2 = 10948624;
	double r = static_cast<double>(range);
	double r1 = static_cast<double>(scale1);
	double c1 = static_cast<double>(count1);
	double r2 = static_cast<double>(scale2);
	double c2 = static_cast<double>(count2);
	uint32_t count = static_cast<uint32_t>(r * (r * (c1 * r2 - c2 * r1) + c2 * r1 * r1 - 
				c1 * r2 * r2) / r1 / r2 / (r1 - r2));

	cout << count << endl;

	return 0;
}
