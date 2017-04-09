/*
 * =====================================================================================
 *
 *       Filename:  strstream_float.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/25/2015 02:33:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>

using namespace std;


int main(int argc, char **argv)
{
	stringstream ss;

    for (int i = 0; i < 20; i++) {
        ss.clear();
        ss.str("");
        ss << i;
        cout << ss.str() << endl;
    }

	return 0;
}
