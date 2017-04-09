#include <unordered_set>
#include <iostream>

using namespace std;


int main()
{
	hash<const char*> H;
	cout << "foo -> " << H("foo") << endl;
	cout << "bar -> " << H("bar") << endl;
	cout << "foo -> " << H("foo") << endl;
	cout << "bar -> " << H("bar") << endl;
}
