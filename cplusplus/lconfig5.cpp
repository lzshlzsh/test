#include <iostream>

using namespace std;

template <typename T, typename O>
class TestClass
{
public:
	TestClass() { cout << "T, O" << endl; }
};

template <typename T>
class TestClass<T *, T *>
{
public:
	TestClass() { cout << "T *, T *" << endl; }
};

template <typename T>
class TestClass<const T *, T *>
{
public:
	TestClass() { cout << "const T &, T *" << endl; }
};

int main()
{
	TestClass<int, int> i1;
	TestClass<int *, int *> i2;
	TestClass<const int *, int *> i3;

	return 0;
}


