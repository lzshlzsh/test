#include <iostream>

using namespace std;

template <typename T1, typename T2>
class SomeTemplate {
public:
	SomeTemplate(){cout << "SomeTemplate(): T1, T2" << endl;}
	~SomeTemplate(){cout << "~SomeTemplate(): T1, T2" << endl;}
};

template <typename T1>
class SomeTemplate<T1, int> {
public:
	SomeTemplate() {cout << "SomeTemplate(): T1, int" << endl;}
	~SomeTemplate() {cout << "~SomeTemplate(): T1, int" << endl;}
};

int main()
{
	SomeTemplate<char, long> cl;
	SomeTemplate<char, int> ci;
	return 0;
}
