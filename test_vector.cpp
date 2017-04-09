/*
 * =====================================================================================
 *
 *       Filename:  vector.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/29/2015 09:41:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int print_v(const vector<int> &v)
{
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	return 0;
}

struct Pref {
	bool operator() (const int i) {return i == 2;}
};

int main(int argc, char **argv)
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	int *ref = &v.back();
	print_v(v);
	*ref = 5;
	print_v(v);

	vector<int>::iterator it = find_if(v.begin(), v.end(), Pref());
	if (it != v.end()) {
		ref = &*it;
		*ref = 6;
	}
	print_v(v);

	return 0;
}
