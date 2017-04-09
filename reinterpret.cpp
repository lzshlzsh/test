/**
 *	Created Time: 2009-09-10 17:10:33
 *	Last Modified: 2009-09-10 17:10:33
 *	File Name: reinterpret.cpp
 *	Description: 
 */

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

ofstream out("reinterp.out");

class X
{
	enum {sz = 5};
	int a[sz];
public:
	X() {memset(a, 0, sz * sizeof(int));}
	virtual void f(){}
	int membsize() {return sizeof(a);}

	friend ostream & operator << (ostream &os , const X &x)
	{
		for (int i = 0; i < sz; i++)
		  os << x.a[i] << ' ';
		return os;
	}
};

int main()
{
	X x;
	cout << x << endl;
	int *xp = reinterpret_cast<int *>(&x);
	xp[1] = 47;
	cout << x << endl;

	X x2;
	const int vptr_size = sizeof(X) - x2.membsize();
	long l = reinterpret_cast<long>(&x2);
	l += vptr_size;
	xp = reinterpret_cast<int *>(l);

	xp[1] = 47;
	cout << x2 << endl;
	return 0;
}
