#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class A
{
public:	
	typedef T PI;
	PI pi;

	A(): pi(PI()) {}
};

int main()
{
	int a = 0;
	vector<int>::pointer p = &a;

	*p = 1;

	cout << a << endl;

	A<int *> aa;

	cout << aa.pi << endl;

	return 0;
}
