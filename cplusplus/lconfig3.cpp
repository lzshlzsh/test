#include <iostream>

using namespace std;

template <typename T>
class A 
{
public:
	static int m_data;
};


template<>
int A<int>::m_data = 1;
template<>
int A<char>::m_data = 2;
template<>
int A<float>::m_data = 3;

int main()
{
	cout << A<int>::m_data << ", " << A<char>::m_data << ", "
		<< A<float>::m_data << endl;
	cout << "*********************************" << endl << endl;

	A<int> i1, i2;
	A<char> c1, c2;
	A<float> f1, f2;

	cout << i1.m_data << ", " << c1.m_data << ", "
		<< f1.m_data << endl;
	cout << i2.m_data << ", " << c2.m_data << ", "
		<< f2.m_data << endl;
	cout << A<int>::m_data << ", " << A<char>::m_data << ", "
		<< A<float>::m_data << endl;
	cout << "*********************************" << endl << endl;

	i1.m_data = 4;
	c2.m_data = 5;
	f1.m_data = 6;

	cout << i1.m_data << ", " << c1.m_data << ", "
		<< f1.m_data << endl;
	cout << i2.m_data << ", " << c2.m_data << ", "
		<< f2.m_data << endl;
	cout << A<int>::m_data << ", " << A<char>::m_data << ", "
		<< A<float>::m_data << endl;

	return 0;
}

