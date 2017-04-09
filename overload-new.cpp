#include <cstdio>
#include <cstdlib>

using namespace std;


class A {
public:
	A() {puts("A()");}
	~A() {puts("~A()");}
	void *operator new(size_t sz)
	{
		void *addr;
		addr = malloc(sz);
		if (!addr){
			puts("no memory\n");
		}
		printf("new %d at %p\n", sz, addr);
		return addr;
	}

	void operator delete(void *addr)
	{
		printf("delete at %p\n", addr);
	}
};


class B : public A{
};
int main()
{
	int *p = new int[10];
	delete []p;
	
	A *pa = new A();
	delete pa;

	A *par = new A[3];
	delete []par;

	B *pb = new B;
	delete pb;

	return 0;
}
