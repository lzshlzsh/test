#include <cstddef>
#include <iostream>

using namespace std;


class LocateNewDelete {
	int i;
public:	
	LocateNewDelete(int i) : i(i)
	{
		cout << "LocateNewDelete()" << endl;
		throw int(1);
	}
	~LocateNewDelete(){cout << "~LocateNewDelete()" << endl;}
	void *operator new(size_t sz, void *addr)
	{
		cout << "new " << sz << " at " << addr << endl;
		return addr;
	}
	void operator delete(void *addr, void *addr2)
	{
		cout << "delete " << addr << " at " << addr2 << endl;
	}
	void operator delete(void *addr)
	{
		cout << "delete " << addr << endl;
	}
};

int main()
{
	int array[10];

	try {
		LocateNewDelete *lnd = new(array) LocateNewDelete(0);

		delete lnd;
	}catch (int ei){
		cout << "exception " << ei << endl;
	}

	return 0;
}
