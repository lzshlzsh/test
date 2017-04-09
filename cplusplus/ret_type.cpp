#include <iostream>

using namespace std;

template <typename T>
class A {
public:
	T *foo()
	{
		return new T(1);
	}
	const T *foo(int a) const
	{
		return new T(2);
	}
};

template <typename T>
T *foo()
{
	return new T(1);
}
template <typename T>
const T *foo(int a)
{
	return new T(2);
}

int main()
{
	return 0;
}
