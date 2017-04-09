/*
 * =====================================================================================
 *
 *       Filename:  aa.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/18/2015 09:55:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <fstream>

using namespace std;

class A {
public:
	A() {
		ofstream ofs("aa.txt", ofstream::app);
		ofs << "A" << getpid() << endl;
	}
	~A() {
		ofstream ofs("aa.txt", ofstream::app);
		ofs << "~A" << getpid() << endl;
	}
	int f() {
		fork();
		return 0;
	}
};

int main()
{
	class A a;
	a.f();

	int i = 10;
	i++;

	int j[i] = {1, };

	cout << j[0] << endl;

	return 0;
}
